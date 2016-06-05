#include <stdio.h>
#include "../include/leitor.hpp"
#include "../include/exibidor.hpp"

int main(int argc, char** argv){

	ClassFile classF;
	FILE *arquivoJava;
	if((arquivoJava = abreArquivo(argc, argv)) == NULL){
        printf("Encerrando...");
        return 1;
	}
	//Leitura 0xCAFEBABE e versão
    leituraHeader(&classF, arquivoJava);

    //leitura constant pool
	leituraConstantPool(&classF, arquivoJava);

    //Leitura accessThisSuper
    leituraAccessThisSuper(&classF, arquivoJava);

    //leitura interfaces
    leituraInterfaces(&classF, arquivoJava);

    //leitura fields
    leituraFields(&classF, arquivoJava);

    //leitura dos methods
    leituraMethods(&classF, arquivoJava);

    //leitura attributes
    leituraAttributes(&classF, arquivoJava);

    exibeClass(classF);

    fclose(arquivoJava);

    char* className = getClassName(&classF);
    printf("Nome da classe: %s\n", className);
    return 0;
}
