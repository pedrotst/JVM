#ifndef _ATTRIBUTES_HPP
#define _ATTRIBUTES_HPP

#include <vector>
#include <stdint.h>

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

/** \class exception_table_info
* \brief Definida para ser utilizada no atributo Code_attribute
*/
typedef struct exception_table_info_s {
      uint16_t start_pc;
      uint16_t end_pc;
      uint16_t handler_pc;
      uint16_t catch_type;
} exception_table_info;


/** \class line_number_table_info
* \brief Definida para ser utilizada no atributo LineNumberTable_attribute
*/
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

//Tudo aqui é StackMapTable
//https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html#jvms-4.7.4
//typedef enum stack_map_frame_e{
//    SAME = 0,
//    SAME_LOCALS_1_STACK_ITEM,
//    SAME_LOCALS_1_STACK_ITEM_EXTENDED,
//    CHOP,
//    SAME_EXTENDED,
//    APPEND,
//    FULL
//}Stack_map_frame_tag;
//
//typedef enum stack_map_frame_e{
//    SAME_FRAME = 0,
//    SAME_LOCALS_1_STACK_ITEM_FRAME,
//    SAME_LOCALS_1_STACK_ITEM_FRAME_EXTENDED,
//    CHOP_FRAME,
//    SAME_FRAME_EXTENDED,
//    APPEND_FRAME,
//    FULL_FRAME
//}Stack_map_frame_type_tag;
//
//typedef enum verification_type_info_e {
//    TOP_VARIABLE = 0,
//    INTEGER_VARIABLE,
//    FLOAT_VARIABLE,
//    LONG_VARIABLE,
//    DOUBLE_VARIABLE,
//    NULL_VARIABLE,
//    UNINITIALIZEDTHIS_VARIABLE,
//    OBJECT_VARIABLE,
//    UNINITIALIZED_VARIABLE
//}Ver_type_info_e;
//
//typedef struct object_variable_info_s {
//    uint8_t tag; // = ITEM_Object; /* 7 */
//    uint16_t cpool_index;
//}Object_variable_info;
//
//typedef struct uninitialized_variable_info_s {
//    uint8_t tag; // = ITEM_Uninitialized /* 8 */
//    uint16_t offset;
//}Uninitialized_variable_info;
//
//typedef union verification_type_info_u {
//    uint8_t Top_variable_info;
//    uint8_t Integer_variable_info;
//    uint8_t Float_variable_info;
//    uint8_t Long_variable_info;
//    uint8_t Double_variable_info;
//    uint8_t Null_variable_info;
//    uint8_t UninitializedThis_variable_info;
//    Object_variable_info            object_variable_info;
//    Uninitialized_variable_info     Uninitialized_variable_info;
//}Ver_type_info_u;
//
//typedef struct verification_type_s{
//    Ver_type_info_e tag;
//    Ver_type_info_u verification_type_u;
//}Verification_type_info;
//
//typedef struct same_frame_s{
//    uint8_t frame_type; //= SAME
//}Same_frame;
//
//typedef struct same_locals_1_stack_item_frame_s {
//    uint8_t frame_type; //= SAME_LOCALS_1_STACK_ITEM /* 64-127 */
//    Verification_type_info stack_;//[1];
//}Same_locals_1_stack_item_frame;
//
//typedef struct same_locals_1_stack_item_frame_extended_s {
//    uint8_t frame_type;  //= SAME_LOCALS_1_STACK_ITEM_EXTENDED/* 247 */
//    uint16_t offset_delta;
//    Verification_type_info stack_;//[1];
//}Same_locals_1_stack_item_frame_extended;
//
//typedef struct chop_frame_s {
//    uint8_t frame_type; // = CHOP; /* 248-250 */
//    uint16_t offset_delta;
//}Chop_frame;
//
//typedef struct same_frame_extended_s {
//    uint8_t frame_type;// = SAME_FRAME_EXTENDED; /* 251 */
//    uint16_t offset_delta;
//}Same_frame_extended;
//
//typedef struct append_frame_s {
//    uint8_t frame_type;// = APPEND; /* 252-254 */
//    uint16_t offset_delta;
//    std::vector<Verification_type_info> *locals;//[frame_type - 251];
//}Append_frame;
//
//typedef struct full_frame_s {
//    uint8_t frame_type;// = FULL_FRAME; /* 255 */
//    uint16_t offset_delta;
//    uint16_t number_of_locals;
//    std::vector<Verification_type_info> *locals;
//    uint16_t number_of_stack_items;
//    std::vector<Verification_type_info> *stack_;
//}Full_frame;
//
//typedef union stack_map_frame_u{
//    Same_frame      						same_frame;
//    Same_locals_1_stack_item_frame			sl1_sif;
//    Same_locals_1_stack_item_frame_extended sl1_sife;
//    Chop_frame      						chop_frame;
//    same_frame_extended 					sfe;
//    Append_frame    						append_frame;
//    Full_frame      						full_frame;
//}Stack_map_frame_u;
//
//typedef struct stack_map_frame_s{
//    Stack_map_frame_tag tag;
//    Stack_map_frame_u stack_map_frame;
//}stack_map_frame;
//
//typedef struct StackMapTable_attribute_s {
//    uint16_t        attribute_name_index;
//    uint32_t        attribute_length;
//    uint16_t        number_of_entries;
//    std::vector<stack_map_frame> *entries;
//}StacMapTable_attribute;
//Fim stackMapTable

/** \class local_variable_table_info
* \brief Definida para ser utilizada no atributo LocalVariableTable_attribute
*/
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

/** \class local_variable_type_table_info
* \brief Definida para ser utilizada no atributo LocalVariableTypeTable_attribute
*/
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


struct attribute_info_s;

typedef struct Code_attribute_s {
       uint16_t attribute_name_index;
       uint32_t attribute_length;
       uint16_t max_stack;
       uint16_t max_locals;
       uint32_t code_length;
       uint8_t *code;
       uint16_t exception_table_length;
       std::vector<exception_table_info> *exception_table;
       uint16_t attributes_count;
       std::vector<struct attribute_info_s> *attributes;
} Code_attribute;

/** \class classes_info
* \brief Definida para ser utilizada no atributo InnerClasses_attribute
*/
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

 typedef struct tions_attribute_s {
        uint16_t attribute_name_index;
        uint32_t attribute_length;
        uint16_t number_of_exceptions;
        std::vector<uint16_t> *exception_index_table;
 } Exceptions_attribute;

typedef union attribute_type_u {
      InnerClasses_attribute              attr_InnerClasses;
      LineNumberTable_attribute           attr_LineNumberTable;
      LocalVariableTable_attribute        attr_LocalVariableTable;
      LocalVariableTypeTable_attribute    attr_LocalVariableTypeTable;
      ConstantValue_attribute             attr_ConstantValue;
      SourceFile_attribute                attr_SourceFile;
      Synthetic_attribute                 attr_Synthetic;
      Code_attribute                      attr_Code;
      Exceptions_attribute                attr_Exceptions;
//      StacMapTable_attribute              attr_StackMapTable;
} attributeType_u;

typedef struct attribute_info_s {
	uint16_t attribute_name_index_l;
	uint32_t attribute_length_l;
	attributeType_u attribute_union;
} attribute_info;

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

typedef struct Deprecated_attribute_s {
      uint16_t attribute_name_index;
      uint32_t attribute_length;
} Deprecated_attribute;

#endif // _ATTRIBUTES_HPP
