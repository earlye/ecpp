#include <iostream>
#include <ecpp/getenv.hpp>

int main( int argc , char** argv )
{
  std::string test = ecpp::getenv( "HOME" );
  std::cout << test << std::endl;
}
