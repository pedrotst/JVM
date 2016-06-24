#include "../include/classFile.hpp"

using namespace std;

string ClassFile::getSource(){
    int index;
    for(int n=0; n < this->attributes_count; n++){
        attribute_info attributeElement = this->attributes[n];
        index = attributeElement.attribute_name_index_l;
        if(!strcmp(this->constant_pool[index-1].cp_union.constant_Utf8.bytes, "SourceFile")) {
            index = attributeElement.attribute_union.attr_SourceFile.sourcefile_index;
            return(this->getCpoolUtf8(index));
        }
    }
}

string ClassFile::getClassName(){
    string source_name = this->getSource();
    size_t found = source_name.find_first_of(".java");
    return source_name.substr(0, found);
}

string ClassFile::getCpoolUtf8(int index){
    if(this->constant_pool[index-1].tag != CONSTANT_Utf8)
        throw "Entrada nao eh utf8";
    return(this->constant_pool[index-1].cp_union.constant_Utf8.bytes);

}

map<string, string> ClassFile::getFieldsNamesTypes(){
    map<string, string> fbind;
    
    for(int i=0; i < this->fields_count; i++){
        string fieldName, fieldType;
        fieldName = this->getCpoolUtf8(this->fields[i].name_index);
        fieldType = this->getCpoolUtf8(this->fields[i].descriptor_index);
        fbind[fieldName] = fieldType;
    }
    return fbind;

}
