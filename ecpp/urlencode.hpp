#ifndef hD73FFD4F_63B5_444F_9B44_F6EB8A41EB1C
#define hD73FFD4F_63B5_444F_9B44_F6EB8A41EB1C

#include <string>

namespace ecpp
{
  // transforms source by encoding any characters not in the regex [a-zA-Z0-9_\-]
  std::string urlencode( std::string const& source );
}

#endif
