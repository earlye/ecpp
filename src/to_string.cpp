#include <ecpp/to_string.hpp>

namespace ecpp
{
  std::string to_string( char const* str )
  {
    if ( str )
      return std::string( str );
    return std::string();
  }

  std::string to_string( char const* str , std::string const& the_default )
  {
    if ( str )
      return std::string( str );
    return the_default;
  }
}
