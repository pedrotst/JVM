#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

#include <cstdint>
//#include <string>
#include <stdio.h>
#include <stdlib.h>

#define numOpcodes 250
#include "../include/frame.hpp"
#include "../include/opcode.hpp"
#include "../include/jvm.hpp"
#include "../include/structs.hpp"
#include "../include/classFile.hpp"

// Somente uma declaraÃ§Ã£o, para poder compilar.
class Jvm;
<<<<<<< HEAD

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
        std::vector<instructionFunction> instructions;//instruÃ§Ãµes
        Frame *frame_corrente;
        Code_attribute *code_corrente;
        uint16_t descriptor_index;
=======
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
>>>>>>> 4ae5775c31374efc6b2deface7b50b2bf9f61355


        /** \fn interpretador execute_instruction (std::string className)
         *
         * \brief Executa a instruÃ§Ã£o de acordo com o opcode de entrada.
         *  para encontrar a funcao correta eh montado o vetor ponteiro
         * para funcoes, os quais seguem a ordem dos opcode
         *
         * \param opcode da funcao a ser executada
         *
         * \return a quantidade de bytes utilizados pela instrucao executada
         * este numero deve ser utilizado para incremento do pc
         */
        int execute_instruction(int opcode);

        //uma das funï¿½ï¿½es do interpretador
        //		void iadd(op_stack *opStack);
        //		int iadd_pusher(char *codeAligned, op_stack *opStack);
        //		void ladd(op_stack *opStack);
        int iadd();
		int ladd();

		int iload();
		int lload();
		int fload();
		int dload();
        int aload();

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
#endif // INTERPRETADOR_H
