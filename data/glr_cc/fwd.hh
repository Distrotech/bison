[
template <typename YYParser>
class yy_glr_state;
template <class Parser>
class yy_glr_stack;

static const int YYEOF = 0;
static const int YYEMPTY = -2;

int yynerrs;
int yychar;

/** Grammar symbol */
typedef int yy_symbol;
/** Rule numbers, as in LALR(1) machine */
typedef int yy_rule_num;

/** Item references, as in LALR(1) machine */
typedef short int yy_item_num;

/** State numbers, as in LALR(1) machine */
typedef int yy_state_num;

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yy_rule_num yyrule);

/** Left-hand-side symbol for rule #YYRULE.  */
static inline yy_symbol
yylhsNonterm (yy_rule_num yyrule);


static inline bool
yyisShiftAction (int yyaction);

static inline bool
yyisErrorAction (int yyaction);

/** True iff LR state YYSTATE has only a default reduction (regardless
 *  of token).  */
static inline bool
yyisDefaultedState (yy_state_num yystate);

/** The default reduction for YYSTATE, assuming it has one.  */
static inline yy_rule_num
yydefaultAction (yy_state_num yystate);

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
                int* yyaction, const short int** yyconflicts);

# ifndef YYFPRINTF
#  define YYFPRINTF fprintf
# endif

#if ]b4_api_PREFIX[DEBUG


# define YYDPRINTF(Args)                        \
  do {                                          \
    if (yydebug)                                \
      YYFPRINTF Args;                           \
  } while (0)


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                  \
  do {                                                                  \
    if (yydebug)                                                        \
      {                                                                 \
        YYFPRINTF (stderr, "%s ", Title);                               \
        yy_symbol_print (stderr, Type, Value]b4_locuser_args([Location])[);        \
        YYFPRINTF (stderr, "\n");                                       \
      }                                                                 \
  } while (0)

//static void yypstack (struct yy_glr_stack* yystackp, size_t yyk)
//  YY_ATTRIBUTE_UNUSED;
//static void yypdumpstack (struct yy_glr_stack* yystackp)
//  YY_ATTRIBUTE_UNUSED;

#else /* !]b4_api_PREFIX[DEBUG */

# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)

#endif /* !]b4_api_PREFIX[DEBUG */

]
