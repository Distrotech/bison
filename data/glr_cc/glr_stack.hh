[
#define YYCHK(YYE)                              \
  do {                                          \
    YYRESULTTAG yychk_flag = YYE;               \
    if (yychk_flag != yyok)                     \
      return yychk_flag;                        \
  } while (0)



# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc);
#  endif
# endif

/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yypred.  Leaves YYVSP[YYLOW1].yypred
 *  containing the pointer to the next state in the chain.  */
template <typename YYParser>
static void yyfillin (yy_glr_state<YYParser> *, int, int) YY_ATTRIBUTE_UNUSED;

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
 * YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
 * For convenience, always return YYLOW1.  */
template <typename YYParser>
static inline int yyfill (yy_glr_state<YYParser> *, int *, int, bool)
     YY_ATTRIBUTE_UNUSED;

#if !]b4_api_PREFIX[DEBUG
# define YY_REDUCE_PRINT(Args)
#else
# define YY_REDUCE_PRINT(Args)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print Args;               \
} while (0)

/*----------------------------------------------------------------------.
| Report that stack #YYK of *YYSTACKP is going to be reduced by YYRULE. |
`----------------------------------------------------------------------*/

#define YY_STATE_PRINT(Title, YYState)                  \
  YY_SYMBOL_PRINT ("state: " Title,                     \
                   (YYState).yylrState,                 \
                   (YYState).yysemantic.get_value(),    \
                   (YYState).yyloc)

template <typename YYParser>
static void
yy_reduce_print (int yynormal, yy_glr_state<YYParser>* yyvsp, size_t yyk,
                 yy_rule_num yyrule]b4_user_formals[);
#endif








/////////////// GLR STACK //////////////////////










template <typename YYParser>
struct yy_glr_stack {
private:
  typedef typename YYParser::semantic_type YYSTYPE;
  typedef typename YYParser::location_type YYLTYPE;
  typedef yy_glr_state<YYParser> state_type;
  typedef yy_glr_stateSet<YYParser> stateSet_type;
  typedef yy_glr_stack<YYParser> stack_type;
  typedef yy_semantic_option<YYParser> semantic_type;
  int yyerrState;
  state_type yyerror_range[3];
  int yyerrcnt;
  int yychar;
  YYSTYPE yyval;
  YYLTYPE yyloc;
  std::vector<state_type> yystate_pool;
  std::vector<semantic_type> yysemantic_pool;
  //yy_glr_state* yyitems;
  state_type* yysplitPoint;
  state_type* yylastDeleted;
  stateSet_type yytops;

public:
  yy_glr_stack()
  : yyerrState(0)
  , yyerrcnt(0)
  , yysplitPoint(YY_NULLPTR)
  , yylastDeleted(YY_NULLPTR)
  {}

  void yyaddDeferredAction (size_t yyk, state_type* yystate,
                     state_type* yyrhs, yy_rule_num yyrule);

  /** Assuming that YYS is a GLRState somewhere on *YYSTACKP, update the
   *  splitpoint of *YYSTACKP, if needed, so that it is at least as deep as
   *  YYS.  */
  void yyupdateSplit (state_type* yys)
  {
    if (yysplitPoint != YY_NULLPTR && yysplitPoint > yys)
      yysplitPoint = yys;
  }

  /** Invalidate stack #YYK in *YYSTACKP.  */
  void
  yymarkStackDeleted (size_t yyk)
  {
    if (yytops.yystates[yyk] != YY_NULLPTR)
      yylastDeleted = yytops.yystates[yyk];
    yytops.yystates[yyk] = YY_NULLPTR;
  }

  /** Undelete the last stack in *YYSTACKP that was marked as deleted.  Can
      only be done once after a deletion, and only when all other stacks have
      been deleted.  */
  void yyundeleteLastStack ();

  void yyremoveDeletes ();

  void
  yyglrShift (size_t yyk, yy_state_num yylrState, size_t yyposn,
              YYSTYPE* yyvalp, YYLTYPE* yylocp);

  /** Shift stack #YYK of *YYSTACKP, to a new state corresponding to LR
   *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
   *  semantic value of YYRHS under the action for YYRULE.  */
  void yyglrShiftDefer (size_t yyk, yy_state_num yylrState, size_t yyposn,
                        state_type* yyrhs, yy_rule_num yyrule);

  /** Pop the symbols consumed by reduction #YYRULE from the top of stack
   *  #YYK of *YYSTACKP, and perform the appropriate semantic action on their
   *  semantic values.  Assumes that all ambiguities in semantic values
   *  have been previously resolved.  Set *YYVALP to the resulting value,
   *  and *YYLOCP to the computed location (if any).  Return value is as
   *  for userAction.  */
  YYRESULTTAG
  yydoAction (size_t yyk, yy_rule_num yyrule, YYSTYPE* yyvalp);

  /** Pop items off stack #YYK of *YYSTACKP according to grammar rule YYRULE,
   *  and push back on the resulting nonterminal symbol.  Perform the
   *  semantic action associated with YYRULE and store its value with the
   *  newly pushed state, if YYFORCEEVAL or if *YYSTACKP is currently
   *  unambiguous.  Otherwise, store the deferred semantic action with
   *  the new state.  If the new state would have an identical input
   *  position, LR state, and predecessor to an existing state on the stack,
   *  it is identified with that existing state, eliminating stack #YYK from
   *  *YYSTACKP.  In this case, the semantic value is
   *  added to the options for the existing state's semantic value.
   */
  YYRESULTTAG
  yyglrReduce (size_t yyk, yy_rule_num yyrule,
               bool yyforceEval]b4_user_formals[);

  size_t
  yysplitStack (size_t yyk);

  YYRESULTTAG
  yyresolveStack (]b4_user_formals_no_comma[);

  YYRESULTTAG
  yyprocessOneStack (size_t yyk, size_t yyposn]b4_pure_formals[);

  void
  yypstack (size_t yyk);

  /** Resolve the previous YYN states starting at and including state YYS
   *  on *YYSTACKP. If result != yyok, some states may have been left
   *  unresolved possibly with empty semantic option chains.  Regardless
   *  of whether result = yyok, each state has been left with consistent
   *  data so that yydestroyGLRState can be invoked if necessary.  */
  YYRESULTTAG
  yyresolveStates (state_type* yys, int yyn ]b4_user_formals[);

  ]b4_locations_if([[
  /** Resolve the locations for each of the YYN1 states in *YYSTACKP,
   *  ending at YYS1.  Has no effect on previously resolved states.
   *  The first semantic option of a state is always chosen.  */
  void
  yyresolveLocations (state_type *yys1, int yyn1
                                    ]b4_user_formals[);
  ]])[
};





static _Noreturn void
yyFail (const std::string& yymsg);

static _Noreturn void
yyMemoryExhausted ();




]
