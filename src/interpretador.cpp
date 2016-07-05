#include "../include/interpretador.hpp"

//------Verificar se faz sentido isso!!----------
int Interpretador::execute_instruction(int opcode){
    if(opcode <= instructions.size()){
        return (*this.*instructions[opcode])();
    }
    else{
        printf("Instrucao nao especificada!\n");
        exit(-1);
    }
}

int Interpretador::runCode(Frame *frame_pt) {
    int n = frame_pt->method_index;

    this->frame_corrente = frame_pt;
    this->code_corrente = frame_pt->cf->getCodeAttr(n);
    this->descriptor_index = frame_pt->cf->methods[n].descriptor_index;

    uint8_t opcode;
    printf("Estou em interpretador.runCode()\n");
    for(this->frame_corrente->pc = 0; this->frame_corrente->pc < this->code_corrente->code_length;) {
        printf("pc->code[%ld]: ", this->frame_corrente->pc);
        opcode = this->code_corrente->code[this->frame_corrente->pc];
        this->frame_corrente->pc += this->execute_instruction(opcode);
    }
    return -1;
}


Interpretador::Interpretador(Jvm *jvm){

    this->jvm = jvm;
    std::vector<instructionFunction> pt(numOpcodes);
    pt[IADD] = &Interpretador::iadd;
    pt[NOP] = &Interpretador::nop;
    pt[ACONST_NULL] = &Interpretador::aconst_null;
    pt[ICONST_M1] = &Interpretador::iconst_m1;
    pt[ICONST_0] = &Interpretador::iconst_0;
    pt[ICONST_1] = &Interpretador::iconst_1;
    pt[ICONST_2] = &Interpretador::iconst_2;
    pt[ICONST_3] = &Interpretador::iconst_3;
    pt[ICONST_4] = &Interpretador::iconst_4;
    pt[ICONST_5] = &Interpretador::iconst_5;
    pt[LCONST_0] = &Interpretador::lconst_0;
    pt[LCONST_1] = &Interpretador::lconst_1;
//    pt[FCONST_0] = &fConst_0;
//    pt[FCONST_1] = &fConst_1;
//    pt[FCONST_2] = &fConst_2;
//    pt[DCONST_0] = &dConst_0;
//    pt[DCONST_1] = &dConst_1;
    pt[BIPUSH] = &Interpretador::bipush;
    pt[SIPUSH] = &Interpretador::sipush;
    pt[LDC] = &Interpretador::ldc;
//    pt[LDC_W] = &ldc_w;
//    pt[LDC2_W] = &ldc2_w;
    pt[ILOAD_0] = &Interpretador::iload_0;
    pt[ILOAD_1] = &Interpretador::iload_1;
    pt[ILOAD_2] = &Interpretador::iload_2;
    pt[ILOAD_3] = &Interpretador::iload_3; // vou deixar os mesmos que os iload pq � a mesma coisa, a diferen�a � s� a tipagem
    pt[LLOAD] = &Interpretador::lload;
    pt[FLOAD] = &Interpretador::fload;
//    pt[DLOAD] = &dLoad;
    pt[ALOAD] = &Interpretador::aload;
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
    pt[ISTORE] = &Interpretador::istore;
//    pt[LSTORE] = &lStore;
//    pt[FSTORE] = &fStore;
//    pt[DSTORE] = &dStore;
//    pt[ASTORE] = &aStore;
    pt[ISTORE_0] = &Interpretador::istore_0;
    pt[ISTORE_1] = &Interpretador::istore_1;
    pt[ISTORE_2] = &Interpretador::istore_2;
    pt[ISTORE_3] = &Interpretador::istore_3;
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
    pt[ASTORE_0] = &Interpretador::astore_0;
    pt[ASTORE_1] = &Interpretador::astore_1;
    pt[ASTORE_2] = &Interpretador::astore_2;
    pt[ASTORE_3] = &Interpretador::astore_3;
//    pt[IASTORE] = &iaStore;
//    pt[LASTORE] = &laStore;
//    pt[DASTORE] = &daStore;
//    pt[AASTORE] = &aaStore;
//    pt[BASTORE] = &baStore;
//    pt[CASTORE] = &caStore;
//    pt[SASTORE] = &saStore;
    pt[POP] = &Interpretador::pop;
    pt[POP2] = &Interpretador::pop2;
    pt[DUP] = &Interpretador::dup;
    pt[DUP_X1] = &Interpretador::dup_x1;
    pt[DUP_X2] = &Interpretador::dup_x2;
    pt[DUP2] = &Interpretador::dup2;
    pt[DUP2_X1] = &Interpretador::dup2_x1;
    pt[DUP2_X2] = &Interpretador::dup2_x2;
    pt[SWAP] = &Interpretador::swap_op;
//    pt[LADD] = &ladd;
//    pt[FADD] = &fadd;
//    pt[DADD] = &dadd;
    pt[ISUB] = &Interpretador::isub;
    pt[LSUB] = &Interpretador::lsub;
//    pt[FSUB] = &fsub;
//    pt[DSUB] = &dsub;
    pt[IMUL] = &Interpretador::imul;
    pt[LMUL] = &Interpretador::lmul;
//    pt[FMUL] = &fmul;
//    pt[DMUL] = &dmul;
//    pt[IDIv] = &idiv;
//    pt[LDIv] = &ldiv;
//    pt[FDIv] = &fdiv;
//    pt[DDIv] = &ddiv;
    pt[IREM] = &Interpretador::irem;
//    pt[LREM] = &lrem;
//    pt[FREM] = &frem;
//    pt[DREM] = &drem;
    pt[INEG] = &Interpretador::ineg;
//    pt[LNEG] = &lneg;
//    pt[FNEG] = &fneg;
//    pt[DNEG] = &dneg;
    pt[ISHL] = &Interpretador::ishl;
//    pt[LSHL] = &lshl;
    pt[ISHR] = &Interpretador::ishr;
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
   pt[I2D] = &Interpretador::i2d;
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
    pt[IFEQ] = &Interpretador::ifeq;
    pt[IFNE] = &Interpretador::ifne;
    pt[IFLT] = &Interpretador::iflt;
    pt[IFLE] = &Interpretador::ifle;
    pt[IFGE] = &Interpretador::ifge;
    pt[IFGT] = &Interpretador::ifgt;
    pt[IF_ICMPEQ] = &Interpretador::if_icmpeq;
    pt[IF_ICMPNE] = &Interpretador::if_icmpne;
    pt[IF_ICMPLT] = &Interpretador::if_icmplt;
    pt[IF_ICMPLE] = &Interpretador::if_icmple;
    pt[IF_ICMPGE] = &Interpretador::if_icmpge;
    pt[IF_ICMPGT] = &Interpretador::if_icmpgt;
    pt[IF_ACMPEQ] = &Interpretador::if_acmpeq;
    pt[IF_ACMPNE] = &Interpretador::if_acmpne;
    pt[GOTO] = &Interpretador::goto_java;
//    pt[JSR] = &jsr;
//    pt[RET] = &ret;
//    pt[TABLESWITCH] = &tableswitch;
//    pt[LOOKUPSWITCH] = &lookupswitch;
    pt[IRETURN] = &Interpretador::ireturn;
//    pt[LRETURN] = &lreturn;
//    pt[FRETURN] = &freturn;
//    pt[DRETURN] = &dreturn;
//    pt[ARETURN] = &areturn;
    pt[RETURN] = &Interpretador::return_op;
    pt[GETSTATIC] = &Interpretador::getfield;
    pt[PUTSTATIC] = &Interpretador::putfield;
    pt[GETFIELD] = &Interpretador::getfield;
    pt[PUTFIELD] = &Interpretador::putfield;
    pt[INVOKEVIRTUAL] = &Interpretador::invokevirtual;
    pt[INVOKESPECIAL] = &Interpretador::invokespecial;
//    pt[INvOKESTATIC] = &invokestatic;
//    pt[INvOKEINTERFACE] = &invokeinterface;
//    pt[INvOKEDYNAMIC] = &invokedynamic;
    pt[NEW] = &Interpretador::new_op;
//    pt[NEWARRAY] = &newarray;
    pt[ANEWARRAY] = &Interpretador::anewarray;
//    pt[ARRAYLENGTH] = &arraylength;
    pt[ATHROW] = &Interpretador::athrow;
//    pt[CHACKCAST] = &checkcast;
//    pt[INSTANCEOF] = &instanceof;
      // Utiliizada na println. Tem a ver com threads e por isso acho que não deve ser
      // implementada. Vai ver só precisa retornar.
    pt[MONITORENTER] = &Interpretador::monitorenter;
    pt[MONITOREXIT] = &Interpretador::monitorexit;
//    pt[WIDE] = &wide;
//    pt[MULTIANEWARRAY] = &multianewarray;
    pt[IFNULL] = &Interpretador::ifnull;
    pt[IFNONNULL] = &Interpretador::ifnonnull;
//    pt[GOTO_W] = &goto;
//    pt[JSR_W] = &jsr_w;
//    pt[BREAKPOINT] = &breakpoint;
//    pt[IMPDEP1] = &impdep1;
//    pt[IMPDEP2] = &impdep2;
    this->instructions = pt;
}

int Interpretador::nop(){
    printf("Executando nop\n");
    return 1;
}

int Interpretador::aconst_null(){
    printf("Executando aconst_null\n");
    Local_var operand;
    operand.tag = OBJECTTYPE;
    operand.value.reference_value = NULL;
    this->frame_corrente->operandStack.push_back(operand);
    return 1;
}

int Interpretador::iconst_m1(){
    printf("Executando iconst_m1\n");
    Local_var op;
    op.tag = INT;
    op.value.int_value = -1;
    this->frame_corrente->operandStack.push_back(op);
    return 1;
}
int Interpretador::iconst_0(){
    printf("Executando iconst_0\n");
    Local_var op;
    op.tag = INT;
    op.value.int_value = 0;
    this->frame_corrente->operandStack.push_back(op);
    return 1;
}
int Interpretador::iconst_1(){
    printf("Executando iconst_1\n");
    Local_var op;
    op.tag = INT;
    op.value.int_value = 1;
    this->frame_corrente->operandStack.push_back(op);
    //printf("joguei o 1 no opstack\n");
    return 1;
}
int Interpretador::iconst_2(){
    printf("Executando iconst_2\n");
    Local_var op;
    op.tag = INT;
    op.value.int_value = 2;
    this->frame_corrente->operandStack.push_back(op);
    return 1;
}
int Interpretador::iconst_3(){
    printf("Executando iconst_3\n");
    Local_var op;
    op.tag = INT;
    op.value.int_value = 3;
    this->frame_corrente->operandStack.push_back(op);
    return 1;
}
int Interpretador::iconst_4(){
    printf("Executando iconst_4\n");
    Local_var op;
    op.tag = INT;
    op.value.int_value = 4;
    this->frame_corrente->operandStack.push_back(op);
    return 1;
}
int Interpretador::iconst_5(){
    printf("Executando iconst_5\n");
    Local_var op;
    op.tag = INT;
    op.value.int_value = 5;
    this->frame_corrente->operandStack.push_back(op);
    return 1;
}

int Interpretador::lconst_0(){
    printf("Executando lconst_0\n");
    Local_var operand[2];
    operand[0].tag = LONGO;
    operand[1].tag = LONGO;
    operand[0].value.long_value = 0;
    operand[1].value.long_value = 0;
    this->frame_corrente->operandStack.push_back(operand[1]);
    this->frame_corrente->operandStack.push_back(operand[0]);
    return 1;
}

int Interpretador::lconst_1(){
    printf("Executando lconst_1\n");
    Local_var operand[2];
    operand[0].tag = LONGO;
    operand[1].tag = LONGO;
    operand[0].value.long_value = 1;
    operand[1].value.long_value = 0;
    this->frame_corrente->operandStack.push_back(operand[1]);
    this->frame_corrente->operandStack.push_back(operand[0]);
    return 1;
}


//int Interpretador::fconst_0(){}
//int Interpretador::fconst_1(){}
//int Interpretador::fconst_2(){}

//int Interpretador::dconst_0(){}
//int Interpretador::dconst_1(){}

int Interpretador::bipush(){
    //o byte � convertido para int, com sinal extendido, e colocado na stack
    printf("Executando bipush\n");
    Local_var operand;
    operand.tag = INT;//quest�es conceituais aqui
    operand.value.int_value = this->code_corrente->code[this->frame_corrente->pc+1];
    this->frame_corrente->operandStack.push_back(operand);
    return 2;
}

int Interpretador::sipush(){
    printf("Executando sipush\n");
    Local_var operand;
    operand.tag = CURTO;
    operand.value.int_value = this->code_corrente->code[this->frame_corrente->pc+1];
    operand.value.int_value <<= 8;
    operand.value.int_value |= this->code_corrente->code[this->frame_corrente->pc+2];
    this->frame_corrente->operandStack.push_back(operand);
    return 3;
}

int Interpretador::ldc(){
    printf("Executando ldc\n");
    uint8_t index = code_corrente->code[frame_corrente->pc+1];

    Local_var operand;
    cp_tag tag = this->frame_corrente->cf->constant_pool[index-1].tag;
    //utilizado formato if()/else if() por alguns casos necessitarem de declarar variaveis
    if(tag == CONSTANT_Integer){
            operand.tag = INT;
            operand.value.int_value = this->frame_corrente->cf->constant_pool[index-1].cp_union.constant_integer.bytes;
            //colocar o valor na operand stack
            this->frame_corrente->operandStack.push_back(operand);
    }else if(tag == CONSTANT_Float){
            //  SEM SUPORTE
            //operand.tag = PFLUTUANTE;
            //operand.value.float_value.bytes = this->frame_corrente->cf->constant_pool[index-1].cp_union.constant_integer.bytes;
            //colocar o valor na operand stack
            //this->frame_corrente->operandStack.push_back(operand);
   }else if(tag == CONSTANT_String){
            //printf("ldc de String\n");
            //cria uma instancia de objeto String e coloca a
            //referencia dessa instancia na pilha

//            std::string stringClass("java/lang/String");
//            InstanceClass *inst = jvm->alocarObjeto(stringClass);//tenho uma inst�ncia para java\lang\String

            operand.tag = STRINGTYPE;
//            operand.value.reference_value = inst;
//            inst->cf = jvm->getClassRef(stringClass);

            uint8_t utf8_index = this->frame_corrente->cf->constant_pool[index-1].cp_union.constant_string.string_index;
            operand.value.string_value = new string(this->frame_corrente->cf->constant_pool[utf8_index-1].cp_union.constant_Utf8.bytes);
            //operand.value.string_value = this->frame_corrente->cf->constant_pool[index-1].cp_union.constant_Utf8.bytes;
//            FieldValue field;
//            field.tag = ARRAYTYPE;
//            field.val.arrtype.arr = new arrayref;
//            for(int i = 0; i<string_value.size(); i++){
//                    FieldValue carac;
//                    carac.tag = BASETYPE;
//                    carac.val.btype.tag = CHAR;
//                    carac.val.btype.val.caractere = string_value[i];
//                    field.val.arrtype.arr->push_back(carac);
//            }
//            string val("value");
//            inst->field_instances[val] = field;
            this->frame_corrente->operandStack.push_back(operand);
   }else if(tag == CONSTANT_Class){
            operand.tag = OBJECTTYPE;

            /*abaixo nao pode ser utilizado getClassName() porque
              nao necessariamente o objeto instanciado sera da mesma classe
              a qual pertence o metodo em execucao
              (ex: metodo de Puppy.class pode instanciar Coco.class)*/
            uint16_t utf8_index = this->frame_corrente->cf->constant_pool[index-1].cp_union.constant_class.name_index;
            std::string className(this->frame_corrente->cf->constant_pool[utf8_index-1].cp_union.constant_Utf8.bytes);

            InstanceClass *inst = jvm->alocarObjeto(className);
            inst->cf = jvm->getClassRef(className);

            operand.value.reference_value = inst;
            this->frame_corrente->operandStack.push_back(operand);
   }else if(tag == CONSTANT_MethodType){
   }else if(tag == CONSTANT_MethodHandle){
            //resolver o methodType ou methodHandle e colocar na operand stack a refer�ncia para a inst�ncia resultante de
            //java.lang.invoke.MethodType ou java.lang.invoke.MethodHandle
   }else{
            //exception
    }
    return 2;//opcode e byte seguinde lidos
}

//int Interpretador::ldc_w(){}
//int Interpretador::ldc2_w(){}

int Interpretador::iload(){
    printf("Executando iload\n");
    Local_var operand;
    operand.tag = INT;
    uint16_t index = this->code_corrente->code[this->frame_corrente->pc+1];
    operand = this->frame_corrente->localVarVector[index-1];
    this->frame_corrente->operandStack.push_back(operand);
    return 2;
}

int Interpretador::lload(){
    printf("Executando lload\n");
    Local_var operand[2];
    operand[0].tag = LONGO;
    operand[1].tag = LONGO;
    uint16_t index = this->code_corrente->code[this->frame_corrente->pc+1];
    operand[0] = this->frame_corrente->localVarVector[index-1];
    operand[1] = this->frame_corrente->localVarVector[index];
    this->frame_corrente->operandStack.push_back(operand[1]);
    this->frame_corrente->operandStack.push_back(operand[0]);
    return 2;
}

int Interpretador::fload(){
    printf("Executando fload\n");
    Local_var operand;
    operand.tag = PFLUTUANTE;
    uint16_t index = this->code_corrente->code[this->frame_corrente->pc+1];
    operand = this->frame_corrente->localVarVector[index-1];
    this->frame_corrente->operandStack.push_back(operand);
    return 2;
}

int Interpretador::dload(){
    printf("Executando dload\n");
    Local_var operand[2];
    operand[0].tag = DUPLO;
    operand[1].tag = DUPLO;
    uint16_t index = this->code_corrente->code[this->frame_corrente->pc+1];
    operand[0] = this->frame_corrente->localVarVector[index-1];
    operand[1] = this->frame_corrente->localVarVector[index];
    this->frame_corrente->operandStack.push_back(operand[1]);
    this->frame_corrente->operandStack.push_back(operand[0]);
    return 2;
}

int Interpretador::aload(){
    printf("Executando aload\n");
    Local_var operand;
    operand.tag = OBJECTTYPE;
    uint16_t index = this->code_corrente->code[this->frame_corrente->pc+1];
    operand = this->frame_corrente->localVarVector[index-1];
    this->frame_corrente->operandStack.push_back(operand);
    return 2;
}


int Interpretador::lload_0(){
    printf("Executando lload_0\n");
    Local_var lvar = this->frame_corrente->localVarVector[0];
    if(lvar.tag != LONGO){
        printf("Variavel local carregada nao eh um long, abortar\n");
        exit(0);
    }
    lvar = this->frame_corrente->localVarVector[1];
    if(lvar.tag != LONGO){
        printf("Variavel local carregada nao eh um long, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[0]);
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[1]);
    return 1;
}

int Interpretador::lload_1(){
    printf("Executando lload_1\n");
    Local_var lvar = this->frame_corrente->localVarVector[1];
    if(lvar.tag != LONGO){
        printf("Variavel local carregada nao eh um long, abortar\n");
        exit(0);
    }
    lvar = this->frame_corrente->localVarVector[2];
    if(lvar.tag != LONGO){
        printf("Variavel local carregada nao eh um long, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[1]);
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[2]);
    return 1;
}

int Interpretador::lload_2(){
    printf("Executando lload_2\n");
    Local_var lvar = this->frame_corrente->localVarVector[2];
    if(lvar.tag != LONGO){
        printf("Variavel local carregada nao eh um long, abortar\n");
        exit(0);
    }
    lvar = this->frame_corrente->localVarVector[3];
    if(lvar.tag != LONGO){
        printf("Variavel local carregada nao eh um long, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[2]);
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[3]);
    return 1;
}

int Interpretador::lload_3(){
    printf("Executando lload_3\n");
    Local_var lvar = this->frame_corrente->localVarVector[3];
    if(lvar.tag != LONGO){
        printf("Variavel local carregada nao eh um long, abortar\n");
        exit(0);
    }
    lvar = this->frame_corrente->localVarVector[4];
    if(lvar.tag != LONGO){
        printf("Variavel local carregada nao eh um long, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[3]);
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[4]);
    return 1;
}

int Interpretador::fload_0(){
    printf("Executando fload_0\n");
    Local_var lvar = this->frame_corrente->localVarVector[0];
    if(lvar.tag != PFLUTUANTE){
        printf("Variavel local carregada nao eh um float, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[0]);
    return 1;
}

int Interpretador::fload_1(){
    printf("Executando fload_1\n");
    Local_var lvar = this->frame_corrente->localVarVector[1];
    if(lvar.tag != PFLUTUANTE){
        printf("Variavel local carregada nao eh um float, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[1]);
    return 1;
}

int Interpretador::fload_2(){
    printf("Executando fload_2\n");
    Local_var lvar = this->frame_corrente->localVarVector[2];
    if(lvar.tag != PFLUTUANTE){
        printf("Variavel local carregada nao eh um float, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[2]);
    return 1;
}

int Interpretador::fload_3(){
    printf("Executando fload_3\n");
    Local_var lvar = this->frame_corrente->localVarVector[3];
    if(lvar.tag != PFLUTUANTE){
        printf("Variavel local carregada nao eh um float, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[3]);
    return 1;
}

int Interpretador::dload_0(){
    printf("Executando dload_0\n");
    Local_var lvar = this->frame_corrente->localVarVector[0];
    if(lvar.tag != DUP){
        printf("Variavel local carregada nao eh um double, abortar\n");
        exit(0);
    }
    lvar = this->frame_corrente->localVarVector[1];
    if(lvar.tag != DUP){
        printf("Variavel local carregada nao eh um double, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[0]);
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[1]);
    return 1;
}

int Interpretador::dload_1(){
    printf("Executando dload_1\n");
    Local_var lvar = this->frame_corrente->localVarVector[1];
    if(lvar.tag != DUP){
        printf("Variavel local carregada nao eh um double, abortar\n");
        exit(0);
    }
    lvar = this->frame_corrente->localVarVector[2];
    if(lvar.tag != DUP){
        printf("Variavel local carregada nao eh um double, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[1]);
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[2]);
    return 1;
}

int Interpretador::dload_2(){
    printf("Executando dload_2\n");
    Local_var lvar = this->frame_corrente->localVarVector[2];
    if(lvar.tag != DUP){
        printf("Variavel local carregada nao eh um double, abortar\n");
        exit(0);
    }
    lvar = this->frame_corrente->localVarVector[3];
    if(lvar.tag != DUP){
        printf("Variavel local carregada nao eh um double, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[2]);
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[3]);
    return 1;
}

int Interpretador::dload_3(){
    printf("Executando dload_3\n");
    Local_var lvar = this->frame_corrente->localVarVector[0];
    if(lvar.tag != DUP){
        printf("Variavel local carregada nao eh um double, abortar\n");
        exit(0);
    }
    lvar = this->frame_corrente->localVarVector[1];
    if(lvar.tag != DUP){
        printf("Variavel local carregada nao eh um double, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[0]);
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[1]);
    return 1;
}

int Interpretador::aload_0(){
    printf("Executando aload_0\n");
    Local_var lvar = this->frame_corrente->localVarVector[0];
    if(lvar.tag != OBJECTTYPE){
        printf("Variavel local carregada nao eh uma referencia, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back(lvar);
    return 1;
}
int Interpretador::aload_1(){
    printf("Executando aload_1\n");
    Local_var lvar = this->frame_corrente->localVarVector[1];
    if(lvar.tag != OBJECTTYPE){
        printf("Variavel local carregada nao eh uma referencia, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back(lvar);
    return 1;
}
int Interpretador::aload_2(){
    printf("Executando aload_2\n");
    Local_var lvar = this->frame_corrente->localVarVector[2];
    if(lvar.tag != OBJECTTYPE){
        printf("Variavel local carregada nao eh uma referencia, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back(lvar);
    return 1;
}
int Interpretador::aload_3(){
    printf("Executando aload_3\n");
    Local_var lvar = this->frame_corrente->localVarVector[3];
    if(lvar.tag != OBJECTTYPE){
        printf("Variavel local carregada nao eh uma referencia, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back(lvar);
    return 1;
}


int Interpretador::iload_0(){
    printf("Executando iload_0\n");
    Local_var lvar = this->frame_corrente->localVarVector[0];
    if(lvar.tag != INT){
        printf("Variavel local carregada nao eh um inteiro, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back(lvar);
    return 1;
}
int Interpretador::iload_1(){
    printf("Executando iload_1\n");
    Local_var lvar = this->frame_corrente->localVarVector[1];
    if(lvar.tag != INT){
        printf("Variavel local carregada nao eh um inteiro, abortar\n");
        //exit(0);
    }
    this->frame_corrente->operandStack.push_back(lvar);
    return 1;
}
int Interpretador::iload_2(){
    printf("Executando iload_2\n");
    Local_var lvar = this->frame_corrente->localVarVector[2];
    if(lvar.tag != INT){
        printf("Variavel local carregada nao eh um inteiro, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back(lvar);
    return 1;
}
int Interpretador::iload_3(){
    printf("Executando iload_3\n");
    Local_var lvar = this->frame_corrente->localVarVector[3];
    if(lvar.tag != INT){
        printf("Variavel local carregada nao eh um inteiro, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back(lvar);
    return 1;
}

int Interpretador::iaload(){}
int Interpretador::laload(){}
int Interpretador::faload(){}
int Interpretador::daload(){}
int Interpretador::aaload(){}
int Interpretador::baload(){}
int Interpretador::caload(){}
int Interpretador::saload(){}

int Interpretador::istore(){
    printf("Executando istore\n");
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em istore: Tipo em operandStack diferente do esperado.\n");
    }
    uint8_t local_var_index = this->code_corrente->code[this->frame_corrente->pc+1];
    if(this->frame_corrente->localVarVector[local_var_index].tag != INT){
        printf("Erro em istore: Tipo em Local_var diferente do esperado.\n");
    }
    this->frame_corrente->localVarVector[local_var_index].value.int_value = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();
    return 2;
}
int Interpretador::lstore(){}
int Interpretador::fstore(){}
int Interpretador::dstore(){}
int Interpretador::astore(){}

int Interpretador::istore_0(){
    printf("Executando istore_0\n");
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em istore: Tipo em operandStack diferente do esperado.");
    }
    if(this->frame_corrente->localVarVector[0].tag != INT){
        printf("Erro em istore: Tipo em Local_var diferente do esperado.");
    }
    this->frame_corrente->localVarVector[0].value.int_value = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();
    return 1;
}
int Interpretador::istore_1(){
    printf("Executando istore_1\n");
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em istore: Tipo em operandStack diferente do esperado.");
    }
    if(this->frame_corrente->localVarVector[1].tag != INT){
        printf("Erro em istore: Tipo em Local_var diferente do esperado.");
    }
    this->frame_corrente->localVarVector[1].value.int_value = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();
    return 1;
}
int Interpretador::istore_2(){
    printf("Executando istore_2\n");
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em istore: Tipo em operandStack diferente do esperado.");
    }
    if(this->frame_corrente->localVarVector[2].tag != INT){
        printf("Erro em istore: Tipo em Local_var diferente do esperado.");
    }
    this->frame_corrente->localVarVector[2].value.int_value = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();
    return 1;
}
int Interpretador::istore_3(){
    printf("Executando istore_3\n");
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em istore: Tipo em operandStack diferente do esperado.");
    }
    if(this->frame_corrente->localVarVector[3].tag != INT){
        printf("Erro em istore: Tipo em Local_var diferente do esperado.");
    }
    this->frame_corrente->localVarVector[3].value.int_value = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();
    return 1;
}

int Interpretador::lstore_0(){}
int Interpretador::lstore_1(){}
int Interpretador::lstore_2(){}
int Interpretador::lstore_3(){}

int Interpretador::fstore_0(){}
int Interpretador::fstore_1(){}
int Interpretador::fstore_2(){}
int Interpretador::fstore_3(){}

int Interpretador::dstore_0(){}
int Interpretador::dstore_1(){}
int Interpretador::dstore_2(){}
int Interpretador::dstore_3(){}

int Interpretador::astore_0(){
    printf("Executando astore_0\n");
    Local_var op;
    size_t old_size = this->frame_corrente->localVarVector.size();
    op = this->frame_corrente->operandStack.back();
    if(op.tag != OBJECTTYPE){
        printf("Variavel local carregada n�o � uma referencia, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.pop_back();
    this->frame_corrente->localVarVector.resize(old_size+1);
    this->frame_corrente->localVarVector[0] = op;
    return 1;
}

int Interpretador::astore_1(){
    printf("Executando astore_1\n");
    Local_var op;
    size_t old_size = this->frame_corrente->localVarVector.size();

    op = this->frame_corrente->operandStack.back();
    if(op.tag != OBJECTTYPE){
        printf("Variavel local carregada nao e uma referencia, abortar\n");
        exit(0);
    }
    cout << "astore_1: " << op.tag << endl;
    this->frame_corrente->operandStack.pop_back();
    this->frame_corrente->localVarVector.resize(old_size+1);
    this->frame_corrente->localVarVector[1] = op;
    return 1;
}

int Interpretador::astore_2(){
    printf("Executando astore_2\n");
    Local_var op;
    size_t old_size = this->frame_corrente->localVarVector.size();
    op = this->frame_corrente->operandStack.back();
    if(op.tag != OBJECTTYPE){
        printf("Variavel local carregada n�o � uma referencia, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.pop_back();
    this->frame_corrente->localVarVector.resize(old_size+1);
    this->frame_corrente->localVarVector[2] = op;
    return 1;
}

int Interpretador::astore_3(){
    printf("Executando astore_3\n");
    Local_var op;
    size_t old_size = this->frame_corrente->localVarVector.size();
    op = this->frame_corrente->operandStack.back();
    if(op.tag != OBJECTTYPE){
        printf("Variavel local carregada n�o � uma referencia, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.pop_back();
    this->frame_corrente->localVarVector.resize(old_size+1);
    this->frame_corrente->localVarVector[3] = op;
    return 1;
}

int Interpretador::iastore(){}
int Interpretador::lastore(){}
int Interpretador::fastore(){}
int Interpretador::dastore(){}
int Interpretador::aastore(){}
int Interpretador::bastore(){}
int Interpretador::castore(){}
int Interpretador::sastore(){}



int Interpretador::pop(){
    printf("Executando pop\n");
    this->frame_corrente->operandStack.pop_back();
    return 1;
}

int Interpretador::pop2(){
    printf("Executando pop2\n");
    this->frame_corrente->operandStack.pop_back();
    this->frame_corrente->operandStack.pop_back();
    return 1;
}

int Interpretador::dup(){
    printf("Executando dup\n");
    this->frame_corrente->operandStack.push_back( this->frame_corrente->operandStack.back() );
    return 1;//opcode lido
}
int Interpretador::dup_x1(){
    printf("Executando dup_x1\n");
    vector<Local_var>::iterator it = this->frame_corrente->operandStack.end();
    this->frame_corrente->operandStack.insert(it-2, this->frame_corrente->operandStack.back());
    return 1;
}
int Interpretador::dup_x2(){
    printf("Executando dup_x2\n");
     vector<Local_var>::iterator it = this->frame_corrente->operandStack.end();
    this->frame_corrente->operandStack.insert(it-3, this->frame_corrente->operandStack.back());
    return 1;
}

int Interpretador::dup2(){
    printf("Executando dup2\n");
    vector<Local_var> *opStack = &this->frame_corrente->operandStack;
    //value2, value1 ->
    opStack->push_back( opStack->at(opStack->size()-2) );//value1, value2, value1 ->
    opStack->push_back( opStack->at(opStack->size()-2) );//value2, value1, value2, value1 ->
    return 1;//opcode lido
}
int Interpretador::dup2_x1(){
    printf("Executando dup2_x1\n");
    vector<Local_var>::iterator it = this->frame_corrente->operandStack.end();
    this->frame_corrente->operandStack.insert(it-3, this->frame_corrente->operandStack.back());
    this->frame_corrente->operandStack.insert(it-3, this->frame_corrente->operandStack.at(this->frame_corrente->operandStack.size()-2));
    return 1;
}
int Interpretador::dup2_x2(){
    printf("Executando dup2_x2\n");
    vector<Local_var>::iterator it = this->frame_corrente->operandStack.end();
    this->frame_corrente->operandStack.insert(it-4, this->frame_corrente->operandStack.back());
    this->frame_corrente->operandStack.insert(it-5, this->frame_corrente->operandStack.at(this->frame_corrente->operandStack.size()-2));
    return 1;
}

int Interpretador::swap_op(){
    printf("Executando swap_op\n");
    vector<Local_var>::iterator it;
    it = this->frame_corrente->operandStack.end();
    this->frame_corrente->operandStack.insert(it-2, this->frame_corrente->operandStack.back());
    this->frame_corrente->operandStack.pop_back();
    return 1;
}

int Interpretador::iadd(){
    printf("Executando iadd\n");
    uint32_t lhs, rhs;
    Local_var op;
    Local_var_Type op_v;
    rhs = frame_corrente->operandStack.back().value.int_value;//extrai o valor em operand
    this->frame_corrente->operandStack.pop_back();
    lhs = frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    //printf("lhs: %d rhs: %d\n", lhs, rhs);
    op_v.int_value = lhs + rhs;
    op.value = op_v;
    op.tag = INT;
    this->frame_corrente->operandStack.push_back(op);
    return 1;
}

int Interpretador::ladd(){
    printf("Executando ladd\n");
    //..., value1, value2 ->  //indica que value2 estao no topo da pilha e logo abaixo value1
    // value1 - value2        //ordem da operacao
    // ..., result            //indica que o resultado vai pro topo da pilha
    Local_var result[2];
    uint64_t lhs, rhs, resultado;
    uint32_t *alocador;
    result[0].tag = LONGO;
    result[1].tag = LONGO;
    //le value2 == rhs
    alocador = (uint32_t*) rhs;//alocador aponta para os 32 bits mais significativos de rhs
    rhs = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();
    *alocador = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();

    //le value 1 == lhs
    alocador = (uint32_t*) lhs;
    lhs = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();
    *alocador = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();

    resultado = lhs + rhs;
    alocador = (uint32_t*) result;

    result[0].value.long_value = *alocador;//mais significativo
    result[1].value.long_value = *(alocador+1);//menos significativo
    this->frame_corrente->operandStack.push_back(result[0]);
    this->frame_corrente->operandStack.push_back(result[1]);
    return 1;
}

int Interpretador::fadd(){}
int Interpretador::dadd(){}

int Interpretador::isub(){
    printf("Executando isub\n");
    uint32_t lhs, rhs;
    Local_var op;
    Local_var_Type op_v;
    rhs = frame_corrente->operandStack.back().value.int_value;//extrai o valor em operand
    this->frame_corrente->operandStack.pop_back();
    lhs = frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    //printf("lhs: %d rhs: %d\n", lhs, rhs);
    op_v.int_value = lhs - rhs;
    op.value = op_v;
    op.tag = INT;
    this->frame_corrente->operandStack.push_back(op);
    return 1;
}

int Interpretador::lsub(){
    printf("Executando lsub\n");
    //..., value1, value2 ->  //indica que value2 estao no topo da pilha e logo abaixo value1
    // value1 - value2        //ordem da operacao
    // ..., result            //indica que o resultado vai pro topo da pilha
    Local_var result[2];
    uint64_t lhs, rhs, resultado;
    uint32_t *alocador;
    result[0].tag = LONGO;
    result[1].tag = LONGO;
    //le value2 == rhs
    alocador = (uint32_t*) rhs;//alocador aponta para os 32 bits mais significativos de rhs
    rhs = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();
    *alocador = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();

    //le value 1 == lhs
    alocador = (uint32_t*) lhs;
    lhs = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();
    *alocador = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();

    resultado = lhs - rhs;
    alocador = (uint32_t*) result;

    result[0].value.long_value = *alocador;//mais significativo
    result[1].value.long_value = *(alocador+1);//menos significativo
    this->frame_corrente->operandStack.push_back(result[0]);
    this->frame_corrente->operandStack.push_back(result[1]);
    return 1;
}

int Interpretador::fsub(){}
int Interpretador::dsub(){}

int Interpretador::imul(){
    printf("Executando imul\n");
    uint32_t lhs, rhs;
    Local_var op;
    Local_var_Type op_v;

    rhs = frame_corrente->operandStack.back().value.int_value;//extrai o valor em operand
    this->frame_corrente->operandStack.pop_back();
    lhs = frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    //printf("lhs: %d rhs: %d\n", lhs, rhs);
    op_v.int_value = lhs * rhs;
    op.value = op_v;
    op.tag = INT;
    this->frame_corrente->operandStack.push_back(op);
    return 1;
}

int Interpretador::lmul(){
    //..., value1, value2 ->  //indica que value2 est� no topo da pilha e logo abaixo value1
    // value1 - value2        //ordem da opera��o
    // ..., result            //indica que o resultado vai pro topo da pilha
    printf("Executando lmul\n");
    Local_var result[2];
    uint64_t lhs, rhs, resultado;
    uint32_t *alocador;
    result[0].tag = LONGO;
    result[1].tag = LONGO;

    //le value2 == rhs
    alocador = (uint32_t*) rhs;//alocador aponta para os 32 bits mais significativos de rhs
    rhs = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();
    *alocador = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();

    //le value 1 == lhs
    alocador = (uint32_t*) lhs;
    lhs = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();
    *alocador = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();

    resultado = lhs * rhs;
    alocador = (uint32_t*) result;

    result[0].value.long_value = *alocador;//mais significativo
    result[1].value.long_value = *(alocador+1);//menos significativo
    this->frame_corrente->operandStack.push_back(result[0]);
    this->frame_corrente->operandStack.push_back(result[1]);
    return 1;
}

int Interpretador::fmul(){}
int Interpretador::dmul(){}

int Interpretador::idiv(){
    printf("Executando idiv\n");
    uint32_t lhs, rhs;
    Local_var op;
    Local_var_Type op_v;

    rhs = frame_corrente->operandStack.back().value.int_value;//extrai o valor em operand
    this->frame_corrente->operandStack.pop_back();
    lhs = frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    //printf("lhs: %d rhs: %d\n", lhs, rhs);
    op_v.int_value = lhs / rhs;
    op.value = op_v;
    op.tag = INT;
    this->frame_corrente->operandStack.push_back(op);
    return 1;
}

int Interpretador::ldiv(){
    //..., value1, value2 ->  //indica que value2 estao no topo da pilha e logo abaixo value1
    // value1 - value2        //ordem da operacao
    // ..., result            //indica que o resultado vai pro topo da pilha
    printf("Executando ldiv\n");
    Local_var result[2];
    uint64_t lhs, rhs, resultado;
    uint32_t *alocador;
    result[0].tag = LONGO;
    result[1].tag = LONGO;

    //le value2 == rhs
    alocador = (uint32_t*) rhs;//alocador aponta para os 32 bits mais significativos de rhs
    rhs = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();
    *alocador = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();

    //le value 1 == lhs
    alocador = (uint32_t*) lhs;
    lhs = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();
    *alocador = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();

    resultado = lhs / rhs;
    alocador = (uint32_t*) result;

    result[0].value.long_value = *alocador;//mais significativo
    result[1].value.long_value = *(alocador+1);//menos significativo
    this->frame_corrente->operandStack.push_back(result[0]);
    this->frame_corrente->operandStack.push_back(result[1]);
    return 1;
}

int Interpretador::fdiv(){}
int Interpretador::ddiv(){}

int Interpretador::irem(){
    printf("Executando irem\n");
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em istore: Tipo de operando 1 em operandStack diferente do esperado.");
    }
    uint32_t rhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em istore: Tipo de operando 2 em operandStack diferente do esperado.");
    }
    uint32_t lhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();
    Local_var operand;
    operand.tag = INT;
    operand.value.int_value = lhs - (lhs/rhs)*rhs;
    this->frame_corrente->operandStack.push_back(operand);
    return 1;
}

int Interpretador::lrem(){
    printf("Executando lrem\n");
    uint64_t rhs, lhs, result;
    uint32_t *alocador;
    alocador = (uint32_t*) &rhs;
    rhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();
    *alocador = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    alocador = (uint32_t*) &lhs;
    lhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();
    *alocador = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    result = lhs - (lhs/rhs)*rhs;
    alocador = (uint32_t*) &result;
    Local_var operand[2];
    operand[0].tag = INT;
    operand[0].value.int_value = *alocador;
    operand[1].tag = INT;
    operand[1].value.int_value = *(alocador+1);

    this->frame_corrente->operandStack.push_back(operand[0]);
    this->frame_corrente->operandStack.push_back(operand[1]);
    return 1;
}
int Interpretador::frem(){}
int Interpretador::drem(){}

int Interpretador::ineg(){//dar pop->push s� pra isso � sacanagem
    printf("Executando ineg\n");
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em istore: Tipo em operandStack diferente do esperado.");
    }
    this->frame_corrente->operandStack.back().value.int_value = -this->frame_corrente->operandStack.back().value.int_value;
    return 1;
}

int Interpretador::lneg(){
    printf("Executando lneg\n");
    int64_t val;
    uint32_t *alocador;
    alocador = (uint32_t*) &val;
    alocador[0] = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();
    alocador[1] = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();

    Local_var operand[2];
    operand[0].tag = LONGO;
    operand[1].tag = LONGO;
    val = -val;
    operand[0].value.long_value = alocador[0];//bits mais significativos
    operand[1].value.long_value = alocador[1];//bits menos significativos
    this->frame_corrente->operandStack.push_back(operand[0]);//mais significativos mais ao fundo
    this->frame_corrente->operandStack.push_back(operand[1]);//menos significativos no topo

    return 1;
}

int Interpretador::fneg(){}
int Interpretador::dneg(){}

int Interpretador::ishl(){
    printf("Executando ishl\n");
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em istore: Tipo em operandStack diferente do esperado.");
    }
    int32_t rhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em istore: Tipo em operandStack diferente do esperado.");
    }
    int32_t lhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    Local_var operand;
    operand.tag = INT;
    rhs &= 0x0000001f;//shifta usando s� os 5 ultimos bits desse numero
    operand.value.int_value = lhs << rhs;
    this->frame_corrente->operandStack.push_back(operand);
    return 1;
}
int Interpretador::lshl(){}

int Interpretador::ishr(){
    printf("Executando ishl\n");
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em istore: Tipo em operandStack diferente do esperado.");
    }
    int32_t rhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em istore: Tipo em operandStack diferente do esperado.");
    }
    int32_t lhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    Local_var operand;
    operand.tag = INT;
    rhs &= 0x0000001f;//shifta usando s� os 5 ultimos bits desse numero
    operand.value.int_value = lhs >> rhs;
    this->frame_corrente->operandStack.push_back(operand);
    return 1;
}
int Interpretador::lshr(){}

int Interpretador::iushl(){}
int Interpretador::lushl(){}

int Interpretador::iand(){
    printf("Executando iand\n");

    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em istore: Tipo de operando 1 em operandStack diferente do esperado.");
    }
    int32_t rhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em istore: Tipo de operando 2 em operandStack diferente do esperado.");
    }
    int32_t lhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    Local_var operand;
    operand.tag = INT;
    operand.value.int_value = lhs & rhs;
    this->frame_corrente->operandStack.push_back(operand);
    return 1;
}
int Interpretador::land(){}

int Interpretador::ior(){}
int Interpretador::lor(){}

int Interpretador::ixor(){}
int Interpretador::lxor(){}

int Interpretador::iinc(){}

int Interpretador::i2l(){}
int Interpretador::i2f(){}
int Interpretador::i2d(){
    printf("Executando i2d\n");

    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em i2d: Tipo de operando no topo do operandStack diferente do esperado.\n");
    }
    uint32_t var = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    Local_var operand1;
    operand1.tag = DUPLO;
    operand1.value.double_value = 0;
    this->frame_corrente->operandStack.push_back(operand1);

    Local_var operand2;
    operand2.tag = DUPLO;
    operand1.value.double_value = var;
    this->frame_corrente->operandStack.push_back(operand1);
    return 1;
}

int Interpretador::l2i(){}
int Interpretador::l2f(){}
int Interpretador::l2d(){}

int Interpretador::f2i(){}
int Interpretador::f2l(){}
int Interpretador::f2d(){}

int Interpretador::d2i(){}
int Interpretador::d2l(){}
int Interpretador::d2f(){}

int Interpretador::i2b(){}
int Interpretador::i2c(){}
int Interpretador::i2s(){}

int Interpretador::lcmp(){}
int Interpretador::fcmpl(){}
int Interpretador::fcmpg(){}

int Interpretador::dcmpl(){}
int Interpretador::dcmpg(){}

////////////////////////// Conditional Branch //////////////////////////
// Conditional branch: ifeq, ifne, iflt, ifle, ifgt, ifge, ifnull, ifnonnull,
// if_icmpeq, if_icmpne, if_icmplt, if_icmple, if_icmpgt, if_icmpge, if_acmpeq, if_acmpne.

/////////// Implementação das if<cond> ///////////
// Todas elas são iguais. Só muda a comparação.

// Não foi testada
int Interpretador::ifeq() {
    printf("Executando ifeq\n");
      int32_t value = 0;
      int16_t offset = 0;

      value = frame_corrente->operandStack.back().value.int_value;
      this->frame_corrente->operandStack.pop_back();

      if (value == 0) {
            offset = this->code_corrente->code[this->frame_corrente->pc+1];
            offset <<= 8;
            offset |= this->code_corrente->code[this->frame_corrente->pc+2];
            return offset;
      }

      else
            return 3;
}

// Não foi testada
int Interpretador::ifne() {
    printf("Executando ifne\n");
      int32_t value = 0;
      int16_t offset = 0;

      value = frame_corrente->operandStack.back().value.int_value;
      this->frame_corrente->operandStack.pop_back();

      if (value != 0) {
            offset = this->code_corrente->code[this->frame_corrente->pc+1];
            offset <<= 8;
            offset |= this->code_corrente->code[this->frame_corrente->pc+2];
            return offset;
      }

      else
            return 3;
}

// Não foi testada
int Interpretador::iflt() {
    printf("Executando iflt\n");
      int32_t value = 0;
      int16_t offset = 0;

      value = frame_corrente->operandStack.back().value.int_value;
      this->frame_corrente->operandStack.pop_back();

      if (value < 0) {
            offset = this->code_corrente->code[this->frame_corrente->pc+1];
            offset <<= 8;
            offset |= this->code_corrente->code[this->frame_corrente->pc+2];
            return offset;
      }

      else
            return 3;
}

// Não foi testada
int Interpretador::ifle() {
    printf("Executando ifle\n");
      int32_t value = 0;
      int16_t offset = 0;

      value = frame_corrente->operandStack.back().value.int_value;
      this->frame_corrente->operandStack.pop_back();

      if (value <= 0) {
            offset = this->code_corrente->code[this->frame_corrente->pc+1];
            offset <<= 8;
            offset |= this->code_corrente->code[this->frame_corrente->pc+2];
            return offset;
      }

      else
            return 3;
}

// Não foi testada
int Interpretador::ifgt() {
    printf("Executando ifgt\n");
      int32_t value = 0;
      int16_t offset = 0;

      value = frame_corrente->operandStack.back().value.int_value;
      this->frame_corrente->operandStack.pop_back();

      if (value > 0) {
            offset = this->code_corrente->code[this->frame_corrente->pc+1];
            offset <<= 8;
            offset |= this->code_corrente->code[this->frame_corrente->pc+2];
            return offset;
      }

      else
            return 3;
}

// Não foi testada
int Interpretador::ifge() {
    printf("Executando ifge\n");
      int32_t value = 0;
      int16_t offset = 0;

      value = frame_corrente->operandStack.back().value.int_value;
      this->frame_corrente->operandStack.pop_back();

      if (value >= 0) {
            offset = this->code_corrente->code[this->frame_corrente->pc+1];
            offset <<= 8;
            offset |= this->code_corrente->code[this->frame_corrente->pc+2];
            return offset;
      }

      else
            return 3;
}

/////////// Implementação das ifnull e ifnonnull ///////////
// Todas elas são iguais. Só muda a comparação.

// Não foi testada
int Interpretador::ifnull() {
    printf("Executando ifnull\n");
      int16_t offset = 0;
      InstanceClass *reference = NULL;

      reference = frame_corrente->operandStack.back().value.reference_value;
      this->frame_corrente->operandStack.pop_back();

      if (reference == NULL) {
            offset = this->code_corrente->code[this->frame_corrente->pc+1];
            offset <<= 8;
            offset |= this->code_corrente->code[this->frame_corrente->pc+2];
            return offset;
      }

      else
            return 3;
}

// Não foi testada
int Interpretador::ifnonnull() {
    printf("Executando ifnonnull\n");
      int16_t offset = 0;
      InstanceClass *reference = NULL;

      reference = frame_corrente->operandStack.back().value.reference_value;
      this->frame_corrente->operandStack.pop_back();

      if (reference != NULL) {
            offset = this->code_corrente->code[this->frame_corrente->pc+1];
            offset <<= 8;
            offset |= this->code_corrente->code[this->frame_corrente->pc+2];
            return offset;
      }

      else
            return 3;
}

/////////// Implementação das if_icmp<cond> ///////////
// Todas elas são iguais. Só muda a comparação.

// Não foi testada
int Interpretador::if_icmpeq() {
    printf("Executando if_icmpeq\n");
      int32_t value1 = 0, value2;
      int16_t offset = 0;

      value1 = frame_corrente->operandStack.back().value.int_value;
      this->frame_corrente->operandStack.pop_back();

      value2 = frame_corrente->operandStack.back().value.int_value;
      this->frame_corrente->operandStack.pop_back();

      if (value1 == value2) {
            offset = this->code_corrente->code[this->frame_corrente->pc+1];
            offset <<= 8;
            offset |= this->code_corrente->code[this->frame_corrente->pc+2];
            return offset;
      }

      else
            return 3;
}

// Não foi testada
int Interpretador::if_icmpne() {
    printf("Executando icmpne\n");
      int32_t value1 = 0, value2;
      int16_t offset = 0;

      value1 = frame_corrente->operandStack.back().value.int_value;
      this->frame_corrente->operandStack.pop_back();

      value2 = frame_corrente->operandStack.back().value.int_value;
      this->frame_corrente->operandStack.pop_back();

      if (value1 != value2) {
            offset = this->code_corrente->code[this->frame_corrente->pc+1];
            offset <<= 8;
            offset |= this->code_corrente->code[this->frame_corrente->pc+2];
            return offset;
      }

      else
            return 3;
}

// Não foi testada
int Interpretador::if_icmplt() {
    printf("Executando if_icmplt\n");
      int32_t value1 = 0, value2;
      int16_t offset = 0;

      value1 = frame_corrente->operandStack.back().value.int_value;
      this->frame_corrente->operandStack.pop_back();

      value2 = frame_corrente->operandStack.back().value.int_value;
      this->frame_corrente->operandStack.pop_back();

      if (value1 < value2) {
            offset = this->code_corrente->code[this->frame_corrente->pc+1];
            offset <<= 8;
            offset |= this->code_corrente->code[this->frame_corrente->pc+2];
            return offset;
      }

      else
            return 3;
}

// Não foi testada
int Interpretador::if_icmple() {
    printf("Executando if_icmple\n");
      int32_t value1 = 0, value2;
      int16_t offset = 0;

      value1 = frame_corrente->operandStack.back().value.int_value;
      this->frame_corrente->operandStack.pop_back();

      value2 = frame_corrente->operandStack.back().value.int_value;
      this->frame_corrente->operandStack.pop_back();

      if (value1 <= value2) {
            offset = this->code_corrente->code[this->frame_corrente->pc+1];
            offset <<= 8;
            offset |= this->code_corrente->code[this->frame_corrente->pc+2];
            return offset;
      }else
        return 3;
}

// Não foi testada
int Interpretador::if_icmpgt() {
    printf("Executando if_icmpgt\n");
      int32_t value1 = 0, value2;
      int16_t offset = 0;

      value1 = frame_corrente->operandStack.back().value.int_value;
      this->frame_corrente->operandStack.pop_back();

      value2 = frame_corrente->operandStack.back().value.int_value;
      this->frame_corrente->operandStack.pop_back();

      if (value1 > value2) {
            offset = this->code_corrente->code[this->frame_corrente->pc+1];
            offset <<= 8;
            offset |= this->code_corrente->code[this->frame_corrente->pc+2];
            return offset;
      }

      else
            return 3;
}

// Não foi testada
int Interpretador::if_icmpge() {
    printf("Executando if_icmpge\n");
      int32_t value1 = 0, value2;
      int16_t offset = 0;

      value1 = frame_corrente->operandStack.back().value.int_value;
      this->frame_corrente->operandStack.pop_back();

      value2 = frame_corrente->operandStack.back().value.int_value;
      this->frame_corrente->operandStack.pop_back();

      if (value1 <= value2) {
            offset = this->code_corrente->code[this->frame_corrente->pc+1];
            offset <<= 8;
            offset |= this->code_corrente->code[this->frame_corrente->pc+2];
            return offset;
      }

      else
            return 3;
}

/////////// Implementação das if_acmp<cond> ///////////
// Todas elas são iguais. Só muda a comparação.

// Não foi testada
int Interpretador::if_acmpeq() {
    printf("Executando if_acmpeq\n");
      int16_t offset = 0;
      InstanceClass *reference1 = NULL, *reference2 = NULL;

      reference1 = frame_corrente->operandStack.back().value.reference_value;
      this->frame_corrente->operandStack.pop_back();

      reference2 = frame_corrente->operandStack.back().value.reference_value;
      this->frame_corrente->operandStack.pop_back();

      if (reference1 == reference2) {
            offset = this->code_corrente->code[this->frame_corrente->pc+1];
            offset <<= 8;
            offset |= this->code_corrente->code[this->frame_corrente->pc+2];
            return offset;
      }

      else
            return 3;
}

// Não foi testada
int Interpretador::if_acmpne() {
    printf("Executando if_acmpne\n");
      int16_t offset = 0;
      InstanceClass *reference1 = NULL, *reference2 = NULL;

      reference1 = frame_corrente->operandStack.back().value.reference_value;
      this->frame_corrente->operandStack.pop_back();

      reference2 = frame_corrente->operandStack.back().value.reference_value;
      this->frame_corrente->operandStack.pop_back();

      if (reference1 != reference2) {
            offset = this->code_corrente->code[this->frame_corrente->pc+1];
            offset <<= 8;
            offset |= this->code_corrente->code[this->frame_corrente->pc+2];
            return offset;
      }

      else
            return 3;
}

////////////////////////// Unconditional Branch //////////////////////////
// Unconditional branch: goto, goto_w, jsr, jsr_w, ret.

// Não foi testada
int Interpretador::goto_java() {
    printf("Executando goto_java\n");
      int16_t offset = 0;

      offset = this->code_corrente->code[this->frame_corrente->pc+1];
      offset <<= 8;
      offset |= this->code_corrente->code[this->frame_corrente->pc+2];

      return offset;
}

// Não foi testada
int Interpretador::goto_w() {
    printf("Executando goto_w\n");
      int32_t offset = 0;

      offset |= this->code_corrente->code[this->frame_corrente->pc+1] << 24 & 0xFF000000;
      offset |= this->code_corrente->code[this->frame_corrente->pc+2] << 16 & 0x00FF0000;
      offset |= this->code_corrente->code[this->frame_corrente->pc+3] << 8 & 0x0000FF00;
      offset |= this->code_corrente->code[this->frame_corrente->pc+4] & 0x000000FF;

      return offset;
}

// Não foi testada
int Interpretador::jsr() {
    printf("Executando jsr\n");
      int16_t offset = 0;
      Local_var operand;

      operand.tag = RETURN_ADDRESS;
      operand.value.returnAddress_value = this->frame_corrente->pc + 3;
      this->frame_corrente->operandStack.push_back(operand);

      offset = this->code_corrente->code[this->frame_corrente->pc+1];
      offset <<= 8;
      offset |= this->code_corrente->code[this->frame_corrente->pc+2];

      return offset;
}

// Não foi testada
int Interpretador::jsr_w() {
    printf("Executando jsr_w\n");
      int32_t offset = 0;
      Local_var operand;

      operand.tag = RETURN_ADDRESS;
      operand.value.returnAddress_value = this->frame_corrente->pc + 5;
      this->frame_corrente->operandStack.push_back(operand);

      offset |= this->code_corrente->code[this->frame_corrente->pc+1] << 24 & 0xFF000000;
      offset |= this->code_corrente->code[this->frame_corrente->pc+2] << 16 & 0x00FF0000;
      offset |= this->code_corrente->code[this->frame_corrente->pc+3] << 8 & 0x0000FF00;
      offset |= this->code_corrente->code[this->frame_corrente->pc+4] & 0x000000FF;

      return offset;
}

////////////////////////// Compound Conditional Branch //////////////////////////
// Compound conditional branch: tableswitch, lookupswitch.

int Interpretador::putfield(){
    printf("Executando putfield\n");
    uint32_t lhs;
    Local_var op;
    uint16_t name_index = code_corrente->code[frame_corrente->pc+1];
    string field_name, field_type;
    Local_var lvar, ref_var;
    FieldValue fvar;

    name_index = name_index << 8;
    name_index |= code_corrente->code[frame_corrente->pc+2];
    field_name = frame_corrente->cf->getFieldName(name_index);
    field_type = frame_corrente->cf->getFieldType(name_index);
    printf("putfield #%d\t//%s(%s)\n", name_index, field_name.c_str(), field_type.c_str());

    lvar = this->frame_corrente->operandStack.back();
    this->frame_corrente->operandStack.pop_back(); // pop the value

    if(field_type.compare("I") == 0){

        ref_var = this->frame_corrente->operandStack.back();
        this->frame_corrente->operandStack.pop_back(); // pop this

        //converte local var para fvar
        fvar.tag = BASETYPE;
        fvar.val.btype.tag = INT;
        fvar.val.btype.val.inteiro = lvar.value.int_value;
        ref_var.value.reference_value->field_instances[field_name] = fvar;
        printf("o int passado para o field eh: %d\n", lvar.value.int_value);
    }
    else if(field_type.compare("Z") == 0){

        ref_var = this->frame_corrente->operandStack.back();
        this->frame_corrente->operandStack.pop_back(); // pop this
        //converte local var para fvar
        fvar.tag = BASETYPE;
        fvar.val.btype.tag = BOOL;
        fvar.val.btype.val.boleano = lvar.value.boolean_value;

        ref_var.value.reference_value->field_instances[field_name] = fvar;
        printf("o bool passado para o field eh: %d\n", lvar.value.boolean_value);
    }
    else if(field_type.compare("C") == 0){
        Local_var lvar_upper;
        lvar_upper = this->frame_corrente->operandStack.back();
        this->frame_corrente->operandStack.pop_back(); // lower
        ref_var = this->frame_corrente->operandStack.back();
        this->frame_corrente->operandStack.pop_back(); // pop this
        //converte local var para fvar
        fvar.tag = BASETYPE;
        fvar.val.btype.tag = LONGO;
        fvar.val.btype.val.longo = (lvar_upper.value.long_value << 16) & lvar.value.long_value;


        ref_var.value.reference_value->field_instances[field_name] = fvar;
        printf("the int passed to the field is: %d\n", (lvar_upper.value.long_value << 16) & lvar.value.long_value);
    }
    else if(field_type.compare("D") == 0){
        Local_var lvar_upper;
        lvar_upper = this->frame_corrente->operandStack.back();
        this->frame_corrente->operandStack.pop_back(); // lower
        ref_var = this->frame_corrente->operandStack.back();
        this->frame_corrente->operandStack.pop_back(); // pop this
        //converte local var para fvar
        fvar.tag = BASETYPE;
        fvar.val.btype.tag = DUPLO;
        fvar.val.btype.val.duplo = lvar_upper.value.long_value << 16 && lvar.value.long_value;


        ref_var.value.reference_value->field_instances[field_name] = fvar;
        printf("the int passed to the field is: %d\n", lvar_upper.value.long_value << 16 && lvar.value.long_value);
    }
    return 3;
}

int Interpretador::getfield(){
    printf("Executando getfield\n");
    uint32_t lhs;
    Local_var op;
    uint16_t name_index = code_corrente->code[frame_corrente->pc+1];
    //printf("entrou na funcao getfield\n");
    string field_name, field_type;
    Local_var lvar, this_var;

    name_index = name_index << 8;
    name_index |= code_corrente->code[frame_corrente->pc+2];
    field_name = frame_corrente->cf->getFieldName(name_index);
    field_type = frame_corrente->cf->getFieldType(name_index);
    //printf("getfield #%d\t//%s(%s)\n", name_index, field_name.c_str(), field_type.c_str());

    if(field_type.compare("I") == 0){
        Local_var lvar;
        lvar = this->frame_corrente->operandStack.back();
        this->frame_corrente->operandStack.pop_back(); // pop the value
        if(lvar.tag != 9){
            //printf("Tentativa de acessar um field de algo q nao eh objeto, abortar!");
            exit(0);
        }
        FieldValue fvar = lvar.value.reference_value->field_instances[field_name];
        //printf("O valor da field eh: %d\n", fvar.val.btype.val.inteiro);

        fvar = lvar.value.reference_value->field_instances[field_name];
        lvar.tag = INT;
        lvar.value.int_value = fvar.val.btype.val.inteiro;
        this->frame_corrente->operandStack.push_back(lvar);
    }
    return 3;
}


int Interpretador::anewarray(){
    printf("Executando anewarray\n");
    //constroi o index
    uint16_t index = this->code_corrente->code[this->frame_corrente->pc+1];
    index <<= 8;
    index |= this->code_corrente->code[this->frame_corrente->pc+2];

    //prepara o contador do tamanho do array
    int count_operand = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    //prepara o operand que vai pra pilha
    Local_var operand;
    operand.tag = ARRAYTYPE;

    //operand � de um arrayref
    ArrayType *vetor = (ArrayType*) malloc(sizeof(ArrayType));
    vetor->arr = new arrayref;
    operand.value.arrayref = vetor;

    string className;//recebe o nome da classe
    cp_tag tag = this->frame_corrente->cf->constant_pool[index -1].tag;
    uint16_t name_index;
    switch(tag){
        case CONSTANT_Class:
            name_index = this->frame_corrente->cf->constant_pool[index -1].cp_union.constant_class.name_index;
            className = this->frame_corrente->cf->constant_pool[name_index].cp_union.constant_Utf8.bytes;
            //cada item no vetor � a inst�ncia de um objeto
            for(int i = 0; i < count_operand; i++){
                    FieldValue field;
                    field.tag = OBJECTTYPE;
                    field.val.objtype.instance = jvm->alocarObjeto(className);
                    vetor->arr->push_back(field);
            }
            break;
        case CONSTANT_InterfaceMethodref:
            for(int i = 0; i < count_operand; i++){

            }
            break;
    }
    this->frame_corrente->operandStack.push_back(operand);
    return 3;
}

// Não foi testada. Não está implementada, porém acho que deve ser uma das últimas.
// Ela pode chamar diversos códigos para tratar erros. Tudo tem que estar implementado
// para ela funcionar.
int Interpretador::athrow() {
    printf("Executando athrow\n");
      return 1;
}

// Não foi testada
int Interpretador::monitorenter() {
    printf("Executando monitorenter\n");
      return 1;
}

// Não foi testada
int Interpretador::monitorexit() {
    printf("Executando monitorexit\n");
      return 1;
}

int Interpretador::new_op(){
    printf("Executando new_op\n");
    uint8_t operand = code_corrente->code[frame_corrente->pc+1];//pc aponta para a instru��o; pc+1 � o byte seguinte
    uint16_t name_index = operand;
    std::string className;
    Local_var op;
    Local_var_Type op_val;

    name_index = name_index << 8;
    operand = code_corrente->code[frame_corrente->pc+2];
    name_index = name_index|operand;
    className = this->frame_corrente->cf->getCpoolClass(name_index);

    printf("new #%d \t// %s\n", name_index, className.c_str());
    //printf("nome da classe: %s\n", className.c_str());
    op.tag = OBJECTTYPE;
    op_val.reference_value = jvm->alocarObjeto(className);
    op.value = op_val;
    frame_corrente->operandStack.push_back(op);
    //printf("Sai da new\n");
    return 3; //dois bytes lidos + o opcode
}

int Interpretador::invokespecial(){
    printf("Executando invokespecial\n");
    uint8_t operand = code_corrente->code[frame_corrente->pc+1];
    uint16_t method_index = operand;
    string invoking_class, method_name, descriptor, argtypes;
    ClassFile* cf;
    vector<Local_var> args;
    InstanceClass *inst;
    Local_var lvar;

    method_index = method_index << 8;
    operand = code_corrente->code[frame_corrente->pc+2];
    method_index = method_index|operand; //este � o indice na constant pool
    this->frame_corrente->cf->getCpoolMethod(method_index, invoking_class, method_name, descriptor);
    printf("invokespecial #%d\t//%s.%s:%s\n", method_index, invoking_class.c_str(), method_name.c_str(), descriptor.c_str());
    cf = this->jvm->getClassRef(invoking_class);

    // pega os argumentos da pilha
    for (int i=1; i < descriptor.find(")"); i++){
        args.push_back(this->frame_corrente->operandStack.back());
        this->frame_corrente->operandStack.pop_back();
    }
    // pega a referencia ao objeto da pilha
    args.push_back(this->frame_corrente->operandStack.back());

    //o vetor ficou invertido, o this tem que ser o primeiro argumento
    reverse(args.begin(), args.end());
    this->frame_corrente->operandStack.pop_back();

    method_index = cf->findMethod(method_name, descriptor);//este e o indice no vetor de metodos

    //executa este m�todo
    lvar = this->jvm->execMethod(method_index, cf, args);

    // bota o retorno na operand stack se nao tiver retornado void
    if(lvar.tag != VOID_T)
        this->frame_corrente->operandStack.push_back(lvar);

    //e fim
    return 3;
}


int Interpretador::invokevirtual(){
    printf("Executando invokevirtual\n");
    uint8_t operand = code_corrente->code[frame_corrente->pc+1];
    uint16_t method_index = operand;
    string invoking_class, method_name, descriptor, argtypes, super_name;
    ClassFile* cf;
    vector<Local_var> args;
    InstanceClass *inst;
    Local_var lvar;
    int found = -1;

    method_index = method_index << 8;
    operand = code_corrente->code[frame_corrente->pc+2];
    method_index = method_index|operand; //este � o indice na constant pool
    this->frame_corrente->cf->getCpoolMethod(method_index, invoking_class, method_name, descriptor);
    //printf("invokevirtual #%d\t//%s.%s:%s\n", method_index, invoking_class.c_str(), method_name.c_str(), descriptor.c_str());

    if(!strcmp(method_name.c_str(), "println") && !strcmp(invoking_class.c_str(), "java/io/PrintStream")){
        printf("%s\n", this->frame_corrente->operandStack.back().value.string_value->c_str());
        return 3;
    }


    cf = this->jvm->getClassRef(invoking_class);
    //precisamos encontrar em qual classF este m�todo foi declarado
    super_name = cf->getClassName(); // come�a loop na classe invocadora
    do{
        cf = this->jvm->getClassRef(super_name);

        found = cf->findMethod(method_name, descriptor);
        super_name = cf->getSuper();
        //cout << "super name: "<< super_name << endl;
        if(super_name.empty()){// se n�o possuir super, ent�o o m�todo n�o existe
            printf("Metodo passado nao existe\n");
            exit(0);
        }
    }while(found == -1);

    method_index = found;
    //printf("encontrei o metodo, esta na classe %s, numero %d\n", cf->getClassName().c_str(), method_index);

    // pega os argumentos da pilha
    for (int i=1; i < descriptor.find(")"); i++){
        args.push_back(this->frame_corrente->operandStack.back());
        this->frame_corrente->operandStack.pop_back();
    }
    // pega a referencia ao objeto da pilha
    args.push_back(this->frame_corrente->operandStack.back());
    this->frame_corrente->operandStack.pop_back();

    //o vetor ficou invertido, o this tem que ser o primeiro argumento
    reverse(args.begin(), args.end());

    //executa este metodo
    lvar = this->jvm->execMethod(method_index, cf, args);

    // bota o retorno na operand stack se nao tiver retornado void
    if(lvar.tag != VOID_T)
        this->frame_corrente->operandStack.push_back(lvar);

    //e fim*/
    return 3;
}


int Interpretador::return_op(){
    printf("Executando return_op\n");
    return 1;
}

int Interpretador::ireturn(){
    printf("Executando ireturn\n");
    if (this->frame_corrente->operandStack.size() != 1){
        printf("Funcao com defeito de retorno, abortar\n");
        exit(0);
    }
    Local_var lvar = this->frame_corrente->operandStack.back();

    if(lvar.tag != 1){
        printf("Funcao nao retornou um inteiro, abortar\n");
        exit(0);
    }

    return 1;
}
