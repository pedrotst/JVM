#ifndef _EXIBIDOR
#define _EXIBIDOR

#include <math.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdint.h>

#include "../include/structs.hpp"
#include "../include/print_code.hpp"
#include "../include/classFile.hpp"
#include "../include/op_instrucs.hpp"
#include "../include/operationMap.hpp"

/** \file exibidor.hpp
*   \brief responsavel pela exibicao textual do .class
*/

void exibeClass(ClassFile classF);
void print_comment(std::vector<cp_info_s> c, int n);



#endif // _EXIBIDOR
