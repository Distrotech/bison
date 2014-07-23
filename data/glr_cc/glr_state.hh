[
/** State numbers, as in LALR(1) machine */
typedef int yy_state_num;

class yy_glr_state
{
public:
  yy_glr_state(yy_state_num lr_state, size_t posn, yy_glr_state* state
                     ]b4_locations_if([[, YYLTYPE& loc]])[)
  : yylrState(lr_state)
  , yypred(state)
  , yyposn(posn)
  , yysemantic(new yy_semantic_simple_value())
  {
  ]b4_variant_if([[
    ]b4_symbol_variant([[yystos[yylrState]]], [[yynewState->yysemantics.yysval]],
                       [move], [*yyvalp])], [[
    yynewState->yysemantics.yysval = *yyvalp;]])[
]b4_locations_if([b4_variant_if(
  [[std::swap(yyloc, loc);]],
  [[yyloc = loc;]])])[
  }

  yy_glr_state(yy_state_num lr_state, size_t posn, yy_glr_state* state)
  : yylrState(lr_state)
  , yypred(state)
  , yyposn(posn)
  , yysemantic(YY_NULLPTR)
  {}

  yy_glr_state()
  : yylrState(0)
  , yypred(YY_NULLPTR)
  , yyposn(0)
  , yysemantic(YY_NULLPTR)
  {}

  yy_glr_state(const yy_glr_state& that)
  yy_glr_state& operator=(const yy_glr_state& that);

  yy_glr_state* next()
  {
    return static_cast<yy_glr_state*>(yynext);
  }

  yy_semantic_option * get_semantic_option()
  {
    return static_cast<yy_semantic_option*>(yysemantic);
  }

  void set_semantic_value(yy_semantic_value_abstract * value)
  {
    yysemantic = value;
  }

  void destroy(const std::string& msg);

  void yy_yypstack (yy_glr_state* yys);

private:
  /** Type tag: always true.  */
  //bool yyisState; -> dynamic dispatch
  /** Type tag for yysemantics.  If true, yysval applies, otherwise
   *  yyfirstVal applies.  */
  //bool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
  yy_state_num yylrState;
  /** Preceding state in this stack */
  yy_glr_state* yypred;
  /** Source position of the last token produced by my symbol */
  size_t yyposn;

  yy_semantic_value_abstract *yysemantic;
  //struct { // on union, when no variant
  //  /** First in a chain of alternative reductions producing the
  //   *  non-terminal corresponding to this state, threaded through
  //   *  yynext.  */
  //  yy_semantic_option* yyfirstVal;
  //  /** Semantic value for this state.  */
  //  YYSTYPE yysval;
  //} yysemantics;
  /** Source location for this state.  */
  YYLTYPE yyloc;
};


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

static void yypstates (yy_glr_state* yyst)
{
  if (yyst == YY_NULLPTR)
    YYFPRINTF (stderr, "<null>");
  else
    yyst->yy_yypstack ();
  YYFPRINTF (stderr, "\n");
}

class yy_glr_stateSet {
public:
  yy_glr_stateSet()
  {
    yystates.emplace_back(nullptr);
  }

  size_t size() const
  {
    return yystates.size();
  }

  void split_stack()
  {
    yystates.push_back(yystates.back());
    yylookahaedNeeds.push_back(yylookahaedNeeds.back());
  }

private:
  std::vector<yy_glr_state*> yystates;
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != YYEMPTY.  */
  std::vector<bool> yylookaheadNeeds;
  //yy_glr_state** yystates;
  //bool* yylookaheadNeeds;
  //size_t yysize, yycapacity;
};
]
