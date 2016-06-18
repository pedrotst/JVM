#ifndef JAVASTACK_FRAME_HPP_INCLUDED
#define JAVASTACK_FRAME_HPP_INCLUDED

#include <vector>

typedef std::vector<uint32_t> op_stack;

typedef struct javaStack_frame_s{
    op_stack opStack;//pilha de execução interna ao frame
    //colocar o restante da estrutura
}jStackFrame;//Mudar o nome para frame

#endif // JAVASTACK_FRAME_HPP_INCLUDED
