#ifndef HEAP
#define HEAP

#include <map>
#include <vector>
#include <string>
#include "../include/classFile.hpp"

struct FieldValue_s;

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
}tag_tipo;

typedef enum tag_FieldType_e{
    BASETYPE = 0,
    OBJECTTYPE,
    ARRAYTYPE
}tag_FieldType;

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
    tag_tipo    tag;
    BaseType_u  val;
}BaseType;

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
    tag_FieldType tag;
    FieldType val;
}FieldValue;

typedef struct instance_class_s {
    ClassFile                       *cf;
    /** field_instances
     * \brief a instancia basicamente mapeia o nome da field para seu valor 
     */
    std::map<std::string, FieldValue>  field_instances;
}InstanceClass;

#endif // HEAP
