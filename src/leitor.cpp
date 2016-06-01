#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string>
#include <cstring>

#include "../include/structs.hpp"
#include "../include/attributes.hpp"
#include "../include/little_to_big.hpp"
#include "../include/read_bytes.hpp"
#include "../include/exibidor.hpp"
#include "../include/read_attributes.hpp"
#include "../include/read_methods.hpp"
#define ByteCode "Puppy.class"



int main(int argc, char** argv){

	int n = 0, m = 0, k = 0, j = 0;
	uint8_t byte = 0, tag = 0;
	uint16_t twoBytes = 0;
	uint32_t fourBytes = 0;
  
	ClassFile classF;
	cp_info cp_element;
	field_info field_element;
	attribute_info attribute_element;
	method_info method_element;
	FILE *arquivoJava;

	if( !(arquivoJava = fopen(argv[1], "rb"))) {
		printf("O arquivo .class não pode ser aberto.\n");
		return 1;
	}

	// Leitura do magicNumber
	classF.magic = read_dword(arquivoJava);

	// Leitura do minor_version
	classF.minor_version = read_word(arquivoJava);

	// Leitura do major_version
	classF.major_version = read_word(arquivoJava);

	// Leitura do constant_pool_count
	classF.constant_pool_count = read_word(arquivoJava);

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
			cp_element.cp_union.constant_class.name_index =  read_word(arquivoJava);
			classF.constant_pool.push_back(cp_element);

			break;

		case CONSTANT_Fieldref:
			cp_element.tag = CONSTANT_Fieldref;
			cp_element.cp_union.constant_fieldref.tag = CONSTANT_Fieldref;
			cp_element.cp_union.constant_fieldref.class_index = read_word(arquivoJava);
			cp_element.cp_union.constant_fieldref.name_and_type_index = read_word(arquivoJava);
			classF.constant_pool.push_back(cp_element);

			break;

		case CONSTANT_Methodref:
			cp_element.tag = CONSTANT_Methodref;
			cp_element.cp_union.constant_methodref.tag = CONSTANT_Methodref;
			cp_element.cp_union.constant_methodref.class_index = read_word(arquivoJava);
			cp_element.cp_union.constant_methodref.name_and_type_index = read_word(arquivoJava);
			classF.constant_pool.push_back(cp_element);

			break;

		case CONSTANT_InterfaceMethodref:
			cp_element.tag = CONSTANT_InterfaceMethodref;
			cp_element.cp_union.constant_interfaceMethodref.tag = CONSTANT_InterfaceMethodref;
			cp_element.cp_union.constant_interfaceMethodref.class_index = read_word(arquivoJava);
			cp_element.cp_union.constant_interfaceMethodref.name_and_type_index = read_word(arquivoJava);
			classF.constant_pool.push_back(cp_element);

			break;

		case CONSTANT_String:
			cp_element.tag = CONSTANT_String;
			cp_element.cp_union.constant_string.tag = CONSTANT_String; \
			cp_element.cp_union.constant_string.string_index = read_word(arquivoJava);
			classF.constant_pool.push_back(cp_element);

			break;

		case CONSTANT_Integer:
			cp_element.tag = CONSTANT_Integer;
			cp_element.cp_union.constant_integer.tag = CONSTANT_Integer;
			cp_element.cp_union.constant_integer.bytes = read_dword(arquivoJava);
			classF.constant_pool.push_back(cp_element);

			break;

		case CONSTANT_Float:
			cp_element.tag = CONSTANT_Float;
			cp_element.cp_union.constant_float.tag = CONSTANT_Float;
			cp_element.cp_union.constant_float.bytes = read_dword(arquivoJava);
			classF.constant_pool.push_back(cp_element);

			break;

		case CONSTANT_Long:
			cp_element.tag = CONSTANT_Long;
			cp_element.cp_union.constant_long.tag = CONSTANT_Long;
			cp_element.cp_union.constant_long.high_bytes = read_dword(arquivoJava);
			cp_element.cp_union.constant_long.low_bytes = read_dword(arquivoJava);
			classF.constant_pool.push_back(cp_element);
      cp_element.tag = ZERO;
      classF.constant_pool.push_back(cp_element);


      n++;//

			break;

		case CONSTANT_Double:
			cp_element.tag = CONSTANT_Double;
			cp_element.cp_union.constant_double.tag = CONSTANT_Double;
			cp_element.cp_union.constant_double.high_bytes = read_dword(arquivoJava);
			cp_element.cp_union.constant_double.low_bytes = read_dword(arquivoJava);
			classF.constant_pool.push_back(cp_element);
      cp_element.tag = ZERO;
      classF.constant_pool.push_back(cp_element);
      n++; //

			break;

		case CONSTANT_NameAndType:
			cp_element.tag = CONSTANT_NameAndType;
			cp_element.cp_union.constant_nameAndType.tag = CONSTANT_NameAndType;
			cp_element.cp_union.constant_nameAndType.name_index = read_word(arquivoJava);
			cp_element.cp_union.constant_nameAndType.descriptor_index = read_word(arquivoJava);
			classF.constant_pool.push_back(cp_element);

			break;

		case CONSTANT_Utf8:
			cp_element.tag = CONSTANT_Utf8;
			cp_element.cp_union.constant_Utf8.tag = CONSTANT_Utf8;
			cp_element.cp_union.constant_Utf8.length = read_word(arquivoJava);

			cp_element.cp_union.constant_Utf8.bytes = (char*)malloc((cp_element.cp_union.constant_Utf8.length + 1)*sizeof(char));
			for (j = 0; j < cp_element.cp_union.constant_Utf8.length; j++) {
				cp_element.cp_union.constant_Utf8.bytes[j] = read_byte(arquivoJava);
			}
			cp_element.cp_union.constant_Utf8.bytes[cp_element.cp_union.constant_Utf8.length] = '\0';

			classF.constant_pool.push_back(cp_element);

			break;

		case CONSTANT_MethodHandle:
			cp_element.tag = CONSTANT_MethodHandle;
			cp_element.cp_union.constant_methodHandle.tag = CONSTANT_MethodHandle;
			cp_element.cp_union.constant_methodHandle.reference_kind = read_byte(arquivoJava);
			cp_element.cp_union.constant_methodHandle.reference_index = read_word(arquivoJava);
			classF.constant_pool.push_back(cp_element);

			break;

		case CONSTANT_MethodType:
			cp_element.tag = CONSTANT_MethodType;
			cp_element.cp_union.constant_methodType.tag = CONSTANT_MethodType;
			cp_element.cp_union.constant_methodType.descriptor_index = read_word(arquivoJava);
			classF.constant_pool.push_back(cp_element);

			break;

		case CONSTANT_InvokeDynamic:
			cp_element.tag = CONSTANT_InvokeDynamic;
			cp_element.cp_union.constant_invokeDynamic.tag = CONSTANT_InvokeDynamic;
			cp_element.cp_union.constant_invokeDynamic.bootstrap_method_attr_index = read_word(arquivoJava);
			cp_element.cp_union.constant_invokeDynamic.name_and_type_index = read_word(arquivoJava);

			break;
		}
	}

	// Leitura do access flags
	classF.access_flags = read_word(arquivoJava);

	// Leitura de this class
	classF.this_class = read_word(arquivoJava);

	// Leitura de super class
	classF.super_class = read_word(arquivoJava);

	// Leitura de interfaces count
	classF.interfaces_count = read_word(arquivoJava);

	if(classF.interfaces_count != 0) {
		//Leitura das interfaces
		for(n = 0; n < classF.interfaces_count; n++) {
			fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
			classF.interfaces.push_back(twoBytes);
		}
	}

	// Leitura de fields count
	classF.fields_count = read_word(arquivoJava);

	//Leitura dos fields
	for(n = 0; n < classF.fields_count; n++) {
		field_element.access_flags = read_word(arquivoJava);
		field_element.name_index = read_word(arquivoJava);
		field_element.descriptor_index = read_word(arquivoJava);
		field_element.attributes_count = read_word(arquivoJava);
		for(m = 0; m < field_element.attributes_count; m++) {
			attribute_element = read_attributes(arquivoJava, classF.constant_pool);
			field_element.attributes.push_back(attribute_element);

	}
	classF.fields.push_back(field_element);
}

// Leitura do methods count
classF.methods_count = read_word(arquivoJava);

/*área de leitura de métodos*/
for(n = 0; n < classF.methods_count; n++) {
    classF.methods.push_back(read_method(arquivoJava, classF.constant_pool));
}

// Leitura de attributes count
classF.attributes_count = read_word(arquivoJava);

// Leitura de attributes
for(n = 0; n < classF.attributes_count; n++) {
	// Lê um atributo
	attribute_element = read_attributes(arquivoJava, classF.constant_pool);

	//Insere o attribute no vetor de attributes do class file
	classF.attributes.push_back(attribute_element);
}

exibeClass(classF);

fclose(arquivoJava);
return 0;
}
