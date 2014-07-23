[
class yy_parsing_error
{
public:
  yy_parsing_error(error_status s)
  : status(s)
  {}

  enum error_status
  {
    abort,
    memory_exhausted,
    bug;
  };
  error_status get_status()
  {
    return status;
  }
private:
  error_status status;
};

  /// A Bison parser.
  class ]b4_parser_class_name[
  {
  public:
]b4_public_types_declare[
  //( declaration of the variant type, misc typedefs, the tokens, the
  //basic_symbol inner class, by_type struct, and the MAKE_symbol methods)

    /// Build a parser object.
    ]b4_parser_class_name[ (]b4_parse_param_decl[);
    virtual ~]b4_parser_class_name[ ();

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

  private:
    /// This class is not copyable.
    ]b4_parser_class_name[ (const ]b4_parser_class_name[&);
    ]b4_parser_class_name[& operator= (const ]b4_parser_class_name[&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yytoken   the lookahead token type, or yyempty_.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         symbol_number_type yytoken) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const ]b4_int_type(b4_pact_ninf, b4_pact_ninf)[ yypact_ninf_;
    static const ]b4_int_type(b4_table_ninf, b4_table_ninf)[ yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (]b4_token_ctor_if([token_type], [int])[ t);

    // Tables.
]b4_parser_tables_declare[]b4_error_verbose_if([

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);])[

]b4_token_table_if([], [[#if ]b4_api_PREFIX[DEBUG]])[
    /// For a symbol, its name in clear.
    static const char* const yytname_[];
]b4_token_table_if([[#if ]b4_api_PREFIX[DEBUG]])[
]b4_integral_parser_table_declare([rline], [b4_rline],
     [[YYRLINE[YYN] -- Source line where rule number YYN was defined.]])[
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:

    /// Stack type.
    typedef yy_glr_stack stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    // Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = ]b4_last[,     ///< Last index in yytable_.
      yynnts_ = ]b4_nterms_number[,  ///< Number of nonterminal symbols.
      yyempty_ = -2,
      yyfinal_ = ]b4_final_state_number[, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = ]b4_tokens_number[  ///< Number of tokens.
    };

    enum
    {
      yyeof_ = 0
    };

    /// Convert a scanner token number \a t to a symbol number.
    static inline token_number_type yytranslate_ (b4_token_ctor_if([token_type], [int]) t);

b4_parse_param_vars
  };

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

/** Grammar symbol */
typedef int yy_symbol;

/** Item references, as in LALR(1) machine */
typedef short int yy_item_num;

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yy_rule_num yyrule)

/** Left-hand-side symbol for rule #YYRULE.  */
static inline yy_symbol
yylhsNonterm (yy_rule_num yyrule)


static inline bool
yyisShiftAction (int yyaction)

static inline bool
yyisErrorAction (int yyaction)

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



#define YY_SYMBOL_COPY(Yychar1, Yyval1, Yyloc1, Yychar2, Yyval2, Yyloc2)


  // Generate an error message.
  std::string
  ]b4_parser_class_name[::yysyntax_error_ (]dnl
b4_error_verbose_if([state_type yystate, symbol_number_type yytoken],
                    [state_type, symbol_number_type])[) const
  {]b4_error_verbose_if([[
  yy_symbol yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);
  size_t yysize0 = yytnamerr (YY_NULLPTR, yytokenName (yytoken));
  size_t yysize = yysize0;
  bool yysize_overflow = false;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected").  */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int n = yypact[yytops.yystates[0]->yylrState];
      yyarg[yycount++] = yytokenName (yytoken);
      if (!yypact_value_is_default_ (n))
        {
          /* Start X at -N if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -N actions for this
             state because they are default actions.  */
          /* Stay within bounds of both yycheck and yytname.  */
          int checklim = YYLAST - n + 1;
          int xend = checklim < YYNTOKENS ? checklim : YYNTOKENS;
          for (int x = YYLAST - n + 1; x < xend; ++x)
            if (yycheck[x + n] == x && x != YYTERROR
                && !yytable_value_is_error (yytable[x + n]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytokenName (x);
                {
                  size_t sz = yysize + yytnamerr (YY_NULLPTR, yytokenName (x));
                  yysize_overflow |= sz < yysize;
                  yysize = sz;
                }
              }
        }
    }


    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;]], [[
    return YY_("syntax error");]])[
  }

  ]b4_parser_class_name[::state_type
  ]b4_parser_class_name[::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  ]b4_parser_class_name[::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  ]b4_parser_class_name[::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  ]b4_parser_class_name[::parse ()
  {
    YYDPRINTF ((stderr, "Starting parse\n"));

    yychar = YYEMPTY;
  ]b4_variant_if([
    /* Variants are always initialized to an empty instance of the
       correct type.  */
    b4_symbol_variant([[0]], [yylval], [build])], [[
    yylval = yyval_default;]])b4_locations_if([
    yylloc = yyloc_default;])[
  ]m4_ifdef([b4_initial_action], [
  b4_dollar_pushdef([yylval], [], [yylloc])dnl
    /* User initialization code.  */
    b4_user_initial_action
  b4_dollar_popdef])[]dnl
  [

    int yyresult;
    size_t yyposn = 0;

    try
    {
      yyglrShift (&yystack, 0, 0, 0, &yylval]b4_locations_if([, &yylloc])[);

      while (true)
        {
          /* For efficiency, we have two loops, the first of which is
             specialized to deterministic operation (single stack, no
             potential ambiguity).  */
          /* Standard mode */
          while (true)
            {
              yy_rule_num yyrule;
              int yyaction;
              const short int* yyconflicts;

              yy_state_num yystate = yystack.yytops.yystates[0]->yylrState;
              YYDPRINTF ((stderr, "Entering state %d\n", yystate));
              if (yystate == YYFINAL)
                goto yyacceptlab;
              if (yyisDefaultedState (yystate))
                {
                  yyrule = yydefaultAction (yystate);
                  if (yyrule == 0)
                    {
    ]b4_locations_if([[               yystack.yyerror_range[1].yystate.yyloc = yylloc;]])[
                      yyreportSyntaxError (&yystack]b4_user_args[);
                      goto yyuser_error;
                    }
                  YYCHK1 (yyglrReduce (&yystack, 0, yyrule, yytrue]b4_user_args[));
                }
              else
                {
                  yy_symbol yytoken;
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
                      yytoken = YYTRANSLATE (yychar);
                      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
                    }

                  yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);
                  if (*yyconflicts != 0)
                    break;
                  if (yyisShiftAction (yyaction))
                    {
                      YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
                      yychar = YYEMPTY;
                      yyposn += 1;
                      yyglrShift (&yystack, 0, yyaction, yyposn, &yylval]b4_locations_if([, &yylloc])[);
                      if (0 < yystack.yyerrState)
                        yystack.yyerrState -= 1;
                    }
                  else if (yyisErrorAction (yyaction))
                    {
    ]b4_locations_if([[               yystack.yyerror_range[1].yystate.yyloc = yylloc;]])[
                      yyreportSyntaxError (&yystack]b4_user_args[);
                      goto yyuser_error;
                    }
                  else
                    YYCHK1 (yyglrReduce (&yystack, 0, -yyaction, yytrue]b4_user_args[));
                }
            }

          while (true)
            {
              yy_symbol yytoken_to_shift;
              size_t yys;

              for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
                yystackp->yytops.yylookaheadNeeds[yys] = yychar != YYEMPTY;

              /* yyprocessOneStack returns one of three things:

                  - An error flag.  If the caller is yyprocessOneStack, it
                    immediately returns as well.  When the caller is finally
                    yyparse, it jumps to an error label via YYCHK1.

                  - yyok, but yyprocessOneStack has invoked yymarkStackDeleted
                    (&yystack, yys), which sets the top state of yys to NULL.  Thus,
                    yyparse's following invocation of yyremoveDeletes will remove
                    the stack.

                  - yyok, when ready to shift a token.

                 Except in the first case, yyparse will invoke yyremoveDeletes and
                 then shift the next token onto all remaining stacks.  This
                 synchronization of the shift (that is, after all preceding
                 reductions on all stacks) helps prevent double destructor calls
                 on yylval in the event of memory exhaustion.  */

              for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
                YYCHK1 (yyprocessOneStack (&yystack, yys, yyposn]b4_lpure_args[));
              yyremoveDeletes (&yystack);
              if (yystack.yytops.yysize == 0)
                {
                  yyundeleteLastStack (&yystack);
                  if (yystack.yytops.yysize == 0)
                    yyFail (&yystack][]b4_lpure_args[, YY_("syntax error"));
                  YYCHK1 (yyresolveStack (&yystack]b4_user_args[));
                  YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
    ]b4_locations_if([[           yystack.yyerror_range[1].yystate.yyloc = yylloc;]])[
                  yyreportSyntaxError (&yystack]b4_user_args[);
                  goto yyuser_error;
                }

              /* If any yyglrShift call fails, it will fail after shifting.  Thus,
                 a copy of yylval will already be on stack 0 in the event of a
                 failure in the following loop.  Thus, yychar is set to YYEMPTY
                 before the loop to make sure the user destructor for yylval isn't
                 called twice.  */
              yytoken_to_shift = YYTRANSLATE (yychar);
              yychar = YYEMPTY;
              yyposn += 1;
              for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
                {
                  int yyaction;
                  const short int* yyconflicts;
                  yy_state_num yystate = yystack.yytops.yystates[yys]->yylrState;
                  yygetLRActions (yystate, yytoken_to_shift, &yyaction,
                                  &yyconflicts);
                  /* Note that yyconflicts were handled by yyprocessOneStack.  */
                  YYDPRINTF ((stderr, "On stack %lu, ", (unsigned long int) yys));
                  YY_SYMBOL_PRINT ("shifting", yytoken_to_shift, &yylval, &yylloc);
                  yyglrShift (&yystack, yys, yyaction, yyposn, &yylval]b4_locations_if([, &yylloc])[);
                  YYDPRINTF ((stderr, "Stack %lu now in state #%d\n",
                              (unsigned long int) yys,
                              yystack.yytops.yystates[yys]->yylrState));
                }

              if (yystack.yytops.yysize == 1)
                {
                  YYCHK1 (yyresolveStack (&yystack]b4_user_args[));
                  YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
                  break;
                }
            }
          continue;
        yyuser_error:
          yy_recover_syntax_error (&yystack]b4_user_args[);
          yyposn = yystack.yytops.yystates[0]->yyposn;
        }

    } catch (const yy_parsing_error& err)
    {
      switch (err.get_status())
      {
        case abort: goto yyabortlab;
        case memory_exhausted: goto yyexhaustedlab;
        default: goto yybuglab;
      }
    }

   yyacceptlab:
    yyresult = 0;
    goto yyreturn;

   yybuglab:
    YYASSERT (yyfalse);
    goto yyabortlab;

   yyabortlab:
    yyresult = 1;
    goto yyreturn;

   yyexhaustedlab:
    error (YY_("memory exhausted"));
    yyresult = 2;
    goto yyreturn;

   yyreturn:
    if (yychar != YYEMPTY)
      yydestruct ("Cleanup: discarding lookahead",
                  YYTRANSLATE (yychar), &yylval]b4_locuser_args([&yylloc])[);

    /* If the stack is well-formed, pop the stack until it is empty,
       destroying its entries as we go.  But free the stack regardless
       of whether it is well-formed.  */
    yystate_pool.clear();

    return yyresult;
  }
]
