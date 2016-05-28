#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

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

    if(classF.fields_count != 0){
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

            if(field_element.attributes_count != 0){
                /*Tem que fazer as estruturas dos attributes que ainda faltam
                for(m = 0, m < field_element.attributes_count; m++){
                    printf("Field Attribute %d:\n", m + 1);

                    fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                    attribute_element.attribute_name_index = little_to_big16(twoBytes);
                    printf("attribute_name_index:\n%04x\n", attribute_element.attribute_name_index);

                    fread(&fourBytes, sizeof(uint8_t), 4, arquivoJava);
                    attribute_element.attribute_length = little_to_big32(twoBytes);
                    printf("attribute_length:\n%08x\n", attribute_element.attribute_length);

                    if(attribute_element.attribute_length != 0){

                        for(k = 0; k < attribute_element.attribute_length; k++){
                            fread(&byte, sizeof(uint8_t), 1, arquivoJava);
                            attribute_element.info.push_back(byte);
                        }
                    }


                }*/
            }
            classF.fields.push_back(field_element);
        }
    }

    fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
    classF.methods_count = little_to_big16(twoBytes);
    printf("methods_count:\n%04x\n", classF.methods_count);

	fclose(arquivoJava);
	return 0;
}
