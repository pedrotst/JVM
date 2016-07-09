#ifndef FRAME_H
#define FRAME_H

#include <vector>
#include <cstdint>
#include <sstream>
#include <iostream>
#include "../include/heap.hpp"
/** \file frame.hpp
 * \brief Define estruturas relacionados aos frames de execucao
*/
//////////////////////////// Estruturas ////////////////////////////
/** \class Local_var_Type
 * \brief O tipo void será utilizado para avisar que a função retorna nada
 * os tipos long e double utilizam duas posicoes na pilha
*/
typedef union Local_var_Type_u {
	bool boolean_value;
	uint8_t byte_value;
	uint8_t char_value;
	int16_t short_value;
	int32_t int_value;
	int32_t long_value;
	InstanceClass*   reference_value;
	//ArrayType* 		arrayref;
	arrayref *arr;
	std::string *string_value;
	bool  void_v;
	uint64_t        returnAddress_value;
	float float_value;
	uint32_t double_value;
}Local_var_Type;


/** \var Local_var
* \brief sao as variaveis utilizadas dentro do frame
* tanto pelo vetor de variaveis locais como pela pilha de operandos
*
*/
class Local_var{
public:
    tag_Tipo tag;
	Local_var_Type value;
	/** \fn repr
	* \return retorna a representacao de uma local_var em String
	*/
    std::string repr();

};

//////////////////////////// Class ////////////////////////////
class Frame{
public:
      /** \var operandStack
      * \brief Pilha de operandos.
      * A pilha de operandos começa vazia. Ela é populada ao longo da execução
      * das instruções.
      */
      std::vector<Local_var> operandStack;


      /** \var localVarVector
      * \brief Vetor de variáveis locais. */
      std::vector<Local_var> localVarVector;

    /** \var pc
      *\brief
     *  Código atual sendo executado
     */
	uint64_t pc;


      /** \var *cf
      * \brief referencia pra constant pool */
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
