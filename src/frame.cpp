#ifndef JAVASTACK_FRAME_HPP_INCLUDED
#define JAVASTACK_FRAME_HPP_INCLUDED

#include <vector>

typedef std::vector<uint32_t> op_stack; // tipo do vetor tem que trocar para tipo union que vai ser definido

class Frame{
    op_stack opStack;//pilha de execução interna ao frame
    //pc
    //vetor de variaveis locais
    //referencia pra runtime constant pool
};

#endif // JAVASTACK_FRAME_HPP_INCLUDED
