#include <stdio.h>
#include <map>
#include "../include/jvm.hpp"

using namespace std;

int Jvm::run(const char* arq_class_name) {
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
    Verificador verificador(classF);
    verificador.verificaClass(classF);
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
