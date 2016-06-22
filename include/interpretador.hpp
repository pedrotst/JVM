#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define numOpcodes 250 //mudar pra 250
#include "../include/frame.hpp"
#include "../include/opcode.hpp"
#include "../include/jvm.hpp"
//void(*)(jStackFrame&) >> ponteiro a função que retorna void e pega a referencia do que for passado como entrada
//typedef utilizado para nomear o item descrito acima como instructionFunction

class Jvm;
//inicializador do interpretador
typedef std::vector<void*> Parametros;
//cada instrução sabe quais posições do vetor deve ler e como interpretar
//por exemplo
//parametros.push_back((void*) &heap);
//parametros.push_back((void*) &opStack);
typedef enum structs_s{
    OPSTACK = 0,
    CPOOL,
    HEAP
}Estruturas;

class Interpretador{
	public:
		Interpretador(Jvm *jvm);
		void execute_instruction(int opcode, std::vector<uint32_t> *opStack);

	private:
		Jvm *jvm;
		typedef void (Interpretador::*instructionFunction)(Parametros*);
		std::vector<instructionFunction> instructions;

		//uma das funções do interpretador
		void iadd(Parametros *param);
		void ladd(Parametros *param);
		void new_op(Parametros *param);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);
//int iadd(uint8_t*);

};
#endif // INTERPRETADOR_H
