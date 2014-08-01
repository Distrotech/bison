b4_namespace_open[


/*
#define YYPROTOTYPE(Type)     \
template <typename YYParser>  \
Type                          \
yy_glr_state<YYParser>


template <typename YYParser>
void yypstates (typename YYParser::symbol_type* yyst)
{
  if (yyst == YY_NULLPTR)
    YYFPRINTF (stderr, "<null>");
  else
    yyst->yy_yypstack ();
  YYFPRINTF (stderr, "\n");
}


YYPROTOTYPE(void)::destroy(const std::string& msg, int type]b4_locuser_formals[)
{
  if (yysemantic)
    yysemantic->destroy(msg, type]b4_locuser_args[);
}

YYPROTOTYPE(void)::yy_yypstack ()
{
  if (yypred)
    {
      yy_yypstack (yypred);
      YYFPRINTF (stderr, " -> ");
    }
  YYFPRINTF (stderr, "%d@@%lu", yylrState,
             (unsigned long int) yyposn);
}

#undef YYPROTOTYPE
*/


]b4_namespace_close
