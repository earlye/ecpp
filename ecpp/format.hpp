#ifndef h4E3AA4F4_024B_4CF4_B05D_742C5476C823
#define h4E3AA4F4_024B_4CF4_B05D_742C5476C823

#include <boost/format.hpp>

namespace ecpp
{
  class format
  {
  public:
    format( std::string const& fmt )
      : fmt_(fmt)
    { }

    operator std::string( ) const
    { return boost::str( fmt_ ); }

    template< typename OTHER_TYPE >
    format& operator%( OTHER_TYPE other )
    {
      fmt_ % other;
      return *this;
    }

  private:
    boost::format fmt_;
  };

  template< typename OSTREAM_TYPE >
  OSTREAM_TYPE& operator<<( OSTREAM_TYPE& os , format const& fmt )
  {
    return os << fmt.operator std::string();
  }
}

#endif
