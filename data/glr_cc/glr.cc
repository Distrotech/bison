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
[[[[YYSTYPE *yylvalp]], [[yylvalp]]][]dnl
b4_locations_if([, [[YYLTYPE *yyllocp], [yyllocp]]])dnl
m4_ifdef([b4_lex_param], [, ]b4_lex_param)])


# b4_lex
# ------
# Call yylex.
m4_define([b4_lex],
[b4_function_call([b4_token_ctor_if(b4_namespace_ref[::yylex_wrapper],
                                    [yylex])],
                  [int], b4_lex_formals)])


# b4_yy_symbol_print_define
# -------------------------
# Bypass the default implementation to generate the "yy_symbol_print"
# and "yy_symbol_value_print" functions.
m4_define([b4_yy_symbol_print_define],
[[
/*--------------------.
| Print this symbol.  |
`--------------------*/

]b4_function_define([yy_symbol_print],
    [static void],
    [[FILE *],      []],
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
#define yylval  ]b4_prefix[lval
#define yychar  ]b4_prefix[char
#define yynerrs ]b4_prefix[nerrs]b4_locations_if([[
#define yylloc  ]b4_prefix[lloc]])])

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
#include <iostream>]b4_defines_if([
b4_bison_locations_if([[#include "location.hh"]])])[

]b4_variant_if([b4_variant_includes])[
]b4_YYDEBUG_define[

]b4_namespace_open[
]b4_defines_if([],
[b4_bison_locations_if([b4_position_define
b4_location_define])])[

]b4_variant_if([b4_variant_define])[

  /// A Bison parser.
  class ]b4_parser_class_name[
  {
  public:
]b4_public_types_declare[

    /// Build a parser object.
    ]b4_parser_class_name[ (]b4_parse_param_decl[);
    virtual ~]b4_parser_class_name[ ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

    /// The current debugging stream.
    std::ostream& debug_stream () const;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);

  public:
    /// Report a syntax error.]b4_locations_if([[
    /// \param loc    where the syntax error is found.]])[
    /// \param msg    a description of the syntax error.
    virtual void error (]b4_locations_if([[const location_type& loc, ]])[const std::string& msg);

# if ]b4_api_PREFIX[DEBUG
  public:
    /// \brief Report a symbol value on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.]b4_locations_if([[
    /// \param yylocationp  Its location.]])[
    virtual void yy_symbol_value_print_ (int yytype,
                                         const semantic_type* yyvaluep]b4_locations_if([[,
                                         const location_type* yylocationp]])[);
    /// \brief Report a symbol on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.]b4_locations_if([[
    /// \param yylocationp  Its location.]])[
    virtual void yy_symbol_print_ (int yytype,
                                   const semantic_type* yyvaluep]b4_locations_if([[,
                                   const location_type* yylocationp]])[);
  private:
    // Debugging.
    std::ostream* yycdebug_;
#endif

    enum
    {
      yyeof_ = 0
    };

    /// Convert a scanner token number \a t to a symbol number.
    static inline token_number_type yytranslate_ (]b4_token_ctor_if([token_type], [int])[ t);

]b4_parse_param_vars[
  };

]b4_token_ctor_if([b4_yytranslate_define
b4_public_types_define])[

]dnl Redirections for glr.c.
b4_percent_define_flag_if([[global_tokens_and_yystype]],
[b4_token_defines])
[
#ifndef ]b4_api_PREFIX[STYPE
# define ]b4_api_PREFIX[STYPE ]b4_namespace_ref[::]b4_parser_class_name[::semantic_type
#endif
#ifndef ]b4_api_PREFIX[LTYPE
# define ]b4_api_PREFIX[LTYPE ]b4_namespace_ref[::]b4_parser_class_name[::location_type
#endif

]b4_namespace_close
b4_function_declare(b4_prefix[parse], [int], b4_parse_param_wrap)
b4_percent_code_get([[provides]])
m4_popdef([b4_parse_param])dnl
])

b4_defines_if(
[b4_output_begin([b4_spec_defines_file])
b4_copyright([Skeleton interface for Bison GLR parsers in C++],
             [2002-2013])[

// C++ GLR parser skeleton written by Akim Demaille.

]b4_cpp_guard_open([b4_spec_defines_file])[
]b4_shared_declarations[
]b4_cpp_guard_close([b4_spec_defines_file])[
]b4_output_end()])

# Let glr.c (and b4_shared_declarations) believe that the user
# arguments include the parser itself.
m4_pushdef([b4_parse_param], m4_defn([b4_parse_param_wrap]))










////////////////// GLR.CC //////////////



## ---------------- ##
## Default values.  ##
## ---------------- ##

# Stack parameters.
m4_define_default([b4_stack_depth_max], [10000])
m4_define_default([b4_stack_depth_init],  [200])


# b4_user_formals
# ---------------
# The possible parse-params formal arguments preceded by a comma.
#
# This is not shared with yacc.c in c.m4 because  GLR relies on ISO C
# formal argument declarations.
m4_define([b4_user_formals],
[m4_ifset([b4_parse_param], [, b4_formals(b4_parse_param)])])

# b4_user_formals_no_comma
# ---------------
# The possible parse-params formal arguments NOT preceded by a comma.
#
# This is not shared with yacc.c in c.m4 because  GLR relies on ISO C
# formal argument declarations.
m4_define([b4_user_formals_no_comma],
[m4_ifset([b4_parse_param], [b4_formals(b4_parse_param)])])

# b4_yyerror_args
# ---------------
# Optional effective arguments passed to yyerror: user args plus yylloc, and
# a trailing comma.
m4_define([b4_yyerror_args],
[b4_locations_if([yylocp, ])dnl
m4_ifset([b4_parse_param], [b4_args(b4_parse_param), ])])


# b4_lyyerror_args
# ----------------
# Same as above, but on the lookahead, hence &yylloc instead of yylocp.
m4_define([b4_lyyerror_args],
[b4_locations_if([&yylloc, ])dnl
m4_ifset([b4_parse_param], [b4_args(b4_parse_param), ])])


# b4_pure_args
# ------------
# Same as b4_yyerror_args, but with a leading comma.
m4_define([b4_pure_args],
[b4_locations_if([, yylocp])[]b4_user_args])


# b4_lpure_args
# -------------
# Same as above, but on the lookahead, hence &yylloc instead of yylocp.
m4_define([b4_lpure_args],
[[b4_locations_if([, &yylloc])][]b4_user_args])


# b4_pure_formals
# ---------------
# Arguments passed to yyerror: user formals plus yylocp with leading comma.
m4_define([b4_pure_formals],
[[b4_locations_if([, YYLTYPE *yylocp])][]b4_user_formals])


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



## -------------- ##
## Output files.  ##
## -------------- ##

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
]][
#define yylval  ]b4_prefix[lval
#define yychar  ]b4_prefix[char
#define yynerrs ]b4_prefix[nerrs]b4_locations_if([[
#define yylloc  ]b4_prefix[lloc]]))[

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

[#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#ifndef YYFREE
# define YYFREE free
#endif
#ifndef YYMALLOC
# define YYMALLOC malloc
#endif
#ifndef YYREALLOC
# define YYREALLOC realloc
#endif

#define YYSIZEMAX ((size_t) -1)

#define yytrue 1
#define yyfalse 0



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

/* Error token number */
#define YYTERROR 1

]b4_locations_if([[
]b4_yylloc_default_define[
# define YYRHSLOC(Rhs, K) ((Rhs)[K].yystate.yyloc)
]])[

#undef yynerrs
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
#define b4_prefix[]lloc yylloc])],
[YYSTYPE yylval;]b4_locations_if([[
YYLTYPE yylloc;]])[

int yynerrs;
int yychar;

static const int YYEOF = 0;
static const int YYEMPTY = -2;

typedef enum { yyok, yyaccept, yyabort, yyerr } YYRESULTTAG;






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

#endif /* !YYERROR_VERBOSE */

/** State numbers, as in LALR(1) machine */
typedef int yy_state_num;

/** Rule numbers, as in LALR(1) machine */
typedef int yy_rule_num;

/** Grammar symbol */
typedef int yy_symbol;

/** Item references, as in LALR(1) machine */
typedef short int yy_item_num;

typedef struct yy_glr_state yy_glr_state;
typedef struct yy_glr_stateSet yy_glr_stateSet;
typedef struct yy_semantic_option yy_semantic_option;
typedef ]b4_variant_if([struct], [union])[ yy_glr_stack_item yy_glr_stack_item;
typedef struct yy_glr_stack yy_glr_stack;

struct yy_glr_state {]b4_variant_if([[
  yy_glr_state()
  {
    // std::cerr << "Default ctor: " << this << std::endl;
  }
  yy_glr_state(const yy_glr_state& that)
  {
    abort();
    //    std::cerr << "Cpy ctor" << std::endl;
    *this = that;
  }
  yy_glr_state& operator=(const yy_glr_state& that)
  {
    //    std::cerr << "Assign: " << this << " = " << &that << std::endl;
    YYASSERT (that.yyisState);
    yyisState = that.yyisState;
    yyresolved = that.yyresolved;
    yylrState = that.yylrState;
    yypred = that.yypred;
    yyposn = that.yyposn;
    yysemantics.yyfirstVal = that.yysemantics.yyfirstVal;]b4_variant_if([[
    //  new (&ysemantics.yysval) YYSTYPE;
    ]b4_symbol_variant([[yystos[yylrState]]], [[yysemantics.yysval]],
                     [copy], [that.yysemantics.yysval])], [[
    yynewState->yysemantics.yysval = *yyvalp;]])b4_locations_if([
    yyloc = that.yyloc;])[
    return *this;
  }]])[
  /** Type tag: always true.  */
  bool yyisState;
  /** Type tag for yysemantics.  If true, yysval applies, otherwise
   *  yyfirstVal applies.  */
  bool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
  yy_state_num yylrState;
  /** Preceding state in this stack */
  yy_glr_state* yypred;
  /** Source position of the last token produced by my symbol */
  size_t yyposn;
  ]b4_variant_if([struct], [union])[ {
    /** First in a chain of alternative reductions producing the
     *  non-terminal corresponding to this state, threaded through
     *  yynext.  */
    yy_semantic_option* yyfirstVal;
    /** Semantic value for this state.  */
    YYSTYPE yysval;
  } yysemantics;]b4_locations_if([[
  /** Source location for this state.  */
  YYLTYPE yyloc;]])[
};

struct yy_glr_stateSet {
  yy_glr_state** yystates;
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != YYEMPTY.  */
  bool* yylookaheadNeeds;
  size_t yysize, yycapacity;
};

struct yy_semantic_option {
  /** Type tag: always false.  */
  bool yyisState;
  /** Rule number for this reduction */
  yy_rule_num yyrule;
  /** The last RHS state in the list of states to be reduced.  */
  yy_glr_state* yystate;
  /** The lookahead for this reduction.  */
  int yyrawchar;
  YYSTYPE yyval;]b4_locations_if([[
  YYLTYPE yyloc;]])[
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
  yy_semantic_option* yynext;

]b4_variant_if([[
  yy_semantic_option& operator= (yy_semantic_option const& other)
  {
    yyisState = other.yyisState;
    yyrule = other.yyrule;
    yystate = other.yystate;
    yyrawchar = other.yyrawchar;
    ]b4_symbol_variant([yystate->yylrState],
                       [yyval], [copy], [other.yyval])b4_locations_if([
    yyloc = other.yyloc;])[
    return *this;
  }
]])[
};

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
  int yyerrcnt;
  int yyrawchar;
  YYSTYPE yyval;]b4_locations_if([[
  YYLTYPE yyloc;]])[
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
  throw yy_parsing_error(yy_parsing_error::error_status::abort);
}

static _Noreturn void
yyMemoryExhausted (yy_glr_stack* yystackp)
{
  throw yy_parsing_error(yy_parsing_error::error_status::memory_exhausted);
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

                                /* GLRStates */

/** Return a fresh GLRStackItem in YYSTACKP.  The item is an LR state
 *  if YYISSTATE, and otherwise a semantic option.  Callers should call
 *  YY_RESERVE_GLRSTACK afterwards to make sure there is sufficient
 *  headroom.  */

//static inline yy_glr_stack_item*
//yynewGLRStackItem (yy_glr_stack* yystackp, bool yyisState)
//{
//  yy_glr_stack_item* yynewItem = yystackp->yynextFree;
//  yystackp->yyspaceLeft -= 1;
//  yystackp->yynextFree += 1;
//  yynewItem->yystate.yyisState = yyisState;
//  yynewItem->yyoption.yyisState = yyisState;
//  return yynewItem;
//}

/** Add a new semantic action that will execute the action for rule
 *  YYRULE on the semantic values in YYRHS to the list of
 *  alternative actions for YYSTATE.  Assumes that YYRHS comes from
 *  stack #YYK of *YYSTACKP. */
static void
yyaddDeferredAction (yy_glr_stack* yystackp, size_t yyk, yy_glr_state* yystate,
                     yy_glr_state* yyrhs, yy_rule_num yyrule)
{
  //  std::cerr << "yyaddDeferredAction" << std::endl;
  //  yypdumpstack(yystackp);
  yy_semantic_option* yynewOption =
    &yynewGLRStackItem (yystackp, yyfalse)->yyoption;
  YYASSERT (!yynewOption->yyisState);
  yynewOption->yystate = yyrhs;
  yynewOption->yyrule = yyrule;
  if (yystackp->yytops.yylookaheadNeeds[yyk])
    {
      yynewOption->yyrawchar = yychar;
]b4_variant_if([[
  new (&yynewOption->yyval) YYSTYPE;
  ]b4_symbol_variant([[YYTRANSLATE (yychar)]],
                     [[yynewOption->yyval]],
                     [copy], [yylval])], [[
  yynewOption->yyval = yylval;]])[
//      yynewOption->yyval = yylval;]b4_locations_if([[
      yynewOption->yyloc = yylloc;]])[
    }
  else
    yynewOption->yyrawchar = YYEMPTY;
  yynewOption->yynext = yystate->yysemantics.yyfirstVal;
  yystate->yysemantics.yyfirstVal = yynewOption;

  YY_RESERVE_GLRSTACK (yystackp);
  //  std::cerr << "yyaddDeferredAction: done" << std::endl;
}

                                /* GLRStacks */

///** Initialize YYSET to a singleton set containing an empty stack.  */
//static bool
//yyinitStateSet (yy_glr_stateSet* yyset)
//{
//  yyset->yysize = 1;
//  yyset->yycapacity = 16;
//  yyset->yystates = (yy_glr_state**) YYMALLOC (16 * sizeof yyset->yystates[0]);
//  if (! yyset->yystates)
//    return yyfalse;
//  yyset->yystates[0] = YY_NULLPTR;
//  yyset->yylookaheadNeeds =
//    (bool*) YYMALLOC (16 * sizeof yyset->yylookaheadNeeds[0]);
//  if (! yyset->yylookaheadNeeds)
//    {
//      YYFREE (yyset->yystates);
//      return yyfalse;
//    }
//  return yytrue;
//}

static void yyfreeStateSet (yy_glr_stateSet* yyset)
{
  YYFREE (yyset->yystates);
  YYFREE (yyset->yylookaheadNeeds);
}

///** Initialize *YYSTACKP to a single empty stack, with total maximum
// *  capacity for all stacks of YYSIZE.  */
//static bool
//yyinitGLRStack (yy_glr_stack* yystackp, size_t yysize)
//{
//  yystackp->yyerrState = 0;
//  yynerrs = 0;
//  yystackp->yyspaceLeft = yysize;
//  yystackp->yyitems =
//    (yy_glr_stack_item*) YYMALLOC (yysize * sizeof yystackp->yynextFree[0]);
//  if (!yystackp->yyitems)
//    return yyfalse;
//  yystackp->yynextFree = yystackp->yyitems;
//  yystackp->yysplitPoint = YY_NULLPTR;
//  yystackp->yylastDeleted = YY_NULLPTR;
//  return yyinitStateSet (&yystackp->yytops);
//}


//#if YYSTACKEXPANDABLE
//# define YYRELOC(YYFROMITEMS,YYTOITEMS,YYX,YYTYPE) \
//  &((YYTOITEMS) - ((YYFROMITEMS) - (yy_glr_stack_item*) (YYX)))->YYTYPE
//
///** If *YYSTACKP is expandable, extend it.  WARNING: Pointers into the
//    stack from outside should be considered invalid after this call.
//    We always expand when there are 1 or fewer items left AFTER an
//    allocation, so that we can avoid having external pointers exist
//    across an allocation.  */
//static void
//yyexpandGLRStack (yy_glr_stack* yystackp)
//{
//  yy_glr_stack_item* yynewItems;
//  yy_glr_stack_item* yyp0, *yyp1;
//  size_t yynewSize;
//  size_t yyn;
//  size_t yysize = yystackp->yynextFree - yystackp->yyitems;
//  if (YYMAXDEPTH - YYHEADROOM < yysize)
//    yyMemoryExhausted (yystackp);
//  yynewSize = 2*yysize;
//  if (YYMAXDEPTH < yynewSize)
//    yynewSize = YYMAXDEPTH;
//  yynewItems = (yy_glr_stack_item*) YYMALLOC (yynewSize * sizeof yynewItems[0]);
//  if (! yynewItems)
//    yyMemoryExhausted (yystackp);
//  for (yyp0 = yystackp->yyitems, yyp1 = yynewItems, yyn = yysize;
//       0 < yyn;
//       yyn -= 1, yyp0 += 1, yyp1 += 1)
//    {
//      *yyp1 = *yyp0;
//      if (*(bool *) yyp0)
//        {
//          yy_glr_state* yys0 = &yyp0->yystate;
//          yy_glr_state* yys1 = &yyp1->yystate;
//          if (yys0->yypred != YY_NULLPTR)
//            yys1->yypred =
//              YYRELOC (yyp0, yyp1, yys0->yypred, yystate);
//          if (! yys0->yyresolved && yys0->yysemantics.yyfirstVal != YY_NULLPTR)
//            yys1->yysemantics.yyfirstVal =
//              YYRELOC (yyp0, yyp1, yys0->yysemantics.yyfirstVal, yyoption);
//        }
//      else
//        {
//          yy_semantic_option* yyv0 = &yyp0->yyoption;
//          yy_semantic_option* yyv1 = &yyp1->yyoption;
//          if (yyv0->yystate != YY_NULLPTR)
//            yyv1->yystate = YYRELOC (yyp0, yyp1, yyv0->yystate, yystate);
//          if (yyv0->yynext != YY_NULLPTR)
//            yyv1->yynext = YYRELOC (yyp0, yyp1, yyv0->yynext, yyoption);
//        }
//    }
//  if (yystackp->yysplitPoint != YY_NULLPTR)
//    yystackp->yysplitPoint = YYRELOC (yystackp->yyitems, yynewItems,
//                                      yystackp->yysplitPoint, yystate);
//
//  for (yyn = 0; yyn < yystackp->yytops.yysize; yyn += 1)
//    if (yystackp->yytops.yystates[yyn] != YY_NULLPTR)
//      yystackp->yytops.yystates[yyn] =
//        YYRELOC (yystackp->yyitems, yynewItems,
//                 yystackp->yytops.yystates[yyn], yystate);
//  YYFREE (yystackp->yyitems);
//  yystackp->yyitems = yynewItems;
//  yystackp->yynextFree = yynewItems + yysize;
//  yystackp->yyspaceLeft = yynewSize - yysize;
//  //  std::cerr << "yyexpandGLRStack: done" << std::endl;
//}
//#endif

static void
yyfreeGLRStack (yy_glr_stack* yystackp)
{
  YYFREE (yystackp->yyitems);
  yyfreeStateSet (&yystackp->yytops);
}

/** Invalidate stack #YYK in *YYSTACKP.  */
static inline void
yymarkStackDeleted (yy_glr_stack* yystackp, size_t yyk)
{
  if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    yystackp->yylastDeleted = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yystates[yyk] = YY_NULLPTR;
}

/** Undelete the last stack in *YYSTACKP that was marked as deleted.  Can
    only be done once after a deletion, and only when all other stacks have
    been deleted.  */
static void
yyundeleteLastStack (yy_glr_stack* yystackp)
{
  if (yystackp->yylastDeleted == YY_NULLPTR || yystackp->yytops.yysize != 0)
    return;
  yystackp->yytops.yystates[0] = yystackp->yylastDeleted;
  yystackp->yytops.yysize = 1;
  YYDPRINTF ((stderr, "Restoring last deleted stack as stack #0.\n"));
  yystackp->yylastDeleted = YY_NULLPTR;
}

static inline void
yyremoveDeletes (yy_glr_stack* yystackp)
{
  size_t yyi, yyj;
  yyi = yyj = 0;
  while (yyj < yystackp->yytops.yysize)
    {
      if (yystackp->yytops.yystates[yyi] == YY_NULLPTR)
        {
          if (yyi == yyj)
            {
              YYDPRINTF ((stderr, "Removing dead stacks.\n"));
            }
          yystackp->yytops.yysize -= 1;
        }
      else
        {
          yystackp->yytops.yystates[yyj] = yystackp->yytops.yystates[yyi];
          /* In the current implementation, it's unnecessary to copy
             yystackp->yytops.yylookaheadNeeds[yyi] since, after
             yyremoveDeletes returns, the parser immediately either enters
             deterministic operation or shifts a token.  However, it doesn't
             hurt, and the code might evolve to need it.  */
          yystackp->yytops.yylookaheadNeeds[yyj] =
            yystackp->yytops.yylookaheadNeeds[yyi];
          if (yyj != yyi)
            {
              YYDPRINTF ((stderr, "Rename stack %lu -> %lu.\n",
                          (unsigned long int) yyi, (unsigned long int) yyj));
            }
          yyj += 1;
        }
      yyi += 1;
    }
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


static YYRESULTTAG yyresolveValue (yy_glr_state* yys,
                                   yy_glr_stack* yystackp]b4_user_formals[);


/** Resolve the previous YYN states starting at and including state YYS
 *  on *YYSTACKP. If result != yyok, some states may have been left
 *  unresolved possibly with empty semantic option chains.  Regardless
 *  of whether result = yyok, each state has been left with consistent
 *  data so that yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveStates (yy_glr_state* yys, int yyn,
                 yy_glr_stack* yystackp]b4_user_formals[)
{
  if (0 < yyn)
    {
      YYASSERT (yys->yypred);
      YYCHK (yyresolveStates (yys->yypred, yyn-1, yystackp]b4_user_args[));
      if (! yys->yyresolved)
        YYCHK (yyresolveValue (yys, yystackp]b4_user_args[));
    }
  return yyok;
}

/** Resolve the states for the RHS of YYOPT on *YYSTACKP, perform its
 *  user action, and return the semantic value and location in *YYVALP
 *  and *YYLOCP.  Regardless of whether result = yyok, all RHS states
 *  have been destroyed (assuming the user action destroys all RHS
 *  semantic values if invoked).  */
static YYRESULTTAG
yyresolveAction (yy_semantic_option* yyopt, yy_glr_stack* yystackp,
                 YYSTYPE* yyvalp]b4_locuser_formals[)
{
  yy_glr_stack_item yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
  int yynrhs = yyrhsLength (yyopt->yyrule);
  YYRESULTTAG yyflag =
    yyresolveStates (yyopt->yystate, yynrhs, yystackp]b4_user_args[);
  if (yyflag != yyok)
    {
      yy_glr_state *yys;
      for (yys = yyopt->yystate; yynrhs > 0; yys = yys->yypred, yynrhs -= 1)
        yydestroyGLRState ("Cleanup: popping", yys]b4_user_args[);
      return yyflag;
    }

  yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred = yyopt->yystate;]b4_locations_if([[
  if (yynrhs == 0)
    /* Set default location.  */
    yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yyopt->yystate->yyloc;]])[
  {
    int yychar_current;
    YYSTYPE yylval_current;]b4_locations_if([
    YYLTYPE yylloc_current;])[
  //  YY_SYMBOL_PRINT("yyresolveAction: BEFORE",
  //                  YYTRANSLATE(yychar), &yylval, &yylloc);

    YY_SYMBOL_SWAP (yychar_current, yylval_current]b4_locations_if([, yylloc_current])[,
                    yychar, yylval]b4_locations_if([, yylloc])[);
    YY_SYMBOL_COPY (yychar, yylval]b4_locations_if([, yylloc])[,
                    yyopt->yyrawchar, yyopt->yyval]b4_locations_if([, yyopt->yyloc])[);

    //  YY_SYMBOL_PRINT("yyresolveAction: DURING",
    //              YYTRANSLATE(yychar), &yylval, &yylloc);
    yyflag = yyuserAction (yyopt->yyrule, yynrhs,
                           yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp]b4_locuser_args[);
    YY_SYMBOL_SWAP (yychar, yylval]b4_locations_if([, yylloc])[,
                    yychar_current, yylval_current]b4_locations_if([, yylloc_current])[);
    //  YY_SYMBOL_PRINT("yyresolveAction: AFTER",
    //              YYTRANSLATE(yychar), &yylval, &yylloc);
  }
  return yyflag;
}

static YYRESULTTAG
yyreportAmbiguity (yy_semantic_option* yyx0,
                   yy_semantic_option* yyx1]b4_pure_formals[)
{
  YYUSE (yyx0);
  YYUSE (yyx1);

#if ]b4_api_PREFIX[DEBUG
  YYFPRINTF (stderr, "Ambiguity detected.\n");
  YYFPRINTF (stderr, "Option 1,\n");
  yyx0->yyreportTree (2);
  YYFPRINTF (stderr, "\nOption 2,\n");
  yyx1->yyreportTree (2);
  YYFPRINTF (stderr, "\n");
#endif

  yyerror (]b4_yyerror_args[YY_("syntax is ambiguous"));
  return yyabort;
}]b4_locations_if([[

/** Resolve the locations for each of the YYN1 states in *YYSTACKP,
 *  ending at YYS1.  Has no effect on previously resolved states.
 *  The first semantic option of a state is always chosen.  */
static void
yyresolveLocations (yy_glr_state *yys1, int yyn1,
                    yy_glr_stack *yystackp]b4_user_formals[)
{
  if (0 < yyn1)
    {
      yyresolveLocations (yys1->yypred, yyn1 - 1, yystackp]b4_user_args[);
      if (!yys1->yyresolved)
        {
          yy_glr_stack_item yyrhsloc[1 + YYMAXRHS];
          int yynrhs;
          yy_semantic_option *yyoption = yys1->yysemantics.yyfirstVal;
          YYASSERT (yyoption);
          yynrhs = yyrhsLength (yyoption->yyrule);
          if (0 < yynrhs)
            {
              yy_glr_state *yys;
              int yyn;
              yyresolveLocations (yyoption->yystate, yynrhs,
                                  yystackp]b4_user_args[);
              for (yys = yyoption->yystate, yyn = yynrhs;
                   yyn > 0;
                   yys = yys->yypred, yyn -= 1)
                yyrhsloc[yyn].yystate.yyloc = yys->yyloc;
            }
          else
            {
              /* Both yyresolveAction and yyresolveLocations traverse the GSS
                 in reverse rightmost order.  It is only necessary to invoke
                 yyresolveLocations on a subforest for which yyresolveAction
                 would have been invoked next had an ambiguity not been
                 detected.  Thus the location of the previous state (but not
                 necessarily the previous state itself) is guaranteed to be
                 resolved already.  */
              yy_glr_state *yyprevious = yyoption->yystate;
              yyrhsloc[0].yystate.yyloc = yyprevious->yyloc;
            }
          YYLLOC_DEFAULT ((yys1->yyloc), yyrhsloc, yynrhs);
        }
    }
}]])[

/** Resolve the ambiguity represented in state YYS in *YYSTACKP,
 *  perform the indicated actions, and set the semantic value of YYS.
 *  If result != yyok, the chain of semantic options in YYS has been
 *  cleared instead or it has been left unmodified except that
 *  redundant options may have been removed.  Regardless of whether
 *  result = yyok, YYS has been left with consistent data so that
 *  yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveValue (yy_glr_state* yys, yy_glr_stack* yystackp]b4_user_formals[)
{
  yy_semantic_option* yyoptionList = yys->yysemantics.yyfirstVal;
  yy_semantic_option* yybest = yyoptionList;
  yy_semantic_option** yypp;
  bool yymerge = yyfalse;
  YYSTYPE yysval;
  YYRESULTTAG yyflag;]b4_locations_if([
  YYLTYPE *yylocp = &yys->yyloc;])[

  for (yypp = &yyoptionList->yynext; *yypp != YY_NULLPTR; )
    {
      yy_semantic_option* yyp = *yypp;

      if (*yybest == *yyp)
        {
          yybest->yymerge_option_sets (*yyp);
          *yypp = yyp->yynext;
        }
      else
        {
          switch (yypreference (yybest, yyp))
            {
            case no_combination:]b4_locations_if([[
              yyresolveLocations (yys, 1, yystackp]b4_user_args[);]])[
              return yyreportAmbiguity (yybest, yyp]b4_pure_args[);
              break;
            case user_mergeable:
              yymerge = yytrue;
              break;
            case left_preferred:
              break;
            case right_preferred:
              yybest = yyp;
              yymerge = yyfalse;
              break;
            default:
              /* This cannot happen so it is not worth a YYASSERT (yyfalse),
                 but some compilers complain if the default case is
                 omitted.  */
              break;
            }
          yypp = &yyp->yynext;
        }
    }

  if (yymerge)
    {
      yy_semantic_option* yyp;
      int yyprec = yydprec[yybest->yyrule];
      yyflag = yyresolveAction (yybest, yystackp, &yysval]b4_locuser_args[);
      if (yyflag == yyok)
        for (yyp = yybest->yynext; yyp != YY_NULLPTR; yyp = yyp->yynext)
          {
            if (yyprec == yydprec[yyp->yyrule])
              {
                YYSTYPE yysval_other;]b4_locations_if([
                YYLTYPE yydummy;])[
                yyflag = yyresolveAction (yyp, yystackp, &yysval_other]b4_locuser_args([&yydummy])[);
                if (yyflag != yyok)
                  {
                    yydestruct ("Cleanup: discarding incompletely merged value for",
                                yystos[yys->yylrState],
                                &yysval]b4_locuser_args[);
                    break;
                  }
                yyuserMerge (yymerger[yyp->yyrule], &yysval, &yysval_other);
              }
          }
    }
  else
    yyflag = yyresolveAction (yybest, yystackp, &yysval]b4_locuser_args([yylocp])[);

  if (yyflag == yyok)
    {
      yys->yyresolved = yytrue;]b4_variant_if([[
      new (&yys->yysemantics.yysval) YYSTYPE; // FIXME: Useful?
      ]b4_symbol_variant([[yystos[yys->yylrState]]],
                         [[yys->yysemantics.yysval]],
                         [move], [yysval])], [[
      yys->yysemantics.yysval = yysval;]])[
    }
  else
    yys->yysemantics.yyfirstVal = YY_NULLPTR;
  return yyflag;
}


//static void
//yyreportSyntaxError (yy_glr_stack* yystackp]b4_user_formals[)
//{
//  if (yystackp->yyerrState != 0)
//    return;
//#if ! YYERROR_VERBOSE
//  yyerror (]b4_lyyerror_args[YY_("syntax error"));
//#else
//  {
//  yy_symbol yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);
//  size_t yysize0 = yytnamerr (YY_NULLPTR, yytokenName (yytoken));
//  size_t yysize = yysize0;
//  bool yysize_overflow = yyfalse;
//  char* yymsg = YY_NULLPTR;
//  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
//  /* Internationalized format string. */
//  const char *yyformat = YY_NULLPTR;
//  /* Arguments of yyformat. */
//  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
//  /* Number of reported tokens (one for the "unexpected", one per
//     "expected").  */
//  int yycount = 0;
//
//  /* There are many possibilities here to consider:
//     - If this state is a consistent state with a default action, then
//       the only way this function was invoked is if the default action
//       is an error action.  In that case, don't check for expected
//       tokens because there are none.
//     - The only way there can be no lookahead present (in yychar) is if
//       this state is a consistent state with a default action.  Thus,
//       detecting the absence of a lookahead is sufficient to determine
//       that there is no unexpected or expected token to report.  In that
//       case, just report a simple "syntax error".
//     - Don't assume there isn't a lookahead just because this state is a
//       consistent state with a default action.  There might have been a
//       previous inconsistent state, consistent state with a non-default
//       action, or user semantic action that manipulated yychar.
//     - Of course, the expected token list depends on states to have
//       correct lookahead information, and it depends on the parser not
//       to perform extra reductions after fetching a lookahead from the
//       scanner and before detecting a syntax error.  Thus, state merging
//       (from LALR or IELR) and default reductions corrupt the expected
//       token list.  However, the list is correct for canonical LR with
//       one exception: it will still contain any token that will not be
//       accepted due to an error action in a later state.
//  */
//  if (yytoken != YYEMPTY)
//    {
//      int yyn = yypact[yystackp->yytops.yystates[0]->yylrState];
//      yyarg[yycount++] = yytokenName (yytoken);
//      if (!yypact_value_is_default (yyn))
//        {
//          /* Start YYX at -YYN if negative to avoid negative indexes in
//             YYCHECK.  In other words, skip the first -YYN actions for this
//             state because they are default actions.  */
//          int yyxbegin = yyn < 0 ? -yyn : 0;
//          /* Stay within bounds of both yycheck and yytname.  */
//          int yychecklim = YYLAST - yyn + 1;
//          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
//          int yyx;
//          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
//            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
//                && !yytable_value_is_error (yytable[yyx + yyn]))
//              {
//                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
//                  {
//                    yycount = 1;
//                    yysize = yysize0;
//                    break;
//                  }
//                yyarg[yycount++] = yytokenName (yyx);
//                {
//                  size_t yysz = yysize + yytnamerr (YY_NULLPTR, yytokenName (yyx));
//                  yysize_overflow |= yysz < yysize;
//                  yysize = yysz;
//                }
//              }
//        }
//    }
//
//  switch (yycount)
//    {
//#define YYCASE_(N, S)                   \
//      case N:                           \
//        yyformat = S;                   \
//      break
//      YYCASE_(0, YY_("syntax error"));
//      YYCASE_(1, YY_("syntax error, unexpected %s"));
//      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
//      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
//      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
//      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
//#undef YYCASE_
//    }
//
//  {
//    size_t yysz = yysize + strlen (yyformat);
//    yysize_overflow |= yysz < yysize;
//    yysize = yysz;
//  }
//
//  if (!yysize_overflow)
//    yymsg = (char *) YYMALLOC (yysize);
//
//  if (yymsg)
//    {
//      char *yyp = yymsg;
//      int yyi = 0;
//      while ((*yyp = *yyformat))
//        {
//          if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
//            {
//              yyp += yytnamerr (yyp, yyarg[yyi++]);
//              yyformat += 2;
//            }
//          else
//            {
//              yyp++;
//              yyformat++;
//            }
//        }
//      yyerror (]b4_lyyerror_args[yymsg);
//      YYFREE (yymsg);
//    }
//  else
//    {
//      yyerror (]b4_lyyerror_args[YY_("syntax error"));
//      yyMemoryExhausted (yystackp);
//    }
//  }
//#endif /* YYERROR_VERBOSE */
//  yynerrs += 1;
//}

///* Recover from a syntax error on *YYSTACKP, assuming that *YYSTACKP->YYTOKENP,
//   yylval, and yylloc are the syntactic category, semantic value, and location
//   of the lookahead.  */
//static void
//yyrecoverSyntaxError (yy_glr_stack* yystackp]b4_user_formals[)
//{
//  size_t yyk;
//  int yyj;
//
//  if (yystackp->yyerrState == 3)
//    /* We just shifted the error token and (perhaps) took some
//       reductions.  Skip tokens until we can proceed.  */
//    while (yytrue)
//      {
//        yy_symbol yytoken;
//        if (yychar == YYEOF)
//          yyFail (yystackp][]b4_lpure_args[, YY_NULLPTR);
//        if (yychar != YYEMPTY)
//          {]b4_locations_if([[
//            /* We throw away the lookahead, but the error range
//               of the shifted error token must take it into account.  */
//            yy_glr_state *yys = yystackp->yytops.yystates[0];
//            yy_glr_stack_item yyerror_range[3];
//            yyerror_range[1].yystate.yyloc = yys->yyloc;
//            yyerror_range[2].yystate.yyloc = yylloc;
//            YYLLOC_DEFAULT ((yys->yyloc), yyerror_range, 2);]])[
//            yytoken = YYTRANSLATE (yychar);
//            yydestruct ("Error: discarding",
//                        yytoken, &yylval]b4_locuser_args([&yylloc])[);
//          }
//        YYDPRINTF ((stderr, "Reading a token: "));
//        yychar = ]b4_lex[;
//        if (yychar <= YYEOF)
//          {
//            yychar = yytoken = YYEOF;
//            YYDPRINTF ((stderr, "Now at end of input.\n"));
//          }
//        else
//          {
//            yytoken = YYTRANSLATE (yychar);
//            YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
//          }
//        yyj = yypact[yystackp->yytops.yystates[0]->yylrState];
//        if (yypact_value_is_default (yyj))
//          return;
//        yyj += yytoken;
//        if (yyj < 0 || YYLAST < yyj || yycheck[yyj] != yytoken)
//          {
//            if (yydefact[yystackp->yytops.yystates[0]->yylrState] != 0)
//              return;
//          }
//        else if (! yytable_value_is_error (yytable[yyj]))
//          return;
//      }
//
//  /* Reduce to one stack.  */
//  for (yyk = 0; yyk < yystackp->yytops.yysize; yyk += 1)
//    if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
//      break;
//  if (yyk >= yystackp->yytops.yysize)
//    yyFail (yystackp][]b4_lpure_args[, YY_NULLPTR);
//  for (yyk += 1; yyk < yystackp->yytops.yysize; yyk += 1)
//    yymarkStackDeleted (yystackp, yyk);
//  yyremoveDeletes (yystackp);
//  yycompressStack (yystackp);
//
//  /* Now pop stack until we find a state that shifts the error token.  */
//  yystackp->yyerrState = 3;
//  while (yystackp->yytops.yystates[0] != YY_NULLPTR)
//    {
//      yy_glr_state *yys = yystackp->yytops.yystates[0];
//      yyj = yypact[yys->yylrState];
//      if (! yypact_value_is_default (yyj))
//        {
//          yyj += YYTERROR;
//          if (0 <= yyj && yyj <= YYLAST && yycheck[yyj] == YYTERROR
//              && yyisShiftAction (yytable[yyj]))
//            {
//              /* Shift the error token.  */]b4_locations_if([[
//              /* First adjust its location.*/
//              YYLTYPE yyerrloc;
//              yystackp->yyerror_range[2].yystate.yyloc = yylloc;
//              YYLLOC_DEFAULT (yyerrloc, (yystackp->yyerror_range), 2);]])[
//              YY_SYMBOL_PRINT ("Shifting", yystos[yytable[yyj]],
//                               &yylval, &yyerrloc);
//              yyglrShift (yystackp, 0, yytable[yyj],
//                          yys->yyposn, &yylval]b4_locations_if([, &yyerrloc])[);
//              yys = yystackp->yytops.yystates[0];
//              break;
//            }
//        }]b4_locations_if([[
//      yystackp->yyerror_range[1].yystate.yyloc = yys->yyloc;]])[
//      if (yys->yypred != YY_NULLPTR)
//        yydestroyGLRState ("Error: popping", yys]b4_user_args[);
//      yystackp->yytops.yystates[0] = yys->yypred;
//      yystackp->yynextFree -= 1;
//      yystackp->yyspaceLeft += 1;
//    }
//  if (yystackp->yytops.yystates[0] == YY_NULLPTR)
//    yyFail (yystackp][]b4_lpure_args[, YY_NULLPTR);
//}

#define YYCHK1(YYE)                                                          \
  do {                                                                       \
    switch (YYE) {                                                           \
    case yyok:                                                               \
      break;                                                                 \
    case yyabort:                                                            \
      goto yyabortlab;                                                       \
    case yyaccept:                                                           \
      goto yyacceptlab;                                                      \
    case yyerr:                                                              \
      goto yyuser_error;                                                     \
    default:                                                                 \
      goto yybuglab;                                                         \
    }                                                                        \
  } while (0)

/*----------.
| yyparse.  |
`----------*/

]b4_function_define([yyparse], [int], b4_parse_param)[
{
  int yyresult;
  yy_glr_stack yystack;
  yy_glr_stack* const yystackp = &yystack;
  size_t yyposn;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY;
]b4_variant_if([
  /* Variants are always initialized to an empty instance of the
     correct type.  */
  b4_symbol_variant([[0]], [yylval], [build])], [[
  yylval = yyval_default;]])b4_locations_if([
  yylloc = yyloc_default;])[
]m4_ifdef([b4_initial_action], [
b4_dollar_pushdef([yylval], [], [yylloc])dnl
  /* User initialization code.  */
  b4_user_initial_action
b4_dollar_popdef])[]dnl
[
  if (! yyinitGLRStack (yystackp, YYINITDEPTH))
    goto yyexhaustedlab;


  try
  {
  yyglrShift (&yystack, 0, 0, 0, &yylval]b4_locations_if([, &yylloc])[);
  yyposn = 0;

  while (yytrue)
    {
      /* For efficiency, we have two loops, the first of which is
         specialized to deterministic operation (single stack, no
         potential ambiguity).  */
      /* Standard mode */
      while (yytrue)
        {
          yy_rule_num yyrule;
          int yyaction;
          const short int* yyconflicts;

          yy_state_num yystate = yystack.yytops.yystates[0]->yylrState;
          YYDPRINTF ((stderr, "Entering state %d\n", yystate));
          if (yystate == YYFINAL)
            goto yyacceptlab;
          if (yyisDefaultedState (yystate))
            {
              yyrule = yydefaultAction (yystate);
              if (yyrule == 0)
                {
]b4_locations_if([[               yystack.yyerror_range[1].yystate.yyloc = yylloc;]])[
                  yyreportSyntaxError (&yystack]b4_user_args[);
                  goto yyuser_error;
                }
              YYCHK1 (yyglrReduce (&yystack, 0, yyrule, yytrue]b4_user_args[));
            }
          else
            {
              yy_symbol yytoken;
              if (yychar == YYEMPTY)
                {
                  YYDPRINTF ((stderr, "Reading a token: "));
                  yychar = ]b4_lex[;
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

              yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);
              if (*yyconflicts != 0)
                break;
              if (yyisShiftAction (yyaction))
                {
                  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
                  yychar = YYEMPTY;
                  yyposn += 1;
                  yyglrShift (&yystack, 0, yyaction, yyposn, &yylval]b4_locations_if([, &yylloc])[);
                  if (0 < yystack.yyerrState)
                    yystack.yyerrState -= 1;
                }
              else if (yyisErrorAction (yyaction))
                {
]b4_locations_if([[               yystack.yyerror_range[1].yystate.yyloc = yylloc;]])[
                  yyreportSyntaxError (&yystack]b4_user_args[);
                  goto yyuser_error;
                }
              else
                YYCHK1 (yyglrReduce (&yystack, 0, -yyaction, yytrue]b4_user_args[));
            }
        }

      while (yytrue)
        {
          yy_symbol yytoken_to_shift;
          size_t yys;

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            yystackp->yytops.yylookaheadNeeds[yys] = yychar != YYEMPTY;

          /* yyprocessOneStack returns one of three things:

              - An error flag.  If the caller is yyprocessOneStack, it
                immediately returns as well.  When the caller is finally
                yyparse, it jumps to an error label via YYCHK1.

              - yyok, but yyprocessOneStack has invoked yymarkStackDeleted
                (&yystack, yys), which sets the top state of yys to NULL.  Thus,
                yyparse's following invocation of yyremoveDeletes will remove
                the stack.

              - yyok, when ready to shift a token.

             Except in the first case, yyparse will invoke yyremoveDeletes and
             then shift the next token onto all remaining stacks.  This
             synchronization of the shift (that is, after all preceding
             reductions on all stacks) helps prevent double destructor calls
             on yylval in the event of memory exhaustion.  */

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            YYCHK1 (yyprocessOneStack (&yystack, yys, yyposn]b4_lpure_args[));
          yyremoveDeletes (&yystack);
          if (yystack.yytops.yysize == 0)
            {
              yyundeleteLastStack (&yystack);
              if (yystack.yytops.yysize == 0)
                yyFail (&yystack][]b4_lpure_args[, YY_("syntax error"));
              YYCHK1 (yyresolveStack (&yystack]b4_user_args[));
              YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
]b4_locations_if([[           yystack.yyerror_range[1].yystate.yyloc = yylloc;]])[
              yyreportSyntaxError (&yystack]b4_user_args[);
              goto yyuser_error;
            }

          /* If any yyglrShift call fails, it will fail after shifting.  Thus,
             a copy of yylval will already be on stack 0 in the event of a
             failure in the following loop.  Thus, yychar is set to YYEMPTY
             before the loop to make sure the user destructor for yylval isn't
             called twice.  */
          yytoken_to_shift = YYTRANSLATE (yychar);
          yychar = YYEMPTY;
          yyposn += 1;
          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            {
              int yyaction;
              const short int* yyconflicts;
              yy_state_num yystate = yystack.yytops.yystates[yys]->yylrState;
              yygetLRActions (yystate, yytoken_to_shift, &yyaction,
                              &yyconflicts);
              /* Note that yyconflicts were handled by yyprocessOneStack.  */
              YYDPRINTF ((stderr, "On stack %lu, ", (unsigned long int) yys));
              YY_SYMBOL_PRINT ("shifting", yytoken_to_shift, &yylval, &yylloc);
              yyglrShift (&yystack, yys, yyaction, yyposn, &yylval]b4_locations_if([, &yylloc])[);
              YYDPRINTF ((stderr, "Stack %lu now in state #%d\n",
                          (unsigned long int) yys,
                          yystack.yytops.yystates[yys]->yylrState));
            }

          if (yystack.yytops.yysize == 1)
            {
              YYCHK1 (yyresolveStack (&yystack]b4_user_args[));
              YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
              yycompressStack (&yystack);
              break;
            }
        }
      continue;
    yyuser_error:
      yyrecoverSyntaxError (&yystack]b4_user_args[);
      yyposn = yystack.yytops.yystates[0]->yyposn;
    }

  } catch (const yy_parsing_error& err)
  {
    switch (err.get_status())
    {
      case abort: goto yyabortlab;
      case memory_exhausted: goto yyexhaustedlab;
      default: goto yybuglab;
    }
  }

 yyacceptlab:
  yyresult = 0;
  goto yyreturn;

 yybuglab:
  YYASSERT (yyfalse);
  goto yyabortlab;

 yyabortlab:
  yyresult = 1;
  goto yyreturn;

 yyexhaustedlab:
  yyerror (]b4_lyyerror_args[YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;

 yyreturn:
  if (yychar != YYEMPTY)
    yydestruct ("Cleanup: discarding lookahead",
                YYTRANSLATE (yychar), &yylval]b4_locuser_args([&yylloc])[);

  /* If the stack is well-formed, pop the stack until it is empty,
     destroying its entries as we go.  But free the stack regardless
     of whether it is well-formed.  */
  if (yystack.yyitems)
    {
      yy_glr_state** yystates = yystack.yytops.yystates;
      if (yystates)
        {
          size_t yysize = yystack.yytops.yysize;
          size_t yyk;
          for (yyk = 0; yyk < yysize; yyk += 1)
            if (yystates[yyk])
              {
                while (yystates[yyk])
                  {
                    yy_glr_state *yys = yystates[yyk];
]b4_locations_if([[                 yystack.yyerror_range[1].yystate.yyloc = yys->yyloc;]]
)[                  if (yys->yypred != YY_NULLPTR)
                      yydestroyGLRState ("Cleanup: popping", yys]b4_user_args[);
                    yystates[yyk] = yys->yypred;
                    yystack.yynextFree -= 1;
                    yystack.yyspaceLeft += 1;
                  }
                break;
              }
        }
      yyfreeGLRStack (&yystack);
    }

  return yyresult;
}

/* DEBUGGING ONLY */
#if ]b4_api_PREFIX[DEBUG
static void
yy_yypstack (yy_glr_state* yys)
{
  if (yys->yypred)
    {
      yy_yypstack (yys->yypred);
      YYFPRINTF (stderr, " -> ");
    }
  YYFPRINTF (stderr, "%d@@%lu", yys->yylrState,
             (unsigned long int) yys->yyposn);
}

static void
yypstates (yy_glr_state* yyst)
{
  if (yyst == YY_NULLPTR)
    YYFPRINTF (stderr, "<null>");
  else
    yy_yypstack (yyst);
  YYFPRINTF (stderr, "\n");
}

static void
yypstack (yy_glr_stack* yystackp, size_t yyk)
{
  yypstates (yystackp->yytops.yystates[yyk]);
}

#define YYINDEX(YYX)                                                         \
    ((YYX) == YY_NULLPTR ? -1 : (yy_glr_stack_item*) (YYX) - yystackp->yyitems)


static void
yypdumpstack (yy_glr_stack* yystackp)
{
  yy_glr_stack_item* yyp;
  size_t yyi;
  for (yyp = yystackp->yyitems; yyp < yystackp->yynextFree; yyp += 1)
    {
      YYFPRINTF (stderr, "%3lu. ",
                 (unsigned long int) (yyp - yystackp->yyitems));
      if (*(bool *) yyp)
        {
          YYASSERT (yyp->yystate.yyisState);
          YYASSERT (yyp->yyoption.yyisState);
          YYFPRINTF (stderr, "Res: %d, LR State: %d, posn: %lu, pred: %ld",
                     yyp->yystate.yyresolved, yyp->yystate.yylrState,
                     (unsigned long int) yyp->yystate.yyposn,
                     (long int) YYINDEX (yyp->yystate.yypred));
          if (! yyp->yystate.yyresolved)
            YYFPRINTF (stderr, ", firstVal: %ld",
                       (long int) YYINDEX (yyp->yystate
                                             .yysemantics.yyfirstVal));
        }
      else
        {
          YYASSERT (!yyp->yystate.yyisState);
          YYASSERT (!yyp->yyoption.yyisState);
          YYFPRINTF (stderr, "Option. rule: %d, state: %ld, next: %ld",
                     yyp->yyoption.yyrule - 1,
                     (long int) YYINDEX (yyp->yyoption.yystate),
                     (long int) YYINDEX (yyp->yyoption.yynext));
        }
      YYFPRINTF (stderr, "\n");
    }
  YYFPRINTF (stderr, "Tops:");
  for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
    YYFPRINTF (stderr, "%lu: %ld; ", (unsigned long int) yyi,
               (long int) YYINDEX (yystackp->yytops.yystates[yyi]));
  YYFPRINTF (stderr, "\n");
}
#endif

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
