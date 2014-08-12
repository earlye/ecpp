#include <ecpp/substr_range.hpp>

namespace ecpp
{
  std::string substr_range( std::string const& src , std::string::size_type begin , std::string::size_type end )
  {
    if ( begin == std::string::npos )
      return std::string();

    std::string::size_type length = end;
    if ( length != std::string::npos )
      length -= begin;
    return src.substr( begin , length );
  }
}
