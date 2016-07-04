#ifndef FRAME_H
#define FRAME_H

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

typedef struct local_var_s {
    tag_Tipo tag;
	Local_var_Type value;
}Local_var;

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
      uint8_t pc;


      /** referencia pra constant pool */
      ClassFile *cf;

      /** \var method_index
       *  \brief esta será a variável que identifica qual método da cf estamos rodando
       */
      int method_index;

      Frame(int method_index, ClassFile *cf);
};

#endif // JAVASTACK_FRAME_HPP_INCLUDED
