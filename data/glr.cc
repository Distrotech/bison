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
[b4_pure_if([[[[YYSTYPE *yylvalp]], [[yylvalp]]][]dnl
b4_locations_if([, [[YYLTYPE *yyllocp], [yyllocp]]])])dnl
m4_ifdef([b4_lex_param], [, ]b4_lex_param)])


# b4_lex
# ------
# Call yylex.
m4_define([b4_lex],
[b4_function_call([b4_token_ctor_if(b4_namespace_ref[::yylex_wrapper],
                                    [yylex])],
                  [int], b4_lex_formals)])


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
#define YYRHSLOC(Rhs, K) ((Rhs)[K].yystate.yyloc)
]b4_function_declare([yyerror],
    [static void],b4_locations_if([
    [[const ]b4_namespace_ref::b4_parser_class_name[::location_type *yylocationp],
                        [yylocationp]],])
    b4_parse_param,
    [[const char* msg], [msg]])[

]b4_token_ctor_if([
]b4_namespace_open[
  // A wrapper around a symbol_type returning yylex, to an old style yylex.
  b4_function_declare([yylex_wrapper], [static int], b4_lex_formals)
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
                    [static int],
                    b4_lex_formals)[
  {
    ]b4_namespace_ref::b4_parser_class_name[::symbol_type s = ]dnl
b4_function_call([yylex], [], m4_unquote(b4_lex_param))[;
  ]b4_symbol_variant([[s.type]], [[(*yylvalp)]],
                     [build])
   b4_symbol_variant([[s.type]], [[(*yylvalp)]],
                     [swap], [s.value])b4_locations_if([
    std::swap (*yyllocp, s.location);])[
    return s.token ();
  }]])[

]dnl In this section, the parse params are the original parse_params.
m4_pushdef([b4_parse_param], m4_defn([b4_parse_param_orig]))dnl
[  /// Build a parser object.
  ]b4_parser_class_name::b4_parser_class_name[ (]b4_parse_param_decl[)]m4_ifset([b4_parse_param], [
    :])[
#if ]b4_api_PREFIX[DEBUG
    ]m4_ifset([b4_parse_param], [  ], [ :])[yycdebug_ (&std::cerr)]m4_ifset([b4_parse_param], [,])[
#endif]b4_parse_param_cons[
  {
  }

  ]b4_parser_class_name::~b4_parser_class_name[ ()
  {
  }

  int
  ]b4_parser_class_name[::parse ()
  {
    return ::yyparse (*this]b4_user_args[);
  }

]b4_token_ctor_if([], [b4_yytranslate_define
b4_public_types_define])[

#if ]b4_api_PREFIX[DEBUG
  /*--------------------.
  | Print this symbol.  |
  `--------------------*/

  inline void
  ]b4_parser_class_name[::yy_symbol_value_print_ (int yytype,
                           const semantic_type* yyvaluep]b4_locations_if([[,
                           const location_type* yylocationp]])[)
  {]b4_locations_if([[
    YYUSE (yylocationp);]])[
    YYUSE (yyvaluep);
    std::ostream& yyoutput = debug_stream ();
    std::ostream& yyo = yyoutput;
    YYUSE (yyo);
    ]b4_symbol_actions([printer])[
  }


  void
  ]b4_parser_class_name[::yy_symbol_print_ (int yytype,
                           const semantic_type* yyvaluep]b4_locations_if([[,
                           const location_type* yylocationp]])[)
  {
    *yycdebug_ << (yytype < YYNTOKENS ? "token" : "nterm")
               << ' ' << yytname[yytype] << " ("]b4_locations_if([[
               << *yylocationp << ": "]])[;
    yy_symbol_value_print_ (yytype, yyvaluep]b4_locations_if([[, yylocationp]])[);
    *yycdebug_ << ')';
  }

  std::ostream&
  ]b4_parser_class_name[::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  ]b4_parser_class_name[::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  ]b4_parser_class_name[::debug_level_type
  ]b4_parser_class_name[::debug_level () const
  {
    return yydebug;
  }

  void
  ]b4_parser_class_name[::set_debug_level (debug_level_type l)
  {
    // Actually, it is yydebug which is really used.
    yydebug = l;
  }

#endif
]m4_popdef([b4_parse_param])dnl
b4_namespace_close
])


# Let glr.c (and b4_shared_declarations) believe that the user
# arguments include the parser itself.
m4_pushdef([b4_parse_param], m4_defn([b4_parse_param_wrap]))










////////////////// GLR.C //////////////






# When glr.c is used from glr.cc, it has provided the version of
# b4_symbol_value and b4_symbol_value_template that are needed.  c.m4
# provides other definitions.  So save and restore the C++
# definitions.

  m4_pushdef([b4_symbol_value])
  m4_pushdef([b4_symbol_value_template])


  m4_popdef([b4_symbol_value_template])
  m4_popdef([b4_symbol_value])

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
m4_define([b4_user_formals_no_comma],
[m4_ifset([b4_parse_param], [b4_formals(b4_parse_param)])])

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
[b4_pure_if([b4_locations_if([, yylocp])])[]b4_user_args])


# b4_lpure_args
# -------------
# Same as above, but on the lookahead, hence &yylloc instead of yylocp.
m4_define([b4_lpure_args],
[b4_pure_if([b4_locations_if([, &yylloc])])[]b4_user_args])



# b4_pure_formals
# ---------------
# Arguments passed to yyerror: user formals plus yylocp with leading comma.
m4_define([b4_pure_formals],
[b4_pure_if([b4_locations_if([, YYLTYPE *yylocp])])[]b4_user_formals])


# b4_locuser_formals(LOC = yylocp)
# --------------------------------
m4_define([b4_locuser_formals],
[b4_locations_if([, YYLTYPE *m4_default([$1], [yylocp])])[]b4_user_formals])


# b4_locuser_args(LOC = yylocp)
# -----------------------------
m4_define([b4_locuser_args],
[b4_locations_if([, m4_default([$1], [yylocp])])[]b4_user_args])



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
[((yy_glr_stack_item const *)yyvsp)@{YYFILL (b4_subtract([$2], [$1]))@}.yystate])

# We temporarily allow changes in the stack as we often transfer
# ownership bw lhs and rhs, e.g. std::swap($$, $1).
m4_define([b4_rhs_data],
[yyvsp@{YYFILL (b4_subtract([$2], [$1]))@}.yystate])

# b4_rhs_value(RULE-LENGTH, NUM, [TYPE])
# --------------------------------------
# Expansion of $<TYPE>NUM, where the current rule has RULE-LENGTH
# symbols on RHS.
m4_define([b4_rhs_value],
[b4_symbol_value([b4_rhs_data([$1], [$2]).yysemantics.yysval], [$3])])



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
# define YYRHSLOC(Rhs, K) ((Rhs)[K].yystate.yyloc)
]])[

]#undef yynerrs
#define yynerrs (yystackp->yyerrcnt)
#undef yychar
#define yychar (yystackp->yyrawchar)
#undef yylval
#define yylval (yystackp->yyval)
#undef yylloc
#define yylloc (yystackp->yyloc)
m4_if(b4_prefix[], [yy], [],
[#define b4_prefix[]nerrs yynerrs
#define b4_prefix[]char yychar
#define b4_prefix[]lval yylval
#define b4_prefix[]lloc yylloc])[


]m4_include(b4_pkgdatadir/[glr_cc/glr_stack.cc])[





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

/** State numbers, as in LALR(1) machine */
typedef int yy_state_num;

/** Rule numbers, as in LALR(1) machine */
typedef int yy_rule_num;

/** Grammar symbol */
typedef int yy_symbol;

]m4_include(b4_pkgdatadir/[glr_cc/glr_state.cc])[
/** Item references, as in LALR(1) machine */
typedef short int yy_item_num;

typedef struct yy_glr_state yy_glr_state;
typedef struct yy_glr_stateSet yy_glr_stateSet;
typedef struct yy_semantic_option yy_semantic_option;
typedef ]b4_variant_if([struct], [union])[ yy_glr_stack_item yy_glr_stack_item;
typedef struct yy_glr_stack yy_glr_stack;


]m4_include(b4_pkgdatadir/[glr_cc/glr_semantic.cc])[


/** Type of the items in the GLR stack.  The yyisState field
 *  indicates which item of the union is valid.  */
]b4_variant_if([struct], [union])[ yy_glr_stack_item {
  yy_glr_state yystate;
  yy_semantic_option yyoption;
};

struct yy_glr_stack {
  int yyerrState;
]b4_locations_if([[  /* To compute the location of the error token.  */
  yy_glr_stack_item yyerror_range[3];]])[
]b4_pure_if(
[
  int yyerrcnt;
  int yyrawchar;
  YYSTYPE yyval;]b4_locations_if([[
  YYLTYPE yyloc;]])[
])[
  YYJMP_BUF yyexception_buffer;
  yy_glr_stack_item* yyitems;
  yy_glr_stack_item* yynextFree;
  size_t yyspaceLeft;
  yy_glr_state* yysplitPoint;
  yy_glr_state* yylastDeleted;
  yy_glr_stateSet yytops;
};

#if YYSTACKEXPANDABLE
static void yyexpandGLRStack (yy_glr_stack* yystackp);
#endif

static _Noreturn void
yyFail (yy_glr_stack* yystackp]b4_pure_formals[, const char* yymsg)
{
  if (yymsg != YY_NULLPTR)
    yyerror (]b4_yyerror_args[yymsg);
  YYLONGJMP (yystackp->yyexception_buffer, 1);
}

static _Noreturn void
yyMemoryExhausted (yy_glr_stack* yystackp)
{
  YYLONGJMP (yystackp->yyexception_buffer, 2);
}

#if ]b4_api_PREFIX[DEBUG || YYERROR_VERBOSE
/** A printable representation of TOKEN.  */
static inline const char*
yytokenName (yy_symbol yytoken)
{
  if (yytoken == YYEMPTY)
    return "";

  return yytname[yytoken];
}
#endif
/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@@$).  Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT.  */
static YYRESULTTAG
yyuserAction (yy_rule_num yyn, size_t yyrhslen, yy_glr_stack_item* yyvsp,
              yy_glr_stack* yystackp,
              YYSTYPE* yyvalp]b4_locuser_formals[)
{
  bool yynormal YY_ATTRIBUTE_UNUSED = (yystackp->yysplitPoint == YY_NULLPTR);
  //  std::cerr << "yyuserAction" << std::endl;
  int yylow;
]b4_parse_param_use([yyvalp], [yylocp])dnl
[  YYUSE (yyrhslen);
# undef yyerrok
# define yyerrok (yystackp->yyerrState = 0)
# undef YYACCEPT
# define YYACCEPT return yyaccept
# undef YYABORT
# define YYABORT return yyabort
# undef YYERROR
# define YYERROR return yyerrok, yyerr
# undef YYRECOVERING
# define YYRECOVERING() (yystackp->yyerrState != 0)
# undef yyclearin
# define yyclearin (yychar = YYEMPTY)
# undef YYFILL
# define YYFILL(N) yyfill (yyvsp, &yylow, N, yynormal)
# undef YYBACKUP
# define YYBACKUP(Token, Value)                                              \
  return yyerror (]b4_yyerror_args[YY_("syntax error: cannot back up")),     \
         yyerrok, yyerr

  yylow = 1;]b4_variant_if([
    /* Variants are always initialized to an empty instance of the
       correct type. The default $$=$1 action is NOT applied when using
       variants.  */
    b4_symbol_variant([[yyr1@{yyn@}]], [(*yyvalp)], [build])], [[
  if (yyrhslen == 0)
    *yyvalp = yyval_default;
  else
    *yyvalp = yyvsp[YYFILL (1-yyrhslen)].yystate.yysemantics.yysval;]])b4_locations_if([[
  YYLLOC_DEFAULT ((*yylocp), (yyvsp - yyrhslen), yyrhslen);
  yystackp->yyerror_range[1].yystate.yyloc = *yylocp;
]])[
  switch (yyn)
    {
      ]b4_user_actions[
      default: break;
    }

  //  std::cerr << "yyuserAction: return yyok" << std::endl;
  return yyok;
# undef yyerrok
# undef YYABORT
# undef YYACCEPT
# undef YYERROR
# undef YYBACKUP
# undef yyclearin
# undef YYRECOVERING
}


static void
yyuserMerge (int yyn, YYSTYPE* yy0, YYSTYPE* yy1)
{
  YYUSE (yy0);
  YYUSE (yy1);

  switch (yyn)
    {
]b4_mergers[
      default: break;
    }
}

                              /* Bison grammar-table manipulation.  */

]b4_yydestruct_define[

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yy_rule_num yyrule)
{
  return yyr2[yyrule];
}

static void
yydestroyGLRState (char const *yymsg, yy_glr_state *yys]b4_user_formals[)
{
  if (yys->yyresolved)
    yydestruct (yymsg, yystos[yys->yylrState],
                &yys->yysemantics.yysval]b4_locuser_args([&yys->yyloc])[);
  else
    {
#if ]b4_api_PREFIX[DEBUG
      if (yydebug)
        {
          if (yys->yysemantics.yyfirstVal)
            YYFPRINTF (stderr, "%s unresolved", yymsg);
          else
            YYFPRINTF (stderr, "%s incomplete", yymsg);
          YY_SYMBOL_PRINT ("", yystos[yys->yylrState], YY_NULLPTR, &yys->yyloc);
        }
#endif

      if (yys->yysemantics.yyfirstVal)
        {
          yy_semantic_option *yyoption = yys->yysemantics.yyfirstVal;
          yy_glr_state *yyrh;
          int yyn;
          for (yyrh = yyoption->yystate, yyn = yyrhsLength (yyoption->yyrule);
               yyn > 0;
               yyrh = yyrh->yypred, yyn -= 1)
            yydestroyGLRState (yymsg, yyrh]b4_user_args[);
        }
    }
}

/** Left-hand-side symbol for rule #YYRULE.  */
static inline yy_symbol
yylhsNonterm (yy_rule_num yyrule)
{
  return yyr1[yyrule];
}

#define yypact_value_is_default(Yystate) \
  ]b4_table_value_equals([[pact]], [[Yystate]], [b4_pact_ninf])[

/** True iff LR state YYSTATE has only a default reduction (regardless
 *  of token).  */
static inline bool
yyisDefaultedState (yy_state_num yystate)
{
  return yypact_value_is_default (yypact[yystate]);
}

/** The default reduction for YYSTATE, assuming it has one.  */
static inline yy_rule_num
yydefaultAction (yy_state_num yystate)
{
  return yydefact[yystate];
}

#define yytable_value_is_error(Yytable_value) \
  ]b4_table_value_equals([[table]], [[Yytable_value]], [b4_table_ninf])[

/** Set *YYACTION to the action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *YYCONFLICTS to a pointer into yyconfl to a 0-terminated list
 *  of conflicting reductions.
 */
static inline void
yygetLRActions (yy_state_num yystate, int yytoken,
                int* yyaction, const short int** yyconflicts)
{
  int yyindex = yypact[yystate] + yytoken;
  if (yypact_value_is_default (yypact[yystate])
      || yyindex < 0 || YYLAST < yyindex || yycheck[yyindex] != yytoken)
    {
      *yyaction = -yydefact[yystate];
      *yyconflicts = yyconfl;
    }
  else if (! yytable_value_is_error (yytable[yyindex]))
    {
      *yyaction = yytable[yyindex];
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
  else
    {
      *yyaction = 0;
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
}

/** Compute post-reduction state.
 * \param yystate   the current state
 * \param yysym     the nonterminal to push on the stack
 */
static inline yy_state_num
yyLRgotoState (yy_state_num yystate, yy_symbol yysym)
{
  int yyr = yypgoto[yysym - YYNTOKENS] + yystate;
  if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
    return yytable[yyr];
  else
    return yydefgoto[yysym - YYNTOKENS];
}

static inline bool
yyisShiftAction (int yyaction)
{
  return 0 < yyaction;
}

static inline bool
yyisErrorAction (int yyaction)
{
  return yyaction == 0;
}



]b4_variant_if([[
static inline void
yysymbolCopy (int& yychar1, YYSTYPE& yyval1]b4_locations_if([, YYLTYPE& yyloc1])[,
              const int& yychar2, const YYSTYPE& yyval2]b4_locations_if([, const YYLTYPE& yyloc2])[)
{
  ]b4_symbol_variant([[YYTRANSLATE (yychar2)]], [[yyval1]],
                     [copy], [yyval2])[
  yychar1 = yychar2;]b4_locations_if([
  yyloc1 = yyloc2;])[
}

static inline void
yysymbolSwap (int& yychar1, YYSTYPE& yyval1]b4_locations_if([, YYLTYPE& yyloc1])[,
              int& yychar2, YYSTYPE& yyval2]b4_locations_if([, YYLTYPE& yyloc2])[)
{
  ]b4_symbol_variant([[YYTRANSLATE (yychar2)]], [[yyval1]],
                     [swap], [yyval2])[
  std::swap (yychar1, yychar2);]b4_locations_if([[
  std::swap (yyloc1,  yyloc2);]])[
}
#define YY_SYMBOL_COPY yysymbolCopy
#define YY_SYMBOL_SWAP yysymbolSwap
]],
[[
#define YY_SYMBOL_COPY(Yychar1, Yyval1]b4_locations_if([, Yyloc1])[, Yychar2, Yyval2]b4_locations_if([, Yyloc2])[) \
  do {                                                                  \
    Yychar1 = Yychar2;                                                  \
    Yyval1  = Yyval2;]b4_locations_if([[                                \
    Yyloc1  = Yyloc2;]])[                                                   \
  } while (0)

#define YY_SYMBOL_SWAP(Yychar1, Yyval1]b4_locations_if([ ,Yyloc1])[, Yychar2, Yyval2]b4_locations_if([, Yyloc2])[) \
    YY_SYMBOL_COPY(Yychar1, Yyval1]b4_locations_if([ ,Yyloc1])[, Yychar2, Yyval2]b4_locations_if([, Yyloc2])[)
]])[
}



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
