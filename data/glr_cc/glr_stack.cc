b4_namespace_open[
#define yylval parser->yylval
#define yylloc parser->yyla.location

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif


#define YYPROTOTYPE(Type)     \
template <typename YYParser>  \
Type                          \
yy_glr_stack<YYParser>


/** Add a new semantic action that will execute the action for rule
 *  YYRULE on the semantic values in YYRHS to the list of
 *  alternative actions for YYSTATE.  Assumes that YYRHS comes from
 *  stack #YYK of *YYSTACKP. */
YYPROTOTYPE(void)::yyaddDeferredAction (size_t yyk, state_type* yystate,
                                             state_type* yyrhs,
                                             yy_rule_num yyrule)
{
  //  std::cerr << "yyaddDeferredAction" << std::endl;
  //  yypdumpstack(yystackp);
  yystate->set_semantic_value(new semantic_type(this, yyrhs, yyrule, yystate->type_get(),
                             yytops.yylookaheadNeeds[yyk], yystate->get_semantic_option()
                            ]b4_locations_if([, yylloc])[));

  //  std::cerr << "yyaddDeferredAction: done" << std::endl;
}

/** Shift to a new state on stack #YYK of *YYSTACKP, corresponding to LR
 * state YYLRSTATE, at input position YYPOSN, with (resolved) semantic
 * value *YYVALP and source location *YYLOCP.  */
YYPROTOTYPE(void)::yyglrShift (size_t yyk, yy_state_num yylrState, size_t yyposn,
                          yys_type* yyvalp, location_type* yylocp)
{
  yystate_pool.push_back(state_type(yylrState, yyposn,
                            yytops.yystates[yyk], *yyvalp
                            ]b4_locations_if([[, yylocp]])[));

  //  std::cerr << "Shifting at: " << *yylocp << std::endl;
  //  std::cerr << "Shifting: " << *yyvalp << std::endl;

  yytops.yystates[yyk] = &yystate_pool.back();
}

/** Shift stack #YYK of *YYSTACKP, to a new state corresponding to LR
 *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
 *  semantic value of YYRHS under the action for YYRULE.  */
YYPROTOTYPE(void)::yyglrShiftDefer (size_t yyk, yy_state_num yylrState,
                                    size_t yyposn, state_type* yyrhs,
                                    yy_rule_num yyrule)
{
  //  std::cerr << "yyglrShiftDefer" << std::endl;
  yystate_pool.push_back(state_type(yylrState, yyposn,
                            yytops.yystates[yyk], yyrhs->yysemantic
                            ]b4_locations_if([[, &yyrhs->location]])[));
  yytops.yystates[yyk] = &yystate_pool.back();

  /* Invokes YY_RESERVE_GLRSTACK.  */
  yyaddDeferredAction (yyk, &yystate_pool.back(), yyrhs, yyrule);
  //  std::cerr << "yyglrShiftDefer: done" << std::endl;
}


/** Undelete the last stack in *YYSTACKP that was marked as deleted.  Can
    only be done once after a deletion, and only when all other stacks have
    been deleted.  */
YYPROTOTYPE(void)::yyundeleteLastStack ()
{
  if (yylastDeleted == YY_NULLPTR || yytops.size() != 0)
    return;
  yytops.pop();
  yytops.push_back(yylastDeleted);
  YYDPRINTF ((stderr, "Restoring last deleted stack as stack #0.\n"));
  yylastDeleted = YY_NULLPTR;
}

YYPROTOTYPE(void)::yyremoveDeletes ()
{
  size_t i = 0, j = 0;
  while (j < yytops.size())
    {
      if (yytops[i] == YY_NULLPTR)
        {
          if (i == j)
            {
              YYDPRINTF ((stderr, "Removing dead stacks.\n"));
            }
          yytops.remove(i);
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
          ++j;
        }
      ++i;
    }
}

/** Pop the symbols consumed by reduction #YYRULE from the top of stack
 *  #YYK of *YYSTACKP, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved.  Set *YYVALP to the resulting value,
 *  and *YYLOCP to the computed location (if any).  Return value is as
 *  for userAction.  */
YYPROTOTYPE(YYRESULTTAG)::yydoAction (size_t yyk, yy_rule_num yyrule,
                                      yys_type* yyvalp]b4_locations_if([, location_type* yylocp])[)
{
  int yynrhs = parser->yyrhs_length (yyrule);

  if (yysplitPoint == YY_NULLPTR)
    {
      /* Standard special case: single stack.  */
      state_type yyrhs;
      yyrhs.move(*yytops[yyk]);
      YYASSERT (yyk == 0);
      yystate_pool.pop_back();
      yytops.yystates[0] = &yystate_pool.back();
      YY_REDUCE_PRINT ((&yyrhs, yyk, yyrule, true));
      return yyuserAction (yyrule, yynrhs, &yyrhs,
                           yyvalp]b4_locuser_args[);
    }
  else
    {
      state_type* yys;
      state_type yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
      yys = yyrhsVals[YYMAXRHS + YYMAXLEFT].yypred
        = yytops.yystates[yyk];]b4_locations_if([[
      if (yynrhs == 0)
        /* Set default location.  */
        yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].location = yys->location;]])[
      for (int i = 0; i < yynrhs; ++i)
        {
          yys = yys->yypred;
          YYASSERT (yys);
        }
      yyupdateSplit (yys);
      yytops.yystates[yyk] = yys;
      YY_REDUCE_PRINT ((yyrhsVals + YYMAXRHS + YYMAXLEFT - 1, yyk, yyrule, false));
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
YYPROTOTYPE(YYRESULTTAG)::yyglrReduce (size_t yyk, yy_rule_num yyrule,
                                       bool yyforceEval)
{
  size_t yyposn = yytops.yystates[yyk]->yyposn;

  if (yyforceEval || yysplitPoint == YY_NULLPTR)
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
          ]b4_variant_if([b4_symbol_variant([[parser->yyr1_[yyrule]]],
                                            [[yysval]], [destroy])]);[
          return yyflag;
        }
      YY_SYMBOL_PRINT ("-> $$ =", parser->yyr1_[yyrule], &yysval, &yyloc);
      //      std::cerr << "Before shitf" << std::endl;
      yyglrShift (yyk,
                  parser->yy_lr_goto_state_ (yytops[yyk]->state,
                                 parser->yylhsNonterm (yyrule)),
                  yyposn, &yysval]b4_locations_if([, &yyloc])[);
      //      std::cerr << "After shitf" << std::endl;
    }
  else
    {
      state_type* yys = yytops.yystates[yyk];
      for (int i = parser->yyrhs_length (yyrule); 0 < i; --i)
        {
          yys = yys->yypred;
          YYASSERT (yys);
        }
      yyupdateSplit (yys);

      yy_state_num yynewLRState = parser->yy_lr_goto_state_ (yys->state,
                                                 parser->yylhsNonterm (yyrule));
      YYDPRINTF ((stderr,
                  "Reduced stack %lu by rule #%d; action deferred.  "
                  "Now in state %d.\n",
                  (unsigned long int) yyk, yyrule - 1, yynewLRState));

      state_type* yys0 = yytops.yystates[yyk];
      for (size_t i = 0; i < yytops.size(); i += 1)
        if (i != yyk && yytops[i] != YY_NULLPTR)
          {
            state_type *yysplit = yysplitPoint;
            state_type *yyp = yytops[i];
            while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn)
              {
                if (yyp->state == yynewLRState && yyp->yypred == yys)
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

      yytops.yystates[yyk] = yys;
      yyglrShiftDefer (yyk, yynewLRState, yyposn, yys0, yyrule);
    }
  return yyok;
}

YYPROTOTYPE(size_t)::yysplitStack (size_t yyk)
{
  if (yysplitPoint == YY_NULLPTR)
    {
      YYASSERT (yyk == 0);
      yysplitPoint = yytops.yystates[yyk];
    }
  yytops.split_stack();
  return yytops.size() - 1;
}

YYPROTOTYPE(YYRESULTTAG)::yyresolveStack (]b4_user_formals_no_comma[)
{
  if (yysplitPoint != YY_NULLPTR)
    {
      state_type* yys = yytops.yystates[0];
      int n = 0;

      for (; yys != yysplitPoint; yys = yys->yypred, ++n)
        continue;
      YYCHK (yyresolveStates (yytops.yystates[0], n));
    }
  return yyok;
}

YYPROTOTYPE(YYRESULTTAG)::yyprocessOneStack (size_t yyk, size_t yyposn]b4_pure_formals[)
{
  while (yytops.yystates[yyk] != YY_NULLPTR)
    {
      yy_state_num yystate = yytops.yystates[yyk]->state;
      YYDPRINTF ((stderr, "Stack %lu Entering state %d\n",
                  (unsigned long int) yyk, yystate));

      YYASSERT (yystate != YYFINAL);

      if (parser->yyisDefaultedState (yystate))
        {
          yy_rule_num yyrule = parser->yydefaultAction (yystate);
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, "Stack %lu dies.\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yyk);
              return yyok;
            }
          YYRESULTTAG yyflag = yyglrReduce (yyk, yyrule,
                                            yyimmediate[yyrule]);
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
          if (parser->yyempty)
            {
              YYDPRINTF ((stderr, "Reading a token: "));]b4_token_ctor_if([[
              ]b4_parser_class_name[::symbol_type yylookahead (]b4_lex[);
              parser->yyla.move (yylookahead);]], [[
              parser->yyla.type = yytranslate_ (]b4_lex[);]])[
              parser->yyempty = false;
            }

          if (parser->yyla.type_get() == YYEOF)
            YYDPRINTF ((stderr, "Now at end of input.\n"));
          else
            YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);

          parser->yygetLRActions (yytops.top()->state, yytoken, &yyaction, &yyconflicts);

          while (*yyconflicts != 0)
            {
              size_t yynewStack = yysplitStack (yyk);
              YYDPRINTF ((stderr, "Splitting off stack %lu from %lu.\n",
                          (unsigned long int) yynewStack,
                          (unsigned long int) yyk));
              YYRESULTTAG yyflag = yyglrReduce (yynewStack, *yyconflicts,
                                    yyimmediate[*yyconflicts]);
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

          if (parser->yyisShiftAction (yyaction))
            break;
          else if (parser->yyisErrorAction (yyaction))
            {
              YYDPRINTF ((stderr, "Stack %lu dies.\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yyk);
              break;
            }
          else
            {
              YYRESULTTAG yyflag = yyglrReduce (yyk, -yyaction,
                                                yyimmediate[-yyaction]);
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


YYPROTOTYPE(void)::yypstack (size_t yyk)
{
  yypstates (yytops.yystates[yyk]);
}
/*#define YYINDEX(YYX)                                                         \
    ((YYX) == YY_NULLPTR ? -1 : (yy_glr_stack_item*) (YYX) - yystackp->yyitems)

void
yy_glr_stack::yypdumpstack ()
{
  yy_glr_state* yyp;
  size_t yyi;
  for (yyp = yyitems; yyp < yynextFree; yyp += 1)
    {
      YYFPRINTF (stderr, "%3lu. ",
                 (unsigned long int) (yyp - yyitems));
      if (*(bool *) yyp)
        {
          YYASSERT (yyp->yystate.yyisState);
          YYASSERT (yyp->yyoption.yyisState);
          YYFPRINTF (stderr, "Res: %d, LR State: %d, posn: %lu, pred: %ld",
                     yyp->yystate.yyresolved, yyp->yystate.yylrState,
                     (unsigned long int) yyp->yystate.yyposn,
                     (long int) YYINDEX (yyp->yystate.yypred));
          if (! yyp->yystate.yyresolved)
            YYFPRINTF (stderr, ", firstVal: %ld",
                       (long int) YYINDEX (yyp->yystate
                                             .yysemantics.yyfirstVal));
        }
      else
        {
          YYASSERT (!yyp->yystate.yyisState);
          YYASSERT (!yyp->yyoption.yyisState);
          YYFPRINTF (stderr, "Option. rule: %d, state: %ld, next: %ld",
                     yyp->yyoption.yyrule - 1,
                     (long int) YYINDEX (yyp->yyoption.yystate),
                     (long int) YYINDEX (yyp->yyoption.yynext));
        }
      YYFPRINTF (stderr, "\n");
    }
  YYFPRINTF (stderr, "Tops:");
  for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
    YYFPRINTF (stderr, "%lu: %ld; ", (unsigned long int) yyi,
               (long int) YYINDEX (yystackp->yytops.yystates[yyi]));
  YYFPRINTF (stderr, "\n");
}*/

YYPROTOTYPE(YYRESULTTAG)::yyresolveValue (state_type* yys)
{
  semantic_type* yyoptionList = yys->get_semantic_option();
  semantic_type* yybest = yyoptionList;
  bool yymerge = false;
  YYSTYPE yysval;]b4_locations_if([
  YYLTYPE *yylocp = &yys->location;])[

  for (semantic_type** yypp = &yyoptionList->next(); *yypp != YY_NULLPTR; )
    {
      semantic_type* yyp = *yypp;

      if (*yybest == *yyp)
        {
          yybest->yymerge_option_sets (*yyp);
          *yypp = yyp->next();
        }
      else
        {
          switch (yybest->yypreference (*yyp))
            {
            case semantic_type::no_combination:]b4_locations_if([[
              yyresolveLocations (yys, 1);]])[
              return parser->yyreportAmbiguity (yybest, yyp]b4_pure_args[);
              break;
            case semantic_type::user_mergeable:
              yymerge = true;
              break;
            case semantic_type::left_preferred:
              break;
            case semantic_type::right_preferred:
              yybest = yyp;
              yymerge = false;
              break;
            default:
              /* This cannot happen so it is not worth a YYASSERT (yyfalse),
                 but some compilers complain if the default case is
                 omitted.  */
              break;
            }
          yypp = &yyp->next();
        }
    }

  YYRESULTTAG yyflag;
  if (yymerge)
    {
      semantic_type* yyp;
      int yyprec = yydprec[yybest->yyrule];
      yyflag = yyresolveAction (yybest, &yysval]b4_locuser_args[);
      if (yyflag == yyok)
        for (yyp = yybest->next(); yyp != YY_NULLPTR; yyp = yyp->next())
          {
            if (yyprec == yydprec[yyp->yyrule])
              {
                yys_type yysval_other;]b4_locations_if([
                location_type yydummy;])[
                yyflag = yyresolveAction (yyp, &yysval_other]b4_locuser_args([&yydummy])[);
                if (yyflag != yyok)
                  {
                    parser->yydestruct ("Cleanup: discarding incompletely merged value for",
                                parser->yystos_[yys->state],
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
      yys->yysemantic = new yy_semantic_simple_value<YYParser>;]b4_variant_if([[
      ]b4_symbol_variant([[parser->yystos_[yys->state]]],
                         [[yys->yysemantic->get_value()]],
                         [template move], [yysval])], [[
      yys->yysemantic->get_value() = yysval;]])[
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
YYPROTOTYPE(YYRESULTTAG)::yyresolveStates (state_type* yys, int yyn)
{
  if (0 < yyn)
    {
      YYASSERT (yys->yypred);
      YYCHK (yyresolveStates (yys->yypred, yyn-1));
      if (! yys->yysemantic->resolved())
        YYCHK (yyresolveValue (yys));
    }
  return yyok;
}

/** Resolve the states for the RHS of YYOPT on *YYSTACKP, perform its
 *  user action, and return the semantic value and location in *YYVALP
 *  and *YYLOCP.  Regardless of whether result = yyok, all RHS states
 *  have been destroyed (assuming the user action destroys all RHS
 *  semantic values if invoked).  */
YYPROTOTYPE(YYRESULTTAG)::yyresolveAction (semantic_type* yyopt,
                               yys_type* yyvalp]b4_locuser_formals[)
{
  state_type yyrhsVals;
  int yynrhs = parser->yyrhs_length (yyopt->yyrule);
  YYRESULTTAG yyflag =
    yyresolveStates (yyopt->yystate, yynrhs);
  if (yyflag != yyok)
    {
      state_type *yys;
      for (yys = yyopt->yystate; yynrhs > 0; yys = yys->yypred, yynrhs -= 1)
        parser->yy_destroy_ ("Cleanup: popping", *yys);
      return yyflag;
    }

  yyrhsVals.yypred = yyopt->yystate;]b4_locations_if([[
  if (yynrhs == 0)
    /* Set default location.  */
    yyrhsVals.location = yyopt->yystate->location;]])[
  {
    ]b4_parser_class_name[::token_number_type yychar_current;
    yys_type yylval_current;]b4_locations_if([
    location_type yylloc_current;])[
  //  YY_SYMBOL_PRINT("yyresolveAction: BEFORE",
  //                  YYTRANSLATE(yychar), &yylval, &yylloc);

    YY_SYMBOL_SWAP (yychar_current, yylval_current]b4_locations_if([, yylloc_current])[,
                    parser->yyla.type_get(), yylval]b4_locations_if([, yylloc])[);
    std::swap(yychar_current, parser->yyla.type);
    YY_SYMBOL_COPY (parser->yyla.type_get(), yylval]b4_locations_if([, yylloc])[,
                    yyopt->yyrawchar, yyopt->yyval]b4_locations_if([, yyopt->yyloc])[);
    parser->yyla.type = yyopt->yyrawchar;
    //  YY_SYMBOL_PRINT("yyresolveAction: DURING",
    //              YYTRANSLATE(yychar), &yylval, &yylloc);
    yyflag = yyuserAction (yyopt->yyrule, yynrhs,
                           &yyrhsVals,
                           yyvalp]b4_locuser_args[);
    YY_SYMBOL_SWAP (parser->yyla.type_get(), yylval]b4_locations_if([, yylloc])[,
                    yychar_current, yylval_current]b4_locations_if([, yylloc_current])[);
    std::swap(parser->yyla.type, yychar_current);
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
YYPROTOTYPE(YYRESULTTAG)::yyuserAction (yy_rule_num yyn, size_t yyrhslen, state_type* yyvsp,
                            yys_type* yyvalp]b4_locuser_formals[)
{
  bool yynormal YY_ATTRIBUTE_UNUSED = (yysplitPoint == YY_NULLPTR);
  //  std::cerr << "yyuserAction" << std::endl;
  YYUSE(yyrhslen);
  YYUSE(yyvalp);]b4_locations_if([
  YYUSE(yylocp);])[
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
# define yyclearin (parser->yychar = YYEMPTY)
# undef YYBACKUP
# define YYBACKUP(Token, Value)                                              \
  return yyerror (]b4_yyerror_args[YY_("syntax error: cannot back up")),     \
         yyerrok, yyerr

  yy_args_stack<YYParser> yyargs(yyvsp, yyrhslen);
  ]b4_variant_if([
    /* Variants are always initialized to an empty instance of the
       correct type. The default $$=$1 action is NOT applied when using
       variants.  */
    b4_symbol_variant([[parser->yyr1_@{yyn@}]], [(*yyvalp)], [template build])], [[
  if (yyrhslen == 0)
    *yyvalp = yyval_default;
  else
    *yyvalp = yyargs[1];]])b4_locations_if([[
  if (yyrhslen)
    {
      yylocp->begin  = yyargs[1]->location.begin;
      yylocp->end    = yyargs[yyrhslen]->location.end;
    }
  else
    {
      yylocp->begin = yylocp->end = yyargs[0]->location.end;
    }
  yyerror_range[1].location = *yylocp;
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
YYPROTOTYPE(void)::yyresolveLocations (state_type *yys1, int yyn1)
{
  if (0 < yyn1)
    {
      yyresolveLocations (yys1->yypred, yyn1 - 1);
      if (!yys1->yysemantic->resolved())
        {
          state_type yyrhsloc[1 + YYMAXRHS];
          int yynrhs;
          semantic_type *yyoption = yys1->get_semantic_option();
          YYASSERT (yyoption);
          yynrhs = parser->yyrhs_length (yyoption->yyrule);
          if (0 < yynrhs)
            {
              state_type *yys;
              int yyn;
              yyresolveLocations (yyoption->yystate, yynrhs);
              for (yys = yyoption->yystate, yyn = yynrhs;
                   yyn > 0;
                   yys = yys->yypred, yyn -= 1)
                yyrhsloc[yyn].location = yys->location;
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
              state_type *yyprevious = yyoption->yystate;
              yyrhsloc[0].location = yyprevious->location;
            }
          YYLLOC_DEFAULT ((yys1->location), yyrhsloc, yynrhs);
        }
    }
}]])[
#undef yylval
#undef yylloc
#undef YYPROTOTYPE
]b4_namespace_close
