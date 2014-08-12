#ifndef h22EB9937_2BAC_4AC0_B321_150A98FEE1D6
#define h22EB9937_2BAC_4AC0_B321_150A98FEE1D6

#include <string>

namespace ecpp
{
  void setenv( char const* name , char const* value , int overwrite );
  void setenv( char const* name , std::string const& value , int overwrite );
}

#endif
