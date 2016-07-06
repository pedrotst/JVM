#ifndef __dbg_h__
#define __dbg_h__

#include<iostream>

#ifdef DEBUG

#define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0)

#else
#define DEBUG_PRINT(message)
#endif


#endif
