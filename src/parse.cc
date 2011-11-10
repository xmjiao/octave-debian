/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse octave_parse
#define yylex   octave_lex
#define yyerror octave_error
#define yylval  octave_lval
#define yychar  octave_char
#define yydebug octave_debug
#define yynerrs octave_nerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ADD_EQ = 258,
     SUB_EQ = 259,
     MUL_EQ = 260,
     DIV_EQ = 261,
     LEFTDIV_EQ = 262,
     POW_EQ = 263,
     EMUL_EQ = 264,
     EDIV_EQ = 265,
     ELEFTDIV_EQ = 266,
     EPOW_EQ = 267,
     AND_EQ = 268,
     OR_EQ = 269,
     LSHIFT_EQ = 270,
     RSHIFT_EQ = 271,
     LSHIFT = 272,
     RSHIFT = 273,
     EXPR_AND_AND = 274,
     EXPR_OR_OR = 275,
     EXPR_AND = 276,
     EXPR_OR = 277,
     EXPR_NOT = 278,
     EXPR_LT = 279,
     EXPR_LE = 280,
     EXPR_EQ = 281,
     EXPR_NE = 282,
     EXPR_GE = 283,
     EXPR_GT = 284,
     LEFTDIV = 285,
     EMUL = 286,
     EDIV = 287,
     ELEFTDIV = 288,
     EPLUS = 289,
     EMINUS = 290,
     QUOTE = 291,
     TRANSPOSE = 292,
     PLUS_PLUS = 293,
     MINUS_MINUS = 294,
     POW = 295,
     EPOW = 296,
     NUM = 297,
     IMAG_NUM = 298,
     STRUCT_ELT = 299,
     NAME = 300,
     END = 301,
     DQ_STRING = 302,
     SQ_STRING = 303,
     FOR = 304,
     WHILE = 305,
     DO = 306,
     UNTIL = 307,
     IF = 308,
     ELSEIF = 309,
     ELSE = 310,
     SWITCH = 311,
     CASE = 312,
     OTHERWISE = 313,
     BREAK = 314,
     CONTINUE = 315,
     FUNC_RET = 316,
     UNWIND = 317,
     CLEANUP = 318,
     TRY = 319,
     CATCH = 320,
     GLOBAL = 321,
     STATIC = 322,
     FCN_HANDLE = 323,
     END_OF_INPUT = 324,
     LEXICAL_ERROR = 325,
     FCN = 326,
     SCRIPT = 327,
     CLOSE_BRACE = 328,
     UNARY = 329
   };
#endif
/* Tokens.  */
#define ADD_EQ 258
#define SUB_EQ 259
#define MUL_EQ 260
#define DIV_EQ 261
#define LEFTDIV_EQ 262
#define POW_EQ 263
#define EMUL_EQ 264
#define EDIV_EQ 265
#define ELEFTDIV_EQ 266
#define EPOW_EQ 267
#define AND_EQ 268
#define OR_EQ 269
#define LSHIFT_EQ 270
#define RSHIFT_EQ 271
#define LSHIFT 272
#define RSHIFT 273
#define EXPR_AND_AND 274
#define EXPR_OR_OR 275
#define EXPR_AND 276
#define EXPR_OR 277
#define EXPR_NOT 278
#define EXPR_LT 279
#define EXPR_LE 280
#define EXPR_EQ 281
#define EXPR_NE 282
#define EXPR_GE 283
#define EXPR_GT 284
#define LEFTDIV 285
#define EMUL 286
#define EDIV 287
#define ELEFTDIV 288
#define EPLUS 289
#define EMINUS 290
#define QUOTE 291
#define TRANSPOSE 292
#define PLUS_PLUS 293
#define MINUS_MINUS 294
#define POW 295
#define EPOW 296
#define NUM 297
#define IMAG_NUM 298
#define STRUCT_ELT 299
#define NAME 300
#define END 301
#define DQ_STRING 302
#define SQ_STRING 303
#define FOR 304
#define WHILE 305
#define DO 306
#define UNTIL 307
#define IF 308
#define ELSEIF 309
#define ELSE 310
#define SWITCH 311
#define CASE 312
#define OTHERWISE 313
#define BREAK 314
#define CONTINUE 315
#define FUNC_RET 316
#define UNWIND 317
#define CLEANUP 318
#define TRY 319
#define CATCH 320
#define GLOBAL 321
#define STATIC 322
#define FCN_HANDLE 323
#define END_OF_INPUT 324
#define LEXICAL_ERROR 325
#define FCN 326
#define SCRIPT 327
#define CLOSE_BRACE 328
#define UNARY 329




/* Copy the first part of user declarations.  */
#line 28 "parse.y"

#define YYDEBUG 1

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cassert>
#include <cstdio>

#ifdef YYBYACC
#include <cstdlib>
#endif

#include <iostream>
#include <map>
#include <sstream>

#include "Cell.h"
#include "Matrix.h"
#include "cmd-edit.h"
#include "cmd-hist.h"
#include "file-ops.h"
#include "file-stat.h"
#include "oct-env.h"
#include "oct-time.h"
#include "quit.h"

#include "comment-list.h"
#include "defaults.h"
#include "defun.h"
#include "dirfns.h"
#include "dynamic-ld.h"
#include "error.h"
#include "input.h"
#include "lex.h"
#include "load-path.h"
#include "oct-hist.h"
#include "oct-map.h"
#include "ov-fcn-handle.h"
#include "ov-usr-fcn.h"
#include "ov-null-mat.h"
#include "toplev.h"
#include "pager.h"
#include "parse.h"
#include "pt-all.h"
#include "pt-eval.h"
#include "symtab.h"
#include "token.h"
#include "unwind-prot.h"
#include "utils.h"
#include "variables.h"

// The current input line number.
int input_line_number = 1;

// The column of the current token.
int current_input_column = 1;

// Buffer for help text snagged from function files.
std::stack<std::string> help_buf;

// Buffer for comments appearing before a function statement.
static std::string fcn_comment_header;

// TRUE means we are using readline.
// (--no-line-editing)
bool line_editing = true;

// TRUE means we printed messages about reading startup files.
bool reading_startup_message_printed = false;

// TRUE means input is coming from startup file.
bool input_from_startup_file = false;

// Keep a count of how many END tokens we expect.
int end_tokens_expected = 0;

// Keep track of symbol table information when parsing functions.
std::stack<symbol_table::scope_id> symtab_context;

// Name of parent function when parsing function files that might
// contain nested functions.
std::string parent_function_name;

// Name of the current class when we are parsing class methods or
// constructors.
std::string current_class_name;

// TRUE means we are in the process of autoloading a function.
static bool autoloading = false;

// TRUE means the current function file was found in a relative path
// element.
static bool fcn_file_from_relative_lookup = false;

// If nonzero, this is a pointer to the function we just finished
// parsing.
static octave_function *curr_fcn_ptr = 0;

// List of autoloads (function -> file mapping).
static std::map<std::string, std::string> autoload_map;

// Forward declarations for some functions defined at the bottom of
// the file.

// Generic error messages.
static void
yyerror (const char *s);

// Error mesages for mismatched end tokens.
static void
end_error (const char *type, token::end_tok_type ettype, int l, int c);

// Check to see that end tokens are properly matched.
static bool
end_token_ok (token *tok, token::end_tok_type expected);

// Maybe print a warning if an assignment expression is used as the
// test in a logical expression.
static void
maybe_warn_assign_as_truth_value (tree_expression *expr);

// Maybe print a warning about switch labels that aren't constants.
static void
maybe_warn_variable_switch_label (tree_expression *expr);

// Finish building a range.
static tree_expression *
finish_colon_expression (tree_colon_expression *e);

// Build a constant.
static tree_constant *
make_constant (int op, token *tok_val);

// Build a function handle.
static tree_fcn_handle *
make_fcn_handle (token *tok_val);

// Build an anonymous function handle.
static tree_anon_fcn_handle *
make_anon_fcn_handle (tree_parameter_list *param_list, tree_statement *stmt);

// Build a binary expression.
static tree_expression *
make_binary_op (int op, tree_expression *op1, token *tok_val,
		tree_expression *op2);

// Build a boolean expression.
static tree_expression *
make_boolean_op (int op, tree_expression *op1, token *tok_val,
		 tree_expression *op2);

// Build a prefix expression.
static tree_expression *
make_prefix_op (int op, tree_expression *op1, token *tok_val);

// Build a postfix expression.
static tree_expression *
make_postfix_op (int op, tree_expression *op1, token *tok_val);

// Build an unwind-protect command.
static tree_command *
make_unwind_command (token *unwind_tok, tree_statement_list *body,
		     tree_statement_list *cleanup, token *end_tok,
		     octave_comment_list *lc, octave_comment_list *mc);

// Build a try-catch command.
static tree_command *
make_try_command (token *try_tok, tree_statement_list *body,
		  tree_statement_list *cleanup, token *end_tok,
		  octave_comment_list *lc, octave_comment_list *mc);

// Build a while command.
static tree_command *
make_while_command (token *while_tok, tree_expression *expr,
		    tree_statement_list *body, token *end_tok,
		    octave_comment_list *lc);

// Build a do-until command.
static tree_command *
make_do_until_command (token *until_tok, tree_statement_list *body,
		       tree_expression *expr, octave_comment_list *lc);

// Build a for command.
static tree_command *
make_for_command (token *for_tok, tree_argument_list *lhs,
		  tree_expression *expr, tree_statement_list *body,
		  token *end_tok, octave_comment_list *lc);

// Build a break command.
static tree_command *
make_break_command (token *break_tok);

// Build a continue command.
static tree_command *
make_continue_command (token *continue_tok);

// Build a return command.
static tree_command *
make_return_command (token *return_tok);

// Start an if command.
static tree_if_command_list *
start_if_command (tree_expression *expr, tree_statement_list *list);

// Finish an if command.
static tree_if_command *
finish_if_command (token *if_tok, tree_if_command_list *list,
		   token *end_tok, octave_comment_list *lc);

// Build an elseif clause.
static tree_if_clause *
make_elseif_clause (token *elseif_tok, tree_expression *expr,
		    tree_statement_list *list, octave_comment_list *lc);

// Finish a switch command.
static tree_switch_command *
finish_switch_command (token *switch_tok, tree_expression *expr,
		       tree_switch_case_list *list, token *end_tok,
		       octave_comment_list *lc);

// Build a switch case.
static tree_switch_case *
make_switch_case (token *case_tok, tree_expression *expr,
		  tree_statement_list *list, octave_comment_list *lc);

// Build an assignment to a variable.
static tree_expression *
make_assign_op (int op, tree_argument_list *lhs, token *eq_tok,
		tree_expression *rhs);

// Define a script.
static void
make_script (tree_statement_list *cmds, tree_statement *end_script);

// Begin defining a function.
static octave_user_function *
start_function (tree_parameter_list *param_list, tree_statement_list *body,
		tree_statement *end_function);

// Create a no-op statement for end_function.
static tree_statement *
make_end (const std::string& type, int l, int c);

// Do most of the work for defining a function.
static octave_user_function *
frob_function (const std::string& fname, octave_user_function *fcn);

// Finish defining a function.
static tree_function_def *
finish_function (tree_parameter_list *ret_list,
		 octave_user_function *fcn, octave_comment_list *lc);

// Reset state after parsing function.
static void
recover_from_parsing_function (void);

// Make an index expression.
static tree_index_expression *
make_index_expression (tree_expression *expr,
		       tree_argument_list *args, char type);

// Make an indirect reference expression.
static tree_index_expression *
make_indirect_ref (tree_expression *expr, const std::string&);

// Make an indirect reference expression with dynamic field name.
static tree_index_expression *
make_indirect_ref (tree_expression *expr, tree_expression *field);

// Make a declaration command.
static tree_decl_command *
make_decl_command (int tok, token *tok_val, tree_decl_init_list *lst);

// Finish building a matrix list.
static tree_expression *
finish_matrix (tree_matrix *m);

// Finish building a cell list.
static tree_expression *
finish_cell (tree_cell *c);

// Maybe print a warning.  Duh.
static void
maybe_warn_missing_semi (tree_statement_list *);

// Set the print flag for a statement based on the separator type.
static tree_statement_list *
set_stmt_print_flag (tree_statement_list *, char, bool);

// Create a statement list.
static tree_statement_list *make_statement_list (tree_statement *stmt);

// Append a statement to an existing statement list.
static tree_statement_list *
append_statement_list (tree_statement_list *list, char sep,
		       tree_statement *stmt, bool warn_missing_semi);

// Finish building a statement.
template <class T>
static tree_statement *
make_statement (T *arg)
{
  octave_comment_list *comment = octave_comment_buffer::get_comment ();

  return new tree_statement (arg, comment);
}

#define ABORT_PARSE \
  do \
    { \
      global_command = 0; \
      yyerrok; \
      if (! symtab_context.empty ()) \
        { \
	  symbol_table::set_scope (symtab_context.top ()); \
	  symtab_context.pop (); \
        } \
      if (interactive || forced_interactive) \
	YYACCEPT; \
      else \
	YYABORT; \
    } \
  while (0)



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 364 "parse.y"
{
  // The type of the basic tokens returned by the lexer.
  token *tok_val;

  // Comment strings that we need to deal with mid-rule.
  octave_comment_list *comment_type;

  // Types for the nonterminals we generate.
  char sep_type;
  tree *tree_type;
  tree_matrix *tree_matrix_type;
  tree_cell *tree_cell_type;
  tree_expression *tree_expression_type;
  tree_constant *tree_constant_type;
  tree_fcn_handle *tree_fcn_handle_type;
  tree_anon_fcn_handle *tree_anon_fcn_handle_type;
  tree_identifier *tree_identifier_type;
  tree_index_expression *tree_index_expression_type;
  tree_colon_expression *tree_colon_expression_type;
  tree_argument_list *tree_argument_list_type;
  tree_parameter_list *tree_parameter_list_type;
  tree_command *tree_command_type;
  tree_if_command *tree_if_command_type;
  tree_if_clause *tree_if_clause_type;
  tree_if_command_list *tree_if_command_list_type;
  tree_switch_command *tree_switch_command_type;
  tree_switch_case *tree_switch_case_type;
  tree_switch_case_list *tree_switch_case_list_type;
  tree_decl_elt *tree_decl_elt_type;
  tree_decl_init_list *tree_decl_init_list_type;
  tree_decl_command *tree_decl_command_type;
  tree_statement *tree_statement_type;
  tree_statement_list *tree_statement_list_type;
  octave_user_function *octave_user_function_type;
}
/* Line 187 of yacc.c.  */
#line 616 "parse.cc"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 629 "parse.cc"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  110
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   986

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  77
/* YYNRULES -- Number of rules.  */
#define YYNRULES  209
/* YYNRULES -- Number of states.  */
#define YYNSTATES  366

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   329

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      82,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      84,    91,     7,     6,    81,     5,    85,     8,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     4,    80,
       2,     3,     2,     2,    90,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    87,     2,    88,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    86,     2,    89,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    83
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    19,
      22,    25,    27,    31,    32,    34,    37,    39,    43,    45,
      47,    49,    52,    54,    57,    59,    61,    63,    65,    67,
      69,    72,    76,    80,    84,    86,    89,    91,    95,    98,
     102,   106,   108,   111,   113,   117,   119,   122,   125,   129,
     131,   133,   135,   137,   139,   143,   145,   147,   149,   153,
     157,   159,   161,   165,   170,   174,   179,   182,   185,   188,
     191,   195,   201,   203,   205,   208,   211,   214,   217,   220,
     224,   228,   232,   236,   240,   244,   248,   252,   256,   260,
     264,   268,   270,   272,   276,   278,   282,   286,   290,   294,
     298,   302,   306,   310,   314,   318,   322,   326,   328,   332,
     336,   340,   344,   348,   352,   356,   360,   364,   368,   372,
     376,   380,   384,   388,   392,   394,   396,   398,   400,   402,
     404,   406,   408,   410,   412,   413,   417,   421,   423,   426,
     427,   429,   434,   436,   438,   443,   445,   448,   452,   455,
     462,   467,   474,   475,   477,   480,   482,   485,   492,   497,
     504,   511,   520,   531,   533,   535,   537,   547,   557,   563,
     564,   566,   568,   572,   575,   576,   578,   580,   584,   587,
     589,   593,   595,   599,   603,   607,   610,   615,   617,   620,
     625,   629,   631,   633,   634,   636,   638,   640,   642,   645,
     648,   649,   651,   653,   655,   657,   660,   663,   666,   667
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      93,     0,    -1,    94,    -1,    95,   164,    -1,   164,    -1,
      82,    -1,    75,    -1,    95,    -1,    95,    82,    -1,    95,
      75,    -1,    96,   166,    -1,   100,    -1,    96,   165,   100,
      -1,    -1,    98,    -1,    99,   168,    -1,   100,    -1,    99,
     167,   100,    -1,   127,    -1,   128,    -1,   101,    -1,   103,
     102,    -1,   104,    -1,   102,   104,    -1,    51,    -1,    53,
      -1,    54,    -1,    48,    -1,    49,    -1,   104,    -1,    87,
      88,    -1,    87,    80,    88,    -1,    87,    81,    88,    -1,
      87,   107,    88,    -1,   108,    -1,   108,    80,    -1,   112,
      -1,   108,    80,   112,    -1,    86,    89,    -1,    86,    80,
      89,    -1,    86,   110,    89,    -1,   111,    -1,   111,    80,
      -1,   112,    -1,   111,    80,   112,    -1,   117,    -1,   117,
      81,    -1,    90,    74,    -1,    90,   151,   100,    -1,   103,
      -1,   105,    -1,   113,    -1,   106,    -1,   109,    -1,    84,
     127,    91,    -1,     4,    -1,   127,    -1,   116,    -1,   117,
      81,   116,    -1,   117,    81,   127,    -1,    85,    -1,   115,
      -1,   119,    84,    91,    -1,   119,    84,   117,    91,    -1,
     119,    86,    89,    -1,   119,    86,   117,    89,    -1,   119,
      44,    -1,   119,    45,    -1,   119,    42,    -1,   119,    43,
      -1,   119,   118,    50,    -1,   119,   118,    84,   127,    91,
      -1,   119,    -1,   121,    -1,    44,   120,    -1,    45,   120,
      -1,    29,   120,    -1,     6,   120,    -1,     5,   120,    -1,
     120,    46,   120,    -1,   120,    47,   120,    -1,   120,     6,
     120,    -1,   120,     5,   120,    -1,   120,     7,   120,    -1,
     120,     8,   120,    -1,   120,    40,   120,    -1,   120,    41,
     120,    -1,   120,    37,   120,    -1,   120,    38,   120,    -1,
     120,    36,   120,    -1,   120,    39,   120,    -1,   123,    -1,
     120,    -1,   123,     4,   120,    -1,   122,    -1,   124,    23,
     124,    -1,   124,    24,   124,    -1,   124,    30,   124,    -1,
     124,    31,   124,    -1,   124,    32,   124,    -1,   124,    34,
     124,    -1,   124,    35,   124,    -1,   124,    33,   124,    -1,
     124,    27,   124,    -1,   124,    28,   124,    -1,   124,    25,
     124,    -1,   124,    26,   124,    -1,   124,    -1,    87,   117,
      79,    -1,   125,     3,   127,    -1,   125,     9,   127,    -1,
     125,    10,   127,    -1,   125,    11,   127,    -1,   125,    12,
     127,    -1,   125,    13,   127,    -1,   125,    14,   127,    -1,
     125,    21,   127,    -1,   125,    22,   127,    -1,   125,    15,
     127,    -1,   125,    16,   127,    -1,   125,    17,   127,    -1,
     125,    18,   127,    -1,   125,    19,   127,    -1,   125,    20,
     127,    -1,   124,    -1,   126,    -1,   114,    -1,   130,    -1,
     134,    -1,   145,    -1,   146,    -1,   147,    -1,   158,    -1,
     156,    -1,    -1,    72,   129,   131,    -1,    73,   129,   131,
      -1,   133,    -1,   131,   133,    -1,    -1,   103,    -1,   103,
       3,   132,   127,    -1,   135,    -1,   140,    -1,    59,   163,
     136,    52,    -1,   137,    -1,   137,   139,    -1,   127,   168,
      97,    -1,   137,   138,    -1,    60,   163,   168,   127,   168,
      97,    -1,    61,   163,   168,    97,    -1,    62,   163,   127,
     168,   141,    52,    -1,    -1,   142,    -1,   142,   144,    -1,
     143,    -1,   142,   143,    -1,    63,   163,   168,   127,   168,
      97,    -1,    64,   163,   168,    97,    -1,    56,   163,   127,
     168,    97,    52,    -1,    57,   163,   168,    97,    58,   127,
      -1,    55,   163,   125,     3,   127,   168,    97,    52,    -1,
      55,   163,    84,   125,     3,   127,    91,   168,    97,    52,
      -1,    65,    -1,    66,    -1,    67,    -1,    68,   163,   168,
      97,    69,   163,   168,    97,    52,    -1,    70,   163,   168,
      97,    71,   163,   168,    97,    52,    -1,    70,   163,   168,
      97,    52,    -1,    -1,    84,    -1,    91,    -1,   149,   152,
     150,    -1,   149,     1,    -1,    -1,   153,    -1,   133,    -1,
     153,    81,   133,    -1,    87,    88,    -1,   155,    -1,    87,
     155,    88,    -1,   103,    -1,   155,    81,   103,    -1,    78,
      97,    75,    -1,   148,    77,   163,    -1,   157,   160,    -1,
     157,   154,     3,   160,    -1,   103,    -1,   159,   161,    -1,
     151,   168,    97,   162,    -1,   168,    97,   162,    -1,    52,
      -1,    75,    -1,    -1,    76,    -1,     1,    -1,    81,    -1,
      80,    -1,   165,    81,    -1,   165,    80,    -1,    -1,   165,
      -1,    81,    -1,    80,    -1,    82,    -1,   167,    81,    -1,
     167,    80,    -1,   167,    82,    -1,    -1,   167,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   491,   491,   497,   499,   503,   505,   510,   512,   514,
     518,   522,   524,   529,   530,   534,   538,   540,   544,   546,
     548,   560,   564,   566,   577,   584,   586,   590,   592,   594,
     598,   604,   610,   616,   624,   626,   630,   632,   639,   641,
     643,   647,   649,   653,   655,   663,   665,   669,   676,   680,
     682,   684,   686,   688,   690,   694,   701,   703,   705,   710,
     717,   721,   723,   725,   727,   729,   731,   733,   735,   737,
     739,   741,   745,   747,   749,   751,   753,   755,   757,   761,
     763,   765,   767,   769,   771,   773,   775,   777,   779,   781,
     783,   787,   791,   793,   800,   802,   804,   806,   808,   810,
     812,   814,   816,   818,   820,   822,   824,   831,   836,   850,
     852,   854,   856,   858,   860,   862,   864,   866,   868,   870,
     872,   874,   876,   878,   882,   884,   886,   894,   896,   898,
     900,   902,   904,   906,   916,   918,   923,   930,   932,   940,
     942,   944,   955,   957,   965,   972,   974,   981,   983,   990,
     994,  1002,  1010,  1011,  1013,  1020,  1022,  1029,  1033,  1043,
    1048,  1053,  1058,  1069,  1074,  1079,  1090,  1096,  1102,  1114,
    1127,  1140,  1147,  1152,  1161,  1162,  1172,  1174,  1185,  1190,
    1198,  1208,  1210,  1221,  1237,  1241,  1246,  1253,  1268,  1279,
    1281,  1285,  1292,  1311,  1314,  1316,  1319,  1321,  1323,  1325,
    1330,  1331,  1335,  1337,  1339,  1341,  1343,  1345,  1350,  1351
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'='", "':'", "'-'", "'+'", "'*'", "'/'",
  "ADD_EQ", "SUB_EQ", "MUL_EQ", "DIV_EQ", "LEFTDIV_EQ", "POW_EQ",
  "EMUL_EQ", "EDIV_EQ", "ELEFTDIV_EQ", "EPOW_EQ", "AND_EQ", "OR_EQ",
  "LSHIFT_EQ", "RSHIFT_EQ", "LSHIFT", "RSHIFT", "EXPR_AND_AND",
  "EXPR_OR_OR", "EXPR_AND", "EXPR_OR", "EXPR_NOT", "EXPR_LT", "EXPR_LE",
  "EXPR_EQ", "EXPR_NE", "EXPR_GE", "EXPR_GT", "LEFTDIV", "EMUL", "EDIV",
  "ELEFTDIV", "EPLUS", "EMINUS", "QUOTE", "TRANSPOSE", "PLUS_PLUS",
  "MINUS_MINUS", "POW", "EPOW", "NUM", "IMAG_NUM", "STRUCT_ELT", "NAME",
  "END", "DQ_STRING", "SQ_STRING", "FOR", "WHILE", "DO", "UNTIL", "IF",
  "ELSEIF", "ELSE", "SWITCH", "CASE", "OTHERWISE", "BREAK", "CONTINUE",
  "FUNC_RET", "UNWIND", "CLEANUP", "TRY", "CATCH", "GLOBAL", "STATIC",
  "FCN_HANDLE", "END_OF_INPUT", "LEXICAL_ERROR", "FCN", "SCRIPT",
  "CLOSE_BRACE", "';'", "','", "'\\n'", "UNARY", "'('", "'.'", "'{'",
  "'['", "']'", "'}'", "'@'", "')'", "$accept", "input", "input1",
  "simple_list", "simple_list1", "opt_list", "list", "list1", "statement",
  "word_list_cmd", "word_list", "identifier", "string", "constant",
  "matrix", "matrix_rows", "matrix_rows1", "cell", "cell_rows",
  "cell_rows1", "cell_or_matrix_row", "fcn_handle", "anon_fcn_handle",
  "primary_expr", "magic_colon", "arg_list", "indirect_ref_op",
  "postfix_expr", "prefix_expr", "binary_expr", "colon_expr",
  "colon_expr1", "simple_expr", "assign_lhs", "assign_expr", "expression",
  "command", "parsing_decl_list", "declaration", "decl1",
  "decl_param_init", "decl2", "select_command", "if_command",
  "if_cmd_list", "if_cmd_list1", "elseif_clause", "else_clause",
  "switch_command", "case_list", "case_list1", "switch_case",
  "default_case", "loop_command", "jump_command", "except_command",
  "push_fcn_symtab", "param_list_beg", "param_list_end", "param_list",
  "param_list1", "param_list2", "return_list", "return_list1", "script",
  "function_beg", "function", "fcn_name", "function1", "function2",
  "function_end", "stash_comment", "parse_error", "sep_no_nl",
  "opt_sep_no_nl", "sep", "opt_sep", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,    61,    58,    45,    43,    42,    47,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
      59,    44,    10,   329,    40,    46,   123,    91,    93,   125,
      64,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    92,    93,    93,    93,    94,    94,    94,    94,    94,
      95,    96,    96,    97,    97,    98,    99,    99,   100,   100,
     100,   101,   102,   102,   103,   104,   104,   105,   105,   105,
     106,   106,   106,   106,   107,   107,   108,   108,   109,   109,
     109,   110,   110,   111,   111,   112,   112,   113,   114,   115,
     115,   115,   115,   115,   115,   116,   117,   117,   117,   117,
     118,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   120,   120,   120,   120,   120,   120,   120,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   122,   123,   123,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   125,   125,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   127,   127,   127,   128,   128,   128,
     128,   128,   128,   128,   129,   130,   130,   131,   131,   132,
     133,   133,   134,   134,   135,   136,   136,   137,   137,   138,
     139,   140,   141,   141,   141,   142,   142,   143,   144,   145,
     145,   145,   145,   146,   146,   146,   147,   147,   147,   148,
     149,   150,   151,   151,   152,   152,   153,   153,   154,   154,
     154,   155,   155,   156,   157,   158,   158,   159,   160,   161,
     161,   162,   162,   163,   164,   164,   165,   165,   165,   165,
     166,   166,   167,   167,   167,   167,   167,   167,   168,   168
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     2,     2,
       2,     1,     3,     0,     1,     2,     1,     3,     1,     1,
       1,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       2,     3,     3,     3,     1,     2,     1,     3,     2,     3,
       3,     1,     2,     1,     3,     1,     2,     2,     3,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     3,     3,
       1,     1,     3,     4,     3,     4,     2,     2,     2,     2,
       3,     5,     1,     1,     2,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     3,     3,     1,     2,     0,
       1,     4,     1,     1,     4,     1,     2,     3,     2,     6,
       4,     6,     0,     1,     2,     1,     2,     6,     4,     6,
       6,     8,    10,     1,     1,     1,     9,     9,     5,     0,
       1,     1,     3,     2,     0,     1,     1,     3,     2,     1,
       3,     1,     3,     3,     3,     2,     4,     1,     2,     4,
       3,     1,     1,     0,     1,     1,     1,     1,     2,     2,
       0,     1,     1,     1,     1,     2,     2,     2,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   195,     0,     0,     0,     0,     0,    27,    28,    24,
      25,    26,   193,   193,   193,   193,   193,   163,   164,   165,
     193,   193,   134,   134,     6,   194,    13,     5,     0,     0,
       0,     0,     0,     2,     0,   200,    11,    20,    49,    29,
      50,    52,    53,    51,   126,    61,    72,    92,    73,    94,
      91,   124,     0,   125,    18,    19,   127,   128,   142,   143,
     129,   130,   131,     0,   133,     0,   132,     4,     0,     0,
      49,    78,    77,    76,    74,    75,     0,     0,   208,     0,
       0,   208,   208,     0,     0,     0,    14,   208,    16,     0,
      55,     0,    38,     0,    41,    43,    57,    45,    56,     0,
       0,    30,     0,    34,    36,    45,    47,   170,     0,   169,
       1,     9,     8,     3,   197,   196,   201,    10,    21,    22,
      68,    69,    66,    67,     0,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   193,     0,
     187,     0,   179,   208,   185,     0,   107,     0,   208,   203,
     202,   204,   209,    13,   208,     0,   145,   208,    13,    13,
     140,   135,   137,   136,   183,   209,    15,    54,    39,    40,
      42,    46,    31,    32,    33,    35,   108,   173,   176,     0,
     175,    48,   199,   198,    12,    23,    62,     0,    64,     0,
      70,     0,    82,    81,    83,    84,    89,    87,    88,    90,
      85,    86,    79,    80,    93,    95,    96,   105,   106,   103,
     104,    97,    98,    99,   102,   100,   101,   109,   110,   111,
     112,   113,   114,   115,   118,   119,   120,   121,   122,   123,
     116,   117,   184,   178,   181,     0,     0,     0,   208,   188,
      13,     0,     0,    13,   206,   205,   207,     0,    13,   144,
     193,   193,   148,   146,   152,     0,     0,   139,   138,    17,
      44,    58,    59,    37,   171,   172,     0,     0,    63,    65,
       0,   180,   187,   186,   182,    13,     0,     0,   208,     0,
       0,   147,   208,   208,   193,     0,   153,   155,   193,   168,
     193,     0,   177,    71,     0,   191,   192,   190,     0,    13,
     159,   160,     0,    13,   208,   151,   193,   156,   154,   208,
     208,   141,   189,   208,     0,   208,   150,     0,   208,    13,
      13,    13,   161,    13,   208,    13,     0,     0,     0,   149,
      13,   158,   166,   167,   162,   157
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    32,    33,    34,    35,    85,    86,    87,    88,    37,
     118,    70,    39,    40,    41,   102,   103,    42,    93,    94,
     104,    43,    44,    45,    96,    97,   127,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    83,    56,   191,
     321,   192,    57,    58,   185,   186,   282,   283,    59,   315,
     316,   317,   338,    60,    61,    62,    63,   108,   295,   109,
     209,   210,   171,   172,    64,    65,    66,   173,   174,   269,
     327,    76,    67,   116,   117,   182,   183
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -191
static const yytype_int16 yypact[] =
{
     351,  -191,   843,   843,   843,   843,   843,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,   705,  -191,   857,   438,
     426,   -54,    29,  -191,    42,   -36,  -191,  -191,    23,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,   -11,   561,  -191,  -191,
      62,   951,   539,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,    -5,  -191,   -29,  -191,  -191,   426,    11,
    -191,    76,    76,    76,    76,    76,   869,   857,   -57,   857,
     857,   -57,   -57,    31,    31,    21,  -191,   -57,  -191,     9,
    -191,    40,  -191,    63,    73,  -191,  -191,    39,  -191,    79,
      80,  -191,    82,    91,  -191,    34,  -191,  -191,    20,   774,
    -191,  -191,  -191,  -191,  -191,  -191,   636,  -191,    23,  -191,
    -191,  -191,  -191,  -191,     8,  -191,   490,   -15,   843,   843,
     843,   843,   843,   843,   843,   843,   843,   843,   843,   843,
     843,   843,   843,   843,   843,   843,   843,   843,   843,   843,
     843,   843,   843,   857,   857,   857,   857,   857,   857,   857,
     857,   857,   857,   857,   857,   857,   857,   857,  -191,   -24,
      12,   169,    92,     6,  -191,   857,   712,   171,   -57,  -191,
    -191,  -191,    45,   705,   -57,   126,    84,   -57,   705,   705,
     173,    31,  -191,    31,  -191,   567,  -191,  -191,  -191,  -191,
     541,   541,  -191,  -191,  -191,   541,  -191,  -191,  -191,    88,
     101,  -191,  -191,  -191,  -191,  -191,  -191,   -13,  -191,   -53,
    -191,   857,   252,   252,    76,    76,    76,    76,    76,    76,
     252,   252,  -191,  -191,   561,  -191,  -191,   131,   307,    16,
     354,   124,   124,   124,   124,   124,   124,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,   -18,    31,    31,   -57,  -191,
     705,   657,   857,   705,  -191,  -191,  -191,   122,   705,  -191,
    -191,  -191,  -191,  -191,   121,   116,   -33,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,    31,   541,  -191,  -191,
      96,  -191,  -191,  -191,  -191,   705,   -34,   857,   -57,   138,
     857,  -191,   -57,   -57,  -191,   140,    86,  -191,  -191,  -191,
    -191,   857,  -191,  -191,   -34,  -191,  -191,  -191,   105,   705,
    -191,  -191,   857,   705,   -57,  -191,  -191,  -191,  -191,   -57,
     -57,  -191,  -191,   -57,   146,   -57,  -191,   857,   -57,   705,
     705,   705,  -191,   705,   -57,   705,   147,   149,   167,  -191,
     705,  -191,  -191,  -191,  -191,  -191
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -191,  -191,  -191,  -191,  -191,    14,  -191,  -191,     5,  -191,
    -191,     0,   -21,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
     -19,  -191,  -191,  -191,  -190,   -14,  -191,  -191,    99,  -191,
    -191,  -191,    -9,   -69,  -191,    51,  -191,   197,  -191,   137,
    -191,  -102,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,   -94,  -191,  -191,  -191,  -191,  -191,  -191,  -191,    50,
    -191,  -191,  -191,    55,  -191,  -191,  -191,  -191,   -41,  -191,
     -84,   -12,   208,  -191,  -191,   156,   -27
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -182
static const yytype_int16 yytable[] =
{
      38,    77,    78,    79,    80,    36,   208,   177,    81,    82,
      95,   291,    90,     2,     3,  -181,   105,   119,   325,   319,
     106,   207,     9,   179,   180,   181,    38,     9,   297,   110,
     107,   120,   121,   122,   123,   220,   299,     4,   320,   141,
     142,   326,    -7,     1,   114,   115,   147,   148,   149,   150,
     151,   152,     5,     6,   188,   189,     7,     8,   169,     9,
     196,    10,    11,   267,   263,   170,   140,   176,   297,   221,
     301,     9,   168,   124,   125,   126,    10,    11,   298,    89,
      98,    98,     9,   190,   190,   106,   179,   180,   181,   288,
     107,   288,    28,  -181,    29,    30,   194,   215,    31,   216,
     197,    71,    72,    73,    74,    75,   271,   291,   190,    38,
     217,  -174,   219,   206,   211,   201,    38,   111,    25,    98,
     201,   214,   138,   139,   112,   274,   275,   276,   178,   198,
     184,   187,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   280,   281,   270,   141,   142,   314,
     336,   273,   199,   200,   141,   142,   262,   278,   145,   146,
     284,   147,   148,   149,   150,   151,   152,   202,   203,   264,
     204,   205,   266,   267,   272,    98,   287,    98,   279,   294,
     310,   290,   296,    38,   314,   318,   293,   323,    38,    38,
     330,   190,   335,   190,   322,    38,   343,   277,   352,   362,
     289,   363,   285,   286,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   364,
      84,   193,   337,   268,   265,   303,    89,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     342,   305,   113,   195,     0,     0,     0,     0,     0,     0,
       0,    98,   292,     0,     0,     0,    98,     0,     0,   130,
     131,     0,     0,     0,     0,     0,   302,   304,   312,   313,
      38,     0,   300,    38,     0,     0,     0,     0,    38,     0,
       0,   329,     0,     0,   306,   332,   333,   309,   132,   133,
     134,   135,   311,     0,     0,     0,   190,     0,   138,   139,
       0,     0,   334,     0,     0,    38,   339,   347,   340,     0,
       0,     0,   349,   350,     0,     0,   351,     0,   353,   324,
       0,   355,     0,   308,   348,     0,     0,   360,     0,    38,
     141,   142,   143,    38,   145,   146,     0,   147,   148,   149,
     150,   151,   152,   344,     0,     0,     0,   346,   292,    38,
      38,    38,     1,    38,     0,    38,     2,     3,   328,     0,
      38,   331,     0,   356,   357,   358,     0,   359,     0,   361,
       0,     0,   341,     0,   365,     0,     0,   141,   142,     0,
       4,   145,     0,   345,   147,   148,   149,   150,   151,   152,
       0,     0,     0,     0,     0,     5,     6,     0,   354,     7,
       8,     0,     9,     0,    10,    11,    12,    13,    14,     0,
      15,     0,     0,    16,     0,     0,    17,    18,    19,    20,
       0,    21,     0,    22,    23,     0,    24,    25,  -169,    26,
      90,     2,     3,    27,     0,    28,     0,    29,    30,     0,
       0,    31,    90,     2,     3,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     4,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     4,     0,     0,
       5,     6,     0,     0,     7,     8,     0,     9,     0,    10,
      11,     0,     5,     6,     0,     0,     7,     8,     0,     9,
       0,    10,    11,     0,    90,     2,     3,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    99,   100,     0,     0,
      28,     0,    29,    30,   101,     0,    31,     0,    91,     4,
       0,     0,    28,     0,    29,    30,     0,    92,    31,     0,
       0,     0,     0,     0,     5,     6,     0,     0,     7,     8,
       0,     9,   153,    10,    11,    90,     2,     3,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,     0,     0,     0,     0,   128,   129,   130,   131,
       4,     0,     2,     3,    28,     0,    29,    30,     0,   218,
      31,     0,     0,     0,     0,     5,     6,     0,     0,     7,
       8,     0,     9,     0,    10,    11,     4,   132,   133,   134,
     135,   136,   137,     0,     0,     0,     0,   138,   139,     0,
       0,     5,     6,     0,     0,     7,     8,     0,     9,     0,
      10,    11,    12,    13,    14,    28,    15,    29,    30,    16,
       0,    31,    17,    18,    19,    20,     0,    21,     0,    22,
      23,     2,     3,     0,  -169,    26,     0,   274,   275,   276,
       0,    28,     0,    29,    30,     0,     0,    31,     0,     0,
     307,     0,     0,     0,     0,     4,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
       5,     6,     0,     0,     7,     8,     0,     9,     0,    10,
      11,    12,    13,    14,     0,    15,     0,     0,    16,     0,
       0,    17,    18,    19,    20,     0,    21,     0,    22,    23,
       2,     3,     0,  -169,    26,     0,   212,   213,     0,     0,
      28,     0,    29,    30,     0,     0,    31,     0,     0,     0,
       0,     0,     0,     0,     4,   141,   142,   143,   144,   145,
     146,     0,   147,   148,   149,   150,   151,   152,     0,     5,
       6,     0,     0,     7,     8,     0,     9,     0,    10,    11,
      12,    13,    14,     0,    15,     0,     0,    16,     0,     0,
      17,    18,    19,    20,     0,    21,     0,    22,    23,     2,
       3,     0,  -169,    26,     0,     0,     0,     0,     0,    28,
       0,    29,    30,     0,     0,    31,     0,     0,     0,     0,
       0,     0,     0,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     6,
       0,     0,     7,     8,     0,     9,     0,    10,    11,    12,
      13,    14,     0,    15,     0,     0,    16,     0,     0,    17,
      18,    19,    20,     0,    21,     0,    22,    23,     2,     3,
       0,     0,    26,     0,     0,     0,     0,     0,    28,     0,
      29,    30,     2,     3,    31,     0,     0,     0,     0,     0,
       0,     0,     4,     0,     2,     3,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     4,     5,     6,     0,
       0,     7,     8,     0,     9,     0,    10,    11,     4,     0,
       0,     5,     6,     0,     0,     7,     8,     0,     9,     0,
      10,    11,     0,     5,     6,     0,     0,     7,     8,     0,
       9,     0,    10,    11,     0,     0,     0,    28,     0,    29,
      68,     0,     0,    69,     0,     0,     0,     0,     0,     0,
       0,    28,     0,    29,    30,     0,     0,    31,     0,     0,
       0,     0,     0,   175,  -107,    29,    30,     0,     0,    69,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,  -107,  -107,   141,   142,   143,   144,   145,   146,
       0,   147,   148,   149,   150,   151,   152
};

static const yytype_int16 yycheck[] =
{
       0,    13,    14,    15,    16,     0,   108,    76,    20,    21,
      29,   201,     4,     5,     6,     3,    30,    38,    52,    52,
      74,     1,    51,    80,    81,    82,    26,    51,    81,     0,
      84,    42,    43,    44,    45,    50,    89,    29,    71,    23,
      24,    75,     0,     1,    80,    81,    30,    31,    32,    33,
      34,    35,    44,    45,    81,    82,    48,    49,    87,    51,
      87,    53,    54,    81,    88,    65,     4,    76,    81,    84,
      88,    51,    77,    84,    85,    86,    53,    54,    91,    28,
      29,    30,    51,    83,    84,    74,    80,    81,    82,   191,
      84,   193,    84,    81,    86,    87,    75,   118,    90,    91,
      91,     2,     3,     4,     5,     6,   175,   297,   108,   109,
     124,    91,   126,    79,   109,    81,   116,    75,    76,    68,
      81,   116,    46,    47,    82,    80,    81,    82,    77,    89,
      79,    80,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,    60,    61,   173,    23,    24,    63,
      64,   178,    89,    80,    23,    24,   168,   184,    27,    28,
     187,    30,    31,    32,    33,    34,    35,    88,    88,   169,
      88,    80,     3,    81,     3,   124,     3,   126,    52,    91,
      58,   200,    81,   183,    63,    69,   205,    91,   188,   189,
      52,   191,    52,   193,   296,   195,    91,   183,    52,    52,
     195,    52,   188,   189,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,    52,
      23,    84,   316,   173,   169,   266,   175,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     324,   268,    34,    87,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   200,   201,    -1,    -1,    -1,   205,    -1,    -1,     7,
       8,    -1,    -1,    -1,    -1,    -1,   266,   267,   280,   281,
     270,    -1,   221,   273,    -1,    -1,    -1,    -1,   278,    -1,
      -1,   308,    -1,    -1,   270,   312,   313,   273,    36,    37,
      38,    39,   278,    -1,    -1,    -1,   296,    -1,    46,    47,
      -1,    -1,   314,    -1,    -1,   305,   318,   334,   320,    -1,
      -1,    -1,   339,   340,    -1,    -1,   343,    -1,   345,   305,
      -1,   348,    -1,   272,   336,    -1,    -1,   354,    -1,   329,
      23,    24,    25,   333,    27,    28,    -1,    30,    31,    32,
      33,    34,    35,   329,    -1,    -1,    -1,   333,   297,   349,
     350,   351,     1,   353,    -1,   355,     5,     6,   307,    -1,
     360,   310,    -1,   349,   350,   351,    -1,   353,    -1,   355,
      -1,    -1,   321,    -1,   360,    -1,    -1,    23,    24,    -1,
      29,    27,    -1,   332,    30,    31,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    44,    45,    -1,   347,    48,
      49,    -1,    51,    -1,    53,    54,    55,    56,    57,    -1,
      59,    -1,    -1,    62,    -1,    -1,    65,    66,    67,    68,
      -1,    70,    -1,    72,    73,    -1,    75,    76,    77,    78,
       4,     5,     6,    82,    -1,    84,    -1,    86,    87,    -1,
      -1,    90,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,
      44,    45,    -1,    -1,    48,    49,    -1,    51,    -1,    53,
      54,    -1,    44,    45,    -1,    -1,    48,    49,    -1,    51,
      -1,    53,    54,    -1,     4,     5,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    81,    -1,    -1,
      84,    -1,    86,    87,    88,    -1,    90,    -1,    80,    29,
      -1,    -1,    84,    -1,    86,    87,    -1,    89,    90,    -1,
      -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    48,    49,
      -1,    51,     3,    53,    54,     4,     5,     6,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,     5,     6,     7,     8,
      29,    -1,     5,     6,    84,    -1,    86,    87,    -1,    89,
      90,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    48,
      49,    -1,    51,    -1,    53,    54,    29,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    46,    47,    -1,
      -1,    44,    45,    -1,    -1,    48,    49,    -1,    51,    -1,
      53,    54,    55,    56,    57,    84,    59,    86,    87,    62,
      -1,    90,    65,    66,    67,    68,    -1,    70,    -1,    72,
      73,     5,     6,    -1,    77,    78,    -1,    80,    81,    82,
      -1,    84,    -1,    86,    87,    -1,    -1,    90,    -1,    -1,
       3,    -1,    -1,    -1,    -1,    29,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      44,    45,    -1,    -1,    48,    49,    -1,    51,    -1,    53,
      54,    55,    56,    57,    -1,    59,    -1,    -1,    62,    -1,
      -1,    65,    66,    67,    68,    -1,    70,    -1,    72,    73,
       5,     6,    -1,    77,    78,    -1,    80,    81,    -1,    -1,
      84,    -1,    86,    87,    -1,    -1,    90,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    23,    24,    25,    26,    27,
      28,    -1,    30,    31,    32,    33,    34,    35,    -1,    44,
      45,    -1,    -1,    48,    49,    -1,    51,    -1,    53,    54,
      55,    56,    57,    -1,    59,    -1,    -1,    62,    -1,    -1,
      65,    66,    67,    68,    -1,    70,    -1,    72,    73,     5,
       6,    -1,    77,    78,    -1,    -1,    -1,    -1,    -1,    84,
      -1,    86,    87,    -1,    -1,    90,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,
      -1,    -1,    48,    49,    -1,    51,    -1,    53,    54,    55,
      56,    57,    -1,    59,    -1,    -1,    62,    -1,    -1,    65,
      66,    67,    68,    -1,    70,    -1,    72,    73,     5,     6,
      -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,    84,    -1,
      86,    87,     5,     6,    90,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    -1,     5,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    44,    45,    -1,
      -1,    48,    49,    -1,    51,    -1,    53,    54,    29,    -1,
      -1,    44,    45,    -1,    -1,    48,    49,    -1,    51,    -1,
      53,    54,    -1,    44,    45,    -1,    -1,    48,    49,    -1,
      51,    -1,    53,    54,    -1,    -1,    -1,    84,    -1,    86,
      87,    -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    -1,    86,    87,    -1,    -1,    90,    -1,    -1,
      -1,    -1,    -1,    84,     3,    86,    87,    -1,    -1,    90,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      -1,    30,    31,    32,    33,    34,    35
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     5,     6,    29,    44,    45,    48,    49,    51,
      53,    54,    55,    56,    57,    59,    62,    65,    66,    67,
      68,    70,    72,    73,    75,    76,    78,    82,    84,    86,
      87,    90,    93,    94,    95,    96,   100,   101,   103,   104,
     105,   106,   109,   113,   114,   115,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   130,   134,   135,   140,
     145,   146,   147,   148,   156,   157,   158,   164,    87,    90,
     103,   120,   120,   120,   120,   120,   163,   163,   163,   163,
     163,   163,   163,   129,   129,    97,    98,    99,   100,   127,
       4,    80,    89,   110,   111,   112,   116,   117,   127,    80,
      81,    88,   107,   108,   112,   117,    74,    84,   149,   151,
       0,    75,    82,   164,    80,    81,   165,   166,   102,   104,
      42,    43,    44,    45,    84,    85,    86,   118,     5,     6,
       7,     8,    36,    37,    38,    39,    40,    41,    46,    47,
       4,    23,    24,    25,    26,    27,    28,    30,    31,    32,
      33,    34,    35,     3,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    77,    87,
     103,   154,   155,   159,   160,    84,   124,   125,   127,    80,
      81,    82,   167,   168,   127,   136,   137,   127,   168,   168,
     103,   131,   133,   131,    75,   167,   168,    91,    89,    89,
      80,    81,    88,    88,    88,    80,    79,     1,   133,   152,
     153,   100,    80,    81,   100,   104,    91,   117,    89,   117,
      50,    84,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   163,    88,   103,   155,     3,    81,   151,   161,
     168,   125,     3,   168,    80,    81,    82,    97,   168,    52,
      60,    61,   138,   139,   168,    97,    97,     3,   133,   100,
     112,   116,   127,   112,    91,   150,    81,    81,    91,    89,
     127,    88,   103,   160,   103,   168,    97,     3,   127,    97,
      58,    97,   163,   163,    63,   141,   142,   143,    69,    52,
      71,   132,   133,    91,    97,    52,    75,   162,   127,   168,
      52,   127,   168,   168,   163,    52,    64,   143,   144,   163,
     163,   127,   162,    91,    97,   127,    97,   168,   163,   168,
     168,   168,    52,   168,   127,   168,    97,    97,    97,    97,
     168,    97,    52,    52,    52,    97
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 492 "parse.y"
    {
		    global_command = (yyvsp[(1) - (1)].tree_statement_list_type);
		    promptflag = 1;
		    YYACCEPT;
		  }
    break;

  case 3:
#line 498 "parse.y"
    { ABORT_PARSE; }
    break;

  case 4:
#line 500 "parse.y"
    { ABORT_PARSE; }
    break;

  case 5:
#line 504 "parse.y"
    { (yyval.tree_statement_list_type) = 0; }
    break;

  case 6:
#line 506 "parse.y"
    {
		    parser_end_of_input = 1;
		    (yyval.tree_statement_list_type) = 0;
		  }
    break;

  case 7:
#line 511 "parse.y"
    { (yyval.tree_statement_list_type) = (yyvsp[(1) - (1)].tree_statement_list_type); }
    break;

  case 8:
#line 513 "parse.y"
    { (yyval.tree_statement_list_type) = (yyvsp[(1) - (2)].tree_statement_list_type); }
    break;

  case 9:
#line 515 "parse.y"
    { (yyval.tree_statement_list_type) = (yyvsp[(1) - (2)].tree_statement_list_type); }
    break;

  case 10:
#line 519 "parse.y"
    { (yyval.tree_statement_list_type) = set_stmt_print_flag ((yyvsp[(1) - (2)].tree_statement_list_type), (yyvsp[(2) - (2)].sep_type), false); }
    break;

  case 11:
#line 523 "parse.y"
    { (yyval.tree_statement_list_type) = make_statement_list ((yyvsp[(1) - (1)].tree_statement_type)); }
    break;

  case 12:
#line 525 "parse.y"
    { (yyval.tree_statement_list_type) = append_statement_list ((yyvsp[(1) - (3)].tree_statement_list_type), (yyvsp[(2) - (3)].sep_type), (yyvsp[(3) - (3)].tree_statement_type), false); }
    break;

  case 13:
#line 529 "parse.y"
    { (yyval.tree_statement_list_type) = new tree_statement_list (); }
    break;

  case 14:
#line 531 "parse.y"
    { (yyval.tree_statement_list_type) = (yyvsp[(1) - (1)].tree_statement_list_type); }
    break;

  case 15:
#line 535 "parse.y"
    { (yyval.tree_statement_list_type) = set_stmt_print_flag ((yyvsp[(1) - (2)].tree_statement_list_type), (yyvsp[(2) - (2)].sep_type), true); }
    break;

  case 16:
#line 539 "parse.y"
    { (yyval.tree_statement_list_type) = make_statement_list ((yyvsp[(1) - (1)].tree_statement_type)); }
    break;

  case 17:
#line 541 "parse.y"
    { (yyval.tree_statement_list_type) = append_statement_list ((yyvsp[(1) - (3)].tree_statement_list_type), (yyvsp[(2) - (3)].sep_type), (yyvsp[(3) - (3)].tree_statement_type), true); }
    break;

  case 18:
#line 545 "parse.y"
    { (yyval.tree_statement_type) = make_statement ((yyvsp[(1) - (1)].tree_expression_type)); }
    break;

  case 19:
#line 547 "parse.y"
    { (yyval.tree_statement_type) = make_statement ((yyvsp[(1) - (1)].tree_command_type)); }
    break;

  case 20:
#line 549 "parse.y"
    { (yyval.tree_statement_type) = make_statement ((yyvsp[(1) - (1)].tree_index_expression_type)); }
    break;

  case 21:
#line 561 "parse.y"
    { (yyval.tree_index_expression_type) = make_index_expression ((yyvsp[(1) - (2)].tree_identifier_type), (yyvsp[(2) - (2)].tree_argument_list_type), '('); }
    break;

  case 22:
#line 565 "parse.y"
    { (yyval.tree_argument_list_type) = new tree_argument_list ((yyvsp[(1) - (1)].tree_constant_type)); }
    break;

  case 23:
#line 567 "parse.y"
    {
		    (yyvsp[(1) - (2)].tree_argument_list_type)->append ((yyvsp[(2) - (2)].tree_constant_type));
		    (yyval.tree_argument_list_type) = (yyvsp[(1) - (2)].tree_argument_list_type);
		  }
    break;

  case 24:
#line 578 "parse.y"
    {
		    symbol_table::symbol_record *sr = (yyvsp[(1) - (1)].tok_val)->sym_rec ();
		    (yyval.tree_identifier_type) = new tree_identifier (*sr, (yyvsp[(1) - (1)].tok_val)->line (), (yyvsp[(1) - (1)].tok_val)->column ());
		  }
    break;

  case 25:
#line 585 "parse.y"
    { (yyval.tree_constant_type) = make_constant (DQ_STRING, (yyvsp[(1) - (1)].tok_val)); }
    break;

  case 26:
#line 587 "parse.y"
    { (yyval.tree_constant_type) = make_constant (SQ_STRING, (yyvsp[(1) - (1)].tok_val)); }
    break;

  case 27:
#line 591 "parse.y"
    { (yyval.tree_constant_type) = make_constant (NUM, (yyvsp[(1) - (1)].tok_val)); }
    break;

  case 28:
#line 593 "parse.y"
    { (yyval.tree_constant_type) = make_constant (IMAG_NUM, (yyvsp[(1) - (1)].tok_val)); }
    break;

  case 29:
#line 595 "parse.y"
    { (yyval.tree_constant_type) = (yyvsp[(1) - (1)].tree_constant_type); }
    break;

  case 30:
#line 599 "parse.y"
    {
		    (yyval.tree_expression_type) = new tree_constant (octave_null_matrix::instance);
		    lexer_flags.looking_at_matrix_or_assign_lhs = false;
		    lexer_flags.pending_local_variables.clear ();
		  }
    break;

  case 31:
#line 605 "parse.y"
    {
		    (yyval.tree_expression_type) = new tree_constant (octave_null_matrix::instance);
		    lexer_flags.looking_at_matrix_or_assign_lhs = false;
		    lexer_flags.pending_local_variables.clear ();
		  }
    break;

  case 32:
#line 611 "parse.y"
    {
		    (yyval.tree_expression_type) = new tree_constant (octave_null_matrix::instance);
		    lexer_flags.looking_at_matrix_or_assign_lhs = false;
		    lexer_flags.pending_local_variables.clear ();
		  }
    break;

  case 33:
#line 617 "parse.y"
    {
		    (yyval.tree_expression_type) = finish_matrix ((yyvsp[(2) - (3)].tree_matrix_type));
		    lexer_flags.looking_at_matrix_or_assign_lhs = false;
		    lexer_flags.pending_local_variables.clear ();
		  }
    break;

  case 34:
#line 625 "parse.y"
    { (yyval.tree_matrix_type) = (yyvsp[(1) - (1)].tree_matrix_type); }
    break;

  case 35:
#line 627 "parse.y"
    { (yyval.tree_matrix_type) = (yyvsp[(1) - (2)].tree_matrix_type); }
    break;

  case 36:
#line 631 "parse.y"
    { (yyval.tree_matrix_type) = new tree_matrix ((yyvsp[(1) - (1)].tree_argument_list_type)); }
    break;

  case 37:
#line 633 "parse.y"
    {
		    (yyvsp[(1) - (3)].tree_matrix_type)->append ((yyvsp[(3) - (3)].tree_argument_list_type));
		    (yyval.tree_matrix_type) = (yyvsp[(1) - (3)].tree_matrix_type);
		  }
    break;

  case 38:
#line 640 "parse.y"
    { (yyval.tree_expression_type) = new tree_constant (octave_value (Cell ())); }
    break;

  case 39:
#line 642 "parse.y"
    { (yyval.tree_expression_type) = new tree_constant (octave_value (Cell ())); }
    break;

  case 40:
#line 644 "parse.y"
    { (yyval.tree_expression_type) = finish_cell ((yyvsp[(2) - (3)].tree_cell_type)); }
    break;

  case 41:
#line 648 "parse.y"
    { (yyval.tree_cell_type) = (yyvsp[(1) - (1)].tree_cell_type); }
    break;

  case 42:
#line 650 "parse.y"
    { (yyval.tree_cell_type) = (yyvsp[(1) - (2)].tree_cell_type); }
    break;

  case 43:
#line 654 "parse.y"
    { (yyval.tree_cell_type) = new tree_cell ((yyvsp[(1) - (1)].tree_argument_list_type)); }
    break;

  case 44:
#line 656 "parse.y"
    {
		    (yyvsp[(1) - (3)].tree_cell_type)->append ((yyvsp[(3) - (3)].tree_argument_list_type));
		    (yyval.tree_cell_type) = (yyvsp[(1) - (3)].tree_cell_type);
		  }
    break;

  case 45:
#line 664 "parse.y"
    { (yyval.tree_argument_list_type) = (yyvsp[(1) - (1)].tree_argument_list_type); }
    break;

  case 46:
#line 666 "parse.y"
    { (yyval.tree_argument_list_type) = (yyvsp[(1) - (2)].tree_argument_list_type); }
    break;

  case 47:
#line 670 "parse.y"
    {
		    (yyval.tree_fcn_handle_type) = make_fcn_handle ((yyvsp[(2) - (2)].tok_val));
		    lexer_flags.looking_at_function_handle--;
		  }
    break;

  case 48:
#line 677 "parse.y"
    { (yyval.tree_anon_fcn_handle_type) = make_anon_fcn_handle ((yyvsp[(2) - (3)].tree_parameter_list_type), (yyvsp[(3) - (3)].tree_statement_type)); }
    break;

  case 49:
#line 681 "parse.y"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_identifier_type); }
    break;

  case 50:
#line 683 "parse.y"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_constant_type); }
    break;

  case 51:
#line 685 "parse.y"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_fcn_handle_type); }
    break;

  case 52:
#line 687 "parse.y"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_expression_type); }
    break;

  case 53:
#line 689 "parse.y"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_expression_type); }
    break;

  case 54:
#line 691 "parse.y"
    { (yyval.tree_expression_type) = (yyvsp[(2) - (3)].tree_expression_type)->mark_in_parens (); }
    break;

  case 55:
#line 695 "parse.y"
    {
		    octave_value tmp (octave_value::magic_colon_t);
		    (yyval.tree_constant_type) = new tree_constant (tmp);
		  }
    break;

  case 56:
#line 702 "parse.y"
    { (yyval.tree_argument_list_type) = new tree_argument_list ((yyvsp[(1) - (1)].tree_expression_type)); }
    break;

  case 57:
#line 704 "parse.y"
    { (yyval.tree_argument_list_type) = new tree_argument_list ((yyvsp[(1) - (1)].tree_constant_type)); }
    break;

  case 58:
#line 706 "parse.y"
    {
		    (yyvsp[(1) - (3)].tree_argument_list_type)->append ((yyvsp[(3) - (3)].tree_constant_type));
		    (yyval.tree_argument_list_type) = (yyvsp[(1) - (3)].tree_argument_list_type);
		  }
    break;

  case 59:
#line 711 "parse.y"
    {
		    (yyvsp[(1) - (3)].tree_argument_list_type)->append ((yyvsp[(3) - (3)].tree_expression_type));
		    (yyval.tree_argument_list_type) = (yyvsp[(1) - (3)].tree_argument_list_type);
		  }
    break;

  case 60:
#line 718 "parse.y"
    { lexer_flags.looking_at_indirect_ref = true; }
    break;

  case 61:
#line 722 "parse.y"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_expression_type); }
    break;

  case 62:
#line 724 "parse.y"
    { (yyval.tree_expression_type) = make_index_expression ((yyvsp[(1) - (3)].tree_expression_type), 0, '('); }
    break;

  case 63:
#line 726 "parse.y"
    { (yyval.tree_expression_type) = make_index_expression ((yyvsp[(1) - (4)].tree_expression_type), (yyvsp[(3) - (4)].tree_argument_list_type), '('); }
    break;

  case 64:
#line 728 "parse.y"
    { (yyval.tree_expression_type) = make_index_expression ((yyvsp[(1) - (3)].tree_expression_type), 0, '{'); }
    break;

  case 65:
#line 730 "parse.y"
    { (yyval.tree_expression_type) = make_index_expression ((yyvsp[(1) - (4)].tree_expression_type), (yyvsp[(3) - (4)].tree_argument_list_type), '{'); }
    break;

  case 66:
#line 732 "parse.y"
    { (yyval.tree_expression_type) = make_postfix_op (PLUS_PLUS, (yyvsp[(1) - (2)].tree_expression_type), (yyvsp[(2) - (2)].tok_val)); }
    break;

  case 67:
#line 734 "parse.y"
    { (yyval.tree_expression_type) = make_postfix_op (MINUS_MINUS, (yyvsp[(1) - (2)].tree_expression_type), (yyvsp[(2) - (2)].tok_val)); }
    break;

  case 68:
#line 736 "parse.y"
    { (yyval.tree_expression_type) = make_postfix_op (QUOTE, (yyvsp[(1) - (2)].tree_expression_type), (yyvsp[(2) - (2)].tok_val)); }
    break;

  case 69:
#line 738 "parse.y"
    { (yyval.tree_expression_type) = make_postfix_op (TRANSPOSE, (yyvsp[(1) - (2)].tree_expression_type), (yyvsp[(2) - (2)].tok_val)); }
    break;

  case 70:
#line 740 "parse.y"
    { (yyval.tree_expression_type) = make_indirect_ref ((yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(3) - (3)].tok_val)->text ()); }
    break;

  case 71:
#line 742 "parse.y"
    { (yyval.tree_expression_type) = make_indirect_ref ((yyvsp[(1) - (5)].tree_expression_type), (yyvsp[(4) - (5)].tree_expression_type)); }
    break;

  case 72:
#line 746 "parse.y"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_expression_type); }
    break;

  case 73:
#line 748 "parse.y"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_expression_type); }
    break;

  case 74:
#line 750 "parse.y"
    { (yyval.tree_expression_type) = make_prefix_op (PLUS_PLUS, (yyvsp[(2) - (2)].tree_expression_type), (yyvsp[(1) - (2)].tok_val)); }
    break;

  case 75:
#line 752 "parse.y"
    { (yyval.tree_expression_type) = make_prefix_op (MINUS_MINUS, (yyvsp[(2) - (2)].tree_expression_type), (yyvsp[(1) - (2)].tok_val)); }
    break;

  case 76:
#line 754 "parse.y"
    { (yyval.tree_expression_type) = make_prefix_op (EXPR_NOT, (yyvsp[(2) - (2)].tree_expression_type), (yyvsp[(1) - (2)].tok_val)); }
    break;

  case 77:
#line 756 "parse.y"
    { (yyval.tree_expression_type) = make_prefix_op ('+', (yyvsp[(2) - (2)].tree_expression_type), (yyvsp[(1) - (2)].tok_val)); }
    break;

  case 78:
#line 758 "parse.y"
    { (yyval.tree_expression_type) = make_prefix_op ('-', (yyvsp[(2) - (2)].tree_expression_type), (yyvsp[(1) - (2)].tok_val)); }
    break;

  case 79:
#line 762 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op (POW, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 80:
#line 764 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op (EPOW, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 81:
#line 766 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op ('+', (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 82:
#line 768 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op ('-', (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 83:
#line 770 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op ('*', (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 84:
#line 772 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op ('/', (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 85:
#line 774 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op ('+', (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 86:
#line 776 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op ('-', (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 87:
#line 778 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op (EMUL, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 88:
#line 780 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op (EDIV, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 89:
#line 782 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op (LEFTDIV, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 90:
#line 784 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op (ELEFTDIV, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 91:
#line 788 "parse.y"
    { (yyval.tree_expression_type) = finish_colon_expression ((yyvsp[(1) - (1)].tree_colon_expression_type)); }
    break;

  case 92:
#line 792 "parse.y"
    { (yyval.tree_colon_expression_type) = new tree_colon_expression ((yyvsp[(1) - (1)].tree_expression_type)); }
    break;

  case 93:
#line 794 "parse.y"
    {
		    if (! ((yyval.tree_colon_expression_type) = (yyvsp[(1) - (3)].tree_colon_expression_type)->append ((yyvsp[(3) - (3)].tree_expression_type))))
		      ABORT_PARSE;
		  }
    break;

  case 94:
#line 801 "parse.y"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_expression_type); }
    break;

  case 95:
#line 803 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op (LSHIFT, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 96:
#line 805 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op (RSHIFT, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 97:
#line 807 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op (EXPR_LT, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 98:
#line 809 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op (EXPR_LE, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 99:
#line 811 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op (EXPR_EQ, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 100:
#line 813 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op (EXPR_GE, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 101:
#line 815 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op (EXPR_GT, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 102:
#line 817 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op (EXPR_NE, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 103:
#line 819 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op (EXPR_AND, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 104:
#line 821 "parse.y"
    { (yyval.tree_expression_type) = make_binary_op (EXPR_OR, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 105:
#line 823 "parse.y"
    { (yyval.tree_expression_type) = make_boolean_op (EXPR_AND_AND, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 106:
#line 825 "parse.y"
    { (yyval.tree_expression_type) = make_boolean_op (EXPR_OR_OR, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 107:
#line 832 "parse.y"
    {
		    (yyval.tree_argument_list_type) = new tree_argument_list ((yyvsp[(1) - (1)].tree_expression_type));
		    (yyval.tree_argument_list_type)->mark_as_simple_assign_lhs ();
		  }
    break;

  case 108:
#line 837 "parse.y"
    {
		    (yyval.tree_argument_list_type) = (yyvsp[(2) - (3)].tree_argument_list_type);
		    lexer_flags.looking_at_matrix_or_assign_lhs = false;
		    for (std::set<std::string>::const_iterator p = lexer_flags.pending_local_variables.begin ();
			 p != lexer_flags.pending_local_variables.end ();
			 p++)
		      {
			symbol_table::force_variable (*p);
		      }
		    lexer_flags.pending_local_variables.clear ();
		  }
    break;

  case 109:
#line 851 "parse.y"
    { (yyval.tree_expression_type) = make_assign_op ('=', (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 110:
#line 853 "parse.y"
    { (yyval.tree_expression_type) = make_assign_op (ADD_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 111:
#line 855 "parse.y"
    { (yyval.tree_expression_type) = make_assign_op (SUB_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 112:
#line 857 "parse.y"
    { (yyval.tree_expression_type) = make_assign_op (MUL_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 113:
#line 859 "parse.y"
    { (yyval.tree_expression_type) = make_assign_op (DIV_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 114:
#line 861 "parse.y"
    { (yyval.tree_expression_type) = make_assign_op (LEFTDIV_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 115:
#line 863 "parse.y"
    { (yyval.tree_expression_type) = make_assign_op (POW_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 116:
#line 865 "parse.y"
    { (yyval.tree_expression_type) = make_assign_op (LSHIFT_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 117:
#line 867 "parse.y"
    { (yyval.tree_expression_type) = make_assign_op (RSHIFT_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 118:
#line 869 "parse.y"
    { (yyval.tree_expression_type) = make_assign_op (EMUL_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 119:
#line 871 "parse.y"
    { (yyval.tree_expression_type) = make_assign_op (EDIV_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 120:
#line 873 "parse.y"
    { (yyval.tree_expression_type) = make_assign_op (ELEFTDIV_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 121:
#line 875 "parse.y"
    { (yyval.tree_expression_type) = make_assign_op (EPOW_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 122:
#line 877 "parse.y"
    { (yyval.tree_expression_type) = make_assign_op (AND_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 123:
#line 879 "parse.y"
    { (yyval.tree_expression_type) = make_assign_op (OR_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 124:
#line 883 "parse.y"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_expression_type); }
    break;

  case 125:
#line 885 "parse.y"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_expression_type); }
    break;

  case 126:
#line 887 "parse.y"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_anon_fcn_handle_type); }
    break;

  case 127:
#line 895 "parse.y"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_decl_command_type); }
    break;

  case 128:
#line 897 "parse.y"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_command_type); }
    break;

  case 129:
#line 899 "parse.y"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_command_type); }
    break;

  case 130:
#line 901 "parse.y"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_command_type); }
    break;

  case 131:
#line 903 "parse.y"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_command_type); }
    break;

  case 132:
#line 905 "parse.y"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_command_type); }
    break;

  case 133:
#line 907 "parse.y"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_command_type); }
    break;

  case 134:
#line 916 "parse.y"
    { lexer_flags.looking_at_decl_list = true; }
    break;

  case 135:
#line 919 "parse.y"
    {
		    (yyval.tree_decl_command_type) = make_decl_command (GLOBAL, (yyvsp[(1) - (3)].tok_val), (yyvsp[(3) - (3)].tree_decl_init_list_type));
		    lexer_flags.looking_at_decl_list = false;
		  }
    break;

  case 136:
#line 924 "parse.y"
    {
		    (yyval.tree_decl_command_type) = make_decl_command (STATIC, (yyvsp[(1) - (3)].tok_val), (yyvsp[(3) - (3)].tree_decl_init_list_type));
		    lexer_flags.looking_at_decl_list = false;
		  }
    break;

  case 137:
#line 931 "parse.y"
    { (yyval.tree_decl_init_list_type) = new tree_decl_init_list ((yyvsp[(1) - (1)].tree_decl_elt_type)); }
    break;

  case 138:
#line 933 "parse.y"
    {
		    (yyvsp[(1) - (2)].tree_decl_init_list_type)->append ((yyvsp[(2) - (2)].tree_decl_elt_type));
		    (yyval.tree_decl_init_list_type) = (yyvsp[(1) - (2)].tree_decl_init_list_type);
		  }
    break;

  case 139:
#line 940 "parse.y"
    { lexer_flags.looking_at_initializer_expression = true; }
    break;

  case 140:
#line 943 "parse.y"
    { (yyval.tree_decl_elt_type) = new tree_decl_elt ((yyvsp[(1) - (1)].tree_identifier_type)); }
    break;

  case 141:
#line 945 "parse.y"
    {
		    lexer_flags.looking_at_initializer_expression = false;
		    (yyval.tree_decl_elt_type) = new tree_decl_elt ((yyvsp[(1) - (4)].tree_identifier_type), (yyvsp[(4) - (4)].tree_expression_type));
		  }
    break;

  case 142:
#line 956 "parse.y"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_if_command_type); }
    break;

  case 143:
#line 958 "parse.y"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_switch_command_type); }
    break;

  case 144:
#line 966 "parse.y"
    {
		    if (! ((yyval.tree_if_command_type) = finish_if_command ((yyvsp[(1) - (4)].tok_val), (yyvsp[(3) - (4)].tree_if_command_list_type), (yyvsp[(4) - (4)].tok_val), (yyvsp[(2) - (4)].comment_type))))
		      ABORT_PARSE;
		  }
    break;

  case 145:
#line 973 "parse.y"
    { (yyval.tree_if_command_list_type) = (yyvsp[(1) - (1)].tree_if_command_list_type); }
    break;

  case 146:
#line 975 "parse.y"
    {
		    (yyvsp[(1) - (2)].tree_if_command_list_type)->append ((yyvsp[(2) - (2)].tree_if_clause_type));
		    (yyval.tree_if_command_list_type) = (yyvsp[(1) - (2)].tree_if_command_list_type);
		  }
    break;

  case 147:
#line 982 "parse.y"
    { (yyval.tree_if_command_list_type) = start_if_command ((yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(3) - (3)].tree_statement_list_type)); }
    break;

  case 148:
#line 984 "parse.y"
    {
		    (yyvsp[(1) - (2)].tree_if_command_list_type)->append ((yyvsp[(2) - (2)].tree_if_clause_type));
		    (yyval.tree_if_command_list_type) = (yyvsp[(1) - (2)].tree_if_command_list_type);
		  }
    break;

  case 149:
#line 991 "parse.y"
    { (yyval.tree_if_clause_type) = make_elseif_clause ((yyvsp[(1) - (6)].tok_val), (yyvsp[(4) - (6)].tree_expression_type), (yyvsp[(6) - (6)].tree_statement_list_type), (yyvsp[(2) - (6)].comment_type)); }
    break;

  case 150:
#line 995 "parse.y"
    { (yyval.tree_if_clause_type) = new tree_if_clause ((yyvsp[(4) - (4)].tree_statement_list_type), (yyvsp[(2) - (4)].comment_type)); }
    break;

  case 151:
#line 1003 "parse.y"
    {
		    if (! ((yyval.tree_switch_command_type) = finish_switch_command ((yyvsp[(1) - (6)].tok_val), (yyvsp[(3) - (6)].tree_expression_type), (yyvsp[(5) - (6)].tree_switch_case_list_type), (yyvsp[(6) - (6)].tok_val), (yyvsp[(2) - (6)].comment_type))))
		      ABORT_PARSE;
		  }
    break;

  case 152:
#line 1010 "parse.y"
    { (yyval.tree_switch_case_list_type) = new tree_switch_case_list (); }
    break;

  case 153:
#line 1012 "parse.y"
    { (yyval.tree_switch_case_list_type) = (yyvsp[(1) - (1)].tree_switch_case_list_type); }
    break;

  case 154:
#line 1014 "parse.y"
    {
		    (yyvsp[(1) - (2)].tree_switch_case_list_type)->append ((yyvsp[(2) - (2)].tree_switch_case_type));
		    (yyval.tree_switch_case_list_type) = (yyvsp[(1) - (2)].tree_switch_case_list_type);
		  }
    break;

  case 155:
#line 1021 "parse.y"
    { (yyval.tree_switch_case_list_type) = new tree_switch_case_list ((yyvsp[(1) - (1)].tree_switch_case_type)); }
    break;

  case 156:
#line 1023 "parse.y"
    {
		    (yyvsp[(1) - (2)].tree_switch_case_list_type)->append ((yyvsp[(2) - (2)].tree_switch_case_type));
		    (yyval.tree_switch_case_list_type) = (yyvsp[(1) - (2)].tree_switch_case_list_type);
		  }
    break;

  case 157:
#line 1030 "parse.y"
    { (yyval.tree_switch_case_type) = make_switch_case ((yyvsp[(1) - (6)].tok_val), (yyvsp[(4) - (6)].tree_expression_type), (yyvsp[(6) - (6)].tree_statement_list_type), (yyvsp[(2) - (6)].comment_type)); }
    break;

  case 158:
#line 1034 "parse.y"
    {
		    (yyval.tree_switch_case_type) = new tree_switch_case ((yyvsp[(4) - (4)].tree_statement_list_type), (yyvsp[(2) - (4)].comment_type));
		  }
    break;

  case 159:
#line 1044 "parse.y"
    {
		    if (! ((yyval.tree_command_type) = make_while_command ((yyvsp[(1) - (6)].tok_val), (yyvsp[(3) - (6)].tree_expression_type), (yyvsp[(5) - (6)].tree_statement_list_type), (yyvsp[(6) - (6)].tok_val), (yyvsp[(2) - (6)].comment_type))))
		      ABORT_PARSE;
		  }
    break;

  case 160:
#line 1049 "parse.y"
    {
		    if (! ((yyval.tree_command_type) = make_do_until_command ((yyvsp[(5) - (6)].tok_val), (yyvsp[(4) - (6)].tree_statement_list_type), (yyvsp[(6) - (6)].tree_expression_type), (yyvsp[(2) - (6)].comment_type))))
		      ABORT_PARSE;
		  }
    break;

  case 161:
#line 1054 "parse.y"
    {
		    if (! ((yyval.tree_command_type) = make_for_command ((yyvsp[(1) - (8)].tok_val), (yyvsp[(3) - (8)].tree_argument_list_type), (yyvsp[(5) - (8)].tree_expression_type), (yyvsp[(7) - (8)].tree_statement_list_type), (yyvsp[(8) - (8)].tok_val), (yyvsp[(2) - (8)].comment_type))))
		      ABORT_PARSE;
		  }
    break;

  case 162:
#line 1059 "parse.y"
    {
		    if (! ((yyval.tree_command_type) = make_for_command ((yyvsp[(1) - (10)].tok_val), (yyvsp[(4) - (10)].tree_argument_list_type), (yyvsp[(6) - (10)].tree_expression_type), (yyvsp[(9) - (10)].tree_statement_list_type), (yyvsp[(10) - (10)].tok_val), (yyvsp[(2) - (10)].comment_type))))
		      ABORT_PARSE;
		  }
    break;

  case 163:
#line 1070 "parse.y"
    {
		    if (! ((yyval.tree_command_type) = make_break_command ((yyvsp[(1) - (1)].tok_val))))
		      ABORT_PARSE;
		  }
    break;

  case 164:
#line 1075 "parse.y"
    {
		    if (! ((yyval.tree_command_type) = make_continue_command ((yyvsp[(1) - (1)].tok_val))))
		      ABORT_PARSE;
		  }
    break;

  case 165:
#line 1080 "parse.y"
    {
		    if (! ((yyval.tree_command_type) = make_return_command ((yyvsp[(1) - (1)].tok_val))))
		      ABORT_PARSE;
		  }
    break;

  case 166:
#line 1092 "parse.y"
    {
		    if (! ((yyval.tree_command_type) = make_unwind_command ((yyvsp[(1) - (9)].tok_val), (yyvsp[(4) - (9)].tree_statement_list_type), (yyvsp[(8) - (9)].tree_statement_list_type), (yyvsp[(9) - (9)].tok_val), (yyvsp[(2) - (9)].comment_type), (yyvsp[(6) - (9)].comment_type))))
		      ABORT_PARSE;
		  }
    break;

  case 167:
#line 1098 "parse.y"
    {
		    if (! ((yyval.tree_command_type) = make_try_command ((yyvsp[(1) - (9)].tok_val), (yyvsp[(4) - (9)].tree_statement_list_type), (yyvsp[(8) - (9)].tree_statement_list_type), (yyvsp[(9) - (9)].tok_val), (yyvsp[(2) - (9)].comment_type), (yyvsp[(6) - (9)].comment_type))))
		      ABORT_PARSE;
		  }
    break;

  case 168:
#line 1103 "parse.y"
    {
		    if (! ((yyval.tree_command_type) = make_try_command ((yyvsp[(1) - (5)].tok_val), (yyvsp[(4) - (5)].tree_statement_list_type), 0, (yyvsp[(5) - (5)].tok_val), (yyvsp[(2) - (5)].comment_type), 0)))
		      ABORT_PARSE;
		  }
    break;

  case 169:
#line 1114 "parse.y"
    {
		    symtab_context.push (symbol_table::current_scope ());
		    symbol_table::set_scope (symbol_table::alloc_scope ());

		    if (! lexer_flags.parsing_nested_function)
		      symbol_table::set_parent_scope (symbol_table::current_scope ());
		  }
    break;

  case 170:
#line 1128 "parse.y"
    {
		    lexer_flags.looking_at_parameter_list = true;

		    if (lexer_flags.looking_at_function_handle)
		      {
		        symtab_context.push (symbol_table::current_scope ());
			symbol_table::set_scope (symbol_table::alloc_scope ());
			lexer_flags.looking_at_function_handle--;
		      }
		  }
    break;

  case 171:
#line 1141 "parse.y"
    {
		    lexer_flags.looking_at_parameter_list = false;
		    lexer_flags.looking_for_object_index = false;
		  }
    break;

  case 172:
#line 1148 "parse.y"
    {
		    lexer_flags.quote_is_transpose = false;
		    (yyval.tree_parameter_list_type) = (yyvsp[(2) - (3)].tree_parameter_list_type);
		  }
    break;

  case 173:
#line 1153 "parse.y"
    {
		    yyerror ("invalid parameter list");
		    (yyval.tree_parameter_list_type) = 0;
		    ABORT_PARSE;
		  }
    break;

  case 174:
#line 1161 "parse.y"
    { (yyval.tree_parameter_list_type) = 0; }
    break;

  case 175:
#line 1163 "parse.y"
    {
		    (yyvsp[(1) - (1)].tree_parameter_list_type)->mark_as_formal_parameters ();
		    if ((yyvsp[(1) - (1)].tree_parameter_list_type)->validate (tree_parameter_list::in))
		      (yyval.tree_parameter_list_type) = (yyvsp[(1) - (1)].tree_parameter_list_type);
		    else
		      ABORT_PARSE;
		  }
    break;

  case 176:
#line 1173 "parse.y"
    { (yyval.tree_parameter_list_type) = new tree_parameter_list ((yyvsp[(1) - (1)].tree_decl_elt_type)); }
    break;

  case 177:
#line 1175 "parse.y"
    {
		    (yyvsp[(1) - (3)].tree_parameter_list_type)->append ((yyvsp[(3) - (3)].tree_decl_elt_type));
		    (yyval.tree_parameter_list_type) = (yyvsp[(1) - (3)].tree_parameter_list_type);
		  }
    break;

  case 178:
#line 1186 "parse.y"
    {
		    lexer_flags.looking_at_return_list = false;
		    (yyval.tree_parameter_list_type) = new tree_parameter_list ();
		  }
    break;

  case 179:
#line 1191 "parse.y"
    {
		    lexer_flags.looking_at_return_list = false;
		    if ((yyvsp[(1) - (1)].tree_parameter_list_type)->validate (tree_parameter_list::out))
		      (yyval.tree_parameter_list_type) = (yyvsp[(1) - (1)].tree_parameter_list_type);
		    else
		      ABORT_PARSE;
		  }
    break;

  case 180:
#line 1199 "parse.y"
    {
		    lexer_flags.looking_at_return_list = false;
		    if ((yyvsp[(2) - (3)].tree_parameter_list_type)->validate (tree_parameter_list::out))
		      (yyval.tree_parameter_list_type) = (yyvsp[(2) - (3)].tree_parameter_list_type);
		    else
		      ABORT_PARSE;
		  }
    break;

  case 181:
#line 1209 "parse.y"
    { (yyval.tree_parameter_list_type) = new tree_parameter_list (new tree_decl_elt ((yyvsp[(1) - (1)].tree_identifier_type))); }
    break;

  case 182:
#line 1211 "parse.y"
    {
		    (yyvsp[(1) - (3)].tree_parameter_list_type)->append (new tree_decl_elt ((yyvsp[(3) - (3)].tree_identifier_type)));
		    (yyval.tree_parameter_list_type) = (yyvsp[(1) - (3)].tree_parameter_list_type);
		  }
    break;

  case 183:
#line 1222 "parse.y"
    {
		    tree_statement *end_of_script
		      = make_end ("endscript", input_line_number,
				  current_input_column);

		    make_script ((yyvsp[(2) - (3)].tree_statement_list_type), end_of_script);

		    (yyval.tree_command_type) = 0;
		  }
    break;

  case 184:
#line 1238 "parse.y"
    { (yyval.comment_type) = (yyvsp[(3) - (3)].comment_type); }
    break;

  case 185:
#line 1242 "parse.y"
    {
		    (yyval.tree_command_type) = finish_function (0, (yyvsp[(2) - (2)].octave_user_function_type), (yyvsp[(1) - (2)].comment_type));
		    recover_from_parsing_function ();
		  }
    break;

  case 186:
#line 1247 "parse.y"
    {
		    (yyval.tree_command_type) = finish_function ((yyvsp[(2) - (4)].tree_parameter_list_type), (yyvsp[(4) - (4)].octave_user_function_type), (yyvsp[(1) - (4)].comment_type));
		    recover_from_parsing_function ();
		  }
    break;

  case 187:
#line 1254 "parse.y"
    {
		    std::string id_name = (yyvsp[(1) - (1)].tree_identifier_type)->name ();

		    if (reading_fcn_file
		        && ! lexer_flags.parsing_nested_function)
		      parent_function_name = (curr_fcn_file_name == id_name)
			? id_name : curr_fcn_file_name;

		    lexer_flags.parsed_function_name = true;

		    (yyval.tree_identifier_type) = (yyvsp[(1) - (1)].tree_identifier_type);
		  }
    break;

  case 188:
#line 1269 "parse.y"
    {
		    std::string fname = (yyvsp[(1) - (2)].tree_identifier_type)->name ();

		    delete (yyvsp[(1) - (2)].tree_identifier_type);

		    if (! ((yyval.octave_user_function_type) = frob_function (fname, (yyvsp[(2) - (2)].octave_user_function_type))))
		      ABORT_PARSE;
		  }
    break;

  case 189:
#line 1280 "parse.y"
    { (yyval.octave_user_function_type) = start_function ((yyvsp[(1) - (4)].tree_parameter_list_type), (yyvsp[(3) - (4)].tree_statement_list_type), (yyvsp[(4) - (4)].tree_statement_type)); }
    break;

  case 190:
#line 1282 "parse.y"
    { (yyval.octave_user_function_type) = start_function (0, (yyvsp[(2) - (3)].tree_statement_list_type), (yyvsp[(3) - (3)].tree_statement_type)); }
    break;

  case 191:
#line 1286 "parse.y"
    {
		    if (end_token_ok ((yyvsp[(1) - (1)].tok_val), token::function_end))
		      (yyval.tree_statement_type) = make_end ("endfunction", (yyvsp[(1) - (1)].tok_val)->line (), (yyvsp[(1) - (1)].tok_val)->column ());
		    else
		      ABORT_PARSE;
		  }
    break;

  case 192:
#line 1293 "parse.y"
    {
		    if (lexer_flags.parsing_nested_function)
		      lexer_flags.parsing_nested_function = -1;

		    if (reading_fcn_file || reading_script_file
			|| get_input_from_eval_string)
		      (yyval.tree_statement_type) = make_end ("endfunction", input_line_number,
				     current_input_column);
		    else
		      YYABORT;
		  }
    break;

  case 193:
#line 1311 "parse.y"
    { (yyval.comment_type) = octave_comment_buffer::get_comment (); }
    break;

  case 194:
#line 1315 "parse.y"
    { yyerror ("parse error"); }
    break;

  case 196:
#line 1320 "parse.y"
    { (yyval.sep_type) = ','; }
    break;

  case 197:
#line 1322 "parse.y"
    { (yyval.sep_type) = ';'; }
    break;

  case 198:
#line 1324 "parse.y"
    { (yyval.sep_type) = (yyvsp[(1) - (2)].sep_type); }
    break;

  case 199:
#line 1326 "parse.y"
    { (yyval.sep_type) = (yyvsp[(1) - (2)].sep_type); }
    break;

  case 200:
#line 1330 "parse.y"
    { (yyval.sep_type) = 0; }
    break;

  case 201:
#line 1332 "parse.y"
    { (yyval.sep_type) = (yyvsp[(1) - (1)].sep_type); }
    break;

  case 202:
#line 1336 "parse.y"
    { (yyval.sep_type) = ','; }
    break;

  case 203:
#line 1338 "parse.y"
    { (yyval.sep_type) = ';'; }
    break;

  case 204:
#line 1340 "parse.y"
    { (yyval.sep_type) = '\n'; }
    break;

  case 205:
#line 1342 "parse.y"
    { (yyval.sep_type) = (yyvsp[(1) - (2)].sep_type); }
    break;

  case 206:
#line 1344 "parse.y"
    { (yyval.sep_type) = (yyvsp[(1) - (2)].sep_type); }
    break;

  case 207:
#line 1346 "parse.y"
    { (yyval.sep_type) = (yyvsp[(1) - (2)].sep_type); }
    break;

  case 208:
#line 1350 "parse.y"
    { (yyval.sep_type) = 0; }
    break;

  case 209:
#line 1352 "parse.y"
    { (yyval.sep_type) = (yyvsp[(1) - (1)].sep_type); }
    break;


/* Line 1267 of yacc.c.  */
#line 3576 "parse.cc"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 1355 "parse.y"


// Generic error messages.

static void
yyerror (const char *s)
{
  int err_col = current_input_column - 1;

  std::ostringstream output_buf;

  if (reading_fcn_file || reading_script_file)
    output_buf << "parse error near line " << input_line_number
	       << " of file " << curr_fcn_file_full_name;
  else
    output_buf << "parse error:";

  if (s && strcmp (s, "parse error") != 0)
    output_buf << "\n\n  " << s;

  output_buf << "\n\n";

  if (! current_input_line.empty ())
    {
      size_t len = current_input_line.length ();

      if (current_input_line[len-1] == '\n')
        current_input_line.resize (len-1);

      // Print the line, maybe with a pointer near the error token.

      output_buf << ">>> " << current_input_line << "\n";

      if (err_col == 0)
	err_col = len;

      for (int i = 0; i < err_col + 3; i++)
	output_buf << " ";

      output_buf << "^";
    }

  output_buf << "\n";

  std::string msg = output_buf.str ();

  parse_error ("%s", msg.c_str ());
}

// Error mesages for mismatched end tokens.

static void
end_error (const char *type, token::end_tok_type ettype, int l, int c)
{
  static const char *fmt
    = "`%s' command matched by `%s' near line %d column %d";

  switch (ettype)
    {
    case token::simple_end:
      error (fmt, type, "end", l, c);
      break;

    case token::for_end:
      error (fmt, type, "endfor", l, c);
      break;

    case token::function_end:
      error (fmt, type, "endfunction", l, c);
      break;

    case token::if_end:
      error (fmt, type, "endif", l, c);
      break;

    case token::switch_end:
      error (fmt, type, "endswitch", l, c); 
      break;

    case token::while_end:
      error (fmt, type, "endwhile", l, c); 
      break;

    case token::try_catch_end:
      error (fmt, type, "end_try_catch", l, c); 
      break;

    case token::unwind_protect_end:
      error (fmt, type, "end_unwind_protect", l, c); 
      break;

    default:
      panic_impossible ();
      break;
    }
}

// Check to see that end tokens are properly matched.

static bool
end_token_ok (token *tok, token::end_tok_type expected)
{
  bool retval = true;

  token::end_tok_type ettype = tok->ettype ();

  if (ettype != expected && ettype != token::simple_end)
    {
      retval = false;

      yyerror ("parse error");

      int l = tok->line ();
      int c = tok->column ();

      switch (expected)
	{
	case token::for_end:
	  end_error ("for", ettype, l, c);
	  break;

	case token::function_end:
	  end_error ("function", ettype, l, c);
	  break;

	case token::if_end:
	  end_error ("if", ettype, l, c);
	  break;

	case token::try_catch_end:
	  end_error ("try", ettype, l, c);
	  break;

	case token::switch_end:
	  end_error ("switch", ettype, l, c);
	  break;

	case token::unwind_protect_end:
	  end_error ("unwind_protect", ettype, l, c);
	  break;

	case token::while_end:
	  end_error ("while", ettype, l, c);
	  break;

	default:
	  panic_impossible ();
	  break;
	}
    }

  return retval;
}

// Maybe print a warning if an assignment expression is used as the
// test in a logical expression.

static void
maybe_warn_assign_as_truth_value (tree_expression *expr)
{
  if (expr->is_assignment_expression ()
      && expr->paren_count () < 2)
    {
      if (curr_fcn_file_full_name.empty ())
	warning_with_id
	  ("Octave:assign-as-truth-value",
	   "suggest parenthesis around assignment used as truth value");
      else
	warning_with_id
	  ("Octave:assign-as-truth-value",
	   "suggest parenthesis around assignment used as truth value near line %d, column %d in file `%s'",
	   expr->line (), expr->column (), curr_fcn_file_full_name.c_str ());
    }
}

// Maybe print a warning about switch labels that aren't constants.

static void
maybe_warn_variable_switch_label (tree_expression *expr)
{
  if (! expr->is_constant ())
    {
      if (curr_fcn_file_full_name.empty ())
	warning_with_id ("Octave:variable-switch-label",
			 "variable switch label");
      else
	warning_with_id
	  ("Octave:variable-switch-label",
	   "variable switch label near line %d, column %d in file `%s'",
	   expr->line (), expr->column (), curr_fcn_file_full_name.c_str ());
    }
}

static tree_expression *
fold (tree_binary_expression *e)
{
  tree_expression *retval = e;

  unwind_protect::begin_frame ("fold_binary_expression");

  unwind_protect_int (error_state);
  unwind_protect_int (warning_state);

  unwind_protect_bool (discard_error_messages);
  unwind_protect_bool (discard_warning_messages);

  discard_error_messages = true;
  discard_warning_messages = true;

  tree_expression *op1 = e->lhs ();
  tree_expression *op2 = e->rhs ();

  octave_value::binary_op op_type = e->op_type ();

  if (op1->is_constant () && op2->is_constant ()
      && (! ((warning_enabled ("Octave:associativity-change")
	      && (op_type == POW || op_type == EPOW))
	     || (warning_enabled ("Octave:precedence-change")
		 && (op_type == EXPR_OR || op_type == EXPR_OR_OR)))))
    {
      octave_value tmp = e->rvalue1 ();

      if (! (error_state || warning_state))
	{
	  tree_constant *tc_retval
	    = new tree_constant (tmp, op1->line (), op1->column ());

	  std::ostringstream buf;

	  tree_print_code tpc (buf);

	  e->accept (tpc);

	  tc_retval->stash_original_text (buf.str ());

	  delete e;

	  retval = tc_retval;
	}
    }

  unwind_protect::run_frame ("fold_binary_expression");

  return retval;
}

static tree_expression *
fold (tree_unary_expression *e)
{
  tree_expression *retval = e;

  unwind_protect::begin_frame ("fold_unary_expression");

  unwind_protect_int (error_state);
  unwind_protect_int (warning_state);

  unwind_protect_bool (discard_error_messages);
  unwind_protect_bool (discard_warning_messages);

  discard_error_messages = true;
  discard_warning_messages = true;

  tree_expression *op = e->operand ();

  if (op->is_constant ())
    {
      octave_value tmp = e->rvalue1 ();

      if (! (error_state || warning_state))
	{
	  tree_constant *tc_retval
	    = new tree_constant (tmp, op->line (), op->column ());

	  std::ostringstream buf;

	  tree_print_code tpc (buf);

	  e->accept (tpc);

	  tc_retval->stash_original_text (buf.str ());

	  delete e;

	  retval = tc_retval;
	}
    }

  unwind_protect::run_frame ("fold_unary_expression");

  return retval;
}

// Finish building a range.

static tree_expression *
finish_colon_expression (tree_colon_expression *e)
{
  tree_expression *retval = e;

  unwind_protect::begin_frame ("finish_colon_expression");

  unwind_protect_int (error_state);
  unwind_protect_int (warning_state);

  unwind_protect_bool (discard_error_messages);
  unwind_protect_bool (discard_warning_messages);

  discard_error_messages = true;
  discard_warning_messages = true;

  tree_expression *base = e->base ();
  tree_expression *limit = e->limit ();
  tree_expression *incr = e->increment ();

  if (base)
    {
      if (limit)
	{
	  if (base->is_constant () && limit->is_constant ()
	      && (! incr || (incr && incr->is_constant ())))
	    {
	      octave_value tmp = e->rvalue1 ();

	      if (! (error_state || warning_state))
		{
		  tree_constant *tc_retval
		    = new tree_constant (tmp, base->line (), base->column ());

		  std::ostringstream buf;

		  tree_print_code tpc (buf);

		  e->accept (tpc);

		  tc_retval->stash_original_text (buf.str ());

		  delete e;

		  retval = tc_retval;
		}
	    }
	}
      else
	{
	  e->preserve_base ();
	  delete e;

	  // FIXME -- need to attempt constant folding here
	  // too (we need a generic way to do that).
	  retval = base;
	}
    }

  unwind_protect::run_frame ("finish_colon_expression");

  return retval;
}

// Make a constant.

static tree_constant *
make_constant (int op, token *tok_val)
{
  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_constant *retval = 0;

  switch (op)
    {
    case NUM:
      {
	octave_value tmp (tok_val->number ());
	retval = new tree_constant (tmp, l, c);
	retval->stash_original_text (tok_val->text_rep ());
      }
      break;

    case IMAG_NUM:
      {
	octave_value tmp (Complex (0.0, tok_val->number ()));
	retval = new tree_constant (tmp, l, c);
	retval->stash_original_text (tok_val->text_rep ());
      }
      break;

    case DQ_STRING:
    case SQ_STRING:
      {
	std::string txt = tok_val->text ();

        char delim = op == DQ_STRING ? '"' : '\'';
        octave_value tmp (txt, delim);

        if (txt.empty ())
          {
            if (op == DQ_STRING)
              tmp = octave_null_str::instance;
            else
              tmp = octave_null_sq_str::instance;
          }

	retval = new tree_constant (tmp, l, c);

	if (op == DQ_STRING)
	  txt = undo_string_escapes (txt);

	// FIXME -- maybe this should also be handled by
	// tok_val->text_rep () for character strings?
	retval->stash_original_text (delim + txt + delim);
      }
      break;

    default:
      panic_impossible ();
      break;
    }

  return retval;
}

// Make a function handle.

static tree_fcn_handle *
make_fcn_handle (token *tok_val)
{
  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_fcn_handle *retval = new tree_fcn_handle (tok_val->text (), l, c);

  return retval;
}

// Make an anonymous function handle.

static tree_anon_fcn_handle *
make_anon_fcn_handle (tree_parameter_list *param_list, tree_statement *stmt)
{
  // FIXME -- need to get these from the location of the @ symbol.

  int l = -1;
  int c = -1;

  tree_parameter_list *ret_list = 0;

  symbol_table::scope_id fcn_scope = symbol_table::current_scope ();

  if (symtab_context.empty ())
    panic_impossible ();

  symbol_table::set_scope (symtab_context.top ());

  symtab_context.pop ();

  stmt->set_print_flag (false);

  tree_statement_list *body = new tree_statement_list (stmt);

  body->mark_as_anon_function_body ();

  tree_anon_fcn_handle *retval
    = new tree_anon_fcn_handle (param_list, ret_list, body, fcn_scope, l, c);

  return retval;
}

static void
maybe_warn_associativity_change (tree_expression *op)
{
  if (op->paren_count () == 0 && op->is_binary_expression ())
    {
      tree_binary_expression *e
	= dynamic_cast<tree_binary_expression *> (op);

      octave_value::binary_op op_type = e->op_type ();

      if (op_type == octave_value::op_pow
	  || op_type == octave_value::op_el_pow)
	{
	  std::string op_str = octave_value::binary_op_as_string (op_type);

	  if (curr_fcn_file_full_name.empty ())
	    warning_with_id
	      ("Octave:associativity-change",
	       "meaning may have changed due to change in associativity for %s operator",
	       op_str.c_str ());
	  else
	    warning_with_id
	      ("Octave:associativity-change",
	       "meaning may have changed due to change in associativity for %s operator near line %d, column %d in file `%s'",
	       op_str.c_str (), op->line (), op->column (),
	       curr_fcn_file_full_name.c_str ());
	}
    }
}

// Build a binary expression.

static tree_expression *
make_binary_op (int op, tree_expression *op1, token *tok_val,
		tree_expression *op2)
{
  octave_value::binary_op t = octave_value::unknown_binary_op;

  switch (op)
    {
    case POW:
      t = octave_value::op_pow;
      maybe_warn_associativity_change (op1);
      break;

    case EPOW:
      t = octave_value::op_el_pow;
      maybe_warn_associativity_change (op1);
      break;

    case '+':
      t = octave_value::op_add;
      break;

    case '-':
      t = octave_value::op_sub;
      break;

    case '*':
      t = octave_value::op_mul;
      break;

    case '/':
      t = octave_value::op_div;
      break;

    case EMUL:
      t = octave_value::op_el_mul;
      break;

    case EDIV:
      t = octave_value::op_el_div;
      break;

    case LEFTDIV:
      t = octave_value::op_ldiv;
      break;

    case ELEFTDIV:
      t = octave_value::op_el_ldiv;
      break;

    case LSHIFT:
      t = octave_value::op_lshift;
      break;

    case RSHIFT:
      t = octave_value::op_rshift;
      break;

    case EXPR_LT:
      t = octave_value::op_lt;
      break;

    case EXPR_LE:
      t = octave_value::op_le;
      break;

    case EXPR_EQ:
      t = octave_value::op_eq;
      break;

    case EXPR_GE:
      t = octave_value::op_ge;
      break;

    case EXPR_GT:
      t = octave_value::op_gt;
      break;

    case EXPR_NE:
      t = octave_value::op_ne;
      break;

    case EXPR_AND:
      t = octave_value::op_el_and;
      break;

    case EXPR_OR:
      t = octave_value::op_el_or;
      if (op2->paren_count () == 0 && op2->is_binary_expression ())
        {
	  tree_binary_expression *e
	    = dynamic_cast<tree_binary_expression *> (op2);

	  if (e->op_type () == octave_value::op_el_and)
	    {
	      if (curr_fcn_file_full_name.empty ())
		warning_with_id
		  ("Octave:precedence-change",
		   "meaning may have changed due to change in precedence for & and | operators");
	      else
		warning_with_id
		  ("Octave:precedence-change",
		   "meaning may have changed due to change in precedence for & and | operators near line %d, column %d in file `%s'",
		   op2->line (), op2->column (),
		   curr_fcn_file_full_name.c_str ());
	    }
        }
      break;

    default:
      panic_impossible ();
      break;
    }

  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_binary_expression *e
    = maybe_compound_binary_expression (op1, op2, l, c, t);

  return fold (e);
}

// Build a boolean expression.

static tree_expression *
make_boolean_op (int op, tree_expression *op1, token *tok_val,
		 tree_expression *op2)
{
  tree_boolean_expression::type t;

  switch (op)
    {
    case EXPR_AND_AND:
      t = tree_boolean_expression::bool_and;
      break;

    case EXPR_OR_OR:
      t = tree_boolean_expression::bool_or;
      if (op2->paren_count () == 0 && op2->is_boolean_expression ())
        {
	  tree_boolean_expression *e
	    = dynamic_cast<tree_boolean_expression *> (op2);

	  if (e->op_type () == tree_boolean_expression::bool_and)
	    warning_with_id
	      ("Octave:precedence-change",
	       "meaning may have changed due to change in precedence for && and || operators");
        }
      break;

    default:
      panic_impossible ();
      break;
    }

  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_boolean_expression *e
    = new tree_boolean_expression (op1, op2, l, c, t);

  return fold (e);
}

// Build a prefix expression.

static tree_expression *
make_prefix_op (int op, tree_expression *op1, token *tok_val)
{
  octave_value::unary_op t = octave_value::unknown_unary_op;

  switch (op)
    {
    case EXPR_NOT:
      t = octave_value::op_not;
      break;

    case '+':
      t = octave_value::op_uplus;
      break;

    case '-':
      t = octave_value::op_uminus;
      break;

    case PLUS_PLUS:
      t = octave_value::op_incr;
      break;

    case MINUS_MINUS:
      t = octave_value::op_decr;
      break;

    default:
      panic_impossible ();
      break;
    }

  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_prefix_expression *e
    = new tree_prefix_expression (op1, l, c, t);

  return fold (e);
}

// Build a postfix expression.

static tree_expression *
make_postfix_op (int op, tree_expression *op1, token *tok_val)
{
  octave_value::unary_op t = octave_value::unknown_unary_op;

  switch (op)
    {
    case QUOTE:
      t = octave_value::op_hermitian;
      break;

    case TRANSPOSE:
      t = octave_value::op_transpose;
      break;

    case PLUS_PLUS:
      t = octave_value::op_incr;
      break;

    case MINUS_MINUS:
      t = octave_value::op_decr;
      break;

    default:
      panic_impossible ();
      break;
    }

  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_postfix_expression *e
    = new tree_postfix_expression (op1, l, c, t);

  return fold (e);
}

// Build an unwind-protect command.

static tree_command *
make_unwind_command (token *unwind_tok, tree_statement_list *body,
		     tree_statement_list *cleanup, token *end_tok,
		     octave_comment_list *lc, octave_comment_list *mc)
{
  tree_command *retval = 0;

  if (end_token_ok (end_tok, token::unwind_protect_end))
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      int l = unwind_tok->line ();
      int c = unwind_tok->column ();

      retval = new tree_unwind_protect_command (body, cleanup,
						lc, mc, tc, l, c);
    }

  return retval;
}

// Build a try-catch command.

static tree_command *
make_try_command (token *try_tok, tree_statement_list *body,
		  tree_statement_list *cleanup, token *end_tok,
		  octave_comment_list *lc, octave_comment_list *mc)
{
  tree_command *retval = 0;

  if (end_token_ok (end_tok, token::try_catch_end))
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      int l = try_tok->line ();
      int c = try_tok->column ();

      retval = new tree_try_catch_command (body, cleanup,
					   lc, mc, tc, l, c);
    }

  return retval;
}

// Build a while command.

static tree_command *
make_while_command (token *while_tok, tree_expression *expr,
		    tree_statement_list *body, token *end_tok,
		    octave_comment_list *lc)
{
  tree_command *retval = 0;

  maybe_warn_assign_as_truth_value (expr);

  if (end_token_ok (end_tok, token::while_end))
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      lexer_flags.looping--;

      int l = while_tok->line ();
      int c = while_tok->column ();

      retval = new tree_while_command (expr, body, lc, tc, l, c);
    }

  return retval;
}

// Build a do-until command.

static tree_command *
make_do_until_command (token *until_tok, tree_statement_list *body,
		       tree_expression *expr, octave_comment_list *lc)
{
  tree_command *retval = 0;

  maybe_warn_assign_as_truth_value (expr);

  octave_comment_list *tc = octave_comment_buffer::get_comment ();

  lexer_flags.looping--;

  int l = until_tok->line ();
  int c = until_tok->column ();

  retval = new tree_do_until_command (expr, body, lc, tc, l, c);

  return retval;
}

// Build a for command.

static tree_command *
make_for_command (token *for_tok, tree_argument_list *lhs,
		  tree_expression *expr, tree_statement_list *body,
		  token *end_tok, octave_comment_list *lc)
{
  tree_command *retval = 0;

  if (end_token_ok (end_tok, token::for_end))
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      lexer_flags.looping--;

      int l = for_tok->line ();
      int c = for_tok->column ();

      if (lhs->length () == 1)
	{
	  tree_expression *tmp = lhs->remove_front ();

	  retval = new tree_simple_for_command (tmp, expr, body,
						lc, tc, l, c);

	  delete lhs;
	}
      else
	retval = new tree_complex_for_command (lhs, expr, body,
					       lc, tc, l, c);
    }

  return retval;
}

// Build a break command.

static tree_command *
make_break_command (token *break_tok)
{
  tree_command *retval = 0;

  int l = break_tok->line ();
  int c = break_tok->column ();

  // We check to see if we are evaluating a function, script, or loop
  // so that we don't turn eval ("break;") inside a function, script,
  // or loop into a no-op command.

  if (lexer_flags.looping || lexer_flags.defining_func
      || reading_script_file || tree_evaluator::in_fcn_or_script_body
      || tree_evaluator::in_loop_command)
    retval = new tree_break_command (l, c);
  else
    retval = new tree_no_op_command ("break", l, c);

  return retval;
}

// Build a continue command.

static tree_command *
make_continue_command (token *continue_tok)
{
  tree_command *retval = 0;

  int l = continue_tok->line ();
  int c = continue_tok->column ();

  // We check to see if we are evaluating a loop so that we don't turn
  // eval ("continue;") into a no-op command inside a loop.

  if (lexer_flags.looping || tree_evaluator::in_loop_command)
    retval = new tree_continue_command (l, c);
  else
    retval = new tree_no_op_command ("continue", l, c);

  return retval;
}

// Build a return command.

static tree_command *
make_return_command (token *return_tok)
{
  tree_command *retval = 0;

  int l = return_tok->line ();
  int c = return_tok->column ();

  if (Vdebugging)
    {
      Vdebugging = false;

      retval = new tree_no_op_command ("return", l, c);
    }
  else
    {
      // We check to see if we are evaluating a function or script so
      // that we don't turn eval ("return;") inside a function, script,
      // or loop into a no-op command.

      if (lexer_flags.defining_func || reading_script_file
          || tree_evaluator::in_fcn_or_script_body)
        retval = new tree_return_command (l, c);
      else
        retval = new tree_no_op_command ("return", l, c);
    }

  return retval;
}

// Start an if command.

static tree_if_command_list *
start_if_command (tree_expression *expr, tree_statement_list *list)
{
  maybe_warn_assign_as_truth_value (expr);

  tree_if_clause *t = new tree_if_clause (expr, list);

  return new tree_if_command_list (t);
}

// Finish an if command.

static tree_if_command *
finish_if_command (token *if_tok, tree_if_command_list *list,
		   token *end_tok, octave_comment_list *lc)
{
  tree_if_command *retval = 0;

  if (end_token_ok (end_tok, token::if_end))
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      int l = if_tok->line ();
      int c = if_tok->column ();

      if (list && ! list->empty ())
	{
	  tree_if_clause *elt = list->front ();

	  if (elt)
	    {
	      elt->line (l);
	      elt->column (c);
	    }
	}

      retval = new tree_if_command (list, lc, tc, l, c);
    }

  return retval;
}

// Build an elseif clause.

static tree_if_clause *
make_elseif_clause (token *elseif_tok, tree_expression *expr,
		    tree_statement_list *list, octave_comment_list *lc)
{
  maybe_warn_assign_as_truth_value (expr);

  int l = elseif_tok->line ();
  int c = elseif_tok->column ();

  return new tree_if_clause (expr, list, lc, l, c);
}

// Finish a switch command.

static tree_switch_command *
finish_switch_command (token *switch_tok, tree_expression *expr,
		       tree_switch_case_list *list, token *end_tok,
		       octave_comment_list *lc)
{
  tree_switch_command *retval = 0;

  if (end_token_ok (end_tok, token::switch_end))
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      int l = switch_tok->line ();
      int c = switch_tok->column ();

      if (list && ! list->empty ())
	{
	  tree_switch_case *elt = list->front ();

	  if (elt)
	    {
	      elt->line (l);
	      elt->column (c);
	    }
	}

      retval = new tree_switch_command (expr, list, lc, tc, l, c);
    }

  return retval;
}

// Build a switch case.

static tree_switch_case *
make_switch_case (token *case_tok, tree_expression *expr,
		  tree_statement_list *list, octave_comment_list *lc)
{
  maybe_warn_variable_switch_label (expr);

  int l = case_tok->line ();
  int c = case_tok->column ();

  return new tree_switch_case (expr, list, lc, l, c);
}

// Build an assignment to a variable.

static tree_expression *
make_assign_op (int op, tree_argument_list *lhs, token *eq_tok,
		tree_expression *rhs)
{
  tree_expression *retval = 0;

  octave_value::assign_op t = octave_value::unknown_assign_op;

  switch (op)
    {
    case '=':
      t = octave_value::op_asn_eq;
      break;

    case ADD_EQ:
      t = octave_value::op_add_eq;
      break;

    case SUB_EQ:
      t = octave_value::op_sub_eq;
      break;

    case MUL_EQ:
      t = octave_value::op_mul_eq;
      break;

    case DIV_EQ:
      t = octave_value::op_div_eq;
      break;

    case LEFTDIV_EQ:
      t = octave_value::op_ldiv_eq;
      break;

    case POW_EQ:
      t = octave_value::op_pow_eq;
      break;

    case LSHIFT_EQ:
      t = octave_value::op_lshift_eq;
      break;

    case RSHIFT_EQ:
      t = octave_value::op_rshift_eq;
      break;

    case EMUL_EQ:
      t = octave_value::op_el_mul_eq;
      break;

    case EDIV_EQ:
      t = octave_value::op_el_div_eq;
      break;

    case ELEFTDIV_EQ:
      t = octave_value::op_el_ldiv_eq;
      break;

    case EPOW_EQ:
      t = octave_value::op_el_pow_eq;
      break;

    case AND_EQ:
      t = octave_value::op_el_and_eq;
      break;

    case OR_EQ:
      t = octave_value::op_el_or_eq;
      break;

    default:
      panic_impossible ();
      break;
    }

  int l = eq_tok->line ();
  int c = eq_tok->column ();

  if (lhs->is_simple_assign_lhs ())
    {
      tree_expression *tmp = lhs->remove_front ();

      retval = new tree_simple_assignment (tmp, rhs, false, l, c, t);

      delete lhs;
    }
  else
    return new tree_multi_assignment (lhs, rhs, false, l, c, t);

  return retval;
}

// Define a function.

static void
make_script (tree_statement_list *cmds, tree_statement *end_script)
{
  std::string doc_string;

  if (! help_buf.empty ())
    {
      doc_string = help_buf.top ();
      help_buf.pop ();
    }

  if (! cmds)
    cmds = new tree_statement_list ();

  cmds->append (end_script);

  octave_user_script *script
    = new octave_user_script (curr_fcn_file_full_name, curr_fcn_file_name,
			      cmds, doc_string);

  octave_time now;

  script->stash_fcn_file_time (now);

  curr_fcn_ptr = script;

  // Unmark any symbols that may have been tagged as local variables
  // while parsing (for example, by force_local_variable in lex.l).

  symbol_table::unmark_forced_variables ();
}

// Begin defining a function.

static octave_user_function *
start_function (tree_parameter_list *param_list, tree_statement_list *body,
		tree_statement *end_fcn_stmt)
{
  // We'll fill in the return list later.

  if (! body)
    body = new tree_statement_list ();

  body->append (end_fcn_stmt);

  octave_user_function *fcn
    = new octave_user_function (symbol_table::current_scope (),
				param_list, 0, body);

  if (fcn)
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      fcn->stash_trailing_comment (tc);
    }

  return fcn;
}

static tree_statement *
make_end (const std::string& type, int l, int c)
{
  return make_statement (new tree_no_op_command (type, l, c));
}

// Do most of the work for defining a function.

static octave_user_function *
frob_function (const std::string& fname, octave_user_function *fcn)
{
  std::string id_name = fname;

  // If input is coming from a file, issue a warning if the name of
  // the file does not match the name of the function stated in the
  // file.  Matlab doesn't provide a diagnostic (it ignores the stated
  // name).

  if (reading_fcn_file || autoloading)
    {
      if (! (autoloading
	     || lexer_flags.parsing_nested_function
	     || lexer_flags.parsing_class_method))
	{
	  // FIXME -- should curr_fcn_file_name already be
	  // preprocessed when we get here?  It seems to only be a
	  // problem with relative file names.

	  std::string nm = curr_fcn_file_name;

	  size_t pos = nm.find_last_of (file_ops::dir_sep_chars ());

	  if (pos != std::string::npos)
	    nm = curr_fcn_file_name.substr (pos+1);

	  if (nm != id_name)
	    {
	      warning_with_id
		("Octave:function-name-clash",
		 "function name `%s' does not agree with function file name `%s'",
		 id_name.c_str (), curr_fcn_file_full_name.c_str ());

	      id_name = nm;
	    }
	}

      octave_time now;

      fcn->stash_fcn_file_name (curr_fcn_file_full_name);
      fcn->stash_fcn_file_time (now);
      fcn->mark_as_system_fcn_file ();

      if (fcn_file_from_relative_lookup)
	fcn->mark_relative ();

      if (lexer_flags.parsing_nested_function)
        {
          fcn->stash_parent_fcn_name (parent_function_name);
          fcn->stash_parent_fcn_scope (symbol_table::parent_scope ());
	}

      if (lexer_flags.parsing_class_method)
	{
	  if (current_class_name == id_name)
	    fcn->mark_as_class_constructor ();
	  else
	    fcn->mark_as_class_method ();

	  fcn->stash_dispatch_class (current_class_name);
	}

      std::string nm = fcn->fcn_file_name ();

      file_stat fs (nm);

      if (fs && fs.is_newer (now))
        warning_with_id ("Octave:future-time-stamp",
			 "time stamp for `%s' is in the future", nm.c_str ());
    }
  else if (! (input_from_tmp_history_file || input_from_startup_file)
	   && reading_script_file
	   && curr_fcn_file_name == id_name)
    {
      warning ("function `%s' defined within script file `%s'",
	       id_name.c_str (), curr_fcn_file_full_name.c_str ());
    }

  fcn->stash_function_name (id_name);

  if (! help_buf.empty ())
    {
      fcn->document (help_buf.top ());

      help_buf.pop ();
    }

  if (reading_fcn_file && ! lexer_flags.parsing_nested_function)
    curr_fcn_ptr = fcn;
  else
    curr_fcn_ptr = 0;

  return fcn;
}

static tree_function_def *
finish_function (tree_parameter_list *ret_list,
		 octave_user_function *fcn, octave_comment_list *lc)
{
  tree_function_def *retval = 0;

  if (ret_list)
    ret_list->mark_as_formal_parameters ();

  if (fcn)
    {
      std::string nm = fcn->name ();
      std::string file = fcn->fcn_file_name ();

      std::string tmp = nm;
      if (! file.empty ())
	tmp += ": " + file;

      symbol_table::cache_name (fcn->scope (), tmp);

      if (lc)
	fcn->stash_leading_comment (lc);

      fcn->define_ret_list (ret_list);

      if (lexer_flags.parsing_nested_function)
	{
	  fcn->mark_as_nested_function ();

	  symbol_table::install_subfunction (nm, octave_value (fcn));

	  if (lexer_flags.parsing_nested_function < 0)
	    {
	      lexer_flags.parsing_nested_function = 0;
	      symbol_table::reset_parent_scope ();
	    }
	}
      else if (! curr_fcn_ptr)
	{
	  // FIXME -- there should be a better way to indicate that we
	  // should create a tree_function_def object other than
	  // looking at curr_fcn_ptr...

	  retval = new tree_function_def (fcn);
	}

      // Unmark any symbols that may have been tagged as local
      // variables while parsing (for example, by force_local_variable
      // in lex.l).

      symbol_table::unmark_forced_variables (fcn->scope ());
    }

  return retval;
}

static void
recover_from_parsing_function (void)
{
  if (symtab_context.empty ())
    panic_impossible ();

  symbol_table::set_scope (symtab_context.top ());
  symtab_context.pop ();

  lexer_flags.defining_func = false;
  lexer_flags.parsed_function_name = false;
  lexer_flags.looking_at_return_list = false;
  lexer_flags.looking_at_parameter_list = false;
}

// Make an index expression.

static tree_index_expression *
make_index_expression (tree_expression *expr, tree_argument_list *args,
		       char type)
{
  tree_index_expression *retval = 0;

  int l = expr->line ();
  int c = expr->column ();

  expr->mark_postfix_indexed ();

  if (expr->is_index_expression ())
    {
      tree_index_expression *tmp = static_cast<tree_index_expression *> (expr);

      tmp->append (args, type);

      retval = tmp;
    }
  else
    retval = new tree_index_expression (expr, args, l, c, type);

  return retval;
}

// Make an indirect reference expression.

static tree_index_expression *
make_indirect_ref (tree_expression *expr, const std::string& elt)
{
  tree_index_expression *retval = 0;

  int l = expr->line ();
  int c = expr->column ();

  if (expr->is_index_expression ())
    {
      tree_index_expression *tmp = static_cast<tree_index_expression *> (expr);

      tmp->append (elt);

      retval = tmp;
    }
  else
    retval = new tree_index_expression (expr, elt, l, c);

  lexer_flags.looking_at_indirect_ref = false;

  return retval;
}

// Make an indirect reference expression with dynamic field name.

static tree_index_expression *
make_indirect_ref (tree_expression *expr, tree_expression *elt)
{
  tree_index_expression *retval = 0;

  int l = expr->line ();
  int c = expr->column ();

  if (expr->is_index_expression ())
    {
      tree_index_expression *tmp = static_cast<tree_index_expression *> (expr);

      tmp->append (elt);

      retval = tmp;
    }
  else
    retval = new tree_index_expression (expr, elt, l, c);

  lexer_flags.looking_at_indirect_ref = false;

  return retval;
}

// Make a declaration command.

static tree_decl_command *
make_decl_command (int tok, token *tok_val, tree_decl_init_list *lst)
{
  tree_decl_command *retval = 0;

  int l = tok_val->line ();
  int c = tok_val->column ();

  switch (tok)
    {
    case GLOBAL:
      retval = new tree_global_command (lst, l, c);
      break;

    case STATIC:
      if (lexer_flags.defining_func)
	retval = new tree_static_command (lst, l, c);
      else
	{
	  if (reading_script_file)
	    warning ("ignoring persistent declaration near line %d of file `%s'",
		     l, curr_fcn_file_full_name.c_str ());
	  else
	    warning ("ignoring persistent declaration near line %d", l);
	}
      break;

    default:
      panic_impossible ();
      break;
    }

  return retval;
}

// Finish building a matrix list.

static tree_expression *
finish_matrix (tree_matrix *m)
{
  tree_expression *retval = m;

  unwind_protect::begin_frame ("finish_matrix");

  unwind_protect_int (error_state);
  unwind_protect_int (warning_state);

  unwind_protect_bool (discard_error_messages);
  unwind_protect_bool (discard_warning_messages);

  discard_error_messages = true;
  discard_warning_messages = true;

  if (m->all_elements_are_constant ())
    {
      octave_value tmp = m->rvalue1 ();

      if (! (error_state || warning_state))
	{
	  tree_constant *tc_retval
	    = new tree_constant (tmp, m->line (), m->column ());

	  std::ostringstream buf;

	  tree_print_code tpc (buf);

	  m->accept (tpc);

	  tc_retval->stash_original_text (buf.str ());

	  delete m;

	  retval = tc_retval;
	}
    }

  unwind_protect::run_frame ("finish_matrix");

  return retval;
}

// Finish building a cell list.

static tree_expression *
finish_cell (tree_cell *c)
{
  return finish_matrix (c);
}

static void
maybe_warn_missing_semi (tree_statement_list *t)
{
  if (lexer_flags.defining_func)
    {
      tree_statement *tmp = t->back();

      if (tmp->is_expression ())
	warning_with_id
	  ("Octave:missing-semicolon",
	   "missing semicolon near line %d, column %d in file `%s'",
	    tmp->line (), tmp->column (), curr_fcn_file_full_name.c_str ());
    }
}

static tree_statement_list *
set_stmt_print_flag (tree_statement_list *list, char sep,
		     bool warn_missing_semi)
{
  tree_statement *tmp = list->back ();

  switch (sep)
    {
    case ';':
      tmp->set_print_flag (false);
      break;

    case 0:
    case ',':
    case '\n':
      tmp->set_print_flag (true);
      if (warn_missing_semi)
	maybe_warn_missing_semi (list);
      break;

    default:
      warning ("unrecognized separator type!");
      break;
    }

  // Even if a statement is null, we add it to the list then remove it
  // here so that the print flag is applied to the correct statement.

  if (tmp->is_null_statement ())
    {
      list->pop_back ();
      delete tmp;
    }

  return list;
}

static tree_statement_list *
make_statement_list (tree_statement *stmt)
{
  return new tree_statement_list (stmt);
}

static tree_statement_list *
append_statement_list (tree_statement_list *list, char sep,
		       tree_statement *stmt, bool warn_missing_semi)
{
  set_stmt_print_flag (list, sep, warn_missing_semi);

  list->append (stmt);

  return list;
}

static void
safe_fclose (void *f)
{
  // FIXME -- comments at the end of an input file are
  // discarded (otherwise, they would be appended to the next
  // statement, possibly from the command line or another file, which
  // can be quite confusing).

  octave_comment_list *tc = octave_comment_buffer::get_comment ();

  delete tc;

  if (f)
    fclose (static_cast<FILE *> (f));
}

static bool
looks_like_copyright (const std::string& s)
{
  bool retval = false;

  if (! s.empty ())
    {
      size_t offset = s.find_first_not_of (" \t");
  
      retval = (s.substr (offset, 9) == "Copyright");
    }

  return retval;
}

static int
text_getc (FILE *f)
{
  int c = getc (f);

  // Convert CRLF into just LF and single CR into LF.

  if (c == '\r')
    {
      c = getc (f);

      if (c != '\n')
	{
	  ungetc (c, f);
	  c = '\n';
	}
    }

  if (c == '\n')
    input_line_number++;

  return c;
}

class
stdio_stream_reader : public stream_reader
{
public:
  stdio_stream_reader (FILE *f_arg) : stream_reader (), f (f_arg) { }

  int getc (void) { return ::text_getc (f); }
  int ungetc (int c)
  {
    if (c == '\n')
      input_line_number--;

    return ::ungetc (c, f);
  }
  
private:
  FILE *f;
};

static bool
skip_white_space (stream_reader& reader)
{
  int c = 0;

  while ((c = reader.getc ()) != EOF)
    {
      switch (c)
	{
	case ' ':
	case '\t':
	  current_input_column++;
	  break;

	case '\n':
	  current_input_column = 0;
	  break;

	default:
	  current_input_column--;
	  reader.ungetc (c);
	  goto done;
	}
    }

 done:

  return (c == EOF);
}

static std::string
gobble_leading_white_space (FILE *ffile, bool& eof)
{
  std::string help_txt;

  eof = false;

  // TRUE means we have already cached the help text.
  bool have_help_text = false;

  std::string txt;

  stdio_stream_reader stdio_reader (ffile);

  while (true)
    {
      eof = skip_white_space (stdio_reader);

      if (eof)
	break;

      txt = grab_comment_block (stdio_reader, true, eof);

      if (txt.empty ())
	break;

      if (! (have_help_text || looks_like_copyright (txt)))
	{
	  help_txt = txt;
	  have_help_text = true;
	}

      octave_comment_buffer::append (txt);

      if (eof)
	break;
    }

  return help_txt;
}

static bool
looking_at_function_keyword (FILE *ffile)
{
  bool status = false;

  long pos = ftell (ffile);

  char buf [10];
  fgets (buf, 10, ffile);
  size_t len = strlen (buf);
  if (len > 8 && strncmp (buf, "function", 8) == 0
      && ! (isalnum (buf[8]) || buf[8] == '_'))
    status = true;

  fseek (ffile, pos, SEEK_SET);

  return status;
}

static void
restore_command_history (void *)
{
  command_history::ignore_entries (! Vsaving_history);
}

static void
restore_input_stream (void *f)
{
  command_editor::set_input_stream (static_cast<FILE *> (f));
}

static octave_function *
parse_fcn_file (const std::string& ff, const std::string& dispatch_type,
		bool force_script = false, bool require_file = true,
		const std::string& warn_for = std::string ())
{
  unwind_protect::begin_frame ("parse_fcn_file");

  octave_function *fcn_ptr = 0;

  // Open function file and parse.

  bool old_reading_fcn_file_state = reading_fcn_file;

  FILE *in_stream = command_editor::get_input_stream ();

  unwind_protect::add (restore_input_stream, in_stream);

  unwind_protect_ptr (ff_instream);

  unwind_protect_int (input_line_number);
  unwind_protect_int (current_input_column);
  unwind_protect_int (end_tokens_expected);
  unwind_protect_bool (reading_fcn_file);
  unwind_protect_bool (line_editing);
  unwind_protect_str (parent_function_name);
  unwind_protect_str (current_class_name);

  input_line_number = 1;
  current_input_column = 1;
  end_tokens_expected = 0;
  reading_fcn_file = true;
  line_editing = false;
  parent_function_name = "";
  current_class_name = dispatch_type;

  // The next four lines must be in this order.
  unwind_protect::add (restore_command_history, 0);

  // FIXME -- we shouldn't need both the
  // command_history object and the
  // Vsaving_history variable...
  command_history::ignore_entries ();

  unwind_protect_bool (Vsaving_history);

  Vsaving_history = false;

  FILE *ffile = get_input_from_file (ff, 0);

  unwind_protect::add (safe_fclose, ffile);

  if (ffile)
    {
      bool eof;

      std::string help_txt = gobble_leading_white_space (ffile, eof);

      if (! eof)
	{
	  std::string file_type;

	  bool parsing_script = false;

	  unwind_protect_bool (get_input_from_eval_string);
	  unwind_protect_bool (parser_end_of_input);

	  get_input_from_eval_string = false;
	  parser_end_of_input = false;

	  if (! force_script && looking_at_function_keyword (ffile))
	    {
	      file_type = "function";

	      unwind_protect_int (Vecho_executing_commands);
	      unwind_protect_bool (reading_fcn_file);

	      Vecho_executing_commands = ECHO_OFF;
	      reading_fcn_file = true;
	    }
	  else
	    {
	      file_type = "script";

	      // The value of `reading_fcn_file' will be restored to the
	      // proper value when we unwind from this frame.
	      reading_fcn_file = old_reading_fcn_file_state;

	      unwind_protect_bool (reading_script_file);

	      reading_script_file = true;

	      parsing_script = true;
	    }

	  YY_BUFFER_STATE old_buf = current_buffer ();
	  YY_BUFFER_STATE new_buf = create_buffer (ffile);

	  unwind_protect::add (restore_input_buffer, old_buf);
	  unwind_protect::add (delete_input_buffer, new_buf);

	  switch_to_buffer (new_buf);

	  unwind_protect_ptr (curr_fcn_ptr);
	  curr_fcn_ptr = 0;

	  reset_parser ();

	  // Do this with an unwind-protect cleanup function so that
	  // the forced variables will be unmarked in the event of an
	  // interrupt. 
	  symbol_table::scope_id scope = symbol_table::top_scope ();
	  unwind_protect::add (symbol_table::unmark_forced_variables, &scope);

	  if (! help_txt.empty ())
	    help_buf.push (help_txt);

	  if (parsing_script)
	    prep_lexer_for_script ();

	  lexer_flags.parsing_class_method = ! dispatch_type.empty ();

	  int status = yyparse ();

	  fcn_ptr = curr_fcn_ptr;

	  if (status != 0)
	    error ("parse error while reading %s file %s",
		   file_type.c_str(), ff.c_str ());
	}
    }
  else if (require_file)
    error ("no such file, `%s'", ff.c_str ());
  else if (! warn_for.empty ())
    error ("%s: unable to open file `%s'", warn_for.c_str (), ff.c_str ());    

  unwind_protect::run_frame ("parse_fcn_file");

  return fcn_ptr;
}

std::string
get_help_from_file (const std::string& nm, bool& symbol_found,
		    std::string& file)
{
  std::string retval;

  file = fcn_file_in_path (nm);

  if (! file.empty ())
    {
      symbol_found = true;

      FILE *fptr = fopen (file.c_str (), "r");

      if (fptr)
	{
	  unwind_protect::add (safe_fclose, fptr);

	  bool eof;
	  retval = gobble_leading_white_space (fptr, eof);

	  if (retval.empty ())
	    {
	      octave_function *fcn = parse_fcn_file (file, "");

	      if (fcn)
		{
		  retval = fcn->doc_string ();

		  delete fcn;
		}
	    }

	  unwind_protect::run ();
	}
    }

  return retval;
}

std::string
get_help_from_file (const std::string& nm, bool& symbol_found)
{
  std::string file;
  return get_help_from_file (nm, symbol_found, file);
}

std::string
lookup_autoload (const std::string& nm)
{
  std::string retval;

  typedef std::map<std::string, std::string>::const_iterator am_iter;

  am_iter p = autoload_map.find (nm);

  if (p != autoload_map.end ())
    retval = load_path::find_file (p->second);

  return retval;
}

string_vector 
autoloaded_functions (void)
{
  string_vector names (autoload_map.size());

  octave_idx_type i = 0;
  typedef std::map<std::string, std::string>::const_iterator am_iter;
  for (am_iter p = autoload_map.begin (); p != autoload_map.end (); p++)
    names[i++] = p->first;

  return names;
}

string_vector
reverse_lookup_autoload (const std::string& nm)
{
  string_vector names;

  typedef std::map<std::string, std::string>::const_iterator am_iter;
  for (am_iter p = autoload_map.begin (); p != autoload_map.end (); p++)
    if (nm == p->second)
      names.append (p->first);

  return names;
}

octave_function *
load_fcn_from_file (const std::string& file_name, const std::string& dir_name,
		    const std::string& dispatch_type,
		    const std::string& fcn_name, bool autoload)
{
  octave_function *retval = 0;

  unwind_protect::begin_frame ("load_fcn_from_file");

  std::string nm = file_name;

  size_t nm_len = nm.length ();

  std::string file;

  unwind_protect_bool (fcn_file_from_relative_lookup);

  fcn_file_from_relative_lookup = false;

  file = nm;

  if ((nm_len > 4 && nm.substr (nm_len-4) == ".oct")
      || (nm_len > 4 && nm.substr (nm_len-4) == ".mex")
      || (nm_len > 2 && nm.substr (nm_len-2) == ".m"))
    {
      nm = octave_env::base_pathname (file);
      nm = nm.substr (0, nm.find_last_of ('.'));
    }

  if (autoload)
    {
      unwind_protect_bool (autoloading);
      autoloading = true;
    }

  fcn_file_from_relative_lookup = ! octave_env::absolute_pathname (file);

  file = octave_env::make_absolute (file, octave_env::getcwd ());

  int len = file.length ();

  if (len > 4 && file.substr (len-4, len-1) == ".oct")
    {
      if (autoload && ! fcn_name.empty ())
	nm = fcn_name;

      retval = octave_dynamic_loader::load_oct (nm, file, fcn_file_from_relative_lookup);
    }
  else if (len > 4 && file.substr (len-4, len-1) == ".mex")
    retval = octave_dynamic_loader::load_mex (nm, file, fcn_file_from_relative_lookup);
  else if (len > 2)
    {
      // These are needed by yyparse.

      unwind_protect_str (curr_fcn_file_name);
      unwind_protect_str (curr_fcn_file_full_name);

      curr_fcn_file_name = nm;
      curr_fcn_file_full_name = file;

      retval = parse_fcn_file (file, dispatch_type, autoloading);
    }

  if (retval)
    {
      retval->stash_dir_name (dir_name);

      if (retval->is_user_function ())
	{
	  symbol_table::scope_id id = retval->scope ();

	  symbol_table::stash_dir_name_for_subfunctions (id, dir_name);
	}
    }

  unwind_protect::run_frame ("load_fcn_from_file");

  return retval;
}

DEFUN (autoload, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} autoload (@var{function}, @var{file})\n\
Define @var{function} to autoload from @var{file}.\n\
\n\
The second argument, @var{file}, should be an absolute file name or\n\
a file name in the same directory as the function or script from which\n\
the autoload command was run.  @var{file} should not depend on the\n\
Octave load path.\n\
\n\
Normally, calls to @code{autoload} appear in PKG_ADD script files that\n\
are evaluated when a directory is added to the Octave's load path.  To\n\
avoid having to hardcode directory names in @var{file}, if @var{file}\n\
is in the same directory as the PKG_ADD script then\n\
\n\
@example\n\
autoload (\"foo\", \"bar.oct\");\n\
@end example\n\
\n\
will load the function @code{foo} from the file @code{bar.oct}.  The above\n\
when @code{bar.oct} is not in the same directory or uses like\n\
\n\
@example\n\
autoload (\"foo\", file_in_loadpath (\"bar.oct\"))\n\
@end example\n\
\n\
@noindent\n\
are strongly discouraged, as their behavior might be unpredictable.\n\
\n\
With no arguments, return a structure containing the current autoload map.\n\
@seealso{PKG_ADD}\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin == 0)
    {
      Cell func_names (dim_vector (autoload_map.size ()), 1);
      Cell file_names (dim_vector (autoload_map.size ()), 1);

      octave_idx_type i = 0;
      typedef std::map<std::string, std::string>::const_iterator am_iter;
      for (am_iter p = autoload_map.begin (); p != autoload_map.end (); p++)
	{
	  func_names(i) = p->first;
	  file_names(i) = p->second;

	  i++;
	}

      Octave_map m;

      m.assign ("function", func_names);
      m.assign ("file", file_names);

      retval = m;
    }
  else if (nargin == 2)
    {
      string_vector argv = args.make_argv ("autoload");

      if (! error_state)
        {
	  std::string nm = argv[2];

	  if (! octave_env::absolute_pathname (nm))
	    {
	      octave_user_code *fcn = octave_call_stack::caller_user_code ();

	      bool found = false;

	      if (fcn)
		{
		  std::string fname = fcn->fcn_file_name ();

		  if (! fname.empty ())
		    {
		      fname = octave_env::make_absolute (fname, octave_env::getcwd ());
		      fname = fname.substr (0, fname.find_last_of (file_ops::dir_sep_str ()) + 1);

		      file_stat fs (fname + nm);

		      if (fs.exists ())
			{
			  nm = fname + nm;
			  found = true;
			}
		    }
		}
	      if (! found)
		warning_with_id ("Octave:autoload-relative-file-name",
				 "autoload: `%s' is not an absolute file name",
				 nm.c_str ());
	    }
	  autoload_map[argv[1]] = nm;
	}
    }
  else
    print_usage ();

  return retval;
}

void
source_file (const std::string& file_name, const std::string& context,
	     bool verbose, bool require_file, const std::string& warn_for)
{
  std::string file_full_name = file_ops::tilde_expand (file_name);

  unwind_protect::begin_frame ("source_file");

  unwind_protect_str (curr_fcn_file_name);
  unwind_protect_str (curr_fcn_file_full_name);

  curr_fcn_file_name = file_name;
  curr_fcn_file_full_name = file_full_name;

  if (! context.empty ())
    {
      if (context == "caller")
	octave_call_stack::goto_caller_frame ();
      else if (context == "base")
	octave_call_stack::goto_base_frame ();
      else
	error ("source: context must be \"caller\" or \"base\"");

      if (! error_state)
	unwind_protect::add (octave_call_stack::unwind_pop);
    }      

  if (! error_state)
    {
      octave_function *fcn = parse_fcn_file (file_full_name, "", true,
					     require_file, warn_for);

      if (! error_state)
	{
	  if (fcn && fcn->is_user_script ())
	    {
	      octave_value_list args;

	      if (verbose)
		{
		  std::cout << "executing commands from " << file_full_name << " ... ";
		  reading_startup_message_printed = true;
		  std::cout.flush ();
		}

	      fcn->do_multi_index_op (0, args);

	      if (verbose)
		std::cout << "done." << std::endl;

	      delete fcn;
	    }
	}
      else
	error ("source: error sourcing file `%s'",
	       file_full_name.c_str ());
    }

  unwind_protect::run_frame ("source_file");
}

DEFUN (mfilename, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} mfilename ()\n\
@deftypefnx {Built-in Function} {} mfilename (@code{\"fullpath\"})\n\
@deftypefnx {Built-in Function} {} mfilename (@code{\"fullpathext\"})\n\
Return the name of the currently executing file.  At the top-level,\n\
return the empty string.  Given the argument @code{\"fullpath\"},\n\
include the directory part of the file name, but not the extension.\n\
Given the argument @code{\"fullpathext\"}, include the directory part\n\
of the file name and the extension.\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin > 1)
    {
      print_usage ();
      return retval;
    }

  std::string arg;

  if (nargin == 1)
    {
      arg = args(0).string_value ();

      if (error_state)
	{
	  error ("mfilename: expecting argument to be a character string");
	  return retval;
	}
    }

  std::string fname;

  octave_user_code *fcn = octave_call_stack::caller_user_code ();

  if (fcn)
    {
      fname = fcn->fcn_file_name ();

      if (fname.empty ())
        fname = fcn->name ();
    }

  if (arg == "fullpathext")
    retval = fname;
  else
    {
      size_t dpos = fname.rfind (file_ops::dir_sep_char ());
      size_t epos = fname.rfind ('.');

      if (epos <= dpos)
        epos = std::string::npos;

      fname = (epos != std::string::npos) ? fname.substr (0, epos) : fname;

      if (arg == "fullpath")
	retval = fname;
      else
        retval = (dpos != std::string::npos) ? fname.substr (dpos+1) : fname;
    }

  return retval;
}


DEFUN (source, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} source (@var{file})\n\
Parse and execute the contents of @var{file}.  This is equivalent to\n\
executing commands from a script file, but without requiring the file to\n\
be named @file{@var{file}.m}.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin == 1 || nargin == 2)
    {
      std::string file_name = args(0).string_value ();

      if (! error_state)
	{
	  std::string context;

	  if (nargin == 2)
	    context = args(1).string_value ();

	  if (! error_state)
	    source_file (file_name, context);
	  else
	    error ("source: expecting context to be character string");
	}
      else
	error ("source: expecting file name as argument");
    }
  else
    print_usage ();

  return retval;
}

// Evaluate an Octave function (built-in or interpreted) and return
// the list of result values.  NAME is the name of the function to
// call.  ARGS are the arguments to the function.  NARGOUT is the
// number of output arguments expected. 

octave_value_list
feval (const std::string& name, const octave_value_list& args, int nargout)
{
  octave_value_list retval;

  octave_value fcn = symbol_table::find_function (name, args);

  if (fcn.is_defined ())
    retval = fcn.do_multi_index_op (nargout, args);
  else
    error ("feval: function `%s' not found", name.c_str ());

  return retval;
}

octave_value_list
feval (octave_function *fcn, const octave_value_list& args, int nargout)
{
  octave_value_list retval;

  if (fcn)
    retval = fcn->do_multi_index_op (nargout, args);

  return retval;
}

static octave_value_list
get_feval_args (const octave_value_list& args)
{
  int tmp_nargin = args.length () - 1;

  octave_value_list retval (tmp_nargin, octave_value ());

  for (int i = 0; i < tmp_nargin; i++)
    retval(i) = args(i+1);

  string_vector arg_names = args.name_tags ();

  if (! arg_names.empty ())
    {
      // tmp_nargin and arg_names.length () - 1 may differ if
      // we are passed all_va_args.

      int n = arg_names.length () - 1;

      int len = n > tmp_nargin ? tmp_nargin : n;

      string_vector tmp_arg_names (len);

      for (int i = 0; i < len; i++)
	tmp_arg_names(i) = arg_names(i+1);

      retval.stash_name_tags (tmp_arg_names);
    }

  return retval;
}


// Evaluate an Octave function (built-in or interpreted) and return
// the list of result values.  The first element of ARGS should be a
// string containing the name of the function to call, then the rest
// are the actual arguments to the function.  NARGOUT is the number of
// output arguments expected.

octave_value_list
feval (const octave_value_list& args, int nargout)
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin > 0)
    {
      octave_value f_arg = args(0);

      if (f_arg.is_string ())
        {
	  std::string name = f_arg.string_value ();

	  if (! error_state)
	    {
	      octave_value_list tmp_args = get_feval_args (args);

	      retval = feval (name, tmp_args, nargout);
	    }
	}
      else
	{
	  octave_function *fcn = f_arg.function_value ();

	  if (fcn)
	    {
	      octave_value_list tmp_args = get_feval_args (args);

	      retval = feval (fcn, tmp_args, nargout);
	    }
	}
    }

  return retval;
}

DEFUN (feval, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} feval (@var{name}, @dots{})\n\
Evaluate the function named @var{name}.  Any arguments after the first\n\
are passed on to the named function.  For example,\n\
\n\
@example\n\
feval (\"acos\", -1)\n\
     @result{} 3.1416\n\
@end example\n\
\n\
@noindent\n\
calls the function @code{acos} with the argument @samp{-1}.\n\
\n\
The function @code{feval} is necessary in order to be able to write\n\
functions that call user-supplied functions, because Octave does not\n\
have a way to declare a pointer to a function (like C) or to declare a\n\
special kind of variable that can be used to hold the name of a function\n\
(like @code{EXTERNAL} in Fortran).  Instead, you must refer to functions\n\
by name, and use @code{feval} to call them.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin > 0)
    retval = feval (args, nargout);
  else
    print_usage ();

  return retval;
}

octave_value_list
eval_string (const std::string& s, bool silent, int& parse_status, int nargout)
{
  octave_value_list retval;

  unwind_protect::begin_frame ("eval_string");

  unwind_protect_int (input_line_number);
  unwind_protect_int (current_input_column);
  unwind_protect_bool (get_input_from_eval_string);
  unwind_protect_bool (input_from_eval_string_pending);
  unwind_protect_bool (parser_end_of_input);
  unwind_protect_bool (line_editing);
  unwind_protect_str (current_eval_string);

  input_line_number = 1;
  current_input_column = 1;
  get_input_from_eval_string = true;
  input_from_eval_string_pending = true;
  parser_end_of_input = false;
  line_editing = false;

  current_eval_string = s;

  YY_BUFFER_STATE old_buf = current_buffer ();
  YY_BUFFER_STATE new_buf = create_buffer (0);

  unwind_protect::add (restore_input_buffer, old_buf);
  unwind_protect::add (delete_input_buffer, new_buf);

  switch_to_buffer (new_buf);

  do
    {
      reset_parser ();

      unwind_protect_ptr (global_command);

      // Do this with an unwind-protect cleanup function so that the
      // forced variables will be unmarked in the event of an
      // interrupt.
      symbol_table::scope_id scope = symbol_table::top_scope ();
      unwind_protect::add (symbol_table::unmark_forced_variables, &scope);

      parse_status = yyparse ();

      tree_statement_list *command_list = global_command;

      // Unmark forced variables.
      unwind_protect::run ();

      // Restore previous value of global_command.
      unwind_protect::run ();

      if (parse_status == 0)
        {
	  if (command_list)
	    {
	      tree_statement *stmt = 0;

	      if (command_list->length () == 1
		  && (stmt = command_list->front ())
		  && stmt->is_expression ())
		{
		  tree_expression *expr = stmt->expression ();

		  if (silent)
		    expr->set_print_flag (false);

		  bool do_bind_ans = false;

		  if (expr->is_identifier ())
		    {
		      tree_identifier *id
			= dynamic_cast<tree_identifier *> (expr);

		      do_bind_ans = (! id->is_variable ());
		    }
		  else
		    do_bind_ans = (! expr->is_assignment_expression ());

		  retval = expr->rvalue (nargout);

		  if (do_bind_ans && ! (error_state || retval.empty ()))
		    bind_ans (retval(0), expr->print_result ());

		  if (nargout == 0)
		    retval = octave_value_list ();
		}
	      else if (nargout == 0)
		command_list->accept (*current_evaluator);
	      else
		error ("eval: invalid use of statement list");

	      delete command_list;

	      command_list = 0;

	      if (error_state
		  || tree_return_command::returning
		  || tree_break_command::breaking
		  || tree_continue_command::continuing)
		break;
	    }
	  else if (parser_end_of_input)
	    break;
        }
    }
  while (parse_status == 0);

  unwind_protect::run_frame ("eval_string");

  return retval;
}

octave_value
eval_string (const std::string& s, bool silent, int& parse_status)
{
  octave_value retval;

  octave_value_list tmp = eval_string (s, silent, parse_status, 1);

  if (! tmp.empty ())
    retval = tmp(0);

  return retval;
}

static octave_value_list
eval_string (const octave_value& arg, bool silent, int& parse_status,
	     int nargout)
{
  std::string s = arg.string_value ();

  if (error_state)
    {
      error ("eval: expecting std::string argument");
      return octave_value (-1);
    }

  return eval_string (s, silent, parse_status, nargout);
}

DEFUN (eval, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} eval (@var{try}, @var{catch})\n\
Parse the string @var{try} and evaluate it as if it were an Octave\n\
program.  If that fails, evaluate the optional string @var{catch}.\n\
The string @var{try} is evaluated in the current context,\n\
so any results remain available after @code{eval} returns.\n\
\n\
The following example makes the variable @var{a} with the approximate\n\
value 3.1416 available.\n\
\n\
@example\n\
eval(\"a = acos(-1);\");\n\
@end example\n\
\n\
If an error occurs during the evaluation of @var{try} the @var{catch}\n\
string is evaluated, as the following example shows:\n\
\n\
@example\n\
eval ('error (\"This is a bad example\");',\n\
      'printf (\"This error occurred:\\n%s\\n\", lasterr ());');\n\
     @print{} This error occurred:\n\
        This is a bad example\n\
@end example\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin > 0)
    {
      unwind_protect::begin_frame ("Feval");

      if (nargin > 1)
	{
	  unwind_protect_int (buffer_error_messages);
	  buffer_error_messages++;
	}

      int parse_status = 0;

      octave_value_list tmp = eval_string (args(0), nargout > 0,
					   parse_status, nargout);

      if (nargin > 1 && (parse_status != 0 || error_state))
	{
	  error_state = 0;

	  // Set up for letting the user print any messages from
	  // errors that occurred in the first part of this eval().

	  buffer_error_messages--;

	  tmp = eval_string (args(1), nargout > 0, parse_status, nargout);

	  if (nargout > 0)
	    retval = tmp;
	}
      else if (nargout > 0)
	retval = tmp;

      unwind_protect::run_frame ("Feval");
    }
  else
    print_usage ();

  return retval;
}

/*

%% test/octave.test/eval/eval-1.m
%!#test
%! x = 1;
%! assert(eval ("x"),1);

%% test/octave.test/eval/eval-2.m
%!test
%! x = 1;
%! assert(eval ("x;"));

%% test/octave.test/eval/eval-3.m
%!test
%! x = 1;
%! assert(eval ("x;"),1);

%% FIXME
%% Disable this test as adding the ";" is redundant with eval-1 and
%% in any case is a syntax error with assert
%% test/octave.test/eval/eval-4.m
%!#test
%! x = 1;
%! assert(eval ("x");,1);

%% test/octave.test/eval/eval-5.m
%!test
%! eval ("flipud = 2;");
%! assert(flipud,2);

%% test/octave.test/eval/eval-6.m
%!function y = f ()
%!  eval ("flipud = 2;");
%!  y = flipud;
%!test
%! assert(f,2);

%% test/octave.test/eval/eval-7.m
%!#test
%! eval ("x = 1");
%! assert(x,1);

%% test/octave.test/eval/eval-8.m
%!test
%! eval ("x = 1;")
%! assert(x,1);

%% test/octave.test/eval/eval-9.m
%!test
%! eval ("x = 1;");
%! assert(x,1);

%% test/octave.test/eval/eval-10.m
%!#test
%! eval ("x = 1")
%! assert(x,1);

%% test/octave.test/eval/eval-11.m
%!test
%! x = 1;
%! y = eval ("x");
%! assert(y,1);

%% test/octave.test/eval/eval-12.m
%!test
%! x = 1;
%! y = eval ("x;");
%! assert(y,1);

%% test/octave.test/eval/eval-13.m
%!test
%! x = 1;
%! y = eval ("x;");
%! assert(y,1);

%% test/octave.test/eval/eval-14.m
%!test
%! x = 1;
%! y = eval ("x");
%! assert(y,1);

*/

DEFUN (assignin, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} assignin (@var{context}, @var{varname}, @var{value})\n\
Assign @var{value} to @var{varname} in context @var{context}, which\n\
may be either @code{\"base\"} or @code{\"caller\"}.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin == 3)
    {
      std::string context = args(0).string_value ();

      if (! error_state)
        {
	  unwind_protect::begin_frame ("Fassignin");

	  if (context == "caller")
	    octave_call_stack::goto_caller_frame ();
	  else if (context == "base")
	    octave_call_stack::goto_base_frame ();
	  else
	    error ("assignin: context must be \"caller\" or \"base\"");

	  if (! error_state)
	    {
	      unwind_protect::add (octave_call_stack::unwind_pop);

	      std::string nm = args(1).string_value ();

	      if (! error_state)
		{
		  if (valid_identifier (nm))
		    symbol_table::varref (nm) = args(2);
		  else
		    error ("assignin: invalid variable name");
		}
	      else
		error ("assignin: expecting variable name as second argument");
	    }

	  unwind_protect::run_frame ("Fassignin");
	}
      else
        error ("assignin: expecting string as first argument");
    }
  else
    print_usage ();

  return retval;
}

DEFUN (evalin, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} evalin (@var{context}, @var{try}, @var{catch})\n\
Like @code{eval}, except that the expressions are evaluated in the\n\
context @var{context}, which may be either @code{\"caller\"} or\n\
@code{\"base\"}.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin > 1)
    {
      std::string context = args(0).string_value ();

      if (! error_state)
        {
	  unwind_protect::begin_frame ("Fevalin");

	  if (context == "caller")
	    octave_call_stack::goto_caller_frame ();
	  else if (context == "base")
	    octave_call_stack::goto_base_frame ();
	  else
	    error ("evalin: context must be \"caller\" or \"base\"");

	  if (! error_state)
	    {
	      unwind_protect::add (octave_call_stack::unwind_pop);

	      if (nargin > 2)
	        {
		  unwind_protect_int (buffer_error_messages);
		  buffer_error_messages++;
		}

	      int parse_status = 0;

	      octave_value_list tmp = eval_string (args(1), nargout > 0,
						   parse_status, nargout);

	      if (nargout > 0)
		retval = tmp;

	      if (nargin > 2 && (parse_status != 0 || error_state))
		{
		  error_state = 0;

		  // Set up for letting the user print any messages from
		  // errors that occurred in the first part of this eval().

		  buffer_error_messages--;

		  tmp = eval_string (args(2), nargout > 0,
				     parse_status, nargout);

		  retval = (nargout > 0) ? tmp : octave_value_list ();
		}
	    }

	  unwind_protect::run_frame ("Fevalin");
	}
      else
        error ("evalin: expecting string as first argument");
    }
  else
    print_usage ();

  return retval;
}

DEFUN (__parser_debug_flag__, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {@var{old_val} =} __parser_debug_flag__ (@var{new_val}))\n\
Undocumented internal function.\n\
@end deftypefn")
{
  octave_value retval;

  bool debug_flag = octave_debug;

  retval = set_internal_variable (debug_flag, args, nargout,
           			  "__parser_debug_flag__");

  octave_debug = debug_flag;

  return retval;
}

/*
;;; Local Variables: ***
;;; mode: text ***
;;; End: ***
*/

