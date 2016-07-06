#ifndef FRAME_H
#define FRAME_H

#include <vector>
#include <cstdint>
#include <sstream>
#include <iostream>
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
	//reference_type pode ser: class type(InstanceClass*), array type (ArrayType*) ou interface type
	InstanceClass*   reference_value; 	//objectType
	ArrayType* 		arrayref;			//arrayType
	std::string *string_value;
	//InterfaceType interfaceref;		//?
	bool  void_v;
	uint64_t        returnAddress_value;
	uint32_t float_value;
	uint32_t double_value;
}Local_var_Type;

class Local_var{
public:
    tag_Tipo tag;
	Local_var_Type value;
    std::string repr();

};

//////////////////////////// Class ////////////////////////////
class Frame{
public:
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
	uint64_t pc;


      /** referencia pra constant pool */
      ClassFile *cf;

      /** \var method_index
       *  \brief esta será a variável que identifica qual método da cf estamos rodando
       */
      int method_index;

      Frame(int method_index, ClassFile *cf);
      void printOperandStack();
	  void printLocalVar();
};

#endif // JAVASTACK_FRAME_HPP_INCLUDED
