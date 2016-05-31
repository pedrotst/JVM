#ifndef _ATTRIBUTES_HPP
#define _ATTRIBUTES_HPP

#include <vector>
#include <stdint.h>
//#include "structs.hpp"

typedef struct ConstantValue_attribute_s {
       uint16_t attribute_name_index;
       uint32_t attribute_length;
       uint16_t constantvalue_index;
} ConstantValue_attribute;

typedef struct SourceFile_attribute_s {
       uint16_t attribute_name_index;
       uint32_t attribute_length;
       uint16_t sourcefile_index;
} SourceFile_attribute;

typedef struct Synthetic_attribute_s {
      uint16_t attribute_name_index;
      uint32_t attribute_length;
} Synthetic_attribute;

// Definida para ser utilizada no atributo Code_attribute
typedef struct exception_table_info_s {
      uint16_t start_pc;
      uint16_t end_pc;
      uint16_t handler_pc;
      uint16_t catch_type;
} exception_table_info;

// Definida para ser utilizada no atributo LineNumberTable_attribute
typedef struct line_number_table_info_s {
      uint16_t start_pc;
      uint16_t line_number;
} line_number_table_info;

typedef struct LineNumberTable_attribute_s {
       uint16_t attribute_name_index;
       uint32_t attribute_length;
       uint16_t line_number_table_length;
       std::vector<line_number_table_info> *line_number_table;
} LineNumberTable_attribute;

// Definida para ser utilizada no atributo LocalVariableTable_attribute
typedef struct local_variable_table_info_s {
      uint16_t start_pc;
      uint16_t length;
      uint16_t name_index;
      uint16_t descriptor_index;
      uint16_t index;
} local_variable_table_info;

typedef struct LocalVariableTable_attribute_s {
      uint16_t attribute_name_index;
      uint32_t attribute_length;
      uint16_t local_variable_table_length;
      std::vector<local_variable_table_info> *local_variable_table;
} LocalVariableTable_attribute;

// Definida para ser utilizada no atributo LocalVariableTypeTable_attribute
typedef struct local_variable_type_table_info_s {
      uint16_t start_pc;
      uint16_t length;
      uint16_t name_index;
      uint16_t signature_index;
      uint16_t index;
} local_variable_type_table_info;

typedef struct LocalVariableTypeTable_attribute_s {
      uint16_t attribute_name_index;
      uint32_t attribute_length;
      uint16_t local_variable_type_table_length;
      std::vector<local_variable_type_table_info> *local_variable_type_table;
} LocalVariableTypeTable_attribute;

// typedef union attribute_type_code_u {
//       LineNumberTable_attribute           attr_LineNumberTable;
//       LocalVariableTable_attribute        attr_LocalVariableTable;
//       LocalVariableTypeTable_attribute    attr_LocalVariableTypeTable;
//       //StackMapTable_attribute           attr_StackMapTable;
// } attributeTypeCode_u;

// typedef struct attribute_info_code_s {
// 	uint16_t attribute_name_index;
// 	uint32_t attribute_length;
// 	attributeTypeCode_u attr_TypeCode_u;
// } attribute_info_code;

struct attribute_info_s;

typedef struct Code_attribute_s {
       uint16_t attribute_name_index;
       uint32_t attribute_length;
       uint16_t max_stack;
       uint16_t max_locals;
       uint32_t code_length;
       char *code;
       uint16_t exception_table_length;
       std::vector<exception_table_info> *exception_table;
       uint16_t attributes_count;
       std::vector<struct attribute_info_s> *attributes;
} Code_attribute;

// Definida para ser utilizada no atributo InnerClasses_attribute
typedef struct classes_info_s {
      uint16_t inner_class_info_index;
      uint16_t outer_class_info_index;
      uint16_t inner_name_index;
      uint16_t inner_class_access_flags;
} classes_info;

typedef struct InnerClasses_attribute_s {
      uint16_t attribute_name_index;
      uint32_t attribute_length;
      uint16_t number_of_classes;
      std::vector<classes_info> *classes;
} InnerClasses_attribute;

typedef union attribute_type_u {
      InnerClasses_attribute              attr_InnerClasses;
      LineNumberTable_attribute           attr_LineNumberTable;
      LocalVariableTable_attribute        attr_LocalVariableTable;
      LocalVariableTypeTable_attribute    attr_LocalVariableTypeTable;
      ConstantValue_attribute             attr_ConstantValue;
      SourceFile_attribute                attr_SourceFile;
      Synthetic_attribute                 attr_Synthetic;
      Code_attribute                      attr_Code;
} attributeType_u;

typedef struct attribute_info_s {
	uint16_t attribute_name_index_l;
	uint32_t attribute_length_l;
	attributeType_u attribute_union;
} attribute_info;


// typedef struct StackMapTable_attribute_s {
//       uint16_t              attribute_name_index;
//       uint32_t              attribute_length;
//       uint16_t              number_of_entries;
//       stack_map_frame entries[number_of_entries];
// } StackMapTable_attribute;


// typedef struct Exceptions_attribute_s {
//        uint16_t attribute_name_index;
//        uint32_t attribute_length;
//        uint16_t number_of_exceptions;
//        uint16_t exception_index_table[number_of_exceptions];
// } Exceptions_attribute;

typedef struct EnclosingMethod_attribute_s {
       uint16_t attribute_name_index;
       uint32_t attribute_length;
       uint16_t class_index;
       uint16_t method_index;
 } EnclosingMethod_attribute;

typedef struct Signature_attribute_s {
      uint16_t attribute_name_index;
      uint32_t attribute_length;
      uint16_t signature_index;
} Signature_attribute;

// typedef struct SourceDebugExtension_attribute_s {
//       uint16_t attribute_name_index;
//       uint32_t attribute_length;
//       uint8_t debug_extension[attribute_length];
// } SourceDebugExtension_attribute;

typedef struct Deprecated_attribute_s {
      uint16_t attribute_name_index;
      uint32_t attribute_length;
} Deprecated_attribute;

// typedef struct RuntimeVisibleAnnotations_attribute_s {
//        uint16_t         attribute_name_index;
//        uint32_t         attribute_length;
//        uint16_t         num_annotations;
//        annotation annotations[num_annotations];
// } RuntimeVisibleAnnotations_attribute;

// typedef struct RuntimeInvisibleAnnotations_attribute_s {
//        uint16_t         attribute_name_index;
//        uint32_t         attribute_length;
//        uint16_t         num_annotations;
//        annotation annotations[num_annotations];
// } RuntimeInvisibleAnnotations_attribute;

// typedef struct RuntimeVisibleParameterAnnotations_attribute_s {
//        uint16_t attribute_name_index;
//        uint32_t attribute_length;
//        uint8_t num_parameters;
//        {   uint16_t         num_annotations;
//            annotation annotations[num_annotations];
//        } parameter_annotations[num_parameters];
//  } RuntimeVisibleParameterAnnotations_attribute;

// typedef struct RuntimeInvisibleParameterAnnotations_attribute_s {
//               uint16_t attribute_name_index;
//               uint32_t attribute_length;
//               uint8_t num_parameters;
//               {   uint16_t         num_annotations;
//                   annotation annotations[num_annotations];
//               } parameter_annotations[num_parameters];
//         } RuntimeInvisibleParameterAnnotations_attribute;


// typedef struct AnnotationDefault_attribute_s {
//               uint16_t            attribute_name_index;
//               uint32_t            attribute_length;
//               element_value default_value;
// } AnnotationDefault_attribute;

// typedef struct BootstrapMethods_attribute {
//        uint16_t attribute_name_index;
//        uint32_t attribute_length;
//        uint16_t num_bootstrap_methods;
//        {   uint16_t bootstrap_method_ref;
//            uint16_t num_bootstrap_arguments;
//            uint16_t bootstrap_arguments[num_bootstrap_arguments];
//        } bootstrap_methods[num_bootstrap_methods];
// } BootstrapMethods_attribute;

#endif // _ATTRIBUTES_HPP
