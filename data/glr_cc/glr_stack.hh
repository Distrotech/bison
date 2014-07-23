[
#define YYCHK(YYE)                              \
  do {                                          \
    YYRESULTTAG yychk_flag = YYE;               \
    if (yychk_flag != yyok)                     \
      return yychk_flag;                        \
  } while (0)

#if ]b4_api_PREFIX[DEBUG

# ifndef YYFPRINTF
#  define YYFPRINTF fprintf
# endif

]b4_yy_location_print_define[

# define YYDPRINTF(Args)                        \
  do {                                          \
    if (yydebug)                                \
      YYFPRINTF Args;                           \
  } while (0)

]b4_yy_symbol_print_define[

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                  \
  do {                                                                  \
    if (yydebug)                                                        \
      {                                                                 \
        YYFPRINTF (stderr, "%s ", Title);                               \
        yy_symbol_print (stderr, Type, Value]b4_locuser_args([Location])[);        \
        YYFPRINTF (stderr, "\n");                                       \
      }                                                                 \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

struct yy_glr_stack;
static void yypstack (struct yy_glr_stack* yystackp, size_t yyk)
  YY_ATTRIBUTE_UNUSED;
static void yypdumpstack (struct yy_glr_stack* yystackp)
  YY_ATTRIBUTE_UNUSED;

#else /* !]b4_api_PREFIX[DEBUG */

# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)

#endif /* !]b4_api_PREFIX[DEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH ]b4_stack_depth_init[
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYMAXDEPTH * sizeof (GLRStackItem)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH ]b4_stack_depth_max[
#endif

/* Minimum number of free items on the stack allowed after an
   allocation.  This is to allow allocation and initialization
   to be completed by functions that call yyexpandGLRStack before the
   stack is expanded, thus insuring that all necessary pointers get
   properly redirected to new data.  */
#define YYHEADROOM 2

#ifndef YYSTACKEXPANDABLE
#  define YYSTACKEXPANDABLE 1
#endif

#if YYSTACKEXPANDABLE
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyexpandGLRStack (Yystack);                       \
  } while (0)
#else
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyMemoryExhausted (Yystack);                      \
  } while (0)
#endif


#if YYERROR_VERBOSE

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif


/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yypred.  Leaves YYVSP[YYLOW1].yypred
 *  containing the pointer to the next state in the chain.  */
static void yyfillin (yy_glr_state *, int, int) YY_ATTRIBUTE_UNUSED;
static void
yyfillin (yy_glr_state *yyvsp, int yylow0, int yylow1)
{
  int i;
  yy_glr_state *s = yyvsp[yylow0].yypred;
  for (i = yylow0-1; i >= yylow1; i -= 1)
    {
      //      YYASSERT (yyvsp[i].yystate.yyisState);
#if ]b4_api_PREFIX[DEBUG
      yyvsp[i].yylrState = s->yylrState;
#endif
      yyvsp[i].yyresolved = s->yyresolved;
      if (s->yyresolved)
        {
          //      std::cerr << "Resolved, copy" << std::endl;]b4_variant_if([[
           ]b4_symbol_variant([[yystos[s->yylrState]]],
                              [[yyvsp[i].yysemantic->get_value()]],
                              [copy], [s->yysemantic->get_value()])], [[
           yyvsp[i].yysemantic = s->yysemantic;]])[;
        }
      else
        /* The effect of using yysval or yyloc (in an immediate rule) is
         * undefined.  */
        yyvsp[i].yysemantic = YY_YY_NULLPTR;]b4_locations_if([[
      yyvsp[i].yyloc = s->yyloc;]])[
      s = yyvsp[i].yypred = s->yypred;
    }
}

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
 * YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
 * For convenience, always return YYLOW1.  */
static inline int yyfill (yy_glr_state *, int *, int, bool)
     YY_ATTRIBUTE_UNUSED;
static inline int
yyfill (yy_glr_state *yyvsp, int *yylow, int yylow1, bool yynormal)
{
  if (!yynormal && yylow1 < *yylow)
    {
      yyfillin (yyvsp, *yylow, yylow1);
      *yylow = yylow1;
    }
  return yylow1;
}


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

static inline void
yy_reduce_print (int yynormal, yy_glr_state* yyvsp, size_t yyk,
                 yy_rule_num yyrule]b4_user_formals[)
{
  int yynrhs = yyrhsLength (yyrule);]b4_locations_if([
  int yylow = 1;])[
  YYFPRINTF (stderr, "Reducing stack %lu by rule %d (line %lu):\n",
             (unsigned long int) yyk, yyrule - 1,
             (unsigned long int) yyrline[yyrule]);
  if (!yynormal)
    yyfillin (yyvsp, 1, -yynrhs);
  /* The symbols being reduced.  */
  for (int i = 0; i < yynrhs; ++i)
    {
      YYFPRINTF (stderr, "   $%d = ", i + 1);
      yy_symbol_print (stderr,
                       yystos[yyvsp[i - yynrhs + 1].yylrState],
                       &yyvsp[i - yynrhs + 1].yysemantic.get_value()
                       ]b4_locations_if([, &]b4_rhs_location(yynrhs, i + 1))[]dnl
                       b4_user_args[);
      if (!yyvsp[i - yynrhs + 1].yyresolved)
        YYFPRINTF (stderr, " (unresolved)");
      YYFPRINTF (stderr, "\n");
    }
}
#endif








/////////////// GLR STACK //////////////////////










struct yy_glr_stack {
private:
  int yyerrState;
  yy_glr_stack_item yyerror_range[3];
  int yyerrcnt;
  int yychar;
  YYSTYPE yyval;
  YYLTYPE yyloc;
  std::vector<yy_glr_state> yystate_pool;
  std::vector<yy_glr_semantic_option> yysemantic_pool;
  //yy_glr_state* yyitems;
  yy_glr_state* yysplitPoint;
  yy_glr_state* yylastDeleted;
  yy_glr_stateSet yytops;

public:
  yy_glr_stack()
  : yyerrState(0)
  , yyerrcnt(0)
  , yysplitPoint(YY_NULLPTR)
  , yylastDeleted(YY_NULLPTR)
  {}

  void yyaddDeferredAction (size_t yyk, yy_glr_state* yystate,
                     yy_glr_state* yyrhs, yy_rule_num yyrule);

  /** Assuming that YYS is a GLRState somewhere on *YYSTACKP, update the
   *  splitpoint of *YYSTACKP, if needed, so that it is at least as deep as
   *  YYS.  */
  void yyupdateSplit (yy_glr_state* yys)
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
                        yy_glr_state* yyrhs, yy_rule_num yyrule);

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
  yy_glr_stack::yyresolveStack (]b4_user_formals_no_comma[);

  YYRESULTTAG
  yy_glr_stack::yyprocessOneStack (size_t yyk, size_t yyposn]b4_pure_formals[);

  void
  yy_glr_stack::yypstack (size_t yyk);

  /** Resolve the previous YYN states starting at and including state YYS
   *  on *YYSTACKP. If result != yyok, some states may have been left
   *  unresolved possibly with empty semantic option chains.  Regardless
   *  of whether result = yyok, each state has been left with consistent
   *  data so that yydestroyGLRState can be invoked if necessary.  */
  YYRESULTTAG
  yyresolveStates (yy_glr_state* yys, int yyn ]b4_user_formals[)
};





//static void yyexpandGLRStack (yy_glr_stack* yystackp);

static _Noreturn void
yyFail (const std::string& yymsg)
{
  if (yymsg != YY_YY_NULLPTR)
    yyerror (yymsg);
  throw yy_parsing_error(yy_parsing_error::error_status::abort);
}

static _Noreturn void
yyMemoryExhausted ()
{
  throw yy_parsing_error(yy_parsing_error::error_status::memory_exhausted);
}

/** Return a fresh GLRStackItem in YYSTACKP.  The item is an LR state
 *  if YYISSTATE, and otherwise a semantic option.  Callers should call
 *  YY_RESERVE_GLRSTACK afterwards to make sure there is sufficient
 *  headroom.  */

//static inline yy_glr_stack_item*
//yynewGLRStackItem (yy_glr_stack* yystackp, bool yyisState)

/** Add a new semantic action that will execute the action for rule
 *  YYRULE on the semantic values in YYRHS to the list of
 *  alternative actions for YYSTATE.  Assumes that YYRHS comes from
 *  stack #YYK of *YYSTACKP. */
void
yy_glr_stack::yyaddDeferredAction (size_t yyk, yy_glr_state* yystate,
                     yy_glr_state* yyrhs, yy_rule_num yyrule)
{
  //  std::cerr << "yyaddDeferredAction" << std::endl;
  //  yypdumpstack(yystackp);
  yysemantic_pool.push_back(yy_glr_state(yyrhs, yyrule, yychar,
                             yytops.yylookaheadNeeds[yyk], yystate->get_semantic_option()));
  yystate->set_semantic_value(&yysemantic_pool.back());

  //  std::cerr << "yyaddDeferredAction: done" << std::endl;
}

///** Initialize *YYSTACKP to a single empty stack, with total maximum
// *  capacity for all stacks of YYSIZE.  */
//static bool
//yyinitGLRStack (yy_glr_stack* yystackp, size_t yysize)

///** If *YYSTACKP is expandable, extend it.  WARNING: Pointers into the
//    stack from outside should be considered invalid after this call.
//    We always expand when there are 1 or fewer items left AFTER an
//    allocation, so that we can avoid having external pointers exist
//    across an allocation.  */
//static void
//yyexpandGLRStack (yy_glr_stack* yystackp)
//
//static void
//yyfreeGLRStack (yy_glr_stack* yystackp)


/** Undelete the last stack in *YYSTACKP that was marked as deleted.  Can
    only be done once after a deletion, and only when all other stacks have
    been deleted.  */
void
yy_glr_stack::yyundeleteLastStack ()
{
  if (yylastDeleted == YY_NULLPTR || yytops.yysize != 0)
    return;
  yytops.yystates[0] = yylastDeleted;
  yytops.yysize = 1;
  YYDPRINTF ((stderr, "Restoring last deleted stack as stack #0.\n"));
  yylastDeleted = YY_NULLPTR;
}

void
yy_glr_stack::yyremoveDeletes ()
{
  size_t i = 0, j = 0;
  while (j < yytops.yysize)
    {
      if (yytops.yystates[i] == YY_NULLPTR)
        {
          if (i == j)
            {
              YYDPRINTF ((stderr, "Removing dead stacks.\n"));
            }
          yytops.yysize -= 1;
        }
      else
        {
          yytops.yystates[j] = yytops.yystates[i];
          /* In the current implementation, it's unnecessary to copy
             yystackp->yytops.yylookaheadNeeds[i] since, after
             yyremoveDeletes returns, the parser immediately either enters
             deterministic operation or shifts a token.  However, it doesn't
             hurt, and the code might evolve to need it.  */
          yytops.yylookaheadNeeds[j] = yytops.yylookaheadNeeds[i];
          if (j != i)
            {
              YYDPRINTF ((stderr, "Rename stack %lu -> %lu.\n",
                          (unsigned long int) i, (unsigned long int) j));
            }
          j += 1;
        }
      i += 1;
    }
}

/** Shift to a new state on stack #YYK of *YYSTACKP, corresponding to LR
 * state YYLRSTATE, at input position YYPOSN, with (resolved) semantic
 * value *YYVALP and source location *YYLOCP.  */
void
yy_glr_stack::yyglrShift (size_t yyk, yy_state_num yylrState, size_t yyposn,
                          YYSTYPE* yyvalp, YYLTYPE* yylocp)
{
  yystate_pool.push_back(yy_glr_state(yylrState, yyposn,
                            yytops.yystates[yyk]
                            ]b4_locations_if([[, *yylocp]])[));

  //  std::cerr << "Shifting at: " << *yylocp << std::endl;
  //  std::cerr << "Shifting: " << *yyvalp << std::endl;

  yytops.yystates[yyk] = &yystate_pool.back();
}

/** Shift stack #YYK of *YYSTACKP, to a new state corresponding to LR
 *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
 *  semantic value of YYRHS under the action for YYRULE.  */
void
yy_glr_stack::yyglrShiftDefer (size_t yyk, yy_state_num yylrState, size_t
                               yyposn, yy_glr_state* yyrhs, yy_rule_num yyrule)
{
  //  std::cerr << "yyglrShiftDefer" << std::endl;
  yystate_pool.emplace_back(yylrState, yyposn,
                            yytops.yystates[yyk]);
  yytops.yystates[yyk] = &yystate_pool.back();

  /* Invokes YY_RESERVE_GLRSTACK.  */
  yyaddDeferredAction (yyk, &yystate_pool.back(), yyrhs, yyrule);
  //  std::cerr << "yyglrShiftDefer: done" << std::endl;
}

/** Pop the symbols consumed by reduction #YYRULE from the top of stack
 *  #YYK of *YYSTACKP, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved.  Set *YYVALP to the resulting value,
 *  and *YYLOCP to the computed location (if any).  Return value is as
 *  for userAction.  */
YYRESULTTAG
yy_glr_stack::yydoAction (size_t yyk, yy_rule_num yyrule, YYSTYPE* yyvalp)
{
  int yynrhs = yyrhsLength (yyrule);

  if (yysplitPoint == YY_NULLPTR)
    {
      /* Standard special case: single stack.  */
      yy_glr_stack_item yyrhs;
      yyrsh.swap(*yytops.yystates[yyk]);
      YYASSERT (yyk == 0);
      yystate_pool.pop_back();
      yytops.yystates[0] = &yystate_pool.back();
      YY_REDUCE_PRINT ((1, &yyrhs, yyk, yyrule]b4_user_args[));
      return yyuserAction (yyrule, yynrhs, &yyrhs,
                           yyvalp]b4_locuser_args[);
    }
  else
    {
      yy_glr_state* yys;
      yy_glr_state yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
      yys = yyrhsVals[YYMAXRHS + YYMAXLEFT].yypred
        = yytops.yystates[yyk];]b4_locations_if([[
      if (yynrhs == 0)
        /* Set default location.  */
        yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yyloc = yys->yyloc;]])[
      for (int i = 0; i < yynrhs; ++i)
        {
          yys = yys->yypred;
          YYASSERT (yys);
        }
      yyupdateSplit (yys);
      yystackp->yytops.yystates[yyk] = yys;
      YY_REDUCE_PRINT ((0, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1, yyk, yyrule]b4_user_args[));
      return yyuserAction (yyrule, yynrhs, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yyvalp]b4_locuser_args[);
    }
}

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
yy_glr_stack::yyglrReduce (size_t yyk, yy_rule_num yyrule,
                           bool yyforceEval]b4_user_formals[)
{
  size_t yyposn = yytops.yystates[yyk]->yyposn;

  if (yyforceEval || yystackp->yysplitPoint == YY_NULLPTR)
    {
      YYSTYPE yysval;]b4_locations_if([[
      YYLTYPE yyloc;]])[

      YYRESULTTAG yyflag = yydoAction (yyk, yyrule, &yysval]b4_locuser_args([&yyloc])[);
      //FIXME: Exception
      if (yyflag == yyerr && yysplitPoint != YY_NULLPTR)
        {
          YYDPRINTF ((stderr, "Parse on stack %lu rejected by rule #%d.\n",
                     (unsigned long int) yyk, yyrule - 1));
        }
      if (yyflag != yyok)
        {
          //          std::cerr << "YYFLAG not OK" << std::endl;
          ]b4_variant_if([b4_symbol_variant([[yyr1[yyrule]]],
                                            [[yysval]], [destroy])]);[
          return yyflag;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyrule], &yysval, &yyloc);
      //      std::cerr << "Before shitf" << std::endl;
      yyglrShift (yystackp, yyk,
                  yy_lr_goto_state (yytops.yystates[yyk]->yylrState,
                                 yylhsNonterm (yyrule)),
                  yyposn, &yysval]b4_locations_if([, &yyloc])[);
      //      std::cerr << "After shitf" << std::endl;
    }
  else
    {
      yy_glr_state* yys = yytops.yystates[yyk];
      for (int i = yyrhsLength (yyrule); 0 < i; --i)
        {
          yys = yys->yypred;
          YYASSERT (yys);
        }
      yyupdateSplit (yys);

      yy_state_num yynewLRState = yy_lr_goto_state (yys->yylrState,
                                                 yylhsNonterm (yyrule));
      YYDPRINTF ((stderr,
                  "Reduced stack %lu by rule #%d; action deferred.  "
                  "Now in state %d.\n",
                  (unsigned long int) yyk, yyrule - 1, yynewLRState));

      yy_glr_state* yys0 = yytops.yystates[yyk];
      for (size_t i = 0; i < yytops.yysize; i += 1)
        if (i != yyk && yytops.yystates[i] != YY_NULLPTR)
          {
            yy_glr_state *yysplit = yysplitPoint;
            yy_glr_state *yyp = yytops.yystates[i];
            while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn)
              {
                if (yyp->yylrState == yynewLRState && yyp->yypred == yys)
                  {
                    yyaddDeferredAction (yyk, yyp, yys0, yyrule);
                    yymarkStackDeleted (yyk);
                    YYDPRINTF ((stderr, "Merging stack %lu into stack %lu.\n",
                                (unsigned long int) yyk,
                                (unsigned long int) i));
                    return yyok;
                  }
                yyp = yyp->yypred;
              }
          }

      yystackp->yytops.yystates[yyk] = yys;
      yyglrShiftDefer (yyk, yynewLRState, yyposn, yys0, yyrule);
    }
  return yyok;
}

size_t
yy_glr_stack::yysplitStack (size_t yyk)
{
  if (yysplitPoint == YY_NULLPTR)
    {
      YYASSERT (yyk == 0);
      yysplitPoint = yytops.yystates[yyk];
    }
  yytops.split_stack();
  return yytops.size() - 1;
}

YYRESULTTAG
yy_glr_stack::yyresolveStack (]b4_user_formals_no_comma[)
{
  if (yysplitPoint != YY_NULLPTR)
    {
      yy_glr_state* yys = yytops.yystates[0];
      int n = 0;

      for (; yys != yysplitPoint; yys = yys->yypred, ++n)
        continue;
      YYCHK (yyresolveStates (yytops.yystates[0], n ]b4_user_args[));
    }
  return yyok;
}

YYRESULTTAG
yy_glr_stack::yyprocessOneStack (size_t yyk, size_t yyposn]b4_pure_formals[)
{
  while (yytops.yystates[yyk] != YY_NULLPTR)
    {
      yy_state_num yystate = yytops.yystates[yyk]->yylrState;
      YYDPRINTF ((stderr, "Stack %lu Entering state %d\n",
                  (unsigned long int) yyk, yystate));

      YYASSERT (yystate != YYFINAL);

      if (yyisDefaultedState (yystate))
        {
          yy_rule_num yyrule = yydefaultAction (yystate);
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, "Stack %lu dies.\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yyk);
              return yyok;
            }
          YYRESULTTAG yyflag = yyglrReduce (yyk, yyrule,
                                            yyimmediate[yyrule]]b4_user_args[);
          if (yyflag == yyerr)
            {
              YYDPRINTF ((stderr,
                          "Stack %lu dies "
                          "(predicate failure or explicit user error).\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yyk);
              return yyok;
            }
          if (yyflag != yyok)
            return yyflag;
        }
      else
        {
          yy_symbol yytoken;
          int yyaction;
          const short int* yyconflicts;

          yytops.yylookaheadNeeds[yyk] = true;
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
              yytoken = yytranslate_ (yychar);
              YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
            }

          yygetLRActions (yytoken, &yyaction, &yyconflicts);

          while (*yyconflicts != 0)
            {
              size_t yynewStack = yysplitStack (yyk);
              YYDPRINTF ((stderr, "Splitting off stack %lu from %lu.\n",
                          (unsigned long int) yynewStack,
                          (unsigned long int) yyk));
              YYRESULTTAG yyflag = yyglrReduce (yynewStack, *yyconflicts,
                                    yyimmediate[*yyconflicts]]b4_user_args[);
              if (yyflag == yyok)
                YYCHK (yyprocessOneStack (yynewStack,
                                          yyposn]b4_pure_args[));
              else if (yyflag == yyerr)
                {
                  YYDPRINTF ((stderr, "Stack %lu dies.\n",
                              (unsigned long int) yynewStack));
                  yymarkStackDeleted (yynewStack);
                }
              else
                return yyflag;
              ++yyconflicts;
            }

          if (yyisShiftAction (yyaction))
            break;
          else if (yyisErrorAction (yyaction))
            {
              YYDPRINTF ((stderr, "Stack %lu dies.\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yyk);
              break;
            }
          else
            {
              YYRESULTTAG yyflag = yyglrReduce (yyk, -yyaction,
                                                yyimmediate[-yyaction]]b4_user_args[);
              if (yyflag == yyerr)
                {
                  YYDPRINTF ((stderr,
                              "Stack %lu dies "
                              "(predicate failure or explicit user error).\n",
                              (unsigned long int) yyk));
                  yymarkStackDeleted (yyk);
                  break;
                }
              else if (yyflag != yyok)
                return yyflag;
            }
        }
    }
  return yyok;
}

static void
yy_glr_stack::yyrecoverSyntaxError ()
{
  if (yyerrState == 3)
    /* We just shifted the error token and (perhaps) took some
       reductions.  Skip tokens until we can proceed.  */
    while (true)
      {
        yy_symbol yytoken;
        if (yychar == YYEOF)
          yyFail ("");
        if (yychar != YYEMPTY)
          {]b4_locations_if([[
            /* We throw away the lookahead, but the error range
               of the shifted error token must take it into account.  */
            yy_glr_state *yys = yytops.yystates[0];
            yy_glr_stack_item yyerror_range[3];
            yyerror_range[1].yystate.yyloc = yys->yyloc;
            yyerror_range[2].yystate.yyloc = yylloc;
            YYLLOC_DEFAULT ((yys->yyloc), yyerror_range, 2);]])[
            yytoken = yytranslate_ (yychar);
            yydestruct ("Error: discarding",
                        yytoken, &yylval]b4_locuser_args([&yylloc])[);
          }
        YYDPRINTF ((stderr, "Reading a token: "));
        yychar = ]b4_lex[;
        if (yychar <= YYEOF)
          {
            yychar = yytoken = YYEOF;
            YYDPRINTF ((stderr, "Now at end of input.\n"));
          }
        else
          {
            yytoken = YTRANSLATE (yychar);
            YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
          }
        int j = yypact[yytops.yystates[0]->yylrState];
        if (yypact_value_is_default_ (j))
          return;
        j += yytoken;
        if (j < 0 || YYLAST < j || yycheck[j] != yytoken)
          {
            if (yydefact[yytops.yystates[0]->yylrState] != 0)
              return;
          }
        else if (! yytable_value_is_error (yytable[j]))
          return;
      }

  /* Reduce to one stack.  */
  {
    size_t yyk = 0;
    for (; yyk < yytops.yysize; yyk += 1)
      if (yytops.yystates[yyk] != YY_NULLPTR)
        break;
    if (yyk >= yytops.yysize)
      yyFail ("");
    for (yyk += 1; yyk < yytops.yysize; yyk += 1)
      yymarkStackDeleted (yyk);
  }
  yyremoveDeletes ();

  /* Now pop stack until we find a state that shifts the error token.  */
  yyerrState = 3;
  while (yytops.yystates[0] != YY_NULLPTR)
    {
      yy_glr_state *yys = yytops.yystates[0];
      int j = yypact[yys->yylrState];
      if (! yypact_value_is_default_ (j))
        {
          j += YYTERROR;
          if (0 <= j && j <= YYLAST && yycheck[j] == YYTERROR
              && yyisShiftAction (yytable[j]))
            {
              /* Shift the error token.  */]b4_locations_if([[
              /* First adjust its location.*/
              YYLTYPE yyerrloc;
              yyerror_range[2].yystate.yyloc = yylloc;
              YYLLOC_DEFAULT (yyerrloc, (yyerror_range), 2);]])[
              YY_SYMBOL_PRINT ("Shifting", yystos[yytable[j]],
                               &yylval, &yyerrloc);
              yyglrShift (0, yytable[j],
                          yys->yyposn, &yylval]b4_locations_if([, &yyerrloc])[);
              yys = yytops.yystates[0];
              break;
            }
        }]b4_locations_if([[
      yyerror_range[1].yystate.yyloc = yys->yyloc;]])[
      if (yys->yypred != YY_NULLPTR)
        yydestroyGLRState ("Error: popping", yys]b4_user_args[);
      yytops.yystates[0] = yys->yypred;
      yynextFree -= 1;
      yyspaceLeft += 1;
    }
  if (yytops.yystates[0] == YY_NULLPTR)
    yyFail ("");
}

void
yy_glr_stack::yypstack (size_t yyk)
{
  yypstates (yytops.yystates[yyk]);
}


//#define YYINDEX(YYX)                                                         \
//    ((YYX) == YY_NULLPTR ? -1 : (yy_glr_stack_item*) (YYX) - yystackp->yyitems)
//
//void
//yy_glr_stack::yypdumpstack ()
//{
//  yy_glr_state* yyp;
//  size_t yyi;
//  for (yyp = yyitems; yyp < yynextFree; yyp += 1)
//    {
//      YYFPRINTF (stderr, "%3lu. ",
//                 (unsigned long int) (yyp - yyitems));
//      if (*(bool *) yyp)
//        {
//          YYASSERT (yyp->yystate.yyisState);
//          YYASSERT (yyp->yyoption.yyisState);
//          YYFPRINTF (stderr, "Res: %d, LR State: %d, posn: %lu, pred: %ld",
//                     yyp->yystate.yyresolved, yyp->yystate.yylrState,
//                     (unsigned long int) yyp->yystate.yyposn,
//                     (long int) YYINDEX (yyp->yystate.yypred));
//          if (! yyp->yystate.yyresolved)
//            YYFPRINTF (stderr, ", firstVal: %ld",
//                       (long int) YYINDEX (yyp->yystate
//                                             .yysemantics.yyfirstVal));
//        }
//      else
//        {
//          YYASSERT (!yyp->yystate.yyisState);
//          YYASSERT (!yyp->yyoption.yyisState);
//          YYFPRINTF (stderr, "Option. rule: %d, state: %ld, next: %ld",
//                     yyp->yyoption.yyrule - 1,
//                     (long int) YYINDEX (yyp->yyoption.yystate),
//                     (long int) YYINDEX (yyp->yyoption.yynext));
//        }
//      YYFPRINTF (stderr, "\n");
//    }
//  YYFPRINTF (stderr, "Tops:");
//  for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
//    YYFPRINTF (stderr, "%lu: %ld; ", (unsigned long int) yyi,
//               (long int) YYINDEX (yystackp->yytops.yystates[yyi]));
//  YYFPRINTF (stderr, "\n");
//}

YYRESULTTAG
yyresolveValue (yy_glr_state* yys]b4_user_formals[)
{
  yy_semantic_option* yyoptionList = yys->get_semantic_option();
  yy_semantic_option* yybest = yyoptionList;
  bool yymerge = false;
  YYSTYPE yysval;]b4_locations_if([
  YYLTYPE *yylocp = &yys->yyloc;])[

  for (yy_semantic_option** yypp = &yyoptionList->yynext; *yypp != YY_NULLPTR; )
    {
      yy_semantic_option* yyp = *yypp;

      if (*yybest == *yyp)
        {
          yybest->yymerge_option_sets (*yyp);
          *yypp = yyp->yynext;
        }
      else
        {
          switch (yybest->yypreference (yyp))
            {
            case no_combination:]b4_locations_if([[
              yyresolveLocations (yys, 1]b4_user_args[);]])[
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

  YYRESULTTAG yyflag;
  if (yymerge)
    {
      yy_semantic_option* yyp;
      int yyprec = yydprec[yybest->yyrule];
      yyflag = yyresolveAction (yybest, &yysval]b4_locuser_args[);
      if (yyflag == yyok)
        for (yyp = yybest->yynext; yyp != YY_NULLPTR; yyp = yyp->yynext)
          {
            if (yyprec == yydprec[yyp->yyrule])
              {
                YYSTYPE yysval_other;]b4_locations_if([
                YYLTYPE yydummy;])[
                yyflag = yyresolveAction (yyp, &yysval_other]b4_locuser_args([&yydummy])[);
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
    yyflag = yyresolveAction (yybest, &yysval]b4_locuser_args([yylocp])[);

  if (yyflag == yyok)
    {
      delete yys->yysemantic;
      yys->yysemantic = new yysemantic_simple_value();
      ]b4_symbol_variant([[yystos[yys->yylrState]]],
                         [[yys->yysemantic.get_value()]],
                         [move], [yysval])], [[
      yys->yysemantic.get_value() = yysval;]])[
    }
  else
    yys->yysemantic = YY_NULLPTR;
  return yyflag;
}

/** Resolve the previous YYN states starting at and including state YYS
 *  on *YYSTACKP. If result != yyok, some states may have been left
 *  unresolved possibly with empty semantic option chains.  Regardless
 *  of whether result = yyok, each state has been left with consistent
 *  data so that yydestroyGLRState can be invoked if necessary.  */
YYRESULTTAG
yy_glr_stack::yyresolveStates (yy_glr_state* yys, int yyn ]b4_user_formals[)
{
  if (0 < yyn)
    {
      YYASSERT (yys->yypred);
      YYCHK (yyresolveStates (yys->yypred, yyn-1]b4_user_args[));
      if (! yys->yyresolved)
        YYCHK (yyresolveValue (yys]b4_user_args[));
    }
  return yyok;
}

/** Resolve the states for the RHS of YYOPT on *YYSTACKP, perform its
 *  user action, and return the semantic value and location in *YYVALP
 *  and *YYLOCP.  Regardless of whether result = yyok, all RHS states
 *  have been destroyed (assuming the user action destroys all RHS
 *  semantic values if invoked).  */
YYRESULTTAG
yy_glr_stack::yyresolveAction (yy_semantic_option* yyopt,,
                               YYSTYPE* yyvalp]b4_locuser_formals[)
{
  yy_glr_state yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
  int yynrhs = yyrhsLength (yyopt->yyrule);
  YYRESULTTAG yyflag =
    yyresolveStates (yyopt->yystate, yynrhs]b4_user_args[);
  if (yyflag != yyok)
    {
      yy_glr_state *yys;
      for (yys = yyopt->yystate; yynrhs > 0; yys = yys->yypred, yynrhs -= 1)
        yydestroyGLRState ("Cleanup: popping", yys]b4_user_args[);
      return yyflag;
    }

  yyrhsVals[YYMAXRHS + YYMAXLEFT].yypred = yyopt->yystate;]b4_locations_if([[
  if (yynrhs == 0)
    /* Set default location.  */
    yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yyloc = yyopt->yystate->yyloc;]])[
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
                           yyvalp]b4_locuser_args[);
    YY_SYMBOL_SWAP (yychar, yylval]b4_locations_if([, yylloc])[,
                    yychar_current, yylval_current]b4_locations_if([, yylloc_current])[);
    //  YY_SYMBOL_PRINT("yyresolveAction: AFTER",
    //              YYTRANSLATE(yychar), &yylval, &yylloc);
  }
  return yyflag;
}

/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@@$).  Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT.  */
YYRESULTTAG
yy_glr_stack::yyuserAction (yy_rule_num yyn, size_t yyrhslen, yy_glr_state* yyvsp,
                            YYSTYPE* yyvalp)
{
  bool yynormal YY_ATTRIBUTE_UNUSED = (yystackp->yysplitPoint == YY_NULLPTR);
  //  std::cerr << "yyuserAction" << std::endl;
  int yylow;
]b4_parse_param_use([yyvalp], [yylocp])dnl
[  YYUSE (yyrhslen);
# undef yyerrok
# define yyerrok (yyerrState = 0)
# undef YYACCEPT
# define YYACCEPT return yyaccept
# undef YYABORT
# define YYABORT return yyabort
# undef YYERROR
# define YYERROR return yyerrok, yyerr
# undef YYRECOVERING
# define YYRECOVERING() (yyerrState != 0)
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
    *yyvalp = yyvsp[YYFILL (1-yyrhslen)].yysemantics.yysval;]])b4_locations_if([[
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

]b4_locations_if([[


/** Resolve the locations for each of the YYN1 states in *YYSTACKP,
 *  ending at YYS1.  Has no effect on previously resolved states.
 *  The first semantic option of a state is always chosen.  */
void
yy_glr_stack::yyresolveLocations (yy_glr_state *yys1, int yyn1
                                  ]b4_user_formals[)
{
  if (0 < yyn1)
    {
      yyresolveLocations (yys1->yypred, yyn1 - 1]b4_user_args[);
      if (!yys1->yyresolved)
        {
          yy_glr_state yyrhsloc[1 + YYMAXRHS];
          int yynrhs;
          yy_semantic_option *yyoption = yys1->yysemantic.get_value();
          YYASSERT (yyoption);
          yynrhs = yyrhsLength (yyoption->yyrule);
          if (0 < yynrhs)
            {
              yy_glr_state *yys;
              int yyn;
              yyresolveLocations (yyoption->yystate, yynrhs]b4_user_args[);
              for (yys = yyoption->yystate, yyn = yynrhs;
                   yyn > 0;
                   yys = yys->yypred, yyn -= 1)
                yyrhsloc[yyn].yyloc = yys->yyloc;
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
              yyrhsloc[0].yyloc = yyprevious->yyloc;
            }
          YYLLOC_DEFAULT ((yys1->yyloc), yyrhsloc, yynrhs);
        }
    }
}]])[
]
