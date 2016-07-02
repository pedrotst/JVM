#include "../include/verificador.hpp"

void verificaClass(ClassFile classF){
    verificaMethods(classF);
}

void verificaMethods(ClassFile classF){
    int i, j, index;

    //Percorre todos os métodos
    for(i = 0; i < classF.methods_count; i++){
        //Percorre todos os atributos dos métodos
        for(j = 0; j < classF.methods[i].attributes_count; j++){
            int code_length;
            index = classF.methods[i].attributes[j].attribute_name_index_l; //Indice no constant pool

            //Se o atributo do método for o Code
            if(!strcmp(classF.getCpoolUtf8(index).c_str(), "Code")){
                code_length = classF.methods[i].attributes[j].attribute_union.attr_Code.code_length;
                //printf("\t Code Length: %d\n", code_length);
                for(int k = 0; k < code_length; k++){
                    uint8_t opcode = classF.methods[i].attributes[j].attribute_union.attr_Code.code[k];
                    //printf("opcode: %X\n", opcode);

                    switch(opcode){
                        //INVOKESPECIAL
                        case(0XB7):
                            printf("INVOKESPECIAL!\n");
                            index = (classF.methods[i].attributes[j].attribute_union.attr_Code.code[k+1] << 8) | classF.methods[i].attributes[j].attribute_union.attr_Code.code[k+2];
                            printf("index = %d\n",index);
                            if(classF.constant_pool[index-1].tag != CONSTANT_Methodref){
                                printf("Erro!\n");
                            }
                            else{
                                printf("Ok!\n");
                            }
                            break;
                    }
                }
            }
        }
    }


}

