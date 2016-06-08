#ifndef JAVASTACK_FRAME_HPP_INCLUDED
#define JAVASTACK_FRAME_HPP_INCLUDED

#include <vector>

typedef struct javaStack_frame_s{
    std::vector<uint8_t> jStack;//pilha de execução interna ao frame
    //colocar o restante da estrutura
}jStackFrame;

#endif // JAVASTACK_FRAME_HPP_INCLUDED
