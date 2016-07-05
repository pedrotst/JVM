#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include "../include/leitor.hpp"
#include "../include/exibidor.hpp"
#include "../include/frame.hpp"
#include "../include/interpretador.hpp"
#include "../include/opcode.hpp"
#include "../include/jvm.hpp"

#define ARG1(ac, av) (ac > 1 ? av[1] : "")

#define ARG2(ac, av) (ac > 2 ? av[2] : "")

const char *help = "\nSintaxe:\n\
                    jvm -h Exibe o menu de ajuda.\n\
                    \n\
                    jvm { -r | -e } {nome_arquivo_class}\n\
                    \n\
                    -r : read. Le o arquivo .class passado e o exibe na tela, assim como o javap -v.\n\
                    \n\
                    -e : execute. Executa o arquivo .class passado.\n\
                    \n";

int main(int argc, char** argv){
    const char *arg1 = NULL, *arg2 = NULL;
    FILE *arquivoClass = NULL;
    ClassFile classF;
    Jvm jvm = Jvm();

    arg1 = ARG1(argc, argv);
    arg2 = ARG2(argc, argv);
    int len = strlen(arg2);
    //printf("resultado da comparacao (%s,%s): %d\n", arg2+len-6, ".class", strcmp(arg2+len-6, ".class"));
    if(strcmp(arg2+len-6, ".class")){
        printf("O arquivo %s nao eh um .class. Encerrando...\n", arg2);
        exit(0);
    }
    // Caso o parâmetro passado seja um -r (READ).
    if (!strcmp(arg1, "-r")) {
        // Abre o arquivo
        if( !(arquivoClass = fopen(arg2, "rb"))) {
            printf("O arquivo .class nao pode ser aberto.\n");
            exit(0);
        }

        // Lê o arquivo .class
        leitorClass_info(&classF, arquivoClass);

        // Exibe o arquivo lido.
        exibeClass(classF);
    }

    // Caso o parâmetro passado seja um -e (EXECUTE).
    else if (!strcmp(arg1, "-e")) {
        printf("Chamando jvm.run(%s)\n", arg2);
        // Inicializa a jvm para a execução do arquivo class passado (arg2).
        jvm.run(arg2);
    }

    // Se a passagem de parâmetros da linha de comando estiver errada.
    else {
        printf("%s\n", help);
    }

    //fclose(arquivoClass);

    return 0;
}
