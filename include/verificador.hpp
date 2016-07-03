#ifndef VERIFICADOR_HPP_INCLUDED
#define VERIFICADOR_HPP_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string>
#include <cstring>

#define NUMOPCODES 250
#include "../include/structs.hpp"
#include "../include/classFile.hpp"
#include "../include/attributes.hpp"
#include "../include/little_to_big.hpp"
#include "../include/read_bytes.hpp"
#include "../include/read_attributes.hpp"
#include "../include/read_methods.hpp"
#include "../include/opcode.hpp"

class Verificador{
    public:
        Verificador(ClassFile classF);

        /** \fn verificaClass (ClassFile classF)
        *
        * \brief Verifica se a class file está consistente realizando checagem de tipo
        *
        * \param classF estrutura class file a ser checada
        *
        * \return void
        */
        void verificaClass(ClassFile classF);
    private:

        typedef int (Verificador::*funcaoInstrucao)();
        std::vector<funcaoInstrucao> instrucoes;//instruções

        /** \fn verificaMethods (ClassFile classF)
        *
        * \brief Verifica as instruções dos métodos
        *
        * \param classF estrutura class file que contém os métodos a serem checados
        *
        * \return void
        */
        int verificaMethods(ClassFile classF);

        int iadd();
		int ladd();
		int return_op();
		int new_op();
		int aload_0();
		int aload_1();
		int aload_2();
		int aload_3();
		int putfield();
		int iconst_m1();
		int astore_0();
		int astore_1();
		int astore_2();
		int astore_3();
		int iconst_0();
		int iconst_1();
		int iconst_2();
		int iconst_3();
		int iconst_4();
		int iconst_5();
		int dup();
		int ldc();
		int invokespecial();

};



#endif // VERIFICADOR_HPP_INCLUDED
