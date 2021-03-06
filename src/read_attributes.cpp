#include "../include/read_attributes.hpp"

attribute_info read_attributes(FILE *fp, std::vector<cp_info> constant_pool) {
	cp_info cp_element;
      line_number_table_info line_number_table_element;
	attribute_info attribute_element, attribute_element_aux;
      exception_table_info exception_table_element;
      local_variable_type_table_info local_variable_type_table_element;
      local_variable_table_info local_variable_table_element;
      classes_info classes_element;

	// Leitura do attribute name index
	attribute_element.attribute_name_index_l = read_word(fp);

	// Leitura do attribute length
	attribute_element.attribute_length_l = read_dword(fp);

	// Leitura do constant pool utilizando o attribute name index
	cp_element = constant_pool[attribute_element.attribute_name_index_l - 1];
	// O elemento no índice tem que ser do tipo CONSTANT_Utf8
	if(cp_element.tag == CONSTANT_Utf8) {
		// Se o attribute for do tipo SourceFile
		if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "SourceFile")) {

			attribute_element.attribute_union.attr_SourceFile.attribute_name_index = attribute_element.attribute_name_index_l;

			attribute_element.attribute_union.attr_SourceFile.attribute_length = attribute_element.attribute_length_l;

			// Leitura do sourcefile_index
			attribute_element.attribute_union.attr_SourceFile.sourcefile_index = read_word(fp);
		}else if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "ConstantValue")) {
			attribute_element.attribute_union.attr_ConstantValue.attribute_name_index = attribute_element.attribute_name_index_l;

			attribute_element.attribute_union.attr_ConstantValue.attribute_length = attribute_element.attribute_length_l;

			// Leitura do constantvalue_index
			attribute_element.attribute_union.attr_ConstantValue.constantvalue_index = read_word(fp);
		}else if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "Code")) {// Se o attribute for do tipo Code
                  attribute_element.attribute_union.attr_Code.attribute_name_index = attribute_element.attribute_name_index_l;
                  attribute_element.attribute_union.attr_Code.attribute_length = attribute_element.attribute_length_l;
                  attribute_element.attribute_union.attr_Code.max_stack = read_word(fp);

                  attribute_element.attribute_union.attr_Code.max_locals = read_word(fp);

                  attribute_element.attribute_union.attr_Code.code_length = read_dword(fp);

                  attribute_element.attribute_union.attr_Code.code = (uint8_t*)malloc((attribute_element.attribute_union.attr_Code.code_length + 1)*sizeof(uint8_t));

                  for (uint32_t n = 0; n < attribute_element.attribute_union.attr_Code.code_length; n++) {
                        attribute_element.attribute_union.attr_Code.code[n] = read_byte(fp);
                  }
                  attribute_element.attribute_union.attr_Code.code[attribute_element.attribute_union.attr_Code.code_length] = '\0';

                  attribute_element.attribute_union.attr_Code.exception_table_length = read_word(fp);

                  attribute_element.attribute_union.attr_Code.exception_table = new std::vector<exception_table_info>;
                  for (uint32_t n = 0; n < attribute_element.attribute_union.attr_Code.exception_table_length; n++) {
                        exception_table_element.start_pc = read_word(fp);
                        exception_table_element.end_pc = read_word(fp);
                        exception_table_element.handler_pc = read_word(fp);
                        exception_table_element.catch_type = read_word(fp);

                        attribute_element.attribute_union.attr_Code.exception_table->push_back(exception_table_element);
                  }

                  attribute_element.attribute_union.attr_Code.attributes_count = read_word(fp);

                  attribute_element.attribute_union.attr_Code.attributes = new std::vector<struct attribute_info_s>;
                  for (uint32_t n = 0; n < attribute_element.attribute_union.attr_Code.attributes_count; n++) {
                        attribute_element_aux = read_attributes(fp, constant_pool);
                        attribute_element.attribute_union.attr_Code.attributes->push_back(attribute_element_aux);
                  }
            }else if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "Exceptions")) { // Se o attribute for do tipo Exceptions
                    attribute_element.attribute_union.attr_Exceptions.exception_index_table = new std::vector<uint16_t>();
                    attribute_element.attribute_union.attr_Exceptions.attribute_name_index = attribute_element.attribute_name_index_l;

                    attribute_element.attribute_union.attr_Exceptions.attribute_length = attribute_element.attribute_length_l;

                    int number_of_exceptions = attribute_element.attribute_union.attr_Exceptions.number_of_exceptions = read_word(fp);
          			for(int i = 0; i < number_of_exceptions; i++ ){
          				attribute_element.attribute_union.attr_Exceptions.exception_index_table->push_back( read_word(fp) );
          			}
            }else if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "InnerClasses")) {// Se o attribute for do tipo InnerClasses
                  attribute_element.attribute_union.attr_InnerClasses.attribute_name_index = attribute_element.attribute_name_index_l;
                  attribute_element.attribute_union.attr_InnerClasses.attribute_length = attribute_element.attribute_length_l;
                  attribute_element.attribute_union.attr_InnerClasses.number_of_classes = read_word(fp);
                  attribute_element.attribute_union.attr_InnerClasses.classes = new std::vector<classes_info>;
                  for (uint32_t n = 0; n < attribute_element.attribute_union.attr_InnerClasses.number_of_classes; n++) {
                        classes_element.inner_class_info_index = read_word(fp);
                        classes_element.outer_class_info_index = read_word(fp);
                        classes_element.inner_name_index = read_word(fp);
                        classes_element.inner_class_access_flags = read_word(fp);
                        attribute_element.attribute_union.attr_InnerClasses.classes->push_back(classes_element);
                  }
            }else if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "LineNumberTable")) {// Se o attribute for do tipo LineNumberTable
                  attribute_element.attribute_union.attr_LineNumberTable.attribute_name_index = attribute_element.attribute_name_index_l;
                  attribute_element.attribute_union.attr_LineNumberTable.attribute_length = attribute_element.attribute_length_l;
                  attribute_element.attribute_union.attr_LineNumberTable.line_number_table_length = read_word(fp);
                  attribute_element.attribute_union.attr_LineNumberTable.line_number_table = new std::vector<line_number_table_info>;
                  for (uint32_t n = 0; n < attribute_element.attribute_union.attr_LineNumberTable.line_number_table_length; n++) {
                        line_number_table_element.start_pc = read_word(fp);
                        line_number_table_element.line_number = read_word(fp);
                        attribute_element.attribute_union.attr_LineNumberTable.line_number_table->push_back(line_number_table_element);
                  }
            }else if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "LocalVariableTable")) {// Se o attribute for do tipo LocalVariableTable
                  attribute_element.attribute_union.attr_LocalVariableTable.attribute_name_index = attribute_element.attribute_name_index_l;
                  attribute_element.attribute_union.attr_LocalVariableTable.attribute_length = attribute_element.attribute_length_l;
                  attribute_element.attribute_union.attr_LocalVariableTable.local_variable_table_length = read_word(fp);
                  attribute_element.attribute_union.attr_LocalVariableTable.local_variable_table = new std::vector<local_variable_table_info>;
                  for (uint32_t n = 0; n < attribute_element.attribute_union.attr_LocalVariableTable.local_variable_table_length; n++) {
                        local_variable_table_element.start_pc = read_word(fp);
                        local_variable_table_element.length = read_word(fp);
                        local_variable_table_element.name_index = read_word(fp);
                        local_variable_table_element.descriptor_index = read_word(fp);
                        local_variable_table_element.index = read_word(fp);
                        attribute_element.attribute_union.attr_LocalVariableTable.local_variable_table->push_back(local_variable_table_element);
                  }
            }else if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "LocalVariableTypeTable")) {// Se o attribute for do tipo LocalVariableTypeTable
                  attribute_element.attribute_union.attr_LocalVariableTypeTable.attribute_name_index = attribute_element.attribute_name_index_l;
                  attribute_element.attribute_union.attr_LocalVariableTypeTable.attribute_length = attribute_element.attribute_length_l;
                  attribute_element.attribute_union.attr_LocalVariableTypeTable.local_variable_type_table_length = read_word(fp);
                  attribute_element.attribute_union.attr_LocalVariableTypeTable.local_variable_type_table = new std::vector<local_variable_type_table_info>;
                  for (uint32_t n = 0; n < attribute_element.attribute_union.attr_LocalVariableTypeTable.local_variable_type_table_length; n++) {
                        local_variable_type_table_element.start_pc = read_word(fp);
                        local_variable_type_table_element.length = read_word(fp);
                        local_variable_type_table_element.name_index = read_word(fp);
                        local_variable_type_table_element.signature_index = read_word(fp);
                        local_variable_type_table_element.index = read_word(fp);
                        attribute_element.attribute_union.attr_LocalVariableTypeTable.local_variable_type_table->push_back(local_variable_type_table_element);
                  }
            }else if(!strcmp(cp_element.cp_union.constant_Utf8.bytes, "Synthetic")) {// Se o attribute for do tipo Synthetic

                  attribute_element.attribute_union.attr_Synthetic.attribute_name_index = attribute_element.attribute_name_index_l;
                  attribute_element.attribute_union.attr_Synthetic.attribute_length = attribute_element.attribute_length_l;
            }else {
                read_word(fp);//posição na constatnt pool, joga fora
                uint32_t smtlen8D = read_dword(fp);
                fseek(fp, smtlen8D, SEEK_CUR);
            }
//                attribute_element.attribute_union.attr_StackMapTable.attribute_name_index = attribute_element.attribute_name_index_l;
//                attribute_element.attribute_union.attr_StackMapTable.attribute_length = attribute_element.attribute_length_l;
//                uint32_t nEntries = attribute_element.attribute_union.attr_StackMapTable.number_of_entries = read_dword(fp);
//                attribute_element.attribute_union.attr_StackMapTable.entries = new vector<stack_map_frame>;
//                stack_map_frame stackMapFrame;
//                for(uint32_t i = 0; i < nEntries; i++){
//                        stackMapFrame.tag = read_byte(fp);
//                        switch(stackMapFrame.tag){
//                            case SAME_FRAME:
//                                    stackMapFrame.stack_map_frame.same_frame.frame_type = SAME;
//                                    attribute_element.attribute_union.attr_StackMapTable.entries->push_back(stackMapFrame);
//                                break;
//                            case SAME_LOCALS_1_STACK_ITEM_FRAME:
//                                    stackMapFrame.stack_map_frame.sl1_sif = SAME_LOCALS_1_STACK_ITEM_FRAME;
//
//                                    Verification_type_info verTypeInfo;
//                                    verTypeInfo.tag = SAME_LOCALS_1_STACK_ITEM;
//                                    verTypeInfo.verification_type_u =
//
//                                    stackMapFrame.stack_map_frame.sl1_sif.stack_
//                                    attribute_element.attribute_union.attr_StackMapTable.entries->push_back(stackMapFrame);
//                                break;
//                            case SAME_LOCALS_1_STACK_ITEM_FRAME_EXTENDED:
//                                break;
//                            case CHOP_FRAME:
//                                break;
//                            case SAME_FRAME_EXTENDED:
//                                break;
//                            case APPEND_FRAME:
//                                break;
//                            case FULL_FRAME:
//                                break;
//                        }
//                }

	}

	// Se o elemento no índice não for do tipo CONSTANT_Utf8
	else{
		printf("Error! Attribute_name_index must point to CONSTANT_Utf8_info structure!\n");
		exit(EXIT_FAILURE);
	}

	return attribute_element;
}
