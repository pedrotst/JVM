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
    Local_var main_str;

    args.push_back(main_str);
    if( !(arquivoClass = fopen(arq_class_name, "rb"))) {
        printf("O arquivo .class %s, nao pode ser aberto.\n", arq_class_name);
        exit(0);
    }


    //printf("Executando leitura do .class\n");
    leitorClass_info(&classF, arquivoClass);
    //printf("Leitura executada\n");
    Verificador verificador(classF);
    verificador.verificaClass(classF);
    // Procura o método main na primeira classe carregada. Se não encontrar,
    // a execução é finalizada. Se encontrar, começa a execução.
    main_index = classF.findMethod("main", "([Ljava/lang/String;)V");
    printf("Valor de main_index: %d\n", main_index);
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
            cout << className << endl;
        if(!(arquivoClass = fopen(className.append(".class").c_str(), "rb"))) {
            printf("O arquivo .class nao pode ser aberto.\n");
            exit(0);
        }
        leitorClass_info(classF, arquivoClass);
        this->loadedClasses.insert(pair<string, ClassFile*>(className, classF));
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
InstanceClass* Jvm::alocarObjetoEstatico(string className){
    ClassFile *classF;
    InstanceClass *inst;
    int found_obj;
    inst = new InstanceClass();

    // Obtém a referência para a classe. A classe é carrega se necessário.

    inst->cf = classF;

    classF = getClassRef(className);
    map<string, string> fbinds = classF->getStaticFieldsNamesTypes();

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

InstanceClass* Jvm::alocarObjeto(string className){
    ClassFile *classF;
    InstanceClass *inst;
    int found_obj;
    inst = new InstanceClass();

    // Obtém a referência para a classe. A classe é carrega se necessário.

    inst->cf = classF;

    classF = getClassRef(className);
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
            oval.instance = new InstanceClass;
            fval.tag = OBJECTTYPE;
            fval.val.objtype = oval;
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

Local_var Jvm::execMethod(int n, ClassFile *classF, vector<Local_var> args) {
    printf("Entrou em execMethod\n");
    Code_attribute *code_attr_pt = NULL;
    Frame frame(n, classF);
    Local_var lvar;
    Local_var_Type lvarval;

    string cname = classF->getClassName();
    Interpretador interpreter(this);

    //checamos se a classe possui variaveis estaticas, mas que ela ainda nao foi inicializada
    int clinitN = classF->findMethod("<clinit>", "()V");

    Frame staticFrame(clinitN, classF);

    if((clinitN != -1) && (this->staticHeap.count(classF->getClassName()) != 1)){
        cout << "Clinit encontrado em: " << clinitN << endl;
        this->staticHeap[cname] = alocarObjetoEstatico(cname);
        cout << "passei" << endl;
        interpreter.runCode(&staticFrame);
    }


    for(vector<Local_var>::iterator it = args.begin(); it != args.end(); ++it){
        //cout << "var type: " << it->tag << endl;
        frame.localVarVector.push_back(*it);
    }

    this->fStack.push_back(frame);
    printf("Criei um frame\n");

    interpreter.runCode(&frame);


    // se a pilha estiver vazia consideramos que ela retornou void

    if(!fStack.back().operandStack.empty()){
        lvar = fStack.back().operandStack.back();
        //printf("o metodo chamado retornou algo\n");
    }
    else{
        //printf("o metodo chamado retornou void\n");
        lvar.tag = VOID_T;
        lvar.value.void_v = true;
    }
    this->fStack.pop_back();
    return lvar;
}
