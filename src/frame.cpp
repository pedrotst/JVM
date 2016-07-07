#include "../include/frame.hpp"

using namespace std;

string Local_var::repr(){
    stringstream converter;
    switch (this->tag){
        case BOOL:
            converter << value.boolean_value;
            return converter.str();
        case INT:
            converter << value.int_value;
            return converter.str();
        case CHAR:
            converter << value.char_value;
            return converter.str();
        case BYTE:
            converter << value.byte_value;
            return converter.str();
        case LONGO:
            converter << value.long_value;
            return converter.str();
        case PFLUTUANTE:
            converter << value.float_value;
            return converter.str();
        case CURTO:
            converter << value.short_value;
            return converter.str();
        case DUPLO:
            converter << value.double_value;
            return converter.str();
            break;
        case BASETYPE:
            break;
        case OBJECTTYPE:
            break;
        case ARRAYTYPE:
            break;
        case VOID_T:
        case RETURN_ADDRESS:
            break;
        case STRINGTYPE:
            return *value.string_value;
    }

    string buf;
    return buf;
}

Frame::Frame(int method_index, ClassFile *cf){
	this->method_index = method_index;
	this->cf = cf;
}
void Frame::printOperandStack(){
    printf("OperandStack:\n");
    for(int i = 0; i < (int)operandStack.size(); i++){
        switch(operandStack[i].tag){
            case BOOL:
                printf("tag: BOOL | %d //", this->operandStack[i].value.boolean_value);
                break;
            case INT:
                printf("tag: INT | %d //", this->operandStack[i].value.int_value);
                break;
            case CHAR:
                printf("tag: CHAR | %d //", this->operandStack[i].value.char_value);
                break;
            case BYTE:
                printf("tag: BYTE | %d //", this->operandStack[i].value.byte_value);
                break;
            case LONGO:
                printf("tag: LONG | %d //", this->operandStack[i].value.long_value);
                break;
            case PFLUTUANTE:
                printf("tag: PF | %d //", this->operandStack[i].value.float_value);
                break;
            case CURTO:
                printf("tag: SHORT | %d //", this->operandStack[i].value.short_value);
                break;
            case DUPLO:
                printf("tag: DOUBLE | %d //", this->operandStack[i].value.double_value);
                break;
            case BASETYPE:
                //printf("tag: BASETYPE | %x", *(this->operandStack[i].value.reference_value));
                printf("tag: BASETYPE //");
                break;
            case OBJECTTYPE:
                //printf("tag: OBJECTTYPE | %x", this->operandStack[i].value.reference_value);
                printf("tag: OBJECTTYPE //");
                break;
            case ARRAYTYPE:
                //printf("tag: ARRAYTYPE | %x", this->operandStack[i].value.arrayref);
                printf("tag: ARRAYTYPE[%zu] {", this->operandStack[i].value.arrayref->arr->size());
                for(int j = 0; j < (int)this->operandStack[i].value.arrayref->arr->size(); j++){
                    printf("%d,", this->operandStack[i].value.arrayref->arr->at(j).val.btype.val.inteiro);
                }
                printf("} //");
                break;
            case VOID_T:
                printf("tag: VOID_T | %d", this->operandStack[i].value.void_v);
                break;
            case RETURN_ADDRESS:
                //printf("tag: RETURN_ADDRESS | %d", this->operandStack[i].value.returnAddress_value);
                printf("tag: RETURN ADDRESS //");
                break;
            case STRINGTYPE:
                cout << "tag: STRINGTYPE |  \\" << this->operandStack[i].repr();
                //printf("tag: STRINGTYPE //");
                break;
        }
    }
    printf("\n");
}

void Frame::printLocalVar(){
    printf("Locar_var:\n");
    if(localVarVector.size() == 0) printf("//vazia//\n");
    for(int i = 0; i < (int)localVarVector.size(); i++){
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
                //printf("tag: BASETYPE | val: %x //", this->localVarVector[i].value.reference_value);
                printf("tag: BASETYPE");
                break;
            case OBJECTTYPE:
                //printf("tag: OBJECTTYPE | val: %x //", this->localVarVector[i].value.reference_value);
                printf("tag: OBJECTTYPE");
                break;
            case ARRAYTYPE:
                //printf("tag: ARRAYTYPE | val: %x //", this->localVarVector[i].value.arrayref);
                printf("tag: ARRAYTYPE[%zu] {", this->localVarVector[i].value.arrayref->arr->size());
                for(int j = 0; j < (int)this->localVarVector[i].value.arrayref->arr->size(); j++){
                    printf("%d,", this->localVarVector[i].value.arrayref->arr->at(j).val.btype.val.inteiro);
                }
                printf("} //");
                break;
            case VOID_T:
                printf("tag: VOID_T | val: %d //", this->localVarVector[i].value.void_v);
                break;
            case RETURN_ADDRESS:
                //printf("tag: RETURN_ADDRESS | val: %d //", this->localVarVector[i].value.returnAddress_value);
                printf("tag: RETURN ADDRESS");
                break;
            case STRINGTYPE:
                //printf("tag: STRINGTYPE | val: %x //", this->localVarVector[i].value.string_value);
                printf("tag: STRINGTYPE");
                break;
        }
    }
    printf("\n");
}
