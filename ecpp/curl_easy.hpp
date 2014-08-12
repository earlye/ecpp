#ifndef h7183BE2E_D987_42AE_B2E9_802D291F5979
#define h7183BE2E_D987_42AE_B2E9_802D291F5979

#include <curl/curl.h>
#include <curl/easy.h>

#include <boost/noncopyable.hpp>

#include <stdexcept>

namespace ecpp
{
  class curl_easy
    : public boost::noncopyable
  {
  public:
    curl_easy( )
      : handle_( allocate_handle() )
    { 
      setopt< void* >( CURLOPT_PROGRESSDATA , this );
      setopt< void* >( CURLOPT_PROGRESSFUNCTION , (void*)progress_callback );
    }

    ~curl_easy( )
    {
      deallocate_handle( handle_ );
      handle_ = NULL;
    }

    void reset( )
    {
      CURL* handle = allocate_handle();
      deallocate_handle( handle_ );
      handle_ = handle;
    }

    void throw_errors( CURLcode check )
    {
      switch( check )
	{
	case CURLE_OK: return;
	default:
	  throw std::runtime_error( curl_easy_strerror( check ) );
	}
    }

    template< typename P1 >
    CURLcode try_setopt(CURLoption option, P1 parameter)
    {
      CURLcode result = curl_easy_setopt( handle_ , option , parameter );
      return result;
    }

    template< typename P1 >
    void setopt( CURLoption option , P1 parameter )
    {
      CURLcode result = try_setopt( option , parameter );
      throw_errors( result );
    }

    template< typename P1 >
    CURLcode try_getinfo( CURLINFO info , P1 parameter )
    {
      CURLcode result = curl_easy_getinfo( handle_ , info , parameter );
      return result;
    }

    template<typename P1 >
    void getinfo( CURLINFO info , P1 parameter )
    {
      CURLcode result = try_getinfo( info , parameter );
      throw_errors( result );
    }

    CURLcode try_perform( )
    {
      return curl_easy_perform( handle_ );
    }

    void perform( )
    {
      CURLcode result = try_perform( );
      throw_errors( result );
    }

    void setopt_verbose( bool value )
    {
      setopt( CURLOPT_VERBOSE , (int)value );
    }

    void setopt_upload( bool value )
    {
      setopt( CURLOPT_UPLOAD , (int)value );
    }

    void setopt_url( std::string const& url )
    {
      setopt( CURLOPT_URL , url.c_str() );
    }

    void setopt_ftp_create_missing_dirs( bool value )
    {
      setopt( CURLOPT_FTP_CREATE_MISSING_DIRS , value ? CURLFTP_CREATE_DIR_RETRY : 0 );
    }

    int progress(double dltotal, double dlnow, double ultotal, double ulnow)
    {
      // TODO: set up a progress_delegate class, and call it if one is connected.
      std::cout << "Progress: dltotal:" << dltotal << " dlnow:" << dlnow << " ultotal:" << ultotal << " ulnow:" << ulnow << std::endl;
    }

  private:

    static int progress_callback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
    {
      curl_easy* handler = reinterpret_cast< curl_easy* >( clientp );
      handler->progress( dltotal , dlnow , ultotal, ulnow );
    }

    static CURL* allocate_handle( )
    {
      CURL* result = curl_easy_init();
      if ( !result )
	throw std::runtime_error( "curl_easy_init failed." );
      return result;
    }

    static void deallocate_handle( CURL* handle )
    {
      if ( handle )
	{
	  curl_easy_cleanup( handle );
	}
    }
  private:
    CURL* handle_;
  };
}

#endif
