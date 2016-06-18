#ifndef JAVASTACK_FRAME_HPP_INCLUDED
#define JAVASTACK_FRAME_HPP_INCLUDED

#include <vector>

typedef std::vector<uint32_t> op_stack;

typedef struct j_frame_s{
    op_stack *opStack;//pilha de execução interna ao frame
    //pc
    //vetor de variaveis locais
    //referencia pra constant pool
}jFrame;

#endif // JAVASTACK_FRAME_HPP_INCLUDED
