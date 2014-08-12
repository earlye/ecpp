#ifndef h2D4BA428_027D_4E40_81F9_2279A27471F4
#define h2D4BA428_027D_4E40_81F9_2279A27471F4

#include <pthread.h>

#include <ecpp/null_type.hpp>

namespace ecpp
{
  template< typename CONTAINED_OBJECT_TYPE , typename tag = null_type > 
  class thread_local_singleton
  {
  public:
    typedef CONTAINED_OBJECT_TYPE contained_object_type;

    static contained_object_type& instance( )
    {
      pthread_once( key_once() , make_key );
      contained_object_type* result = 
	reinterpret_cast< contained_object_type* >( pthread_getspecific( *key() ) );

      if ( !result )
	{
	  result = allocate_contained_object_type( );
	  pthread_setspecific( *key() , result );
	}

      return *result;
    }

  private:
    static contained_object_type* allocate_contained_object_type( )
    {
      return new contained_object_type;
    }

    static void cleanup_thread( void* value )
    {
      std::cout << boost::format( "%s - %p\n" ) % __PRETTY_FUNCTION__ % value;
      contained_object_type* data = reinterpret_cast< contained_object_type* >( value );
      delete data;
    }

    static pthread_once_t* key_once( )
    {
      static pthread_once_t result = PTHREAD_ONCE_INIT;
      return &result;
    }

    static pthread_key_t* key( )
    {
      static pthread_key_t result;
      return &result;
    }

    static void make_key( )
    {
      pthread_key_create( key() , &cleanup_thread );
    }
  };
}

#endif
