#include <vector>

// Constant poll tags
typedef enum cp_tag_e {
	CONSTANT_Class = 7,
	CONSTANT_Fieldref = 9,
	CONSTANT_Methodref = 10,
	CONSTANT_InterfaceMethodref = 11,
	CONSTANT_String = 8,
	CONSTANT_Integer = 3,
	CONSTANT_Float = 4,
	CONSTANT_Long = 5,
	CONSTANT_Double = 6,
	CONSTANT_NameAndType = 12,
	CONSTANT_Utf8 = 1,
	CONSTANT_MethodHandle = 15,
	CONSTANT_MethodType = 16,
	CONSTANT_InvokeDynamic = 18
} cp_tag;

// Constant pool structures
typedef struct CONSTANT_Class_info_s {
	cp_tag tag;
	uint16_t name_index;
} CONSTANT_Class_info;

typedef struct CONSTANT_Fieldref_info_s {
	cp_tag tag;
	uint16_t class_index;
	uint16_t name_and_type_index;
} CONSTANT_Fieldref_info;

typedef struct CONSTANT_Methodref_info_s {
	cp_tag tag;
	uint16_t class_index;
	uint16_t name_and_type_index;
} CONSTANT_Methodref_info;

typedef struct CONSTANT_InterfaceMethodref_info_s {
	cp_tag tag;
	uint16_t class_index;
	uint16_t name_and_type_index;
} CONSTANT_InterfaceMethodref_info;

typedef struct CONSTANT_String_info_s {
	cp_tag tag;
	uint16_t string_index;
} CONSTANT_String_info;

typedef struct CONSTANT_Integer_info_s {
	cp_tag tag;
	uint32_t bytes;
} CONSTANT_Integer_info;

typedef struct CONSTANT_Float_info_s {
	cp_tag tag;
	uint32_t bytes;
} CONSTANT_Float_info;

typedef struct CONSTANT_Long_info_s {
	cp_tag tag;
	uint32_t high_bytes;
	uint32_t low_bytes;
} CONSTANT_Long_info;

typedef struct CONSTANT_Double_info_s {
	cp_tag tag;
	uint32_t high_bytes;
	uint32_t low_bytes;
} CONSTANT_Double_info;

typedef struct CONSTANT_NameAndType_info_s {
	cp_tag tag;
	uint16_t name_index;
	uint16_t descriptor_index;
} CONSTANT_NameAndType_info;

typedef struct CONSTANT_Utf8_info_s {
	cp_tag tag;
	uint16_t length;
	char *bytes;
} CONSTANT_Utf8_info;

typedef struct CONSTANT_MethodHandle_info_s {
	cp_tag tag;
	uint8_t reference_kind;
	uint16_t reference_index;
} CONSTANT_MethodHandle_info;

typedef struct CONSTANT_MethodType_info_s {
	cp_tag tag;
	uint16_t descriptor_index;
} CONSTANT_MethodType_info;

typedef struct CONSTANT_InvokeDynamic_info_s {
	cp_tag tag;
	uint16_t bootstrap_method_attr_index;
	uint16_t name_and_type_index;
} CONSTANT_InvokeDynamic_info;

typedef union cp_info_u {
	CONSTANT_Class_info 			constant_class;
	CONSTANT_Fieldref_info 			constant_fieldref;
	CONSTANT_Methodref_info 		constant_methodref;
	CONSTANT_InterfaceMethodref_info 	constant_interfaceMethodref;
	CONSTANT_String_info 			constant_string;
	CONSTANT_Integer_info 			constant_integer;
	CONSTANT_Float_info 			constant_float;
	CONSTANT_Long_info 			constant_long;
	CONSTANT_Double_info 			constant_double;
	CONSTANT_NameAndType_info 		constant_nameAndType;
	CONSTANT_Utf8_info 			constant_Utf8;
	CONSTANT_MethodHandle_info 		constant_methodHandle;
	CONSTANT_MethodType_info 		constant_methodType;
	CONSTANT_InvokeDynamic_info 		constant_invokeDynamic;
} cpInfo_u;

typedef enum AccessClass {
	ACC_PUBLIC = 0x0001,
	ACC_FINAL = 0x0010,
	ACC_SUPER = 0x0020,
	ACC_INTERFACE = 0x0200,
	ACC_ABSTRACT = 0x0400,
	ACC_SYNTHETIC = 0x1000,
	ACC_ANNOTATION = 0x2000,
	ACC_ENUM = 0x4000
} ACC_FLAGS;

typedef struct cp_info_s {
	cp_tag tag;
	cpInfo_u cp_union;
} cp_info;

typedef struct attribute_info_s {
	uint16_t attribute_name_index;
	uint32_t attribute_length;
	std::vector<uint8_t> info;
} attribute_info;

typedef struct field_info_s {
	uint16_t access_flags;
	uint16_t name_index;
	uint16_t descriptor_index;
	uint16_t attributes_count;
	std::vector<attribute_info> atributes;
} field_info;

typedef struct method_info_s {
	uint16_t access_flags;
	uint16_t name_index;
	uint16_t descriptor_index;
	uint16_t attributes_count;
	std::vector<attribute_info> attributes;
} method_info;

typedef struct ClassFile_s {
	uint32_t magic;
	uint16_t minor_version;
	uint16_t major_version;
	uint32_t constant_pool_count;
	std::vector<cp_info> constant_pool;
	uint16_t access_flags;
	uint16_t this_class;
	uint16_t super_class;
	uint16_t interfaces_count;
	std::vector<uint16_t> interfaces;
	uint16_t fields_count;
	std::vector<field_info> fields;
	uint16_t methods_count;
	std::vector<method_info> methods;
	uint16_t attributes_count;
	std::vector<attribute_info> attributes;
} ClassFile;
