#include "../include/leitor.hpp"

int leitorClass_info(ClassFile *classF, FILE* arquivoJava){

    //Leitura 0xCAFEBABE e versão
    leituraHeader(classF, arquivoJava);

    //leitura constant pool
	leituraConstantPool(classF, arquivoJava);

    //Leitura accessThisSuper
    leituraAccessThisSuper(classF, arquivoJava);

    //leitura interfaces
    leituraInterfaces(classF, arquivoJava);

    //leitura fields
    leituraFields(classF, arquivoJava);

    //leitura dos methods
    leituraMethods(classF, arquivoJava);

    //leitura attributes
    leituraAttributes(classF, arquivoJava);

    fclose(arquivoJava);
    return 0;
}

FILE* abreArquivo(char *nomeArquivo){
    FILE *arquivoJava;
    if((arquivoJava = fopen(nomeArquivo, "rb")) == NULL){
        printf("Falha ao abrir arquivo -%s-. Encerrando...", nomeArquivo);
	}
	return arquivoJava;
}

FILE* abreArqLinhaComando(int argc, char** argv){
    FILE *arquivo;
    char str[FileNameLen];
    if( argc == 1){//não foi passado por linha de comando
        printf("Qual arquivo deseja abrir? ");
        scanf("%s", str);
    }else{
        strcpy(str, argv[1]);
    }
    if( !(arquivo = fopen(str, "rb"))) {
		printf("O arquivo .class nao pode ser aberto.\n");
		return NULL;
	}
	return arquivo;
}

int leituraHeader(ClassFile* classF, FILE *arquivoJava){
    	// Leitura do magicNumber
    	classF->magic = read_dword(arquivoJava);
        // Leitura do minor_version
        classF->minor_version = read_word(arquivoJava);
        // Leitura do major_version
        classF->major_version = read_word(arquivoJava);

        return 0;
}

int leituraConstantPool(ClassFile *classF, FILE *arquivoJava){
    	uint8_t tag = 0;
        cp_info cp_element;
    	//Le o tamanho da constant pool +1
    	classF->constant_pool_count = read_word(arquivoJava);
    	// Leitura da constant poll
        for (int n = 0; n < classF->constant_pool_count - 1; n++) {
            fread(&tag, sizeof(uint8_t), 1, arquivoJava);

            // Todas as entradas da constant pool são obtidas de forma parecida,
            // então há um exemplo no primeiro case e o resto segue uma mesma
            // lógica.
            switch (tag) {
            case CONSTANT_Class:
                cp_element.tag = CONSTANT_Class;
                cp_element.cp_union.constant_class.tag = CONSTANT_Class;
                cp_element.cp_union.constant_class.name_index =  read_word(arquivoJava);
                classF->constant_pool.push_back(cp_element);

                break;

            case CONSTANT_Fieldref:
                cp_element.tag = CONSTANT_Fieldref;
                cp_element.cp_union.constant_fieldref.tag = CONSTANT_Fieldref;
                cp_element.cp_union.constant_fieldref.class_index = read_word(arquivoJava);
                cp_element.cp_union.constant_fieldref.name_and_type_index = read_word(arquivoJava);
                classF->constant_pool.push_back(cp_element);

                break;

            case CONSTANT_Methodref:
                cp_element.tag = CONSTANT_Methodref;
                cp_element.cp_union.constant_methodref.tag = CONSTANT_Methodref;
                cp_element.cp_union.constant_methodref.class_index = read_word(arquivoJava);
                cp_element.cp_union.constant_methodref.name_and_type_index = read_word(arquivoJava);
                classF->constant_pool.push_back(cp_element);

                break;

            case CONSTANT_InterfaceMethodref:
                cp_element.tag = CONSTANT_InterfaceMethodref;
                cp_element.cp_union.constant_interfaceMethodref.tag = CONSTANT_InterfaceMethodref;
                cp_element.cp_union.constant_interfaceMethodref.class_index = read_word(arquivoJava);
                cp_element.cp_union.constant_interfaceMethodref.name_and_type_index = read_word(arquivoJava);
                classF->constant_pool.push_back(cp_element);

                break;

            case CONSTANT_String:
                cp_element.tag = CONSTANT_String;
                cp_element.cp_union.constant_string.tag = CONSTANT_String; \
                cp_element.cp_union.constant_string.string_index = read_word(arquivoJava);
                classF->constant_pool.push_back(cp_element);

                break;

            case CONSTANT_Integer:
                cp_element.tag = CONSTANT_Integer;
                cp_element.cp_union.constant_integer.tag = CONSTANT_Integer;
                cp_element.cp_union.constant_integer.bytes = read_dword(arquivoJava);
                classF->constant_pool.push_back(cp_element);

                break;

            case CONSTANT_Float:
                cp_element.tag = CONSTANT_Float;
                cp_element.cp_union.constant_float.tag = CONSTANT_Float;
                cp_element.cp_union.constant_float.bytes = read_dword(arquivoJava);
                classF->constant_pool.push_back(cp_element);

                break;

            case CONSTANT_Long:
                cp_element.tag = CONSTANT_Long;
                cp_element.cp_union.constant_long.tag = CONSTANT_Long;
                cp_element.cp_union.constant_long.high_bytes = read_dword(arquivoJava);
                cp_element.cp_union.constant_long.low_bytes = read_dword(arquivoJava);
                classF->constant_pool.push_back(cp_element);
                cp_element.tag = ZERO;
                classF->constant_pool.push_back(cp_element);
                n++;//

                break;

            case CONSTANT_Double:
                cp_element.tag = CONSTANT_Double;
                cp_element.cp_union.constant_double.tag = CONSTANT_Double;
                cp_element.cp_union.constant_double.high_bytes = read_dword(arquivoJava);
                cp_element.cp_union.constant_double.low_bytes = read_dword(arquivoJava);
                classF->constant_pool.push_back(cp_element);
                cp_element.tag = ZERO;
                classF->constant_pool.push_back(cp_element);
                n++; //

                break;

            case CONSTANT_NameAndType:
                cp_element.tag = CONSTANT_NameAndType;
                cp_element.cp_union.constant_nameAndType.tag = CONSTANT_NameAndType;
                cp_element.cp_union.constant_nameAndType.name_index = read_word(arquivoJava);
                cp_element.cp_union.constant_nameAndType.descriptor_index = read_word(arquivoJava);
                classF->constant_pool.push_back(cp_element);

                break;

            case CONSTANT_Utf8:
                cp_element.tag = CONSTANT_Utf8;
                cp_element.cp_union.constant_Utf8.tag = CONSTANT_Utf8;
                cp_element.cp_union.constant_Utf8.length = read_word(arquivoJava);
                //printf("length: %d\n", cp_element.cp_union.constant_Utf8.length);

                cp_element.cp_union.constant_Utf8.bytes = (char*)malloc((cp_element.cp_union.constant_Utf8.length + 1)*sizeof(char));
                for (int j = 0; j < cp_element.cp_union.constant_Utf8.length; j++) {
                    cp_element.cp_union.constant_Utf8.bytes[j] = read_byte(arquivoJava);
                }
                cp_element.cp_union.constant_Utf8.bytes[cp_element.cp_union.constant_Utf8.length] = '\0';
                //printf("na leitura: %s\n", cp_element.cp_union.constant_Utf8.bytes);
                classF->constant_pool.push_back(cp_element);

                break;

            case CONSTANT_MethodHandle:
                cp_element.tag = CONSTANT_MethodHandle;
                cp_element.cp_union.constant_methodHandle.tag = CONSTANT_MethodHandle;
                cp_element.cp_union.constant_methodHandle.reference_kind = read_byte(arquivoJava);
                cp_element.cp_union.constant_methodHandle.reference_index = read_word(arquivoJava);
                classF->constant_pool.push_back(cp_element);

                break;

            case CONSTANT_MethodType:
                cp_element.tag = CONSTANT_MethodType;
                cp_element.cp_union.constant_methodType.tag = CONSTANT_MethodType;
                cp_element.cp_union.constant_methodType.descriptor_index = read_word(arquivoJava);
                classF->constant_pool.push_back(cp_element);

                break;

            case CONSTANT_InvokeDynamic:
                cp_element.tag = CONSTANT_InvokeDynamic;
                cp_element.cp_union.constant_invokeDynamic.tag = CONSTANT_InvokeDynamic;
                cp_element.cp_union.constant_invokeDynamic.bootstrap_method_attr_index = read_word(arquivoJava);
                cp_element.cp_union.constant_invokeDynamic.name_and_type_index = read_word(arquivoJava);

                break;
            }
	}

      return 0;
}

int leituraAccessThisSuper(ClassFile *classF, FILE *arquivoJava){
    // Leitura do access flags
	classF->access_flags = read_word(arquivoJava);

	// Leitura de this class
	classF->this_class = read_word(arquivoJava);

	// Leitura de super class
	classF->super_class = read_word(arquivoJava);

      return 0;
}

int leituraInterfaces(ClassFile *classF, FILE *arquivoJava){
    classF->interfaces_count = read_word(arquivoJava);
	if(classF->interfaces_count != 0) {
		//Leitura das interfaces
		uint16_t twoBytes;
		for(int n = 0; n < classF->interfaces_count; n++) {
			fread(&twoBytes, sizeof(uint8_t), 2, arquivoJava);
			classF->interfaces.push_back(twoBytes);
		}
	}

      return 0;
}

int leituraFields(ClassFile *classF, FILE *arquivoJava){
    field_info field_element;
    attribute_info attribute_element;

    // Leitura de fields count
	classF->fields_count = read_word(arquivoJava);

	//Leitura dos fields
	for(int n = 0; n < classF->fields_count; n++) {
		field_element.access_flags = read_word(arquivoJava);
		field_element.name_index = read_word(arquivoJava);
		field_element.descriptor_index = read_word(arquivoJava);
		field_element.attributes_count = read_word(arquivoJava);
		for(int m = 0; m < field_element.attributes_count; m++) {
			attribute_element = read_attributes(arquivoJava, classF->constant_pool);
			field_element.attributes.push_back(attribute_element);
        }
        classF->fields.push_back(field_element);
    }

    return 0;
}

int leituraMethods(ClassFile *classF, FILE *arquivoJava){
    // Leitura do methods count
    classF->methods_count = read_word(arquivoJava);

    // Leitura de todos os methods
    for(int n = 0; n < classF->methods_count; n++) {
        classF->methods.push_back(read_method(arquivoJava, classF->constant_pool));
    }

    return 0;
}

int leituraAttributes(ClassFile *classF, FILE *arquivoJava){
    attribute_info attribute_element;

    // Leitura de attributes count
    classF->attributes_count = read_word(arquivoJava);

    // Leitura de todos attributes
    for(int n = 0; n < classF->attributes_count; n++) {
        // Lê um atributo
        attribute_element = read_attributes(arquivoJava, classF->constant_pool);

        //Insere o attribute no vetor de attributes do class file
        classF->attributes.push_back(attribute_element);
    }

    return 0;
}

char* getClassName(ClassFile *classF){
    char *className;
    //this_class é o indice que faz referencia a propria classe;
    //naquele indice encontramos o name_index (UTF8) da classe, i.e., o nome da classe
    //o vetor vai de 0-max; a constant pool de 1 a max+1;
    //o indice 1 a constant pool esta na posicao 0 do vetor; index-1
    int index = classF->constant_pool[classF->this_class-1].cp_union.constant_class.name_index;
    className = (char*) calloc(sizeof(char), classF->constant_pool[index-1].cp_union.constant_Utf8.length);
    strcpy(className, classF->constant_pool[index-1].cp_union.constant_Utf8.bytes);
    return className;
}
