# C++ GLR skeleton for Bison

# Copyright (C) 2002-2013 Free Software Foundation, Inc.

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


# This skeleton produces a C++ class that encapsulates a C glr parser.
# This is in order to reduce the maintenance burden.  The glr.c
# skeleton is clean and pure enough so that there are no real
# problems.  The C++ interface is the same as that of lalr1.cc.  In
# fact, glr.c can replace yacc.c without the user noticing any
# difference, and similarly for glr.cc replacing lalr1.cc.
#
# The passing of parse-params
#
#   The additional arguments are stored as members of the parser
#   object, yyparser.  The C routines need to carry yyparser
#   throughout the C parser; that's easy: make yyparser an
#   additional parse-param.  But because the C++ skeleton needs to
#   know the "real" original parse-param, we save them
#   (b4_parse_param_orig).  Note that b4_parse_param is overquoted
#   (and c.m4 strips one level of quotes).  This is a PITA, and
#   explains why there are so many levels of quotes.
#
# The locations
#
#   We use location.cc just like lalr1.cc, but because glr.c stores
#   the locations in a union, the position and location classes
#   must not have a constructor.  Therefore, contrary to lalr1.cc, we
#   must not define "b4_location_constructors".  As a consequence the
#   user must initialize the first positions (in particular the
#   filename member).

# We require a pure interface.
m4_define([b4_locations_flag], [1])
# FIXME: this is possible with variants, not without.
b4_variant_if([m4_define([b4_location_constructors])])
m4_define([b4_pure_flag],      [1])

m4_include(b4_pkgdatadir/[c++.m4])
b4_bison_locations_if([m4_include(b4_pkgdatadir/[location.cc])])
b4_variant_if([m4_include(b4_pkgdatadir/[variant.hh])])

m4_define([b4_parser_class_name],
          [b4_percent_define_get([[parser_class_name]])])

# Save the parse parameters.
m4_define([b4_parse_param_orig], m4_defn([b4_parse_param]))

# b4_parse_param_wrap
# -------------------
# New ones.
m4_ifset([b4_parse_param],
[m4_define([b4_parse_param_wrap],
           [[b4_namespace_ref::b4_parser_class_name[& yyparser], [[yyparser]]],]
m4_defn([b4_parse_param]))],
[m4_define([b4_parse_param_wrap],
           [[b4_namespace_ref::b4_parser_class_name[& yyparser], [[yyparser]]]])
])

# b4_lex_wrapper_formals
# ----------------------
# The yylex_wrapper formal arguments.
# Yes, this is quite ugly...
m4_define([b4_lex_wrapper_formals],
[[[[yys_type *yylvalp]], [[yylvalp]]][]dnl
b4_locations_if([, [[location_type *yyllocp], [yyllocp]]])
m4_ifdef([b4_lex_param], [, ]b4_lex_param)])


# b4_lex
# ------
# Call yylex.
#m4_define([b4_lex],
#[b4_function_call([b4_token_ctor_if(b4_namespace_ref[::yylex_wrapper],
                                    [yylex])],
                  [int], b4_lex_formals)])
# b4_lex
# ------
# Call yylex.
m4_define([b4_lex],
[b4_token_ctor_if(
[b4_function_call(b4_namespace_ref[::yylex_wrapper],
                  [symbol_type], b4_lex_formals)],
[b4_function_call([yylex], [int],
                  [b4_api_PREFIX[STYPE*], [&yyla.value]][]dnl
b4_locations_if([, [[location*], [&yyla.location]]])dnl
m4_ifdef([b4_lex_param], [, ]b4_lex_param))])])


]b4_function_define([yy_symbol_print],
    [static void],
    [[std::ostream& ],      []],
    [[int yytype],  [yytype]],
    [[const ]b4_namespace_ref::b4_parser_class_name[::semantic_type *yyvaluep],
                    [yyvaluep]][]dnl
b4_locations_if([,
    [[const ]b4_namespace_ref::b4_parser_class_name[::location_type *yylocationp],
                    [yylocationp]]]),
    b4_parse_param)[
{
]b4_parse_param_use[]dnl
[  yyparser.yy_symbol_print_ (yytype, yyvaluep]b4_locations_if([, yylocationp])[);
}
]])[

# Hijack the initial action to initialize the locations.
]b4_bison_locations_if([m4_define([b4_initial_action],
[yylloc.initialize ();]m4_ifdef([b4_initial_action], [
m4_defn([b4_initial_action])]))])[

# Hijack the post prologue to insert early definition of YYLLOC_DEFAULT
# and declaration of yyerror.
]m4_append([b4_post_prologue],
[b4_syncline([@oline@], [@ofile@])[
]b4_yylloc_default_define[
]b4_function_declare([yyerror],
    [static void],b4_locations_if([
    [[const ]b4_namespace_ref::b4_parser_class_name[::location_type *yylocationp],
                        [yylocationp]],])
    b4_parse_param,
    [[const char* msg], [msg]])[

]b4_token_ctor_if([
]b4_namespace_open[
  // A wrapper around a symbol_type returning yylex, to an old style yylex.
  b4_function_declare([yylex_wrapper], [static ]b4_parser_class_name[::symbol_type], b4_lex_formals)
]b4_namespace_close[
])
])

#undef yynerrs
#undef yychar
#undef yylval]b4_locations_if([
#undef yylloc])

m4_if(b4_prefix, [yy], [],
[[/* Substitute the variable and function names.  */
#define yyparse ]b4_prefix[parse
#define yylex   ]b4_prefix[lex
#define yyerror ]b4_prefix[error
#define yydebug ]b4_prefix[debug
]]b4_pure_if([], [[
#define yylval  ]b4_prefix[lval
#define yychar  ]b4_prefix[char
#define yynerrs ]b4_prefix[nerrs]b4_locations_if([[
#define yylloc  ]b4_prefix[lloc]])]))

# Hijack the epilogue to define implementations (yyerror, parser member
# functions etc.).
m4_append([b4_epilogue],
[b4_syncline([@oline@], [@ofile@])[

/*------------------.
| Report an error.  |
`------------------*/

]b4_function_define([yyerror],
    [static void],b4_locations_if([
    [[const ]b4_namespace_ref::b4_parser_class_name[::location_type *yylocationp],
                        [yylocationp]],])
    b4_parse_param,
    [[const char* msg], [msg]])[
{
]b4_parse_param_use[]dnl
[  yyparser.error (]b4_locations_if([[*yylocationp, ]])[msg);
}

]b4_namespace_open[
]b4_token_ctor_if([[
  // A wrapper around a symbol_type returning yylex, to an old style yylex.
]b4_function_define([yylex_wrapper],
                    [static ]b4_namespace_ref::b4_parser_class_name[::symbol_type],
                    b4_lex_formals)[
  {
    ]b4_namespace_ref::b4_parser_class_name[::symbol_type s = ]dnl
b4_function_call([yylex], [], m4_unquote(b4_lex_param))[;
  ]b4_symbol_variant([[s.type]], [[(*yylvalp)]],
                     [build])
   b4_symbol_variant([[s.type]], [[(*yylvalp)]],
                     [swap], [s.get_value()])b4_locations_if([
    std::swap (*yyllocp, s.location);])[
    return s;
  }]])[

]dnl In this section, the parse params are the original parse_params.
m4_pushdef([b4_parse_param], m4_defn([b4_parse_param_orig]))dnl
[  /// Build a parser object.
  ]b4_parser_class_name::b4_parser_class_name[ (]b4_parse_param_decl[)]m4_ifset([b4_parse_param], [
    :])[
    : yystack_(this)
#if ]b4_api_PREFIX[DEBUG
    ]m4_ifset([b4_parse_param], [  ], [ ,])[yycdebug_ (&std::cerr)]m4_ifset([b4_parse_param], [,])[
#endif]b4_parse_param_cons[
  {
  }

  ]b4_parser_class_name::~b4_parser_class_name[ ()
  {
  }

]b4_token_ctor_if([], [b4_yytranslate_define
b4_public_types_define])[

]m4_popdef([b4_parse_param])dnl
b4_namespace_close
])


# Let glr.c (and b4_shared_declarations) believe that the user
# arguments include the parser itself.
m4_pushdef([b4_parse_param], m4_defn([b4_parse_param_wrap]))










////////////////// GLR.C //////////////






## ---------------- ##
## Default values.  ##
## ---------------- ##

# Stack parameters.
m4_define_default([b4_stack_depth_max], [10000])
m4_define_default([b4_stack_depth_init],  [200])



## ------------------------ ##
## Pure/impure interfaces.  ##
## ------------------------ ##

b4_define_flag_if([pure])
# If glr.cc is including this file and thus has already set b4_pure_flag,
# do not change the value of b4_pure_flag, and do not record a use of api.pure.
m4_ifndef([b4_pure_flag],
[b4_percent_define_default([[api.pure]], [[false]])
 m4_define([b4_pure_flag],
           [b4_percent_define_flag_if([[api.pure]], [[1]], [[0]])])])

# b4_user_formals_no_comma
# ---------------
# The possible parse-params formal arguments, NOT preceded by a comma.
m4_define([b4_user_formals_no_comma], [])
# [m4_ifset([b4_parse_param], [b4_formals(b4_parse_param)])])

# b4_user_formals
# ---------------
# The possible parse-params formal arguments preceded by a comma.
#
# This is not shared with yacc.c in c.m4 because  GLR relies on ISO C
# formal argument declarations.
m4_define([b4_user_formals],
[m4_ifset([b4_parse_param], [, b4_user_formals_no_comma])])



# b4_yyerror_args
# ---------------
# Optional effective arguments passed to yyerror: user args plus yylloc, and
# a trailing comma.
m4_define([b4_yyerror_args],
[b4_pure_if([b4_locations_if([yylocp, ])])dnl
m4_ifset([b4_parse_param], [b4_args(b4_parse_param), ])])


# b4_lyyerror_args
# ----------------
# Same as above, but on the lookahead, hence &yylloc instead of yylocp.
m4_define([b4_lyyerror_args],
[b4_pure_if([b4_locations_if([&yylloc, ])])dnl
m4_ifset([b4_parse_param], [b4_args(b4_parse_param), ])])


# b4_pure_args
# ------------
# Same as b4_yyerror_args, but with a leading comma.
m4_define([b4_pure_args],
[b4_pure_if([b4_locations_if([, yylocp])])])


# b4_lpure_args
# -------------
# Same as above, but on the lookahead, hence &yylloc instead of yylocp.
m4_define([b4_lpure_args],
[b4_pure_if([b4_locations_if([, &yylloc])])])



# b4_pure_formals
# ---------------
# Arguments passed to yyerror: user formals plus yylocp with leading comma.
m4_define([b4_pure_formals],
[b4_pure_if([b4_locations_if([, location_type *yylocp])])])


# b4_locuser_formals(LOC = yylocp)
# --------------------------------
m4_define([b4_locuser_formals],
[b4_locations_if([, location_type *m4_default([$1], [yylocp])])])


# b4_locuser_args(LOC = yylocp)
# -----------------------------
m4_define([b4_locuser_args],
[b4_locations_if([, m4_default([$1], [yylocp])])])



## ----------------- ##
## Semantic Values.  ##
## ----------------- ##


# b4_lhs_value([TYPE])
# --------------------
# Expansion of $<TYPE>$.
m4_define([b4_lhs_value],
[b4_symbol_value([(*yyvalp)], [$1])])


# b4_rhs_data(RULE-LENGTH, NUM)
# -----------------------------
# Expand to the semantic stack place that contains value and location
# of symbol number NUM in a rule of length RULE-LENGTH.
m4_define([b4_rhs_data],
[yyargs@{$2@}])
# [((yy_glr_stack_item const *)yyvsp)@{YYFILL (b4_subtract([$2], [$1]))@}.yystate])

# We temporarily allow changes in the stack as we often transfer
# ownership bw lhs and rhs, e.g. std::swap($$, $1).
# m4_define([b4_rhs_data],
# [yyvsp@{YYFILL (b4_subtract([$2], [$1]))@}.yystate])

# b4_rhs_value(RULE-LENGTH, NUM, [TYPE])
# --------------------------------------
# Expansion of $<TYPE>NUM, where the current rule has RULE-LENGTH
# symbols on RHS.
m4_define([b4_rhs_value],
[b4_symbol_value([b4_rhs_data([$1], [$2])->get_value()], [$3])])

# [b4_symbol_value([b4_rhs_data([$1], [$2]).yysemantics.yysval], [$3])])



## ----------- ##
## Locations.  ##
## ----------- ##

# b4_lhs_location()
# -----------------
# Expansion of @$.
m4_define([b4_lhs_location],
[(*yylocp)])


# b4_rhs_location(RULE-LENGTH, NUM)
# ---------------------------------
# Expansion of @NUM, where the current rule has RULE-LENGTH symbols
# on RHS.
m4_define([b4_rhs_location],
[(b4_rhs_data([$1], [$2]).yyloc)])


## --------------------- ##
## Shared declarations.  ##
## --------------------- ##

# b4_shared_declarations
# ----------------------
# Declaration that might either go into the header (if --defines)
# or open coded in the parser body.
m4_define([b4_shared_declarations],
[m4_pushdef([b4_parse_param], m4_defn([b4_parse_param_orig]))dnl
b4_percent_code_get([[requires]])[

#include <stdexcept>
]b4_parse_assert_if([#include <cassert>])[
#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>]b4_defines_if([
b4_bison_locations_if([[#include "location.hh"]])])[

]b4_variant_if([b4_variant_includes])[
]b4_YYDEBUG_define[

]b4_namespace_open[
]b4_defines_if([],
[b4_bison_locations_if([b4_position_define
b4_location_define])])[

]b4_variant_if([b4_variant_define])[

typedef enum { yyok, yyaccept, yyabort, yyerr } YYRESULTTAG;
class ]b4_parser_class_name[;
]b4_attribute_define[

]m4_include(b4_pkgdatadir/[glr_cc/fwd.hh])[
]m4_include(b4_pkgdatadir/[glr_cc/glr_semantic.hh])[
]m4_include(b4_pkgdatadir/[glr_cc/glr_state.hh])[
]m4_include(b4_pkgdatadir/[glr_cc/glr_stack.hh])[
]m4_include(b4_pkgdatadir/[glr_cc/glr.hh])[

]b4_token_ctor_if([b4_yytranslate_define
b4_public_types_define])[

]dnl Redirections for glr.c.
b4_percent_define_flag_if([[global_tokens_and_yystype]],
[b4_token_defines])
[

]b4_namespace_close
b4_function_declare(b4_prefix[parse], [int], b4_parse_param_wrap)
b4_percent_code_get([[provides]])
m4_popdef([b4_parse_param])dnl
])


## -------------- ##
## Output files.  ##
## -------------- ##

b4_defines_if(
[b4_output_begin([b4_spec_defines_file])
b4_copyright([Skeleton interface for Bison GLR parsers in C++],
             [2002-2013])[

// C++ GLR parser skeleton written by Akim Demaille.

]b4_cpp_guard_open([b4_spec_defines_file])[
]b4_shared_declarations[
]b4_cpp_guard_close([b4_spec_defines_file])[
]b4_output_end()])

b4_output_begin([b4_parser_file_name])
b4_copyright([Skeleton implementation for Bison GLR parsers in C],
             [2002-2013])[

/* C GLR parser skeleton written by Paul Hilfinger.  */

]b4_identification

b4_percent_code_get([[top]])[
]m4_if(b4_api_prefix, [yy], [],
[[/* Substitute the type names.  */
#define YYSTYPE ]b4_api_PREFIX[STYPE]b4_locations_if([[
#define YYLTYPE ]b4_api_PREFIX[LTYPE]])])[
]m4_if(b4_prefix, [yy], [],
[[/* Substitute the variable and function names.  */
#define yyparse ]b4_prefix[parse
#define yylex   ]b4_prefix[lex
#define yyerror ]b4_prefix[error
#define yydebug ]b4_prefix[debug
#define yylval  ]b4_prefix[lval
#define yychar  ]b4_prefix[char
#define yynerrs ]b4_prefix[nerrs]b4_locations_if([[
#define yylloc  ]b4_prefix[lloc]])])[

/* First part of user declarations.  */
]b4_user_pre_prologue[

]b4_null_define[

]b4_defines_if([[#include "@basename(]b4_spec_defines_file[@)"]],
               [b4_shared_declarations])[

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE ]b4_error_verbose_if([1], [0])[
#endif

#ifndef ]b4_api_PREFIX[STYPE
# define ]b4_api_PREFIX[STYPE ]b4_namespace_ref[::]b4_parser_class_name[::semantic_type
#endif
#ifndef ]b4_api_PREFIX[LTYPE
# define ]b4_api_PREFIX[LTYPE ]b4_namespace_ref[::]b4_parser_class_name[::location_type
#endif
]b4_variant_if([], [/* Default (constant) value used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template,
   here we set the default value of $$ to a zeroed-out value.
   Since the default value is undefined, this behavior is
   technically correct.  */
static YYSTYPE yyval_default;])[]b4_locations_if([[
static YYLTYPE yyloc_default][]b4_yyloc_default;])[

/* Copy the second part of user declarations.  */
]b4_user_post_prologue
b4_percent_code_get[]dnl

[
#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#define YYSIZEMAX ((size_t) -1)


]b4_attribute_define[

#ifndef YYASSERT
# define YYASSERT(Condition) ((void) ((Condition) || (abort (), 0)))
#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  ]b4_final_state_number[
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   ]b4_last[

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  ]b4_tokens_number[
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  ]b4_nterms_number[
/* YYNRULES -- Number of rules.  */
#define YYNRULES  ]b4_rules_number[
/* YYNRULES -- Number of states.  */
#define YYNSTATES  ]b4_states_number[
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS ]b4_r2_max[
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT ]b4_max_left_semantic_context[

/* YYTRANSLATE(X) -- Bison symbol number corresponding to X.  */
#define YYUNDEFTOK  ]b4_undef_token_number[
#define YYMAXUTOK   ]b4_user_token_number_max[

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

]b4_namespace_open[

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const ]b4_int_type_for([b4_translate])[ yytranslate[] =
{
  ]b4_translate[
};

#if ]b4_api_PREFIX[DEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const ]b4_int_type_for([b4_rline])[ yyrline[] =
{
  ]b4_rline[
};
#endif

#if ]b4_api_PREFIX[DEBUG || YYERROR_VERBOSE || ]b4_token_table_flag[
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  ]b4_tname[
};
#endif

#define YYPACT_NINF ]b4_pact_ninf[
#define YYTABLE_NINF ]b4_table_ninf[

]b4_parser_tables_define[

/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none).  */
static const ]b4_int_type_for([b4_dprec])[ yydprec[] =
{
  ]b4_dprec[
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM.  */
static const ]b4_int_type_for([b4_merger])[ yymerger[] =
{
  ]b4_merger[
};

/* YYIMMEDIATE[RULE-NUM] -- True iff rule #RULE-NUM is not to be deferred, as
   in the case of predicates.  */
static const bool yyimmediate[] =
{
  ]b4_immediate[
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const ]b4_int_type_for([b4_conflict_list_heads])[ yyconflp[] =
{
  ]b4_conflict_list_heads[
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
]dnl Do not use b4_int_type_for here, since there are places where
dnl pointers onto yyconfl are taken, whose type is "short int *".
dnl We probably ought to introduce a type for confl.
[static const short int yyconfl[] =
{
  ]b4_conflicting_rules[
};

]b4_namespace_close[
/* Error token number */
#define YYTERROR 1

]b4_locations_if([[
]b4_yylloc_default_define[
# define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
]])[

]m4_if(b4_prefix[], [yy], [],
[#define b4_prefix[]nerrs yynerrs
#define b4_prefix[]char yychar
#define b4_prefix[]lval yylval
#define b4_prefix[]lloc yylloc])[


#define yydebug() yyparser.yydebug()
#define yy_symbol_print_ yyparser.yy_symbol_print_
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#undef yydebug
#undef yy_symbol_print_
]m4_include(b4_pkgdatadir/[glr_cc/glr_semantic.cc])[
]m4_include(b4_pkgdatadir/[glr_cc/glr_stack.cc])[
]m4_include(b4_pkgdatadir/[glr_cc/glr_state.cc])[
]m4_include(b4_pkgdatadir/[glr_cc/glr.cc])[





////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////////////////////////////CODE STARTS HERE//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////////////////////////////CODE STARTS HERE//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////////////////////////////CODE STARTS HERE//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////















# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static size_t
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      size_t yyn = 0;
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
    return strlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif




#undef yylval
#undef yychar
#undef yynerrs]b4_locations_if([
#undef yylloc])

m4_if(b4_prefix, [yy], [],
[[/* Substitute the variable and function names.  */
#define yyparse ]b4_prefix[parse
#define yylex   ]b4_prefix[lex
#define yyerror ]b4_prefix[error
#define yylval  ]b4_prefix[lval
#define yychar  ]b4_prefix[char
#define yydebug ]b4_prefix[debug
#define yynerrs ]b4_prefix[nerrs]b4_locations_if([[
#define yylloc  ]b4_prefix[lloc]])])[

]b4_epilogue[]dnl
b4_output_end()

# glr.cc produces its own header.
m4_if(b4_skeleton, ["glr.c"],
[b4_defines_if(
[b4_output_begin([b4_spec_defines_file])
b4_copyright([Skeleton interface for Bison GLR parsers in C],
             [2002-2013])[

]b4_cpp_guard_open([b4_spec_defines_file])[
]b4_shared_declarations[
]b4_cpp_guard_close([b4_spec_defines_file])[
]b4_output_end()
])])
