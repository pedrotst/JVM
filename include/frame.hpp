#ifndef FRAME_H
#define FRAME_H

#include <vector>
#include <cstdint>
#include "../include/heap.hpp"

//////////////////////////// Estruturas ////////////////////////////
// Os tipos float e double não estão presentes porque não vamos dar suporte a
// ponto flutuante.
// Falta definir os tipos reference e returnAddress.
typedef union operand_value_u {
	bool boolean_value;
	uint8_t byte_value;
	uint8_t char_value;
	int16_t short_value;
	int32_t int_value;
	int64_t long_value;
	InstanceClass*   reference_value;
	//returnAddress        returnAddress_value;
}operand_value;

typedef struct operand_s {
	uint8_t tag;
	operand_value value;
}operand;

// A diferença entre os operandos e as variáveis locais é que as variáveis locais
// não podem receber long ou double. Para salvar um long ou um double são necessárias
// duas variáveis locais.
typedef union local_var_value_u {
	bool boolean_value;
	uint8_t byte_value;
	uint8_t char_value;
	int16_t short_value;
	int32_t int_value;
	InstanceClass*   reference_value;
	//returnAddress        returnAddress_value;
} local_var_value;

typedef struct local_var_s {
	uint8_t tag;
	local_var_value value;
}local_var;

typedef std::vector<operand> op_stack;
typedef std::vector<local_var> local_var_vector;

//////////////////////////// Class ////////////////////////////
class Frame{
public:
      int max_stack, max_locals;
      // Pilha de operandos.
    // A pilha de operandos começa vazia. Ela é populada ao longo da execução
	// das instruções.
	op_stack operandStack;
	// Vetor de variáveis locais.
	local_var_vector localVarVector;
      // pc
      uint8_t pc;
      // referencia pra constant pool
      std::vector<cp_info> *constant_pool_pt;

      Frame(){} //Depois esse Construtor deve ser deletado

      Frame(int max_stack, int max_locals, uint16_t descriptor_index, std::vector<cp_info> *constant_pool_pt);
};

#endif // JAVASTACK_FRAME_HPP_INCLUDED
