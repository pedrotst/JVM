#include "../include/interpretador.hpp"

int iadd(uint8_t* frameInit){
    printf("Entrou na funcao\n");
    return frameInit[0]+frameInit[1];
}


//função initInterpreter(void)
//retorna um vetor de ponteiros a função (ponteiro de ponteiro de função)
//as funções q compõem o vetor sao do tipo: int func(uint8_t*)
int (**initInterpreter(void))(uint8_t*){
    //inicializa o vetor de ponteiros pra função.
    //so n sei como uma função recebe/retorna ponteiro pra função D:
    int (**pt)(uint8_t*);//declara o vetor de ponteiro de função
    pt = (int(**)(uint8_t*)) calloc(sizeof(int(*)(uint8_t*)), numOpcodes );//aloca o vetor
    pt[0] = &iadd;//associa a função a posição
    printf("Interpretador inicializado.\n");
    return pt;
}
