#ifndef HEAP
#define HEAP
/** \file heap.hpp
* Este arquivo trata a documentação 4.3.2
*/
#include <map>
#include <vector>
#include <string>
#include "../include/classFile.hpp"

struct FieldValue_s;

typedef enum tag_tipo_e{
    BOOL = 0,
    INT,
    CHAR,
    BYTE,
    LONGO,
    PFLUTUANTE,
    CURTO,
    DUPLO,
    BASETYPE,
    OBJECTTYPE,
    ARRAYTYPE
}tag_Tipo;

typedef union base_type_s{
    uint8_t         byte;
    char            caractere;
    uint64_t        duplo;
    uint32_t        pFlutuante;
    int32_t         inteiro;
    int64_t         longo;
    int16_t         curto;
    bool            boleano;
}BaseType_u;

typedef struct BaseType_s{
    tag_Tipo    tag;
    BaseType_u  val;
}BaseType;

/**
 * Não esquecer que este classname é o nome completo
*/
typedef struct ObjectType_s{
    char *className;
}ObjectType;

typedef struct ArrayType_s{
    std::vector<struct FieldValue_s> *field;
}ArrayType;

typedef union FieldType_u{
    BaseType btype;
    ObjectType objtype;
    ArrayType  arrtype;
}FieldType;

typedef struct FieldValue_s{
    tag_Tipo  tag;
    FieldType val;
}FieldValue;

//testando
typedef std::vector<FieldValue> Fields_Values;
/** \class InstanceClass
* Esta struct representa o mapeamento entre a instância de uma classe e a referência
* para esta no vetor de classes carregadas.
*/
typedef struct instance_class_s {
    ClassFile  *cf;
    /** \var field_instances
     * \brief a instancia basicamente mapeia o nome da field para seu valor
     */
    //std::map<std::string, FieldValue>  field_instances;
    //std::vector<FieldValue>  field_instances;
    Fields_Values  *field_instances;
}InstanceClass;

#endif // HEAP
