#define DEBUG

#include <stdio.h>
#include <map>
#include "../include/jvm.hpp"

using namespace std;

int Jvm::run(const char* arq_class_name) {
    //printf("Entrou em jvm.run()\n");
    ClassFile classF;
    int main_index;

    FILE *arquivoClass;
    vector<Local_var> args; //coloque a string de argumento aqui
    Local_var main_args;
    FieldValue main_str;
    main_str.tag = BASETYPE;
    main_str.val.btype.tag = STRINGTYPE;
    main_str.val.btype.val.stringue = new string("main args");
    main_args.tag = ARRAYTYPE;
    main_args.value.arr = new arrayref();
    main_args.value.arr->push_back(main_str);


    if( !(arquivoClass = fopen(arq_class_name, "rb"))) {
        printf("Erro em jvm.run: O arquivo .class %s, nao pode ser aberto.\n", arq_class_name);
        exit(0);
    }


    this->classpath = getClassPath(arq_class_name); //esta funcao esta no leitor.cpp

    leitorClass_info(&classF, arquivoClass);

    Verificador verificador(classF);
    verificador.verificaClass(classF);

    // Procura o método main na primeira classe carregada. Se não encontrar,
    // a execução é finalizada. Se encontrar, começa a execução.
    main_index = classF.findMethod("main", "([Ljava/lang/String;)V");
    if(main_index == -1){
        main_index = classF.findMethod("main", "()V");
    }
    else{
        args.push_back(main_args);
    }
    //printf("Valor de main_index: %d\n", main_index);
    if(main_index > 0){
        execMethod(main_index, &classF, args);
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
    if(loadedClasses.count(className) != 1) {
        if(!(arquivoClass = fopen((classpath + className + ".class").c_str(), "rb"))){ // procura no classpath
            if(!(arquivoClass = fopen((className + ".class").c_str(), "rb"))) { // se no encontrar procura no diretório do programa
                printf("Erro em getClassRef: O arquivo %s.class nao pode ser aberto.\n", className.c_str());
                exit(0);
            }
        }
        leitorClass_info(classF, arquivoClass);
        this->loadedClasses.insert(pair<string, ClassFile*>(className, classF));
    }
    else {
        classF = this->loadedClasses[className];
    }
    return classF;
}

/////////////////////////////////////////////////////////////////////////////
//Classe para iniciar instanciacao da classe
//Se ele o classfile ainda nao foi carregado, ele carrega
InstanceClass* Jvm::alocarObjetoEstatico(string className){
    ClassFile *classF;
    InstanceClass *inst;
    inst = new InstanceClass();

    // Obtém a referência para a classe. A classe é carrega se necessário.


    classF = getClassRef(className);
    inst->cf = classF;
    map<string, string> fbinds = classF->getStaticFieldsNamesTypes();

    for(auto const &ent : fbinds) {
        string fname = ent.first;
        const char* ftype = ent.second.c_str();

        FieldValue fval;
        fval = this->inicializaFval(ftype, 0);
        inst->field_instances[fname]= fval;
    }
    staticHeap[className] = inst;
    return inst;
}

InstanceClass* Jvm::alocarObjeto(string className){
    ClassFile *classF;
    InstanceClass *inst;
    inst = new InstanceClass();

    // Obtém a referência para a classe. A classe é carrega se necessário.


    classF = getClassRef(className);
    inst->cf = classF;
    map<string, string> m_buffer = classF->getFieldsNamesTypes();
    map<string, string> fbinds;
    string super_name = classF->getClassName(); // começa loop na classe invocadora
    do{
        fbinds.insert(m_buffer.begin(), m_buffer.end());
        classF = getClassRef(super_name);
        m_buffer = classF->getFieldsNamesTypes();
        super_name = classF->getSuper();
    }while(super_name.compare("java/lang/Object") != 0);

    for(auto const &ent : fbinds) {
        string fname = ent.first;
        const char* ftype = ent.second.c_str();

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
            bval.val.caractere = '\0';
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
            fval.tag = OBJECTTYPE;
            fval.val.objtype.instance = NULL;
            break;
        case '[': // array
            fval.tag = ARRAYTYPE;
            aval.arr = new std::vector<FieldValue>();
            aval.arr->push_back(this->inicializaFval(ftype + n + 1, n+1));
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

tuple<Local_var, Local_var> Jvm::execMethod(int method_index, ClassFile *classF, vector<Local_var> &args) {
    DEBUG_PRINT(endl << "============== " << classF->getClassName() << "." << classF->getMethodName(method_index) << " ==============");

    Local_var ret_var_h, ret_var_l;
    Frame frame(method_index, classF);

    string cname = classF->getClassName();
    Interpretador interpreter(this);
    //checamos se a classe possui variaveis estaticas, mas que ela ainda nao foi inicializada
    if(classF->getClassName().compare("Object") != 0){ // se for o Object, nao rode o clinit, ele tem register methods :(
        int clinitN = classF->findMethod("<clinit>", "()V");

        Frame staticFrame(clinitN, classF);

        if((clinitN != -1) && (this->staticHeap.count(classF->getClassName()) != 1)){
            //cout << "Clinit encontrado em: " << clinitN << endl;
            this->staticHeap[cname] = alocarObjetoEstatico(cname);
            interpreter.runCode(&staticFrame);
        }
    }


    frame.localVarVector.resize(0);

    for(vector<Local_var>::iterator it = args.begin(); it != args.end(); ++it){
        frame.localVarVector.push_back(*it);
    }

    this->fStack.push_back(frame);

    interpreter.runCode(&frame);

    DEBUG_PRINT(" ANTES:");DEBUG_ONLY(frame.printOperandStack());
    // Caso a pilha não esteja vazia checamos se o retorno é formado por 1 ou 2 Local_var.
    // Um valor de retorno só é formado por 2 Local_var`s se ele for um LONG ou um DOUBLE.
    if(!frame.operandStack.empty()){
       if(frame.operandStack.back().tag == LONGO || frame.operandStack.back().tag == DUPLO){
          
             ret_var_l = frame.operandStack.back();
             frame.operandStack.pop_back();
             ret_var_h = frame.operandStack.back();
             frame.operandStack.pop_back();
       }
       // Caso o valor retornado for formado somente por 1 Local_var.
       else{
             ret_var_l = frame.operandStack.back();
             frame.operandStack.pop_back();
             ret_var_h.tag = VOID_T;
             ret_var_h.value.void_v = true;
       }

        //printf("o metodo chamado retornou algo\n");
    }
    // se a pilha estiver vazia consideramos que ela retornou void
    else {
        //printf("o metodo chamado retornou void\n");
        ret_var_h.tag = VOID_T;
        ret_var_h.value.void_v = true;
        ret_var_l.tag = VOID_T;
        ret_var_l.value.void_v = true;
    }
    this->fStack.pop_back();

    DEBUG_PRINT("======= " << classF->getClassName() << "." << classF->getMethodName(method_index) << " Retornou: " << "high: " << ret_var_h.repr() << " low: " << ret_var_l.repr() << " ======== " << endl);
    return make_tuple(ret_var_h, ret_var_l);
}

#ifdef Debug
#undef Debug
#endif
