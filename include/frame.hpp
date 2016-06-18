#ifndef FRAME_H
#define FRAME_H

#include<vector>
#include<cstdint>

typedef std::vector<uint32_t> op_stack; //trocar para o tipo da union depois

class Frame{
public:
    op_stack *opStack;//pilha de execução interna ao frame
    //pc
    //vetor de variaveis locais
    //referencia pra constant pool

    Frame();

};

#endif // JAVASTACK_FRAME_HPP_INCLUDED
