#include <stdio.h>
#include <map>
#include "../include/jvm.hpp"

using namespace std;

int Jvm::run(const char* arq_class_name) {
<<<<<<< HEAD
    ClassFile classF;
    int main_index;
    FILE *arquivoClass;
    vector<Local_var> args; //coloque a string de argumento aqui
    Local_var main_str;
    args.push_back(main_str);
    if( !(arquivoClass = fopen(arq_class_name, "rb"))) {
        printf("O arquivo .class %s, nao pode ser aberto.\n", arq_class_name);
        exit(0);
    }



    leitorClass_info(&classF, arquivoClass);
    verificaClass(classF);
    // Procura o método main na primeira classe carregada. Se não encontrar,
    // a execução é finalizada. Se encontrar, começa a execução.
    main_index = classF.findMethod("main");
    printf("Valor de main_index: %d\n", main_index);
    if(main_index > 0){
        execStaticMethod(main_index, &classF, args);
    }else {
        printf("O arquivo .class nao possui uma main.\n");
        exit(0);
    }

    return 0;
=======
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
	if (main_index != -1) {
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
>>>>>>> 4ae5775c31374efc6b2deface7b50b2bf9f61355
}

/////////////////////////////////////////////////////////////////////////////
ClassFile* Jvm::getClassRef(string className) {
    ClassFile *classF = new ClassFile();
    FILE *arquivoClass = NULL;

    // Se a classe não for encontrada no map, o find retorna um iterador para end.
    // Ou seja, caso a classe não for encontrada.
    // Carrega a nova classe.
    if(this->loadedClasses.find(className) == this->loadedClasses.end()) {
        if(!(arquivoClass = fopen(className.append(".class").c_str(), "rb"))) {
            printf("O arquivo .class nao pode ser aberto.\n");
            exit(0);
        }
        leitorClass_info(classF, arquivoClass);
        this->loadedClasses[className] = classF;
    }
    // Se a classe for encontrada retorna uma referência para ela
    else {
        classF = this->loadedClasses[className];
    }
    return classF;
}

/////////////////////////////////////////////////////////////////////////////
//Classe para iniciar instanciacao da classe
//Se ele o classfile ainda nao foi carregado, ele carrega
InstanceClass* Jvm::alocarObjeto(string className){
    ClassFile *classF;
    InstanceClass *inst;

    inst = new InstanceClass();
    //inst->field_instances = new Fields_Values();//(Fields_Values*)malloc(sizeof(Fields_Values));
    // Obtém a referência para a classe. A classe é carrega se necessário.
    classF = getClassRef(className);

    inst->cf = classF;

    cout << "Creating class " << className << endl;
    map<string, string> fbinds = classF->getFieldsNamesTypes();
    for(auto const &ent : fbinds) {
        string fname = ent.first;
        const char* ftype = ent.second.c_str();
        cout << fname << " " << ftype[0] << endl;

        FieldValue fval;
        fval = this->inicializaFval(ftype, 0);
        inst->field_instances[fname]= fval;
    }
    heap.push_back(inst);
    return inst;
}

FieldValue Jvm::inicializaFval(const char* ftype, int n){
    FieldValue fval;
    BaseType bval;
    ObjectType oval;
    ArrayType aval;
    switch(ftype[n]) {
        case 'B': //byte type
            bval.tag = BYTE;
            bval.val.byte = 0;
            fval.tag = BASETYPE;
            fval.val.btype = bval;
            break;
        case 'C': //char
            bval.tag = CHAR;
            bval.val.caractere = 0;
            fval.tag = BASETYPE;
            fval.val.btype = bval;
            break;
        case 'D': // double
            bval.tag = DUPLO;
            bval.val.duplo = 0;
            fval.tag = BASETYPE;
            fval.val.btype = bval;
            break;
        case 'F': // float
            bval.tag = PFLUTUANTE;
            bval.val.pFlutuante = 0;
            fval.tag = BASETYPE;
            fval.val.btype = bval;
            break;
        case 'I': // int
            bval.tag = INT;
            bval.val.inteiro = 0;
            fval.tag = BASETYPE;
            fval.val.btype = bval;
            break;
        case 'J': // long
            bval.tag = LONGO;
            bval.val.longo = 0;
            fval.tag = BASETYPE;
            fval.val.btype = bval;
            break;
        case 'S': // short
            bval.tag = CURTO;
            bval.val.curto = 0;
            fval.tag = BASETYPE;
            fval.val.btype = bval;
            break;
        case 'Z': // boolean
            bval.tag = BOOL;
            bval.val.boleano = false;
            fval.tag = BASETYPE;
            fval.val.btype = bval;
            break;
        case 'L': // reference
            oval.className = (char*)calloc(strlen(ftype) - 1, sizeof(char));
            strcpy(oval.className, ftype+1);
            fval.tag = OBJECTTYPE;
            fval.val.objtype = oval;
            break;
        case '[': // array
            fval.tag = ARRAYTYPE;
            aval.field = new std::vector<FieldValue>();
            aval.field->push_back(this->inicializaFval(ftype + n + 1, n+1));
            fval.val.arrtype = aval;
            break;
    }
    return fval;
}

/////////////////////////////////////////////////////////////////////////////
<<<<<<< HEAD
/** execMethod é criar o ambiente para que o método possa ser executado:
 * inicializa as informações no frame;
 * encontra e prepara method para execução;
 * encontra o índice do descritor do metodo.
 *
 */

Local_var Jvm::execStaticMethod(int n, ClassFile *classF, vector<Local_var> args) {
    Code_attribute *code_attr_pt = NULL;
    Frame frame(n, classF);
    Local_var lvar;
    Local_var_Type lvarval;

    for(vector<Local_var>::iterator it = args.begin(); it != args.end(); ++it){
        frame.localVarVector.push_back(*it);
    }
    this->fStack.push_back(frame);
    printf("Criei um frame\n");

    Interpretador interpreter(this);
    interpreter.runCode(&frame);

    // se a pilha estiver vazia consideramos que ela retornou void
    if(!fStack.back().operandStack.empty()){
        lvar = fStack.back().operandStack.back();
        printf("o metodo chamado retornou algo\n");
    }
    else{
        printf("o metodo chamado retornou void\n");
        lvar.tag = VOID_T;
        lvar.value.void_v = true;
    }
    this->fStack.pop_back();
    return lvar;
=======
int Jvm::execMethod(int atual, ClassFile classF) {
	int index, j, pc, buffer;
	uint32_t code_length;
	// Frame da javaStack.
	Frame frame;
	// Popula a pilha de variáveis locais. Ela recebe as variáveis locais do
	// método, inclusive os parâmetros.
	// Empilha o frame.
	this->jStack.push_back(frame);

 	index = classF.methods[atual].descriptor_index;
	for(j=0; j < classF.methods[atual].attributes_count; j++){
		printf("\t Attribute number: %d\n", j + 1);
        index = classF.methods[atual].attributes[j].attribute_name_index_l;
        printf("\t Attribute Name: %s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);
        printf("\t Attribute Length: %d\n", classF.methods[atual].attributes[j].attribute_length_l);

		if(!strcmp(classF.constant_pool[index-1].cp_union.constant_Utf8.bytes, "Code")){
            //achei o Code
            printf("\t Max Stack: %d, ", classF.methods[atual].attributes[j].attribute_union.attr_Code.max_stack);
            printf("\t Max Locals: %d, ", classF.methods[atual].attributes[j].attribute_union.attr_Code.max_locals);
            code_length = classF.methods[atual].attributes[j].attribute_union.attr_Code.code_length;
            printf("\t Code Length: %d\n", code_length);
            jStack.back().code_length = code_length;
            jStack.back().code = classF.methods[atual].attributes[j].attribute_union.attr_Code.code;
            // interpretar o opcode, saber qual é o tipo do operando, ler e colocar na pilha, antes de chamar a função
            //^^^^Falha aqui. O interpretador não atua somente em cima da pilha de operandos, ele deve pegar a string CODE
            //e interpretar (dur). Interpretador recebe a string code e, de acordo com o opcode lido, chama a instrução.
            //Instruçoes como o New, por exemplo, não utilizam apenas a pilha de operandos. New checa a constant pool para
            //checar o nome da classe (atributo passado para new); alocar espaço na heap (outra estrutura a qual deve ter acesso)
            //e por fim colocar na pilha a referência para a referencia para a instância (objectref) é colocado na pilha.
            //New só usou a pilha para obter um valor e devolver o resultado; todo o resto foi feito utilizando outras estruturas.
            //Assim, o mais correto para o interpretador seria: receber a string code; seu tamanho; receber o frame, contendo:
            //pc (para saber em qual instrução está); referencia para constant pool; vetor de variaveis locais; pilha de operandos.

            int arg_qnt = interpreter_code(&jStack/*, heap*/);
            }
        }
	// Esse é o interpretador mesmo. Ele passa pelas instruções executando uma
	// por uma.
	// Executa o código do método.
	//execCode();
	return 0;
>>>>>>> 4ae5775c31374efc6b2deface7b50b2bf9f61355
}

/////////////////////////////////////////////////////////////////////////////
/** execMethod é criar o ambiente para que o método possa ser executado:
 * inicializa as informações no frame;
 * encontra e prepara method para execução;
 * encontra o índice do descritor do metodo.
 *
 */

InstanceClass* Jvm::execVirtualMethod(int n, ClassFile *classF) {
    uint16_t descriptor_index;
    Frame frame(n, classF);
    InstanceClass *inst;
    Local_var lvar;
    Local_var_Type lvarval;

    /** Insere o this no localVarVector caso método não seja estático*/
    inst = this->alocarObjeto(classF->getClassName());
    //insere a instancia na heap para não se perder a referencia
    //note que a heap é só um monte de objetos largados soltos e perdidos
    heap.push_back(inst);
    lvar.tag = OBJECTTYPE;
    lvarval.reference_value = inst;
    lvar.value = lvarval;
    frame.localVarVector.push_back(lvar);

    this->fStack.push_back(frame);
    printf("Criei um frame\n");

    Interpretador interpreter(this);
    interpreter.runCode(&frame);

    this->fStack.pop_back();
    return inst;
}
