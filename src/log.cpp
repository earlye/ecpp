#include <ecpp/log.hpp>

#include <ecpp/expand_env.hpp>
#include <ecpp/setenv.hpp>
#include <ecpp/getenv.hpp>

#include <fstream>
#include <iostream>

#ifndef ECPP_LOGPATH
#define ECPP_LOGPATH "$HOME/ecpp.log"
#endif

namespace ecpp
{
  void log::write( char const* file , int line , char const* function ,  std::string message )
  {
    logFile_ << file << ":" << line << ":" << function << ":" << message << std::endl;
  }

  void log::write( char const* file , int line , char const* function ,  boost::format const& message )
  {
    logFile_ << file << ":" << line << ":" << function << ":" << boost::str( message ) << std::endl;
  }

  log& log::instance( )
  {
    static log result;
    return result;
  }

  std::string log::logFileName( ) 
  { 
    std::string unexpanded = ecpp::getenv( "LOGPATH" , ECPP_LOGPATH );

    // Make sure that the ECPP_LOGDIR and ECPP_LOGNAME environment variables are set.
    // setenv's third parameter, if 0, says that if the environment variable is already set, do nothing.
    ecpp::setenv( "HOME" , ecpp::getenv( "USERPROFILE" ) , 0 );

    std::string result = ecpp::expand_env( unexpanded );
    return result;
  }


  log::log( )
    : logFileName_( logFileName( ) ) 
    , logFile_( logFileName_.c_str() )
  {
    write( __FILE__ , __LINE__ , __PRETTY_FUNCTION__ , "----" );
    write( __FILE__ , __LINE__ , __PRETTY_FUNCTION__ , "Log Session Starting" );
  }

}
