#ifndef HEAP_HPP_INCLUDED
#define HEAP_HPP_INCLUDED

union type_s{
    int32_t inteiro;
    char* palavra;
    char caractere;
    uint8_t byte;//byte e boolean e null
    int64_t longo;
    uint32_t pFlutuante;
    int16_t curto;
    uint64_t duplo;
}type;

typedef enum tag_tupo_e{
    INT = 0,
    CHAR,
    PALAVRA,
    BYTE,
    LONGO,
    PFLUTUANTE,
    CURTO,
    DUPLO;
}tag_tipo;

typedef struct field_value_s{
    uint8_t tag;
    union type;
}value;


#endif // HEAP_HPP_INCLUDED
