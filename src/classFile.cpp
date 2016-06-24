#include "../include/classFile.hpp"


std::string ClassFile::getSource(){
    int index;
    for(int n=0; n < this->attributes_count; n++){
        attribute_info attributeElement = this->attributes[n];
        index = attributeElement.attribute_name_index_l;
        if(!strcmp(this->constant_pool[index-1].cp_union.constant_Utf8.bytes, "SourceFile")) {
            index = attributeElement.attribute_union.attr_SourceFile.sourcefile_index;
            return(this->constant_pool[index-1].cp_union.constant_Utf8.bytes);
        }
    }
}

std::string ClassFile::getClassName(){
    std::string source_name = this->getSource();
    std::size_t found = source_name.find_first_of(".java");
    return source_name.substr(0, found);
}

std::vector<field_info> ClassFile::getFields(){


}
