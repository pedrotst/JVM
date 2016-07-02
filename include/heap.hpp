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
    INT = 1,
    CHAR = 2,
    BYTE = 3,
    LONGO = 4,
    PFLUTUANTE = 5,
    CURTO = 6,
    DUPLO = 7,
    BASETYPE = 8,
    OBJECTTYPE = 9,
    ARRAYTYPE = 10,
    VOID_T = 11
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

/** \class InstanceClass
* Esta struct representa o mapeamento entre a instância de uma classe e a referência
* para esta no vetor de classes carregadas.
*/
class InstanceClass {
    public:
    ClassFile  *cf;
    /** \var field_instances
     * \brief a instancia basicamente mapeia o nome da field para seu valor
     */
    std::map<std::string, FieldValue>  field_instances;
    //InstanceClass();
    //std::vector<FieldValue>  field_instances;
    //Fields_Values  *field_instances;
};

#endif // HEAP
