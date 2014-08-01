[
//template <typename YYParser>
//class yy_glr_state;
template <class Parser>
class yy_glr_stack;

static const int YYEOF = 0;
static const int YYEMPTY = -2;

/** Grammar symbol */
typedef int yy_symbol;
/** Rule numbers, as in LALR(1) machine */
typedef int yy_rule_num;

/** Item references, as in LALR(1) machine */
typedef short int yy_item_num;

/** State numbers, as in LALR(1) machine */
typedef int yy_state_num;

# ifndef YYFPRINTF
#  define YYFPRINTF fprintf
# endif

#if ]b4_api_PREFIX[DEBUG


# define YYDPRINTF(Args)                        \
  do {                                          \
    if (yydebug())                              \
      YYFPRINTF Args;                           \
  } while (false)


# define YY_SYMBOL_PRINT(Title, Symbol)                                 \
  do {                                                                  \
    if (yydebug())                                                      \
      {                                                                 \
        *yycdebug_ << Title << ' ';                                     \
        yy_symbol_print_ (*yycdebug_, Symbol);                          \
        *yycdebug_ << std::endl;                                        \
      }                                                                 \
  } while (false)

#undef YY_SYMBOL_PRINT
#define YY_SYMBOL_PRINT(...)

//static void yypstack (struct yy_glr_stack* yystackp, size_t yyk)
//  YY_ATTRIBUTE_UNUSED;
//static void yypdumpstack (struct yy_glr_stack* yystackp)
//  YY_ATTRIBUTE_UNUSED;

#else /* !]b4_api_PREFIX[DEBUG */

# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)

#endif /* !]b4_api_PREFIX[DEBUG */

]
