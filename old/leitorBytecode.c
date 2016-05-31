#include <stdio.h>
#include <stdint.h>

#include "ClassStructure.h"
#define ByteCode "Teste.class"

typedef enum AccessClass{
    ACC_PUBLIC       = 0x0001,
    ACC_FINAL        = 0x0010,
    ACC_SUPER        = 0x0020,
    ACC_INTERFACE    = 0x0200,
    ACC_ABSTRACT     = 0x0400,
    ACC_SYNTHETIC    = 0x1000,
    ACC_ANNOTATION   = 0x2000,
    ACC_ENUM         = 0x4000
}ACC_FLAGS;

int main(int argc, char** argv){
    FILE *arquivoJava;
    if( !(arquivoJava = fopen(ByteCode, "r"))){
        printf("Deu ruim ao abrir o .class\n");
        return 1;
    }
    pCLASS leituraClass;
    int charLido = 0;//TODO: mudar charLido para a struct
    printf("Magic Number: \n");
    uint32_t *byte = leituraClass.magicNumber;
    for(int i = 0; i<4; i++){
        fread(leituraClass.magicNumber+i, sizeof(uint8_t), 1, arquivoJava);
        printf("%02x ", *(leituraClass.magicNumber+i) );
    }
    printf("\n");

    /*
    O numero da versão é dividido em 4 bytes;
    Cada byte é referente a um numero:
    b1.b2.b3.b4
    b1 e b2 se referem a minor version
    b3 e b4 se referem a major version
    b4 contem o numero mais significativo da versao

    O mais correto seria fazer a leitura com um array de 4bytes
    */
    fread(&charLido, sizeof(uint8_t), 2, arquivoJava);
    printf("Versao: \nminor: %x\n", charLido);
    charLido = 0;

    fread(&charLido, sizeof(uint8_t), 2, arquivoJava);
    charLido>>=8;//charLido contem b3.b4: para pegar apenas b4, shifta 1 byte para direita
    printf("major: %x(hex) | %d(int)\n", charLido, charLido);

    /*
    Inicio da leitura do Constant Pool:
        Os 2 primeiros bytes do Constant Pool indica o numero de entradas (elementos) + 1;
        ex: Se tem 10 elementos, será 00 0a; 14 elementos, 00 0e; etc.
        Em esguida, cada elemento na é precedido por um tag de 1byte informando o tipo daquela posição.
        Cada tipo define a quantidade de bytes posterior.
    */

    fread(&charLido, sizeof(uint8_t), 2, arquivoJava);
    charLido>>=8;//os bytes no arquivo estao na ordem b1.b2; são colocados em charLido na ordem b2.b1
    //nesse caso específico, quero pegar b2, por isso shift 8 bits para direita
    printf("Elementos na Constant Pool +1: %x(hex) | %d(int)\n", charLido, charLido);

    int elementosConstantPool = charLido;
    for(int i = 0; i < elementosConstantPool -1; i++){
        charLido = getc(arquivoJava);
        printf("index[%04d(int)] - ", charLido);
        switch(charLido){
            case 1:
                printf("CONSTANT_Utf8: \n");
                /*Se for um Utf8_info, os proximos x+1 bytes são referentes a:
                tamanho da string;
                string[tamanho];
                */
                fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                charLido <<= 8;
                fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                printf("lenght: %02x(hex) | %02d(int) \n", charLido, charLido);
                printf("Caracteres(hex):(char) - ");
                int lenght = charLido;
                /* Tem que arrumar a leitura de um Utf-8 para mostrar como caractere*/
                for(int i = 0; i < lenght; i++){
                    fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                    printf(" %04x:%c |", charLido, charLido);
                }
                printf("\n");
                break;
            case 3:
                printf("CONSTANT_Integer: \n");
                /*
                Se for um Integer_info, os proximos 4 bytes serão referentes a:
                bytes;
                */
                /*
                Refatorar essa leitura
                */
                fread(&charLido, sizeof(uint8_t), 4, arquivoJava);
//                    charLido <<= 8;
//                    fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                printf("class_index: %02x(hex) | %02d(int) \n", charLido, charLido);

//                    fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
//                    charLido <<= 8;
//                    fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
//                    fprintf(arquivoSaida, "name_and_type_index: %02x(hex) | %02d(int) \n", charLido);
//                    printf("name_and_type_index: %02x(hex) | %02d(int) \n", charLido);
                break;
            case 4:
                printf("CONSTANT_Float: \n");
                /*
                Se for um Float_info, os proximos 4 bytes serão referentes a:
                bytes;
                */
                /*
                Refatorar essa leitura
                */
                fread(&charLido, sizeof(uint8_t), 4, arquivoJava);
//                    charLido <<= 8;
//                    fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                printf("class_index: %02x(hex) | %02d(int) \n", charLido, charLido);

//                    fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
//                    charLido <<= 8;
//                    fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
//                    fprintf(arquivoSaida, "name_and_type_index: %02x(hex) | %02d(int) \n", charLido);
//                    printf("name_and_type_index: %02x(hex) | %02d(int) \n", charLido);
                break;
            case 5:
                printf("CONSTANT_Long: \n");
                break;
            case 6:
                printf("CONSTANT_Double: \n");
                break;
            case 7:
                printf("CONSTANT_Class: \n");
                /*
                Se for um Class_info, os proximos 2 bytes serão referentes a:
                name_index;
                */
                fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                charLido <<= 8;
                fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                printf("name_index: %02x(hex) | %02d(int) \n", charLido, charLido);
                printf("\n");
                break;
            case 8:
                printf("CONSTANT_String: \n");
                break;
            case 9:
                printf("CONSTANT_Fieldref: \n");
                /*
                Se for um Methodref, os proximos dois bytes serão referentes a:
                class_index;
                name_and_type_index, respectivamente
                */
                /*
                Refatorar essa leitura
                */
                fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                charLido <<= 8;
                fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                printf("class_index: %02x(hex) | %02d(int) \n", charLido, charLido);

                fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                charLido <<= 8;
                fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                printf("name_and_type_index: %02x(hex) | %02d(int) \n", charLido, charLido);
                printf("\n");
                break;
            case 10:
                printf("CONSTANT_Methodref: \n");
                /*
                Se for um Methodref, os proximos dois bytes serão referentes a:
                class_index;
                name_and_type_index, respectivamente
                */
                /*
                Refatorar essa leitura
                */
                fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                charLido <<= 8;
                fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                printf("class_index: %02x(hex) | %02d(int) \n", charLido, charLido);

                fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                charLido <<= 8;
                fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                printf("name_and_type_index: %02x(hex) | %02d(int) \n", charLido, charLido);
                printf("\n");
                break;
            case 11:
                printf("CONSTANT_InterfaceMethodref: \n");
                /*
                Se for um Methodref, os proximos dois bytes serão referentes a:
                class_index;
                name_and_type_index, respectivamente
                */
                /*
                Refatorar essa leitura
                */
                fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                charLido <<= 8;
                fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                printf("class_index: %02x(hex) | %02d(int) \n", charLido, charLido);

                fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                charLido <<= 8;
                fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                printf("name_and_type_index: %02x(hex) | %02d(int) \n", charLido, charLido);
                printf("\n");
                break;
            case 12:
                printf("CONSTANT_NameAndType: \n");
                /*
                Se for um NameAndType_info, os proximos dois bytes serão referentes a:
                name_index;
                descriptor_index, respectivamente
                */
                fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                charLido <<= 8;
                fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                printf("name_index: %02x(hex) | %02d(int) \n", charLido, charLido);

                fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                charLido <<= 8;
                fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
                printf("descriptor_index: %02x(hex) | %02d(int) \n", charLido, charLido);
                break;
            case 15:
                printf("CONSTANT_MethodHandle: \n");
                break;
            case 16:
                printf("CONSTANT_MethodType: \n");
                break;
            case 18:
                printf("CONSTANT_InvokeDynamic: \n");
                break;
        }
        printf("\n");
    }
    /*fim da leitura da Constant Pool*/

    /*Switch para interpretação do Flag de Acesso*/
    fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
    charLido <<=8;
    fread(&charLido, sizeof(uint8_t), 1, arquivoJava);
    printf("Access flags: %04x\n", charLido);
    uint16_t accessFlag = charLido;

    fclose(arquivoJava);
    return 0;
}
