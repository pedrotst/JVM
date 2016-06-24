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

    this->alocarClasse(classF.getClassName());

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

//Classe para iniciar instanciacao da classe
//Se ele o classfile ainda nao foi carregado, ele carrega
void Jvm::alocarClasse(string className){
    ClassFile classF;
    FILE *arquivoClass = NULL;
    InstanceClass inst;

    //if checa se a classe jah foi carregada
    if(this->loadedClasses.find(className) == this->loadedClasses.end()){
        if(!(arquivoClass = fopen(className.append(".class").c_str(), "rb"))) {
            printf("O arquivo .class nao pode ser aberto.\n");
            exit(0);
        }

        leitorClass_info(&classF, arquivoClass);
        this->loadedClasses[className] = classF;
    }
    else {
        classF = this->loadedClasses[className];
    }

    cout << "Creating class" << className << endl;
    vector<string> fnames = classF.getFieldsNames();
    for(int i=0; i < fnames.size(); i++){
        string fname = fnames[i];
        cout << fnames[i] << endl;

        //faz instancia do field segundo seu tipo
        //inst.field_instances[fname] =  

    }




}
/////////////////////////////////////////////////////////////////////////////
int Jvm::execMethod(int n, ClassFile classF) {
	int index, j, pc, buffer;


	uint32_t code_length;
	// Pilha de operandos.
	// A pilha de operandos começa vazia. Ela é populada ao longo da execução
	// das instruções.
	std::vector<operand_value> operandStack;
	// Pilha de variáveis locais.
	std::vector<local_var> localVarStack;
	// Frame da javaStack.
	Frame frame;
	// Popula a pilha de variáveis locais. Ela recebe as variáveis locais do
	// método, inclusive os parâmetros.

	// Empilha o frame.
	this->jStack.push_back(frame);

 	index = classF.methods[n].descriptor_index;
	for(j=0; j < classF.methods[n].attributes_count; j++){
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

                    //teste
                    /*O interpreter_op_code ira identificar os operandos de cada instrucao, lendo os bytes correspondentes
                    de cada operando, formar os operandos com os bytes lidos (concatenando-os se necessário) e puxando-os
                    na pilha. Para este fim criamos o interpreter_op_code.cpp/hpp. 

                    A ideia seguinte seria chamar o vetor de instruções passando o op_code */

                    int arg_qnt = interpreter_op_code(opcode);
                    //as linhas abaixo deverao ser parte do interpreter_op_code, mas para tal é necessário passar as referencias
                    //para area de codigo, a posição do leitor na area de codigo(neste caso o k) e a referencia para a pilha.
                    uint8_t operand = classF.methods[n].attributes[j].attribute_union.attr_Code.code[k+1];
                    buffer = operand;
                    buffer = buffer<<8;
                    operand = classF.methods[n].attributes[j].attribute_union.attr_Code.code[k+2];
                    buffer = buffer|operand;
                    printf("%d a\n", buffer);



                    // interpretar o opcode, saber qual é o tipo do operando, ler e colocar na pilha, antes de chamar a função

                    
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


