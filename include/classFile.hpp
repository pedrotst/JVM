#ifndef CLASS_FILE
#define CLASS_FILE

#include <stdio.h>
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
    /** \fn getCpoolClass Busca na Constant Pool o nome da Classe a partir do index
    *
    *   \param index Index utilizado para encontrar o ClassName
    *
    *   \return Retorna o nome da classe em format String
    *
    *   \brief O index primeiro localiza o ClassName no Constant Pool que irá indicar
    *           o index do UTF-8 que contem o nome da classe
    */
    std::string getCpoolClass(int index);

	/** \brief Procura o método main em uma classe.
	*
	*   \return Se a main for encontrada, retorna o index do método main na classe. Se a main não for encontrada, retorna -1.
	*/
	int findMain();

	/** \brief Resolve uma referência para um nome presente na constant_pool.
	*
	*   \param int name_index: Um index da constant_pool.
	*
	*   \return Se o index apontar para uma string, retorna a string. Se o index não apontar para uma string, retorna NULL.
	*/
	char* getName(int name_index);

	/** \brief Retorna o atributo Code de um dos métodos da classe.
	*
	*   \param method_info *method: ponteiro para o método que terá seu atributo Code obtido.
	*
	*   \return Retorna um ponteiro para o atributo Code do método. Se o método não possuir um atributo code, retorna NULL.
	*/
	Code_attribute* getCodeAttr(method_info *method);
};

#endif //CLASS_FILE
