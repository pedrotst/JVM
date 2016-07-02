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
    return NULL;
}

string ClassFile::getClassName(){
    string source_name = this->getSource();
    size_t found = source_name.find_first_of(".java");
    return source_name.substr(0, found);
}

string ClassFile::getCpoolClass(int index){
    int cname_index = this->constant_pool[index-1].cp_union.constant_class.name_index;
    //if(this->constant_pool[index-1].tag != CONSTANT_Class)
       // throw "Entrada nao eh uma classe";

    return(this->getCpoolUtf8(cname_index));
}

string ClassFile::getCpoolMethod(int index, string &invoking_class, string &method_name, string &descriptor){
    int class_index = this->constant_pool[index-1].cp_union.constant_methodref.class_index;
    int type_index = this->constant_pool[index-1].cp_union.constant_methodref.name_and_type_index;
    //printf("/////%d %d///", class_index, type_index);
    if(this->constant_pool[index-1].tag != CONSTANT_Methodref);
        //throw "Entrada nao eh uma classe";
    invoking_class = this->getCpoolClass(class_index);
    this->getCpoolNameAndType(type_index, method_name, descriptor);
    return(this->getCpoolClass(class_index)+"."+this->getCpoolNameAndType(type_index, method_name, descriptor));
}
string ClassFile::getCpoolNameAndType(int index, string &method_name, string &descriptor){
    int name_index = this->constant_pool[index-1].cp_union.constant_nameAndType.name_index;
    int descriptor_index= this->constant_pool[index-1].cp_union.constant_nameAndType.descriptor_index;
    if(this->constant_pool[index-1].tag != CONSTANT_NameAndType);
        //throw "Entrada nao eh uma name & type";
    method_name = this->getCpoolUtf8(name_index);
    descriptor = this->getCpoolUtf8(descriptor_index);
    return(this->getCpoolUtf8(name_index)+ ":"+ this->getCpoolUtf8(descriptor_index));
}

string ClassFile::getCpoolUtf8(int index){
    //if(this->constant_pool[index-1].tag != CONSTANT_Utf8)
        //throw "Entrada nao eh utf8";
    //string str(this->constant_pool[index-1].cp_union.constant_Utf8.bytes);
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

string ClassFile::getFieldName(int n){
    int name_type_index = this->constant_pool[n-1].cp_union.constant_fieldref.name_and_type_index;
    int name_index = this->constant_pool[name_type_index - 1].cp_union.constant_nameAndType.name_index;
    return this->getCpoolUtf8(name_index);
}
string ClassFile::getFieldType(int n){
    int name_type_index = this->constant_pool[n-1].cp_union.constant_fieldref.name_and_type_index;
    int type_index = this->constant_pool[name_type_index - 1].cp_union.constant_nameAndType.descriptor_index;
    return this->getCpoolUtf8(type_index);
}

/////////////////////////////////////////////////////////////////////////////
int ClassFile::findMethod(string method) {
	int i = 0;
	string method_name;
	method_info *method_pt = NULL;
    //printf("Em findMain():\n");
	// Para cada método
	for (i = 0; i < this->methods_count; i++) {
		// Pega o método
		method_pt = &this->methods[i];
		// Pega o nome do método
		method_name = this->getName(method_pt->name_index);
		//printf("Nome do metodo checado: %s\n", method_name);
		// Retorna index do método, se for o main
		//printf("Resultado de strcmp(): %d\n", strcmp(method_name, "main"));
		if (method_name.compare(method) == 0){
			return i;
		}
	}
	// Só ocorre se não houver main
	return -1;
}

/////////////////////////////////////////////////////////////////////////////
string ClassFile::getName(int name_index){
	char *name = NULL;

	// Checa se a entrada da constant_pool apontada pelo index é uma string.
	// Se não for retorna NULL.
      if (this->constant_pool[name_index-1].tag != CONSTANT_Utf8) {
            printf("O index (da constant_pool) passado não aponta para uma string.\n");
            return NULL;
      }
	// Obtém a string da constant_pool.
	name = this->constant_pool[name_index-1].cp_union.constant_Utf8.bytes;

	return name;
}

/////////////////////////////////////////////////////////////////////////////
Code_attribute* ClassFile::getCodeAttr(int m_index){
	Code_attribute *code_attr = NULL;
	int i = 0, name_index = 0;
    char *name = NULL;
    method_info *method = &this->methods[m_index];
	for(i = 0; i < method->attributes_count; i++) {
		// Obtém o name_index do atributo i
		name_index = method->attributes[i].attribute_name_index_l;
		// Resolve o nome do atributo na constant_pool
		name = this->constant_pool[name_index-1].cp_union.constant_Utf8.bytes;
            // Checa se o nome do atributo é "Code".
            if (!strcmp(name, "Code")) {
			code_attr = &method->attributes[i].attribute_union.attr_Code;
			return code_attr;
		}
	}

	return NULL;
}


bool ClassFile::isStaticMethod(int method_index){
    if(this->methods[method_index].access_flags && 0x0008 == 0x0008)
        return true;
    return false;

}
