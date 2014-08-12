#ifndef hF70D7A32_1286_4EEE_8985_D6B917D9E2D1
#define hF70D7A32_1286_4EEE_8985_D6B917D9E2D1

/*
This module is intended to handle all of the ifdef crap necessary to
figure out which header to include to get the usual socket api
support.
*/

#if defined( WINDOWS ) || defined( _WIN32 )
#include <winsock2.h>
#else
#include <arpa/inet.h>
#endif

#endif
