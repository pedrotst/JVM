#ifndef __dbg_h__
#define __dbg_h__

#include<iostream>

#ifdef DEBUG
//se estiver definido debug, imprime os trecos
#define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0);
#define DEBUG_ONLY(x) do{x;}while(0);

#else
//caso contrario, recebe argumentos mas faz nada
#define DEBUG_PRINT(message)
#define DEBUG_ONLY(x) //do{;}while(0)

#endif


#endif
