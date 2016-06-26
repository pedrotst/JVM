#ifndef CLASS_FILE
#define CLASS_FILE

#include <string.h>
#include <string>
#include <map>
#include <exception>
#include "../include/structs.hpp"

class ClassFile{
public:
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

	std::string getSource();
	std::string getClassName();
	std::string getCpoolUtf8(int index);
	//retorna um bind entre o nome e o tipo
	std::map<std::string, std::string> getFieldsNamesTypes();

	// Descrição:
	//    Procura o método main em uma classe.
	//
	// Retorno:
	//    Se a main for encontrada, retorna o index do método main na classe.
	//
	//    Se a main não for encontrada, retorna -1.
	//
	int findMain();

	// Descrição:
	//    Resolve uma referência para um nome presente na constant_pool.
	//
	// Parâmetros:
	//    int name_index: Um index da constant_pool.
	//
	// Retorno:
	//    Se o index apontar para uma string, retorna a string.
	//
	//    Se o index não apontar para uma string, retorna NULL.
	//
	char* getName(int name_index);

	// Descrição:
	//    Retorna o atributo Code de um dos métodos da classe.
	//
	// Parâmetros:
	//    method_info *method: ponteiro para o método que terá seu atributo
	//	Code obtido.
	//
	// Retorno:
	//    Retorna um ponteiro para o atributo Code do método.
	//
	//    Se o método não possuir um atributo code, retorna NULL.
	//
	Code_attribute* getCodeAttr(method_info *method);
};

#endif //CLASS_FILE
