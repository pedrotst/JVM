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

#endif // HEAP
