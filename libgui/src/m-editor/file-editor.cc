/*

Copyright (C) 2011-2015 Jacob Dawid

This file is part of Octave.

Octave is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

Octave is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with Octave; see the file COPYING.  If not, see
<http://www.gnu.org/licenses/>.

*/

#if defined (HAVE_CONFIG_H)
#  include "config.h"
#endif

#if defined (HAVE_QSCINTILLA)

#include "file-editor.h"
#include "resource-manager.h"
#include "shortcut-manager.h"

#include <QVBoxLayout>
#include <QApplication>
#include <QFile>
#include <QFont>
#include <QFileDialog>
#include <QMessageBox>
#include <QStyle>
#include <QTextStream>
#include <QTabBar>
#include <QProcess>
#include <QInputDialog>
#include <Qsci/qscicommandset.h>

#include "octave-link.h"
#include "utils.h"
#include "main-window.h"
#include <oct-map.h>

file_editor::file_editor (QWidget *p)
  : file_editor_interface (p)
{
  // Set current editing directory before construct because loaded
  // files will change ced accordingly.
  ced = QDir::currentPath ();

  // set action that are later added by the main window to null,
  // preventing access to them when they are still undefined
  _undo_action = 0;
  _copy_action = 0;
  _paste_action = 0;
  _selectall_action = 0;

  construct ();

  setVisible (false);
  setAcceptDrops(true);

  _file_encoding = QString ();  // for selecting an encoding in open dialog
}

file_editor::~file_editor (void)
{
  if (_mru_file_menu)
    delete _mru_file_menu;
}

bool
file_editor::check_closing (void)
{
  // When the applications is closing all editor tabs are checked whether
  // they need to be saved. During these ckecked the tabs are not closed
  // since the user might cancel closing octave during one of these saving
  // dialogs. Therefore, saving the session for restoring at next start
  // is not done before the application is definitely closing

  // Have all file editor tabs signal what their filenames are.
  editor_tab_map.clear ();
  emit fetab_file_name_query (0);

  // Save all tabs with confirmation.
  file_editor_tab::reset_cancel ();
  emit fetab_check_modified_file ();

  // If there was a cancellation, make the already saved/discarded tabs
  // recovering from the exit by removing the read-only state and by
  // recovering the debugger breakpoints. Finally return false in order to
  // cancel closing the application
  if (file_editor_tab::was_cancelled ())
    {
      emit fetab_recover_from_exit ();
      return false;
    }

  // Here, the application will be closed -> store the session

  // Save open files for restoring in next session; this only is possible
  QSettings *settings = resource_manager::get_settings ();

  // save filenames (even if last session will not be restored next time)
  // together with encoding and the tab index
  QStringList fetFileNames;
  QStringList fet_encodings;
  QStringList fet_index;

  // save all open tabs before they are definitely closed
  for (editor_tab_map_const_iterator p = editor_tab_map.begin ();
       p != editor_tab_map.end (); p++)
    {
      QString file_name = p->first;   // get file name of tab
      if (! file_name.isEmpty ())      // do not append unnamed files
        {
          fetFileNames.append (file_name);
          fet_encodings.append (editor_tab_map[file_name].encoding);
          QString index;
          fet_index.append (index.setNum
             (_tab_widget->indexOf (editor_tab_map[file_name].fet_ID)));
        }
    }

  settings->setValue ("editor/savedSessionTabs", fetFileNames);
  settings->setValue ("editor/saved_session_encodings", fet_encodings);
  settings->setValue ("editor/saved_session_tab_index", fet_index);
  settings->sync ();

  // Finally close all the tabs and return indication that we can exit
  // the application
  for (int i = 0; i < _tab_widget->count (); i++)
    {
      delete _tab_widget->widget (i);
      _tab_widget->removeTab (i);
    }

  return true;
}

void
file_editor::focus (void)
{
  octave_dock_widget::focus ();

  // set focus to current tab
  QWidget *fileEditorTab = _tab_widget->currentWidget ();
  if (fileEditorTab)
    emit fetab_set_focus (fileEditorTab);
}

void
file_editor::update_octave_directory (const QString& dir)
{
  ced = dir;
  emit fetab_set_directory (ced);  // for save dialog
}

QMenu *
file_editor::debug_menu (void)
{
  return _debug_menu;
}

QToolBar *
file_editor::toolbar (void)
{
  return _tool_bar;
}

void
file_editor::handle_enter_debug_mode (void)
{
  _run_action->setEnabled (false);
  _run_action->setShortcut (QKeySequence ());
}

void
file_editor::handle_exit_debug_mode (void)
{
  _run_action->setEnabled (true);
  shortcut_manager::set_shortcut (_run_action, "editor_run:run_file");
}

void
file_editor::request_new_file (const QString& commands)
{
  // Custom editor? If yes, we can only call the editor without passing
  // some initial contents and even without being sure a new file is opened
  if (call_custom_editor ())
    return;

  // New file isn't a file_editor_tab function since the file
  // editor tab has yet to be created and there is no object to
  // pass a signal to.  Hence, functionality is here.

  file_editor_tab *fileEditorTab = new file_editor_tab (ced);
  if (fileEditorTab)
    {
      add_file_editor_tab (fileEditorTab, "");  // new tab with empty title
      fileEditorTab->new_file (commands);       // title is updated here
      focus ();                                 // focus editor and new tab
    }
}

void
file_editor::request_new_script (const QString& commands)
{
  request_new_file (commands);
}

void
file_editor::request_new_function (bool)
{
  bool ok;
  // get the name of the new function
  QString new_name = QInputDialog::getText (this, tr ("New Function"),
                     tr ("New function name:\n"), QLineEdit::Normal, "", &ok);
  if (ok && new_name.length () > 0)
    {
      // append suffix if it not already exists
      if (new_name.rightRef (2) != ".m")
        new_name.append (".m");
      // check whether new files are created without prompt
      QSettings *settings = resource_manager::get_settings ();
      if (! settings->value ("editor/create_new_file",false).toBool ())
        {
          // no, so enable this settings and wait for end of new file loading
          settings->setValue ("editor/create_new_file",true);
          connect (this, SIGNAL (file_loaded_signal ()),
                   this, SLOT (restore_create_file_setting ()));
        }
      // start the edit command
      emit execute_command_in_terminal_signal ("edit " + new_name);
    }
}

void
file_editor::restore_create_file_setting ()
{
  // restore the new files creation setting
  QSettings *settings = resource_manager::get_settings ();
  settings->setValue ("editor/create_new_file",false);
  disconnect (this, SIGNAL (file_loaded_signal ()),
              this, SLOT (restore_create_file_setting ()));
}

void
file_editor::request_open_file (void)
{
  // Open file isn't a file_editor_tab function since the file
  // editor tab has yet to be created and there is no object to
  // pass a signal to.  Hence, functionality is here.

  // Create a NonModal message.
  QFileDialog *fileDialog = new QFileDialog (this);
  fileDialog->setNameFilter (tr ("Octave Files (*.m);;All Files (*)"));

  // Giving trouble under KDE (problem is related to Qt signal handling on unix,
  // see https://bugs.kde.org/show_bug.cgi?id=260719 ,
  // it had/has no effect on Windows, though)
  fileDialog->setOption(QFileDialog::DontUseNativeDialog, true);

  // define a new grid layout with the extra elements
  QGridLayout *extra = new QGridLayout (fileDialog);
  QFrame *separator = new QFrame (fileDialog);
  separator->setFrameShape (QFrame::HLine);   // horizontal line as separator
  separator->setFrameStyle (QFrame::Sunken);

  // combo box for encoding
  QLabel *label_enc = new QLabel (tr ("File Encoding:"));
  QComboBox *combo_enc = new QComboBox ();
  resource_manager::combo_encoding (combo_enc);
  _file_encoding = QString ();  // default, no special encoding

  // track changes in the combo boxes
  connect (combo_enc, SIGNAL (currentIndexChanged (QString)),
           this, SLOT (handle_combo_enc_current_index (QString)));

  // build the extra grid layout
  extra->addWidget (separator,0,0,1,3);
  extra->addWidget (label_enc,1,0);
  extra->addWidget (combo_enc,1,1);
  extra->addItem   (new QSpacerItem (1,20,QSizePolicy::Expanding,
                                          QSizePolicy::Fixed), 1,2);

  // and add the extra grid layout to the dialog's layout
  QGridLayout *dialog_layout = dynamic_cast<QGridLayout*> (fileDialog->layout ());
  dialog_layout->addLayout (extra,dialog_layout->rowCount (),0,
                                  1,dialog_layout->columnCount ());

  fileDialog->setAcceptMode (QFileDialog::AcceptOpen);
  fileDialog->setViewMode (QFileDialog::Detail);
  fileDialog->setFileMode (QFileDialog::ExistingFiles);
  fileDialog->setDirectory (ced);

  connect (fileDialog, SIGNAL (filesSelected (const QStringList&)),
           this, SLOT (request_open_files (const QStringList&)));

  fileDialog->setWindowModality (Qt::NonModal);
  fileDialog->setAttribute (Qt::WA_DeleteOnClose);
  fileDialog->show ();
}

void
file_editor::handle_combo_enc_current_index (QString new_encoding)
{
  _file_encoding = new_encoding;
}

// Check whether this file is already open in the editor.
QWidget *
file_editor::find_tab_widget (const QString& file) const
{
  QWidget *retval = 0;

  for (editor_tab_map_const_iterator p = editor_tab_map.begin ();
       p != editor_tab_map.end (); p++)
    {
      QString tab_file = p->first;

      if (same_file (file.toStdString (), tab_file.toStdString ())
          || file == tab_file)     // needed as same_file ("","") is false.
        {
          retval = p->second.fet_ID;
          break;
        }
    }

  return retval;
}

bool
file_editor::call_custom_editor (const QString& file_name, int line)
{
  // Check if the user wants to use a custom file editor.
  QSettings *settings = resource_manager::get_settings ();

  if (settings->value ("useCustomFileEditor",false).toBool ())
    {
      if (line > -1)  // check for a specific line (debugging)
        return true;  // yes: do ont open a file in external editor

      QString editor = settings->value ("customFileEditor").toString ();
      editor.replace ("%f", file_name);
      editor.replace ("%l", QString::number (line));

      bool started_ok = QProcess::startDetached (editor);

      if (started_ok != true)
        {
          QMessageBox *msgBox
            = new QMessageBox (QMessageBox::Critical,
                               tr ("Octave Editor"),
                               tr ("Could not start custom file editor\n%1").
                               arg (editor),
                               QMessageBox::Ok, this);

           msgBox->setWindowModality (Qt::NonModal);
           msgBox->setAttribute (Qt::WA_DeleteOnClose);
           msgBox->show ();
        }

      if (line < 0 && ! file_name.isEmpty ())
        handle_mru_add_file (QFileInfo (file_name).canonicalFilePath (),
                             QString ());

      return true;
    }

  return false;
}

bool
file_editor::is_editor_console_tabbed ()
{
  main_window *w = static_cast<main_window *>(main_win ());
  QList<QDockWidget *> w_list = w->tabifiedDockWidgets (this);
  QDockWidget *console =
    static_cast<QDockWidget *> (w->get_dock_widget_list ().at (0));

  for (int i = 0; i < w_list.count (); i++)
    {
      if (w_list.at (i) == console)
        return true;
    }

  return false;
}

// The following slot is called after files have been selected in the
// open file dialog, possibly with a new selected encoding stored in
// _file_encoding
void
file_editor::request_open_files (const QStringList& open_file_names)
{
  for (int i = 0; i < open_file_names.count (); i++)
    request_open_file (open_file_names.at (i), _file_encoding);
}

// Open a file, if not already open, and mark the current execution location
// and/or a breakpoint with condition cond.
void
file_editor::request_open_file (const QString& openFileName,
                                const QString& encoding,
                                int line, bool debug_pointer,
                                bool breakpoint_marker, bool insert,
                                const QString& cond)
{
  if (call_custom_editor (openFileName, line))
    return;   // custom editor called

  if (openFileName.isEmpty ())
    {
      // This happens if edit is calles without an argument
      // Open eitor with empty edit area instead (as new file would do)
      request_new_file ("");
    }
  else
    {
      // Have all file editor tabs signal what their filenames are.
      editor_tab_map.clear ();
      emit fetab_file_name_query (0);

      // Check whether this file is already open in the editor.
      QWidget *tab = find_tab_widget (openFileName);

      if (tab)
        {
          _tab_widget->setCurrentWidget (tab);

          if (line > 0)
            {
              emit fetab_goto_line (tab, line);

              if (debug_pointer)
                emit fetab_insert_debugger_pointer (tab, line);

              if (breakpoint_marker)
                emit fetab_do_breakpoint_marker (insert, tab, line, cond);
            }

          if (! ((breakpoint_marker || debug_pointer) && is_editor_console_tabbed ()))
            {
              emit fetab_set_focus (tab);
              focus ();
            }
        }
      else
        {
          file_editor_tab *fileEditorTab = 0;
          // Reuse <unnamed> tab if it hasn't yet been modified.
          bool reusing = false;
          tab = find_tab_widget ("");
          if (tab)
            {
              fileEditorTab = static_cast<file_editor_tab *>(tab);
              if (fileEditorTab->qsci_edit_area ()->isModified ())
                fileEditorTab = 0;
              else
                reusing = true;
            }

          // If <unnamed> was absent or modified, create a new tab.
          if (!fileEditorTab)
            fileEditorTab = new file_editor_tab ();

          if (fileEditorTab)
            {
              fileEditorTab->set_encoding (encoding);
              QString result = fileEditorTab->load_file (openFileName);
              if (result == "")
                {
                  // Supply empty title then have the file_editor_tab update
                  // with full or short name.
                  if (!reusing)
                    add_file_editor_tab (fileEditorTab, "");
                  fileEditorTab->update_window_title (false);
                  // file already loaded, add file to mru list here
                  QFileInfo file_info = QFileInfo (openFileName);
                  handle_mru_add_file (file_info.canonicalFilePath (),
                                       encoding);

                  if (line > 0)
                    {
                      emit fetab_goto_line (fileEditorTab, line);

                      if (debug_pointer)
                        emit fetab_insert_debugger_pointer (fileEditorTab,
                                                            line);
                      if (breakpoint_marker)
                        emit fetab_do_breakpoint_marker (insert, fileEditorTab,
                                                         line, cond);
                    }
                }
              else
                {
                  delete fileEditorTab;

                  if (QFile::exists (openFileName))
                    {
                      // File not readable:
                      // create a NonModal message about error.
                      QMessageBox *msgBox
                        = new QMessageBox (QMessageBox::Critical,
                                           tr ("Octave Editor"),
                                           tr ("Could not open file\n%1\nfor read: %2.").
                                           arg (openFileName).arg (result),
                                           QMessageBox::Ok, this);

                      msgBox->setWindowModality (Qt::NonModal);
                      msgBox->setAttribute (Qt::WA_DeleteOnClose);
                      msgBox->show ();
                    }
                  else
                    {
                      // File does not exist, should it be created?
                      bool create_file = true;
                      QMessageBox *msgBox;
                      QSettings *settings = resource_manager::get_settings ();

                      if (! settings->value ("editor/create_new_file", false).toBool ())
                        {
                          msgBox = new QMessageBox (QMessageBox::Question,
                                                    tr ("Octave Editor"),
                                                    tr ("File\n%1\ndoes not exist. "
                                                        "Do you want to create it?").arg (openFileName),
                                                    QMessageBox::NoButton,0);
                          QPushButton *create_button =
                            msgBox->addButton (tr ("Create"), QMessageBox::YesRole);
                          msgBox->addButton (tr ("Cancel"), QMessageBox::RejectRole);
                          msgBox->setDefaultButton (create_button);
                          msgBox->exec ();

                          QAbstractButton *clicked_button = msgBox->clickedButton ();
                          if (clicked_button != create_button)
                            create_file = false;

                          delete msgBox;
                        }

                      if (create_file)
                        {
                          // create the file and call the editor again
                          QFile file (openFileName);
                          if (! file.open (QIODevice::WriteOnly))
                            {
                              // error opening the file
                              msgBox = new QMessageBox (QMessageBox::Critical,
                                                        tr ("Octave Editor"),
                                                        tr ("Could not open file\n%1\nfor write: %2.").
                                                        arg (openFileName).arg (file.errorString ()),
                                                        QMessageBox::Ok, this);

                              msgBox->setWindowModality (Qt::NonModal);
                              msgBox->setAttribute (Qt::WA_DeleteOnClose);
                              msgBox->show ();
                            }
                          else
                            {
                              file.close ();
                              request_open_file (openFileName);
                            }
                        }
                    }
                }
            }

          if (! ((breakpoint_marker || debug_pointer) && is_editor_console_tabbed ()))
            {
              // really show editor and the current editor tab
              focus ();
              emit file_loaded_signal ();
            }
        }
    }
}

// open a file from the mru list
void
file_editor::request_mru_open_file (QAction *action)
{
  if (action)
    {
      request_open_file (action->data ().toStringList ().at (0),
                         action->data ().toStringList ().at (1));
    }
}

void
file_editor::check_conflict_save (const QString& saveFileName,
                                  bool remove_on_success)
{
  // Have all file editor tabs signal what their filenames are.
  editor_tab_map.clear ();
  emit fetab_file_name_query (0);

  // Check whether this file is already open in the editor.
  QWidget *tab = find_tab_widget (saveFileName);

  if (tab)
    {
      // Note: to overwrite the contents of some other file editor tab
      // with the same name requires identifying which file editor tab
      // that is (not too difficult) then close that tab.  Of course,
      // that could trigger another dialog box if the file editor tab
      // with the same name has modifications in it.  This could become
      // somewhat confusing to the user.  For now, opt to do nothing.

      // Create a NonModal message about error.
      QMessageBox *msgBox
        = new QMessageBox (QMessageBox::Critical, tr ("Octave Editor"),
                           tr ("File not saved! A file with the selected name\n%1\n"
                               "is already open in the editor").
                           arg (saveFileName),
                           QMessageBox::Ok, 0);

      msgBox->setWindowModality (Qt::NonModal);
      msgBox->setAttribute (Qt::WA_DeleteOnClose);
      msgBox->show ();

      return;
    }

  QObject *saveFileObject = sender ();
  QWidget *saveFileWidget = 0;

  for (int i = 0; i < _tab_widget->count (); i++)
    {
      if (_tab_widget->widget (i) == saveFileObject)
        {
          saveFileWidget = _tab_widget->widget (i);
          break;
        }
    }
  if (! saveFileWidget)
    {
      // Create a NonModal message about error.
      QMessageBox *msgBox
        = new QMessageBox (QMessageBox::Critical, tr ("Octave Editor"),
                           tr ("The associated file editor tab has disappeared."),
                           QMessageBox::Ok, 0);

      msgBox->setWindowModality (Qt::NonModal);
      msgBox->setAttribute (Qt::WA_DeleteOnClose);
      msgBox->show ();

      return;
    }

  // Can save without conflict, have the file editor tab do so.
  emit fetab_save_file (saveFileWidget, saveFileName, remove_on_success);
}

void
file_editor::handle_edit_mfile_request (const QString& fname,
                                        const QString& ffile,
                                        const QString& curr_dir, int line)
{
  // Is it a regular function within the search path? (Call __which__)
  octave_value_list fct = F__which__ (ovl (fname.toStdString ()),0);
  octave_map map = fct(0).map_value ();

  QString type = QString::fromStdString (
                         map.contents ("type").data ()[0].string_value ());
  QString name = QString::fromStdString (
                         map.contents ("name").data ()[0].string_value ());

  QString message = QString ();
  QString filename = QString ();

  if (type == QString("built-in function"))
    { // built in function: can't edit
      message = tr ("%1 is a built-in function");
    }
  else if (type.isEmpty ())
    {
      // function not known to octave -> try directory of edited file
      // get directory
      QDir dir;
      if (ffile.isEmpty ())
        {
          if (curr_dir.isEmpty ())
            dir = QDir (ced);
          else
            dir = QDir (curr_dir);
        }
      else
        dir = QDir (QFileInfo (ffile).canonicalPath ());

      // function not known to octave -> try directory of edited file
      QFileInfo file = QFileInfo (dir, fname + ".m");

      if (file.exists ())
        {
          filename = file.canonicalFilePath (); // local file exists
        }
      else
        { // local file does not exist -> try private directory
          file = QFileInfo (ffile);
          file = QFileInfo (QDir (file.canonicalPath () + "/private"),
                            fname + ".m");

          if (file.exists ())
            {
              filename = file.canonicalFilePath ();  // private function exists
            }
          else
            {
              message = tr ("Can not find function %1");  // no file found
            }
        }
    }

  if (! message.isEmpty ())
    {
      QMessageBox *msgBox
          = new QMessageBox (QMessageBox::Critical,
                             tr ("Octave Editor"),
                             message.arg (name),
                             QMessageBox::Ok, this);

      msgBox->setWindowModality (Qt::NonModal);
      msgBox->setAttribute (Qt::WA_DeleteOnClose);
      msgBox->show ();
      return;
    }

  if ( filename.isEmpty ())
    filename = QString::fromStdString (
                           map.contents ("file").data ()[0].string_value ());

  if (! filename.endsWith (".m"))
    filename.append (".m");

  request_open_file (filename, QString (), line);  // default encoding
}

void
file_editor::handle_insert_debugger_pointer_request (const QString& file,
                                                     int line)
{
  request_open_file (file, QString (), line, true); // default encoding
}

void
file_editor::handle_delete_debugger_pointer_request (const QString& file,
                                                     int line)
{
  if (! file.isEmpty ())
    {
      // Have all file editor tabs signal what their filenames are.
      editor_tab_map.clear ();
      emit fetab_file_name_query (0);

      // Check whether this file is already open in the editor.
      QWidget *tab = find_tab_widget (file);

      if (tab)
        {
          _tab_widget->setCurrentWidget (tab);

          if (line > 0)
            emit fetab_delete_debugger_pointer (tab, line);

          emit fetab_set_focus (tab);
        }
    }
}

void
file_editor::handle_update_breakpoint_marker_request (bool insert,
                                                      const QString& file,
                                                      int line,
                                                      const QString& cond)
{
  request_open_file (file, QString (), line, false, true, insert, cond);
}

void
file_editor::handle_edit_file_request (const QString& file)
{
  request_open_file (file);
}

void
file_editor::do_undo ()
{
  if (editor_tab_has_focus ())
    emit fetab_scintilla_command (_tab_widget->currentWidget (),
                                  QsciScintillaBase::SCI_UNDO);
}

void
file_editor::request_redo (bool)
{
  emit fetab_scintilla_command (_tab_widget->currentWidget (),
                                QsciScintillaBase::SCI_REDO);
}

void
file_editor::copyClipboard ()
{
  if (editor_tab_has_focus ())
    emit fetab_scintilla_command (_tab_widget->currentWidget (),
                                  QsciScintillaBase::SCI_COPY);
}

void
file_editor::request_cut (bool)
{
  emit fetab_scintilla_command (_tab_widget->currentWidget (),
                                QsciScintillaBase::SCI_CUT);
}

void
file_editor::pasteClipboard ()
{
  if (editor_tab_has_focus ())
    emit fetab_scintilla_command (_tab_widget->currentWidget (),
                                  QsciScintillaBase::SCI_PASTE);
}

void
file_editor::selectAll ()
{
  if (editor_tab_has_focus ())
    emit fetab_scintilla_command (_tab_widget->currentWidget (),
                                  QsciScintillaBase::SCI_SELECTALL);
}

void
file_editor::request_context_help (bool)
{
  emit fetab_context_help (_tab_widget->currentWidget (), false);
}
void
file_editor::request_context_doc (bool)
{
  emit fetab_context_help (_tab_widget->currentWidget (), true);
}

void
file_editor::request_context_edit (bool)
{
  emit fetab_context_edit (_tab_widget->currentWidget ());
}

void
file_editor::request_save_file (bool)
{
  emit fetab_save_file (_tab_widget->currentWidget ());
}

void
file_editor::request_save_file_as (bool)
{
  emit fetab_save_file_as (_tab_widget->currentWidget ());
}

void
file_editor::request_print_file (bool)
{
  emit fetab_print_file (_tab_widget->currentWidget ());
}

void
file_editor::request_run_file (bool)
{
  emit fetab_run_file (_tab_widget->currentWidget ());
}

void
file_editor::request_context_run (bool)
{
  emit fetab_context_run (_tab_widget->currentWidget ());
}

void
file_editor::request_toggle_bookmark (bool)
{
  emit fetab_toggle_bookmark (_tab_widget->currentWidget ());
}

void
file_editor::request_next_bookmark (bool)
{
  emit fetab_next_bookmark (_tab_widget->currentWidget ());
}

void
file_editor::request_previous_bookmark (bool)
{
  emit fetab_previous_bookmark (_tab_widget->currentWidget ());
}

void
file_editor::request_remove_bookmark (bool)
{
  emit fetab_remove_bookmark (_tab_widget->currentWidget ());
}

// FIXME: What should this do with conditional breakpoints?
void
file_editor::request_toggle_breakpoint (bool)
{
  emit fetab_toggle_breakpoint (_tab_widget->currentWidget ());
}

void
file_editor::request_next_breakpoint (bool)
{
  emit fetab_next_breakpoint (_tab_widget->currentWidget ());
}

void
file_editor::request_previous_breakpoint (bool)
{
  emit fetab_previous_breakpoint (_tab_widget->currentWidget ());
}

void
file_editor::request_remove_breakpoint (bool)
{
  emit fetab_remove_all_breakpoints (_tab_widget->currentWidget ());
}

// slots for Edit->Commands actions
void
file_editor::request_delete_start_word (bool)
{
  emit fetab_scintilla_command (_tab_widget->currentWidget (),
                                QsciScintillaBase::SCI_DELWORDLEFT);
}
void
file_editor::request_delete_end_word (bool)
{
  emit fetab_scintilla_command (_tab_widget->currentWidget (),
                                QsciScintillaBase::SCI_DELWORDRIGHT);
}
void
file_editor::request_delete_start_line (bool)
{
  emit fetab_scintilla_command (_tab_widget->currentWidget (),
                                QsciScintillaBase::SCI_DELLINELEFT);
}
void
file_editor::request_delete_end_line (bool)
{
  emit fetab_scintilla_command (_tab_widget->currentWidget (),
                                QsciScintillaBase::SCI_DELLINERIGHT);
}
void
file_editor::request_delete_line (bool)
{
  emit fetab_scintilla_command (_tab_widget->currentWidget (),
                                QsciScintillaBase::SCI_LINEDELETE);
}
void
file_editor::request_copy_line (bool)
{
  emit fetab_scintilla_command (_tab_widget->currentWidget (),
                                QsciScintillaBase::SCI_LINECOPY);
}
void
file_editor::request_cut_line (bool)
{
  emit fetab_scintilla_command (_tab_widget->currentWidget (),
                                QsciScintillaBase::SCI_LINECUT);
}
void
file_editor::request_duplicate_selection (bool)
{
  emit fetab_scintilla_command (_tab_widget->currentWidget (),
                                QsciScintillaBase::SCI_SELECTIONDUPLICATE);
}
void
file_editor::request_transpose_line (bool)
{
  emit fetab_scintilla_command (_tab_widget->currentWidget (),
                                QsciScintillaBase::SCI_LINETRANSPOSE);
}
void
file_editor::request_comment_selected_text (bool)
{
  emit fetab_comment_selected_text (_tab_widget->currentWidget ());
}
void
file_editor::request_uncomment_selected_text (bool)
{
  emit fetab_uncomment_selected_text (_tab_widget->currentWidget ());
}

// slots for Edit->Format actions
void
file_editor::request_upper_case (bool)
{
  emit fetab_scintilla_command (_tab_widget->currentWidget (),
                                QsciScintillaBase::SCI_UPPERCASE);
}
void
file_editor::request_lower_case (bool)
{
  emit fetab_scintilla_command (_tab_widget->currentWidget (),
                                QsciScintillaBase::SCI_LOWERCASE);
}
void
file_editor::request_indent_selected_text (bool)
{
  emit fetab_indent_selected_text (_tab_widget->currentWidget ());
}

void
file_editor::request_unindent_selected_text (bool)
{
  emit fetab_unindent_selected_text (_tab_widget->currentWidget ());
}

void
file_editor::request_conv_eol_windows (bool)
{
  emit fetab_convert_eol (_tab_widget->currentWidget (),
                          QsciScintilla::EolWindows);
}
void
file_editor::request_conv_eol_unix (bool)
{
  emit fetab_convert_eol (_tab_widget->currentWidget (),
                          QsciScintilla::EolUnix);
}
void
file_editor::request_conv_eol_mac (bool)
{
  emit fetab_convert_eol (_tab_widget->currentWidget (),
                          QsciScintilla::EolMac);
}

void
file_editor::request_find (bool)
{
  emit fetab_find (_tab_widget->currentWidget ());
}

void
file_editor::request_goto_line (bool)
{
  emit fetab_goto_line (_tab_widget->currentWidget ());
}

void
file_editor::request_move_match_brace (bool)
{
  emit fetab_move_match_brace (_tab_widget->currentWidget (), false);
}

void
file_editor::request_sel_match_brace (bool)
{
  emit fetab_move_match_brace (_tab_widget->currentWidget (), true);
}

void
file_editor::request_completion (bool)
{
  emit fetab_completion (_tab_widget->currentWidget ());
}

void
file_editor::handle_mru_add_file (const QString& file_name,
                                  const QString& encoding)
{
  int index;
  while ((index = _mru_files.indexOf (file_name)) >= 0)
    {
      _mru_files.removeAt (index);
      _mru_files_encodings.removeAt (index);
    }

  _mru_files.prepend (file_name);
  _mru_files_encodings.prepend (encoding);

  mru_menu_update ();
}

void
file_editor::mru_menu_update (void)
{
  int num_files = qMin (_mru_files.size (), int (MaxMRUFiles));

  // configure and show active actions of mru-menu
  for (int i = 0; i < num_files; ++i)
    {
      QString text = tr ("&%1 %2").
                     arg ((i+1) % int (MaxMRUFiles)).arg (_mru_files.at (i));
      _mru_file_actions[i]->setText (text);

      QStringList action_data;
      action_data << _mru_files.at (i) << _mru_files_encodings.at (i);
      _mru_file_actions[i]->setData (action_data);

      _mru_file_actions[i]->setVisible (true);
    }

  // hide unused mru-menu entries
  for (int j = num_files; j < MaxMRUFiles; ++j)
    _mru_file_actions[j]->setVisible (false);

  // delete entries in string-list beyond MaxMRUFiles
  while (_mru_files.size () > MaxMRUFiles)
    {
      _mru_files.removeLast ();
      _mru_files_encodings.removeLast ();
    }

  // save actual mru-list in settings
  QSettings *settings = resource_manager::get_settings ();

  settings->setValue ("editor/mru_file_list", _mru_files);
  settings->setValue ("editor/mru_file_encodings", _mru_files_encodings);
  settings->sync ();
}

void
file_editor::handle_file_name_changed (const QString& fname,
                                       const QString& tip)
{
  QObject *fileEditorTab = sender ();
  if (fileEditorTab)
    {
      for (int i = 0; i < _tab_widget->count (); i++)
        {
          if (_tab_widget->widget (i) == fileEditorTab)
            {
              _tab_widget->setTabText (i, fname);
              _tab_widget->setTabToolTip (i, tip);
            }
        }
    }
}

void
file_editor::request_close_file (bool)
{
  file_editor_tab *editor_tab =
      static_cast<file_editor_tab *> (_tab_widget->currentWidget ());
  editor_tab->conditional_close ();
}

void
file_editor::request_close_all_files (bool)
{
  file_editor_tab *editor_tab;

  // loop over all tabs starting from last one otherwise deletion changes index
  for (int index = _tab_widget->count ()-1; index >= 0; index--)
    {
      editor_tab = static_cast<file_editor_tab *> (_tab_widget->widget (index));
      editor_tab->conditional_close ();
    }
}

void
file_editor::request_close_other_files (bool)
{
  file_editor_tab *editor_tab;
  QWidget *tabID = _tab_widget->currentWidget ();

  // loop over all tabs starting from last one otherwise deletion changes index
  for (int index = _tab_widget->count ()-1; index >= 0; index--)
    {
      if (tabID != _tab_widget->widget (index))
        {
          editor_tab =
              static_cast<file_editor_tab *> (_tab_widget->widget (index));
          editor_tab->conditional_close ();
        }
    }
}

void
file_editor::handle_tab_close_request (int index)
{
  file_editor_tab *editor_tab =
       static_cast<file_editor_tab *> (_tab_widget->widget (index));
  editor_tab->conditional_close ();
}

void
file_editor::handle_tab_remove_request (void)
{
  QObject *fileEditorTab = sender ();
  if (fileEditorTab)
    {
      for (int i = 0; i < _tab_widget->count (); i++)
        {
          if (_tab_widget->widget (i) == fileEditorTab)
            {
              _tab_widget->removeTab (i);
              // Deleting sender is dodgy, but works because the signal
              // is the last item in the sender's routines.
              delete fileEditorTab;
              break;
            }
        }
    }
  check_actions ();

  focus ();     // focus stays in editor when tab is closed
}

void
file_editor::handle_add_filename_to_list (const QString& fileName,
                                          const QString& encoding, QWidget *ID)
{
  // Should we allow multiple tabs for a single file?
  editor_tab_map[fileName].fet_ID = ID;
  editor_tab_map[fileName].encoding = encoding;
}

// context menu of edit area
void
file_editor::active_tab_changed (int index)
{
  emit fetab_change_request (_tab_widget->widget (index));
}

void file_editor::create_context_menu (QMenu *menu)
{
  // remove all standard actions from scintilla
  QList<QAction *> all_actions = menu->actions ();
  QAction* a;

  foreach (a, all_actions)
    menu->removeAction (a);

  // add editor's actions with icons and customized shortcuts
  menu->addAction (_undo_action);
  menu->addAction (_redo_action);
  menu->addSeparator ();
  menu->addAction (_cut_action);
  menu->addAction (_copy_action);
  menu->addAction (_paste_action);
  menu->addSeparator ();
  menu->addAction (_selectall_action);
  menu->addSeparator ();
  menu->addAction (_run_selection_action);
}

void
file_editor::toggle_preference (const QString& preference, bool def)
{
  QSettings *settings = resource_manager::get_settings ();
  bool old = settings->value (preference,def).toBool ();
  settings->setValue (preference,! old);
  notice_settings (settings);
}

void
file_editor::show_line_numbers (bool)
{
  toggle_preference ("editor/showLineNumbers",true);
}
void
file_editor::show_white_space (bool)
{
  toggle_preference ("editor/show_white_space",false);
}
void
file_editor::show_eol_chars (bool)
{
  toggle_preference ("editor/show_eol_chars",false);
}
void
file_editor::show_indent_guides (bool)
{
  toggle_preference ("editor/show_indent_guides",false);
}
void
file_editor::show_long_line (bool)
{
  toggle_preference ("editor/long_line_marker",true);
}
void
file_editor::show_toolbar (bool)
{
  toggle_preference ("editor/show_toolbar",true);
}
void
file_editor::show_statusbar (bool)
{
  toggle_preference ("editor/show_edit_status_bar",true);
}
void
file_editor::show_hscrollbar (bool)
{
  toggle_preference ("editor/show_hscroll_bar",true);
}

void
file_editor::zoom_in (bool)
{
  emit fetab_zoom_in (_tab_widget->currentWidget ());
}

void
file_editor::zoom_out (bool)
{
  emit fetab_zoom_out (_tab_widget->currentWidget ());
}

void
file_editor::zoom_normal (bool)
{
  emit fetab_zoom_normal (_tab_widget->currentWidget ());
}

void
file_editor::edit_status_update (bool undo, bool redo)
{
  if (_undo_action)
    _undo_action->setEnabled (undo);
  _redo_action->setEnabled (redo);
}

void
file_editor::handle_editor_state_changed (bool copy_available,
                                          bool is_octave_file)
{
  // In case there is some scenario where traffic could be coming from
  // all the file editor tabs, just process info from the current active tab.
  if (sender () == _tab_widget->currentWidget ())
    {
      if (_copy_action)
        _copy_action->setEnabled (copy_available);
      _cut_action->setEnabled (copy_available);
      _run_selection_action->setEnabled (copy_available);
      _run_action->setEnabled (is_octave_file);

      setFocusProxy (_tab_widget->currentWidget ());
    }
}

void
file_editor::notice_settings (const QSettings *settings)
{
  int icon_size_settings = settings->value ("toolbar_icon_size",0).toInt ();
  QStyle *st = style ();
  int icon_size = st->pixelMetric (QStyle::PM_ToolBarIconSize);

  if (icon_size_settings == 1)
    icon_size = st->pixelMetric (QStyle::PM_LargeIconSize);
  else if (icon_size_settings == -1)
    icon_size = st->pixelMetric (QStyle::PM_SmallIconSize);

  _tool_bar->setIconSize (QSize (icon_size,icon_size));

  int tab_width_min = settings->value ("editor/notebook_tab_width_min", 160)
                                      .toInt ();
  int tab_width_max = settings->value ("editor/notebook_tab_width_max", 300)
                                      .toInt ();

  if (settings->value ("editor/longWindowTitle", false).toBool ())
    {
      QString style_sheet = QString ("QTabBar::tab "
                                     "{min-width: %1px; max-width: %2px;}")
                             .arg (tab_width_min).arg (tab_width_max);
      _tab_widget->setElideMode (Qt::ElideLeft);
      _tab_widget->setStyleSheet (style_sheet);
    }
  else
    _tab_widget->setElideMode (Qt::ElideNone);

  _tab_widget->setUsesScrollButtons (true);

  bool show_it;
  show_it = settings->value ("editor/showLineNumbers",true).toBool ();
  _show_linenum_action->setChecked (show_it);
  show_it = settings->value ("editor/show_white_space",false).toBool ();
  _show_whitespace_action->setChecked (show_it);
  show_it = settings->value ("editor/show_eol_chars",false).toBool ();
  _show_eol_action->setChecked (show_it);
  show_it = settings->value ("editor/show_indent_guides",false).toBool ();
  _show_indguide_action->setChecked (show_it);
  show_it = settings->value ("editor/long_line_marker",true).toBool ();
  _show_longline_action->setChecked (show_it);

  show_it = settings->value ("editor/show_toolbar",true).toBool ();
  _show_toolbar_action->setChecked (show_it);
  _tool_bar->setVisible (show_it);
  show_it = settings->value ("editor/show_edit_status_bar",true).toBool ();
  _show_statusbar_action->setChecked (show_it);
  show_it = settings->value ("editor/show_hscroll_bar",true).toBool ();
  _show_hscrollbar_action->setChecked (show_it);

  set_shortcuts ();

  // Relay signal to file editor tabs.
  emit fetab_settings_changed (settings);
}

void
file_editor::request_preferences (bool)
{
  emit request_settings_dialog ("editor");
}

void
file_editor::request_styles_preferences (bool)
{
  emit request_settings_dialog ("editor_styles");
}

// insert global actions, that should also be displayed in the editor window,
// into the editor's menu and/or toolbar
void
file_editor::insert_global_actions (QList<QAction*> shared_actions)
{
  // actions/menus that have to be added to the toolbar or the menu
  QAction *open_action = shared_actions.at (OPEN_ACTION);
  QAction *new_action = shared_actions.at (NEW_SCRIPT_ACTION);
  QAction *new_fcn_action = shared_actions.at (NEW_FUNCTION_ACTION);
  _fileMenu->insertAction (_mru_file_menu->menuAction (), open_action);
  _fileMenu->insertAction (open_action, new_fcn_action);
  _fileMenu->insertAction (new_fcn_action, new_action);
  _tool_bar->insertAction (_popdown_mru_action, open_action);
  _tool_bar->insertAction (open_action, new_action);

  // actions that are additionally enabled/disabled later by the editor
  // undo
  _undo_action = shared_actions.at (UNDO_ACTION);
  _tool_bar->insertAction (_redo_action,_undo_action);
  _edit_menu->insertAction (_redo_action,_undo_action);
  _undo_action->setEnabled (false);
  // copy
  _copy_action = shared_actions.at (COPY_ACTION);
  _tool_bar->insertAction (_cut_action,_copy_action);
  _edit_menu->insertAction (_cut_action,_copy_action);
  _copy_action->setEnabled (false);
  // select all
  _selectall_action = shared_actions.at (SELECTALL_ACTION);
  _edit_menu->insertAction (_find_action,_selectall_action);
  _edit_menu->insertSeparator (_find_action);
  // paste
  _paste_action = shared_actions.at (PASTE_ACTION);
  _tool_bar->insertAction (_find_action,_paste_action);
  _edit_menu->insertAction (_selectall_action,_paste_action);
  _edit_menu->insertSeparator (_selectall_action);
  _paste_action->setEnabled (false);
  // find files
  _find_files_action = shared_actions.at (FIND_FILES_ACTION);
  _edit_menu->insertAction (_find_action, _find_files_action);
}

QAction*
file_editor::add_action (QMenu *menu, const QIcon &icon, const QString &text,
                         const char *member)
{
  QAction *a;

  if (menu)
    a = menu->addAction (icon, text, this, member);
  else
    {
      a = new QAction (this);
      connect (a, SIGNAL (triggered ()), this, member);
    }

  addAction (a);  // important for shortcut context
  a->setShortcutContext (Qt::WidgetWithChildrenShortcut);

  return a;
}

// function enabling/disabling the menu accelerators depending on the
// focus of the editor
void
file_editor::enable_menu_shortcuts (bool enable)
{
  QHash<QMenu*, QStringList>::const_iterator i = _hash_menu_text.constBegin();

  while (i != _hash_menu_text.constEnd())
    {
      i.key ()->setTitle (i.value ().at (! enable));
      ++i;
    }

  // when editor loses focus, enable the actions, which are always active
  // in the main window due to missing info on selected text and undo actions
  if (! enable && _copy_action && _undo_action)
    {
      _copy_action->setEnabled (true);
      _undo_action->setEnabled (true);
    }
}

QMenu*
file_editor::m_add_menu (QMenuBar *p, QString name)
{
  QMenu *menu = p->addMenu (name);

  QString base_name = name;  // get a copy
  // replace intended '&' ("&&") by a temp. string
  base_name.replace ("&&","___octave_amp_replacement___");
  // remove single '&' (shortcut)
  base_name.remove ("&");
  // restore intended '&'
  base_name.replace ("___octave_amp_replacement___","&&");

  // remember names with and without shortcut
  _hash_menu_text[menu] = QStringList () << name << base_name;

  return menu;
}

void
file_editor::construct (void)
{
  QWidget *editor_widget = new QWidget (this);

  // FIXME: what was the intended purpose of this unused variable?
  // QStyle *editor_style = QApplication::style ();
  _menu_bar = new QMenuBar (editor_widget);
#if defined (Q_OS_MAC)
  _menu_bar->setNativeMenuBar (false);
#endif
  _tool_bar = new QToolBar (editor_widget);
  _tool_bar->setMovable (true);
  _tab_widget = new tab_widget (editor_widget);
  _tab_widget->setTabsClosable (true);
#if defined (HAVE_QTABWIDGET_SETMOVABLE)
  _tab_widget->setMovable (true);
#endif

  // the mru-list and an empty array of actions
  QSettings *settings = resource_manager::get_settings ();
  _mru_files = settings->value ("editor/mru_file_list").toStringList ();
  _mru_files_encodings = settings->value ("editor/mru_file_encodings")
                                   .toStringList ();

  if (_mru_files_encodings.count () != _mru_files.count ())
    { // encodings don't have the same count -> do not use them!
      _mru_files_encodings = QStringList ();
      for (int i = 0; i < _mru_files.count (); i++)
        _mru_files_encodings << QString ();
    }

  for (int i = 0; i < MaxMRUFiles; ++i)
    {
      _mru_file_actions[i] = new QAction (this);
      _mru_file_actions[i]->setVisible (false);
    }

  // menu bar

  // file menu

  _fileMenu = m_add_menu (_menu_bar, tr ("&File"));

  // new and open menus are inserted later by the main window
  _mru_file_menu = new QMenu (tr ("&Recent Editor Files"), _fileMenu);
  for (int i = 0; i < MaxMRUFiles; ++i)
    _mru_file_menu->addAction (_mru_file_actions[i]);
  _fileMenu->addMenu (_mru_file_menu);

  _fileMenu->addSeparator ();

  _edit_function_action = add_action (_fileMenu, QIcon (),
          tr ("&Edit Function"), SLOT (request_context_edit (bool)));

  _fileMenu->addSeparator ();

  _save_action = add_action (_fileMenu, resource_manager::icon ("document-save"),
          tr ("&Save File"), SLOT (request_save_file (bool)));
  _save_as_action = add_action (_fileMenu, resource_manager::icon ("document-save-as"),
          tr ("Save File &As..."), SLOT (request_save_file_as (bool)));

  _fileMenu->addSeparator ();

  _close_action = add_action (_fileMenu, resource_manager::icon ("window-close",false),
          tr ("&Close"), SLOT (request_close_file (bool)));
  _close_all_action = add_action (_fileMenu, resource_manager::icon ("window-close",false),
          tr ("Close All"), SLOT (request_close_all_files (bool)));
  _close_others_action = add_action (_fileMenu, resource_manager::icon ("window-close",false),
          tr ("Close Other Files"), SLOT (request_close_other_files (bool)));

  _fileMenu->addSeparator ();

  _print_action = add_action (_fileMenu, resource_manager::icon ("document-print"),
          tr ("Print..."), SLOT (request_print_file (bool)));

  // edit menu (undo, copy, paste and select all later via main window)

  _edit_menu = m_add_menu (_menu_bar, tr ("&Edit"));

  _redo_action = add_action (_edit_menu, resource_manager::icon ("edit-redo"),
          tr ("&Redo"), SLOT (request_redo (bool)));
  _redo_action->setEnabled (false);

  _edit_menu->addSeparator ();

  _cut_action = add_action (_edit_menu, resource_manager::icon ("edit-cut"),
          tr ("Cu&t"), SLOT (request_cut (bool)));
  _cut_action->setEnabled (false);

  _find_action = add_action (_edit_menu, resource_manager::icon ("edit-find-replace"),
          tr ("&Find and Replace..."), SLOT (request_find (bool)));

  _edit_menu->addSeparator ();

  _edit_cmd_menu = _edit_menu->addMenu (tr ("&Commands"));

  _delete_line_action = add_action (_edit_cmd_menu, QIcon (),
          tr ("Delete Line"), SLOT (request_delete_line (bool)));
  _copy_line_action = add_action (_edit_cmd_menu, QIcon (),
          tr ("Copy Line"), SLOT (request_copy_line (bool)));
  _cut_line_action = add_action (_edit_cmd_menu, QIcon (),
          tr ("Cut Line"), SLOT (request_cut_line (bool)));

  _edit_cmd_menu->addSeparator ();

  _delete_start_word_action = add_action (_edit_cmd_menu, QIcon (),
          tr ("Delete to Start of Word"), SLOT (request_delete_start_word (bool)));
  _delete_end_word_action = add_action (_edit_cmd_menu, QIcon (),
          tr ("Delete to End of Word"), SLOT (request_delete_end_word (bool)));
  _delete_start_line_action = add_action (_edit_cmd_menu, QIcon (),
          tr ("Delete to Start of Line"), SLOT (request_delete_start_line (bool)));
  _delete_end_line_action = add_action (_edit_cmd_menu, QIcon (),
          tr ("Delete to End of Line"), SLOT (request_delete_end_line (bool)));

  _edit_cmd_menu->addSeparator ();

  _duplicate_selection_action = add_action (_edit_cmd_menu, QIcon (),
          tr ("Duplicate Selection/Line"), SLOT (request_duplicate_selection (bool)));
  _transpose_line_action = add_action (_edit_cmd_menu, QIcon (),
          tr ("Transpose Line"), SLOT (request_transpose_line (bool)));

  _edit_cmd_menu->addSeparator ();

  _completion_action = add_action (_edit_cmd_menu, QIcon (),
          tr ("&Show Completion List"), SLOT (request_completion (bool)));

  _edit_fmt_menu = _edit_menu->addMenu (tr ("&Format"));

  _upper_case_action = add_action (_edit_fmt_menu, QIcon (),
          tr ("&Uppercase Selection"), SLOT (request_upper_case (bool)));
  _lower_case_action = add_action (_edit_fmt_menu, QIcon (),
          tr ("&Lowercase Selection"), SLOT (request_lower_case (bool)));

  _edit_fmt_menu->addSeparator ();

  _comment_selection_action = add_action (_edit_fmt_menu, QIcon (),
          tr ("&Comment"), SLOT (request_comment_selected_text (bool)));
  _uncomment_selection_action = add_action (_edit_fmt_menu, QIcon (),
          tr ("&Uncomment"), SLOT (request_uncomment_selected_text (bool)));

  _edit_fmt_menu->addSeparator ();

  _indent_selection_action = add_action (_edit_fmt_menu, QIcon (),
          tr ("&Indent"), SLOT (request_indent_selected_text (bool)));
  _unindent_selection_action = add_action (_edit_fmt_menu, QIcon (),
          tr ("&Unindent"), SLOT (request_unindent_selected_text (bool)));

  _edit_fmt_menu->addSeparator ();

  _conv_eol_windows_action = add_action (_edit_fmt_menu, QIcon (),
          tr ("Convert Line Endings to &Windows (CRLF)"),
          SLOT (request_conv_eol_windows (bool)));
  _conv_eol_unix_action = add_action (_edit_fmt_menu, QIcon (),
          tr ("Convert Line Endings to &Unix (LF)"),
          SLOT (request_conv_eol_unix (bool)));
  _conv_eol_mac_action = add_action (_edit_fmt_menu, QIcon (),
          tr ("Convert Line Endings to &Mac (CR)"),
          SLOT (request_conv_eol_mac (bool)));

  _edit_nav_menu = _edit_menu->addMenu (tr ("Navi&gation"));

  _goto_line_action = add_action (_edit_nav_menu, QIcon (),
          tr ("Go &to Line..."), SLOT (request_goto_line (bool)));

  _edit_cmd_menu->addSeparator ();

  _move_to_matching_brace = add_action (_edit_nav_menu, QIcon (),
          tr ("Move to Matching Brace"), SLOT (request_move_match_brace (bool)));
  _sel_to_matching_brace = add_action (_edit_nav_menu, QIcon (),
          tr ("Select to Matching Brace"), SLOT (request_sel_match_brace (bool)));

  _edit_nav_menu->addSeparator ();

  _previous_bookmark_action = add_action (_edit_nav_menu, QIcon (),
          tr ("Pre&vious Bookmark"), SLOT (request_previous_bookmark (bool)));
  _next_bookmark_action = add_action (_edit_nav_menu, QIcon (),
          tr ("&Next Bookmark"), SLOT (request_next_bookmark (bool)));
  _toggle_bookmark_action = add_action (_edit_nav_menu, QIcon (),
          tr ("Toggle &Bookmark"), SLOT (request_toggle_bookmark (bool)));
  _remove_bookmark_action = add_action (_edit_nav_menu, QIcon (),
          tr ("&Remove All Bookmarks"), SLOT (request_remove_bookmark (bool)));

  _edit_menu->addSeparator ();

  _preferences_action = add_action (_edit_menu, resource_manager::icon ("preferences-system"),
          tr ("&Preferences..."), SLOT (request_preferences (bool)));
  _styles_preferences_action = add_action (_edit_menu,  resource_manager::icon ("preferences-system"),
          tr ("&Styles Preferences..."), SLOT (request_styles_preferences (bool)));

  // view menu

  QMenu *view_menu = m_add_menu (_menu_bar, tr ("&View"));

  _view_editor_menu = view_menu->addMenu (tr ("&Editor"));

  _show_linenum_action = add_action (_view_editor_menu, QIcon (),
          tr ("Show &Line Numbers"), SLOT (show_line_numbers (bool)));
  _show_linenum_action->setCheckable (true);

  _show_whitespace_action = add_action (_view_editor_menu, QIcon (),
          tr ("Show &Whitespace Characters"), SLOT (show_white_space (bool)));
  _show_whitespace_action->setCheckable (true);

  _show_eol_action = add_action (_view_editor_menu, QIcon (),
          tr ("Show Line &Endings"), SLOT (show_eol_chars (bool)));
  _show_eol_action->setCheckable (true);

  _show_indguide_action = add_action (_view_editor_menu, QIcon (),
          tr ("Show &Indentation Guides"), SLOT (show_indent_guides (bool)));
  _show_indguide_action->setCheckable (true);

  _show_longline_action = add_action (_view_editor_menu, QIcon (),
          tr ("Show Long Line &Marker"), SLOT (show_long_line (bool)));
  _show_longline_action->setCheckable (true);

  _view_editor_menu->addSeparator ();

  _show_toolbar_action = add_action (_view_editor_menu, QIcon (),
          tr ("Show &Toolbar"), SLOT (show_toolbar (bool)));
  _show_toolbar_action->setCheckable (true);

  _show_statusbar_action = add_action (_view_editor_menu, QIcon (),
          tr ("Show &Statusbar"), SLOT (show_statusbar (bool)));
  _show_statusbar_action->setCheckable (true);

  _show_hscrollbar_action = add_action (_view_editor_menu, QIcon (),
          tr ("Show &Horizontal Scrollbar"), SLOT (show_hscrollbar (bool)));
  _show_hscrollbar_action->setCheckable (true);

  view_menu->addSeparator ();

  _zoom_in_action = add_action (view_menu, resource_manager::icon ("zoom-in"),
          tr ("Zoom &In"), SLOT (zoom_in (bool)));
  _zoom_out_action = add_action (view_menu, resource_manager::icon ("zoom-out"),
          tr ("Zoom &Out"), SLOT (zoom_out (bool)));
  _zoom_normal_action = add_action (view_menu,  QIcon (),
          tr ("&Normal Size"), SLOT (zoom_normal (bool)));

  _menu_bar->addMenu (view_menu);

  // debug menu

  _debug_menu = m_add_menu (_menu_bar, tr ("&Debug"));

  _toggle_breakpoint_action = add_action (_debug_menu,
          resource_manager::icon ("bp-toggle"), tr ("Toggle &Breakpoint"),
          SLOT (request_toggle_breakpoint (bool)));
  _next_breakpoint_action = add_action (_debug_menu,
          resource_manager::icon ("bp-next"), tr ("&Next Breakpoint"),
          SLOT (request_next_breakpoint (bool)));
  _previous_breakpoint_action = add_action (_debug_menu,
          resource_manager::icon ("bp-prev"), tr ("Pre&vious Breakpoint"),
          SLOT (request_previous_breakpoint (bool)));
  _remove_all_breakpoints_action = add_action (_debug_menu,
          resource_manager::icon ("bp-rm-all"), tr ("&Remove All Breakpoints"),
          SLOT (request_remove_breakpoint (bool)));

  _debug_menu->addSeparator ();

  // The other debug actions will be added by the main window.

  // run menu

  QMenu *_run_menu = m_add_menu (_menu_bar, tr ("&Run"));

  _run_action = add_action (_run_menu,  resource_manager::icon ("system-run"),
          tr ("Save File and Run"), SLOT (request_run_file (bool)));
  _run_selection_action = add_action (_run_menu, QIcon (),
          tr ("Run &Selection"), SLOT (request_context_run (bool)));
  _run_selection_action->setEnabled (false);

  // help menu

  QMenu *_help_menu = m_add_menu (_menu_bar, tr ("&Help"));

  _context_help_action = add_action (_help_menu, QIcon (),
          tr ("&Help on Keyword"), SLOT (request_context_help (bool)));
  _context_doc_action = add_action (_help_menu, QIcon (),
          tr ("&Documentation on Keyword"), SLOT (request_context_doc (bool)));

  // tab navigation (no menu, only actions)

  _switch_left_tab_action = add_action (0, QIcon (), "",
                                        SLOT (switch_left_tab ()));
  _switch_right_tab_action = add_action (0, QIcon (), "",
                                         SLOT (switch_right_tab ()));
  _move_tab_left_action = add_action (0, QIcon (), "",
                                      SLOT (move_tab_left ()));
  _move_tab_right_action = add_action (0, QIcon (), "",
                                       SLOT (move_tab_right ()));

  // toolbar

  // popdown menu with mru files
  QToolButton *popdown_button = new QToolButton ();
  popdown_button->setToolTip (tr ("Recent Files"));
  popdown_button->setMenu (_mru_file_menu);
  popdown_button->setPopupMode (QToolButton::InstantPopup);
  popdown_button->setToolButtonStyle (Qt::ToolButtonTextOnly);

  // new and open actions are inserted later from main window
  _popdown_mru_action = _tool_bar->addWidget (popdown_button);
  _tool_bar->addAction (_save_action);
  _tool_bar->addAction (_save_as_action);
  _tool_bar->addAction (_print_action);
  _tool_bar->addSeparator ();
  // _undo_action: later via main window
  _tool_bar->addAction (_redo_action);
  // _copy_action: later via the main window
  _tool_bar->addAction (_cut_action);
  // _paste_action: later via the main window
  _tool_bar->addAction (_find_action);
  _tool_bar->addSeparator ();
  _tool_bar->addAction (_run_action);
  _tool_bar->addSeparator ();
  _tool_bar->addAction (_toggle_breakpoint_action);
  _tool_bar->addAction (_previous_breakpoint_action);
  _tool_bar->addAction (_next_breakpoint_action);
  _tool_bar->addAction (_remove_all_breakpoints_action);

  // layout
  QVBoxLayout *vbox_layout = new QVBoxLayout ();
  vbox_layout->addWidget (_menu_bar);
  vbox_layout->addWidget (_tool_bar);
  vbox_layout->addWidget (_tab_widget);
  vbox_layout->setMargin (0);
  editor_widget->setLayout (vbox_layout);
  setWidget (editor_widget);

  // signals
  connect (this, SIGNAL (request_settings_dialog (const QString&)),
           main_win (),
           SLOT (process_settings_dialog_request (const QString&)));

  connect (main_win (), SIGNAL (new_file_signal (const QString&)),
           this, SLOT (request_new_file (const QString&)));

  connect (main_win (), SIGNAL (open_file_signal (const QString&)),
           this, SLOT (request_open_file (const QString&)));

  connect (main_win (), SIGNAL (edit_mfile_request (const QString&,
                                       const QString&, const QString&, int)),
           this, SLOT (handle_edit_mfile_request (const QString&,
                                       const QString&, const QString&, int)));

  connect (_mru_file_menu, SIGNAL (triggered (QAction *)),
           this, SLOT (request_mru_open_file (QAction *)));

  mru_menu_update ();

  connect (_tab_widget, SIGNAL (tabCloseRequested (int)),
           this, SLOT (handle_tab_close_request (int)));

  connect (_tab_widget, SIGNAL (currentChanged (int)),
           this, SLOT (active_tab_changed (int)));

  resize (500, 400);
  setWindowIcon (QIcon (":/actions/icons/logo.png"));
  set_title (tr ("Editor"));

  restore_session (settings);

  check_actions ();
}

void
file_editor::restore_session (QSettings *settings)
{
  //restore previous session
  if (! settings->value ("editor/restoreSession", true).toBool ())
    return;

  // get the data from the settings file
  QStringList sessionFileNames = settings->value ("editor/savedSessionTabs",
                                          QStringList ()).toStringList ();
  QStringList session_encodings = settings->value ("editor/saved_session_encodings",
                                          QStringList ()).toStringList ();
  QStringList session_index = settings->value ("editor/saved_session_tab_index",
                                          QStringList ()).toStringList ();

  // fill a list of the struct and sort it (depending on index)
  QList<session_data> s_data;

  bool do_encoding = (session_encodings.count () == sessionFileNames.count ());
  bool do_index    = (session_index.count () == sessionFileNames.count ());

  for (int n = 0; n < sessionFileNames.count (); ++n)
    {
      QFileInfo file = QFileInfo (sessionFileNames.at (n));
      if (! file.exists ())
        continue;

      session_data item = { QString (), sessionFileNames.at (n), QString ()};
      if (do_index)
        item.index = session_index.at (n);
      if (do_encoding)
        item.encoding = session_encodings.at (n);

     s_data << item;
    }

  qSort (s_data);

  // finally open the file with the desired encoding in the desired order
  for (int n = 0; n < s_data.count (); ++n)
    request_open_file (s_data.at (n).file_name, s_data.at (n).encoding);
}

void
file_editor::add_file_editor_tab (file_editor_tab *f, const QString& fn)
{
  _tab_widget->addTab (f, fn);

  // signals from the qscintilla edit area
  connect (f->qsci_edit_area (), SIGNAL (status_update (bool, bool)),
           this, SLOT (edit_status_update (bool, bool)));

  connect (f->qsci_edit_area (), SIGNAL (show_doc_signal (const QString&)),
           main_win (), SLOT (handle_show_doc (const QString&)));

  connect (f->qsci_edit_area (), SIGNAL (create_context_menu_signal (QMenu *)),
           this, SLOT (create_context_menu (QMenu *)));

  connect (f->qsci_edit_area (), SIGNAL (execute_command_in_terminal_signal (const QString&)),
           main_win (), SLOT (execute_command_in_terminal (const QString&)));

  // Signals from the file editor_tab
  connect (f, SIGNAL (file_name_changed (const QString&, const QString&)),
           this, SLOT (handle_file_name_changed (const QString&,
                                                 const QString&)));

  connect (f, SIGNAL (editor_state_changed (bool, bool)),
           this, SLOT (handle_editor_state_changed (bool, bool)));

  connect (f, SIGNAL (tab_remove_request ()),
           this, SLOT (handle_tab_remove_request ()));

  connect (f, SIGNAL (add_filename_to_list (const QString&,
                                            const QString&, QWidget*)),
           this, SLOT (handle_add_filename_to_list (const QString&,
                                                    const QString&, QWidget*)));

  connect (f, SIGNAL (editor_check_conflict_save (const QString&, bool)),
           this, SLOT (check_conflict_save (const QString&, bool)));

  connect (f, SIGNAL (mru_add_file (const QString&, const QString&)),
           this, SLOT (handle_mru_add_file (const QString&, const QString&)));

  connect (f, SIGNAL (run_file_signal (const QFileInfo&)),
           main_win (), SLOT (run_file_in_terminal (const QFileInfo&)));

  connect (f, SIGNAL (request_open_file (const QString&)),
           this, SLOT (request_open_file (const QString&)));

  connect (f, SIGNAL (edit_mfile_request (const QString&, const QString&,
                                          const QString&, int)),
           this, SLOT (handle_edit_mfile_request (const QString&, const QString&,
                                                  const QString&, int)));

  // Signals from the file_editor non-trivial operations
  connect (this, SIGNAL (fetab_settings_changed (const QSettings *)),
           f, SLOT (notice_settings (const QSettings *)));

  connect (this, SIGNAL (fetab_change_request (const QWidget*)),
           f, SLOT (change_editor_state (const QWidget*)));

  connect (this, SIGNAL (fetab_file_name_query (const QWidget*)),
           f, SLOT (file_name_query (const QWidget*)));

  connect (this, SIGNAL (fetab_save_file (const QWidget*, const QString&,
                                          bool)),
           f, SLOT (save_file (const QWidget*, const QString&, bool)));

  connect (this, SIGNAL (fetab_check_modified_file (void)),
           f, SLOT (check_modified_file (void)));

  connect (f, SIGNAL (execute_command_in_terminal_signal (const QString&)),
           main_win (), SLOT (execute_command_in_terminal (const QString&)));

  // Signals from the file_editor trivial operations
  connect (this, SIGNAL (fetab_recover_from_exit (void)),
           f, SLOT (recover_from_exit (void)));

  connect (this, SIGNAL (fetab_set_directory (const QString&)),
           f, SLOT (set_current_directory (const QString&)));

  connect (this, SIGNAL (fetab_zoom_in (const QWidget*)),
           f, SLOT (zoom_in (const QWidget*)));
  connect (this, SIGNAL (fetab_zoom_out (const QWidget*)),
           f, SLOT (zoom_out (const QWidget*)));
  connect (this, SIGNAL (fetab_zoom_normal (const QWidget*)),
           f, SLOT (zoom_normal (const QWidget*)));

  connect (this, SIGNAL (fetab_context_help (const QWidget*, bool)),
           f, SLOT (context_help (const QWidget*, bool)));

  connect (this, SIGNAL (fetab_context_edit (const QWidget*)),
           f, SLOT (context_edit (const QWidget*)));

  connect (this, SIGNAL (fetab_save_file (const QWidget*)),
           f, SLOT (save_file (const QWidget*)));

  connect (this, SIGNAL (fetab_save_file_as (const QWidget*)),
           f, SLOT (save_file_as (const QWidget*)));

  connect (this, SIGNAL (fetab_print_file (const QWidget*)),
           f, SLOT (print_file (const QWidget*)));

  connect (this, SIGNAL (fetab_run_file (const QWidget*)),
           f, SLOT (run_file (const QWidget*)));

  connect (this, SIGNAL (fetab_context_run (const QWidget*)),
           f, SLOT (context_run (const QWidget*)));

  connect (this, SIGNAL (fetab_toggle_bookmark (const QWidget*)),
           f, SLOT (toggle_bookmark (const QWidget*)));

  connect (this, SIGNAL (fetab_next_bookmark (const QWidget*)),
           f, SLOT (next_bookmark (const QWidget*)));

  connect (this, SIGNAL (fetab_previous_bookmark (const QWidget*)),
           f, SLOT (previous_bookmark (const QWidget*)));

  connect (this, SIGNAL (fetab_remove_bookmark (const QWidget*)),
           f, SLOT (remove_bookmark (const QWidget*)));

  connect (this, SIGNAL (fetab_toggle_breakpoint (const QWidget*)),
           f, SLOT (toggle_breakpoint (const QWidget*)));

  connect (this, SIGNAL (fetab_next_breakpoint (const QWidget*)),
           f, SLOT (next_breakpoint (const QWidget*)));

  connect (this, SIGNAL (fetab_previous_breakpoint (const QWidget*)),
           f, SLOT (previous_breakpoint (const QWidget*)));

  connect (this, SIGNAL (fetab_remove_all_breakpoints (const QWidget*)),
           f, SLOT (remove_all_breakpoints (const QWidget*)));

  connect (this, SIGNAL (fetab_scintilla_command (const QWidget *, unsigned int)),
           f, SLOT (scintilla_command (const QWidget *, unsigned int)));

  connect (this, SIGNAL (fetab_comment_selected_text (const QWidget*)),
           f, SLOT (comment_selected_text (const QWidget*)));

  connect (this, SIGNAL (fetab_uncomment_selected_text (const QWidget*)),
           f, SLOT (uncomment_selected_text (const QWidget*)));

  connect (this, SIGNAL (fetab_indent_selected_text (const QWidget*)),
           f, SLOT (indent_selected_text (const QWidget*)));

  connect (this, SIGNAL (fetab_unindent_selected_text (const QWidget*)),
           f, SLOT (unindent_selected_text (const QWidget*)));

  connect (this, SIGNAL (fetab_convert_eol (const QWidget*, QsciScintilla::EolMode)),
           f, SLOT (convert_eol (const QWidget*, QsciScintilla::EolMode)));

  connect (this, SIGNAL (fetab_find (const QWidget*)),
           f, SLOT (find (const QWidget*)));

  connect (this, SIGNAL (fetab_goto_line (const QWidget*, int)),
           f, SLOT (goto_line (const QWidget*, int)));

  connect (this, SIGNAL (fetab_move_match_brace (const QWidget*, bool)),
           f, SLOT (move_match_brace (const QWidget*, bool)));

  connect (this, SIGNAL (fetab_completion (const QWidget*)),
           f, SLOT (show_auto_completion (const QWidget*)));

  connect (this, SIGNAL (fetab_set_focus (const QWidget*)),
           f, SLOT (set_focus (const QWidget*)));

  connect (this, SIGNAL (fetab_insert_debugger_pointer (const QWidget*, int)),
           f, SLOT (insert_debugger_pointer (const QWidget*, int)));

  connect (this, SIGNAL (fetab_delete_debugger_pointer (const QWidget*, int)),
           f, SLOT (delete_debugger_pointer (const QWidget*, int)));

  connect (this, SIGNAL (fetab_do_breakpoint_marker (bool, const QWidget*,
                                                     int, const QString&)),
           f, SLOT (do_breakpoint_marker (bool, const QWidget*, int,
                                          const QString&)));

  _tab_widget->setCurrentWidget (f);

  check_actions ();
}

bool
file_editor::editor_tab_has_focus ()
{
  QWidget * foc_w = focusWidget ();
  if (foc_w && foc_w->inherits ("octave_qscintilla"))
    return true;
  return false;
}

void
file_editor::set_shortcuts ()
{
  // Shortcuts also available in the main window, as well as the realted
  // ahotcuts, are defined in main_window and added to the editor

  // File menu
  shortcut_manager::set_shortcut (_edit_function_action, "editor_file:edit_function");
  shortcut_manager::set_shortcut (_save_action, "editor_file:save");
  shortcut_manager::set_shortcut (_save_as_action, "editor_file:save_as");
  shortcut_manager::set_shortcut (_close_action, "editor_file:close");
  shortcut_manager::set_shortcut (_close_all_action, "editor_file:close_all");
  shortcut_manager::set_shortcut (_close_others_action, "editor_file:close_other");
  shortcut_manager::set_shortcut (_print_action, "editor_file:print");

  // Edit menu
  shortcut_manager::set_shortcut (_redo_action, "editor_edit:redo");
  shortcut_manager::set_shortcut (_cut_action, "editor_edit:cut");
  shortcut_manager::set_shortcut (_find_action, "editor_edit:find_replace");

  shortcut_manager::set_shortcut (_delete_start_word_action, "editor_edit:delete_start_word");
  shortcut_manager::set_shortcut (_delete_end_word_action, "editor_edit:delete_end_word");
  shortcut_manager::set_shortcut (_delete_start_line_action, "editor_edit:delete_start_line");
  shortcut_manager::set_shortcut (_delete_end_line_action, "editor_edit:delete_end_line");
  shortcut_manager::set_shortcut (_delete_line_action, "editor_edit:delete_line");
  shortcut_manager::set_shortcut (_copy_line_action, "editor_edit:copy_line");
  shortcut_manager::set_shortcut (_cut_line_action, "editor_edit:cut_line");
  shortcut_manager::set_shortcut (_duplicate_selection_action, "editor_edit:duplicate_selection");
  shortcut_manager::set_shortcut (_transpose_line_action, "editor_edit:transpose_line");
  shortcut_manager::set_shortcut (_comment_selection_action, "editor_edit:comment_selection");
  shortcut_manager::set_shortcut (_uncomment_selection_action, "editor_edit:uncomment_selection");

  shortcut_manager::set_shortcut (_upper_case_action, "editor_edit:upper_case");
  shortcut_manager::set_shortcut (_lower_case_action, "editor_edit:lower_case");
  shortcut_manager::set_shortcut (_indent_selection_action, "editor_edit:indent_selection");
  shortcut_manager::set_shortcut (_unindent_selection_action, "editor_edit:unindent_selection");
  shortcut_manager::set_shortcut (_completion_action, "editor_edit:completion_list");
  shortcut_manager::set_shortcut (_goto_line_action, "editor_edit:goto_line");
  shortcut_manager::set_shortcut (_move_to_matching_brace, "editor_edit:move_to_brace");
  shortcut_manager::set_shortcut (_sel_to_matching_brace, "editor_edit:select_to_brace");
  shortcut_manager::set_shortcut (_toggle_bookmark_action, "editor_edit:toggle_bookmark");
  shortcut_manager::set_shortcut (_next_bookmark_action, "editor_edit:next_bookmark");
  shortcut_manager::set_shortcut (_previous_bookmark_action, "editor_edit:previous_bookmark");
  shortcut_manager::set_shortcut (_remove_bookmark_action, "editor_edit:remove_bookmark");
  shortcut_manager::set_shortcut (_preferences_action, "editor_edit:preferences");
  shortcut_manager::set_shortcut (_styles_preferences_action, "editor_edit:styles_preferences");

  shortcut_manager::set_shortcut (_conv_eol_windows_action, "editor_edit:conv_eol_winows");
  shortcut_manager::set_shortcut (_conv_eol_unix_action,    "editor_edit:conv_eol_unix");
  shortcut_manager::set_shortcut (_conv_eol_mac_action,     "editor_edit:conv_eol_mac");

  // View menu
  shortcut_manager::set_shortcut (_show_linenum_action, "editor_view:show_line_numbers");
  shortcut_manager::set_shortcut (_show_whitespace_action, "editor_view:show_white_spaces");
  shortcut_manager::set_shortcut (_show_eol_action, "editor_view:show_eol_chars");
  shortcut_manager::set_shortcut (_show_indguide_action, "editor_view:show_ind_guides");
  shortcut_manager::set_shortcut (_show_longline_action, "editor_view:show_long_line");
  shortcut_manager::set_shortcut (_show_toolbar_action, "editor_view:show_toolbar");
  shortcut_manager::set_shortcut (_show_statusbar_action, "editor_view:show_statusbar");
  shortcut_manager::set_shortcut (_show_hscrollbar_action, "editor_view:show_hscrollbar");
  shortcut_manager::set_shortcut (_zoom_in_action, "editor_view:zoom_in");
  shortcut_manager::set_shortcut (_zoom_out_action, "editor_view:zoom_out");
  shortcut_manager::set_shortcut (_zoom_normal_action, "editor_view:zoom_normal");

  // Debug menu
  shortcut_manager::set_shortcut (_toggle_breakpoint_action, "editor_debug:toggle_breakpoint");
  shortcut_manager::set_shortcut (_next_breakpoint_action, "editor_debug:next_breakpoint");
  shortcut_manager::set_shortcut (_previous_breakpoint_action, "editor_debug:previous_breakpoint");
  shortcut_manager::set_shortcut (_remove_all_breakpoints_action, "editor_debug:remove_breakpoints");

  // Run menu
  shortcut_manager::set_shortcut (_run_action, "editor_run:run_file");
  shortcut_manager::set_shortcut (_run_selection_action, "editor_run:run_selection");

  // Help menu
  shortcut_manager::set_shortcut (_context_help_action, "editor_help:help_keyword");
  shortcut_manager::set_shortcut (_context_doc_action,  "editor_help:doc_keyword");

  // Tab navigation without menu entries
  shortcut_manager::set_shortcut (_switch_left_tab_action, "editor_tabs:switch_left_tab");
  shortcut_manager::set_shortcut (_switch_right_tab_action, "editor_tabs:switch_right_tab");
  shortcut_manager::set_shortcut (_move_tab_left_action, "editor_tabs:move_tab_left");
  shortcut_manager::set_shortcut (_move_tab_right_action, "editor_tabs:move_tab_right");

}

void
file_editor::check_actions ()
{
  bool have_tabs = _tab_widget->count () > 0;

  _edit_cmd_menu->setEnabled (have_tabs);
  _edit_fmt_menu->setEnabled (have_tabs);
  _edit_nav_menu->setEnabled (have_tabs);

  _comment_selection_action->setEnabled (have_tabs);
  _uncomment_selection_action->setEnabled (have_tabs);
  _indent_selection_action->setEnabled (have_tabs);
  _unindent_selection_action->setEnabled (have_tabs);

  _context_help_action->setEnabled (have_tabs);
  _context_doc_action->setEnabled (have_tabs);

  _view_editor_menu->setEnabled (have_tabs);
  _zoom_in_action->setEnabled (have_tabs);
  _zoom_out_action->setEnabled (have_tabs);
  _zoom_normal_action->setEnabled (have_tabs);

  _find_action->setEnabled (have_tabs);
  _print_action->setEnabled (have_tabs);
  _run_action->setEnabled (have_tabs);

  _edit_function_action->setEnabled (have_tabs);
  _save_action->setEnabled (have_tabs);
  _save_as_action->setEnabled (have_tabs);
  _close_action->setEnabled (have_tabs);
  _close_all_action->setEnabled (have_tabs);
  _close_others_action->setEnabled (have_tabs && _tab_widget->count () > 1);
}

// empty_script determines whether we have to create an empty script
// 1. At startup, when the editor has to be (really) visible
//    (Here we can not use the visibility changed signal)
// 2. When the editor becomes visible when octave is running
void
file_editor::empty_script (bool startup, bool visible)
{
  QSettings *settings = resource_manager::get_settings ();
  if (settings->value ("useCustomFileEditor",false).toBool ())
    return;  // do not open an empty script in the external editor

  bool real_visible;

  if (startup)
    real_visible = isVisible ();
  else
    real_visible = visible;

  if (! real_visible || _tab_widget->count () > 0)
    return;

  if (startup && ! isFloating ())
    {
      // check is editor is really visible or hidden between tabbed widgets
      QList<QTabBar *> tab_list = main_win ()->findChildren<QTabBar *>();

      bool in_tab = false;
      int i = 0;
      while ((i < tab_list.count ()) && (! in_tab))
        {
          QTabBar *tab = tab_list.at (i);
          i++;

          int j = 0;
          while ((j < tab->count ()) && (! in_tab))
            {
              // check all tabs for the editor
              if (tab->tabText (j) == windowTitle ())
                {
                  // editor is in this tab widget
                  in_tab = true;
                  int top = tab->currentIndex ();
                  if (top > -1 && tab->tabText (top) == windowTitle ())
                    real_visible = true;  // and is the current tab
                  else
                    return; // not current tab -> not visible
                }
              j++;
            }
        }
    }

  request_new_file ("");
}

// This slot is a reimplementation of the virtual slot in octave_dock_widget.
// We need this for creating an empty script when the editor has no open files
// and is made visible
void
file_editor::handle_visibility (bool visible)
  {
    empty_script (false, visible);

    if (visible && ! isFloating ())
      focus ();
  }

void
file_editor::dragEnterEvent (QDragEnterEvent *e)
  {
    if (e->mimeData ()->hasUrls ())
      {
        e->acceptProposedAction();
      }
  }

void
file_editor::dropEvent (QDropEvent *e)
  {
    if (e->mimeData ()->hasUrls ())
      {
        foreach (QUrl url, e->mimeData ()->urls ())
        {
          request_open_file (url.toLocalFile ());
        }
      }
  }

// slots for tab navigation
void
file_editor::switch_left_tab ()
{
  switch_tab (-1);
}
void
file_editor::switch_right_tab ()
{
  switch_tab (1);
}
void
file_editor::move_tab_left ()
{
#if defined (HAVE_QTABWIDGET_SETMOVABLE)
  switch_tab (-1, true);
#endif
}
void
file_editor::move_tab_right ()
{
#if defined (HAVE_QTABWIDGET_SETMOVABLE)
  switch_tab (1, true);
#endif
}
void
file_editor::switch_tab (int direction, bool movetab)
{
  int tabs = _tab_widget->count ();

  if (tabs < 2)
    return;

  int old_pos = _tab_widget->currentIndex ();
  int new_pos = _tab_widget->currentIndex () + direction;

  if (new_pos < 0 || new_pos >= tabs)
    new_pos = new_pos - direction*tabs;

  if (movetab)
    {
#if defined (HAVE_QTABWIDGET_SETMOVABLE)
      _tab_widget->tabBar ()->moveTab (old_pos, new_pos);
      _tab_widget->setCurrentIndex (old_pos);
      _tab_widget->setCurrentIndex (new_pos);
      focus ();
#endif
    }
  else
    _tab_widget->setCurrentIndex (new_pos);
}

#endif
