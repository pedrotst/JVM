#include <stdio.h>
#include <map>
#include "../include/jvm.hpp"

using namespace std;

Jvm::Jvm(){
    std::vector<Frame> jStack = std::vector<Frame>();
    this->jStack = jStack;
}

int Jvm::run(const char* arq_class_name) {
	// Vetor de classes carregadas.
	// Pilha de execução da jvm. Pilha de frames.
	std::vector<Frame> Stack;
	ClassFile classF;
	int main_index;
	FILE *arquivoClass;

	if( !(arquivoClass = fopen(arq_class_name, "rb"))) {
		printf("O arquivo .class %s, nao pode ser aberto.\n", arq_class_name);
		exit(0);
	}

	leitorClass_info(&classF, arquivoClass);

	this->loadedClasses.push_back(classF);

	// Procura o método main na primeira classe carregada. Se não encontrar,
	// a execução é finalizada. Se encontrar, começa a execução.
	main_index = findMain(&classF);
	if (main_index) {
		execMethod(main_index, classF);
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
    /*Frame frame = Frame();
    //coloca operandos na pilha de operandos
    frame.opStack->push_back(23);
    frame.opStack->push_back(3);

    //inicializa interpretador

    Interpretador interpreter = Interpretador(this);
    interpreter.execute_instruction(IADD, frame.opStack);

	//exibe resultado
	printf("Resultado: %d\n", frame.opStack->back());

	//exibeClass(classF);*/

	return 0;
}

bool Jvm::isCode(attribute_info attr){
	//if(attr.)
	return false;
}

/////////////////////////////////////////////////////////////////////////////
//Retorna o numero da posicao da main
int Jvm::findMain(ClassFile *classF_pt) {
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
			return i;
	}

	// Só ocorre se não houver main
	return -1;
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
int Jvm::execMethod(int n, ClassFile classF) {
	int index, j;
	uint32_t code_length;
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

 	index = classF.methods[n].descriptor_index;
	for(int i=0; i < classF.methods[n].attributes_count; i++){
		printf("\t Attribute number: %d\n", j + 1);
        index = classF.methods[n].attributes[j].attribute_name_index_l;
        printf("\t Attribute Name: %s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);
        printf("\t Attribute Length: %d\n", classF.methods[n].attributes[j].attribute_length_l);
		if(!strcmp(classF.constant_pool[index-1].cp_union.constant_Utf8.bytes, "Code")){
            printf("\t Max Stack: %d, ", classF.methods[n].attributes[j].attribute_union.attr_Code.max_stack);
            printf("\t Max Locals: %d, ", classF.methods[n].attributes[j].attribute_union.attr_Code.max_locals);
            code_length = classF.methods[n].attributes[j].attribute_union.attr_Code.code_length;
            printf("\t Code Length: %d\n", code_length);

                for(int k = 0; k < code_length; k++){
                    uint8_t opcode = classF.methods[n].attributes[j].attribute_union.attr_Code.code[k];

                    //printf("\t Code: %02x\n", opcode);
                    int arg_qnt = print_code(opcode);
                    cout << "\t"<< k << ":\t"<<  opcode << "\t";
                    //printf("arg_qnt = %d\n", arg_qnt);
                    for(int u = 0 ; u < arg_qnt; u += (!(arg_qnt%2) + 1)){
                        uint16_t cp_ref;
                        if((arg_qnt%2) == 0)
                            cp_ref = (classF.methods[n].attributes[j].attribute_union.attr_Code.code[k+u+1] << 8) | classF.methods[n].attributes[j].attribute_union.attr_Code.code[k+u+2];
                        else
                            cp_ref = classF.methods[n].attributes[j].attribute_union.attr_Code.code[k+u+1];
                        printf(" #%d ",cp_ref);
                    }
                    if(arg_qnt > 0){
                        cout << "\t // ";
                    }
                    for(int u = 0 ; u < arg_qnt; u+= (!(arg_qnt%2) + 1)){
                        printf(" ");
                        uint16_t cp_ref;
                        if((arg_qnt%2) == 0)
                            cp_ref = (classF.methods[n].attributes[j].attribute_union.attr_Code.code[k+u+1] << 8) | classF.methods[n].attributes[j].attribute_union.attr_Code.code[k+u+2];
                        else
                            cp_ref = classF.methods[n].attributes[j].attribute_union.attr_Code.code[k+u+1];
                        print_comment(classF.constant_pool, cp_ref - 1);
                    }
                    cout << endl;
                    k += arg_qnt;
                }
            }
        }
	// Esse é o interpretador mesmo. Ele passa pelas instruções executando uma
	// por uma.
	// Executa o código do método.
	//execCode();
	return 0;
}
