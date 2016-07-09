#include "../include/frame.hpp"

using namespace std;

string FieldValue::repr(){
    stringstream converter;
    switch (this->tag){
        case BASETYPE:
            switch (this->val.btype.tag){
            case BOOL:
                converter << val.btype.val.boleano;
                return converter.str();
            case INT:
                converter << val.btype.val.inteiro;
                return converter.str();
            case CHAR:
                converter << val.btype.val.caractere;
                return converter.str();
            case BYTE:
                converter << val.btype.val.byte;
                return converter.str();
            case LONGO:
                converter << val.btype.val.longo;
                return converter.str();
            case PFLUTUANTE:
                converter << val.btype.val.pFlutuante;
                return converter.str();
            case CURTO:
                converter << val.btype.val.curto;
                return converter.str();
            case DUPLO:
                converter << val.btype.val.duplo;
                return converter.str();
            case STRINGTYPE:
                return "'" + *val.btype.val.stringue + "'";
            default:
                break;
            }
        case OBJECTTYPE:{
            string buff("Referencia para objeto de: ");
            return buff.append(val.objtype.instance->cf->getClassName());
        }
        case ARRAYTYPE:
            return *new string("Array");
        case VOID_T:
            return "VOID";
        default:
            break;
    }

    string buf;
    return buf;
}

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
            return "VOID";
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
    printf(" OperandStack:\n");
    if(operandStack.size() == 0) printf(" //vazia//");
    for(int i = 0; i < (int)operandStack.size(); i++){
        switch(operandStack[i].tag){
            case BOOL:
                printf(" [%d] BOOL: %d //", i, this->operandStack[i].value.boolean_value);
                break;
            case INT:
                printf(" [%d] INT: %d //", i, this->operandStack[i].value.int_value);
                break;
            case CHAR:
                printf(" [%d] CHAR: %c //", i, this->operandStack[i].value.char_value);
                break;
            case BYTE:
                printf(" [%d] BYTE: %d //", i, this->operandStack[i].value.byte_value);
                break;
            case LONGO:
                printf(" [%d] LONG: %d //", i, this->operandStack[i].value.long_value);
                break;
            case PFLUTUANTE:
                printf(" [%d] FLOAT: %f //", i, this->operandStack[i].value.float_value);
                break;
            case CURTO:
                printf(" [%d] SHORT: %d //", i, this->operandStack[i].value.short_value);
                break;
            case DUPLO:
                printf(" [%d] tag: DOUBLE: %X //", i, this->operandStack[i].value.double_value);
                break;
            case BASETYPE:
                //printf("tag: BASETYPE | %x", *(this->operandStack[i].value.reference_value));
                printf(" [%d] BASETYPE //", i);
                break;
            case OBJECTTYPE:
                //printf("tag: OBJECTTYPE | %x", this->operandStack[i].value.reference_value);
                printf(" [%d]  OBJECTTYPE: %s //", i, this->operandStack[i].value.reference_value->cf->getClassName().c_str());
                break;
            case ARRAYTYPE:
                //printf("tag: ARRAYTYPE | %x", this->operandStack[i].value.arrayref);
                printf(" [%d] ARRAYTYPE[%zu] {", i, this->operandStack[i].value.arr->size());
                for(int j = 0; j < (int)this->operandStack[i].value.arr->size(); j++){
                    cout << this->operandStack[i].value.arr->at(j).repr() << ", ";
                }
                printf("} //");
                break;
            case VOID_T:
                printf(" [%d] VOID_T: %d", i, this->operandStack[i].value.void_v);
                break;
            case RETURN_ADDRESS:
                //printf("tag: RETURN_ADDRESS | %d", this->operandStack[i].value.returnAddress_value);
                printf(" [%d] RETURN ADDRESS //", i);
                break;
            case STRINGTYPE:
                printf(" [%d] STRINGTYPE: {""%s""} //", i, this->operandStack[i].value.string_value->c_str());
                //printf("tag: STRINGTYPE //");
                break;
        }
    }
    printf("\n");
}

void Frame::printLocalVar(){
    printf(" Locar_var:\n");
    if(localVarVector.size() == 0) printf(" //vazia//");
    for(int i = 0; i < (int)localVarVector.size(); i++){
        switch(localVarVector[i].tag){
            case BOOL:
                printf(" [%d] BOOL: %d //", i, this->localVarVector[i].value.boolean_value);
                break;
            case INT:
                printf(" [%d] INT: %d //", i, this->localVarVector[i].value.int_value);
                break;
            case CHAR:
                printf(" [%d] CHAR: %c //", i, this->localVarVector[i].value.char_value);
                break;
            case BYTE:
                printf(" [%d] BYTE: %d //", i, this->localVarVector[i].value.byte_value);
                break;
            case LONGO:
                printf(" [%d] LONG: %d //", i,  this->localVarVector[i].value.long_value);
                break;
            case PFLUTUANTE:
                printf(" [%d] FLOAT: %f //",  i, this->localVarVector[i].value.float_value);
                break;
            case CURTO:
                printf(" [%d] SHORT: %d //",  i, this->localVarVector[i].value.short_value);
                break;
            case DUPLO:
                printf(" [%d] DOUBLE: %d //",  i, this->localVarVector[i].value.double_value);
                break;
            case BASETYPE:
                //printf("tag: BASETYPE | val: %x //", this->localVarVector[i].value.reference_value);
                printf(" [%d] BASETYPE", i);
                break;
            case OBJECTTYPE:
                //printf("tag: OBJECTTYPE | val: %x //", this->localVarVector[i].value.reference_value);
                printf(" [%d] OBJECTTYPE", i);
                break;
            case ARRAYTYPE:
                //printf("tag: ARRAYTYPE | val: %x //", this->localVarVector[i].value.arrayref);
                printf(" [%d] ARRAYTYPE[%zu] {",  i, this->localVarVector[i].value.arr->size());
                for(int j = 0; j < (int)this->localVarVector[i].value.arr->size(); j++){
                    cout << this->localVarVector[i].value.arr->at(j).repr() << ", ";
                }
                printf("} //");
                break;
            case VOID_T:
                printf(" [%d] VOID_T: %d //",  i, this->localVarVector[i].value.void_v);
                break;
            case RETURN_ADDRESS:
                printf(" [%d] RETURN ADDRESS", i);
                break;
            case STRINGTYPE:
                printf(" [%d] STRINGTYPE: {""%s""} //",  i, this->localVarVector[i].value.string_value->c_str());
                break;
        }
    }
    printf("\n");
}

void InstanceClass::printInstancia(){
    cout << " PrintInstancia da classe: " << cf->getClassName() << endl;
    for(auto const &ent : field_instances) {
        string fname = ent.first;
        FieldValue fval = ent.second;
        cout << " " << fname << "*" << fval.tag << "*" << ": " << fval.repr() << "// ";
    }
    cout << endl;
}
