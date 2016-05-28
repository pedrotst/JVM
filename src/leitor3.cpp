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
	int n = 0, j = 0;
	uint8_t byte = 0, tag = 0;
	uint16_t twoBytes = 0;
	uint32_t fourBytes = 0;
	ClassFile *classF = NULL;
      cp_info *cp_element = NULL;
	FILE *arquivoJava;

	classF =  (ClassFile*)malloc(sizeof(ClassFile));

	if( !(arquivoJava = fopen(ByteCode, "rb"))) {
		printf("O arquivo .class não pode ser aberto.\n");
		return 1;
	}

	// Leitura do magicNumber
	printf("Magic Number: \n");
	fread(&fourBytes, sizeof(uint8_t), 4, arquivoJava);
	classF->magic = little_to_big32(fourBytes);
	printf("%08x\n", classF->magic);

 	// Leitura do minor_version
	printf("minor_version: \n");
	fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
	classF->minor_version = little_to_big16(twoBytes);
	printf("%04x\n", classF->minor_version);

	// Leitura do major_version
	printf("major_version: \n");
	fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
	classF->major_version = little_to_big16(twoBytes);
	printf("%04x\n", classF->major_version);

	// Leitura do constant_pool_count
	printf("constant_pool_count: \n");
	fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
	classF->constant_pool_count = little_to_big16(twoBytes);
	printf("%04x\n", classF->constant_pool_count);

      // Leitura da constant poll
	cp_element = (cp_info*)malloc(sizeof(cp_info));
      for (n = 0; n < classF->constant_pool_count; n++) {
            cp_element->ptr = NULL;
            fread(&tag, sizeof(uint8_t), 1, arquivoJava);

            // Todas as entradas da constant pool são obtidas de forma parecida,
            // então há um exemplo no primeiro case e o resto segue uma mesma
            // lógica.
            switch (tag) {
                  case CONSTANT_Class:
                        // Cria um novo elemento da constant pool e atribui a
                        // sua tag e seu ponteiro de acordo com o case.
                        // Exemplo:
                        // typedef struct cp_info_s {
                        // 	uint8_t tag;
                        // 	void *ptr;
                        // } cp_info;
                        //
                        // cp_info cp_element;
                        //
                        // cp_element->tag = CONSTANT_Class
                        // cp_element-> = PONTEIRO_PARA_CONSTANT_Class_info
                        // A próxima linha adiciona essa entrada à constant pool
                        // classF->constant_pool.push_back(*cp_element);
                        cp_element->tag = CONSTANT_Class;
                        cp_element->ptr = (CONSTANT_Class_info*)malloc(sizeof(CONSTANT_Class_info));
                        classF->constant_pool.push_back(*cp_element);

                        // A estrutura da constant class é populada com as informações
                        // lidas do .class
                        //
                        // typedef struct CONSTANT_Class_info_s {
                        // 	uint8_t tag;
                        // 	uint16_t name_index;
                        // } CONSTANT_Class_info;
                        ((CONSTANT_Class_info*)cp_element->ptr)->tag = CONSTANT_Class;
                        fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                        ((CONSTANT_Class_info*)cp_element->ptr)->name_index = little_to_big16(twoBytes);

                        break;

                  case CONSTANT_Fieldref:
                        cp_element->tag = CONSTANT_Fieldref;
                        cp_element->ptr = (CONSTANT_Fieldref_info*)malloc(sizeof(CONSTANT_Fieldref_info));
                        classF->constant_pool.push_back(*cp_element);

                        // uint8_t tag
                        ((CONSTANT_Fieldref_info*)cp_element->ptr)->tag = CONSTANT_Fieldref;

                        // uint16_t class_index
                        fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                        ((CONSTANT_Fieldref_info*)cp_element->ptr)->class_index = little_to_big16(twoBytes);

                        // uint16_t name_and_type_index
                        fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                        ((CONSTANT_Fieldref_info*)cp_element->ptr)->name_and_type_index = little_to_big16(twoBytes);

                        break;

                  case CONSTANT_Methodref:
                        cp_element->tag = CONSTANT_Methodref;
                        cp_element->ptr = (CONSTANT_Methodref_info*)malloc(sizeof(CONSTANT_Methodref_info));
                        classF->constant_pool.push_back(*cp_element);

                        ((CONSTANT_Methodref_info*)cp_element->ptr)->tag = CONSTANT_Methodref;

                        fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                        ((CONSTANT_Methodref_info*)cp_element->ptr)->class_index = little_to_big16(twoBytes);

                        fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                        ((CONSTANT_Methodref_info*)cp_element->ptr)->name_and_type_index = little_to_big16(twoBytes);

                        break;

                  case CONSTANT_InterfaceMethodref:
                        cp_element->tag = CONSTANT_InterfaceMethodref;
                        cp_element->ptr = (CONSTANT_InterfaceMethodref_info*)malloc(sizeof(CONSTANT_InterfaceMethodref_info));
                        classF->constant_pool.push_back(*cp_element);

                        ((CONSTANT_InterfaceMethodref_info*)cp_element->ptr)->tag = CONSTANT_InterfaceMethodref;

                        fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                        ((CONSTANT_InterfaceMethodref_info*)cp_element->ptr)->class_index = little_to_big16(twoBytes);

                        fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                        ((CONSTANT_InterfaceMethodref_info*)cp_element->ptr)->name_and_type_index = little_to_big16(twoBytes);

                        break;

                  case CONSTANT_String:
                        cp_element->tag = CONSTANT_String;
                        cp_element->ptr = (CONSTANT_String_info*)malloc(sizeof(CONSTANT_String_info));
                        classF->constant_pool.push_back(*cp_element);

                        ((CONSTANT_String_info*)cp_element->ptr)->tag = CONSTANT_String;

                        fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                        ((CONSTANT_String_info*)cp_element->ptr)->string_index = little_to_big16(twoBytes);

                        break;

                  case CONSTANT_Integer:
                        cp_element->tag = CONSTANT_Integer;
                        cp_element->ptr = (CONSTANT_Integer_info*)malloc(sizeof(CONSTANT_Integer_info));
                        classF->constant_pool.push_back(*cp_element);

                        ((CONSTANT_Integer_info*)cp_element->ptr)->tag = CONSTANT_Integer;

                        fread(&fourBytes, sizeof(uint8_t), 4, arquivoJava);
                        ((CONSTANT_Integer_info*)cp_element->ptr)->bytes = little_to_big32(fourBytes);

                        break;

                  case CONSTANT_Float:
                        cp_element->tag = CONSTANT_Float;
                        cp_element->ptr = (CONSTANT_Float_info*)malloc(sizeof(CONSTANT_Float_info));
                        classF->constant_pool.push_back(*cp_element);

                        ((CONSTANT_Float_info*)cp_element->ptr)->tag = CONSTANT_Float;

                        fread(&fourBytes, sizeof(uint8_t), 4, arquivoJava);
                        ((CONSTANT_Float_info*)cp_element->ptr)->bytes = little_to_big32(fourBytes);

                        break;

                  case CONSTANT_Long:
                        cp_element->tag = CONSTANT_Long;
                        cp_element->ptr = (CONSTANT_Long_info*)malloc(sizeof(CONSTANT_Long_info));
                        classF->constant_pool.push_back(*cp_element);

                        ((CONSTANT_Long_info*)cp_element->ptr)->tag = CONSTANT_Long;

                        fread(&fourBytes, sizeof(uint8_t), 4, arquivoJava);
                        ((CONSTANT_Long_info*)cp_element->ptr)->high_bytes = little_to_big32(fourBytes);

                        fread(&fourBytes, sizeof(uint8_t), 4, arquivoJava);
                        ((CONSTANT_Long_info*)cp_element->ptr)->low_bytes = little_to_big32(fourBytes);

                        break;

                  case CONSTANT_Double:
                        cp_element->tag = CONSTANT_Double;
                        cp_element->ptr = (CONSTANT_Double_info*)malloc(sizeof(CONSTANT_Double_info));
                        classF->constant_pool.push_back(*cp_element);

                        ((CONSTANT_Double_info*)cp_element->ptr)->tag = CONSTANT_Double;

                        fread(&fourBytes, sizeof(uint8_t), 4, arquivoJava);
                        ((CONSTANT_Double_info*)cp_element->ptr)->high_bytes = little_to_big32(fourBytes);

                        fread(&fourBytes, sizeof(uint8_t), 4, arquivoJava);
                        ((CONSTANT_Double_info*)cp_element->ptr)->low_bytes = little_to_big32(fourBytes);

                        break;

                  case CONSTANT_NameAndType:
                        cp_element->tag = CONSTANT_NameAndType;
                        cp_element->ptr = (CONSTANT_NameAndType_info*)malloc(sizeof(CONSTANT_NameAndType_info));
                        classF->constant_pool.push_back(*cp_element);

                        ((CONSTANT_NameAndType_info*)cp_element->ptr)->tag = CONSTANT_NameAndType;

                        fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                        ((CONSTANT_NameAndType_info*)cp_element->ptr)->name_index = little_to_big16(twoBytes);

                        fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                        ((CONSTANT_NameAndType_info*)cp_element->ptr)->descriptor_index = little_to_big16(twoBytes);

                        break;


                  case CONSTANT_Utf8:
                        cp_element->tag = CONSTANT_Utf8;
                        cp_element->ptr = (CONSTANT_Utf8_info*)malloc(sizeof(CONSTANT_Utf8_info));
                        classF->constant_pool.push_back(*cp_element);

                        ((CONSTANT_Utf8_info*)cp_element->ptr)->tag = CONSTANT_Utf8;

                        fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                        ((CONSTANT_Utf8_info*)cp_element->ptr)->length = little_to_big16(twoBytes);

                        ((CONSTANT_Utf8_info*)cp_element->ptr)->bytes = (char*)malloc(((CONSTANT_Utf8_info*)cp_element->ptr)->length*sizeof(char));
                        for (j = 0; j < ((CONSTANT_Utf8_info*)cp_element->ptr)->length; j++) {
                              fread(&byte, sizeof(uint8_t), 1, arquivoJava);
                              ((CONSTANT_Utf8_info*)cp_element->ptr)->bytes[j] = byte;
                        }

                        break;

                  case CONSTANT_MethodHandle:
                        cp_element->tag = CONSTANT_MethodHandle;
                        cp_element->ptr = (CONSTANT_MethodHandle_info*)malloc(sizeof(CONSTANT_MethodHandle_info));
                        classF->constant_pool.push_back(*cp_element);

                        ((CONSTANT_MethodHandle_info*)cp_element->ptr)->tag = CONSTANT_MethodHandle;

                        fread(&byte, sizeof(uint8_t), 1, arquivoJava);
                        ((CONSTANT_MethodHandle_info*)cp_element->ptr)->reference_kind = byte;

                        fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                        ((CONSTANT_MethodHandle_info*)cp_element->ptr)->reference_index = little_to_big16(twoBytes);

                        break;

                  case CONSTANT_MethodType:
                        cp_element->tag = CONSTANT_MethodType;
                        cp_element->ptr = (CONSTANT_MethodType_info*)malloc(sizeof(CONSTANT_MethodType_info));
                        classF->constant_pool.push_back(*cp_element);

                        ((CONSTANT_MethodType_info*)cp_element->ptr)->tag = CONSTANT_MethodType;

                        fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                        ((CONSTANT_MethodType_info*)cp_element->ptr)->descriptor_index = little_to_big16(twoBytes);

                        break;

                  case CONSTANT_InvokeDynamic:
                        cp_element->tag = CONSTANT_InvokeDynamic;
                        cp_element->ptr = (CONSTANT_InvokeDynamic_info*)malloc(sizeof(CONSTANT_InvokeDynamic_info));
                        classF->constant_pool.push_back(*cp_element);

                        ((CONSTANT_InvokeDynamic_info*)cp_element->ptr)->tag = CONSTANT_InvokeDynamic;

                        fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                        ((CONSTANT_InvokeDynamic_info*)cp_element->ptr)->bootstrap_method_attr_index = little_to_big16(twoBytes);

                        fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
                        ((CONSTANT_InvokeDynamic_info*)cp_element->ptr)->name_and_type_index = little_to_big16(twoBytes);

                        break;
            }
      }

	fclose(arquivoJava);
	return 0;
}
