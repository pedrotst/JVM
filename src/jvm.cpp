#include <stdio.h>
#include <map>
#include "../include/jvm.hpp"

using namespace std;

int Jvm::run(const char* arq_class_name) {
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
	main_index = classF.findMain();
	if (main_index) {
		//execMethod(main_index, classF);
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

/////////////////////////////////////////////////////////////////////////////
ClassFile Jvm::getClassRef(std::string className) {
      ClassFile classF;
      FILE *arquivoClass = NULL;

      // Se a classe não for encontrada no map, o find retorna um iterador para end.
      // Ou seja, caso a classe não for encontrada.
      // Carrega a nova classe.
      if(this->loadedClasses.find(className) == this->loadedClasses.end()) {
            if(!(arquivoClass = fopen(className.append(".class").c_str(), "rb"))) {
      		printf("O arquivo .class nao pode ser aberto.\n");
      		exit(0);
      	}

      	leitorClass_info(&classF, arquivoClass);

      	this->loadedClasses[className] = classF;
      }
      // Se a classe for encontrada retorna uma referência para ela
      else {
      	classF = this->loadedClasses[className];
      }

      return classF;
}

/////////////////////////////////////////////////////////////////////////////
bool Jvm::isCode(attribute_info attr){
	//if(attr.)
	return false;
}

/////////////////////////////////////////////////////////////////////////////
//Classe para iniciar instanciacao da classe
//Se ele o classfile ainda nao foi carregado, ele carrega
void Jvm::alocarClasse(string className){
	ClassFile classF;
	FILE *arquivoClass = NULL;
	InstanceClass inst;

      // Obtém a referência para a classe. A classe é carrega se necessário.
      classF = getClassRef(className);

      inst.cf = &classF;

	cout << "Creating class" << className << endl;
	map<string, string> fbinds = classF.getFieldsNamesTypes();
	for(auto const &ent : fbinds) {
		string fname = ent.first;
		const char* ftype = ent.second.c_str();
		cout << fname << " " << ftype[0] << endl;

		field_value fval;
		switch(ftype[0]) {
		case 'B': //byte type
			fval.tag = BYTE;
			fval.val.byte = 0;
			break;
		case 'C': //char
			fval.tag = CHAR;
			fval.val.caractere = 0;
			break;
		case 'D': // double
			fval.tag = DUPLO;
			fval.val.duplo = 0;
			break;
		case 'F': // float
			fval.tag = INSTANCIA;
			fval.val.pFlutuante = 0;
			break;
		case 'I': // int
			fval.tag = INT;
			fval.val.inteiro = 0;
			break;
		case 'J': // long
			fval.tag = LONGO;
			fval.val.longo = 0;
			break;
		case 'S': // short
			fval.tag = CURTO;
			fval.val.curto = 0;
			break;
		case 'Z': // boolean
			fval.tag = BOOL;
			fval.val.boleano = false;
			break;
		case 'L': // reference
			fval.tag = INSTANCIA;
			fval.val.instancia = NULL;
			break;
		case '[': // array
			fval.tag = LISTA;
			//fval.val = NULL;
			break;
			inst.field_instances[fname] = fval;
		}
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
	for(j=0; j < classF.methods[n].attributes_count; j++) {
		printf("\t Attribute number: %d\n", j + 1);
		index = classF.methods[n].attributes[j].attribute_name_index_l;
		printf("\t Attribute Name: %s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);
		printf("\t Attribute Length: %d\n", classF.methods[n].attributes[j].attribute_length_l);

		if(!strcmp(classF.constant_pool[index-1].cp_union.constant_Utf8.bytes, "Code")) {
			printf("\t Max Stack: %d, ", classF.methods[n].attributes[j].attribute_union.attr_Code.max_stack);
			printf("\t Max Locals: %d, ", classF.methods[n].attributes[j].attribute_union.attr_Code.max_locals);
			code_length = classF.methods[n].attributes[j].attribute_union.attr_Code.code_length;
			printf("\t Code Length: %d\n", code_length);

			for(int k = 0; k < code_length; k++) {
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
