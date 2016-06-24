#ifndef HEAP
#define HEAP

#include <map>
#include <vector>
#include "../include/classFile.hpp"

struct instance_class_u;

typedef union type_s{
    bool            boleano;
    int32_t         inteiro;
    char*           palavra;
    char            caractere;
    uint8_t         byte;
    int64_t         longo;
    uint32_t        pFlutuante;
    int16_t         curto;
    uint64_t        duplo;
    struct instance_class_u*  instancia;
    //std::vector<union type_s> lista;
}field_type;

typedef enum tag_tipo_e{
    BOOL = 0,
    INT,
    CHAR,
    PALAVRA,
    BYTE,
    LONGO,
    PFLUTUANTE,
    CURTO,
    DUPLO,
    INSTANCIA,
    LISTA
}tag_tipo;

typedef struct field_value_s{
    uint8_t tag;
    field_type val;
}field_value;

typedef struct instance_class_u {
    ClassFile                       *cf;
    std::map<std::string, field_value>  field_instances;
}InstanceClass;

// Os tipos float e double não estão presentes porque não vamos dar suporte a
// ponto flutuante.
// Falta definir os tipos reference e returnAddress.
typedef union operand_u {
    bool             boolean_type;
    uint8_t          byte_type;
    uint8_t          char_type;
    int16_t          short_type;
    int32_t          int_type;
    int64_t          long_type;
    InstanceClass*   reference_type;
    //returnAddress        returnAddress_type;
}operand_type;

typedef struct operand_value_s{
    uint8_t tag;
    operand_type op;
}operand_value;



// A diferença entre os operandos e as variáveis locais é que as variáveis locais
// não podem receber long ou double. Para salvar um long ou um double são necessárias
// duas variáveis locais.
typedef union local_var_u {
    bool             boolean_type;
    uint8_t          byte_type;
    uint8_t          char_type;
    int16_t          short_type;
    int32_t          int_type;
    InstanceClass*   reference_type;
    //returnAddress        returnAddress_type;
} local_var;



#endif // HEAP
