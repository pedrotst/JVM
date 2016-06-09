#ifndef INTERPRETADOR_HPP_INCLUDED
#define INTERPRETADOR_HPP_INCLUDED

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/javaStack_frame.hpp"
#define numOpcodes 1

typedef void (*instructionFunction)(jStackFrame&);

//inicializador do interpretador
std::vector<instructionFunction> init_interpreter ();

//uma das funções do interpretador
void iadd(jStackFrame &jStack);

#endif // INTERPRETADOR_HPP_INCLUDED
