#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <map>
#include <string>

#include "../include/structs.hpp"
#define ByteCode "Puppy.class"

uint16_t little_to_big16(uint16_t x) {
    x = ((x & 0xFF00FF00) >> 8) | ((x & 0x00FF00FF) << 8);

    return x;
}

uint32_t little_to_big32(uint32_t x) {
    x = ((x & 0xFF00FF00) >> 8) | ((x & 0x00FF00FF) << 8);
    x = ((x & 0xFFFF0000) >> 16) | ((x & 0x0000FFFF) << 16);

    return x;
}

enum Errors {ErrorA=0, ErrorB, ErrorC};

void exibeClass(ClassFile classF){
    uint8_t tag;
    int n;
    //printf("%d\n", classF.magic);
    printf("Minor version: %d\n", classF.minor_version);
    printf("Major version: %d\n", classF.major_version);
    printf("Constant Pool Count: %d\n", classF.constant_pool_count);

     

    for (n = 0; n < classF.constant_pool_count - 1; n++) {
        int index;
        cp_info_u cinfo = classF.constant_pool[n].cp_union;
        tag = classF.constant_pool[n].tag;
        printf("#%d = ",n+1);

        // Todas as entradas da constant pool são obtidas de forma parecida,
        // então há um exemplo no primeiro case e o resto segue uma mesma
        // lógica.
        switch (tag) {
            case CONSTANT_Class:
                printf("Class\t\t");
                index = cinfo.constant_class.name_index;
                printf("#%d\t\t", index);
                printf("// %s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);
                break;

            case CONSTANT_Fieldref:
                printf("Fieldref\t\t");
                printf("#%d.#%d\n", cinfo.constant_fieldref.class_index, cinfo.constant_fieldref.name_and_type_index);
                break;

            case CONSTANT_Methodref:
                printf("Methodref\t\t");
                printf("#%d.#%d\n", cinfo.constant_methodref.class_index, cinfo.constant_methodref.name_and_type_index);
                break;

            case CONSTANT_InterfaceMethodref:
                printf("InterfaceMethodref\t\t");
                printf("#%d.#%d\n", cinfo.constant_interfaceMethodref.class_index, cinfo.constant_interfaceMethodref.name_and_type_index);
                break;

            case CONSTANT_String:
                printf("String\t\t");
                printf("#%d\n", cinfo.constant_string.string_index);
                break;

            case CONSTANT_Integer:
                printf("Integer\t\t");
                printf("#%d\n", cinfo.constant_integer.bytes);
                break;

            case CONSTANT_Float:
                printf("Float\t\t");
                printf("#%d\n", cinfo.constant_float.bytes);
                break;

            case CONSTANT_Long:
                printf("Long\t\t");
                printf("#%d.#%d\n", cinfo.constant_long.high_bytes, cinfo.constant_long.low_bytes);
                break;

            case CONSTANT_Double:
                printf("Double\t\t");
                printf("#%d.#%d\n", cinfo.constant_double.high_bytes, cinfo.constant_double.low_bytes);
                break;

            case CONSTANT_NameAndType:
                printf("NameAndType\t");
                printf("#%d.#%d\n", cinfo.constant_nameAndType.name_index, cinfo.constant_nameAndType.descriptor_index);
                break;

            case CONSTANT_Utf8:
                printf("Utf8\t\t");
                printf("%s\n", cinfo.constant_Utf8.bytes);
                break;

            case CONSTANT_MethodHandle:
                printf("MethodHandle\t\t");
                printf("#%d.#%d\n", cinfo.constant_methodHandle.reference_kind, cinfo.constant_methodHandle.reference_index);
                break;

            case CONSTANT_MethodType:
                printf("MethodType\t\t");
                printf("#%d\n", cinfo.constant_methodType.descriptor_index);
                break;

            case CONSTANT_InvokeDynamic:
                printf("InvokeDynamic\t\t");
                printf("#%d.#%d\n", cinfo.constant_invokeDynamic.bootstrap_method_attr_index, cinfo.constant_invokeDynamic.name_and_type_index);
                break;
        }
    }
}

int main(int argc, char** argv){
    int n = 0, j = 0;
    uint8_t byte = 0, tag = 0;
    uint16_t twoBytes = 0;
    uint32_t fourBytes = 0;
    ClassFile classF;
    cp_info cp_element;
    FILE *arquivoJava;

    if( !(arquivoJava = fopen(ByteCode, "rb"))) {
        printf("O arquivo .class não pode ser aberto.\n");
        return 1;
    }

    // Leitura do magicNumber
    //printf("Magic Number: \n");
    fread(&fourBytes, sizeof(uint8_t), 4, arquivoJava);
    classF.magic = little_to_big32(fourBytes);
    //printf("%08x\n", classF.magic);

    // Leitura do minor_version
    //printf("minor_version: \n");
    fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
    classF.minor_version = little_to_big16(twoBytes);
    //printf("%04x\n", classF.minor_version);

    // Leitura do major_version
    //printf("major_version: \n");
    fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
    classF.major_version = little_to_big16(twoBytes);
    //printf("%04x\n", classF.major_version);

    // Leitura do constant_pool_count
    //printf("constant_pool_count: \n");
    fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
    classF.constant_pool_count = little_to_big16(twoBytes);
    //printf("%04x\n", classF.constant_pool_count);

    // Leitura da constant poll
    for (n = 0; n < classF.constant_pool_count; n++) {
        fread(&tag, sizeof(uint8_t), 1, arquivoJava);

        // Todas as entradas da constant pool são obtidas de forma parecida,
        // então há um exemplo no primeiro case e o resto segue uma mesma
        // lógica.
        switch (tag) {
            case CONSTANT_Class:
                cp_element.tag = CONSTANT_Class;
                cp_element.cp_union.constant_class.tag = CONSTANT_Class;
                fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                cp_element.cp_union.constant_class.name_index =  little_to_big16(twoBytes);
                classF.constant_pool.push_back(cp_element);

                break;

            case CONSTANT_Fieldref:
                cp_element.tag = CONSTANT_Fieldref;
                cp_element.cp_union.constant_fieldref.tag = CONSTANT_Fieldref;
                fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                cp_element.cp_union.constant_fieldref.class_index = little_to_big16(twoBytes);
                fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                cp_element.cp_union.constant_fieldref.name_and_type_index = little_to_big16(twoBytes);
                classF.constant_pool.push_back(cp_element);

                break;

            case CONSTANT_Methodref:
                cp_element.tag = CONSTANT_Methodref;
                cp_element.cp_union.constant_methodref.tag = CONSTANT_Methodref;
                fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                cp_element.cp_union.constant_methodref.class_index = little_to_big16(twoBytes);
                fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                cp_element.cp_union.constant_methodref.name_and_type_index = little_to_big16(twoBytes);
                classF.constant_pool.push_back(cp_element);

                break;

            case CONSTANT_InterfaceMethodref:
                cp_element.tag = CONSTANT_InterfaceMethodref;
                cp_element.cp_union.constant_interfaceMethodref.tag = CONSTANT_InterfaceMethodref;
                fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                cp_element.cp_union.constant_interfaceMethodref.class_index = little_to_big16(twoBytes);
                fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                cp_element.cp_union.constant_interfaceMethodref.name_and_type_index = little_to_big16(twoBytes);
                classF.constant_pool.push_back(cp_element);

                break;

            case CONSTANT_String:
                cp_element.tag = CONSTANT_String;
                cp_element.cp_union.constant_string.tag = CONSTANT_String;\
                                                          fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                cp_element.cp_union.constant_string.string_index = little_to_big16(twoBytes);
                classF.constant_pool.push_back(cp_element);

                break;

            case CONSTANT_Integer:
                cp_element.tag = CONSTANT_Integer;
                cp_element.cp_union.constant_integer.tag = CONSTANT_Integer;
                fread(&fourBytes, sizeof(uint8_t), 4, arquivoJava);
                cp_element.cp_union.constant_integer.bytes = little_to_big32(fourBytes);
                classF.constant_pool.push_back(cp_element);

                break;

            case CONSTANT_Float:
                cp_element.tag = CONSTANT_Float;
                cp_element.cp_union.constant_float.tag = CONSTANT_Float;
                fread(&fourBytes, sizeof(uint8_t), 4, arquivoJava);
                cp_element.cp_union.constant_float.bytes = little_to_big32(fourBytes);
                classF.constant_pool.push_back(cp_element);

                break;

            case CONSTANT_Long:
                cp_element.tag = CONSTANT_Long;
                cp_element.cp_union.constant_long.tag = CONSTANT_Long;
                fread(&fourBytes, sizeof(uint8_t), 4, arquivoJava);
                cp_element.cp_union.constant_long.high_bytes = little_to_big32(fourBytes);
                fread(&fourBytes, sizeof(uint8_t), 4, arquivoJava);
                cp_element.cp_union.constant_long.low_bytes = little_to_big32(fourBytes);
                classF.constant_pool.push_back(cp_element);

                break;

            case CONSTANT_Double:
                cp_element.tag = CONSTANT_Double;
                cp_element.cp_union.constant_double.tag = CONSTANT_Double;
                fread(&fourBytes, sizeof(uint8_t), 4, arquivoJava);
                cp_element.cp_union.constant_double.high_bytes = little_to_big32(fourBytes);
                fread(&fourBytes, sizeof(uint8_t), 4, arquivoJava);
                cp_element.cp_union.constant_double.low_bytes = little_to_big32(fourBytes);
                classF.constant_pool.push_back(cp_element);

                break;

            case CONSTANT_NameAndType:
                cp_element.tag = CONSTANT_NameAndType;
                cp_element.cp_union.constant_nameAndType.tag = CONSTANT_NameAndType;
                fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                cp_element.cp_union.constant_nameAndType.name_index = little_to_big16(twoBytes);
                fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                cp_element.cp_union.constant_nameAndType.descriptor_index = little_to_big16(twoBytes);
                classF.constant_pool.push_back(cp_element);

                break;

            case CONSTANT_Utf8:
                cp_element.tag = CONSTANT_Utf8;
                cp_element.cp_union.constant_Utf8.tag = CONSTANT_Utf8;
                fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                cp_element.cp_union.constant_Utf8.length = little_to_big16(twoBytes);

                cp_element.cp_union.constant_Utf8.bytes = (char*)malloc(cp_element.cp_union.constant_Utf8.length*sizeof(char));
                for (j = 0; j < cp_element.cp_union.constant_Utf8.length; j++) {
                    fread(&byte, sizeof(uint8_t), 1, arquivoJava);
                    cp_element.cp_union.constant_Utf8.bytes[j] = byte;
                }

                classF.constant_pool.push_back(cp_element);

                break;

            case CONSTANT_MethodHandle:
                cp_element.tag = CONSTANT_MethodHandle;
                cp_element.cp_union.constant_methodHandle.tag = CONSTANT_MethodHandle;
                fread(&byte, sizeof(uint8_t), 1, arquivoJava);
                cp_element.cp_union.constant_methodHandle.reference_kind = byte;
                fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                cp_element.cp_union.constant_methodHandle.reference_index = little_to_big16(twoBytes);
                classF.constant_pool.push_back(cp_element);

                break;

            case CONSTANT_MethodType:
                cp_element.tag = CONSTANT_MethodType;
                cp_element.cp_union.constant_methodType.tag = CONSTANT_MethodType;
                fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                cp_element.cp_union.constant_methodType.descriptor_index = little_to_big16(twoBytes);
                classF.constant_pool.push_back(cp_element);

                break;

            case CONSTANT_InvokeDynamic:
                cp_element.tag = CONSTANT_InvokeDynamic;
                cp_element.cp_union.constant_invokeDynamic.tag = CONSTANT_InvokeDynamic;
                fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                cp_element.cp_union.constant_invokeDynamic.bootstrap_method_attr_index = little_to_big16(twoBytes);
                fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                cp_element.cp_union.constant_invokeDynamic.name_and_type_index = little_to_big16(twoBytes);

                break;
        }
    }

    exibeClass(classF);

    fclose(arquivoJava);
    return 0;
}
