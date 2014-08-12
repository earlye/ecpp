#ifndef hA46DA356_6B40_4774_A3C3_DB4E00A3ED7A
#define hA46DA356_6B40_4774_A3C3_DB4E00A3ED7A

#include <boost/format.hpp>
#include <fstream>
#include <string>

namespace ecpp
{
  class log
  {
  public:
    void write( char const* file , int line , char const* function ,  std::string message );
    void write( char const* file , int line , char const* function ,  boost::format const& message );
    static log& instance( );
  private:
    static std::string logFileName( );
    log( );
  private:
    std::string logFileName_;
    std::ofstream logFile_;
  };
}

#define LOG( MESSAGE ) ::ecpp::log::instance().write( __FILE__ , __LINE__ , __PRETTY_FUNCTION__ , MESSAGE )

#endif
