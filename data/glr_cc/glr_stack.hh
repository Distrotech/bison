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

#if !]b4_api_PREFIX[DEBUG
# define YY_REDUCE_PRINT(Args)
#else
# define YY_REDUCE_PRINT(Args)          \
do {                                    \
  if (yydebug())                        \
    parser->yy_reduce_print_ Args;      \
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
yy_reduce_print (int yynormal, typename YYParser::stack_symbol_type* yyvsp, size_t yyk,
                 yy_rule_num yyrule]b4_user_formals[);
#endif








/////////////// GLR STACK //////////////////////










template <typename YYParser>
struct yy_glr_stack {
public:
  typedef YYParser yyparser;
  typedef typename yyparser::semantic_type yys_type;
  typedef typename yyparser::location_type location_type;
  typedef typename YYParser::stack_symbol_type state_type;
  typedef yy_glr_stateSet<yyparser> stateSet_type;
  typedef yy_glr_stack<yyparser> stack_type;
  typedef yy_semantic_option<yyparser> semantic_type;
  int yyerrState;
  state_type yyerror_range[3];
  int yyerrcnt;
  yys_type yyval;
  location_type yyloc;
  std::vector<state_type> yystate_pool;
  //std::vector<semantic_type> yysemantic_pool;
  //yy_glr_state* yyitems;
  state_type* yysplitPoint;
  state_type* yylastDeleted;
  stateSet_type yytops;
  yyparser* parser;

public:
  yy_glr_stack(yyparser* p)
  : yyerrState(0)
  , yyerrcnt(0)
  , yysplitPoint(YY_NULLPTR)
  , yylastDeleted(YY_NULLPTR)
  , parser(p)
  {}

  yyparser* get_parser()
  {
    return parser;
  }

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
    if (yytops[yyk] != YY_NULLPTR)
    {
      yylastDeleted = yytops[yyk];
      yytops.remove(yyk);
    }
  }

  /** Undelete the last stack in *YYSTACKP that was marked as deleted.  Can
      only be done once after a deletion, and only when all other stacks have
      been deleted.  */
  void yyundeleteLastStack ();

  void yyremoveDeletes ();

  void
  yyglrShift (size_t yyk, yy_state_num yylrState, size_t yyposn,
              yys_type* yyvalp, location_type* yylocp);

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
  yydoAction (size_t yyk, yy_rule_num yyrule,
              yys_type* yyvalp]b4_locations_if([, location_type* yylocp])[);

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
  yyglrReduce (size_t yyk, yy_rule_num yyrule, bool yyforceEval);

  size_t
  yysplitStack (size_t yyk);

  YYRESULTTAG
  yyresolveStack (]b4_user_formals_no_comma[);

  YYRESULTTAG
  yyprocessOneStack (size_t yyk, size_t yyposn]b4_pure_formals[);

  YYRESULTTAG
  yyresolveValue (state_type* yys);

  /** Resolve the states for the RHS of YYOPT on *YYSTACKP, perform its
   *  user action, and return the semantic value and location in *YYVALP
   *  and *YYLOCP.  Regardless of whether result = yyok, all RHS states
   *  have been destroyed (assuming the user action destroys all RHS
   *  semantic values if invoked).  */
  YYRESULTTAG
  yyresolveAction (semantic_type* yyopt, yys_type* yyvalp]b4_locuser_formals[);

  /** Perform user action for rule number YYN, with RHS length YYRHSLEN,
   *  and top stack item YYVSP.  YYLVALP points to place to put semantic
   *  value ($$), and yylocp points to place for location information
   *  (@@$).  Returns yyok for normal return, yyaccept for YYACCEPT,
   *  yyerr for YYERROR, yyabort for YYABORT.  */
  YYRESULTTAG
  yyuserAction (yy_rule_num yyn, size_t yyrhslen, state_type* yyvsp,
                yys_type* yyvalp]b4_locuser_formals[);
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

  bool yydebug() const;
};


]
