#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <map>
#include <string>
#include <cstring>

#include "../include/structs.hpp"
#include "../include/attributes.hpp"
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
    int n, i;
    printf("Magic: %X\n", classF.magic);
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
                printf("%s\n", cinfo.constant_Utf8.bytes); //Não tem '\0' no final por isso pode dar erro!
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
	int n = 0, m = 0, k = 0, j = 0;
	uint8_t byte = 0, tag = 0;
	uint16_t twoBytes = 0;
	uint32_t fourBytes = 0;
	ClassFile classF;
      cp_info cp_element;
      field_info field_element;
      attribute_info attribute_element;
	FILE *arquivoJava;

	if( !(arquivoJava = fopen(ByteCode, "rb"))) {
		printf("O arquivo .class não pode ser aberto.\n");
		return 1;
	}

	// Leitura do magicNumber
	printf("Magic Number: \n");
	fread(&fourBytes, sizeof(uint8_t), 4, arquivoJava);
	classF.magic = little_to_big32(fourBytes);
	printf("%08x\n", classF.magic);

 	// Leitura do minor_version
	printf("minor_version: \n");
	fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
	classF.minor_version = little_to_big16(twoBytes);
	printf("%04x\n", classF.minor_version);

	// Leitura do major_version
	printf("major_version: \n");
	fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
	classF.major_version = little_to_big16(twoBytes);
	printf("%04x\n", classF.major_version);

	// Leitura do constant_pool_count
	printf("constant_pool_count: \n");
	fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
	classF.constant_pool_count = little_to_big16(twoBytes);
	printf("%04x\n", classF.constant_pool_count);

      // Leitura da constant poll
      for (n = 0; n < classF.constant_pool_count - 1; n++) {
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
                        //printf("Methodref:\n");
                        cp_element.tag = CONSTANT_Methodref;
                        //printf("tag:\n%02x\n", cp_element.tag);
				cp_element.cp_union.constant_methodref.tag = CONSTANT_Methodref;
				fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
				cp_element.cp_union.constant_methodref.class_index = little_to_big16(twoBytes);
				//printf("class index:\n%04x\n", cp_element.cp_union.constant_methodref.class_index);
				fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
				cp_element.cp_union.constant_methodref.name_and_type_index = little_to_big16(twoBytes);
				//printf("name and type index:\n%04x\n", cp_element.cp_union.constant_methodref.name_and_type_index);
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

				cp_element.cp_union.constant_Utf8.bytes = (char*)malloc((cp_element.cp_union.constant_Utf8.length + 1)*sizeof(char));
				for (j = 0; j < cp_element.cp_union.constant_Utf8.length; j++) {
					fread(&byte, sizeof(uint8_t), 1, arquivoJava);
					cp_element.cp_union.constant_Utf8.bytes[j] = byte;
				}
				cp_element.cp_union.constant_Utf8.bytes[cp_element.cp_union.constant_Utf8.length] = '\0';

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

    // Leitura do access flags
	printf("access_flags: \n");
	fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
	classF.access_flags = little_to_big16(twoBytes);
    printf("%04x\n", classF.access_flags);

    // Leitura de this class
	printf("this_class: \n");
	fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
	classF.this_class = little_to_big16(twoBytes);
    printf("%04x\n", classF.this_class);

    // Leitura de super class
	printf("super_class: \n");
	fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
	classF.super_class = little_to_big16(twoBytes);
    printf("%04x\n", classF.super_class);

    // Leitura de interfaces count
	printf("interfaces_count: \n");
	fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
	classF.interfaces_count = little_to_big16(twoBytes);
    printf("%04x\n", classF.interfaces_count);

    if(classF.interfaces_count != 0){
        //Leitura das interfaces
        for(n = 0; n < classF.interfaces_count; n++){
            fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
            classF.interfaces.push_back(twoBytes);
        }
    }

    // Leitura de fields count
	printf("fields_count: \n");
	fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
	classF.fields_count = little_to_big16(twoBytes);
    printf("%04x\n", classF.fields_count);

    //Leitura dos fields
    for(n = 0; n < classF.fields_count; n++){
        printf("Field %d:\n", n + 1);

        fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
        field_element.access_flags = little_to_big16(twoBytes);
        printf("access_flags:\n%04x\n", field_element.access_flags);

        fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
        field_element.name_index = little_to_big16(twoBytes);
        printf("name_index:\n%04x\n", field_element.name_index);

        fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
        field_element.descriptor_index = little_to_big16(twoBytes);
        printf("descriptor_index:\n%04x\n", field_element.descriptor_index);

        fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
        field_element.attributes_count = little_to_big16(twoBytes);
        printf("attributes_count:\n%04x\n", field_element.attributes_count);

        /*Tem que fazer as estruturas dos attributes que ainda faltam*/
        /*for(m = 0, m < field_element.attributes_count; m++){
            printf("Field Attribute %d:\n", m + 1);

            fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
            attribute_element.attribute_name_index = little_to_big16(twoBytes);
            printf("attribute_name_index:\n%04x\n", attribute_element.attribute_name_index);

            fread(&fourBytes, sizeof(uint8_t), 4, arquivoJava);
            attribute_element.attribute_length = little_to_big32(twoBytes);
            printf("attribute_length:\n%08x\n", attribute_element.attribute_length);

            read_attribute_type(attribute_element.attribute_name_index)
            for(k = 0; k < attribute_element.attribute_length; k++){
                fread(&byte, sizeof(uint8_t), 1, arquivoJava);

            }
        }*/
            classF.fields.push_back(field_element);
    }

    // Leitura do methods count
    fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
    classF.methods_count = little_to_big16(twoBytes);
    printf("methods_count:\n%04x\n", classF.methods_count);

    /*área de leitura de métodos*/
    for(n = 0; n < 302; n++){
        fread(&byte, sizeof(uint8_t), 1, arquivoJava);
    }

    // Leitura de attributes count
    fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
    classF.attributes_count = little_to_big16(twoBytes);
    printf("attributes_count:\n%04x\n", classF.attributes_count);

    // Leitura de attributes
    for(n = 0; n < classF.attributes_count; n++){
        printf("Attribute %d:\n", n + 1);

        // Leitura do attribute name index
        fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
        attribute_element.attribute_name_index = little_to_big16(twoBytes);

        // Leitura do attribute length
        fread(&fourBytes, sizeof(uint8_t), 4, arquivoJava);
        attribute_element.attribute_length = little_to_big32(fourBytes);

        // Leitura do constant pool utilizando o attribute name index
        cp_element = classF.constant_pool[attribute_element.attribute_name_index - 1];
        // O elemento no índice tem que ser do tipo CONSTANT_Utf8
        if(cp_element.tag == CONSTANT_Utf8){
            // Se o attribute for do tipo SourceFile
            if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "SourceFile")){
                printf("Attribute: SourceFile\n");

                attribute_element.attribute_union.attr_SourceFile.attribute_name_index = attribute_element.attribute_name_index;
                printf("attribute_name_index:\n%04x\n", attribute_element.attribute_union.attr_SourceFile.attribute_name_index);

                attribute_element.attribute_union.attr_SourceFile.attribute_length = attribute_element.attribute_length;
                printf("attribute_length:\n%08x\n", attribute_element.attribute_union.attr_SourceFile.attribute_length);

                // Leitura do sourcefile_index
                fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                attribute_element.attribute_union.attr_SourceFile.sourcefile_index = little_to_big16(twoBytes);
                printf("Sourcefile_index:\n%04x\n", attribute_element.attribute_union.attr_SourceFile.sourcefile_index);
            }

            // Se o attribute for do tipo ConstantValue
            if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "ConstantValue")){
                printf("Attribute: ConstantValue\n");

                attribute_element.attribute_union.attr_ConstantValue.attribute_name_index = attribute_element.attribute_name_index;
                printf("attribute_name_index:\n%04x\n", attribute_element.attribute_union.attr_ConstantValue.attribute_name_index);

                attribute_element.attribute_union.attr_ConstantValue.attribute_length = attribute_element.attribute_length;
                printf("attribute_length:\n%08x\n", attribute_element.attribute_union.attr_ConstantValue.attribute_length);

                // Leitura do constantvalue_index
                fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                attribute_element.attribute_union.attr_ConstantValue.constantvalue_index = little_to_big16(twoBytes);
                printf("Constantvalue_index:\n%04x\n", attribute_element.attribute_union.attr_ConstantValue.constantvalue_index);
            }

        }

        // Se o elemento no índice não for do tipo CONSTANT_Utf8
        else{
            printf("Error! Attribute_name_index must point to CONSTANT_Utf8_info structure!\n");
            exit(EXIT_FAILURE);
        }

        //Insere o attribute no vetor de attributes do class file
        classF.attributes.push_back(attribute_element);
    }

    printf("\n\n");
    exibeClass(classF);

	fclose(arquivoJava);
	return 0;
}
