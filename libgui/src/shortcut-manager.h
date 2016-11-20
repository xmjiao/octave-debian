/*

Copyright (C) 2014-2016 Torsten <ttl@justmail.de>

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

#if ! defined (octave_shortcut_manager_h)
#define octave_shortcut_manager_h 1

#include <QWidget>
#include <QTreeWidget>
#include <QLineEdit>
#include <QKeyEvent>
#include <QLabel>
#include <QSettings>

class enter_shortcut : public QLineEdit
{
  Q_OBJECT

public:
  enter_shortcut (QWidget *p = 0);
  ~enter_shortcut ();

  virtual void keyPressEvent (QKeyEvent *e);

public slots:
  void handle_direct_shortcut (int);

private:
  bool _direct_shortcut;

};


class shortcut_manager : public QWidget
{
  Q_OBJECT

public:

  enum
  {
    OSC_IMPORT  = 0,
    OSC_EXPORT  = 1,
    OSC_DEFAULT = 2
  };

  shortcut_manager ();
  ~shortcut_manager ();

  static void init_data ()
  {
    if (instance_ok ())
      instance->do_init_data ();
  }

  static void write_shortcuts (QSettings *settings, bool closing)
  {
    if (instance_ok ())
      instance->do_write_shortcuts (settings, closing);
  }

  static void set_shortcut (QAction *action, const QString& key)
  {
    if (instance_ok ())
      instance->do_set_shortcut (action, key);
  }

  static void fill_treewidget (QTreeWidget *tree_view)
  {
    if (instance_ok ())
      instance->do_fill_treewidget (tree_view);
  }

  static void import_export (int action)
  {
    if (instance_ok ())
      instance->do_import_export (action);
  }

  static shortcut_manager *instance;

public slots:

  static void cleanup_instance (void) { delete instance; instance = 0; }

signals:

protected:

protected slots:

  void handle_double_clicked (QTreeWidgetItem*, int);
  void shortcut_dialog_finished (int);
  void shortcut_dialog_set_default ();

private:

  // No copying!

  static bool instance_ok (void);

  void init (const QString&, const QString&, const QKeySequence&);
  void do_init_data ();
  void do_write_shortcuts (QSettings *settings, bool closing);
  void do_set_shortcut (QAction *action, const QString& key);
  void do_fill_treewidget (QTreeWidget *tree_view);
  bool do_import_export (int action);
  void shortcut_dialog (int);
  void import_shortcuts (QSettings *settings);
  bool overwrite_all_shortcuts (void);

  class shortcut_t
  {
  public:

    shortcut_t (void)
      : tree_item (0), description (), settings_key (),
        actual_sc (QKeySequence ()), default_sc (QKeySequence ())
    {  }

    shortcut_t (const shortcut_t& x)
      : tree_item (x.tree_item), description (x.description),
        settings_key (x.settings_key)
    {
      actual_sc = x.actual_sc;
      default_sc = x.default_sc;
    }

    shortcut_t& operator = (const shortcut_t& x)
    {
      if (&x != this)
        {
          tree_item = x.tree_item;
          description = x.description;
          settings_key = x.settings_key;

          actual_sc = QKeySequence ();
          default_sc = QKeySequence ();

          actual_sc = x.actual_sc;
          default_sc = x.default_sc;
        }

      return *this;
    }

    ~shortcut_t (void)
    { }

    QTreeWidgetItem *tree_item;
    QString description;
    QString settings_key;
    QKeySequence actual_sc;
    QKeySequence default_sc;
  };

  QList<shortcut_t> _sc;
  QHash<QString, int> _shortcut_hash;
  QHash<QString, int> _action_hash;
  QHash <QString, QTreeWidgetItem*> _level_hash;
  QHash<int, QTreeWidgetItem*> _index_item_hash;
  QHash<QTreeWidgetItem*, int> _item_index_hash;

  QDialog *_dialog;
  enter_shortcut *_edit_actual;
  QLabel *_label_default;
  int _handled_index;

  QSettings *_settings;

};

#endif

