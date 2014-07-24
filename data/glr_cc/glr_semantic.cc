b4_namespace_open[


  yy_semantic_option::yy_semantic_option(state_type* rhs, yy_rule_num r, int c,
                     bool has_lookahead, this_type* next
                     ]b4_locations_if([[, YYLTYPE loc]])[)
  : yyrule(r)
  , yystate(rhs)
  , yyrawchar(has_lookahead ? c : YYEMPTY)]b4_locations_if([[
  , yyloc(loc)]])[
  , yynext(next)
  {
    if (has_lookahead)
      {
      ]b4_variant_if([[
        ]b4_symbol_variant([[YYTRANSLATE (yychar)]],
                           [[yyval]],
                           [copy], [yylval])], [[
      yynewOption->yyval = yylval;]])[
      }
  }


yy_semantic_option::this_type& operator= (yy_semantic_option::this_type const& other);
{
  yyrule = other.yyrule;
  yystate = other.yystate;
  yyrawchar = other.yyrawchar;
  ]b4_symbol_variant([yystate->yylrState],
                     [yyval], [copy], [other.yyval])[
    yyloc = other.yyloc;
  return *this;
}


bool
yy_semantic_option::operator== (const yy_semantic_option& yyy1) const
{
  if (yyrule == yyy1.yyrule)
    {
      int i = yyrhsLength (yyy0->yyrule);
      for (yy_glr_state *yys0 = yyy0->yystate, *yys1 = yyy1->yystate;
           i > 0;
           yys0 = yys0->yynext, yys1 = yys1->yynext, --i)
        if (yys0->yyposn != yys1->yyposn)
          return false;
      return true;
    }
  else
    return false;
}


/** True iff YYY0 and YYY1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols.  */
//static bool
//yyidenticalOptions (yy_semantic_option* yyy0, yy_semantic_option* yyy1)
// -> operator ==

/** Assuming identicalOptions (YYY0,YYY1), destructively merge the
 *  alternative semantic values for the RHS-symbols of YYY1 and YYY0.  */
void
yy_semantic_option::yymerge_option_sets (yy_semantic_option& yyy1)
{
  int i = yyrhsLength (yyy0->yyrule);
  for (yy_glr_state *yys0 = yyy0->yystate, *yys1 = yyy1->yystate;
       i > 0;
       yys0 = yys0->yypred, yys1 = yys1->yypred, --i)
    {
      if (yys0 == yys1)
        break;
      else if (yys0->yyresolved)
        {
          yys1->yyresolved = yytrue;
          ]b4_variant_if(b4_symbol_variant([yys1->yylrState],
                                           [yys1->yysemantics.yysval],
                                           [copy],
                                           [yys0->yysemantics.yysval]),
                         [yys1->yysemantics.yysval = yys0->yysemantics.yysval;])[
        }
      else if (yys1->yyresolved)
        {
          yys0->yyresolved = yytrue;
          ]b4_variant_if(b4_symbol_variant([yys0->yylrState],
                                           [yys0->yysemantics.yysval],
                                           [copy],
                                           [yys1->yysemantics.yysval]),
                         [yys0->yysemantics.yysval = yys1->yysemantics.yysval;])[
        }
      else
        {
          yy_semantic_option** yyz0p = &yys0->yysemantics.yyfirstVal;
          yy_semantic_option* yyz1 = yys1->yysemantics.yyfirstVal;
          while (yytrue)
            {
              if (yyz1 == *yyz0p || yyz1 == YY_NULLPTR)
                break;
              else if (*yyz0p == YY_NULLPTR)
                {
                  *yyz0p = yyz1;
                  break;
                }
              else if (*yyz0p < yyz1)
                {
                  yy_semantic_option* yyz = *yyz0p;
                  *yyz0p = yyz1;
                  yyz1 = yyz1->yynext;
                  (*yyz0p)->yynext = yyz;
                }
              yyz0p = &(*yyz0p)->yynext;
            }
          yys1->yysemantics.yyfirstVal = yys0->yysemantics.yyfirstVal;
        }
    }
}

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state.  */
yy_semantic_option::yypreference_value
yy_semantic_option::yypreference (yy_semantic_option& y1)
{
  yy_rule_num r0 = yyrule, r1 = y1.yyrule;
  int p0 = yydprec[r0], p1 = yydprec[r1];

  if (p0 == p1)
    return (yymerger[r0] == 0 || yymerger[r0] != yymerger[r1]) ?
      no_combination : user_mergeable;
  if (p0 == 0 || p1 == 0)
    return no_combination;
  if (p0 < p1)
    return right_preferred;
  if (p1 < p0)
    return left_preferred;
  return no_combination;
}


#if ]b4_api_PREFIX[DEBUG
void
yy_semantic_option::yyreportTree (int yyindent) const
{
  int yynrhs = yyrhsLength (yyrule);
  yy_glr_state* yys;
  yy_glr_state* yystates[1 + YYMAXRHS];
  yy_glr_state yyleftmost_state;

  for (int i = yynrhs, yys = yystate; 0 < i; --i, yys = yys->yypred)
    yystates[i] = yys;
  if (yys == YY_NULLPTR)
    {
      yyleftmost_state.yyposn = 0;
      yystates[0] = &yyleftmost_state;
    }
  else
    yystates[0] = yys;

  if (yystate->yyposn < yys->yyposn + 1)
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, empty>\n",
               yyindent, "", yytokenName (yylhsNonterm (yyrule)),
               yyrule - 1);
  else
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, tokens %lu .. %lu>\n",
               yyindent, "", yytokenName (yylhsNonterm (yyrule)),
               yyrule - 1, (unsigned long int) (yys->yyposn + 1),
               (unsigned long int) yystate->yyposn);
  for (int i = 1; i <= yynrhs; ++i)
    {
      if (yystates[i]->yyresolved)
        {
          if (yystates[i-1]->yyposn+1 > yystates[i]->yyposn)
            YYFPRINTF (stderr, "%*s%s <empty>\n", yyindent+2, "",
                       yytokenName (yystos[yystates[i]->yylrState]));
          else
            YYFPRINTF (stderr, "%*s%s <tokens %lu .. %lu>\n", yyindent+2, "",
                       yytokenName (yystos[yystates[i]->yylrState]),
                       (unsigned long int) (yystates[i-1]->yyposn + 1),
                       (unsigned long int) yystates[i]->yyposn);
        }
      else
        yystates[i]->yysemantics.yyfirstVal->yyreportTree(yyindent+2);
    }
}
#endif

YYRESULTTAG
yy_semantic_option::yyreportAmbiguity (yy_semantic_option& yyx1]b4_pure_formals[) const
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
}


// YYSTYPE

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

]b4_variant_if([[
static inline void
yysymbolCopy (int& yychar1, YYSTYPE& yyval1, YYLTYPE& yyloc1,
              const int& yychar2, const YYSTYPE& yyval2, const YYLTYPE& yyloc2)
{
  ]b4_symbol_variant([[YYTRANSLATE (yychar2)]], [[yyval1]],
                     [copy], [yyval2])[
  yychar1 = yychar2;]b4_locations_if([
  yyloc1 = yyloc2;])[
}

static inline void
yysymbolSwap (int& yychar1, YYSTYPE& yyval1, YYLTYPE& yyloc1,
              int& yychar2, YYSTYPE& yyval2, YYLTYPE& yyloc2)
{
  ]b4_symbol_variant([[YYTRANSLATE (yychar2)]], [[yyval1]],
                     [swap], [yyval2])[
  std::swap (yychar1, yychar2);]b4_locations_if([[
  std::swap (yyloc1,  yyloc2);]])[
}
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










]b4_namespace_close
