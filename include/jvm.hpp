#ifndef _JVM_HPP
#define _JVM_HPP

#include <iostream>
#include "../include/leitor.hpp"
#include "../include/exibidor.hpp"
#include "../include/frame.hpp"
#include "../include/interpretador.hpp"
#include "../include/opcode.hpp"
#include "../include/exibidor.hpp"
#include "../include/op_instrucs.hpp"



// Os tipos float e double não estão presentes porque não vamos dar suporte a
// ponto flutuante.
//
// Falta definir os tipos reference e returnAddress.
typedef union operand_u {
    bool             boolean_type;
    uint8_t          byte_type;
    uint8_t          char_type;
    int16_t          short_type;
    int32_t          int_type;
    int64_t          long_type;
    void             *reference_type;
    //returnAddress        returnAddress_type;
} operand;

// A diferença entre os operandos e as variáveis locais é que as variáveis locais
// não podem receber long ou double. Para salvar um long ou um double são necessárias
// duas variáveis locais.
typedef union local_var_u {
    bool             boolean_type;
    uint8_t          byte_type;
    uint8_t          char_type;
    int16_t          short_type;
    int32_t          int_type;
    //reference        reference_type;
    //returnAddress        returnAddress_type;
} local_var;

class Jvm{
    private:
        std::vector<Frame> jStack;
        std::vector<ClassFile> loadedClasses;
    public:
        //Construtor
        Jvm();

        // Descrição:
        //    Procura o método main em uma classe.
        //
        // Parâmetros:
        //    ClassFile *classF_pt: Um ponteiro para uma classe carregada.
        //
        // Retorno:
        //    Se a main for encontrada, retorna um ponteiro para sua method_info.
        //    A mesma method_info que está dentro da constant_pool.
        //
        //    Se a main não for encontrada, retorna NULL.
        //
        int findMain (ClassFile *classF_pt);

        // Descrição:
        //    Resolve uma referência para um nome presente na constant_pool.
        //
        // Parâmetros:
        //    ClassFile *classF_pt: Um ponteiro para uma classe carregada.
        //
        //    int name_index: Um index da constant_pool.
        //
        // Retorno:
        //    Se o index apontar para uma string, retorna a string.
        //
        //    Se o index não apontar para uma string, retorna NULL.
        //
        char* getName(ClassFile *classF_pt, int name_index);

        // Em andamento
        //
        // Cria o frame
        int execMethod(int main_index, ClassFile classF);
        bool isCode(attribute_info attr);


        // Em andamento
        //
        // Executa as instruções.
        // interpretador
        //execCode();

        // Descrição:
        //    Executa a jvm em si.
        //    Utiliza grande parte das funções declaradas acima.
        //
        //    Etapas:
        //          * Procura a main.
        //          * Se houver main, começa a executar.
        //
        // Parâmetros:
        //    *const char arq_class_name: nome do arquivo .class a ser executado.
        //
        //
        int run(const char* arq_class_name);
};

#endif // _JVM_HPP
