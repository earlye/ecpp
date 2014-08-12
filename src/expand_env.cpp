#include <ecpp/substr_range.hpp>

#include <ecpp/getenv.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace ecpp
{
  typedef std::runtime_error bad_substitution;

  /*! \brief parser for environment strings
   *
   * \author eehlinge
   * \date 2011-12-02
   *
   * This class implements a simple state machine to parse environment
   * strings.  The current state is represented by the address of a
   * member function, stored in state_.  Each time the state machine
   * processes a step (in the constructor), we just call the function
   * that state_ points to.  To indicate that the parsing is done, a
   * member function can set state_ to NULL.
   *
   * A typical parser state machine for a complex language will scan a
   * character at a time and have dozens of states, each with switch
   * statements and the like to figure out what state to proceed to.
   * Environment variable expansion is a very simple language by
   * comparison, so we use std::string member functions like find and
   * find_first_not_of to ease development and hopefully clarify what's
   * going on.
   *
   * The machine starts off in state_init, which looks for "$" and
   * switches to state_saw_dollar when it finds one, copying
   * non-variable substrings to the result along the way.
   *
   * In state_saw_dollar, we check to see if it's a curly-brace
   * expansion, like ${FOO}, or a simple one, like $FOO.  In the first
   * case, we look for the '}' to determine the variable name.  In the
   * second case, we look for the first non-alphanumeric/underscore
   * character.  Once the variable name is known, we use getenv() to
   * expand it, and move on.
   * 
   */
  class environment_string_parser
  {
  public:
    environment_string_parser( std::string const& src )
      : src_(src)
      , i_(0)
      , word_start_(0)
      , state_( &environment_string_parser::state_init )
    { 
      while( state_ )
	(this->*state_)( );
    }

    std::string result( ) const
    {
      return result_.str();
    }

  private:
    void state_init( )
    {
      dollar_ = src_.find( '$' , i_ );
      result_ << ecpp::substr_range( src_ , i_ , dollar_ );
      if ( dollar_ == std::string::npos )
	state_ = NULL;
      else
	state_ = &environment_string_parser::state_saw_dollar;
    }

    void state_saw_dollar( )
    {
      i_ = dollar_ + 1;
      if ( i_ >= src_.length() )
	{
	  result_ << '$';
	  state_ = NULL;
	  return;
	}

      if ( i_ == '$' )
	{
	  result_ << '$';
	  state_ = &environment_string_parser::state_init;
	  return;
	}

      if ( src_[i_] == '{' )
	{
	  ++i_;
	  size_type end_curl = src_.find( '}' , i_ );
	  if ( end_curl == std::string::npos )
	    throw bad_substitution( "Environment substitution has open {, but no close }" );

	  std::string var_name = ecpp::substr_range( src_ , i_ , end_curl );
	  result_ << ecpp::getenv( var_name.c_str() );
	  i_ = end_curl + 1;
	  state_ = &environment_string_parser::state_init;
	  return;
	}

      static std::string const symbol_chars( "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
					     "abcdefghijklmnopqrstuvwxyz"
					     "0123456789"
					     "_" );
      size_type end_var_name = src_.find_first_not_of( symbol_chars , i_ );
      std::string var_name = ecpp::substr_range( src_ , i_ , end_var_name );
      result_ << ecpp::getenv( var_name.c_str() );
      i_ = end_var_name;
      state_ = &environment_string_parser::state_init;
    }


  private:
    typedef void (environment_string_parser::* state_method)( );
    typedef std::string::size_type size_type;

    std::string const& src_;
    std::stringstream result_;
    size_type i_;
    size_type word_start_;
    size_type dollar_;
    state_method state_;
  };

  /*! \brief Expand environment variables contained in "src"
   *
   * \author eehlinge
   * \date   2011-12-01
   *
   * So it turns out that wordexp is horribly broken on OSX (perhaps
   * Linux, too?).  Using it in a tight loop will result in random,
   * silent failures, which of course is completely unacceptable.  So
   * we'll parse src ourselves and move on with life.
   *
   */
  std::string expand_env( std::string const& src )
  {
    environment_string_parser parser(src);
    std::string result = parser.result();
    return result;
  }

}
