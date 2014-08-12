#ifndef h589F3C3F_A01B_4AC9_B08A_AA3FEB69A1A1
#define h589F3C3F_A01B_4AC9_B08A_AA3FEB69A1A1

#include <cstdio>

#include <boost/noncopyable.hpp>

namespace ecpp
{

  class auto_FILE
    : public boost::noncopyable
  {
  public:

    auto_FILE( FILE* handle )
      : handle_( handle )
    { }

    ~auto_FILE( )
    {
      reset( NULL );
    }

    void reset( FILE* handle )
    {
      if ( handle_ )
	{
	  fclose( handle_ );
	}
      handle_ = handle;
    }

    FILE* get( )
    {
      return handle_;
    }

  private:
    FILE* handle_;
  };

}

#endif
