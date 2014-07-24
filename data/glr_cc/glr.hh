[
class yy_parsing_error
{
public:

  enum error_status
  {
    abort,
    memory_exhausted,
    bug
  };

  yy_parsing_error(error_status s)
  : status(s)
  {}

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
    typedef yy_glr_stack<]b4_parser_class_name[> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    //void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    //void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    //void yypop_ (unsigned int n = 1);

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

    ]b4_parse_param_vars[
  };

#ifndef ]b4_api_PREFIX[STYPE
# define ]b4_api_PREFIX[STYPE ]b4_namespace_ref[::]b4_parser_class_name[::semantic_type
#endif
#ifndef ]b4_api_PREFIX[LTYPE
# define ]b4_api_PREFIX[LTYPE ]b4_namespace_ref[::]b4_parser_class_name[::location_type
#endif

]
