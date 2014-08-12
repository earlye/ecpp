#include <ecpp/getenv.hpp>
#include <ecpp/to_string.hpp>

#include <cassert>

#if defined( WINDOWS ) || defined( __WINNT__ )
#include <windows.h>
#include <vector>
#else
#include <stdlib.h>
#endif

namespace ecpp
{
  std::string getenv( char const* name )
  {
    return getenv( name , "" );
  }

  std::string getenv( char const* name , char const* the_default )
  {
    assert( the_default );
#if defined( WINDOWS ) || defined( __WINNT__ )

    for( DWORD size = 512; ; )
      {
	std::vector<char> buffer(size);
	DWORD check = GetEnvironmentVariableA( name , &*buffer.begin() , buffer.size() );
	if ( check == 0 )
	  {
	    return ecpp::to_string( the_default );
	  }
	if ( check > buffer.size() )
	  {
	    size = check + 1;
	    continue;
	  }
	buffer.resize( check + 1 );
	*buffer.rbegin() = '\0';
	return ecpp::to_string(&*buffer.begin());
      }
    
#else
    return ecpp::to_string( ::getenv( name ) , the_default );
#endif
  }
}
