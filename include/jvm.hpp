#ifndef _JVM_HPP
#define _JVM_HPP

/**  \file  */

#include <iostream>
#include <tuple>
#include "../include/leitor.hpp"
#include "../include/heap.hpp"
#include "../include/frame.hpp"
#include "../include/interpretador.hpp"
#include "../include/opcode.hpp"
#include "../include/exibidor.hpp"
#include "../include/classFile.hpp"
#include "../include/op_instrucs.hpp"
#include "../include/interpreter_op_code.hpp"
#include "../include/verificador.hpp"
#include "../include/debug.hpp"

/**  \class Jvm
 *
 * \brief Esta é a classe mãe da JVM ela
 * Ela quem deve encontrar a main da classe inicial e rodar o loop para
 * rodar os métodos.
 * Ela quem é responsável pela heap, e pela gerencia dos objetos alocados em geral
 * inclusive os classfile!
 *
 */


class Jvm{
private:
        /**
        *   \var O .class principal encontra-se em um classpath,
        * todos próximos arquivos serão procurados na mesma pasta que o programa
        * ou dentro deste classpath.
        *
        */
        std::string classpath;
        /** \fn inicializaFval
         *
         * \brief Constroi uma FieldValue com os valores padroes, a maioria zero
         * ou false para booleanos, ou array com a dimensao certa mas vazio, ou null.
         *
         * \param ftype
         * \param ftype eh o descritor da field
         * \param n parametro para recursao, chame esta funcao passando como valor inicial sempre zero.
         *
         * \return uma FieldValue inicializada
         *
         */
        FieldValue inicializaFval(const char* ftype, int n);

public:
        /** \var fStack
         *
         *  \brief Pilha de execução da jvm. Pilha de frames.
         */
        std::vector<Frame> fStack;

        /** \var std::map<std::string, ClassFile> loadedClasses
         *
         * \brief mapa de classes carregadas.
         */
        std::map<std::string, ClassFile*> loadedClasses;

        /** \var heap
         *
         * \brief Mapeia classname para instancias
         */
        std::vector<InstanceClass*> heap;
        std::map<std::string, InstanceClass*> staticHeap;

        /** \fn JVM()
         *
         * \brief Construtor
         */
        Jvm(){}

        /** \fn ClassFile getClassRef (std::string className)
         *
         * \brief Obtém uma referencia para uma classe carregada. A classe é
         * carregada, caso já não estiver.
         *
         * \param className nome da classe a ser retornada
         *
         * \return A classfile que de fato representa a estrutura do .class
         *
         */
        ClassFile* getClassRef(std::string className);

        /** \fn ClassFile getClassRef (std::string className)
         *
         * \brief Altera o valor de um dado field
         *
         * \param field_name nome do field a ser alterado
         * \param valor para colocar no field
         *
         * \return void
         *
         */
        void put_field(std::string field_name, Local_var lvar);

        /** \fn ClassFile alocarObjeto (std::string className)
         *
         * \brief Carrega a instancia de uma classe carregada, alocando
         * as fields e instanciando com os valores padrão.
         *
         * \param className nome da classe a ser alocada
         *
         * \return A referência da instancia da classe alocada com valores padrao.
         *
         */
        InstanceClass* alocarObjeto(std::string className);


        /** \fn ClassFile alocarObjetoEstatico (std::string className)
         *
         * \brief Carrega a instância de uma classe carregada, alocando
         * as fields estaticas e instânciando com os valores padrão.
         *
         * \param className nome da classe a ser alocada
         *
         * \return A referencia da instância da classe estatica alocada com valores padrao.
         *
         */
        InstanceClass* alocarObjetoEstatico(std::string className);

        /** \fn execMethod
         *
         * \brief executa o enesimo metodo da classF com argumentos args
         *
         * \param method_index o indice do método na classF a ser executado
         * \param classF é o ponteiro para o ClassFile dono do método a ser executado
         * \param args são os parametros que serao passado como argumento
         *
         * \return o retorno do metodo empacotado numa Local_var
         *
         */
        tuple<Local_var, Local_var> execMethod(int method_index, ClassFile *classF, vector<Local_var> &jargs);




        int run(const char* arq_class_name);
};

#endif // _JVM_HPP
