#ifndef leitor_h
#define leitor_h
#include <stdint.h>
#include <inttypes.h>

#define CONSTANT_METHODREF 10

/*Estruturas utilizadas*/

/*Estrutura do constant pool
  Tipo define o tag do elemento
  O ponteiro para void receberá a estrutura definida pelo tag*/
typedef struct const_pool_struct{
    uint8_t tipo;
    void *ptr;
}CONSTANT_POOL;

/*Estrutura do methodref*/
typedef struct method_ref_struct{
    uint8_t tag;
    uint8_t class_index[2];
    uint8_t name_and_type_index[2];
}METHOD_REF;

/*Protótipos das funções*/

uint8_t* ler_magic(uint8_t *buffer);

uint8_t* ler_minor_version(uint8_t *buffer);

uint8_t* ler_major_version(uint8_t *buffer);

uint8_t* ler_const_pool_count(uint8_t *buffer);

int const_pool_count_toInt(uint8_t *const_pool_count);

void ler_const_pool(uint8_t *buffer, uint8_t *const_pool_count, CONSTANT_POOL *const_pool);

void imprimir_var(uint8_t *var, int tamanho);

#endif
