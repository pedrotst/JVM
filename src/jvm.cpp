#include <stdio.h>
#include <map>
#include "../include/leitor.hpp"
#include "../include/exibidor.hpp"
#include "../include/frame.hpp"
#include "../include/interpretador.hpp"
#include "../include/opcode.hpp"
#include "../include/jvm.hpp"

Jvm::Jvm(){
    std::vector<Frame> jStack = std::vector<Frame>();
    this->jStack = jStack;
}

int Jvm::run(const char* arq_class_name) {
	// Vetor de classes carregadas.
	std::vector<ClassFile> loadedClasses;
	// Pilha de execução da jvm. Pilha de frames.
	std::vector<Frame> Stack;
	ClassFile classF;
	method_info *main;
	FILE *arquivoClass;

	if( !(arquivoClass = fopen(arq_class_name, "rb"))) {
		printf("O arquivo .class %s, nao pode ser aberto.\n", arq_class_name);
		exit(0);
	}

	leitorClass_info(&classF, arquivoClass);

	loadedClasses.push_back(classF);

	// Procura o método main na primeira classe carregada. Se não encontrar,
	// a execução é finalizada. Se encontrar, começa a execução.
	if (main = findMain(&classF)) {
		execMethod(main);
	}
	else {
		printf("O arquivo .class nao possui uma main.\n");
		exit(0);
	}

	/*execCode() {
		//
		while (não acabar as instruções) {
			(*instrucs[op])();
		}
	};*/

    //cria um frame para a javaStack
    Frame frame = Frame();
    //coloca operandos na pilha de operandos
    frame.opStack->push_back(23);
    frame.opStack->push_back(3);

    //inicializa interpretador

    Interpretador interpreter = Interpretador();
    interpreter.execute_instruction(IADD, frame.opStack);

	//exibe resultado
	printf("Resultado: %d\n", frame.opStack->back());

	//exibeClass(classF);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
method_info* Jvm::findMain(ClassFile *classF_pt) {
	int i = 0;
	char *method_name = NULL;
	method_info *method_pt = NULL;

	// Para cada método
	for (i = 0; i < classF_pt->methods_count; i++) {
		// Pega o método
		method_pt = &classF_pt->methods[i];
		// Pega o nome do método
		method_name = getName(classF_pt, method_pt->name_index);
		// Retorna o método, se for o main
		if (!strcmp(method_name, "main"))
			return method_pt;
	}

	// Só ocorre se não houver main
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
char* Jvm::getName(ClassFile *classF, int name_index){
	char *name = NULL;

	// Checa se a entrada da constant_pool apontada pelo index é uma string.
	// Se não for retorna NULL.
	/*if (classF.constant_pool[name_index-1].tag != cp_tag.CONSTANT_Utf8) {
		printf("O index (da constant_pool) passado não aponta para uma string.\n");
		return NULL;
	}*/

	// Obtém a string da constant_pool.
	name = classF->constant_pool[name_index-1].cp_union.constant_Utf8.bytes;

	return name;
}

/////////////////////////////////////////////////////////////////////////////
int Jvm::execMethod(method_info *method) {
	// Pilha de operandos.
	// A pilha de operandos começa vazia. Ela é populada ao longo da execução
	// das instruções.
	std::vector<operand> operandStack;
	// Pilha de variáveis locais.
	std::vector<local_var> localVarStack;
	// Frame da javaStack.
	Frame frame;

	// Popula a pilha de variáveis locais. Ela recebe as variáveis locais do
	// método, inclusive os parâmetros.

	// Empilha o frame.
	this->jStack.push_back(frame);


	// Esse é o interpretador mesmo. Ele passa pelas instruções executando uma
	// por uma.
	// Executa o código do método.
	//execCode();
	return 0;
}
