#include "../include/read_attributes.hpp"

attribute_info read_attributes(FILE *fp, std::vector<cp_info> constant_pool) {
	cp_info cp_element;
	attribute_info attribute_element;

	// Leitura do attribute name index
	attribute_element.attribute_name_index = read_word(fp);

	// Leitura do attribute length
	attribute_element.attribute_length = read_dword(fp);

	// Leitura do constant pool utilizando o attribute name index
	cp_element = constant_pool[attribute_element.attribute_name_index - 1];
	// O elemento no índice tem que ser do tipo CONSTANT_Utf8
	if(cp_element.tag == CONSTANT_Utf8) {
		// Se o attribute for do tipo SourceFile
		if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "SourceFile")) {
			printf("Attribute: SourceFile\n");

			attribute_element.attribute_union.attr_SourceFile.attribute_name_index = attribute_element.attribute_name_index;
			printf("attribute_name_index:\n%04x\n", attribute_element.attribute_union.attr_SourceFile.attribute_name_index);

			attribute_element.attribute_union.attr_SourceFile.attribute_length = attribute_element.attribute_length;
			printf("attribute_length:\n%08x\n", attribute_element.attribute_union.attr_SourceFile.attribute_length);

			// Leitura do sourcefile_index
			attribute_element.attribute_union.attr_SourceFile.sourcefile_index = read_word(fp);
			printf("Sourcefile_index:\n%04x\n", attribute_element.attribute_union.attr_SourceFile.sourcefile_index);
		}

		// Se o attribute for do tipo ConstantValue
		if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "ConstantValue")) {
			printf("Attribute: ConstantValue\n");

			attribute_element.attribute_union.attr_ConstantValue.attribute_name_index = attribute_element.attribute_name_index;
			printf("attribute_name_index:\n%04x\n", attribute_element.attribute_union.attr_ConstantValue.attribute_name_index);

			attribute_element.attribute_union.attr_ConstantValue.attribute_length = attribute_element.attribute_length;
			printf("attribute_length:\n%08x\n", attribute_element.attribute_union.attr_ConstantValue.attribute_length);

			// Leitura do constantvalue_index
			attribute_element.attribute_union.attr_ConstantValue.constantvalue_index = read_word(fp);
			printf("Constantvalue_index:\n%04x\n", attribute_element.attribute_union.attr_ConstantValue.constantvalue_index);
		}

	}

	// Se o elemento no índice não for do tipo CONSTANT_Utf8
	else{
		printf("Error! Attribute_name_index must point to CONSTANT_Utf8_info structure!\n");
		exit(EXIT_FAILURE);
	}

	return attribute_element;
}
