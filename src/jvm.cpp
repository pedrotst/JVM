#include <stdio.h>
#include <map>
#include "../include/leitor.hpp"
#include "../include/exibidor.hpp"
#include "../include/javaStack_frame.hpp"
#include "../include/interpretador.hpp"
#include "../include/opcode.hpp"

int jvm(*char classF_name) {
	std::vector<ClassFile> loadedClasses;
      std::vector<jStackFrame> jStack;
	ClassFile classF;
	FILE *arquivoJava;

      pt = init_interpreter();

	arquivoJava = abreArqLinhaComando(argc, argv);

	//leitorClass_info ja fecha o arquivo. Acham melhor n�o faze-lo para explicitar?
	leitorClass_info(&classF, arquivoJava);

	loadedClasses.push_back(classF);

	printf("Nome da classe: %s\n", getClassName( &loadedClasses[0] ) );

	// Procura o método main na primeira classe carregada. Se não encontrar,
	// a execução é finalizada. Se encontra, começa a execução.
	if (getMethodName() == "main") {
		execMethod();
	}

	execMethod(std::vector<jStackFrame> &jStack) {
		//cria um frame para a javaStack
		jStackFrame stackFrame;

		// A pilha de operandos começa vazia. Ela é populada ao longo da execução
            // das instruções.

            // Popula a pilha de variáveis locais. Ela recebe as variáveis locais do
            // método, inclusive os parâmetros.

            // Empilha o frame.
            push(std::vector<jStackFrame> &jStack, jStackFrame &stackFrame);

            // Executa o código do método.
            execCode();
	}

      execCode() {
            //
            while (não acabar as instruções) {
                  (*instrucs[op]) ();
            }
      };

	//inicializa interpretador
	std::vector<instructionFunction> pt;
	pt[IADD](stackFrame);
	//exibe resultado
	printf("Resultado: %d\n", stackFrame.opStack.back());//usando pt[0] == usar iadd(uint_8*)

	//exibeClass(classF);
	return 0;
}
