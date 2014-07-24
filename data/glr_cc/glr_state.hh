[

template <typename YYParser>
class yy_glr_state
{
  typedef yy_glr_state<YYParser> this_type;
  typedef typename YYParser::semantic_type YYSTYPE;
  typedef typename YYParser::location_type YYLTYPE;
public:
  yy_glr_state(yy_state_num lr_state, size_t posn, this_type* state
                     ]b4_locations_if([[, YYLTYPE& loc]])[);

  yy_glr_state(yy_state_num lr_state, size_t posn, this_type* state)
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

  yy_glr_state(const this_type& that);
  this_type& operator=(const this_type& that);

  yy_semantic_option<YYParser> * get_semantic_option()
  {
    return static_cast<yy_semantic_option<YYParser>*>(yysemantic);
  }

  void set_semantic_value(yy_semantic_value_abstract<YYParser> * value)
  {
    yysemantic = value;
  }

  void destroy(const std::string& msg);

  void yy_yypstack (this_type* yys);

private:
  /** Type tag: always true.  */
  //bool yyisState; -> dynamic dispatch
  /** Type tag for yysemantics.  If true, yysval applies, otherwise
   *  yyfirstVal applies.  */
  //bool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
  yy_state_num yylrState;
  /** Preceding state in this stack */
  this_type* yypred;
  /** Source position of the last token produced by my symbol */
  size_t yyposn;

  yy_semantic_value_abstract<YYParser> *yysemantic;
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

template <typename YYParser>
static void yypstates (yy_glr_state<YYParser>* yyst);

template <typename YYParser>
class yy_glr_stateSet {
public:
  yy_glr_stateSet()
  {
    yystates.emplace_back(YY_NULLPTR);
  }

  size_t size() const
  {
    return yystates.size();
  }

  void split_stack()
  {
    yystates.push_back(yystates.back());
    yylookaheadNeeds.push_back(yylookaheadNeeds.back());
  }

private:
  std::vector<yy_glr_state<YYParser>*> yystates;
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
