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

/////////////////////////////////////////////////////////////////////////////
int ClassFile::findMain() {
	int i = 0;
	char *method_name = NULL;
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
		if (strcmp(method_name, "main") == 0){
			return i;
		}
	}
	// Só ocorre se não houver main
	return -1;
}

/////////////////////////////////////////////////////////////////////////////
char* ClassFile::getName(int name_index){
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
Code_attribute* ClassFile::getCodeAttr(method_info *method){
	Code_attribute *code_attr = NULL;
	int i = 0, name_index = 0;
    char *name = NULL;

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
