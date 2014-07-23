
  /// A Bison parser.
  class b4_parser_class_name
  {
  public:
b4_public_types_declare
  //( declaration of the variant type, misc typedefs, the tokens, the
  //basic_symbol inner class, by_type struct, and the MAKE_symbol methods)

    /// Build a parser object.
    b4_parser_class_name (b4_parse_param_decl);
    virtual ~b4_parser_class_name ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

    /// The current debugging stream.
    std::ostream& debug_stream () const;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);

  public:
    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

# if DEBUG
  public:
    /// \brief Report a symbol value on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void yy_symbol_value_print_ (int yytype,
                                         const semantic_type* yyvaluep,
                                         const location_type* yylocationp);
    /// \brief Report a symbol on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void yy_symbol_print_ (int yytype,
                                   const semantic_type* yyvaluep,
                                   const location_type* yylocationp);
  private:
    // Debugging.
    std::ostream* yycdebug_;
#endif

    enum
    {
      yyeof_ = 0
    };

    /// Convert a scanner token number \a t to a symbol number.
    static inline token_number_type yytranslate_ (b4_token_ctor_if([token_type], [int]) t);

b4_parse_param_vars
  };

# b4_yy_symbol_print_define
# -------------------------
# Bypass the default implementation to generate the "yy_symbol_print"
# and "yy_symbol_value_print" functions.
/*--------------------.
| Print this symbol.  |
`--------------------*/
static void
yy_symbol_print(
    FILE *,
    int yytype,
    const b4_namespace_ref::b4_parser_class_name::semantic_type *yyvaluep,
    const b4_namespace_ref::b4_parser_class_name::location_type *yylocationp);

static void yyerror (const yy::calcxx_parser::location_type *yylocationp, yy::calcxx_parser& yyparser, calcxx_driver& driver, const char* msg);

namespace yy {
  // A wrapper around a symbol_type returning yylex, to an old style yylex.
  static int yylex_wrapper (YYSTYPE *yylvalp, YYLTYPE *yyllocp, calcxx_driver& driver);

} // yy

/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////
//////////////// C //////////////////////
/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////
/////////////////////////////////////////

/** State numbers, as in LALR(1) machine */
typedef int yy_state_num;

/** Rule numbers, as in LALR(1) machine */
typedef int yy_rule_num;

/** Grammar symbol */
typedef int yy_symbol;

/** Item references, as in LALR(1) machine */
typedef short int yy_item_num;

struct yy_glr_state {

  yy_glr_state(){}

  yy_glr_state(const yy_glr_state& that)
  yy_glr_state& operator=(const yy_glr_state& that);

  /** Type tag: always true.  */
  bool yyisState;
  /** Type tag for yysemantics.  If true, yysval applies, otherwise
   *  yyfirstVal applies.  */
  bool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
  yy_state_num yylrState;
  /** Preceding state in this stack */
  yy_glr_state* yypred;
  /** Source position of the last token produced by my symbol */
  size_t yyposn;
  struct {
    /** First in a chain of alternative reductions producing the
     *  non-terminal corresponding to this state, threaded through
     *  yynext.  */
    yy_semantic_option* yyfirstVal;
    /** Semantic value for this state.  */
    YYSTYPE yysval;
  } yysemantics;
  /** Source location for this state.  */
  YYLTYPE yyloc;
};

struct yy_glr_stateSet {
  yy_glr_state** yystates;
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != YYEMPTY.  */
  bool* yylookaheadNeeds;
  size_t yysize, yycapacity;
};

struct yy_semantic_option {
  /** Type tag: always false.  */
  bool yyisState;
  /** Rule number for this reduction */
  yy_rule_num yyrule;
  /** The last RHS state in the list of states to be reduced.  */
  yy_glr_state* yystate;
  /** The lookahead for this reduction.  */
  int yyrawchar;
  YYSTYPE yyval;
  YYLTYPE yyloc;
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
  yy_semantic_option* yynext;

  yy_semantic_option& operator= (yy_semantic_option const& other)
  {
    yyisState = other.yyisState;
    yyrule = other.yyrule;
    yystate = other.yystate;
    yyrawchar = other.yyrawchar;
    b4_symbol_variant([yystate->yylrState],
                       [yyval], [copy], [other.yyval])
    yyloc = other.yyloc;
    return *this;
  }
};

/** Type of the items in the GLR stack.  The yyisState field
 *  indicates which item of the union is valid.  */
struct yy_glr_stack_item {
  yy_glr_state yystate;
  yy_semantic_option yyoption;
};

struct yy_glr_stack {
  int yyerrState;
  yy_glr_stack_item yyerror_range[3];
  int yyerrcnt;
  int yyrawchar;
  YYSTYPE yyval;
  YYLTYPE yyloc;
  YYJMP_BUF yyexception_buffer;
  yy_glr_stack_item* yyitems;
  yy_glr_stack_item* yynextFree;
  size_t yyspaceLeft;
  yy_glr_state* yysplitPoint;
  yy_glr_state* yylastDeleted;
  yy_glr_stateSet yytops;
};

static void yyexpandGLRStack (yy_glr_stack* yystackp);

static _Noreturn void
yyFail (yy_glr_stack* yystackp, const char* yymsg)

static _Noreturn void
yyMemoryExhausted (yy_glr_stack* yystackp)

/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yystate.yypred.  Leaves YYVSP[YYLOW1].yystate.yypred
 *  containing the pointer to the next state in the chain.  */
static void
yyfillin (yy_glr_stack_item *yyvsp, int yylow0, int yylow1)

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
 * YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
 * For convenience, always return YYLOW1.  */
static inline int
yyfill (yy_glr_stack_item *yyvsp, int *yylow, int yylow1, bool yynormal)

/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@@$).  Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT.  */
static YYRESULTTAG
yyuserAction (yy_rule_num yyn, size_t yyrhslen, yy_glr_stack_item* yyvsp,
              yy_glr_stack* yystackp,
              YYSTYPE* yyvalp)


static void
yyuserMerge (int yyn, YYSTYPE* yy0, YYSTYPE* yy1)

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yy_rule_num yyrule)

static void
yydestroyGLRState (char const *yymsg, yy_glr_state *yys)

/** Left-hand-side symbol for rule #YYRULE.  */
static inline yy_symbol
yylhsNonterm (yy_rule_num yyrule)

/** True iff LR state YYSTATE has only a default reduction (regardless
 *  of token).  */
static inline bool
yyisDefaultedState (yy_state_num yystate)

/** The default reduction for YYSTATE, assuming it has one.  */
static inline yy_rule_num
yydefaultAction (yy_state_num yystate)


/** Set *YYACTION to the action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *YYCONFLICTS to a pointer into yyconfl to a 0-terminated list
 *  of conflicting reductions.
 */
static inline void
yygetLRActions (yy_state_num yystate, int yytoken,
                int* yyaction, const short int** yyconflicts)

/** Compute post-reduction state.
 * \param yystate   the current state
 * \param yysym     the nonterminal to push on the stack
 */
static inline yy_state_num
yyLRgotoState (yy_state_num yystate, yy_symbol yysym)

static inline bool
yyisShiftAction (int yyaction)

static inline bool
yyisErrorAction (int yyaction)


                                /* GLRStates */

/** Return a fresh GLRStackItem in YYSTACKP.  The item is an LR state
 *  if YYISSTATE, and otherwise a semantic option.  Callers should call
 *  YY_RESERVE_GLRSTACK afterwards to make sure there is sufficient
 *  headroom.  */

static inline yy_glr_stack_item*
yynewGLRStackItem (yy_glr_stack* yystackp, bool yyisState)

/** Add a new semantic action that will execute the action for rule
 *  YYRULE on the semantic values in YYRHS to the list of
 *  alternative actions for YYSTATE.  Assumes that YYRHS comes from
 *  stack #YYK of *YYSTACKP. */
static void
yyaddDeferredAction (yy_glr_stack* yystackp, size_t yyk, yy_glr_state* yystate,
                     yy_glr_state* yyrhs, yy_rule_num yyrule)

                                /* GLRStacks */

/** Initialize YYSET to a singleton set containing an empty stack.  */
static bool
yyinitStateSet (yy_glr_stateSet* yyset)

static void yyfreeStateSet (yy_glr_stateSet* yyset)

/** Initialize *YYSTACKP to a single empty stack, with total maximum
 *  capacity for all stacks of YYSIZE.  */
static bool
yyinitGLRStack (yy_glr_stack* yystackp, size_t yysize)

/** If *YYSTACKP is expandable, extend it.  WARNING: Pointers into the
    stack from outside should be considered invalid after this call.
    We always expand when there are 1 or fewer items left AFTER an
    allocation, so that we can avoid having external pointers exist
    across an allocation.  */
static void
yyexpandGLRStack (yy_glr_stack* yystackp)

static void
yyfreeGLRStack (yy_glr_stack* yystackp)

/** Assuming that YYS is a GLRState somewhere on *YYSTACKP, update the
 *  splitpoint of *YYSTACKP, if needed, so that it is at least as deep as
 *  YYS.  */
static inline void
yyupdateSplit (yy_glr_stack* yystackp, yy_glr_state* yys)

/** Invalidate stack #YYK in *YYSTACKP.  */
static inline void
yymarkStackDeleted (yy_glr_stack* yystackp, size_t yyk)

/** Undelete the last stack in *YYSTACKP that was marked as deleted.  Can
    only be done once after a deletion, and only when all other stacks have
    been deleted.  */
static void
yyundeleteLastStack (yy_glr_stack* yystackp)

static inline void
yyremoveDeletes (yy_glr_stack* yystackp)

static inline void
yysymbolCopy (int& yychar1, YYSTYPE& yyval1, YYLTYPE& yyloc1,
              const int& yychar2, const YYSTYPE& yyval2, const YYLTYPE& yyloc2)

static inline void
yysymbolSwap (int& yychar1, YYSTYPE& yyval1, YYLTYPE& yyloc1,
              int& yychar2, YYSTYPE& yyval2, YYLTYPE& yyloc2)

#define YY_SYMBOL_COPY(Yychar1, Yyval1, Yyloc1, Yychar2, Yyval2, Yyloc2)

/** Shift to a new state on stack #YYK of *YYSTACKP, corresponding to LR
 * state YYLRSTATE, at input position YYPOSN, with (resolved) semantic
 * value *YYVALP and source location *YYLOCP.  */
static inline void
yyglrShift (yy_glr_stack* yystackp, size_t yyk, yy_state_num yylrState,
            size_t yyposn,
            YYSTYPE* yyvalp, YYLTYPE* yylocp)

/** Shift stack #YYK of *YYSTACKP, to a new state corresponding to LR
 *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
 *  semantic value of YYRHS under the action for YYRULE.  */
static inline void
yyglrShiftDefer (yy_glr_stack* yystackp, size_t yyk, yy_state_num yylrState,
                 size_t yyposn, yy_glr_state* yyrhs, yy_rule_num yyrule)

static inline void
yy_reduce_print (int yynormal, yy_glr_stack_item* yyvsp, size_t yyk,
                 yy_rule_num yyrule)


/** Pop the symbols consumed by reduction #YYRULE from the top of stack
 *  #YYK of *YYSTACKP, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved.  Set *YYVALP to the resulting value,
 *  and *YYLOCP to the computed location (if any).  Return value is as
 *  for userAction.  */
static inline YYRESULTTAG
yydoAction (yy_glr_stack* yystackp, size_t yyk, yy_rule_num yyrule,
            YYSTYPE* yyvalp)

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
static inline YYRESULTTAG
yyglrReduce (yy_glr_stack* yystackp, size_t yyk, yy_rule_num yyrule,
             bool yyforceEval]b4_user_formals[)

static size_t
yysplitStack (yy_glr_stack* yystackp, size_t yyk)

/** True iff YYY0 and YYY1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols.  */
static bool
yyidenticalOptions (yy_semantic_option* yyy0, yy_semantic_option* yyy1)

/** Assuming identicalOptions (YYY0,YYY1), destructively merge the
 *  alternative semantic values for the RHS-symbols of YYY1 and YYY0.  */
static void
yymergeOptionSets (yy_semantic_option* yyy0, yy_semantic_option* yyy1)

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state; return 0 if no combination is possible,
 *  1 if user-mergeable, 2 if Y0 is preferred, 3 if Y1 is preferred.  */
static int
yypreference (yy_semantic_option* y0, yy_semantic_option* y1)

static YYRESULTTAG yyresolveValue (yy_glr_state* yys,
                                   yy_glr_stack* yystackp]b4_user_formals[);

/** Resolve the previous YYN states starting at and including state YYS
 *  on *YYSTACKP. If result != yyok, some states may have been left
 *  unresolved possibly with empty semantic option chains.  Regardless
 *  of whether result = yyok, each state has been left with consistent
 *  data so that yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveStates (yy_glr_state* yys, int yyn,
                 yy_glr_stack* yystackp]b4_user_formals[)

/** Resolve the states for the RHS of YYOPT on *YYSTACKP, perform its
 *  user action, and return the semantic value and location in *YYVALP
 *  and *YYLOCP.  Regardless of whether result = yyok, all RHS states
 *  have been destroyed (assuming the user action destroys all RHS
 *  semantic values if invoked).  */
static YYRESULTTAG
yyresolveAction (yy_semantic_option* yyopt, yy_glr_stack* yystackp,
                 YYSTYPE* yyvalp]b4_locuser_formals[)

static void
yyreportTree (yy_semantic_option* yyx, int yyindent)

static YYRESULTTAG
yyreportAmbiguity (yy_semantic_option* yyx0,
                   yy_semantic_option* yyx1]b4_pure_formals[)

/** Resolve the locations for each of the YYN1 states in *YYSTACKP,
 *  ending at YYS1.  Has no effect on previously resolved states.
 *  The first semantic option of a state is always chosen.  */
static void
yyresolveLocations (yy_glr_state *yys1, int yyn1,
                    yy_glr_stack *yystackp]b4_user_formals[)

/** Resolve the ambiguity represented in state YYS in *YYSTACKP,
 *  perform the indicated actions, and set the semantic value of YYS.
 *  If result != yyok, the chain of semantic options in YYS has been
 *  cleared instead or it has been left unmodified except that
 *  redundant options may have been removed.  Regardless of whether
 *  result = yyok, YYS has been left with consistent data so that
 *  yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveValue (yy_glr_state* yys, yy_glr_stack* yystackp]b4_user_formals[)

static YYRESULTTAG
yyresolveStack (yy_glr_stack* yystackp]b4_user_formals[)

static void
yycompressStack (yy_glr_stack* yystackp)

static YYRESULTTAG
yyprocessOneStack (yy_glr_stack* yystackp, size_t yyk,
                   size_t yyposn]b4_pure_formals[)

static void
yyreportSyntaxError (yy_glr_stack* yystackp]b4_user_formals[)

static void
yyrecoverSyntaxError (yy_glr_stack* yystackp]b4_user_formals[)


]b4_function_define([yyparse], [int], b4_parse_param)[


/* DEBUGGING ONLY */

static void
yy_yypstack (yy_glr_state* yys)

static void
yypstates (yy_glr_state* yyst)

static void
yypstack (yy_glr_stack* yystackp, size_t yyk)

static void
yypdumpstack (yy_glr_stack* yystackp)
