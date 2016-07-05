#ifndef _JVM_HPP
#define _JVM_HPP

/**  \file  */

#include <iostream>
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

/**  \class Jvm
 *
 *  \brief Esta é a classe mãe da JVM ela
 *  Ela quem deve encontrar a main da classe inicial e rodar o loop para
 *  rodar os métodos
 */


class Jvm{
    public:
        /** \var fStack
         *
         *  \brief Pilha de execução da jvm. Pilha de frames.
         */
        std::vector<Frame> fStack;

        /** \var std::map<std::string, ClassFile> loadedClasses
         *
         * \brief Vetor de classes carregadas.
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
         * \brief Obtém uma referência para uma classe carregada. A classe é
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
         * \brief Carrega a instância de uma classe carregada, alocando
         * as fields e instânciando com os valores padrão.
         *
         * \param className nome da classe a ser retornada
         *
         * \return A referência da instância da classe alocada com valores padrão.
         *
         */
        InstanceClass* alocarObjeto(std::string className);


        // Em andamento
        //
        // Cria o frame
        Local_var execMethod(int main_index, ClassFile *classF, vector<Local_var> args);

        int execCode(Code_attribute *code_attr_pt, Frame *frame_pt);

        FieldValue inicializaFval(const char* ftype, int n);


        // Em andamento
        //
        // Executa as instruções.
        // interpretador
        //execCode();

        // Descrição:
        //    Executa a jvm em si.
        //    Utiliza grande parte das funções declaradas acima.
        //
        //    Etapas:
        //          * Procura a main.
        //          * Se houver main, começa a executar.
        //
        // Parâmetros:
        //    *const char arq_class_name: nome do arquivo .class a ser executado.
        //
        //
        int run(const char* arq_class_name);
};

#endif // _JVM_HPP
