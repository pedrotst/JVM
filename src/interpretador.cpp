#define DEBUG

//Se nao quiser ver entrada e saida de cada instrucao, comenta DEBUG_E_S
//Assim, o DEBUG ainda funciona de forma independente
#ifdef DEBUG
    #define DEBUG_E_S
#endif // DEBUG

#ifdef DEBUG_E_S
    #define DEBUG_ENTRADA do{DEBUG_PRINT(" ANTES:");DEBUG_ONLY(this->frame_corrente->printOperandStack());DEBUG_PRINT("");DEBUG_ONLY(this->frame_corrente->printLocalVar());DEBUG_PRINT("-\n");}while(0);
    #define DEBUG_SAIDA do{DEBUG_PRINT(" DEPOIS:");DEBUG_ONLY(this->frame_corrente->printOperandStack());DEBUG_ONLY(this->frame_corrente->printLocalVar());DEBUG_PRINT("-\n");}while(0);
#else
    #define DEBUG_ENTRADA
    #define DEBUG_SAIDA
#endif // DEBUG



#include <inttypes.h>
#include "../include/interpretador.hpp"

/**
*   PARA UTILIZAR AS FUCOES DE DEBUG:
*
*   DEBUG_PRINT("mesagem" << variavel << "mais msgs");
*   caso esteja em modo debug
*   eh compilado para cout << "mensagem" << variavel << "mais msgs" << endl;
*
*   DEBUG_ONLY(funcao_qualquer());
*   caso esteja em modo debug eh compilado para funcao_qualquer();
*
*   Para chamar o print da pilha de operandos utilize o seguinte:
*   DEBUG_ONLY(frame_corrente->printOperandStack());
*
*   Para facilitar investigar como OperandStack e LocalVar estavam
*   ao entrar na instrução e como ficaram imetiatamente antes da saída,
*   use DEBUG_ENTRADA e  imediatamente ao entrar e antes de sair da
*   instrução, respectivamente.
*/

int Interpretador::execute_instruction(int opcode){
    if(instructions[opcode] != NULL){
        return (*this.*instructions[opcode])();
    }
    else{
        printf("Instrucao nao especificada!\n");
        return 1;
    }
}

int Interpretador::runCode(Frame *frame_pt) {
    int n = frame_pt->method_index;

    this->frame_corrente = frame_pt;
    this->code_corrente = frame_pt->cf->getCodeAttr(n);
    this->descriptor_index = frame_pt->cf->methods[n].descriptor_index;

    uint8_t opcode;

    this->frame_corrente->localVarVector.resize(this->code_corrente->max_locals);
    for(this->frame_corrente->pc = 0; this->frame_corrente->pc < this->code_corrente->code_length;) {
        opcode = this->code_corrente->code[this->frame_corrente->pc];
        DEBUG_PRINT("pc->code[" << hex << this->frame_corrente->pc << "]: " << OperationMap::getOperation((uint8_t)opcode));

        this->frame_corrente->pc += this->execute_instruction(opcode);
        DEBUG_SAIDA;

    }
    return 0;
}

uint16_t Interpretador::read_code_word(uint8_t *code, uint64_t pc) {
      uint16_t word = 0;

      word = code[pc];
      word <<= 8;
      word |= code[pc+1];

      return word;
}

Interpretador::Interpretador(Jvm *jvm){

    this->jvm = jvm;
    this->_wide = false;
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
    pt[FCONST_0] = &Interpretador::fconst_0;//ni
    pt[FCONST_1] = &Interpretador::fconst_1;//ni
    pt[FCONST_2] = &Interpretador::fconst_2;//ni
    pt[DCONST_0] = &Interpretador::dconst_0;//ni
    pt[DCONST_1] = &Interpretador::dconst_1;//ni
    pt[BIPUSH] = &Interpretador::bipush;
    pt[SIPUSH] = &Interpretador::sipush;
    pt[LDC] = &Interpretador::ldc;
    pt[LDC_W] = &Interpretador::ldc_w;
    pt[LDC2_W] = &Interpretador::ldc2_w;
    pt[ILOAD] = &Interpretador::iload;
    pt[ILOAD_0] = &Interpretador::iload_0;
    pt[ILOAD_1] = &Interpretador::iload_1;
    pt[ILOAD_2] = &Interpretador::iload_2;
    pt[ILOAD_3] = &Interpretador::iload_3; // vou deixar os mesmos que os iload pq � a mesma coisa, a diferen�a � s� a tipagem
    pt[LLOAD] = &Interpretador::lload;
    pt[LLOAD_1] = &Interpretador::lload_1;
    pt[LLOAD_2] = &Interpretador::lload_2;
    pt[LLOAD_3] = &Interpretador::lload_3;
    pt[FLOAD] = &Interpretador::fload;
    pt[DLOAD] = &Interpretador::dload;//ni
    pt[ALOAD] = &Interpretador::aload;
    pt[ALOAD_0] = &Interpretador::aload_0;
    pt[ALOAD_1] = &Interpretador::aload_1;
    pt[ALOAD_2] = &Interpretador::aload_2;
    pt[ALOAD_3] = &Interpretador::aload_3;
    pt[FLOAD_0] = &Interpretador::fload_0;//ni
    pt[FLOAD_1] = &Interpretador::fload_1;//ni
    pt[FLOAD_2] = &Interpretador::fload_2;//ni
    pt[FLOAD_3] = &Interpretador::fload_3;//ni
    pt[DLOAD_0] = &Interpretador::dload_0;//ni
    pt[DLOAD_1] = &Interpretador::dload_1;//ni
    pt[DLOAD_2] = &Interpretador::dload_2;//ni
    pt[DLOAD_3] = &Interpretador::dload_3;//ni
    pt[IALOAD] = &Interpretador::iaload;
    pt[LALOAD] = &Interpretador::laload;//ni
    pt[FALOAD] = &Interpretador::faload;//ni
    pt[DALOAD] = &Interpretador::daload;//ni
    pt[AALOAD] = &Interpretador::aaload;//ni
    pt[BALOAD] = &Interpretador::baload;//ni
    pt[CALOAD] = &Interpretador::caload;//ni
    pt[SALOAD] = &Interpretador::saload;//ni
    pt[ISTORE] = &Interpretador::istore;
    pt[LSTORE] = &Interpretador::lstore;
    pt[FSTORE] = &Interpretador::fstore;//ni
    pt[DSTORE] = &Interpretador::dstore;//ni
    pt[ASTORE] = &Interpretador::astore;//ni
    pt[ISTORE_0] = &Interpretador::istore_0;
    pt[ISTORE_1] = &Interpretador::istore_1;
    pt[ISTORE_2] = &Interpretador::istore_2;
    pt[ISTORE_3] = &Interpretador::istore_3;
    pt[LSTORE_0] = &Interpretador::lstore_0;
    pt[LSTORE_1] = &Interpretador::lstore_1;
    pt[LSTORE_2] = &Interpretador::lstore_2;
    pt[LSTORE_3] = &Interpretador::lstore_3;
    pt[FSTORE_0] = &Interpretador::fstore_0;//ni
    pt[FSTORE_1] = &Interpretador::fstore_1;//ni
    pt[FSTORE_2] = &Interpretador::fstore_2;//ni
    pt[FSTORE_3] = &Interpretador::fstore_3;//ni
    pt[DSTORE_0] = &Interpretador::dstore_0;//ni
    pt[DSTORE_1] = &Interpretador::dstore_1;//ni
    pt[DSTORE_2] = &Interpretador::dstore_2;//ni
    pt[DSTORE_3] = &Interpretador::dstore_3;//ni
    pt[ASTORE_0] = &Interpretador::astore_0;
    pt[ASTORE_1] = &Interpretador::astore_1;
    pt[ASTORE_2] = &Interpretador::astore_2;
    pt[ASTORE_3] = &Interpretador::astore_3;
    pt[IASTORE] = &Interpretador::iastore;
    pt[LASTORE] = &Interpretador::lastore;//ni
    pt[DASTORE] = &Interpretador::dastore;//ni
    pt[AASTORE] = &Interpretador::aastore;//ni
    pt[BASTORE] = &Interpretador::bastore;//ni
    pt[CASTORE] = &Interpretador::castore;//ni
    pt[SASTORE] = &Interpretador::sastore;//ni
    pt[POP] = &Interpretador::pop;
    pt[POP2] = &Interpretador::pop2;
    pt[DUP] = &Interpretador::dup;
    pt[DUP_X1] = &Interpretador::dup_x1;
    pt[DUP_X2] = &Interpretador::dup_x2;
    pt[DUP2] = &Interpretador::dup2;
    pt[DUP2_X1] = &Interpretador::dup2_x1;
    pt[DUP2_X2] = &Interpretador::dup2_x2;
    pt[SWAP] = &Interpretador::swap_op;
    pt[LADD] = &Interpretador::ladd;
    pt[FADD] = &Interpretador::fadd;//ni
    pt[DADD] = &Interpretador::dadd;//ni
    pt[ISUB] = &Interpretador::isub;
    pt[LSUB] = &Interpretador::lsub;
    pt[FSUB] = &Interpretador::fsub;//ni
    pt[DSUB] = &Interpretador::dsub;//ni
    pt[IMUL] = &Interpretador::imul;
    pt[LMUL] = &Interpretador::lmul;
    pt[FMUL] = &Interpretador::fmul;//ni
    pt[DMUL] = &Interpretador::dmul;//ni
    pt[IDIV] = &Interpretador::idiv;
    pt[LDIV] = &Interpretador::ldiv;//ni
    pt[FDIV] = &Interpretador::fdiv;//ni
    pt[DDIV] = &Interpretador::ddiv;//ni
    pt[IREM] = &Interpretador::irem;
    pt[LREM] = &Interpretador::lrem;//ni
    pt[FREM] = &Interpretador::frem;//ni
    pt[DREM] = &Interpretador::drem;//ni
    pt[INEG] = &Interpretador::ineg;
    pt[LNEG] = &Interpretador::lneg;//ni
    pt[FNEG] = &Interpretador::fneg;//ni
    pt[DNEG] = &Interpretador::dneg;//ni
    pt[ISHL] = &Interpretador::ishl;
    pt[LSHL] = &Interpretador::lshl;//ni
    pt[ISHR] = &Interpretador::ishr;
    pt[LSHR] = &Interpretador::lshr;//ni
    pt[IUSHR] = &Interpretador::iushr;//ni
    pt[LUSHR] = &Interpretador::lushr;//ni
    pt[IAND] = &Interpretador::iand;
    pt[LAND] = &Interpretador::land;//ni
    pt[IOR] = &Interpretador::ior;
    pt[LOR] = &Interpretador::lor;//ni
    pt[IXOR] = &Interpretador::ixor;
    pt[LXOR] = &Interpretador::lxor;//ni
    pt[IINC] = &Interpretador::iinc;
    pt[I2L] = &Interpretador::i2l;
    pt[I2F] = &Interpretador::i2f;
    pt[I2D] = &Interpretador::i2d;
    pt[L2I] = &Interpretador::l2i;//ni
    pt[L2F] = &Interpretador::l2f;//ni
    pt[L2D] = &Interpretador::l2d;//ni
    pt[D2I] = &Interpretador::d2i;//ni
    pt[D2L] = &Interpretador::d2l;//ni
    pt[D2F] = &Interpretador::d2f;//ni
    pt[I2B] = &Interpretador::i2b;
    pt[I2C] = &Interpretador::i2c;
    pt[I2S] = &Interpretador::i2s;
    pt[LCMP] = &Interpretador::lcmp;//ni
    pt[FCMPL] = &Interpretador::fcmpl;//ni
    pt[FCMPG] = &Interpretador::fcmpg;//ni
    pt[DCMPL] = &Interpretador::dcmpl;//ni
    pt[DCMPG] = &Interpretador::dcmpg;//ni
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
    pt[JSR] = &Interpretador::jsr;//nao foi testada
    pt[RET] = &Interpretador::ret;//ni
    pt[TABLESWITCH] = &Interpretador::tableswitch;
    pt[LOOKUPSWITCH] = &Interpretador::lookupswitch;
    pt[IRETURN] = &Interpretador::ireturn;
    pt[LRETURN] = &Interpretador::lreturn;//ni
    pt[FRETURN] = &Interpretador::freturn;//ni
    pt[DRETURN] = &Interpretador::dreturn;//ni
    pt[ARETURN] = &Interpretador::areturn;//ni
    pt[RETURN] = &Interpretador::return_op;
    pt[GETSTATIC] = &Interpretador::getstatic;
    pt[PUTSTATIC] = &Interpretador::putstatic;
    pt[GETFIELD] = &Interpretador::getfield;
    pt[PUTFIELD] = &Interpretador::putfield;
    pt[INVOKEVIRTUAL] = &Interpretador::invokevirtual;
    pt[INVOKESPECIAL] = &Interpretador::invokespecial;
    pt[INVOKESTATIC] = &Interpretador::invokestatic;
    pt[INVOKEINTERFACE] = &Interpretador::invokeinterface;//ni
    pt[INVOKEDYNAMIC] = &Interpretador::invokedynamic;//ni
    pt[NEW] = &Interpretador::new_op;
    pt[NEWARRAY] = &Interpretador::newarray;
    pt[ANEWARRAY] = &Interpretador::anewarray;
    pt[ARRAYLENGTH] = &Interpretador::arraylength;//ni
    pt[ATHROW] = &Interpretador::athrow;
    pt[CHECKCAST] = &Interpretador::checkcast;//ni
    pt[INSTANCEOF] = &Interpretador::instanceof;//ni
      // Utiliizada na println. Tem a ver com threads e por isso acho que não deve ser
    // implementada. Vai ver só precisa retornar.
    pt[MONITORENTER] = &Interpretador::monitorenter;
    pt[MONITOREXIT] = &Interpretador::monitorexit;
    pt[WIDE] = &Interpretador::wide;
    pt[MULTIANEWARRAY] = &Interpretador::multianewarray;//ni
    pt[IFNULL] = &Interpretador::ifnull;
    pt[IFNONNULL] = &Interpretador::ifnonnull;
    pt[GOTO_W] = &Interpretador::goto_w;
    pt[JSR_W] = &Interpretador::jsr_w;//nao foi testada
    pt[BREAKPOINT] = &Interpretador::breakpoint;//ni
    pt[IMPDEP1] = &Interpretador::impdep1;//ni
    pt[IMPDEP2] = &Interpretador::impdep2;//ni
    this->instructions = pt;
}

int Interpretador::nop(){
    return 1;
}

int Interpretador::aconst_null(){
    Local_var operand;
    operand.tag = OBJECTTYPE;
    operand.value.reference_value = NULL;
    this->frame_corrente->operandStack.push_back(operand);
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

int Interpretador::lconst_0(){
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
    Local_var operand[2];
    operand[0].tag = LONGO;
    operand[1].tag = LONGO;
    operand[0].value.long_value = 1;
    operand[1].value.long_value = 0;
    this->frame_corrente->operandStack.push_back(operand[1]);
    this->frame_corrente->operandStack.push_back(operand[0]);
    return 1;
}


int Interpretador::fconst_0(){
      Local_var value;

      value.tag = PFLUTUANTE;
      value.value.float_value = 0;
      this->frame_corrente->operandStack.push_back(value);

      return 1;
}

int Interpretador::fconst_1(){
      Local_var value;

      value.tag = PFLUTUANTE;
      value.value.float_value = 1;
      this->frame_corrente->operandStack.push_back(value);

      return 1;
}

int Interpretador::fconst_2(){
      Local_var value;

      value.tag = PFLUTUANTE;
      value.value.float_value = 2;
      this->frame_corrente->operandStack.push_back(value);

      return 1;
}

int Interpretador::dconst_0(){
    Local_var zero;
    zero.tag = DUPLO;
    zero.value.double_value= 0;
    this->frame_corrente->operandStack.push_back(zero);
    this->frame_corrente->operandStack.push_back(zero);
    return 1;
}
int Interpretador::dconst_1(){
    double val = 1;
    double *p= &val;
    int *i;
    Local_var high;
    Local_var low;

    low.tag=DUPLO;
    high.tag=DUPLO;
    i = (int*)p;
    high.value.double_value=*i;
    printf("TESTE Maroto do Diego %d\n", *i);
    i++;

    low.value.double_value=*i;

    this->frame_corrente->operandStack.push_back(low);
    this->frame_corrente->operandStack.push_back(high);
    return 1;
}

int Interpretador::bipush(){
    Local_var operand;
    uint32_t n = (uint8_t) this->code_corrente->code[this->frame_corrente->pc+1];
    if (n & 0x80)
        n |= 0xFFFFFF00; //sign extend the number

    operand.tag = INT;
    operand.value.int_value = n;

    this->frame_corrente->operandStack.push_back(operand);
    return 2;
}

int Interpretador::sipush(){
    DEBUG_ENTRADA;
    Local_var resultado;

    uint16_t var = read_code_word(this->code_corrente->code, this->frame_corrente->pc+1);

    resultado.tag = INT;
    resultado.value.int_value = (int32_t)var;
    this->frame_corrente->operandStack.push_back(resultado);
    DEBUG_PRINT(resultado.value.int_value);
    DEBUG_SAIDA;
    return 3;
}

int Interpretador::ldc(){

    uint8_t index = code_corrente->code[frame_corrente->pc+1];
    float * alocador = NULL;

    Local_var operand;
    cp_tag tag = this->frame_corrente->cf->constant_pool[index-1].tag;
    //utilizado formato if()/else if() por alguns casos necessitarem de declarar variaveis
    if(tag == CONSTANT_Integer){
            operand.tag = INT;
            operand.value.int_value = this->frame_corrente->cf->constant_pool[index-1].cp_union.constant_integer.bytes;
            //colocar o valor na operand stack
            this->frame_corrente->operandStack.push_back(operand);
    }else if(tag == CONSTANT_Float){
          operand.tag = PFLUTUANTE;
          alocador = (float *)&this->frame_corrente->cf->constant_pool[index-1].cp_union.constant_float.bytes;
          operand.value.float_value = *alocador;
          this->frame_corrente->operandStack.push_back(operand);
   }else if(tag == CONSTANT_String){

            operand.tag = STRINGTYPE;


            uint8_t utf8_index = this->frame_corrente->cf->constant_pool[index-1].cp_union.constant_string.string_index;
            operand.value.string_value = new string(this->frame_corrente->cf->constant_pool[utf8_index-1].cp_union.constant_Utf8.bytes);

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

// Não foi testada, mas a única diferença da ldc é que o index dessa são 2 bytes.
// Só muda o modo de obter o index e o return.
int Interpretador::ldc_w(){
    uint16_t index = 0;
    Local_var operand;

    index = read_code_word(this->code_corrente->code, this->frame_corrente->pc+1);

    cp_tag tag = this->frame_corrente->cf->constant_pool[index-1].tag;

    //utilizado formato if()/else if() por alguns casos necessitarem de declarar variaveis
    if(tag == CONSTANT_Integer){
            operand.tag = INT;
            operand.value.int_value = this->frame_corrente->cf->constant_pool[index-1].cp_union.constant_integer.bytes;
            //colocar o valor na operand stack
            this->frame_corrente->operandStack.push_back(operand);
    }else if(tag == CONSTANT_Float){


   }else if(tag == CONSTANT_String){
            operand.tag = STRINGTYPE;

            uint8_t utf8_index = this->frame_corrente->cf->constant_pool[index-1].cp_union.constant_string.string_index;
            operand.value.string_value = new string(this->frame_corrente->cf->constant_pool[utf8_index-1].cp_union.constant_Utf8.bytes);

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
    return 3;//opcode e byte seguinde lidos
}

// A única diferença dessa para a ldc_w é que essa carrega 2 bytes ao invés de 1
// Os byte são colocados na pilha de operandos da seguinte forma:
// ---- topo da pilha de operandos ----
// LOW
// HIGH
// ---- base da pilha ------
int Interpretador::ldc2_w(){
    uint16_t index = 0;
    Local_var operand_high, operand_low;

    index = this->code_corrente->code[this->frame_corrente->pc+1];
    index <<= 8;
    index |= this->code_corrente->code[this->frame_corrente->pc+2];

    cp_tag tag = this->frame_corrente->cf->constant_pool[index-1].tag;
    //utilizado formato if()/else if() por alguns casos necessitarem de declarar variaveis
    if(tag == CONSTANT_Long) {
            operand_high.tag = LONGO;
            operand_low.tag = LONGO;
            operand_high.value.long_value = this->frame_corrente->cf->constant_pool[index-1].cp_union.constant_long.high_bytes;
            operand_low.value.long_value = this->frame_corrente->cf->constant_pool[index-1].cp_union.constant_long.low_bytes;
            //colocar o valor na operand stack
            this->frame_corrente->operandStack.push_back(operand_high);
            this->frame_corrente->operandStack.push_back(operand_low);

      }
      else if(tag == CONSTANT_Double) {
          operand_high.tag = DUPLO;
          operand_low.tag = DUPLO;
          operand_high.value.double_value = this->frame_corrente->cf->constant_pool[index-1].cp_union.constant_double.high_bytes;
          operand_low.value.double_value = this->frame_corrente->cf->constant_pool[index-1].cp_union.constant_double.low_bytes;
          //colocar o valor na operand stack
          this->frame_corrente->operandStack.push_back(operand_high);
          this->frame_corrente->operandStack.push_back(operand_low);
   }
   else {
            //exception
    }

    return 3;//opcode e byte seguinde lidos
}


//int Interpretador::ldc_w(){}
//int Interpretador::ldc2_w(){}



int Interpretador::lload(){
    Local_var operand[2];
    operand[0].tag = LONGO;
    operand[1].tag = LONGO;
    uint16_t index = this->code_corrente->code[this->frame_corrente->pc+1];
    operand[0] = this->frame_corrente->localVarVector[index];
    operand[1] = this->frame_corrente->localVarVector[index+1];
    this->frame_corrente->operandStack.push_back(operand[1]);
    this->frame_corrente->operandStack.push_back(operand[0]);
    return 2;

}

int Interpretador::fload(){
    Local_var operand;
    operand.tag = PFLUTUANTE;
    uint16_t index = this->code_corrente->code[this->frame_corrente->pc+1];
    operand = this->frame_corrente->localVarVector[index];
    this->frame_corrente->operandStack.push_back(operand);
    return 2;
}

int Interpretador::dload(){
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
    Local_var operand;
    operand.tag = OBJECTTYPE;
    uint16_t index = this->code_corrente->code[this->frame_corrente->pc+1];
    operand = this->frame_corrente->localVarVector[index-1];
    this->frame_corrente->operandStack.push_back(operand);
    return 2;
}


int Interpretador::lload_0(){
    Local_var lvar = this->frame_corrente->localVarVector[0];
    if(lvar.tag != LONGO){
        printf("Variavel local carregada nao e um long, abortar\n");
    }
    lvar = this->frame_corrente->localVarVector[1];
    if(lvar.tag != LONGO){
        printf("Variavel local carregada nao e um long, abortar\n");
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[0]);
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[1]);
    return 1;

}

int Interpretador::lload_1(){
    Local_var lvar = this->frame_corrente->localVarVector[1];
    if(lvar.tag != LONGO){
        printf("Variavel local carregada nao e um long, abortar\n");
    }
    lvar = this->frame_corrente->localVarVector[2];
    if(lvar.tag != LONGO){
        printf("Variavel local carregada nao e um long, abortar\n");
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[1]);
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[2]);
    return 1;
}

int Interpretador::lload_2(){
    Local_var lvar = this->frame_corrente->localVarVector[2];
    if(lvar.tag != LONGO){
        printf("Variavel local carregada nao e um long, abortar\n");
    }
    lvar = this->frame_corrente->localVarVector[3];
    if(lvar.tag != LONGO){
        printf("Variavel local carregada nao e um long, abortar\n");
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[2]);
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[3]);
    return 1;
}

int Interpretador::lload_3(){
    Local_var lvar = this->frame_corrente->localVarVector[3];
    if(lvar.tag != LONGO){
        printf("Variavel local carregada nao e um long, abortar\n");
        exit(0);
    }
    lvar = this->frame_corrente->localVarVector[4];
    if(lvar.tag != LONGO){
        printf("Variavel local carregada nao e um long, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[3]);
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[4]);
    return 1;
}

int Interpretador::fload_0(){
    Local_var lvar = this->frame_corrente->localVarVector[0];
    if(lvar.tag != PFLUTUANTE){
        printf("Variavel local carregada nao e um float, abortar\n");
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[0]);
    return 1;
}

int Interpretador::fload_1(){
    Local_var lvar = this->frame_corrente->localVarVector[1];
    if(lvar.tag != PFLUTUANTE){
        printf("Variavel local carregada nao e um float, abortar\n");
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[1]);
    return 1;
}

int Interpretador::fload_2(){
    Local_var lvar = this->frame_corrente->localVarVector[2];
    if(lvar.tag != PFLUTUANTE){
        printf("Variavel local carregada nao e um float, abortar\n");
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[2]);
    return 1;
}

int Interpretador::fload_3(){
    Local_var lvar = this->frame_corrente->localVarVector[3];
    if(lvar.tag != PFLUTUANTE){
        printf("Variavel local carregada nao e um float, abortar\n");
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[3]);
    return 1;
}

int Interpretador::dload_0(){
    Local_var lvar = this->frame_corrente->localVarVector[0];
    if(lvar.tag != DUPLO){
        printf("Variavel local carregada nao e um double, abortar\n");
        exit(0);
    }
    lvar = this->frame_corrente->localVarVector[1];
    if(lvar.tag != DUPLO){
        printf("Variavel local carregada nao e um double, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[0]);
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[1]);
    return 1;
}

int Interpretador::dload_1(){
    Local_var lvar = this->frame_corrente->localVarVector[1];
    if(lvar.tag != DUPLO){
        printf("Variavel local carregada nao e um double, abortar\n");
        exit(0);
    }
    lvar = this->frame_corrente->localVarVector[2];
    if(lvar.tag != DUPLO){
        printf("Variavel local carregada nao e um double, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[1]);
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[2]);
    return 1;
}

int Interpretador::dload_2(){
    Local_var lvar = this->frame_corrente->localVarVector[2];
    if(lvar.tag != DUPLO){
        printf("Variavel local carregada nao e um double, abortar\n");
        exit(0);
    }
    lvar = this->frame_corrente->localVarVector[3];
    if(lvar.tag != DUPLO){
        printf("Variavel local carregada nao e um double, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[2]);
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[3]);
    return 1;
}

int Interpretador::dload_3(){
    Local_var lvar = this->frame_corrente->localVarVector[3];
    if(lvar.tag != DUPLO){
        printf("Variavel local carregada nao e um double, abortar\n");
        exit(0);
    }
    lvar = this->frame_corrente->localVarVector[4];
    if(lvar.tag != DUPLO){
        printf("Variavel local carregada nao e um double, abortar\n");
    }
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[0]);
    this->frame_corrente->operandStack.push_back( this->frame_corrente->localVarVector[1]);
    return 1;
}

int Interpretador::aload_0(){
    Local_var lvar = this->frame_corrente->localVarVector[0];
    if(lvar.tag != OBJECTTYPE){
        printf("Variavel local carregada nao eh uma referencia\n");
    }
    this->frame_corrente->operandStack.push_back(lvar);
    return 1;
}
int Interpretador::aload_1(){
    Local_var lvar = this->frame_corrente->localVarVector[1];
    if(lvar.tag != OBJECTTYPE){
        printf("Variavel local carregada nao eh uma referencia\n");
    }
    this->frame_corrente->operandStack.push_back(lvar);
    return 1;
}
int Interpretador::aload_2(){
    Local_var lvar = this->frame_corrente->localVarVector[2];
    if(lvar.tag != OBJECTTYPE){
        printf("Variavel local carregada nao e uma referencia\n");
    }
    this->frame_corrente->operandStack.push_back(lvar);
    return 1;
}
int Interpretador::aload_3(){
    Local_var lvar = this->frame_corrente->localVarVector[3];
    if(lvar.tag != OBJECTTYPE && lvar.tag != ARRAYTYPE && lvar.tag != STRINGTYPE){
        printf("Variavel local carregada nao e uma referencia\n");
    }
    this->frame_corrente->operandStack.push_back(lvar);
    return 1;
}

int Interpretador::iload(){

    Local_var operand;
    uint16_t index;

    operand.tag = INT;

    if(!_wide){
        index = (uint8_t)this->code_corrente->code[this->frame_corrente->pc+1];
        operand = this->frame_corrente->localVarVector[index];
        this->frame_corrente->operandStack.push_back(operand);
        return 2;
    }
    else{
        index = (uint16_t)this->code_corrente->code[this->frame_corrente->pc+1];

        DEBUG_PRINT(index);
        operand = this->frame_corrente->localVarVector[index];
        this->frame_corrente->operandStack.push_back(operand);
        _wide = false;
        return 3;
    }

}

int Interpretador::iload_0(){

    Local_var lvar = this->frame_corrente->localVarVector[0];
    if(lvar.tag != INT){
        printf("Variavel local carregada nao eh um inteiro! eh um: %d\n", lvar.tag);
    }
    this->frame_corrente->operandStack.push_back(lvar);
    return 1;
}
int Interpretador::iload_1(){

    Local_var lvar = this->frame_corrente->localVarVector[1];
    if(lvar.tag != INT){
        printf("Variavel local carregada nao eh um inteiro! eh um: %d\n", lvar.tag);
    }
    this->frame_corrente->operandStack.push_back(lvar);
    return 1;
}
int Interpretador::iload_2(){

    Local_var lvar = this->frame_corrente->localVarVector[2];
    if(lvar.tag != INT){
        printf("Variavel local carregada nao eh um inteiro! eh um: %d\n", lvar.tag);
    }
    this->frame_corrente->operandStack.push_back(lvar);
    return 1;
}
int Interpretador::iload_3(){

    Local_var lvar = this->frame_corrente->localVarVector[3];
    if(lvar.tag != INT){
        printf("Variavel local carregada nao eh um inteiro! eh um: %d\n", lvar.tag);
    }
    this->frame_corrente->operandStack.push_back(lvar);
    return 1;
}

int Interpretador::iaload(){
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Variavel local carregada nao eh um inteiro!\n");
    }
    int32_t index = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    if(this->frame_corrente->operandStack.back().tag != ARRAYTYPE){
        printf("Variavel local carregada nao eh um arrayref!\n");
    }
    Local_var operand;
    operand.tag = INT;
    operand.value.int_value = this->frame_corrente->operandStack.back().value.arr->at(index).val.btype.val.inteiro;
    this->frame_corrente->operandStack.pop_back();
    this->frame_corrente->operandStack.push_back(operand);
    return 1;
}
int Interpretador::laload(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::faload(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::daload(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::aaload(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::baload(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::caload(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::saload(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}



int Interpretador::fstore(){
    DEBUG_ONLY(frame_corrente->printOperandStack());
    Local_var lvar;
    lvar = this->frame_corrente->operandStack.back();
    this->frame_corrente->operandStack.pop_back();

    if(lvar.tag != PFLUTUANTE){
        printf("Erro em fstore: Tipo em operandStack diferente do esperado\n");
    }
    uint8_t local_var_index = this->code_corrente->code[this->frame_corrente->pc+1];

    this->frame_corrente->localVarVector[local_var_index]=lvar;
    DEBUG_ONLY(frame_corrente->printOperandStack());
    return 2;
}
int Interpretador::dstore(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 2;
}
int Interpretador::astore(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 2;
}

int Interpretador::istore(){

    Local_var lvar;
    lvar = this->frame_corrente->operandStack.back();
    this->frame_corrente->operandStack.pop_back();

    if(lvar.tag != INT){
        printf("Erro em istore: Tipo em operandStack diferente do esperado.\n");
    }
    uint8_t local_var_index = this->code_corrente->code[this->frame_corrente->pc+1];

    //removendo warning "unused opStackSize"
    //size_t opStackSize = this->frame_corrente->localVarVector.size();

    lvar.value.int_value = (int32_t)lvar.value.int_value;
    this->frame_corrente->localVarVector[local_var_index] = lvar;

    return 2;
}


int Interpretador::istore_0(){


    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em istore: Tipo em operandStack diferente do esperado:");
        printf("INT != %d\n", this->frame_corrente->operandStack.back().tag);
    }
    this->frame_corrente->localVarVector[0] = this->frame_corrente->operandStack.back();
    this->frame_corrente->operandStack.pop_back();

    return 1;
}
int Interpretador::istore_1(){
    Local_var new_local_var;

    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em istore: Tipo em operandStack diferente do esperado:");
        printf("INT != %d\n", this->frame_corrente->operandStack.back().tag);
    }


    new_local_var = this->frame_corrente->operandStack.back();
    this->frame_corrente->operandStack.pop_back();

    this->frame_corrente->localVarVector[1] = new_local_var;


    return 1;
}
int Interpretador::istore_2(){
    Local_var new_local_var;

    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em istore: Tipo em operandStack diferente do esperado:");
        printf("INT != %d\n", this->frame_corrente->operandStack.back().tag);
    }


    new_local_var = this->frame_corrente->operandStack.back();
    this->frame_corrente->operandStack.pop_back();

    this->frame_corrente->localVarVector[2] = new_local_var;
    return 1;
}
int Interpretador::istore_3(){
    Local_var new_local_var;

    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em istore: Tipo em operandStack diferente do esperado:");
        printf("INT != %d\n", this->frame_corrente->operandStack.back().tag);
    }


    new_local_var = this->frame_corrente->operandStack.back();
    this->frame_corrente->operandStack.pop_back();

    this->frame_corrente->localVarVector[3] = new_local_var;
    return 1;
}

// Não foi testada
int Interpretador::lstore(){
      Local_var operand_high, operand_low;
      uint8_t local_var_index = 0;
      vector<Local_var>::iterator it;

      if(this->frame_corrente->operandStack.back().tag != LONGO){
          printf("Erro em lstore: Tipo em operandStack diferente do esperado.\n");
      }
      local_var_index = this->code_corrente->code[this->frame_corrente->pc+1];


      operand_low.tag = LONGO;
      operand_low.value.long_value = this->frame_corrente->operandStack.back().value.long_value;
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[local_var_index+1] = operand_low;

      operand_high.tag = LONGO;
      operand_high.value.long_value = this->frame_corrente->operandStack.back().value.long_value;
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[local_var_index] = operand_high;

      return 2;
}

// Não foi testada
int Interpretador::lstore_0(){
      Local_var operand_high, operand_low;
      vector<Local_var>::iterator it;

      if(this->frame_corrente->operandStack.back().tag != LONGO){
          printf("Erro em lstore_0: Tipo em operandStack diferente do esperado.\n");
      }


      operand_low.tag = LONGO;
      operand_low.value.long_value = this->frame_corrente->operandStack.back().value.long_value;
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[1] = operand_low;

      operand_high.tag = LONGO;
      operand_high.value.long_value = this->frame_corrente->operandStack.back().value.long_value;
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[0] = operand_high;

      return 1;
}

int Interpretador::lstore_1(){
      Local_var operand_high, operand_low;
      vector<Local_var>::iterator it;

      if(this->frame_corrente->operandStack.back().tag != LONGO){
          printf("Erro em lstore_1: Tipo em operandStack diferente do esperado.\n");
      }



      operand_low.tag = LONGO;
      operand_low.value.long_value = this->frame_corrente->operandStack.back().value.long_value;
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[2] = operand_low;



      operand_high.tag = LONGO;
      operand_high.value.long_value = this->frame_corrente->operandStack.back().value.long_value;
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[1] = operand_high;

      return 1;
}

int Interpretador::lstore_2(){
      Local_var operand_high, operand_low;
      vector<Local_var>::iterator it;

      if(this->frame_corrente->operandStack.back().tag != LONGO){
          printf("Erro em lstore_2: Tipo em operandStack diferente do esperado.\n");
      }

      operand_low.tag = LONGO;
      operand_low.value.long_value = this->frame_corrente->operandStack.back().value.long_value;
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[3] = operand_low;

      operand_high.tag = LONGO;
      operand_high.value.long_value = this->frame_corrente->operandStack.back().value.long_value;
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[2] = operand_high;

      return 1;
}

int Interpretador::lstore_3(){
      Local_var operand_high, operand_low;
      vector<Local_var>::iterator it;

      if(this->frame_corrente->operandStack.back().tag != LONGO){
          printf("Erro em lstore_3: Tipo em operandStack diferente do esperado.\n");
      }


      operand_low.tag = LONGO;
      operand_low.value.long_value = this->frame_corrente->operandStack.back().value.long_value;
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[4] = operand_low;

      operand_high.tag = LONGO;
      operand_high.value.long_value = this->frame_corrente->operandStack.back().value.long_value;
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[3] = operand_high;

      return 1;
}

int Interpretador::fstore_0(){
        Local_var local_var;
        vector<Local_var>::iterator it;

        if(this->frame_corrente->operandStack.back().tag != PFLUTUANTE){
             printf("Erro em fstore_1: Tipo em operandStack diferente do esperado.\n");
        }


        local_var.tag = PFLUTUANTE;
        local_var.value.float_value = this->frame_corrente->operandStack.back().value.float_value;
        this->frame_corrente->operandStack.pop_back();
        this->frame_corrente->localVarVector[0] = local_var;

    return 1;
}
int Interpretador::fstore_1(){
      Local_var local_var;
      vector<Local_var>::iterator it;

      if(this->frame_corrente->operandStack.back().tag != PFLUTUANTE){
          printf("Erro em fstore_1: Tipo em operandStack diferente do esperado.\n");
      }


      local_var.tag = PFLUTUANTE;
      local_var.value.float_value = this->frame_corrente->operandStack.back().value.float_value;
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[1] = local_var;

      return 1;
}

int Interpretador::fstore_2(){
      Local_var local_var;
      vector<Local_var>::iterator it;

      if(this->frame_corrente->operandStack.back().tag != PFLUTUANTE){
          printf("Erro em fstore_2: Tipo em operandStack diferente do esperado.\n");
      }

      local_var.tag = PFLUTUANTE;
      local_var.value.float_value = this->frame_corrente->operandStack.back().value.float_value;
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[2] = local_var;

      return 1;
}
int Interpretador::fstore_3(){
      Local_var local_var;
      vector<Local_var>::iterator it;

      if(this->frame_corrente->operandStack.back().tag != PFLUTUANTE){
          printf("Erro em fstore_3: Tipo em operandStack diferente do esperado.\n");
      }

      local_var.tag = PFLUTUANTE;
      local_var.value.float_value = this->frame_corrente->operandStack.back().value.float_value;
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[3] = local_var;

      return 1;
}

int Interpretador::dstore_0(){
      Local_var high, low;

      low = this->frame_corrente->operandStack.back();
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[0] = low;

      high = this->frame_corrente->operandStack.back();
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[1] = high;

      return 1;
}
int Interpretador::dstore_1(){
      Local_var high, low;

      low = this->frame_corrente->operandStack.back();
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[1] = low;

      high = this->frame_corrente->operandStack.back();
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[2] = high;

      return 1;
}

int Interpretador::dstore_2(){
      Local_var high, low;

      low = this->frame_corrente->operandStack.back();
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[2] = low;

      high = this->frame_corrente->operandStack.back();
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[3] = high;

      return 1;
}

int Interpretador::dstore_3(){
      Local_var high, low;

      low = this->frame_corrente->operandStack.back();
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[3] = low;

      high = this->frame_corrente->operandStack.back();
      this->frame_corrente->operandStack.pop_back();
      this->frame_corrente->localVarVector[4] = high;

      return 1;
}

int Interpretador::astore_0(){
    Local_var op;
    size_t old_size = this->frame_corrente->localVarVector.size();
    op = this->frame_corrente->operandStack.back();
    if(op.tag != OBJECTTYPE){
        printf("Variavel local carregada nao eh uma referencia, abortar\n");
        exit(0);
    }

    this->frame_corrente->localVarVector.resize(old_size+1);
    this->frame_corrente->localVarVector[0] = op;
    return 1;
}

int Interpretador::astore_1(){
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
    Local_var op;
    size_t old_size = this->frame_corrente->localVarVector.size();
    op = this->frame_corrente->operandStack.back();
    if(op.tag != OBJECTTYPE){
        printf("Variavel local carregada nao e uma referencia, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.pop_back();
    this->frame_corrente->localVarVector.resize(old_size+1);
    this->frame_corrente->localVarVector[2] = op;
    return 1;
}

int Interpretador::astore_3(){
    Local_var op;
    size_t old_size = this->frame_corrente->localVarVector.size();
    op = this->frame_corrente->operandStack.back();
    if(op.tag != OBJECTTYPE && op.tag != ARRAYTYPE && op.tag != STRINGTYPE){
        printf("Variavel local carregada nao e uma referencia, abortar\n");
        exit(0);
    }
    this->frame_corrente->operandStack.pop_back();
    this->frame_corrente->localVarVector.resize(old_size+1);
    this->frame_corrente->localVarVector[3] = op;
    return 1;
}

int Interpretador::iastore(){
    if(this->frame_corrente->operandStack.back().tag != INT){
            printf("Erro em iastore: Tipo de value em operandStack diferente do esperado:");
            printf("INT != %d\n", this->frame_corrente->operandStack.back().tag);
    }
    int32_t val = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    if(this->frame_corrente->operandStack.back().tag != INT){
            printf("Erro em iastore: Tipo de index em operandStack diferente do esperado:");
            printf("INT != %d\n", this->frame_corrente->operandStack.back().tag);
    }
    int32_t index = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    //epa, problema. Se o elemento levar pop aqui, não tem mais como acessar o vetor. Precisa que tenha esse vetor na heap
    //Resposta ao problema acima: o compilador é mais esperto, sempre que iastore aparece, foi executado antes um dup
    arrayref *arr = this->frame_corrente->operandStack.back().value.arr;
    arr->at(index).val.btype.val.inteiro = val;
    this->frame_corrente->operandStack.pop_back();
    return 1;
}
int Interpretador::lastore(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::fastore(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::dastore(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::aastore(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::bastore(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::castore(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::sastore(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}

int Interpretador::pop(){
    this->frame_corrente->operandStack.pop_back();
    return 1;
}

int Interpretador::pop2(){
    this->frame_corrente->operandStack.pop_back();
    this->frame_corrente->operandStack.pop_back();
    return 1;
}

int Interpretador::dup(){
    this->frame_corrente->operandStack.push_back( this->frame_corrente->operandStack.back() );
    return 1;//opcode lido
}
int Interpretador::dup_x1(){
    vector<Local_var>::iterator it = this->frame_corrente->operandStack.end();
    this->frame_corrente->operandStack.insert(it-2, this->frame_corrente->operandStack.back());
    return 1;
}
int Interpretador::dup_x2(){
     vector<Local_var>::iterator it = this->frame_corrente->operandStack.end();
    this->frame_corrente->operandStack.insert(it-3, this->frame_corrente->operandStack.back());
    return 1;
}

int Interpretador::dup2(){
    vector<Local_var> *opStack = &this->frame_corrente->operandStack;
    //value2, value1 ->
    opStack->push_back( opStack->at(opStack->size()-2) );//value1, value2, value1 ->
    opStack->push_back( opStack->at(opStack->size()-2) );//value2, value1, value2, value1 ->
    return 1;//opcode lido
}
int Interpretador::dup2_x1(){
    vector<Local_var>::iterator it = this->frame_corrente->operandStack.end();
    this->frame_corrente->operandStack.insert(it-3, this->frame_corrente->operandStack.back());
    this->frame_corrente->operandStack.insert(it-3, this->frame_corrente->operandStack.at(this->frame_corrente->operandStack.size()-2));
    return 1;
}
int Interpretador::dup2_x2(){
    vector<Local_var>::iterator it = this->frame_corrente->operandStack.end();
    this->frame_corrente->operandStack.insert(it-4, this->frame_corrente->operandStack.back());
    this->frame_corrente->operandStack.insert(it-5, this->frame_corrente->operandStack.at(this->frame_corrente->operandStack.size()-2));
    return 1;
}

int Interpretador::swap_op(){
    vector<Local_var>::iterator it;
    it = this->frame_corrente->operandStack.end();
    this->frame_corrente->operandStack.insert(it-2, this->frame_corrente->operandStack.back());
    this->frame_corrente->operandStack.pop_back();
    return 1;
}

int Interpretador::iadd(){
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
    //..., value1, value2 ->  //indica que value2 estao no topo da pilha e logo abaixo value1
    // value1 - value2        //ordem da operacao
    // ..., result            //indica que o resultado vai pro topo da pilha
    Local_var result[2];
    int64_t lhs, rhs, resultado;
    uint32_t *alocador;
    result[0].tag = LONGO;
    result[1].tag = LONGO;
    //le value2 == rhs
    rhs = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();
    alocador = (uint32_t*) &rhs;//alocador aponta para os 32 bits mais significativos de rhs
    *(alocador+1) = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();

    //le value 1 == lhs
    lhs = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();
    alocador = (uint32_t*) &lhs;
    *(alocador+1) = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();

    resultado = lhs + rhs;
    alocador = (uint32_t*) &resultado;

    result[0].value.long_value = *alocador;//mais significativo
    result[1].value.long_value = *(alocador+1);//menos significativo
    this->frame_corrente->operandStack.push_back(result[0]);
    this->frame_corrente->operandStack.push_back(result[1]);
    return 1;
}

int Interpretador::fadd(){
      float value1 = 0, value2 = 0;
      Local_var result;

      value1 = this->frame_corrente->operandStack.back().value.float_value;
      this->frame_corrente->operandStack.pop_back();
      value2 = this->frame_corrente->operandStack.back().value.float_value;
      this->frame_corrente->operandStack.pop_back();

      result.tag = PFLUTUANTE;
      result.value.float_value = value1 + value2;
      this->frame_corrente->operandStack.push_back(result);

      return 1;
}

int Interpretador::dadd(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}

int Interpretador::isub(){
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
    //..., value1, value2 ->  //indica que value2 estao no topo da pilha e logo abaixo value1
    // value1 - value2        //ordem da operacao
    // ..., result            //indica que o resultado vai pro topo da pilha
    Local_var result[2];
    int64_t lhs, rhs, resultado;
    uint32_t *alocador;
    result[0].tag = LONGO;
    result[1].tag = LONGO;
    //le value2 == rhs
    rhs = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();
    alocador = (uint32_t*) &rhs;//alocador aponta para os 32 bits mais significativos de rhs
    *(alocador+1) = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();

    //le value 1 == lhs
    lhs = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();
    alocador = (uint32_t*) &lhs;
    *(alocador+1) = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();

    resultado = lhs - rhs;
    alocador = (uint32_t*) &resultado;

    result[0].value.long_value = *alocador;//mais significativo
    result[1].value.long_value = *(alocador+1);//menos significativo
    this->frame_corrente->operandStack.push_back(result[0]);
    this->frame_corrente->operandStack.push_back(result[1]);
    return 1;
}

int Interpretador::fsub(){
      float value1 = 0, value2 = 0;
      Local_var result;

      value2 = this->frame_corrente->operandStack.back().value.float_value;
      this->frame_corrente->operandStack.pop_back();
      value1 = this->frame_corrente->operandStack.back().value.float_value;
      this->frame_corrente->operandStack.pop_back();

      result.tag = PFLUTUANTE;
      result.value.float_value = value1 - value2;
      this->frame_corrente->operandStack.push_back(result);

      return 1;
}

int Interpretador::dsub(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}

int Interpretador::imul(){
    uint32_t lhs, rhs;
    Local_var op;
    Local_var_Type op_v;

    rhs = frame_corrente->operandStack.back().value.int_value;//extrai o valor em operand
    this->frame_corrente->operandStack.pop_back();
    lhs = frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    //printf("lhs: %d rhs: %d\n", lhs, rhs);
    op_v.int_value = (int32_t)(lhs * rhs);
    op.value = op_v;
    op.tag = INT;
    this->frame_corrente->operandStack.push_back(op);
    return 1;
}

int Interpretador::lmul(){
    //..., value1, value2 ->  //indica que value2 est� no topo da pilha e logo abaixo value1
    // value1 - value2        //ordem da opera��o
    // ..., result            //indica que o resultado vai pro topo da pilha
    Local_var result[2];
    int64_t lhs , rhs, resultado;
    uint32_t *alocador;
    result[0].tag = LONGO;
    result[1].tag = LONGO;

    //le value2 == rhs
    rhs = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();
    alocador = (uint32_t*) &rhs;//alocador aponta para os 32 bits mais significativos de rhs
    *(alocador+1) = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();

    //le value 1 == lhs
    lhs = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();
    alocador = (uint32_t*) &lhs;
    *(alocador+1) = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();

    resultado = lhs * rhs;
    alocador = (uint32_t*) &resultado;

    result[0].value.long_value = *alocador;//mais significativo
    result[1].value.long_value = *(alocador+1);//menos significativo
    this->frame_corrente->operandStack.push_back(result[0]);
    this->frame_corrente->operandStack.push_back(result[1]);
    return 1;
}

int Interpretador::fmul(){
      float value1 = 0, value2 = 0;
      Local_var result;

      value2 = this->frame_corrente->operandStack.back().value.float_value;
      this->frame_corrente->operandStack.pop_back();
      value1 = this->frame_corrente->operandStack.back().value.float_value;
      this->frame_corrente->operandStack.pop_back();

      result.tag = PFLUTUANTE;
      result.value.float_value = value1 * value2;
      this->frame_corrente->operandStack.push_back(result);

      return 1;
}

int Interpretador::dmul(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}

int Interpretador::idiv(){
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

    Local_var result[2];
    int64_t lhs, rhs, resultado;
    uint32_t *alocador;
    result[0].tag = LONGO;
    result[1].tag = LONGO;
    //le value2 == rhs
    rhs = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();
    alocador = (uint32_t*) &rhs;//alocador aponta para os 32 bits mais significativos de rhs
    *(alocador+1) = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();

    //le value 1 == lhs
    lhs = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();
    alocador = (uint32_t*) &lhs;
    *(alocador+1) = this->frame_corrente->operandStack.back().value.long_value;
    this->frame_corrente->operandStack.pop_back();
    resultado = lhs / rhs;
    alocador = (uint32_t*) &resultado;

    result[0].value.long_value = *alocador;//mais significativo
    result[1].value.long_value = *(alocador+1);//menos significativo
    this->frame_corrente->operandStack.push_back(result[0]);
    this->frame_corrente->operandStack.push_back(result[1]);
    ;
    return 1;
}

int Interpretador::fdiv(){
      float value1 = 0, value2 = 0;
      Local_var result;

      value2 = this->frame_corrente->operandStack.back().value.float_value;
      this->frame_corrente->operandStack.pop_back();
      value1 = this->frame_corrente->operandStack.back().value.float_value;
      this->frame_corrente->operandStack.pop_back();

      result.tag = PFLUTUANTE;
      result.value.float_value = value1 / value2;
      this->frame_corrente->operandStack.push_back(result);

      return 1;
}

int Interpretador::ddiv(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}

int Interpretador::irem(){
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em irem: Tipo de operando 1 em operandStack diferente do esperado.");
    }
    uint32_t rhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em irem: Tipo de operando 2 em operandStack diferente do esperado.");
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
    int64_t rhs, lhs, result;
    uint32_t *alocador;
    alocador = (uint32_t*) &rhs;
    rhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();
    *(alocador+1) = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    alocador = (uint32_t*) &lhs;
    lhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();
    *(alocador+1) = this->frame_corrente->operandStack.back().value.int_value;
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
int Interpretador::frem(){
      float value1 = 0, value2 = 0;
      Local_var result;

      value2 = this->frame_corrente->operandStack.back().value.float_value;
      this->frame_corrente->operandStack.pop_back();
      value1 = this->frame_corrente->operandStack.back().value.float_value;
      this->frame_corrente->operandStack.pop_back();

      result.tag = PFLUTUANTE;
      result.value.float_value = fmod(value1, value2);
      this->frame_corrente->operandStack.push_back(result);

      return 1;
}

int Interpretador::drem(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}

int Interpretador::ineg(){//dar pop->push s� pra isso � sacanagem
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em ineg: Tipo em operandStack diferente do esperado.");
    }
    this->frame_corrente->operandStack.back().value.int_value = -this->frame_corrente->operandStack.back().value.int_value;
    return 1;
}

int Interpretador::lneg(){
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

int Interpretador::fneg(){
      float value = 0;
      Local_var result;

      value = this->frame_corrente->operandStack.back().value.float_value;
      this->frame_corrente->operandStack.pop_back();

      result.tag = PFLUTUANTE;
      result.value.float_value = -value;
      this->frame_corrente->operandStack.push_back(result);

      return 1;
}

int Interpretador::dneg(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}

int Interpretador::ishl(){
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em ishl: Tipo em operandStack diferente do esperado:");

    }
    int32_t rhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em ishl: Tipo em operandStack diferente do esperado.");
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
int Interpretador::lshl(){
    int64_t lhs, result;
    int32_t shiftAmount;
    uint32_t *alocador;

    shiftAmount = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    alocador = (uint32_t*) &lhs;
    lhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();
    *(alocador+1) = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    shiftAmount &= 0x0000003f;
    result = lhs << shiftAmount;
    alocador = (uint32_t*) &result;
    Local_var operand[2];
    operand[0].tag = LONGO;
    operand[0].value.int_value = *alocador;
    operand[1].tag = LONGO;
    operand[1].value.int_value = *(alocador+1);

    this->frame_corrente->operandStack.push_back(operand[0]);
    this->frame_corrente->operandStack.push_back(operand[1]);
    return 1;
}

int Interpretador::ishr(){

    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em ishr: Tipo em operandStack diferente do esperado.");
    }
    int32_t rhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em ishr: Tipo em operandStack diferente do esperado.");
    }
    // está havendo problema na passagem:   lhs <=== negativo; lhs final sai positivo
    int32_t lhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    Local_var operand;
    operand.tag = INT;

    operand.value.int_value = (int32_t)(lhs / pow(2, rhs));

    this->frame_corrente->operandStack.push_back(operand);
    return 1;
}
int Interpretador::lshr(){
      int64_t lhs, result;
    int32_t shiftAmount;
    uint32_t *alocador;

    shiftAmount = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    alocador = (uint32_t*) &lhs;
    lhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();
    *(alocador+1) = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    shiftAmount &= 0x0000003f;
    result = lhs >> shiftAmount;
    alocador = (uint32_t*) &result;
    Local_var operand[2];
    operand[0].tag = LONGO;
    operand[0].value.int_value = *alocador;
    operand[1].tag = LONGO;
    operand[1].value.int_value = *(alocador+1);

    this->frame_corrente->operandStack.push_back(operand[0]);
    this->frame_corrente->operandStack.push_back(operand[1]);
    return 1;
}

int Interpretador::iushl(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::lushl(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}

int Interpretador::iand(){
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em iand: Tipo de operando 1 em operandStack diferente do esperado.");
    }
    int32_t rhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em iand: Tipo de operando 2 em operandStack diferente do esperado.");
    }
    int32_t lhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    Local_var operand;
    operand.tag = INT;
    operand.value.int_value = lhs & rhs;
    this->frame_corrente->operandStack.push_back(operand);
    return 1;
}
int Interpretador::land(){
   int64_t rhs, lhs, result;
    uint32_t *alocador;
    alocador = (uint32_t*) &rhs;
    rhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();
    *(alocador+1) = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    alocador = (uint32_t*) &lhs;
    lhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();
    *(alocador+1) = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    result = lhs & rhs;
    DEBUG_PRINT("result: " << result );
    alocador = (uint32_t*) &result;
    Local_var operand[2];
    operand[0].tag = LONGO;
    operand[0].value.int_value = *alocador;
    operand[1].tag = LONGO;
    operand[1].value.int_value = *(alocador+1);

    this->frame_corrente->operandStack.push_back(operand[0]);
    this->frame_corrente->operandStack.push_back(operand[1]);
    return 1;
}

int Interpretador::ior(){
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em ior: Tipo de operando 2 em operandStack diferente do esperado.");
    }
    int32_t rhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em ior: Tipo de operando 2 em operandStack diferente do esperado.");
    }
    int32_t lhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    Local_var operand;
    operand.tag = INT;
    operand.value.int_value = lhs | rhs;
    this->frame_corrente->operandStack.push_back(operand);
    return 1;
}
int Interpretador::lor(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}

int Interpretador::ixor(){
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em ixor: Tipo de operando 2 em operandStack diferente do esperado.");
    }
    int32_t rhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em ixor: Tipo de operando 2 em operandStack diferente do esperado.");
    }
    int32_t lhs = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    Local_var operand;
    operand.tag = INT;
    operand.value.int_value = lhs ^ rhs;
    this->frame_corrente->operandStack.push_back(operand);
    return 1;
}
int Interpretador::lxor(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}

int Interpretador::iinc(){
    uint8_t index = this->code_corrente->code[this->frame_corrente->pc+1];
    int32_t constante = this->code_corrente->code[this->frame_corrente->pc+2];

    this->frame_corrente->localVarVector[index].value.int_value += constante;
    return 3;
}

int Interpretador::i2l(){
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em i2l: Tipo de operando no topo do operandStack diferente do esperado.\n");
    }
    int32_t var = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    long int long_var = (long int) var;
    uint32_t *uint_var = (uint32_t*)&long_var;
    Local_var operand1;
    operand1.tag = LONGO;
    operand1.value.long_value = *(uint_var);
    this->frame_corrente->operandStack.push_back(operand1);

    Local_var operand2;
    operand2.tag = LONGO;
    operand2.value.long_value = *(uint_var + 1);
    this->frame_corrente->operandStack.push_back(operand2);
    return 1;
}
int Interpretador::i2f(){
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em i2f: Tipo de operando no topo do operandStack diferente do esperado.\n");
    }
    int32_t var = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    float var_float = (float)var;
    Local_var operand1;
    operand1.tag = PFLUTUANTE;
    operand1.value.float_value = var_float;
    this->frame_corrente->operandStack.push_back(operand1);
    return 1;
}
int Interpretador::i2d(){
    int tag = this->frame_corrente->operandStack.back().tag;
    if(tag != INT){
        printf("Erro em i2d: Tipo de operando no topo do operandStack diferente do esperado. %d \n", tag);
    }
    int32_t var = this->frame_corrente->operandStack.back().value.int_value;

    this->frame_corrente->operandStack.pop_back();

    double var_double = (double) var;
    uint32_t *pt_uint32 = (uint32_t*) &var_double;

    Local_var operandHigh;
    operandHigh.tag = DUPLO;
    operandHigh.value.double_value = *(pt_uint32);
    this->frame_corrente->operandStack.push_back(operandHigh);

    Local_var operandLow;
    operandLow.tag = DUPLO;
    operandLow.value.double_value = *(pt_uint32 + 1);
    this->frame_corrente->operandStack.push_back(operandLow);
    return 1;
}

int Interpretador::l2i(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::l2f(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::l2d(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}

int Interpretador::f2i(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::f2l(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::f2d(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}

int Interpretador::d2i(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::d2l(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::d2f(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}

int Interpretador::i2b(){
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em i2b: Tipo de operando no topo do operandStack diferente do esperado.\n");
    }
    int32_t var = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    int8_t int8_var = (int8_t)var;

    Local_var operand;
    operand.tag = INT;
    operand.value.int_value = (int32_t)int8_var;
    this->frame_corrente->operandStack.push_back(operand);

    return 1;
}
int Interpretador::i2c(){
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em i2c: Tipo de operando no topo do operandStack diferente do esperado.\n");
    }
    int32_t var = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    char char_var = (char)var;
    DEBUG_PRINT(var);
    DEBUG_PRINT((int32_t)char_var);
    Local_var operand;
    operand.tag = CHAR;
    operand.value.char_value = (uint8_t)char_var;
    this->frame_corrente->operandStack.push_back(operand);

    return 1;
}
int Interpretador::i2s(){
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em i2s: Tipo de operando no topo do operandStack diferente do esperado.\n");
    }
    int32_t var = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    int16_t int16_var = (int16_t)var;

    Local_var operand;
    operand.tag = INT;
    operand.value.int_value = (int32_t)int16_var;
    this->frame_corrente->operandStack.push_back(operand);

    return 1;
}

int Interpretador::lcmp(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::fcmpl(){
      float value1 = 0, value2 = 0;
      Local_var result;

      value2 = this->frame_corrente->operandStack.back().value.float_value;
      this->frame_corrente->operandStack.pop_back();
      value1 = this->frame_corrente->operandStack.back().value.float_value;
      this->frame_corrente->operandStack.pop_back();

      result.tag = INT;
      if (value1 > value2)
            result.value.int_value = 1;
      else if (value1 == value2)
            result.value.int_value = 0;
      else if (value1 < value2)
            result.value.int_value = -1;
      else
            result.value.int_value = -1;

      this->frame_corrente->operandStack.push_back(result);

      return 1;
}

int Interpretador::fcmpg(){
      float value1 = 0, value2 = 0;
      Local_var result;

      value2 = this->frame_corrente->operandStack.back().value.float_value;
      this->frame_corrente->operandStack.pop_back();
      value1 = this->frame_corrente->operandStack.back().value.float_value;
      this->frame_corrente->operandStack.pop_back();

      result.tag = INT;
      if (value1 > value2)
            result.value.int_value = 1;
      else if (value1 == value2)
            result.value.int_value = 0;
      else if (value1 < value2)
            result.value.int_value = -1;
      else
            result.value.int_value = 1;

      this->frame_corrente->operandStack.push_back(result);

      return 1;
}

int Interpretador::dcmpl(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}
int Interpretador::dcmpg(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}

////////////////////////// Conditional Branch //////////////////////////
// Conditional branch: ifeq, ifne, iflt, ifle, ifgt, ifge, ifnull, ifnonnull,
// if_icmpeq, if_icmpne, if_icmplt, if_icmple, if_icmpgt, if_icmpge, if_acmpeq, if_acmpne.

/////////// Implementação das if<cond> ///////////
// Todas elas são iguais. Só muda a comparação.

// Não foi testada
int Interpretador::ifeq() {
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
      int16_t offset = 0;

      offset = this->code_corrente->code[this->frame_corrente->pc+1];
      offset <<= 8;
      offset |= this->code_corrente->code[this->frame_corrente->pc+2];

      return offset;
}

// Não foi testada
int Interpretador::goto_w() {
      int32_t offset = 0;

      offset |= this->code_corrente->code[this->frame_corrente->pc+1] << 24 & 0xFF000000;
      offset |= this->code_corrente->code[this->frame_corrente->pc+2] << 16 & 0x00FF0000;
      offset |= this->code_corrente->code[this->frame_corrente->pc+3] << 8 & 0x0000FF00;
      offset |= this->code_corrente->code[this->frame_corrente->pc+4] & 0x000000FF;

      return offset;
}

// Não foi testada
int Interpretador::jsr() {
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

int Interpretador::tableswitch(){
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em tableswitch: valor na operandStack diferente de INT!\n");
    }
    int32_t index = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();

    uint8_t resto = this->frame_corrente->pc%4;
    int32_t defaultbytes, lowbytes, highbytes;
    int8_t *alocador;
    // 0  1  2  3  4
    //OP PD PD PD dB1
    //3 bytes de padding
    for(int i = 0; i < 4; i++){
            alocador = (int8_t*) &defaultbytes;
            alocador[i] = this->code_corrente->code[this->frame_corrente->pc + (4-resto) + i ];

            alocador = (int8_t*) &lowbytes;
            alocador[i] = this->code_corrente->code[this->frame_corrente->pc + (4-resto) + i + 4];

            alocador = (int8_t*) &highbytes;
            alocador[i] = this->code_corrente->code[this->frame_corrente->pc + (4-resto) + i + 8];
    }
    int32_t offsets[highbytes - lowbytes + 1];
    for(int j = 0; j < highbytes - lowbytes + 1; j++){
        for(int i = 0; i < 4; i++){
                alocador = (int8_t*) &offsets[j];
                alocador[i] = this->code_corrente->code[this->frame_corrente->pc + (4-resto) + i + 4*j + 12];
        }
    }
    if(index < lowbytes || index > highbytes){
        return defaultbytes;
    }else{
        return offsets[index-lowbytes];
    }
}

int Interpretador::lookupswitch(){
    if(this->frame_corrente->operandStack.back().tag != INT){
        printf("Erro em lookupswitch: valor na operandStack diferente de INT!\n");
    }
    int32_t key = this->frame_corrente->operandStack.back().value.int_value;
    this->frame_corrente->operandStack.pop_back();
    uint8_t resto = this->frame_corrente->pc%4;
    int32_t defaultbytes, npairs;
    int8_t *alocador;
    // 0  1  2  3  4
    //OP PD PD PD dB1
    //3 bytes de padding
    for(int i = 0; i < 4; i++){
            alocador = (int8_t*) &defaultbytes;
            alocador[i] = this->code_corrente->code[this->frame_corrente->pc + (4-resto) + i ];

            alocador = (int8_t*) &npairs;
            alocador[i] = this->code_corrente->code[this->frame_corrente->pc + (4-resto) + i + 4];
    }
    int32_t match[npairs], offset[npairs];
    for(int j = 0; j < npairs; j++){
        for(int i = 0; i < 4; i++){
                alocador = (int8_t*) &match[j];
                alocador[i] = this->code_corrente->code[this->frame_corrente->pc + (4-resto) + i + 8*j + 8];
                alocador = (int8_t*) &offset[j];
                alocador[i] = this->code_corrente->code[this->frame_corrente->pc + (4-resto) + i + 8*j + 12];
        }
    }
    for(int i = 0; i < npairs; i++){
        if(key == match[i]) return offset[i];
    }
    return defaultbytes;
}

int Interpretador::putstatic(){
    uint16_t name_index = code_corrente->code[frame_corrente->pc+1];
    string field_name, field_type;
    Local_var lvar;
    FieldValue fvar;

    name_index = name_index << 8;
    name_index |= code_corrente->code[frame_corrente->pc+2];
    field_name = frame_corrente->cf->getFieldName(name_index);
    field_type = frame_corrente->cf->getFieldType(name_index);
    //printf("putstatic #%d\t//%s(%s)\n", name_index, field_name.c_str(), field_type.c_str());

    lvar = this->frame_corrente->operandStack.back();
    this->frame_corrente->operandStack.pop_back(); // pop the value

    if(field_type.compare("I") == 0){
        //converte local var para fvar
        fvar.tag = BASETYPE;
        fvar.val.btype.tag = INT;
        fvar.val.btype.val.inteiro = lvar.value.int_value;

        jvm->staticHeap[frame_corrente->cf->getClassName()]->field_instances[field_name] = fvar;
        //printf("o int passado para o field eh: %d\n", lvar.value.int_value);
    }
    else if(field_type.compare("Z") == 0){
        //converte local var para fvar
        fvar.tag = BASETYPE;
        fvar.val.btype.tag = BOOL;
        fvar.val.btype.val.boleano = lvar.value.boolean_value;

        jvm->staticHeap[frame_corrente->cf->getClassName()]->field_instances[field_name] = fvar;
        //printf("o bool passado para o field eh: %d\n", lvar.value.boolean_value);
    }
    else if(field_type.compare("C") == 0){
        Local_var lvar_upper;
        lvar_upper = this->frame_corrente->operandStack.back();
        this->frame_corrente->operandStack.pop_back(); // lower
        //converte local var para fvar
        fvar.tag = BASETYPE;
        fvar.val.btype.tag = LONGO;
        fvar.val.btype.val.longo = (lvar_upper.value.long_value << 16) | lvar.value.long_value;


        jvm->staticHeap[frame_corrente->cf->getClassName()]->field_instances[field_name] = fvar;
        //printf("the int passed to the field is: %d\n", (lvar_upper.value.long_value << 16) | lvar.value.long_value);
    }
    else if(field_type.compare("D") == 0){
        Local_var lvar_upper;
        lvar_upper = this->frame_corrente->operandStack.back();
        this->frame_corrente->operandStack.pop_back();
        //converte local var para fvar
        fvar.tag = BASETYPE;
        fvar.val.btype.tag = DUPLO;
        fvar.val.btype.val.duplo = lvar_upper.value.long_value << 16 | lvar.value.long_value;


        jvm->staticHeap[frame_corrente->cf->getClassName()]->field_instances[field_name] = fvar;
        //printf("the double passed to the field is: %f\n", (double)((lvar_upper.value.long_value << 16) | (lvar.value.long_value)));
    }

    else if(field_type.substr(0, 1).compare("L") == 0){
        if(lvar.tag != STRINGTYPE)
            cout << "Tentando fazer putstatic de objeto que nao eh string, :(" << lvar.tag << endl;
        //converte local var para fvar
        fvar.tag = BASETYPE;
        fvar.val.btype.tag = STRINGTYPE;
        fvar.val.btype.val.stringue = lvar.value.string_value;


        jvm->staticHeap[frame_corrente->cf->getClassName()]->field_instances[field_name] = fvar;
        //printf("a string passada pra field: %s\n", fvar.val.btype.val.stringue->c_str());

    }
    return 3;
}

int Interpretador::putfield(){
    uint16_t name_index = code_corrente->code[frame_corrente->pc+1];
    string field_name, field_type;
    Local_var lvar, ref_var;
    FieldValue fvar;

    name_index = name_index << 8;
    name_index |= code_corrente->code[frame_corrente->pc+2];
    field_name = frame_corrente->cf->getFieldName(name_index);
    field_type = frame_corrente->cf->getFieldType(name_index);
    //printf("putfield #%d\t//%s(%s)\n", name_index, field_name.c_str(), field_type.c_str());

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
        //printf("o int passado para o field eh: %d\n", lvar.value.int_value);
    }
    else if(field_type.compare("Z") == 0){

        ref_var = this->frame_corrente->operandStack.back();
        this->frame_corrente->operandStack.pop_back(); // pop this
        //converte local var para fvar
        fvar.tag = BASETYPE;
        fvar.val.btype.tag = BOOL;
        fvar.val.btype.val.boleano = lvar.value.boolean_value;

        ref_var.value.reference_value->field_instances[field_name] = fvar;
        //printf("o bool passado para o field eh: %d\n", lvar.value.boolean_value);
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
        //printf("the int passed to the field is: %d\n", (lvar_upper.value.long_value << 16) & lvar.value.long_value);
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
        //printf("the int passed to the field is: %f\n", (double)((lvar_upper.value.long_value << 16) && (lvar.value.long_value)));
    }
    return 3;
}


int Interpretador::getstatic(){
    uint16_t name_index = code_corrente->code[frame_corrente->pc+1];
    string field_name, field_type, class_name;
    Local_var lvar;

    name_index = name_index << 8;
    name_index |= code_corrente->code[frame_corrente->pc+2];
    class_name = frame_corrente->cf->getFieldClassName(name_index);
    field_name = frame_corrente->cf->getFieldName(name_index);
    field_type = frame_corrente->cf->getFieldType(name_index);
    DEBUG_ONLY(printf("getstatic: #%d\t//%s.%s(%s)\n", name_index, class_name.c_str(), field_name.c_str(), field_type.c_str()));

    if(field_type.compare("I") == 0){

        FieldValue fvar = jvm->staticHeap[class_name]->field_instances[field_name];

        //cout << "fvar tag: " << fvar.val.btype.val.inteiro << endl;

        lvar.tag = INT;
        lvar.value.int_value = fvar.val.btype.val.inteiro;
        this->frame_corrente->operandStack.push_back(lvar);
    }

    else if(field_type.substr(0, 1).compare("L") == 0){
        Local_var lvar;

        lvar.tag = STRINGTYPE;
        if(field_type.compare("Ljava/io/PrintStream;") == 0)
            lvar.value.string_value = new string("PrintStream");//jvm->staticHeap[class_name]->field_instances[field_name].val.btype.val.stringue;
        else{
            lvar.value.string_value = jvm->staticHeap[class_name]->field_instances[field_name].val.btype.val.stringue;

            //cout << "Valor do field: " << jvm->staticHeap[class_name]->field_instances[field_name].val.btype.val.stringue << endl;
        }
        this->frame_corrente->operandStack.push_back(lvar);

    }

    return 3;
}



int Interpretador::getfield(){
    uint16_t name_index = code_corrente->code[frame_corrente->pc+1];
    //printf("entrou na funcao getfield\n");
    string field_name, field_type;
    Local_var lvar;

    name_index = name_index << 8;
    name_index |= code_corrente->code[frame_corrente->pc+2];
    field_name = frame_corrente->cf->getFieldName(name_index);
    field_type = frame_corrente->cf->getFieldType(name_index);
    //printf("getfield #%d\t//%s(%s)\n", name_index, field_name.c_str(), field_type.c_str());

    if(field_type.compare("I") == 0){
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
    //ArrayType *vetor = (ArrayType*) malloc(sizeof(ArrayType));
    //vetor->arr = new arrayref;
    operand.value.arr = new arrayref;

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
                    operand.value.arr->push_back(field);
            }
            break;
        case CONSTANT_InterfaceMethodref:
            for(int i = 0; i < count_operand; i++){

            }
            break;
        default:
            break;
    }
    this->frame_corrente->operandStack.push_back(operand);
    return 3;
}

// Não foi testada. Não está implementada, porém acho que deve ser uma das últimas.
// Ela pode chamar diversos códigos para tratar erros. Tudo tem que estar implementado
// para ela funcionar.
int Interpretador::athrow() {

    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;

}

// Não foi testada
int Interpretador::monitorenter() {

    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;

}

// Não foi testada
int Interpretador::monitorexit() {

    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}

int Interpretador::new_op(){
    uint8_t operand = code_corrente->code[frame_corrente->pc+1];//pc aponta para a instru��o; pc+1 � o byte seguinte
    uint16_t name_index = operand;
    std::string className;
    Local_var op;
    Local_var_Type op_val;

    name_index = name_index << 8;
    operand = code_corrente->code[frame_corrente->pc+2];
    name_index = name_index|operand;
    className = this->frame_corrente->cf->getCpoolClass(name_index);

    //printf("new #%d \t// %s\n", name_index, className.c_str());
    //printf("nome da classe: %s\n", className.c_str());
    op.tag = OBJECTTYPE;
    op_val.reference_value = jvm->alocarObjeto(className);
    op.value = op_val;
    frame_corrente->operandStack.push_back(op);
    //printf("Sai da new\n");
    return 3; //dois bytes lidos + o opcode
}
typedef enum atype_type_s{
    T_BOOLEAN = 4,
    T_CHAR = 5,
    T_FLOAT = 6,
    T_DOUBLE = 7,
    T_BYTE = 8,
    T_SHORT = 9,
    T_INT = 10,
    T_LONG = 11,
}a_type;

int Interpretador::newarray(){
    if(this->frame_corrente->operandStack.back().tag != INT){
            printf("Erro em newarray: Tipo de operando no topo do operandStack diferente do esperado.\n");
    }
    int32_t contador = this->frame_corrente->operandStack.back().value.int_value;
    uint8_t atype = this->code_corrente->code[this->frame_corrente->pc+1];

    //ArrayType *arrType = (ArrayType*) malloc(sizeof(ArrayType));//arraytype carrega só um ponteiro, malloc ok
    //arrayref *arr = new arrayref;
    Local_var operand;
    operand.tag = ARRAYTYPE;
    operand.value.arr = new arrayref;
    FieldValue field;
    switch(atype){
        case T_BOOLEAN:
            for(int i = 0; i < contador; i++ ){
                    field.tag = BASETYPE;
                    field.val.btype.tag = BOOL;
                    field.val.btype.val.boleano = false;
                    operand.value.arr->push_back(field);
            }
            break;
        case T_CHAR:
            for(int i = 0; i < contador; i++ ){
                    field.tag = BASETYPE;
                    field.val.btype.tag = CHAR;
                    field.val.btype.val.caractere = 0;
                    operand.value.arr->push_back(field);
            }
            break;
        case T_FLOAT:
            for(int i = 0; i < contador; i++ ){
                    field.tag = BASETYPE;
                    field.val.btype.tag = PFLUTUANTE;
                    field.val.btype.val.pFlutuante = 0;
                    operand.value.arr->push_back(field);
            }
            break;
        case T_DOUBLE:
            for(int i = 0; i < contador; i++ ){
                    field.tag = BASETYPE;
                    field.val.btype.tag = DUPLO;
                    field.val.btype.val.duplo = 0;
                    operand.value.arr->push_back(field);
            }
            break;
        case T_BYTE:
            for(int i = 0; i < contador; i++ ){
                    field.tag = BASETYPE;
                    field.val.btype.tag = BYTE;
                    field.val.btype.val.byte = 0;
                    operand.value.arr->push_back(field);
            }
            break;
        case T_SHORT:
            for(int i = 0; i < contador; i++ ){
                    field.tag = BASETYPE;
                    field.val.btype.tag = CURTO;
                    field.val.btype.val.curto = 0;
                    operand.value.arr->push_back(field);
            }
            break;
        case T_INT:
            for(int i = 0; i < contador; i++ ){
                    field.tag = BASETYPE;
                    field.val.btype.tag = INT;
                    field.val.btype.val.inteiro = 0;
                    operand.value.arr->push_back(field);
            }
            break;
        case T_LONG:
            for(int i = 0; i < contador; i++ ){
                    field.tag = BASETYPE;
                    field.val.btype.tag = LONGO;
                    field.val.btype.val.longo = 0;
                    operand.value.arr->push_back(field);
            }
            break;
    }
    this->frame_corrente->operandStack.push_back(operand);
    return 2;
}

int Interpretador::invokespecial(){
    uint8_t operand = code_corrente->code[frame_corrente->pc+1];
    uint16_t method_index = operand;
    string invoking_class, method_name, descriptor, argtypes;
    ClassFile* cf;
    vector<Local_var> args;
    Local_var lvar;

    method_index = method_index << 8;
    operand = code_corrente->code[frame_corrente->pc+2];
    method_index = method_index|operand; //este � o indice na constant pool
    this->frame_corrente->cf->getCpoolMethod(method_index, invoking_class, method_name, descriptor);
    //printf("invokespecial #%d\t//%s.%s:%s\n", method_index, invoking_class.c_str(), method_name.c_str(), descriptor.c_str());
    cf = this->jvm->getClassRef(invoking_class);

    // pega os argumentos da pilha
    for (int i=1; i < (int)descriptor.find(")"); i++){
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


int Interpretador::invokestatic(){
    uint8_t operand = code_corrente->code[frame_corrente->pc+1];
    uint16_t method_index = operand;
    string invoking_class, method_name, descriptor, argtypes, super_name;
    ClassFile* cf;
    vector<Local_var> args;
    Local_var lvar;
    int found = -1;

    method_index = method_index << 8;
    operand = code_corrente->code[frame_corrente->pc+2];
    method_index = method_index|operand; //este � o indice na constant pool
    this->frame_corrente->cf->getCpoolMethod(method_index, invoking_class, method_name, descriptor);

    // se for o println então printamos e esta tudo certo
    if(!strcmp(method_name.c_str(), "println") && !strcmp(invoking_class.c_str(), "java/io/PrintStream")){
        Local_var print_var = this->frame_corrente->operandStack.back();
        this->frame_corrente->operandStack.pop_back();
        cout << print_var.repr() << endl;
        return 3;
    }
    // se for o registerNatives, ignore
    if(method_name.compare("registerNatives") == 0){
        return 3;
    }

    cf = this->jvm->getClassRef(invoking_class);
    Frame *staticFrame;

    if((jvm->staticHeap.count(invoking_class) != 1)){
        int clinitN = cf->findMethod("<clinit>", "()V");
        staticFrame = new Frame(clinitN, cf);
        //cout << "Clinit encontrado em: " << clinitN << endl;
        jvm->staticHeap[invoking_class] = jvm->alocarObjetoEstatico(invoking_class);
        runCode(staticFrame);
    }
    DEBUG_PRINT(("invokestatic: passei daqui\n"));
    //precisamos encontrar em qual classF este m�todo foi declarado
    super_name = cf->getClassName(); // come�a loop na classe invocadora
    do{
        cf = this->jvm->getClassRef(super_name);

        found = cf->findMethod(method_name, descriptor);
        super_name = cf->getSuper();
        if(super_name.empty()){// se n�o possuir super, ent�o o m�todo n�o existe
            printf("Metodo passado nao existe\n");
            exit(0);
        }
    }while(found == -1);

    method_index = found;
    //printf("encontrei o metodo, esta na classe %s, numero %d\n", cf->getClassName().c_str(), method_index);

    // pega os argumentos da pilha
    for (int i=1; i < (int)descriptor.find(")"); i++){
        args.push_back(this->frame_corrente->operandStack.back());
        this->frame_corrente->operandStack.pop_back();
    }

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

int Interpretador::invokevirtual(){
    uint16_t method_index;
    string invoking_class, method_name, descriptor, argtypes, super_name;
    ClassFile* cf;
    vector<Local_var> args;
    Local_var lvar;
    int found = -1;


    method_index = code_corrente->code[frame_corrente->pc+1];
    method_index = method_index  << 8;
    method_index |= code_corrente->code[frame_corrente->pc+2];
    this->frame_corrente->cf->getCpoolMethod(method_index, invoking_class, method_name, descriptor);
    //printf("invokevirtual #%d\t//%s.%s:%s\n", method_index, invoking_class.c_str(), method_name.c_str(), descriptor.c_str());

    if(!strcmp(method_name.c_str(), "println") && !strcmp(invoking_class.c_str(), "java/io/PrintStream")){
        Local_var print_var = this->frame_corrente->operandStack.back();
        this->frame_corrente->operandStack.pop_back();
        if(print_var.tag == LONGO){
                Local_var print_var2 = this->frame_corrente->operandStack.back();
                this->frame_corrente->operandStack.pop_back();
                int64_t var64bits;
                uint32_t *alocador = (uint32_t*) &var64bits;
                alocador[0] = print_var2.value.long_value;
                alocador[1] = print_var.value.long_value;
                cout << var64bits <<endl;

        }else if(print_var.tag == DUPLO){
                Local_var print_var2 = this->frame_corrente->operandStack.back();
                this->frame_corrente->operandStack.pop_back();
                double var64bits;
                uint32_t *alocador = (uint32_t*) &var64bits;
                alocador[0] = print_var2.value.double_value;
                alocador[1] = print_var.value.double_value;
                cout.precision(16);
                cout << fixed << var64bits <<endl;

        }else if(print_var.tag == PFLUTUANTE){
                cout.precision(7);
                cout << fixed << print_var.value.float_value << endl;
        }

        else{

                cout << print_var.repr() << endl;
        }
        this->frame_corrente->operandStack.pop_back(); // pop printstream ref
        ;
        return 3;
    }


    cf = this->jvm->getClassRef(invoking_class);
    //precisamos encontrar em qual classF este metodo foi declarado
    super_name = cf->getClassName(); // comeca loop na classe invocadora
    do{
        cf = this->jvm->getClassRef(super_name);

        found = cf->findMethod(method_name, descriptor);
        super_name = cf->getSuper();
        //cout << "super name: "<< super_name << endl;
        if(super_name.empty()){// se nao possuir super, entao o metodo nao existe
            printf("Metodo passado nao existe\n");
            exit(0);
        }
    }while(found == -1);

    method_index = found;
    //printf("encontrei o metodo, esta na classe %s, numero %d\n", cf->getClassName().c_str(), method_index);

    // pega os argumentos da pilha
    for (int i=1; i < (int)descriptor.find(")"); i++){
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
    return 1;
}

int Interpretador::ireturn(){
    if (this->frame_corrente->operandStack.size() != 1){
        printf("Funcao com defeito de retorno,\n");
    }
    Local_var lvar = this->frame_corrente->operandStack.back();

    if(lvar.tag != 1){
        printf("Funcao nao retornou um inteiro\n");
    }

    return 1;
}

int Interpretador::iushr(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}

int Interpretador::lushr(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}

int Interpretador::ret(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}

int Interpretador::lreturn(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}

int Interpretador::freturn(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}//ni
int Interpretador::dreturn(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}//ni
int Interpretador::areturn(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}//ni
int Interpretador::invokeinterface(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}//ni
int Interpretador::invokedynamic(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}//ni
int Interpretador::arraylength(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}//ni
int Interpretador::checkcast(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}//ni
int Interpretador::instanceof(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}//ni

int Interpretador::wide(){
    this->_wide = true;
    DEBUG_PRINT("wide!!!!");

    return 1;
}

int Interpretador::multianewarray(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}//ni
int Interpretador::breakpoint(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}//ni
int Interpretador::impdep1(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}//ni
int Interpretador::impdep2(){
    DEBUG_PRINT("INSTRUCAO NAO IMPLEMENTADA");
    return 1;
}//ni

#ifdef DEBUG_E_S
    #undef DEBUG_E_S
#endif // DEBUG_E_S

#ifdef Debug
    #undef Debug
#endif
