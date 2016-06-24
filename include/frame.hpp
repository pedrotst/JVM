#ifndef FRAME_H
#define FRAME_H

#include<vector>
#include<cstdint>
#include "../include/heap.hpp"

typedef std::vector<operand_value> op_stack; //trocar para o tipo da union depois

class Frame{
public:
    op_stack *opStack;//pilha de execução interna ao frame
    //pc
    //vetor de variaveis locais
    //referencia pra constant pool

    Frame();

};

#endif // JAVASTACK_FRAME_HPP_INCLUDED
