#ifndef HEAP
#define HEAP
/** \file heap.hpp
* \brief Este arquivo trata a documentacaoo 4.3.2
* https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html#jvms-4.3
*/
#include <map>
#include <vector>
#include <string>
#include "../include/classFile.hpp"

class FieldValue;
class InstanceClass;

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
    VOID_T = 11,
    RETURN_ADDRESS = 12,
    STRINGTYPE = 13
}tag_Tipo;

typedef union base_type_s{
    uint8_t         byte;
    char            caractere;
    double        duplo;
    float        pFlutuante;
    int32_t         inteiro;
    int64_t         longo;
    int16_t         curto;
    bool            boleano;
    std::string     *stringue;
}BaseType_u;

typedef struct BaseType_s{
    tag_Tipo    tag;
    BaseType_u  val;
}BaseType;


typedef struct ObjectType_s{
    InstanceClass *instance;
}ObjectType;

typedef std::vector<FieldValue> arrayref;

typedef struct ArrayType_s{
     arrayref *arr;
}ArrayType;

typedef union FieldType_u{
    BaseType btype;
    ObjectType objtype;
    ArrayType  arrtype;
}FieldType;

/** \class FieldValue
* \brief Valor empacotado da representacao de uma classe
* ela pode ser dos tipos BaseType, ObjectType e ArrayType
* para mais informacoes visite https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html#jvms-4.5
*/
class FieldValue{
    public:
    tag_Tipo  tag;
    FieldType val;

    std::string repr();
};

/** \class InstanceClass
* \brief Esta classe eh a instancia fisica de um objeto
* para isto ela o valor de todos fields dentro de si
* e um ponteiro para sua classfile para facilitar a manipualacao das referencias
*/
class InstanceClass {
public:
    ClassFile  *cf;

    /** \var field_instances
     * \brief a instancia basicamente mapeia o nome da field para seu valor
     */
    std::map<std::string, FieldValue>  field_instances;

    void printInstancia();
};

#endif // HEAP
