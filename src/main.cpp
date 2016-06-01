#include <stdlib.h>
#include <stdio.h>
#include "Leitor.h"

int main(int argc, char **argv){
FILE *arq_class = NULL;
CONSTANT_POOL *const_pool_array = NULL;
uint8_t *buffer = NULL, *magic_number = NULL, *minor_version = NULL, *major_version = NULL, *const_pool_count = NULL;
long int lSize;

    arq_class = fopen(argv[1], "rb");
    if(!arq_class){
        printf("Erro ao ler arquivo .class: %s", argv[1]);
        exit(EXIT_FAILURE);
    }

     /*Verifica o tamanho do arquivo*/
    fseek(arq_class, 0, SEEK_END);
    if((lSize = ftell(arq_class)) <= 0){
        printf("Estouro de tamanho maximo de arquivo!\n");
    }
    rewind(arq_class);

    /*Aloca o buffer de entrada*/
    if(!(buffer = (uint8_t*)malloc(lSize*sizeof(uint8_t)))){
        printf("Erro ao alocar buffer de leitura!\n");
        return(EXIT_FAILURE);
    }

    /*Realiza a leitura bufferizada do arquivo de entrada*/
    if(fread(buffer, sizeof(uint8_t), lSize, arq_class) != lSize){
        printf("Erro na leitura do arquivo de entrada\n");
        return(EXIT_FAILURE);
    }

    magic_number = ler_magic(buffer);
    minor_version = ler_minor_version(buffer);
    major_version = ler_major_version(buffer);
    const_pool_count = ler_const_pool_count(buffer);
    ler_const_pool(buffer, const_pool_count, const_pool_array);
    printf("Magic: ");
    imprimir_var(magic_number, 4);
    printf("\nMinor version: ");
    imprimir_var(minor_version, 2);
    printf("\nMajor version: ");
    imprimir_var(major_version, 2);
    printf("\nConstant pool count: ");
    imprimir_var(const_pool_count, 2);
    return EXIT_SUCCESS;
}
