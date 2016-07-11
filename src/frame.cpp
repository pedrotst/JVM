#include "../include/frame.hpp"

using namespace std;

//a id�ia � gerar: [size1][size2][size3]...
//como os tamanhos dentro de cada dimens�o s�o homog�neos,
//basta olhar sempre a posi��o 0
string Frame::arrayDimension(arrayref *aRef){
    stringstream arrDim;
    arrDim << "[" << aRef->size() << "]";
    if(aRef->at(0).tag == ARRAYTYPE ){
        //vetor de fields; se for um array simples, a tag da field (at(0).tag)
        //ser� diferente de ARRAYTYPE.
        arrDim << arrayDimension(aRef->at(0).val.arrtype.arr);
        return arrDim.str();
    }else{
        return arrDim.str();
    }
}

bool Frame::isSimpleArray(arrayref *aRef){
    return aRef->at(0).tag != ARRAYTYPE;
}

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
                converter << (double) val.btype.val.duplo;
                return converter.str();
            case STRINGTYPE:
                return "'" + *val.btype.val.stringue + "'";
            default:
                break;
            }
        case OBJECTTYPE:{
            string buff("ObjRef: ");
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
            if(value.boolean_value == 1)
                converter << "TRUE";
            else
                converter << "FALSE";
            return converter.str();
        case INT:
            if(this->origem == CHAR){
                converter << (char)value.int_value;
            }
            else if(this->origem == BOOL){
                if(value.int_value == 1)
                    converter << "TRUE";
                else
                    converter << "FALSE";
            }
            else if(this->origem == BYTE){
                  converter << value.byte_value;
            }
            else {
                converter <<  value.int_value;
            }

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
            return "'" + *value.string_value + "'";
    }

    string buf;
    return buf;
}

//a id�ia � gerar {{valor1, valor2},{valor3,valor4}}
string Frame::arrayContents(arrayref *aRef){
    stringstream arrCon;
    if(aRef->at(0).tag == ARRAYTYPE ){//aRef � um ponteiro para arrayref; aRef->at(indice) � um FieldValue
        arrCon << "{";
        for(uint32_t i = 0; i < aRef->size(); i++){
            arrCon << arrayContents(aRef->at(i).val.arrtype.arr);
            if(aRef->size()-1 != i){
                arrCon << " , ";
             }
        }
        arrCon << "}";
        return arrCon.str();
    }else{//aqui imprime {val1, val2l...}
        arrCon << "<";
        for(uint32_t j = 0; j < aRef->size(); j++){
             arrCon << aRef->at(j).repr();
             if(aRef->size()-1 != j){
                    arrCon << ",";
             }
        }
        arrCon << ">";
        return arrCon.str();
    }
}

Frame::Frame(int method_index, ClassFile *cf){
	this->method_index = method_index;
	this->cf = cf;
}
void Frame::printOperandStack(){
    string arrDim, arrCon;
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
                arrDim = arrayDimension(this->operandStack[i].value.arr);
                arrCon = arrayContents(this->operandStack[i].value.arr);
                printf(" [%d] ARRAYTYPE %s%s", i, arrDim.c_str(), arrCon.c_str());
                printf(" //");
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
    string arrDim, arrCon;
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
                printf(" [%d] DOUBLE: %X //",  i, this->localVarVector[i].value.double_value);
                break;
            case BASETYPE:
                //printf("tag: BASETYPE | val: %x //", this->localVarVector[i].value.reference_value);
                printf(" [%d] BASETYPE", i);
                break;
            case OBJECTTYPE:
                //printf("tag: OBJECTTYPE | val: %x //", this->localVarVector[i].value.reference_value);
                printf(" [%d] OBJECTTYPE: %s", i, this->localVarVector[i].value.reference_value->cf->getClassName().c_str());
                break;
            case ARRAYTYPE:
                    arrDim = arrayDimension(this->localVarVector[i].value.arr);
                    arrCon = arrayContents(this->localVarVector[i].value.arr);
                    printf(" [%d] ARRAYTYPE %s%s", i, arrDim.c_str(), arrCon.c_str());
                printf(" //");
                break;
            case VOID_T:
                printf(" [%d] VOID_T: %d //",  i, this->localVarVector[i].value.void_v);
                break;
            case RETURN_ADDRESS:
                printf(" [%d] RETURN ADDRESS | val: %zu", i, this->localVarVector[i].value.returnAddress_value);
                break;
            case STRINGTYPE:
                printf(" [%d] STRINGTYPE: {%s} //",  i, this->localVarVector[i].value.string_value->c_str());
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
