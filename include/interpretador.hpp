#ifndef INTERPRETADOR_HPP_INCLUDED
#define INTERPRETADOR_HPP_INCLUDED

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define numOpcodes 1

//inicializador do interpretador
int (**initInterpreter(void))(uint8_t*);

//uma das funções do interpretador
int iadd(uint8_t*);

#endif // INTERPRETADOR_HPP_INCLUDED
