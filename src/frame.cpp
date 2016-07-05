#include "../include/frame.hpp"

Frame::Frame(int method_index, ClassFile *cf){
	this->method_index = method_index;
	this->cf = cf;
}

void Frame::printOperandStack(){
    printf("OperandStack:\n");
    if(operandStack.size() == 0) printf("//vazia//\n");
    for(int i = 0; i < operandStack.size(); i++){
        switch(operandStack[i].tag){
            case BOOL:
                printf("tag: BOOL | val: %d //", this->operandStack[i].value.boolean_value);
                break;
            case INT:
                printf("tag: INT | val: %d //", this->operandStack[i].value.int_value);
                break;
            case CHAR:
                printf("tag: CHAR | val: %d //", this->operandStack[i].value.char_value);
                break;
            case BYTE:
                printf("tag: BYTE | val: %d //", this->operandStack[i].value.byte_value);
                break;
            case LONGO:
                printf("tag: LONG | val: %d //", this->operandStack[i].value.long_value);
                break;
            case PFLUTUANTE:
                printf("tag: PF | val: %d //", this->operandStack[i].value.float_value);
                break;
            case CURTO:
                printf("tag: SHORT | val: %d //", this->operandStack[i].value.short_value);
                break;
            case DUPLO:
                printf("tag: DOUBLE | val: %d //", this->operandStack[i].value.double_value);
                break;
            case BASETYPE:
                printf("tag: BASETYPE | val: %x //", this->operandStack[i].value.reference_value);
                break;
            case OBJECTTYPE:
                printf("tag: OBJECTTYPE | val: %x //", this->operandStack[i].value.reference_value);
                break;
            case ARRAYTYPE:
                printf("tag: ARRAYTYPE | val: %x //", this->operandStack[i].value.arrayref);
                break;
            case VOID_T:
                printf("tag: VOID_T | val: %d //", this->operandStack[i].value.void_v);
                break;
            case RETURN_ADDRESS:
                printf("tag: RETURN_ADDRESS | val: %d //", this->operandStack[i].value.returnAddress_value);
                break;
            case STRINGTYPE:
                printf("tag: STRINGTYPE | val: %x //", this->operandStack[i].value.string_value);
                break;
        }
    }
    printf("\n");
}

void Frame::printLocalVar(){
    printf("Locar_var:\n");
    if(localVarVector.size() == 0) printf("//vazia//\n");
    for(int i = 0; i < localVarVector.size(); i++){
        switch(localVarVector[i].tag){
            case BOOL:
                printf("tag: BOOL | val: %d //", this->localVarVector[i].value.boolean_value);
                break;
            case INT:
                printf("tag: INT | val: %d //", this->localVarVector[i].value.int_value);
                break;
            case CHAR:
                printf("tag: CHAR | val: %d //", this->localVarVector[i].value.char_value);
                break;
            case BYTE:
                printf("tag: BYTE | val: %d //", this->localVarVector[i].value.byte_value);
                break;
            case LONGO:
                printf("tag: LONG | val: %d //", this->localVarVector[i].value.long_value);
                break;
            case PFLUTUANTE:
                printf("tag: PF | val: %d //", this->localVarVector[i].value.float_value);
                break;
            case CURTO:
                printf("tag: SHORT | val: %d //", this->localVarVector[i].value.short_value);
                break;
            case DUPLO:
                printf("tag: DOUBLE | val: %d //", this->localVarVector[i].value.double_value);
                break;
            case BASETYPE:
                printf("tag: BASETYPE | val: %x //", this->localVarVector[i].value.reference_value);
                break;
            case OBJECTTYPE:
                printf("tag: OBJECTTYPE | val: %x //", this->localVarVector[i].value.reference_value);
                break;
            case ARRAYTYPE:
                printf("tag: ARRAYTYPE | val: %x //", this->localVarVector[i].value.arrayref);
                break;
            case VOID_T:
                printf("tag: VOID_T | val: %d //", this->localVarVector[i].value.void_v);
                break;
            case RETURN_ADDRESS:
                printf("tag: RETURN_ADDRESS | val: %d //", this->localVarVector[i].value.returnAddress_value);
                break;
            case STRINGTYPE:
                printf("tag: STRINGTYPE | val: %x //", this->localVarVector[i].value.string_value);
                break;
        }
    }
    printf("\n");
}
