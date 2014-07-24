b4_namespace_open[



template <typename YYParser>
static void yypstates (yy_glr_state<YYParser>* yyst)
{
  if (yyst == YY_NULLPTR)
    YYFPRINTF (stderr, "<null>");
  else
    yyst->yy_yypstack ();
  YYFPRINTF (stderr, "\n");
}

yy_glr_state::yy_glr_state(yy_state_num lr_state, size_t posn, this_type* state
                     ]b4_locations_if([[, YYLTYPE& loc]])[)
  : yylrState(lr_state)
  , yypred(state)
  , yyposn(posn)
  , yysemantic(new yy_semantic_simple_value<YYParser>())
  {
  ]b4_variant_if([[
    ]b4_symbol_variant([[yystos[yylrState]]], [[yynewState->yysemantics.yysval]],
                       [move], [*yyvalp])], [[
    yynewState->yysemantics.yysval = *yyvalp;]])[
]b4_locations_if([b4_variant_if(
  [[std::swap(yyloc, loc);]],
  [[yyloc = loc;]])])[
  }

void yy_glr_state::destroy(const std::string& msg)
{
  if (yysemantics)
    yysemantics->destroy(msg, yystos[yylrState]]b4_locuser_args([&yyloc])[);
}

void yy_glr_state::yy_yypstack ()
{
  if (yypred)
    {
      yy_yypstack (yypred);
      YYFPRINTF (stderr, " -> ");
    }
  YYFPRINTF (stderr, "%d@@%lu", yylrState,
             (unsigned long int) yyposn);
}



]b4_namespace_close
