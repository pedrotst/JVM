//#include "../include/print_attributes.hpp"
//
//void print_attributes(attribute_info attribute_element) {
//      int n = 0;
//	cp_info cp_element;
//      line_number_table_info line_number_table_element;
//	     attribute_info attribute_element, attribute_element_aux;
//      exception_table_info exception_table_element;
//      local_variable_type_table_info local_variable_type_table_element;
//      local_variable_table_info local_variable_table_element;
//      classes_info classes_element;
//
//	// Leitura do attribute name index
//	//attribute_element.attribute_name_index_l = read_word(fp);
//      printf("%d", attribute_element.attribute_name_index_l);
//
//	// Leitura do attribute length
//	//attribute_element.attribute_length_l = read_dword(fp);
//
//	// Leitura do constant pool utilizando o attribute name index
//	cp_element = constant_pool[attribute_element.attribute_name_index_l - 1];
//	// O elemento no índice tem que ser do tipo CONSTANT_Utf8
//	printf("Attribute da vez: %s\n", cp_element.cp_union.constant_Utf8.bytes);
//	if(cp_element.tag == CONSTANT_Utf8) {
//		// Se o attribute for do tipo SourceFile
//		if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "SourceFile")) {
//			printf("Attribute: SourceFile\n");
//
//			attribute_element.attribute_union.attr_SourceFile.attribute_name_index = attribute_element.attribute_name_index_l;
//			printf("attribute_name_index:\n%04x\n", attribute_element.attribute_union.attr_SourceFile.attribute_name_index);
//
//			attribute_element.attribute_union.attr_SourceFile.attribute_length = attribute_element.attribute_length_l;
//			printf("attribute_length:\n%08x\n", attribute_element.attribute_union.attr_SourceFile.attribute_length);
//
//			// Leitura do sourcefile_index
//			attribute_element.attribute_union.attr_SourceFile.sourcefile_index = read_word(fp);
//			printf("Sourcefile_index:\n%04x\n", attribute_element.attribute_union.attr_SourceFile.sourcefile_index);
//		}
//
//		// Se o attribute for do tipo ConstantValue
//		if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "ConstantValue")) {
//			printf("Attribute: ConstantValue\n");
//
//			attribute_element.attribute_union.attr_ConstantValue.attribute_name_index = attribute_element.attribute_name_index_l;
//			printf("attribute_name_index:\n%04x\n", attribute_element.attribute_union.attr_ConstantValue.attribute_name_index);
//
//			attribute_element.attribute_union.attr_ConstantValue.attribute_length = attribute_element.attribute_length_l;
//			printf("attribute_length:\n%08x\n", attribute_element.attribute_union.attr_ConstantValue.attribute_length);
//
//			// Leitura do constantvalue_index
//			attribute_element.attribute_union.attr_ConstantValue.constantvalue_index = read_word(fp);
//			printf("Constantvalue_index:\n%04x\n", attribute_element.attribute_union.attr_ConstantValue.constantvalue_index);
//		}
//
//            // Se o attribute for do tipo Code
//            if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "Code")) {
//                  printf("Attribute: Code\n");
//
//                  attribute_element.attribute_union.attr_Code.attribute_name_index = attribute_element.attribute_name_index_l;
//                  printf("attribute_name_index:\n%04x\n", attribute_element.attribute_union.attr_Code.attribute_name_index);
//
//                  attribute_element.attribute_union.attr_Code.attribute_length = attribute_element.attribute_length_l;
//                  printf("attribute_length:\n%08x\n", attribute_element.attribute_union.attr_Code.attribute_length);
//
//                  attribute_element.attribute_union.attr_Code.max_stack = read_word(fp);
//
//                  attribute_element.attribute_union.attr_Code.max_locals = read_word(fp);
//
//                  attribute_element.attribute_union.attr_Code.code_length = read_dword(fp);
//
//                  attribute_element.attribute_union.attr_Code.code = (char*)malloc((attribute_element.attribute_union.attr_Code.code_length + 1)*sizeof(char));
//                  for (n = 0; n < attribute_element.attribute_union.attr_Code.code_length; n++) {
//                        attribute_element.attribute_union.attr_Code.code[n] = read_byte(fp);
//                  }
//                  attribute_element.attribute_union.attr_Code.code[attribute_element.attribute_union.attr_Code.code_length] = '\0';
//
//                  attribute_element.attribute_union.attr_Code.exception_table_length = read_word(fp);
//
//                  attribute_element.attribute_union.attr_Code.exception_table = new std::vector<exception_table_info>;
//                  for (n = 0; n < attribute_element.attribute_union.attr_Code.exception_table_length; n++) {
//                        exception_table_element.start_pc = read_word(fp);
//                        exception_table_element.end_pc = read_word(fp);
//                        exception_table_element.handler_pc = read_word(fp);
//                        exception_table_element.catch_type = read_word(fp);
//
//                        attribute_element.attribute_union.attr_Code.exception_table->push_back(exception_table_element);
//                  }
//
//                  attribute_element.attribute_union.attr_Code.attributes_count = read_word(fp);
//
//                  attribute_element.attribute_union.attr_Code.attributes = new std::vector<struct attribute_info_s>;
//                  for (n = 0; n < attribute_element.attribute_union.attr_Code.attributes_count; n++) {
//                        attribute_element_aux = read_attributes(fp, constant_pool);
//                        attribute_element.attribute_union.attr_Code.attributes->push_back(attribute_element_aux);
//                  }
//            }
//
//            // Se o attribute for do tipo Exceptions
//            if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "Exceptions")) {
//                    attribute_element.attribute_union.attr_Exceptions.exception_index_table = (std::vector<uint16_t>*)malloc(sizeof(std::vector<uint16_t>));
//                	printf("Attribute: Exceptions\n");
//                    attribute_element.attribute_union.attr_Exceptions.attribute_name_index = attribute_element.attribute_name_index_l;
//                    printf("attribute_name_index:\n%04x\n", attribute_element.attribute_union.attr_Exceptions.attribute_name_index);
//
//                    attribute_element.attribute_union.attr_Exceptions.attribute_length = attribute_element.attribute_length_l;
//                    printf("attribute_length:\n%08x\n", attribute_element.attribute_union.attr_Exceptions.attribute_length);
//
//                    int number_of_exceptions = attribute_element.attribute_union.attr_Exceptions.number_of_exceptions = read_word(fp);
//                    printf("number_of_exceptions: \n%x\n", number_of_exceptions);
//                    printf("Exception_index_table: \n");
//          			for(int i = 0; i < number_of_exceptions; i++ ){
//          				attribute_element.attribute_union.attr_Exceptions.exception_index_table->push_back( read_word(fp) );
//          				//printf("[%d]:%x - ",i, attribute_element.attribute_union.attr_Exceptions.exception_index_table[i]);
//          			}
//            }
//
//            // Se o attribute for do tipo InnerClasses
//            if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "InnerClasses")) {
//                  attribute_element.attribute_union.attr_InnerClasses.attribute_name_index = attribute_element.attribute_name_index_l;
//                  attribute_element.attribute_union.attr_InnerClasses.attribute_length = attribute_element.attribute_length_l;
//                  attribute_element.attribute_union.attr_InnerClasses.number_of_classes = read_word(fp);
//                  attribute_element.attribute_union.attr_InnerClasses.classes = new std::vector<classes_info>;
//                  for (n = 0; n < attribute_element.attribute_union.attr_InnerClasses.number_of_classes; n++) {
//                        classes_element.inner_class_info_index = read_word(fp);
//                        classes_element.outer_class_info_index = read_word(fp);
//                        classes_element.inner_name_index = read_word(fp);
//                        classes_element.inner_class_access_flags = read_word(fp);
//                        attribute_element.attribute_union.attr_InnerClasses.classes->push_back(classes_element);
//                  }
//            }
//
//            // Se o attribute for do tipo LineNumberTable
//            if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "LineNumberTable")) {
//                  attribute_element.attribute_union.attr_LineNumberTable.attribute_name_index = attribute_element.attribute_name_index_l;
//                  attribute_element.attribute_union.attr_LineNumberTable.attribute_length = attribute_element.attribute_length_l;
//                  attribute_element.attribute_union.attr_LineNumberTable.line_number_table_length = read_word(fp);
//                  attribute_element.attribute_union.attr_LineNumberTable.line_number_table = new std::vector<line_number_table_info>;
//                  for (n = 0; n < attribute_element.attribute_union.attr_LineNumberTable.line_number_table_length; n++) {
//                        line_number_table_element.start_pc = read_word(fp);
//                        line_number_table_element.line_number = read_word(fp);
//                        attribute_element.attribute_union.attr_LineNumberTable.line_number_table->push_back(line_number_table_element);
//                  }
//            }
//
//            // Se o attribute for do tipo LocalVariableTable
//            if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "LocalVariableTable")) {
//                  attribute_element.attribute_union.attr_LocalVariableTable.attribute_name_index = attribute_element.attribute_name_index_l;
//                  attribute_element.attribute_union.attr_LocalVariableTable.attribute_length = attribute_element.attribute_length_l;
//                  attribute_element.attribute_union.attr_LocalVariableTable.local_variable_table_length = read_word(fp);
//                  attribute_element.attribute_union.attr_LocalVariableTable.local_variable_table = new std::vector<local_variable_table_info>;
//                  for (n = 0; n < attribute_element.attribute_union.attr_LocalVariableTable.local_variable_table_length; n++) {
//                        local_variable_table_element.start_pc = read_word(fp);
//                        local_variable_table_element.length = read_word(fp);
//                        local_variable_table_element.name_index = read_word(fp);
//                        local_variable_table_element.descriptor_index = read_word(fp);
//                        local_variable_table_element.index = read_word(fp);
//                        attribute_element.attribute_union.attr_LocalVariableTable.local_variable_table->push_back(local_variable_table_element);
//                  }
//            }
//
//            // Se o attribute for do tipo LocalVariableTypeTable
//            if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "LocalVariableTypeTable")) {
//                  attribute_element.attribute_union.attr_LocalVariableTypeTable.attribute_name_index = attribute_element.attribute_name_index_l;
//                  attribute_element.attribute_union.attr_LocalVariableTypeTable.attribute_length = attribute_element.attribute_length_l;
//                  attribute_element.attribute_union.attr_LocalVariableTypeTable.local_variable_type_table_length = read_word(fp);
//                  attribute_element.attribute_union.attr_LocalVariableTypeTable.local_variable_type_table = new std::vector<local_variable_type_table_info>;
//                  for (n = 0; n < attribute_element.attribute_union.attr_LocalVariableTypeTable.local_variable_type_table_length; n++) {
//                        local_variable_type_table_element.start_pc = read_word(fp);
//                        local_variable_type_table_element.length = read_word(fp);
//                        local_variable_type_table_element.name_index = read_word(fp);
//                        local_variable_type_table_element.signature_index = read_word(fp);
//                        local_variable_type_table_element.index = read_word(fp);
//                        attribute_element.attribute_union.attr_LocalVariableTypeTable.local_variable_type_table->push_back(local_variable_type_table_element);
//                  }
//            }
//
//
//            // Se o attribute for do tipo Synthetic
//            if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "Synthetic")) {
//                  printf("Attribute: Synthetic\n");
//
//                  attribute_element.attribute_union.attr_Synthetic.attribute_name_index = attribute_element.attribute_name_index_l;
//                  printf("attribute_name_index:\n%04x\n", attribute_element.attribute_union.attr_Synthetic.attribute_name_index);
//
//                  attribute_element.attribute_union.attr_Synthetic.attribute_length = attribute_element.attribute_length_l;
//                  printf("attribute_length:\n%08x\n", attribute_element.attribute_union.attr_Synthetic.attribute_length);
//            }
//
//	}
//
//	// Se o elemento no índice não for do tipo CONSTANT_Utf8
//	else{
//		printf("Error! Attribute_name_index must point to CONSTANT_Utf8_info structure!\n");
//		exit(EXIT_FAILURE);
//	}
//
//	return attribute_element;
//}
