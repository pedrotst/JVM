#include "../include/interpretador.hpp"

std::vector<instructionFunction> init_interpreter (){
    //inicializa o vetor de ponteiros pra função.
    //so n sei como uma função recebe/retorna ponteiro pra função D:
    //int (*pt)(op_stack**);//declara o vetor de ponteiro de função
    //pt = (int(**)(op_stack**)) calloc(sizeof(int(*)(**op_stack)), numOpcodes );//aloca o vetor
    //pt[0] = &iadd;//associa a função a posição
    std::vector<instructionFunction> pt;

    //cada instrução deverá ser colocada na posição do vetor equivalente ao seu byte de opcode
    pt.push_back(&iadd);
    printf("Interpretador inicializado.\n");
    return pt;
}
void iadd(jStackFrame &jStack){
    uint8_t lhs, rhs;
    printf("Entrou na funcao\n");
    lhs = jStack.opStack.back();
    jStack.opStack.pop_back();
    rhs = jStack.opStack.back();
    jStack.opStack.pop_back();
    printf("lhs: %d rhs: %d\n", lhs, rhs);
    jStack.opStack.push_back(lhs + rhs);

}

//int iadd(uint8_t* frameInit){
//    printf("Entrou na funcao\n");
//    return frameInit[0]+frameInit[1];
//}

//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
//
//int ladd(uint8_t* frameInit){
//    return 0;
//}
