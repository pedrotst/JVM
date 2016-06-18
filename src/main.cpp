#include <stdio.h>
#include <map>
#include "../include/leitor.hpp"
#include "../include/exibidor.hpp"
#include "../include/frame.hpp"
#include "../include/interpretador.hpp"
#include "../include/opcode.hpp"


int main(int argc, char** argv){
    //não consegui fazer esse formato rodar com getClassName()
	//std::map<char*, ClassFile> classMap;//map contendo todas as classes
	//std::vector<char*> classNames;        //vetor contendo os nomes para referenciar no map

	std::vector<ClassFile> loadedClasses;
	ClassFile classF;
	FILE *arquivoJava;
	//arquivoJava = abreArqLinhaComando(argc, argv);//só serve pra ler a primeira por tratar entrada via linha de comando

    //leitorClass_info ja fecha o arquivo. Acham melhor não faze-lo para explicitar?
    if(argc > 1){
        if(strcmp(argv[1], "-v") == 0){
            arquivoJava = abreArquivo(argv[2]);
            leitorClass_info(&classF, arquivoJava);
            exibeClass(classF);
        }
    }
    else{
        arquivoJava = abreArqLinhaComando(argc, argv);
        leitorClass_info(&classF, arquivoJava);
    }
    
    //no caso de usar o map
    //classMap.emplace(getClassName(&classF), classF);//classe mapeada pelo nome
    //classNames.push_back(getClassName(&classF));   //vetor com nomes das classes. Unico jeito que eu pensei de navegar no map "via indice"
                                                    //sei que tem o iterator, mas ta dando problema na hora de imprimir, então whatever
    loadedClasses.push_back(classF);
    //Comentei só pra n ficar aparecendo aquilo tudo
    //ainda tem que colocar exibição condicional
    //exibeClass(loadedClasses[0]);


    printf("Nome da classe: %s\n", getClassName( &loadedClasses[0] ) );

    //cria um frame para a javaStack
    Frame frame;
    //coloca operandos na pilha de operandos
    frame.opStack->push_back(23);
    frame.opStack->push_back(3);

    //inicializa interpretador
    Interpretador interpreter;
    interpreter.execute_instruction(IADD, frame.opStack);

    //exibe resultado
    printf("Resultado: %d\n", frame.opStack->back());//usando pt[0] == usar iadd(uint_8*)

    //exibeClass(classF);
    return 0;
}
