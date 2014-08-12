#include <ecpp/urlencode.hpp>

#include <ecpp/format.hpp>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iterator>
#include <iomanip>

namespace ecpp
{
  std::string urlencode(const std::string& source) 
  {
    using std::string;

    static std::string const not_encoded( "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_" );

#ifdef ECPP_DEBUG_URLENCODE
    std::cout << "0         1         2         3         4" << std::endl;
    std::cout << "01234567890123456789012345678901234567890" << std::endl;
    std::cout << source << std::endl;
#endif
    string result;
    string::size_type start = 0;
    string::size_type end = source.size();
    while( start != string::npos )
      {
	string::size_type enc = source.find_first_not_of( not_encoded , start );
	string sub = source.substr( start , enc - start );
	result += sub;
	if ( enc < end )
	  {
	    string::value_type ch = source[enc];
	    string encoded = ecpp::format( "%%%02x" ) % static_cast< int >( ch );
	    result += encoded;
	    ++enc;
	  }
#ifdef ECPP_DEBUG_URLENCODE
	std::cout << ecpp::format( "start:%d enc:%d sub:\"%s\" result:\"%s\"" ) % start % static_cast<long>(enc) % sub % result << std::endl;
#endif
	start = enc;
      }
    return result;
  }

}
