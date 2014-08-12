#include <ecpp/setenv.hpp>

#if defined( WINDOWS ) || defined (__WINNT__)
#include <windows.h>
#else
#include <stdlib.h>
#endif

namespace ecpp
{
  void setenv( char const* name , char const* value , int overwrite )
  {
    if ( !overwrite && getenv( name ) )
      return;

#if defined( WINDOWS ) || defined (__WINNT__)
    SetEnvironmentVariable( name , value );
#else
    if ( value )
      {
	::setenv( name , value , overwrite );
      }
    else
      ::unsetenv( name );  
#endif
  }

  void setenv( char const* name , std::string const& value , int overwrite )
  {
    setenv( name , value.c_str() , overwrite );
  }
}
