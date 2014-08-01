b4_namespace_open[

void
]b4_parser_class_name[::yydestruct(const std::string& msg, int yytype,
                                   semantic_type *yyvaluep]b4_locuser_formals[)
{
  YYUSE(yytype);
  YYUSE(yyvaluep);]b4_locations_if([
  YYUSE(yylocp);])[
  std::string yymsg = msg.empty() ? "Deleting" : yymsg;
  YY_SYMBOL_PRINT (yymsg.c_str(), yytype, yyvaluep, yylocp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  ]b4_symbol_actions([destructor])[
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

#if ]b4_api_PREFIX[DEBUG
void
]b4_parser_class_name[::yy_reduce_print_ (stack_symbol_type* state,
                                          yy_rule_num yyrule, size_t yyk,
                                          bool yynormal)
{
  int yynrhs = yyrhs_length (yyrule);
  YYFPRINTF (stderr, "Reducing stack %lu by rule %d (line %lu):\n",
             (unsigned long int) yyk, yyrule - 1,
             (unsigned long int) yyrline[yyrule]);
  yy_args_stack<]b4_parser_class_name[> yyargs(state, yynrhs);
  /* The symbols being reduced.  */
  for (int i = 0; i < yynrhs; ++i)
    {
      YYFPRINTF (stderr, "   $%d = ", i + 1);
      yy_symbol_print_ (yystos_[yyargs[i + 1]->state],
                       *yyargs[i + 1]);
      if (!yyargs[i + 1]->yysemantic->resolved())
        YYFPRINTF (stderr, " (unresolved)");
      YYFPRINTF (stderr, "\n");
    }
}
#endif

const char*
]b4_parser_class_name[::yy_token_name(yy_symbol yytoken) const
{
  if (yytoken == YYEMPTY)
    return "";

  return yytname[yytoken];
}

void
]b4_parser_class_name[::yygetLRActions (yy_state_num yystate, int yytoken,
                int* yyaction, const short int** yyconflicts)
{
  int yyindex = yypact_[yystate] + yytoken;
  if (yy_pact_value_is_default_ (yypact_[yystate])
      || yyindex < 0 || YYLAST < yyindex || yycheck_[yyindex] != yytoken)
    {
      *yyaction = -yydefact_[yystate];
      *yyconflicts = yyconfl;
    }
  else if (! yy_table_value_is_error_ (yytable_[yyindex]))
    {
      *yyaction = yytable_[yyindex];
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
  else
    {
      *yyaction = 0;
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
}

void
]b4_parser_class_name[::yy_recover_syntax_error ()
{
  if (yystack_.yyerrState == 3)
    /* We just shifted the error token and (perhaps) took some
       reductions.  Skip tokens until we can proceed.  */
    while (true)
      {
        if (yyla.type_get() == yyeof_)
          yyFail ("", YY_NULLPTR);
        if (!yyempty)
          {]b4_locations_if([[
            /* We throw away the lookahead, but the error range
               of the shifted error token must take it into account.  */
            stack_symbol_type *yys = yystack_.yytops.top();
            stack_symbol_type yyerror_range[3];
            yyerror_range[1].location = yys->location;
            yyerror_range[2].location = yylloc;
            YYLLOC_DEFAULT ((yys->location), yyerror_range, 2);]])[
            yy_destroy_ ("Error: discarding", yyla);
          }
        YYDPRINTF ((stderr, "Reading a token: "));
        {
          symbol_type lookahead (]b4_lex[);
          yyla.move(lookahead);
        }
        yyempty = false;
        if (yyla.type_get() == yyeof_)
          {
            YYDPRINTF ((stderr, "Now at end of input.\n"));
          }
        else
          {
            YY_SYMBOL_PRINT ("Next token is", yyla);
          }
        int j = yypact_[yystack_.yytops.top()->state];
        if (yy_pact_value_is_default_ (j))
          return;
        j += yyla.type_get();
        if (j < 0 || YYLAST < j || yycheck_[j] != yyla.type_get())
          {
            if (yydefact_[yystack_.yytops.top()->state] != 0)
              return;
          }
        else if (! yy_table_value_is_error_ (yytable_[j]))
          return;
      }

  /* Reduce to one stack.  */
  {
    size_t yyk = 0;
    for (; yyk < yystack_.yytops.size(); yyk += 1)
      if (yystack_.yytops[yyk] != YY_NULLPTR)
        break;
    if (yyk >= yystack_.yytops.size())
      yyFail ("", YY_NULLPTR);
    for (yyk += 1; yyk < yystack_.yytops.size(); yyk += 1)
      yystack_.yymarkStackDeleted (yyk);
  }
  yystack_.yyremoveDeletes ();

  /* Now pop stack until we find a state that shifts the error token.  */
  yystack_.yyerrState = 3;
  while (yystack_.yytops.top() != YY_NULLPTR)
    {
      stack_symbol_type *yys = yystack_.yytops.top();
      int j = yypact_[yys->state];
      if (! yy_pact_value_is_default_ (j))
        {
          j += YYTERROR;
          if (0 <= j && j <= YYLAST && yycheck_[j] == YYTERROR
              && yyisShiftAction (yytable_[j]))
            {
              /* Shift the error token.  */]b4_locations_if([[
              /* First adjust its location.*/
              YYLTYPE yyerrloc;
              yystack_.yyerror_range[2].location = yylloc;
              YYLLOC_DEFAULT (yyerrloc, (yystack_.yyerror_range), 2);]])[
              YY_SYMBOL_PRINT ("Shifting", yystos[yytable_[j]],
                               &yylval, &yyerrloc);
              yystack_.yyglrShift (0, yytable_[j],
                          yys->yyposn, &yylval]b4_locations_if([, &yyerrloc])[);
              yys = yystack_.yytops.top();
              break;
            }
        }]b4_locations_if([[
      yystack_.yyerror_range[1].location = yys->location;]])[
      if (yys->yypred != YY_NULLPTR)
        yy_destroy_ ("Error: popping", *yys);
      yystack_.yytops.pop();
    }
  if (yystack_.yytops.top() == YY_NULLPTR)
    yyFail ("", YY_NULLPTR);
}

_Noreturn void
]b4_parser_class_name[::yyFail (const std::string& yymsg, const location* yylocp)
{
  if (yymsg != "")
    yyerror (yylocp, *this, yymsg.c_str());
  throw yy_parsing_error(yy_parsing_error::abort_parsing);
}

_Noreturn void
]b4_parser_class_name[::yyMemoryExhausted ()
{
  throw yy_parsing_error(yy_parsing_error::memory_exhausted);
}

YYRESULTTAG
]b4_parser_class_name[::yyreportAmbiguity (yy_semantic_option<]b4_parser_class_name[>* yyx0,
                                           yy_semantic_option<]b4_parser_class_name[>* yyx1]b4_pure_formals[)
{
  YYUSE (yyx0);
  YYUSE (yyx1);

#if ]b4_api_PREFIX[DEBUG
  YYFPRINTF (stderr, "Ambiguity detected.\n");
  YYFPRINTF (stderr, "Option 1,\n");
  yyx0->yyreportTree (2);
  YYFPRINTF (stderr, "\nOption 2,\n");
  yyx1->yyreportTree (2);
  YYFPRINTF (stderr, "\n");
#endif

  yyerror (&yyla.location, *this, YY_("syntax is ambiguous"));
  return yyabort;
}

  // Generate an error message.
  std::string
  ]b4_parser_class_name[::yysyntax_error_ (]dnl
b4_error_verbose_if([state_type yystate],
                    [state_type])[) const
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
      int n = yypact_[yystack_.yytops.top()->state];
      yyarg[yycount++] = yytokenName (yytoken);
      if (!yy_pact_value_is_default_ (n))
        {
          /* Start X at -N if negative to avoid negative indexes in
             YYCHECK_.  In other words, skip the first -N actions for this
             state because they are default actions.  */
          /* Stay within bounds of both yycheck_ and yytname.  */
          int checklim = YYLAST - n + 1;
          int xend = checklim < YYNTOKENS ? checklim : YYNTOKENS;
          for (int x = YYLAST - n + 1; x < xend; ++x)
            if (yycheck_[x + n] == x && x != YYTERROR
                && !yy_table_value_is_error_ (yytable_[x + n]))
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

#define YYCHK1(YYE)                                                          \
  do {                                                                       \
    switch (YYE) {                                                           \
    case yyok:                                                               \
      break;                                                                 \
    case yyabort:                                                            \
      goto yyabortlab;                                                       \
    case yyaccept:                                                           \
      goto yyacceptlab;                                                      \
    case yyerr:                                                              \
      goto yyuser_error;                                                     \
    default:                                                                 \
      goto yybuglab;                                                         \
    }                                                                        \
  } while (0);


  int
  ]b4_parser_class_name[::parse ()
  {
    YYDPRINTF ((stderr, "Starting parse\n"));

    //yychar = YYEMPTY;
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
    yyempty = true;

    try
    {
      yystack_.yyglrShift (0, 0, 0, &yylval]b4_locations_if([, &yylloc])[);

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

              yy_state_num yystate = yystack_.yytops.top()->state;
              YYDPRINTF ((stderr, "Entering state %d\n", yystate));
              if (yystate == YYFINAL)
                goto yyacceptlab;
              if (yyisDefaultedState (yystate))
                {
                  yyrule = yydefaultAction (yystate);
                  if (yyrule == 0)
                    {
    ]b4_locations_if([[               yystack_.yyerror_range[1].location = yylloc;]])[
                      yysyntax_error_ (yystate);
                      goto yyuser_error;
                    }
                  YYCHK1 (yystack_.yyglrReduce (0, yyrule, true));
                }
              else
                {
                  yy_symbol yytoken;
                  if (yyempty)
                    {
                      YYDPRINTF ((stderr, "Reading a token: "));]b4_token_ctor_if([[
                      symbol_type yylookahead (]b4_lex[);
                      yyla.move (yylookahead);]], [[
                      yyla.type = yytranslate_ (]b4_lex[);]])[
                      yyempty = false;
                    }

                  if (yyla.type_get() == YYEOF)
                    YYDPRINTF ((stderr, "Now at end of input.\n"));
                  else
                    YY_SYMBOL_PRINT ("Next token is", yyla);

                  yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);
                  if (*yyconflicts != 0)
                    break;
                  if (yyisShiftAction (yyaction))
                    {
                      YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
                      yyempty = true;
                      yyposn += 1;
                      yystack_.yyglrShift (0, yyaction, yyposn, &yylval]b4_locations_if([, &yylloc])[);
                      if (0 < yystack_.yyerrState)
                        yystack_.yyerrState -= 1;
                    }
                  else if (yyisErrorAction (yyaction))
                    {
    ]b4_locations_if([[               yystack_.yyerror_range[1].location = yylloc;]])[
                      yysyntax_error_ (yystate);
                      goto yyuser_error;
                    }
                  else
                    YYCHK1 (yystack_.yyglrReduce (0, -yyaction, true));
                }
            }

          while (true)
            {
              yy_symbol yytoken_to_shift;

              for (size_t s = 0; s < yystack_.yytops.size(); s += 1)
                yystack_.yytops.yylookaheadNeeds[s] = !yyempty;

              /* yyprocessOneStack returns one of three things:

                  - An error flag.  If the caller is yyprocessOneStack, it
                    immediately returns as well.  When the caller is finally
                    yyparse, it jumps to an error label via YYCHK1.

                  - yyok, but yyprocessOneStack has invoked yymarkStackDeleted
                    (&yystack_, s), which sets the top state of s to NULL.  Thus,
                    yyparse's following invocation of yyremoveDeletes will remove
                    the stack.

                  - yyok, when ready to shift a token.

                 Except in the first case, yyparse will invoke yyremoveDeletes and
                 then shift the next token onto all remaining stacks.  This
                 synchronization of the shift (that is, after all preceding
                 reductions on all stacks) helps prevent double destructor calls
                 on yylval in the event of memory exhaustion.  */

              for (size_t s = 0; s < yystack_.yytops.size(); s += 1)
                YYCHK1 (yystack_.yyprocessOneStack (s, yyposn]b4_lpure_args[));
              yystack_.yyremoveDeletes ();
              if (yystack_.yytops.size() == 0)
                {
                  yystack_.yyundeleteLastStack ();
                  if (yystack_.yytops.size() == 0)
                    yyFail (YY_("syntax error"), &yyla.location);
                  YYCHK1 (yystack_.yyresolveStack ());
                  YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
    ]b4_locations_if([[           yystack_.yyerror_range[1].location = yylloc;]])[
                  yysyntax_error_ (yystack_.yytops.top()->state);
                  goto yyuser_error;
                }

              /* If any yyglrShift call fails, it will fail after shifting.  Thus,
                 a copy of yylval will already be on stack 0 in the event of a
                 failure in the following loop.  Thus, yychar is set to YYEMPTY
                 before the loop to make sure the user destructor for yylval isn't
                 called twice.  */

              yytoken_to_shift = yyla.type_get();
              yyempty = true;
              yyposn += 1;
              for (size_t s = 0; s < yystack_.yytops.size(); s += 1)
                {
                  int yyaction;
                  const short int* yyconflicts;
                  yy_state_num yystate = yystack_.yytops[s]->state;
                  yygetLRActions (yystate, yytoken_to_shift, &yyaction,
                                  &yyconflicts);
                  /* Note that yyconflicts were handled by yyprocessOneStack.  */
                  YYDPRINTF ((stderr, "On stack %lu, ", (unsigned long int) s));
                  YY_SYMBOL_PRINT ("shifting", yytoken_to_shift, &yyla.get_value(), &yyla.location);
                  yystack_.yyglrShift (s, yyaction, yyposn, &yyla.get_value()]b4_locations_if([, &yyla.location])[);
                  YYDPRINTF ((stderr, "Stack %lu now in state #%d\n",
                              (unsigned long int) s,
                              yystack_.yytops[s]->state));
                }

              if (yystack_.yytops.size() == 1)
                {
                  YYCHK1 (yystack_.yyresolveStack ());
                  YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
                  break;
                }
            }
          continue;
        yyuser_error:
          yy_recover_syntax_error ();
          yyposn = yystack_.yytops.top()->yyposn;
        }

    } catch (const yy_parsing_error& err)
    {
      switch (err.get_status())
      {
        case yy_parsing_error::abort_parsing: goto yyabortlab;
        case yy_parsing_error::memory_exhausted: goto yyexhaustedlab;
        default: goto yybuglab;
      }
    }

   yyacceptlab:
    yyresult = 0;
    goto yyreturn;

   yybuglab:
    YYASSERT (false);
    goto yyabortlab;

   yyabortlab:
    yyresult = 1;
    goto yyreturn;

   yyexhaustedlab:
    error (yyla.location, YY_("memory exhausted"));
    yyresult = 2;
    goto yyreturn;

   yyreturn:
    if (!yyempty)
      yydestruct ("Cleanup: discarding lookahead",
                  yyla.type_get(), &yyla.get_value()]b4_locuser_args([&yyla.location])[);

    /* If the stack is well-formed, pop the stack until it is empty,
       destroying its entries as we go.  But free the stack regardless
       of whether it is well-formed.  */
    yystack_.yystate_pool.clear();

    return yyresult;
  }

#if ]b4_api_PREFIX[DEBUG
  /*--------------------.
  | Print this symbol.  |
  `--------------------*/

  void
  ]b4_parser_class_name[::yy_symbol_value_print_ (int yytype,
                            const semantic_type* yyvaluep]b4_locations_if([[,
                            const location_type* yylocationp]])[)
  {]b4_locations_if([[
    YYUSE (yylocationp);]])[
    YYUSE (yyvaluep);
    std::ostream& yyoutput = debug_stream ();
    std::ostream& yyo = yyoutput;
    YYUSE (yyo);
    ]b4_symbol_actions([printer])[
  }


  void
  ]b4_parser_class_name[::yy_symbol_print_ (int yytype,
                                            const stack_symbol_type& yysym)
  {
    *yycdebug_ << (yytype < YYNTOKENS ? "token" : "nterm")
               << ' ' << yytname[yytype] << " ("]b4_locations_if([[
               << yysym.location << ": "]])[;
    yy_symbol_value_print_ (yytype, &yysym.get_value()]b4_locations_if([[, &yysym.location]])[);
    *yycdebug_ << ')';
  }

  std::ostream&
  ]b4_parser_class_name[::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  ]b4_parser_class_name[::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  ]b4_parser_class_name[::debug_level_type
  ]b4_parser_class_name[::debug_level () const
  {
    return yydebug_;
  }

  void
  ]b4_parser_class_name[::set_debug_level (debug_level_type l)
  {
    // Actually, it is yydebug which is really used.
    yydebug_ = l;
  }

#endif

  // by_state.
  inline
  ]b4_parser_class_name[::by_state::by_state ()
    : state (empty)
  {}

  inline
  ]b4_parser_class_name[::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  ]b4_parser_class_name[::by_state::move (by_state& that)
  {
    state = that.state;
    that.state = empty;
  }

  inline
  ]b4_parser_class_name[::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  ]b4_parser_class_name[::symbol_number_type
  ]b4_parser_class_name[::by_state::type_get () const
  {
    return state == empty ? 0 : yystos_[state];
  }

  inline
  ]b4_parser_class_name[::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  ]b4_parser_class_name[::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s]b4_locations_if([, that.location])[)
  {
    ]b4_variant_if([b4_symbol_variant([that.type_get ()],
                                      [get_value()], [move], [that.get_value()])],
                   [[get_value() = that.get_value();]])[
    // that is emptied.
    that.type = empty;
  }

  inline
  ]b4_parser_class_name[::stack_symbol_type::stack_symbol_type (yy_state_num yyst, size_t posn,
                                                                stack_symbol_type *pred,
                                                                const semantic_type& val]b4_locuser_formals[)
    : super_type(yyst, val]b4_locations_if([, *yylocp])[)
    , yyposn(posn)
    , yypred(pred)
  {}

  inline
  ]b4_parser_class_name[::stack_symbol_type::stack_symbol_type (yy_state_num yyst, size_t posn,
                                                                stack_symbol_type* pred,
                                                                const yy_semantic_value_abstract<]b4_parser_class_name[>& val
                                                                ]b4_locuser_formals[)
    : super_type(yyst, val]b4_locations_if([, *yylocp])[)
    , yyposn(posn)
    , yypred(pred)
  {}

  inline
  ]b4_parser_class_name[::stack_symbol_type&
  ]b4_parser_class_name[::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    ]b4_variant_if([b4_symbol_variant([that.type_get ()],
                                      [get_value()], [copy], [that.get_value()])],
                   [[get_value() = that.get_value();]])[]b4_locations_if([
    location = that.location;])[
    return *this;
  }


  template <typename Base>
  inline
  void
  ]b4_parser_class_name[::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);]b4_variant_if([], [

    // User destructor.
    b4_symbol_actions([destructor], [yysym.type_get ()])])[
  }

]b4_namespace_close
