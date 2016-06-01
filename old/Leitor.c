#include <stdio.h>
#include <stdlib.h>
#include "Leitor.h"

/*Função realiza a leitura do magic number e retorna o valor lido*/
uint8_t* ler_magic(uint8_t *buffer){
int i, j;
uint8_t *magic = NULL;

    magic = (uint8_t*)malloc(4*sizeof(uint8_t));
    if(!magic){
        printf("Erro ao alocar magic number!\n");
        exit(EXIT_FAILURE);
    }

    for(i = 0, j = 0; i < 4 && j < 4; i++, j++){
        magic[j] = buffer[i];
    }

    return magic;
}

/*Função realiza a leitura do minor version e retorna o valor lido*/
uint8_t* ler_minor_version(uint8_t *buffer){
int i, j;
uint8_t *minor = NULL;

    minor = (uint8_t*)malloc(2*sizeof(uint8_t));
    if(!minor){
        printf("Erro ao alocar minor version!\n");
        exit(EXIT_FAILURE);
    }

    for(i = 4, j = 0; i < 6 && j < 2; i++, j++){
        minor[j] = buffer[i];
    }

    return minor;
}

/*Função realiza a leitura do major version e retorna o valor lido*/
uint8_t* ler_major_version(uint8_t *buffer){
int i, j;
uint8_t *major = NULL;

    major = (uint8_t*)malloc(2*sizeof(uint8_t));
    if(!major){
        printf("Erro ao alocar major version!\n");
        exit(EXIT_FAILURE);
    }

    for(i = 6, j = 0; i < 8 && j < 2; i++, j++){
        major[j] = buffer[i];
    }

    return major;
}

/*Função realiza a leitura do constant pool count e retorna o valor lido*/
uint8_t* ler_const_pool_count(uint8_t *buffer){
int i, j;
uint8_t *const_pool_count = NULL;

    const_pool_count = (uint8_t*)malloc(2*sizeof(uint8_t));
    if(!const_pool_count){
        printf("Erro ao alocar major version!\n");
        exit(EXIT_FAILURE);
    }

    for(i = 8, j = 0; i < 10 && j < 2; i++, j++){
        const_pool_count[j] = buffer[i];
    }

    return const_pool_count;
}

/*Função converte o pool count para inteiro*/
int const_pool_count_toInt(uint8_t *const_pool_count){
int result = 0;
    result = const_pool_count[0] << 8 | const_pool_count[1];
    //printf("result: %X\n", result);
    return result;
}

/*Função realiza leitura do constant pool do arquivo .class e preenche a estrutura CONSTANT_POOL*/
void ler_const_pool(uint8_t *buffer, uint8_t *const_pool_count, CONSTANT_POOL *const_pool){
int i, j = 10;

    /*Aloca a estrutra do constant pool*/
    const_pool = malloc(const_pool_count_toInt(const_pool_count)*sizeof(CONSTANT_POOL));

    /*Enquanto não preencher toda a estrutura*/
    for(i = 1; i < const_pool_count_toInt(const_pool_count); i++){
        switch(buffer[j]){
            /*Caso o tag for Methodref*/
            case(CONSTANT_METHODREF):
                const_pool[i].tipo = buffer[j]; //O tipo recebe 10 (valor de methodref)
                const_pool[i].ptr = malloc(sizeof(METHOD_REF)); //Aloca espaço para a estrutra de methodref
                ((METHOD_REF *)(const_pool[i].ptr))->tag = buffer[j++]; //O tag é 10 (valor de methodref)
                printf("Tag: %X\n", ((METHOD_REF *)(const_pool[i].ptr))->tag);
                ((METHOD_REF *)(const_pool[i].ptr))->class_index[0] = buffer[j++]; //Recebe o primeiro byte do valor de class index
                ((METHOD_REF *)(const_pool[i].ptr))->class_index[1] = buffer[j++]; //Recebe o segundo byte do valor de class index
                printf("Class Index: %X%X\n", ((METHOD_REF *)(const_pool[i].ptr))->class_index[0], ((METHOD_REF *)(const_pool[i].ptr))->class_index[1]);
                ((METHOD_REF *)(const_pool[i].ptr))->name_and_type_index[0] = buffer[j++]; //Recebe o primeiro byte do valor de name and type index
                ((METHOD_REF *)(const_pool[i].ptr))->name_and_type_index[1] = buffer[j++]; //Recebe o segundo byte do valor de name and type index
                break;
        }
    }
}

/*Função imprime o valor da variável*/
void imprimir_var(uint8_t *var, int tamanho){
int i;
    for(i = 0; i < tamanho; i++){
        printf("%X", var[i]);
    }
    return;
}
