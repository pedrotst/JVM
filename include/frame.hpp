#ifndef FRAME_H
#define FRAME_H

#include <vector>
#include <cstdint>
#include "../include/heap.hpp"

//////////////////////////// Estruturas ////////////////////////////
/** \class Operand_Type
 * \brief Os tipos float e double não estão presentes porque não vamos dar suporte a
 * ponto flutuante.
 * Falta definir os tipos reference e returnAddress.
*/
typedef union operand_value_u {
	bool boolean_value;
	uint8_t byte_value;
	uint8_t char_value;
	int16_t short_value;
	int32_t int_value;
	int64_t long_value;
	InstanceClass*   reference_value;
	//returnAddress        returnAddress_value;
}Operand_Type;

typedef struct operand_s {
	tag_Tipo tag;
	Operand_Type value;
}Operand;

/** \class local_var_value
 *  \var A diferença entre os operandos e as variáveis locais é que as variáveis locais
 *       não podem receber long ou double. Para salvar um long ou um double são necessárias
 *       duas variáveis locais.
 */
typedef union local_var_value_u {
	bool boolean_value;
	uint8_t byte_value;
	uint8_t char_value;
	int16_t short_value;
	int32_t int_value;
	InstanceClass*   reference_value;
	//returnAddress        returnAddress_value;
} Local_var_value;

typedef struct local_var_s {
	uint8_t tag;
	Local_var_value value;
}Local_var;

typedef std::vector<Operand> op_stack;
typedef std::vector<Local_var> local_var_vector;

//////////////////////////// Class ////////////////////////////
class Frame{
public:
      /** Pilha de operandos.
      * A pilha de operandos começa vazia. Ela é populada ao longo da execução
      * das instruções.
      */
      op_stack operandStack;
      /** Vetor de variáveis locais. */
      local_var_vector localVarVector;
      uint8_t pc;
      /** referencia pra constant pool */
      ClassFile *cf;

      /** \var method_index
       *  \brief esta será a variável que identifica qual método da cf estamos rodando
       */
      int method_index;

      Frame(){} //Depois esse Construtor deve ser deletado
      Frame(int method_index, ClassFile *cf);
};

#endif // JAVASTACK_FRAME_HPP_INCLUDED
