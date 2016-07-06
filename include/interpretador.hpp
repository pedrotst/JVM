#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

#include <cstdint>
//#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define numOpcodes 250
#include "../include/frame.hpp"
#include "../include/opcode.hpp"
#include "../include/jvm.hpp"
#include "../include/structs.hpp"
#include "../include/classFile.hpp"
#include "../include/operationMap.hpp"

/** \file interpretador.hpp
*   \brief Estruturas de interpretacao dos opcodes
*/

class Jvm;

/** \class Interpretador
*   \brief Responsavel por receber um frame e rodar as instrucoes contidas ali
*/
class Interpretador{
    public:
        /** \fn Interpretador
        *   \param Jvm Recebe a jvm que esta sendo executada como argumento
        *   para poder ter acesso as estruturas de runtime, tais como
        *   vetor de classes alocadas, heap, heapstatica, etc
        */
        Interpretador(Jvm *jvm);

        /** \fn runcode
         *  \brief esta eh a funcao chave que sera chamada pela jvm
         *  \param *frame_pt ponteiro para o frame sendo executado
         *
         */
        int runCode(Frame *frame_pt);
    private:
        /**   \var *jvm Recebe a jvm que esta sendo executada como argumento
        *       para poder ter acesso as estruturas de runtime, tais como
        *    vetor de classes alocadas, heap, heapstatica, etc
        */
        Jvm *jvm;

        typedef int (Interpretador::*instructionFunction)();
        /** \var instructions
         *  \brief Vetor com todas funcoes implementadas, elas estao alinhadas pelo seu opcode
         * no entanto devem ser chamadas pela \ref execute_instruction
         *
         */
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
        //
        //
        //
        int nop();
        int aconst_null();

        int iconst_0();
		int iconst_1();
		int iconst_2();
		int iconst_3();
		int iconst_4();
		int iconst_5();

        int lconst_0();
        int lconst_1();

        //int fconst_0();
        //int fconst_1();
        //int fconst_2();

        //int dconst_0();
        //int dconst_1();

        int bipush();
        int sipush();

        int ldc();
        int ldc_w();
        int ldc2_w();

        int getstatic();
        int getfield();

        int putstatic();

        int iload();
		int lload();
		int fload();
		int dload();
        int aload();

        int iload_0();
        int iload_1();
        int iload_2();
        int iload_3();

        int lload_0();
        int lload_1();
        int lload_2();
        int lload_3();

        int fload_0();
        int fload_1();
        int fload_2();
        int fload_3();

        int dload_0();
        int dload_1();
        int dload_2();
        int dload_3();

        int aload_0();
		int aload_1();
		int aload_2();
		int aload_3();

		int iaload();
		int laload();
		int faload();
		int daload();
		int aaload();
		int baload();
		int caload();
		int saload();

		int istore();
		int lstore();
		int fstore();
		int dstore();
		int astore();

        int istore_0();
		int istore_1();
		int istore_2();
		int istore_3();

		int lstore_0();
		int lstore_1();
		int lstore_2();
		int lstore_3();

		int fstore_0();
		int fstore_1();
		int fstore_2();
		int fstore_3();

		int dstore_0();
		int dstore_1();
		int dstore_2();
		int dstore_3();

		int astore_0();
		int astore_1();
		int astore_2();
		int astore_3();

		int iastore();
		int lastore();
		int fastore();
		int dastore();
		int aastore();
		int bastore();
		int castore();
		int sastore();

		int pop();
		int pop2();

		int dup();
		int dup_x1();
		int dup_x2();

		int dup2();
		int dup2_x1();
		int dup2_x2();

		int swap_op();

        int iadd();
		int ladd();
		int fadd();
		int dadd();

		int isub();
		int lsub();
		int fsub();
		int dsub();

		int imul();
		int lmul();
		int fmul();
		int dmul();

		int idiv();
		int ldiv();
        int fdiv();
        int ddiv();

        int irem();
        int lrem();
        int frem();
        int drem();

        int ineg();
        int lneg();
        int fneg();
        int dneg();

        int ishl();
        int lshl();

        int ishr();
        int lshr();

        int iushl();
        int lushl();

        int iand();
        int land();

        int ior();
        int lor();

        int ixor();
        int lxor();

        int iinc();

        int i2l();
        int i2f();
        int i2d();

        int l2i();
        int l2f();
        int l2d();

        int f2i();
        int f2l();
        int f2d();

        int d2i();
        int d2l();
        int d2f();

        int i2b();
        int i2c();
        int i2s();

        int lcmp();
        int fcmpl();
        int fcmpg();

        int dcmpl();
        int dcmpg();

        ////////////////////////// Conditional Branch //////////////////////////
        // Conditional branch: ifeq, ifne, iflt, ifle, ifgt, ifge, ifnull, ifnonnull,
        // if_icmpeq, if_icmpne, if_icmplt, if_icmple, if_icmpgt, if_icmpge, if_acmpeq, if_acmpne.
        int ifeq();
        int ifne();
        int iflt();
        int ifle();
        int ifgt();
        int ifge();
        int ifnull();
        int ifnonnull();
        int if_icmpeq();
        int if_icmpne();
        int if_icmplt();
        int if_icmple();
        int if_icmpgt();
        int if_icmpge();
        int if_acmpeq();
        int if_acmpne();

        ////////////////////////// Unconditional Branch //////////////////////////
        // Unconditional branch: goto, goto_w, jsr, jsr_w, ret.
        int goto_java();
        int goto_w();

        int jsr_w();
        int jsr();


		int anewarray();

		int ireturn();
		int return_op();
		int new_op();

		int newarray();

		int putfield();
		int iconst_m1();

		int invokespecial();
		int invokevirtual();
        int invokestatic();




        void valida_tipos_fields(Local_var ref_var, string field_type, string field_name);


      ///////////////////// Funções que acho (o Felipe)        /////////////////////
      ///////////////////// que não precisam ser implementadas /////////////////////
      // Essa pode até ser importante, mas acho que deve ficar por último.
      int athrow();
      // Relacionada a threads.
      int monitorenter();
      // Relacionada a threads.
      int monitorexit();




};
#endif // INTERPRETADOR_H
