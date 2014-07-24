b4_namespace_open[

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

]b4_namespace_close
