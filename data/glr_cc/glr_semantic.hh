[
template <typename YYParser>
class yy_semantic_value_abstract
{
public:
  typedef typename YYParser::semantic_type yys_type;
  typedef typename YYParser::location_type location_type;
  typedef typename YYParser::stack_symbol_type state_type;
  virtual ~yy_semantic_value_abstract()
  {}
  virtual yys_type& get_value() = 0;
  virtual void destroy(const std::string& msg, int type
                       ]b4_locuser_formals([yylocp])[) = 0;
  virtual bool resolved() = 0;
  virtual yy_semantic_value_abstract<YYParser>* clone() const = 0;
};

template <typename YYParser>
class yy_semantic_simple_value : public yy_semantic_value_abstract<YYParser>
{
public:
  typedef yy_semantic_value_abstract<YYParser> super_type;
  typedef typename super_type::yys_type yys_type;
  typedef typename super_type::location_type location_type;
  typedef typename YYParser::by_state::kind_type kind_type;
  typedef yy_semantic_simple_value<YYParser> this_type;

  yy_semantic_simple_value()
  {}


  yy_semantic_simple_value(kind_type kind, yys_type& value);

  template<typename Value>
  yy_semantic_simple_value(kind_type kind, const Value& value);

  this_type& operator= (const this_type& other);

  yys_type& get_value()
  {
    return yyvalue;
  }
  virtual void destroy(const std::string& msg, int type]b4_locuser_formals([yylocp])[)
  {
    yydestruct (msg, type,
                &yyvalue]b4_locuser_args([yylocp])[);
  }
  virtual bool resolved() { return true; }
  virtual yy_semantic_value_abstract<YYParser>* clone() const;
private:
  /// No copy
  yy_semantic_simple_value(const yy_semantic_simple_value&);
  /// The type of the value in the variant
  kind_type yykind;
  /// The variant
  yys_type yyvalue;
};

template <typename YYParser>
class yy_semantic_option : public yy_semantic_value_abstract<YYParser>
{
public:
  typedef yy_semantic_value_abstract<YYParser> super_type;
  typedef typename super_type::yys_type yys_type;
  typedef typename super_type::location_type location_type;
  typedef typename super_type::state_type state_type;
  typedef yy_semantic_option<YYParser> this_type;
  typedef yy_glr_stack<YYParser> stack_type;

  /** Rule number for this reduction */
  yy_rule_num yyrule;
  /** The last RHS state in the list of states to be reduced.  */
  state_type* yystate;
  /** The lookahead for this reduction.  */
  int yyrawchar;
  yys_type yyval;
  location_type yyloc;
private:
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
  this_type* yynext;

  stack_type* yystack;

public:
  yy_semantic_option(stack_type* yystack, state_type* rhs, yy_rule_num r, int c,
                     bool has_lookahead, this_type* next
                     ]b4_locations_if([[, location_type loc]])[);
  yy_semantic_option(const this_type& other);

  virtual void destroy(const std::string& msg, int type]b4_locuser_formals([yylocp])[)
  {
    YYFPRINTF (stderr, "%s unresolved", msg.c_str());
    state_type *yyrh = this->yystate;
    for (int yyn = yystack->get_parser()->yyrhs_length (yyrule);
         yyn > 0;
         yyrh = yyrh->yypred, --yyn)
      yystack->parser->yy_destroy_ (msg.c_str(), *yyrh);
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

  yys_type& get_value()
  {
    return yyval;
  }

  this_type*& next()
  {
    return yynext;
  }

  virtual bool resolved() { return false; }
  virtual yy_semantic_value_abstract<YYParser>* clone() const;
};
]
