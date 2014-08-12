#include <ecpp/demangle_cpp_identifier.hpp>
#include <ecpp/to_string.hpp>

#if defined( __GNUC__ ) && ( __GXX_ABI_VERSION >= 1002 ) // g++ with C++ ABI > 1002
#include <cxxabi.h>
#else
#error Demangle for your compiler
#endif

namespace ecpp
{
  std::string demangle_cpp_identifier( char const* id )
  {
#if defined( __GNUC__ ) && ( __GXX_ABI_VERSION >= 1002 ) // g++ with C++ ABI > 1002
    int status = 0;
    char* result = abi::__cxa_demangle(id, 0, 0, &status);
    return to_string( result , ecpp::to_string( id ) );
#else
    #error Demangle for your compiler.
#endif
  }
}
