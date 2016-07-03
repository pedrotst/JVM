#include "../include/interpreter_op_code.hpp"
#include "../include/interpretador.hpp"

int interpreter_code(std::vector<Frame> *jStack/*, heap*/) {
    for(int k = 0; k < jStack->back().code_length;){
        uint8_t opcode = code[pc];
        /*O interpreter_op_code ira identificar os operandos de cada instrucao, lendo os bytes correspondentes
        de cada operando, formar os operandos com os bytes lidos (concatenando-os se necessário) e puxando-os
        na pilha. Para este fim criamos o interpreter_op_code.cpp/hpp.

        A ideia seguinte seria chamar o vetor de instruções passando o op_code */
        //k = interpretador(opcode)(dados necessarios)


        //as linhas abaixo deverao ser parte do interpreter_op_code, mas para tal é necessário passar as referencias
        //para area de codigo, a posição do leitor na area de codigo(neste caso o k) e a referencia para a pilha.
    }
}
