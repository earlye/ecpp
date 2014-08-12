#ifndef hDEE79673_0DDE_4BAF_88FE_35E78D2102D4
#define hDEE79673_0DDE_4BAF_88FE_35E78D2102D4

namespace ecpp
{
  template< typename string_type , typename const_iterator >
  string_type collapse( string_type separator , const_iterator begin , const_iterator end )
  {
    string_type delimiter;
    string_type result;
    for( ; begin != end ; ++begin )
      {
	result += delimiter;
	result += *begin;
	delimiter = separator;
      }
    return result;
  }

  template< typename string_type , typename container_type >
  string_type collapse( string_type separator , container_type const & container )
  {
    return collapse<string_type>(separator,container.begin(),container.end());
  }
}

#endif
