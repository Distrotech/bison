b4_namespace_open[

#define YYPROTOTYPE(Type)     \
template <typename YYParser>  \
Type                          \
yy_semantic_option<YYParser>

YYPROTOTYPE()::yy_semantic_option(stack_type* yystack, state_type* rhs, yy_rule_num r, int c,
                   bool has_lookahead, this_type* next
                   ]b4_locations_if([[, location_type loc]])[)
: yyrule(r)
, yystate(rhs)
, yyrawchar(has_lookahead ? c : YYEMPTY)]b4_locations_if([[
, yyloc(loc)]])[
, yynext(next)
{
  if (has_lookahead)
    {
    ]b4_variant_if([[
      ]b4_symbol_variant([[rhs->type_get()]],
                         [[yyval]],
                         [template copy], [rhs->yysemantic->get_value()])], [[
    yyval = yylval;]])[
    }
}

YYPROTOTYPE()::yy_semantic_option(const this_type& other)
: yyrule(other.yyrule)
, yystate(other.yystate)
, yyrawchar(other.yyrawchar)]b4_locations_if([[
, yyloc(other.yyloc)]])[
, yynext(other.yynext)
{
  if (yyrawchar != YYEMPTY)
    {
    ]b4_variant_if([[
      ]b4_symbol_variant([[yystate->type_get()]],
                         [[yyval]],
                         [template copy], [other.yyval])], [[
    yyval = other.yyval;]])[
    }
}

YYPROTOTYPE(yy_semantic_option<YYParser>&)::operator= (this_type const& other)
{
  yyrule = other.yyrule;
  yystate = other.yystate;
  yyrawchar = other.yyrawchar;
  ]b4_symbol_variant([yystate->state],
                     [yyval], [template copy], [other.yyval])[
    yyloc = other.yyloc;
  return *this;
}


YYPROTOTYPE(bool)::operator== (const yy_semantic_option& yyy1) const
{
  if (yyrule == yyy1.yyrule)
    {
      int i = yystack->get_parser()->yyrhs_length (yyrule);
      for (state_type *yys0 = yystate, *yys1 = yyy1.yystate;
           i > 0;
           yys0 = yys0->yypred, yys1 = yys1->yypred, --i)
        if (yys0->yyposn != yys1->yyposn)
          return false;
      return true;
    }
  else
    return false;
}

template <typename YYParser>
yy_semantic_simple_value<YYParser>::yy_semantic_simple_value(const yy_semantic_simple_value& other)
  : yykind(other.yykind)
{
  ]b4_symbol_variant([yykind],
                     [yyvalue], [template copy], [other.yyvalue])[
}

template <typename YYParser>
yy_semantic_simple_value<YYParser>::yy_semantic_simple_value(kind_type kind, yys_type& value)
  : yykind(kind)
{
  ]b4_symbol_variant([yykind],
                     [yyvalue], [template copy], [value])[
}

template <typename YYParser>
template <typename Value>
yy_semantic_simple_value<YYParser>::yy_semantic_simple_value(kind_type kind, const Value& value)
  : yykind(kind)
{
  ]b4_symbol_variant([yykind],
                     [yyvalue], [template copy], [value])[
}

template <typename YYParser>
yy_semantic_simple_value<YYParser>&
yy_semantic_simple_value<YYParser>::operator=(this_type const& other)
{
  yykind = other.yykind;
  ]b4_symbol_variant([yykind],
                     [yyvalue], [template copy], [other.yyvalue])[
}


template <typename YYParser>
yy_semantic_value_abstract<YYParser>*
yy_semantic_simple_value<YYParser>::clone() const
{
  return new yy_semantic_simple_value<YYParser>(*this);
}

YYPROTOTYPE(yy_semantic_value_abstract<YYParser>*)::clone() const
{
  return new yy_semantic_option<YYParser>(*this);
}


/** True iff YYY0 and YYY1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols.  */
//static bool
//yyidenticalOptions (yy_semantic_option* yyy0, yy_semantic_option* yyy1)
// -> operator ==

/** Assuming identicalOptions (YYY0,YYY1), destructively merge the
 *  alternative semantic values for the RHS-symbols of YYY1 and YYY0.  */
YYPROTOTYPE(void)::yymerge_option_sets (yy_semantic_option& yyy1)
{
  int i = yystack->get_parser()->yyrhs_length (yyrule);
  for (state_type *yys0 = yystate, *yys1 = yyy1.yystate;
       i > 0;
       yys0 = yys0->yypred, yys1 = yys1->yypred, --i)
    {
      if (yys0 == yys1)
        break;
      else if (yys0->yysemantic->resolved())
        {
          delete yys0->yysemantic;
          yys0->yysemantic = new yy_semantic_simple_value<]b4_parser_class_name[>
                                 (yys1->state, yys1->yysemantic->get_value());
        }
      else if (yys1->yysemantic->resolved())
        {
          delete yys1->yysemantic;
          yys1->yysemantic =
            new yy_semantic_simple_value<]b4_parser_class_name[>(yys0->state, yys0->yysemantic->get_value());
        }
      else
        {
          this_type** yyz0p = reinterpret_cast<this_type**>(&yys0->yysemantic);
          this_type* yyz1 = static_cast<this_type*>(yys1->yysemantic);
          while (true)
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
                  this_type* yyz = *yyz0p;
                  *yyz0p = yyz1;
                  yyz1 = yyz1->yynext;
                  (*yyz0p)->yynext = yyz;
                }
              yyz0p = &(*yyz0p)->yynext;
            }
          yys1->yysemantic = yys0->yysemantic;
        }
    }
}

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state.  */
YYPROTOTYPE(typename yy_semantic_option<YYParser>::yypreference_value)
::yypreference (yy_semantic_option& y1)
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
# define YYPARSER yystack->get_parser()
YYPROTOTYPE(void)::yyreportTree (int yyindent) const
{
  int yynrhs = yystack->get_parser()->yyrhs_length (yyrule);
  state_type* yys = yystate;
  state_type* yystates[1 + YYMAXRHS];
  state_type yyleftmost_state;

  for (int i = yynrhs; 0 < i; --i, yys = yys->yypred)
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
               yyindent, "", YYPARSER->yy_token_name (YYPARSER->yylhsNonterm (yyrule)),
               yyrule - 1);
  else
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, tokens %lu .. %lu>\n",
               yyindent, "", YYPARSER->yy_token_name (YYPARSER->yylhsNonterm (yyrule)),
               yyrule - 1, (unsigned long int) (yys->yyposn + 1),
               (unsigned long int) yystate->yyposn);
  for (int i = 1; i <= yynrhs; ++i)
    {
      if (yystates[i]->yysemantic->resolved())
        {
          if (yystates[i-1]->yyposn+1 > yystates[i]->yyposn)
            YYFPRINTF (stderr, "%*s%s <empty>\n", yyindent+2, "",
                       YYPARSER->yy_token_name (YYPARSER->yystos_[yystates[i]->state]));
          else
            YYFPRINTF (stderr, "%*s%s <tokens %lu .. %lu>\n", yyindent+2, "",
                       YYPARSER->yy_token_name (YYPARSER->yystos_[yystates[i]->state]),
                       (unsigned long int) (yystates[i-1]->yyposn + 1),
                       (unsigned long int) yystates[i]->yyposn);
        }
      else
        yystates[i]->get_semantic_option()->yyreportTree(yyindent+2);
    }
}
#endif

YYPROTOTYPE(YYRESULTTAG)::yyreportAmbiguity (yy_semantic_option& yyx1]b4_pure_formals[) const
{
  YYUSE (yyx1);

#if ]b4_api_PREFIX[DEBUG
  YYFPRINTF (stderr, "Ambiguity detected.\n");
  YYFPRINTF (stderr, "Option 1,\n");
  yyreportTree (2);
  YYFPRINTF (stderr, "\nOption 2,\n");
  yyx1->yyreportTree (2);
  YYFPRINTF (stderr, "\n");
#endif

  YYPARSER->error (yylocp, YY_("syntax is ambiguous"));
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
yysymbolCopy (int yychar1, YYSTYPE& yyval1, YYLTYPE& yyloc1,
              const int& yychar2, const YYSTYPE& yyval2, const YYLTYPE& yyloc2)
{
  ]b4_symbol_variant([[yychar2]], [[yyval1]],
                     [copy], [yyval2])[]b4_locations_if([
  yyloc1 = yyloc2;])[
}

static inline void
yysymbolSwap (int yychar1, YYSTYPE& yyval1, YYLTYPE& yyloc1,
              int yychar2, YYSTYPE& yyval2, YYLTYPE& yyloc2)
{
  ]b4_symbol_variant([[yychar2]], [[yyval1]],
                     [swap], [yyval2])[]b4_locations_if([[
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



#undef YYPROTOTYPE

]b4_namespace_close
