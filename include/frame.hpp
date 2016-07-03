#ifndef FRAME_H
#define FRAME_H

<<<<<<< HEAD
#include <vector>
#include <cstdint>
#include "../include/heap.hpp"

//////////////////////////// Estruturas ////////////////////////////
/** \class Operand_Type
 * \brief Os tipos float e double não estão presentes porque não vamos dar suporte a
 * ponto flutuante.
 * O tipo void será utilizado para avisar que a função retorna nada
*/
typedef union Local_var_Type_u {
	bool boolean_value;
	uint8_t byte_value;
	uint8_t char_value;
	int16_t short_value;
	int32_t int_value;
	int32_t long_value;//longs usam dois local_var para cada operando
	//uint32_t long_value;//
	InstanceClass*   reference_value;
	bool  void_v;
	//returnAddress        returnAddress_value;
}Local_var_Type;
=======
#include<vector>
#include<cstdint>
#include "..\include\jvm.hpp"//para operand
>>>>>>> 4ae5775c31374efc6b2deface7b50b2bf9f61355

typedef struct local_var_s {
    tag_Tipo tag;
	Local_var_Type value;
}Local_var;

//////////////////////////// Class ////////////////////////////
class Frame{
public:
<<<<<<< HEAD
      /** Pilha de operandos.
      * A pilha de operandos começa vazia. Ela é populada ao longo da execução
      * das instruções.
      */
      std::vector<Local_var> operandStack;


      /** Vetor de variáveis locais. */
      std::vector<Local_var> localVarVector;

    /** \brief
     *  Código atual sendo executado
     */
      uint8_t pc;


      /** referencia pra constant pool */
      ClassFile *cf;

      /** \var method_index
       *  \brief esta será a variável que identifica qual método da cf estamos rodando
       */
      int method_index;

      Frame(){} //Depois esse Construtor deve ser deletado
      Frame(int method_index, ClassFile *cf);
=======
    //op_stack *opStack;//pilha de execuчуo interna ao frame
    std::vector<uint32_t> op_stack;

    //operandStack *opStack;
    std::vector<operand> operandStack;

    //Vetor de variaveis locais
    //localVarStack *localVar; //pilha de variaveis locais
    std::vector<local_var> localVarStack;
>>>>>>> 4ae5775c31374efc6b2deface7b50b2bf9f61355

    //Referência para a ConstantPool
    cp_info *cpReference;

    //Serve para ler o Code:
    int pc;
    int code_length;
    char *code;
    Frame();
};

#endif // JAVASTACK_FRAME_HPP_INCLUDED
