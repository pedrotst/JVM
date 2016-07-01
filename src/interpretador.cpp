#include "../include/interpretador.hpp"


int Interpretador::execute_instruction(int opcode){
    return (*this.*instructions[opcode])();
}

int Interpretador::runCode(Frame *frame_pt) {
    int n = frame_pt->method_index;
    //Agora o interpretador sabe sobre o code e sobre o frame. FIM 8D
    this->frame_corrente = frame_pt;
    this->code_corrente = frame_pt->cf->getCodeAttr(n);
    this->descriptor_index = frame_pt->cf->methods[n].descriptor_index;

    uint8_t opcode;
    for(this->frame_corrente->pc = 0; this->frame_corrente->pc < this->code_corrente->code_length;) {
        opcode = this->code_corrente->code[this->frame_corrente->pc];
        this->frame_corrente->pc += this->execute_instruction(opcode);
    }
    return -1;
}


Interpretador::Interpretador(Jvm *jvm){

    this->jvm = jvm;
    std::vector<instructionFunction> pt(numOpcodes);
    pt[IADD] = &Interpretador::iadd;
//    pt[NOP] = &nop;
//    pt[ACONST_NULL] = &aConst_null;
    pt[ICONST_M1] = &Interpretador::iconst_m1;
    pt[ICONST_0] = &Interpretador::iconst_0;
    pt[ICONST_1] = &Interpretador::iconst_1;
    pt[ICONST_2] = &Interpretador::iconst_2;
    pt[ICONST_3] = &Interpretador::iconst_3;
    pt[ICONST_4] = &Interpretador::iconst_4;
    pt[ICONST_5] = &Interpretador::iconst_5;
//    pt[LCONST_0] = &lConst_0;
//    pt[LCONST_1] = &lConst_1;
//    pt[FCONST_0] = &fConst_0;
//    pt[FCONST_1] = &fConst_1;
//    pt[FCONST_2] = &fConst_2;
//    pt[DCONST_0] = &dConst_0;
//    pt[DCONST_1] = &dConst_1;
//    pt[BIPUSH] = &biPush;
//    pt[SIPUSH] = &siPush;
    pt[LDC] = &Interpretador::ldc;
//    pt[LDC_W] = &ldc_w;
//    pt[LDC2_W] = &ldc2_w;
//    pt[ILOAD] = &iLoad;
//    pt[LLOAD] = &lLoad;
//    pt[FLOAD] = &fLoad;
//    pt[DLOAD] = &dLoad;
//    pt[ALOAD] = &Interpretador::aload;
    pt[ALOAD_0] = &Interpretador::aload_0;
    pt[ALOAD_1] = &Interpretador::aload_1;
    pt[ALOAD_2] = &Interpretador::aload_2;
    pt[ALOAD_3] = &Interpretador::aload_3;
//    pt[FLOAD_0] = &fLoad_0;
//    pt[FLOAD_1] = &fLoad_1;
//    pt[FLOAD_2] = &fLoad_2;
//    pt[FLOAD_3] = &fLoad_3;
//    pt[DLOAD_0] = &dLoad_0;
//    pt[DLOAD_1] = &dLoad_1;
//    pt[DLOAD_2] = &dLoad_2;
//    pt[DLOAD_3] = &dLoad_3;
//    pt[ALOAD_0] = &aLoad_0;
//    pt[ALOAD_1] = &aLoad_1;
//    pt[ALOAD_2] = &aLoad_2;
//    pt[ALOAD_3] = &aLoad_3;
//    pt[IALOAD] = &iaLoad;
//    pt[LALOAD] = &laLoad;
//    pt[FALOAD] = &faLoad;
//    pt[DALOAD] = &daLoad;
//    pt[AALOAD] = &aaLoad;
//    pt[BALOAD] = &baLoad;
//    pt[CALOAD] = &caLoad;
//    pt[SALOAD] = &saLoad;
//    pt[ISTORE] = &iStore;
//    pt[LSTORE] = &lStore;
//    pt[FSTORE] = &fStore;
//    pt[DSTORE] = &dStore;
//    pt[ASTORE] = &aStore;
//    pt[ISTORE_0] = &iStore_0;
//    pt[ISTORE_1] = &iStore_1;
//    pt[ISTORE_2] = &iStore_2;
//    pt[ISTORE_3] = &iStore_3;
//    pt[LSTORE_0] = &lStore_0;
//    pt[LSTORE_1] = &lStore_1;
//    pt[LSTORE_2] = &lStore_2;
//    pt[LSTORE_3] = &lStore_3;
//    pt[FSTORE_0] = &fStore_0;
//    pt[FSTORE_1] = &fStore_1;
//    pt[FSTORE_2] = &fStore_2;
//    pt[FSTORE_3] = &fStore_3;
//    pt[DSTORE_0] = &dStore_0;
//    pt[DSTORE_1] = &dStore_1;
//    pt[DSTORE_2] = &dStore_2;
//    pt[DSTORE_3] = &dStore_3;
//    pt[ASTORE_0] = &aStore_0;
//    pt[ASTORE_1] = &aStore_1;
//    pt[ASTORE_2] = &aStore_2;
//    pt[ASTORE_3] = &aStore_3;
//    pt[IASTORE] = &iaStore;
//    pt[LASTORE] = &laStore;
//    pt[DASTORE] = &daStore;
//    pt[AASTORE] = &aaStore;
//    pt[BASTORE] = &baStore;
//    pt[CASTORE] = &caStore;
//    pt[SASTORE] = &saStore;
//    pt[POP] = &pop;
//    pt[POP2] = &pop2;
    pt[DUP] = &Interpretador::dup;
//    pt[DUP_X1] = &dup_x1;
//    pt[DUP_X2] = &dup_x2;
//    pt[DUP2] = &dup2;
//    pt[DUP2_X1] = &dup2_x1;
//    pt[DUP2_X2] = &dup2_x2;
//    pt[SWAP] = &swap;
//    pt[LADD] = &ladd;
//    pt[FADD] = &fadd;
//    pt[DADD] = &dadd;
//    pt[ISUB] = &isub;
//    pt[LSUB] = &lsub;
//    pt[FSUB] = &fsub;
//    pt[DSUB] = &dsub;
//    pt[IMUL] = &imul;
//    pt[LMUL] = &lmul;
//    pt[FMUL] = &fmul;
//    pt[DMUL] = &dmul;
//    pt[IDIv] = &idiv;
//    pt[LDIv] = &ldiv;
//    pt[FDIv] = &fdiv;
//    pt[DDIv] = &ddiv;
//    pt[IREM] = &irem;
//    pt[LREM] = &lrem;
//    pt[FREM] = &frem;
//    pt[DREM] = &drem;
//    pt[INEG] = &ineg;
//    pt[LNEG] = &lneg;
//    pt[FNEG] = &fneg;
//    pt[DNEG] = &dneg;
//    pt[ISHL] = &ishl;
//    pt[LSHL] = &lshl;
//    pt[ISHR] = &ishr;
//    pt[LSHR] = &lshr;
//    pt[IUSHR] = &iushr;
//    pt[LUSHR] = &lushr;
//    pt[IAND] = &iand;
//    pt[LAND] = &land;
//    pt[IOR] = &ior;
//    pt[LOR] = &lor;
//    pt[IXOR] = &ixor;
//    pt[LXOR] = &lxor;
//    pt[IINC] = &iinc;
//    pt[I2L] = &i2l;
//    pt[I2F] = &i2f;
//    pt[I2D] = &i2d;
//    pt[L2I] = &l2i;
//    pt[L2F] = &l2f;
//    pt[L2D] = &l2d;
//    pt[D2I] = &d2i;
//    pt[D2L] = &d2l;
//    pt[D2F] = &d2f;
//    pt[I2B] = &i2b;
//    pt[I2C] = &i2c;
//    pt[I2S] = &i2s;
//    pt[LCMP] = &lcmp;
//    pt[FCMPL] = &fcmpl;
//    pt[FCMPG] = &fcmpg;
//    pt[DCMPL] = &dcmpl;
//    pt[DCMPG] = &dcmpg;
//    pt[IFEQ] = &ifeq;
//    pt[IFNE] = &ifne;
//    pt[IFLT] = &iflt;
//    pt[IFGE] = &ifge;
//    pt[IFGT] = &ifgt;
//    pt[IFLT] = &iflt;
//    pt[IF_ICMPEQ] = &if_icmpeq;
//    pt[IF_ICMPNE] = &if_icmpne;
//    pt[IF_ICMPLT] = &if_icmplt;
//    pt[IF_ICMPGE] = &if_icmpge;
//    pt[IF_ICMPGT] = &if_cmpgt;
//    pt[IF_ICMPLE] = &if_cmple;
//    pt[IF_ACMPEQ] = &if_acmpeq;
//    pt[IF_ACMPNE] = &if_acmpne;
//    pt[GOTO] = &goto;
//    pt[JSR] = &jsr;
//    pt[RET] = &ret;
//    pt[TABLESWITCH] = &tableswitch;
//    pt[LOOKUPSWITCH] = &lookupswitch;
//    pt[IRETURN] = &ireturn;
//    pt[LRETURN] = &lreturn;
//    pt[FRETURN] = &freturn;
//    pt[DRETURN] = &dreturn;
//    pt[ARETURN] = &areturn;
//    pt[RETURN] = &return;
//    pt[GETSTATIC] = &getstatic;
//    pt[PUTSTATIC] = &putstatic;
//    pt[GETFIELD] = &getfield;
//    pt[PUTFIELD] = &putfield;
//    pt[INvOKEvIRTUAL] = &invokevirtual;
    pt[INvOKESPECIAL] = &Interpretador::invokespecial;
//    pt[INvOKESTATIC] = &invokestatic;
//    pt[INvOKEINTERFACE] = &invokeinterface;
//    pt[INvOKEDYNAMIC] = &invokedynamic;
    pt[NEW] = &Interpretador::new_op;
//    pt[NEWARRAY] = &newarray;
//    pt[ANEWARRAY] = &anewarray;
//    pt[ARRAYLENGTH] = &arraylength;
//    pt[ATHROW] = &athrow;
//    pt[CHACKCAST] = &checkcast;
//    pt[INSTANCEOF] = &instanceof;
//    pt[MONITORENTER] = &monitorenter;
//    pt[MONITOREXIT] = &monitorexit;
//    pt[WIDE] = &wide;
//    pt[MULTIANEWARRAY] = &multianewarray;
//    pt[IFNULL] = &ifnull;
//    pt[IFNONNULL] = &ifnonnull;
//    pt[GOTO_W] = &goto;
//    pt[JSR_W] = &jsr_w;
//    pt[BREAKPOINT] = &breakpoint;
//    pt[IMPDEP1] = &impdep1;
//    pt[IMPDEP2] = &impdep2;
    this->instructions = pt;
}

//void Interpretador::iadd(op_stack *opStack){
int Interpretador::iadd(){

    uint32_t lhs, rhs;
    Local_var op;
    Local_var_Type op_v;
    printf("Entrou na funcao iadd\n");
    lhs = frame_corrente->operandStack.back().value.int_value;//extrai o valor em operand
    this->frame_corrente->operandStack.pop_back();
    rhs = frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    printf("lhs: %d rhs: %d\n", lhs, rhs);
    op_v.int_value = lhs + rhs;
    op.value = op_v;
    op.tag = INT;
    //opStack->push_back(op);
    this->frame_corrente->operandStack.push_back(op);
    return 1;
}

/*
int Interpretador::ladd(){
    uint32_t operand1[2], operand2[2];
    printf("Entrou na funcao\n");
    operand1[0] = opStack->back();
    opStack->pop_back();
    operand1[1] = opStack->back();
    opStack->pop_back();

    operand2[0] = opStack->back();
    opStack->pop_back();
    operand2[1] = opStack->back();
    opStack->pop_back();

    opStack->push_back(operand1[0] + operand2[0]);
    opStack->push_back(operand1[1] + operand2[1]);
}*/
int Interpretador::ldc(){
    printf("Entrei na ldc\n");
    uint8_t index = code_corrente->code[frame_corrente->pc+1];
    printf("Index: %d\n", index);

    Local_var operand;
    cp_tag tag = this->frame_corrente->cf->constant_pool[index-1].tag;
    printf("Tag: %d\n", tag);
    //utilizado formato if()/else if() por alguns casos necessitarem de declarar variaveis
    if(tag == CONSTANT_Integer){
            operand.tag = INT;
            operand.value.int_value = this->frame_corrente->cf->constant_pool[index-1].cp_union.constant_integer.bytes;
            //colocar o valor na operand stack
            this->frame_corrente->operandStack.push_back(operand);
    }else if(tag == CONSTANT_Float){
            //  SEM SUPORTE
            //operand.tag = PFLUTUANTE;
            //operand.value.float_value.bytes;
            //colocar o valor na operand stack
   }else if(tag == CONSTANT_String){
            printf("ldc de String\n");
            //cria uma instância de objeto String e coloca a
            //referência dessa instância na pilha

            std::string stringClass("String");
            InstanceClass *inst = jvm->alocarObjeto(stringClass);

            //criando instância
            operand.tag = OBJECTTYPE;
            inst->cf = jvm->getClassRef(stringClass);//referencia ao classFile de String
            inst->field_instances = new Fields_Values;
            inst->field_instances->push_back(jvm->inicializaFval("L", 0));
            /*na linha abaixo, colocar o valor que a instância deve receber informado via index.
              Como colocar o valor se ObjectType tem apenas o nome da classe como campo?
              Tem que ser via field_instances, mas para isso tem que se conhecer a organização
              interna de String.class*/

            //colocar a referencia da string na operand stack
            operand.value.reference_value = inst;
            this->frame_corrente->operandStack.push_back(operand);
   }else if(tag == CONSTANT_Class){
            //resolver a classe e colocar a refeência ao class object (value) na operand stack
            operand.tag = OBJECTTYPE;

            /*abaixo nao pode ser utilizado getClassName() porque
              não necessariamente o objeto instanciado será da mesma classe
              a qual pertence o método em execução
              (ex: método de Puppy.class pode instanciar Cocô.class)*/
            uint16_t utf8_index = this->frame_corrente->cf->constant_pool[index-1].cp_union.constant_class.name_index;
            std::string className(this->frame_corrente->cf->constant_pool[utf8_index-1].cp_union.constant_Utf8.bytes);

            InstanceClass *inst = jvm->alocarObjeto(className);
            inst->cf = jvm->getClassRef(className);//a instância deve receber referência de onde foi alocado o ClassFile
            inst->field_instances = new Fields_Values;
            inst->field_instances->push_back(jvm->inicializaFval("L", 0));
            /*falta colocar o valor*/


   }else if(tag == CONSTANT_MethodType){
   }else if(tag == CONSTANT_MethodHandle){
            //resolver o methodType ou methodHandle e colocar na operand stack a referência para a instância resultante de
            //java.lang.invoke.MethodType ou java.lang.invoke.MethodHandle
   }else{
            //exception
    }
    return 2;//opcode e byte seguinde lidos
}

int Interpretador::dup(){
    printf("Entrei na dup\n");
    this->frame_corrente->operandStack.push_back( this->frame_corrente->operandStack.back() );
    return 1;//opcode lido
}


//void Interpretador::new_op(op_stack *opStack){
int Interpretador::new_op(){
    printf("Cheguei na new\n");
    uint8_t operand = code_corrente->code[frame_corrente->pc+1];//pc aponta para a instrução; pc+1 é o byte seguinte
    uint16_t name_index = operand;
    std::string className;
    Local_var op;
    Local_var_Type op_val;

    name_index = name_index << 8;
    operand = code_corrente->code[frame_corrente->pc+2];
    name_index = name_index|operand;
    printf("new #%d\n", name_index);
    className = this->frame_corrente->cf->getCpoolClass(name_index);

    printf("nome da classe: %s\n", className.c_str());
    op.tag = OBJECTTYPE;
    op_val.reference_value = jvm->alocarObjeto(className);
    op.value = op_val;
    frame_corrente->operandStack.push_back(op);
    printf("Sai da new\n");
    return 3; //dois bytes lidos + o opcode
}

int Interpretador::invokespecial(){
    uint8_t operand = code_corrente->code[frame_corrente->pc+1];
    uint16_t method_index = operand;
    string invoking_class, method_name, descriptor;
    ClassFile* cf;
    vector<Local_var> args;

    method_index = method_index << 8;
    operand = code_corrente->code[frame_corrente->pc+2];
    method_index = method_index|operand;
    this->frame_corrente->cf->getCpoolMethod(method_index, invoking_class, method_name, descriptor);
    printf("invokespecial #%d\t//%s.%s:%s\n", method_index, invoking_class.c_str(), method_name.c_str(), descriptor.c_str());
    cf = this->jvm->getClassRef(invoking_class);
    string argtypes;

    for (int i=1; i < descriptor.find(")"); i++){
        argtypes += descriptor[i];
        cout << argtypes;
        args.push_back(this->frame_corrente->operandStack.back());
        this->frame_corrente->operandStack.back();
    }

    cout << endl;

    this->jvm->execStaticMethod(method_index, cf, args);



    return 3;
}

int Interpretador::aload_0(){
    printf("coloquei a primeiro variável na pilha");
    this->frame_corrente->operandStack.push_back(this->frame_corrente->localVarVector[0]);
    return 1;
}
int Interpretador::aload_1(){
    this->frame_corrente->operandStack.push_back(this->frame_corrente->localVarVector[1]);
    return 1;
}
int Interpretador::aload_2(){
    this->frame_corrente->operandStack.push_back(this->frame_corrente->localVarVector[2]);
    return 1;
}
int Interpretador::aload_3(){
    this->frame_corrente->operandStack.push_back(this->frame_corrente->localVarVector[3]);
    return 1;
}


int Interpretador::iconst_m1(){
    Local_var op;
    op.tag = INT;
    op.value.int_value = -1;
    this->frame_corrente->operandStack.push_back(op);
    return 1;
}
int Interpretador::iconst_0(){
    Local_var op;
    op.tag = INT;
    op.value.int_value = 0;
    this->frame_corrente->operandStack.push_back(op);
    return 1;
}
int Interpretador::iconst_1(){
    Local_var op;
    op.tag = INT;
    op.value.int_value = 1;
    this->frame_corrente->operandStack.push_back(op);
    printf("joguei o 1 no opstack\n");
    return 1;
}
int Interpretador::iconst_2(){
    Local_var op;
    op.tag = INT;
    op.value.int_value = 2;
    this->frame_corrente->operandStack.push_back(op);
    return 1;
}
int Interpretador::iconst_3(){
    Local_var op;
    op.tag = INT;
    op.value.int_value = 3;
    this->frame_corrente->operandStack.push_back(op);
    return 1;
}
int Interpretador::iconst_4(){
    Local_var op;
    op.tag = INT;
    op.value.int_value = 4;
    this->frame_corrente->operandStack.push_back(op);
    return 1;
}
int Interpretador::iconst_5(){
    Local_var op;
    op.tag = INT;
    op.value.int_value = 5;
    this->frame_corrente->operandStack.push_back(op);
    return 1;
}
//
//void fadd(jStackFrame &jStack){
//}
//
//void dadd(jStackFrame &jStack){
//}
