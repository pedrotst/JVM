#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

#include <cstdint>
#include <stdio.h>
#include <stdlib.h>

#define numOpcodes 250
#include "../include/frame.hpp"
#include "../include/opcode.hpp"
#include "../include/jvm.hpp"
#include "../include/structs.hpp"

// Somente uma declaração, para poder compilar.
class Jvm;

class Interpretador{
	public:
		Interpretador(/*Jvm *jvm*/);
		//void execute_instruction(int opcode, op_stack *opStack);
		//int push_operands(uint8_t opcode, char* codeAligned, op_stack *opStack);
        int runCode(uint16_t descriptor_index, Code_attribute *code_attr_pt, Frame *frame_pt);
	private:
		Jvm *jvm;
		//typedef void (Interpretador::*instructionFunction)(op_stack*);
		typedef int (Interpretador::*instructionFunction)();
		std::vector<instructionFunction> instructions;//instruções
		Frame *frame_corrente;
		Code_attribute *code_corrente;
		uint16_t descriptor_index;
        /** \fn interpretador execute_instruction (std::string className)
         *
         * \brief Executa a instrução de acordo com o opcode de entrada.
         *  para encontrar a funcao correta eh montado o vetor ponteiro
         * para funcoes, os quais seguem a ordem dos opcode
         *
         * \param opcode da funcao a ser executada
         *
         * \return a quantidade de bytes utilizados pela instrucao executada
         * este numero deve ser utilizado para incremento do pc
         */
		int execute_instruction(int opcode);
		//uma das fun��es do interpretador
//		void iadd(op_stack *opStack);
//		int iadd_pusher(char *codeAligned, op_stack *opStack);
//		void ladd(op_stack *opStack);
//		void new_op(op_stack *opStack);
//		int new_op_pusher(char* codeAligned, op_stack *opStack);
        int iadd();
		int ladd();
		int new_op();
		int dup();
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
