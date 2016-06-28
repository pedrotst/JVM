#include "../include/interpretador.hpp"


void Interpretador::execute_instruction(int opcode){
    printf("Vou executar a instrucao\n");
    (*this.*instructions[opcode])();
}

int Interpretador::push_operands(uint8_t opcode){
    return (*this.*operands_pusher[opcode])();
}
//
//
//void Interpretador::setFrame(Frame *frame){
//    this->referencias[0] = (void*) frame->operandStack;
//    this->referencias[1] = (void*) frame->constant_pool_pt;
//    this->referencias[2] = (void*) frame->localVarVector;
//}

int Interpretador::runCode(uint16_t descriptor_index, Code_attribute *code_attr_pt, Frame *frame_pt) {
    //Agora o interpretador sabe sobre o code e sobre o frame. FIM 8D
    this->frame_corrente = frame_pt;
    this->code_corrente = code_attr_pt;
    this->descriptor_index = descriptor_index;

    uint8_t opcode;
    for(this->frame_corrente->pc = 0; this->frame_corrente->pc < 1/*code_attr_pt->code_length*/;) {
    opcode = this->code_corrente->code[this->frame_corrente->pc];
//        //Coloca os argumentos na pilha
//        //pc sempre aponta pra proxima instrução
//        interpreter.setConstantPool(frame_pt->constant_pool_pt);
//        interpreter.setOperandStack(frame_pt->operandStack);
//        frame_pt->pc += interpreter.push_operands(opcode, code+frame_pt->pc+1, &frame_pt->operandStack);
    this->frame_corrente->pc += this->push_operands(opcode);
    this->execute_instruction(opcode);
    //n += arg_qnt;
    }
    return -1;
}


Interpretador::Interpretador(/*Jvm *jvm*/){
    //this->jvm = jvm;
    std::vector<instructionFunction> pt(numOpcodes);
    std::vector<instructionFunctionOperands> pt2(numOpcodes);
    pt[IADD] = &Interpretador::iadd;
    pt2[IADD] = &Interpretador::iadd_pusher;
//    pt[NOP] = &nop;
//    pt[ACONST_NULL] = &aConst_null;
//    pt[ICONST_M1] = &iConst_m1;
//    pt[ICONST_0] = &iConst_0;
//    pt[ICONST_1] = &iConst_1;
//    pt[ICONST_2] = &iConst_2;
//    pt[ICONST_3] = &iConst_3;
//    pt[ICONST_4] = &iConst_4;
//    pt[ICONST_5] = &iConst_5;
//    pt[LCONST_0] = &lConst_0;
//    pt[LCONST_1] = &lConst_1;
//    pt[FCONST_0] = &fConst_0;
//    pt[FCONST_1] = &fConst_1;
//    pt[FCONST_2] = &fConst_2;
//    pt[DCONST_0] = &dConst_0;
//    pt[DCONST_1] = &dConst_1;
//    pt[BIPUSH] = &biPush;
//    pt[SIPUSH] = &siPush;
//    pt[LDC] = &ldc;
//    pt[LDC_W] = &ldc_w;
//    pt[LDC2_W] = &ldc2_w;
//    pt[ILOAD] = &iLoad;
//    pt[LLOAD] = &lLoad;
//    pt[FLOAD] = &fLoad;
//    pt[DLOAD] = &dLoad;
//    pt[ALOAD] = &aLoad;
//    pt[ILOAD_0] = &iLoad_0;
//    pt[ILOAD_1] = &iLoad_1;
//    pt[ILOAD_2] = &iLoad_2;
//    pt[ILOAD_3] = &iLoad_3;
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
//    pt[DUP] = &dup;
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
//    pt[INvOKESPECIAL] = &invokespecial;
//    pt[INvOKESTATIC] = &invokestatic;
//    pt[INvOKEINTERFACE] = &invokeinterface;
//    pt[INvOKEDYNAMIC] = &invokedynamic;
    pt[NEW] = &Interpretador::new_op;
    pt2[NEW] = &Interpretador::new_op_pusher;
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
    this->operands_pusher = pt2;
}

//int Interpretador::iadd_pusher(char* code, op_stack *opStack){
int Interpretador::iadd_pusher(){
    return 0;
}

//void Interpretador::iadd(op_stack *opStack){
void Interpretador::iadd(){

    uint32_t lhs, rhs;
    operand op;
    operand_value op_v;
    printf("Entrou na funcao\n");
//    lhs = opStack->back().value.int_value;
//    opStack->pop_back();
//    rhs = opStack->back().value.int_value;
//    opStack->pop_back();
    lhs = frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();
    rhs = frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    printf("lhs: %d rhs: %d\n", lhs, rhs);
    op_v.int_value = lhs + rhs;
    op.value = op_v;
    op.tag = INT;
    //opStack->push_back(op);
    this->frame_corrente->operandStack.push_back(op);
}

/*
void Interpretador::ladd(op_stack *opStack){
    uint8_t operand1[2], operand2[2];
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

//int Interpretador::new_op_pusher(char* codeAligned, op_stack *opStack){
int Interpretador::new_op_pusher(){
//new não utiliza a stack como entrada
    return 0;
}

//void Interpretador::new_op(op_stack *opStack){
void Interpretador::new_op(){
    printf("Cheguei na new\n");
    uint8_t operand = code_corrente->code[frame_corrente->pc+1];//pc aponta para a instrução; pc+1 é o byte seguinte
    uint16_t buffer = operand;
    buffer = buffer<<8;
    operand = code_corrente->code[frame_corrente->pc+2];
    buffer = buffer|operand;
    printf("new #%d\n", buffer);
    this->frame_corrente->pc += 2; //dois bytes lidos,
}
//
//void fadd(jStackFrame &jStack){
//}
//
//void dadd(jStackFrame &jStack){
//}
