#ifndef CLASS_FILE
#define CLASS_FILE

#include <stdio.h>
#include <string.h>
#include <string>
#include <map>
#include <exception>
#include "../include/structs.hpp"

/** \class ClassFile
* \brief ver https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html#jvms-4.4
*/

using namespace std;
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


	/** \fn getSource
	* \return retorna o arquivo que gerou esta classe
	*/
	std::string getSource();

	/** \fn getMethodName
	* \return retorna o nome do método n
	*/
	std::string getMethodName(int n);

	/** \fn getClassName
	* \return retorna o nome desta classe
	*/
	std::string getClassName();
	/** \fn getCpoolUtf8
	* \return retorna o valor da posicao index -1 da constant pool
	* assume-se que ha um utf8 nesta posicao
	*/
	std::string getCpoolUtf8(int index);
	//
	/** \fn getFieldsNamesTypes
	* \brief retorna um bind entre o nome e o tipo de todas fields nao estaticas da classe
	*/
	std::map<std::string, std::string> getFieldsNamesTypes();

	/** \fn getStaticFieldsNamesTypes
	* \brief retorna um bind entre o nome e o tipo de todas fields estaticas da classe
	*/
	std::map<std::string, std::string> getStaticFieldsNamesTypes();



    /** \fn getCpoolClass Busca na Constant Pool o nome da Classe a partir do index
    *
    *   \param index Index utilizado para encontrar o ClassName
    *
    *   \return Retorna o nome da classe em format String
    *
    *   \brief O index primeiro localiza o ClassName no Constant Pool que irá indicar
    *           o index do UTF-8 que contem o nome da classe
    */
    string getCpoolClass(int index);

    /** \fn getCpoolInterfaceMethod
    *   \brief Busca na Constant Pool o nome e o tipo do método a partir do index
    *
    *   \param index Index utilizado para encontrar o método da interface
    *   \param invoking_class referencia para string onde será escrito o nome da classe a ser invocada
    *   \param method_name referencia para string onde será escrito o nome do método
    *   \param descriptor referencia para string onde será escrito o descritor do método
    *
    *   \return Retorna o nome o nome e o tipo de retorno da classe no formato invoking_class.nome:tipo
    *
    */
    string getCpoolInterfaceMethod(int index, string &invoking_class, string &method_name, string &descriptor);


    /** \fn getCpoolMethod
    *   \brief Busca na Constant Pool o nome e o tipo do método a partir do index
    *
    *   \param index Index utilizado para encontrar o método
    *   \param invoking_class referencia para string onde será escrito o nome da classe a ser invocada
    *   \param method_name referencia para string onde será escrito o nome do método
    *   \param descriptor referencia para string onde será escrito o descritor do método
    *
    *   \return Retorna o nome o nome e o tipo de retorno da classe no formato invoking_class.nome:tipo
    *
    */
    string getCpoolMethod(int index, string &invoking_class, string &method_name, string &descriptor);

    /** \fn getCpoolClass Busca na Constant Pool o nome da Classe a partir do index
    *
    *   \param index Index utilizado para encontrar o ClassName
    *
    *   \param method_name referencia para string onde será escrito o nome do método
    *   \param descriptor referencia para string onde será escrito o descritor do método
    *
    *   \return Retorna o nome da classe em format String
    *
    *   \brief O index primeiro localiza o ClassName no Constant Pool que irá indicar
    *           o index do UTF-8 que contem o nome da classe
    */
    string getCpoolNameAndType(int index, string &method_name, string &descriptor);


    /** \fn getFieldClassName
	*   \brief Pega o nome da classe de onde a field pertence
	*/
    string getFieldClassName(int n);

	/** \fn getFieldName
	*   \brief Pega o nome de uma field n na constant pool
	*/
    string getFieldName(int n);

	/** \fn getFieldType(int n)
	*  \brief Resolve o tipo de uma field n na constant pool
	*/
    string getFieldType(int n);

    /** \fn getFieldType(string fname)
	*  \brief Resolve o tipo de uma field n na constant pool
    * a partir do nome da field
	*/
    string getFieldType(string fname);



	/** \brief Procura o método em uma classe.
	*
	*   \return Se o método for encontrada, retorna o index do método na classe.
    *   Se o método não for encontrada, retorna -1.
	*/
	int findMethod(string method_name, string descriptor);


	/**
	*   \return retorna o nome da superclasse
    *   se for o object retorna string vazia
	*/
	string getSuper();

	/** \brief Resolve uma referência para um nome presente na constant_pool.
	*
	*   \param int name_index: Um index da constant_pool.
	*
	*   \return Se o index apontar para uma string, retorna a string. Se o index não apontar para uma string, retorna NULL.
	*/
	string getName(int name_index);

	/** \brief Retorna o atributo Code de um dos métodos da classe.
	*
	*   \param method_info indice do método que se quer o code attribute
	*
	*   \return Retorna um ponteiro para o atributo Code do método. Se o método não possuir um atributo code, retorna NULL.
	*/
	Code_attribute* getCodeAttr(int m_index);


	/**
	*   \return Retorna true se o método no indice method_index for estatico
	*/
	bool isStaticMethod(int method_index);


};

#endif //CLASS_FILE
