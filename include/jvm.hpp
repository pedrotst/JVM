#ifndef _JVM_HPP
#define _JVM_HPP

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





class Jvm{
    private:
        std::vector<Frame> jStack;
        //troquei loadedClasses para mapa entre className e classFile
        //pois assim podemos
        //checar se a classe ta carregada checando simplesmente
        //se loadedClasses[className] != NULL
        std::map<std::string, ClassFile> loadedClasses;
        //mapeia classname para instancias
        std::map<std::string, InstanceClass> heap;
    public:
        //Construtor
        Jvm();
        void alocarClasse(std::string className);

        // Descrição:
        //    Procura o método main em uma classe.
        //
        // Parâmetros:
        //    ClassFile *classF_pt: Um ponteiro para uma classe carregada.
        //
        // Retorno:
        //    Se a main for encontrada, retorna um ponteiro para sua method_info.
        //    A mesma method_info que está dentro da constant_pool.
        //
        //    Se a main não for encontrada, retorna NULL.
        //
        int findMain (ClassFile *classF_pt);

        // Descrição:
        //    Resolve uma referência para um nome presente na constant_pool.
        //
        // Parâmetros:
        //    ClassFile *classF_pt: Um ponteiro para uma classe carregada.
        //
        //    int name_index: Um index da constant_pool.
        //
        // Retorno:
        //    Se o index apontar para uma string, retorna a string.
        //
        //    Se o index não apontar para uma string, retorna NULL.
        //
        char* getName(ClassFile *classF_pt, int name_index);

        // Em andamento
        //
        // Cria o frame
        int execMethod(int main_index, ClassFile classF);
        bool isCode(attribute_info attr);


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
