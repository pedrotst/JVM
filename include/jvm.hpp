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
        // Pilha de execução da jvm. Pilha de frames.
        std::vector<Frame> jStack;
        // Vetor de classes carregadas.
        std::map<std::string, ClassFile> loadedClasses;
        // Mapeia classname para instancias
        std::map<std::string, InstanceClass> heap;

    public:
        // Construtor
        Jvm(){}

        // Descrição:
        //    Obtém uma referência para uma classe carregada. A classe é carregada,
        //    caso já não estiver.
        //
        // Parâmetros:
        //    string className: nome da classe a ser retornada
        //
        // Retorno:
        //    Refrência para uma classe carregada.
        ClassFile getClassRef(std::string className);

        // Descrição:
        //
        // Parâmetros:
        //
        // Retorno:
        //
        void alocarObjeto(std::string className);


        // Em andamento
        //
        // Cria o frame
        int execMethod(int main_index, ClassFile *classF);
        bool isCode(attribute_info attr);

        int execCode(Code_attribute *code_attr_pt, Frame *frame_pt);


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
