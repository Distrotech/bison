[

/*
template <typename YYParser>
class yy_glr_state
{
  typedef yy_glr_state<YYParser> this_type;
  typedef typename YYParser::semantic_type yys_type;
  typedef typename YYParser::location_type location_type;
public:

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

  void destroy(const std::string& msg, int type]b4_locuser_formals[);

  void yy_yypstack ();

  this_type* pred()
  {
    return yypred;
  }

  yy_state_num get_yylrState() const
  {
    return yylrState;
  }

  yy_semantic_value_abstract<YYParser> *get_yysemantic()
  {
    return yysemantic;
  }

public:
  /// Type tag: always true.
  //bool yyisState; -> dynamic dispatch
  /// Type tag for yysemantics.  If true, yysval applies, otherwise
  /// yyfirstVal applies.
  //bool yyresolved;
  /// Number of corresponding LALR(1) machine state.
  yy_state_num yylrState;
  /// Preceding state in this stack
  this_type* yypred;
  /// Source position of the last token produced by my symbol
  size_t yyposn;

  yy_semantic_value_abstract<YYParser> *yysemantic;
  //struct { // on union, when no variant
  //  /// First in a chain of alternative reductions producing the
  //  /// non-terminal corresponding to this state, threaded through
  //  /// yynext.
  //  yy_semantic_option* yyfirstVal;
  //  /// Semantic value for this state.
  //  YYSTYPE yysval;
  //} yysemantics;
  /// Source location for this state.
  location_type yyloc;
};

template <typename YYParser>
static void yypstates (yy_glr_state<YYParser>* yyst);
*/

template <typename YYParser>
class yy_glr_stateSet {
public:
  typedef typename YYParser::stack_symbol_type state_type;
  yy_glr_stateSet()
  {
    yystates.push_back(YY_NULLPTR);
    yylookaheadNeeds.push_back(false);
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

  state_type* top()
  {
    return yystates.back();
  }

  state_type* operator[] (int index)
  {
    //return yystates[size() - index - 1];
    return yystates[index];
  }

  void pop()
  {
    yystates.pop_back();
    yylookaheadNeeds.pop_back();
  }

  void remove(size_t index)
  {
    yystates.erase(yystates.begin() + index);
    yylookaheadNeeds.erase(yylookaheadNeeds.begin() + index);
  }

  void push_back(state_type* st)
  {
    yystates.push_back(st);
    yylookaheadNeeds.push_back(false);
  }

public:
  std::vector<state_type*> yystates;

public:
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != yyempty_.  */
  std::vector<bool> yylookaheadNeeds;
  //yy_glr_state** yystates;
  //bool* yylookaheadNeeds;
  //size_t yysize, yycapacity;
};

/** Shift all the args of a rule into another vector, to guarantee contiguity
 * in memory.  When accessing $0 or negative elements, follow the linked list.
 */
template <typename YYParser>
class yy_args_stack
{
  typedef typename YYParser::stack_symbol_type state_type;
  typedef yy_semantic_value_abstract<YYParser> semantic_type;
public:
  yy_args_stack(state_type* state, size_t rule_size)
  {
    values.reserve(rule_size);
    for (size_t i = 0; i < rule_size; ++i, state = state->yypred)
      values.push_back(state);
  }

  state_type*& operator[] (int index)
  {
    if (index > 0)
      return values[values.size() - index];
    state_type*& s = values.back();
    for (; index < -1; ++index)
      s = s->yypred;
    return s;
  }

private:
  std::vector<state_type*> values;
  size_t rsize;
};
]
