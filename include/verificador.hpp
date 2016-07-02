#ifndef VERIFICADOR_HPP_INCLUDED
#define VERIFICADOR_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string>
#include <cstring>

#include "../include/structs.hpp"
#include "../include/classFile.hpp"
#include "../include/attributes.hpp"
#include "../include/little_to_big.hpp"
#include "../include/read_bytes.hpp"
#include "../include/read_attributes.hpp"
#include "../include/read_methods.hpp"

/** \fn verificaClass (ClassFile classF)
*
* \brief Verifica se a class file está consistente realizando checagem de tipo
*
* \param classF estrutura class file a ser checada
*
* \return void
*/
void verificaClass(ClassFile classF);

/** \fn verificaMethods (ClassFile classF)
*
* \brief Verifica as instruções dos métodos
*
* \param classF estrutura class file que contém os métodos a serem checados
*
* \return void
*/
void verificaMethods(ClassFile classF);
#endif // VERIFICADOR_HPP_INCLUDED
