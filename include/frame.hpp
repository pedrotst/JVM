#ifndef FRAME_H
#define FRAME_H

#include<vector>
#include<cstdint>
#include "..\include\jvm.hpp"//para operand

class Frame{
public:
    //op_stack *opStack;//pilha de execuчуo interna ao frame
    std::vector<uint32_t> op_stack;

    //operandStack *opStack;
    std::vector<operand> operandStack;

    //Vetor de variaveis locais
    //localVarStack *localVar; //pilha de variaveis locais
    std::vector<local_var> localVarStack;

    //Referência para a ConstantPool
    cp_info *cpReference;

    //Serve para ler o Code:
    int pc;
    int code_length;
    char *code;
    Frame();
};

#endif // JAVASTACK_FRAME_HPP_INCLUDED
