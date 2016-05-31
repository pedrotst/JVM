#include "../include/read_attributes.hpp"

method_info read_method(FILE *fp, std::vector<cp_info> constant_pool){
    method_info novoMethod;
    novoMethod.access_flags = read_word(fp);
    printf("access_flags: %x\n", novoMethod.access_flags);

    novoMethod.name_index = read_word(fp);
    printf("name_index: %x\n", novoMethod.name_index);

    novoMethod.descriptor_index = read_word(fp);
    printf("descriptor_index: %x\n", novoMethod.descriptor_index);

    novoMethod.attributes_count = read_word(fp);
    printf("attributes_count: %x\n", novoMethod.attributes_count);
    for(int i = 0; i < novoMethod.attributes_count; i++){
        novoMethod.attributes.push_back( read_attributes(fp, constant_pool) );
    }
    return novoMethod;
}
