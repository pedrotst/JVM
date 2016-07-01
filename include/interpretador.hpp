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
#include "../include/classFile.hpp"

// Somente uma declaração, para poder compilar.
class Jvm;

class Interpretador{
    public:
        Interpretador(Jvm *jvm);

        /** \fn runcode
         *
         *  \param ponteiro para o frame sendo executado
         */
        int runCode(Frame *frame_pt);
    private:
        Jvm *jvm;

        /** \var *cf
         *  \brief Decidimos que o interpretador tem acesso ao classfile inteiro
         */
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
        void new_op(op_stack *opStack);
        int iadd();
		int ladd();
		int new_op();
		int dup();
		int ldc();
		int invokespecial();
};
#endif // INTERPRETADOR_H
