[
template <typename YYParser>
class yy_semantic_value_abstract
{
public:
  typedef typename YYParser::semantic_type YYSTYPE;
  typedef typename YYParser::location_type YYLTYPE;
  virtual YYSTYPE& get_value() = 0;
  virtual void destroy(const std::string& msg, int type
                       ]b4_locuser_formals([yylocp])[) = 0;

};

template <typename YYParser>
class yy_semantic_simple_value : public yy_semantic_value_abstract<YYParser>
{
public:
  typedef yy_semantic_value_abstract<YYParser> super_t;
  typedef typename super_t::YYSTYPE YYSTYPE;
  typedef typename super_t::YYLTYPE YYLTYPE;
  YYSTYPE& get_value()
  {
    return yyvalue;
  }
  virtual void destroy(const std::string& msg, int type]b4_locuser_formals([yylocp])[)
  {
    yydestruct (msg, type,
                &yyvalue]b4_locuser_args([yylocp])[);
  }
private:
  YYSTYPE yyvalue;
};

template <typename YYParser>
class yy_semantic_option : public yy_semantic_value_abstract<YYParser>
{
public:
  typedef yy_semantic_value_abstract<YYParser> super_t;
  typedef typename super_t::YYSTYPE YYSTYPE;
  typedef typename super_t::YYLTYPE YYLTYPE;
  typedef yy_glr_state<YYParser> state_type;
  typedef yy_semantic_option<YYParser> this_type;
private:
  /** Type tag: always false.  */
  // bool yyisState; -> dynamic dispatch
  /** Rule number for this reduction */
  yy_rule_num yyrule;
  /** The last RHS state in the list of states to be reduced.  */
  state_type* yystate;
  /** The lookahead for this reduction.  */
  int yyrawchar;
  YYSTYPE yyval;
  YYLTYPE yyloc;
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
  this_type* yynext;

public:
  yy_semantic_option(state_type* rhs, yy_rule_num r, int c,
                     bool has_lookahead, this_type* next
                     ]b4_locations_if([[, YYLTYPE loc]])[);

  virtual void destroy(const std::string& msg, int type]b4_locuser_formals([yylocp])[)
  {
    YYFPRINTF (stderr, "%s unresolved", msg);
    state_type *yyrh = yystate;
    for (int yyn = yyrhsLength (yyrule);
         yyn > 0;
         yyrh = yyrh->yypred, --yyn)
      yyrh->yydestroyGLRState (msg]b4_user_args[);
  }

  this_type& operator= (this_type const& other);

  /** True iff YYY0 and YYY1 represent identical options at the top level.
   *  That is, they represent the same rule applied to RHS symbols
   *  that produce the same terminal symbols.  */
  bool operator== (const this_type& yyy1) const;

  /** Assuming identicalOptions (YYY0,YYY1), destructively merge the
   *  alternative semantic values for the RHS-symbols of YYY1 and YYY0.  */
  void yymerge_option_sets (this_type& yyy1);

  /** Return type for yypreference. */
  enum yypreference_value {
    no_combination,
    user_mergeable,
    left_preferred,
    right_preferred
  };

  /** Y0 and Y1 represent two possible actions to take in a given
   *  parsing state.  */
  yypreference_value yypreference (this_type& y1);

#if ]b4_api_PREFIX[DEBUG
  void yyreportTree (int yyindent) const;
#endif

  YYRESULTTAG
  yyreportAmbiguity (this_type& yyx1]b4_pure_formals[) const;

  YYSTYPE& get_value()
  {
    return yyval;
  }
};
]
