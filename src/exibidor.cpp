#include "../include/exibidor.hpp"

void exibeClass(ClassFile classF){
    uint8_t tag;
    int n, i;
    printf("Magic: %X\n", classF.magic);
    printf("Minor version: %d\n", classF.minor_version);
    printf("Major version: %d\n", classF.major_version);
    printf("Constant Pool Count: %d\n", classF.constant_pool_count);



    for (n = 0; n < classF.constant_pool_count - 1; n++) {
        int index;
        cp_info_u cinfo = classF.constant_pool[n].cp_union;
        tag = classF.constant_pool[n].tag;
        printf("#%d = ",n+1);

        // Todas as entradas da constant pool são obtidas de forma parecida,
        // então há um exemplo no primeiro case e o resto segue uma mesma
        // lógica.
        switch (tag) {
            case CONSTANT_Class:
                printf("Class\t\t");
                index = cinfo.constant_class.name_index;
                printf("#%d\t\t", index);
                printf("// %s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);
                break;

            case CONSTANT_Fieldref:
                printf("Fieldref\t\t");
                printf("#%d.#%d\n", cinfo.constant_fieldref.class_index, cinfo.constant_fieldref.name_and_type_index);
                break;

            case CONSTANT_Methodref:
                printf("Methodref\t\t");
                printf("#%d.#%d\n", cinfo.constant_methodref.class_index, cinfo.constant_methodref.name_and_type_index);
                break;

            case CONSTANT_InterfaceMethodref:
                printf("InterfaceMethodref\t\t");
                printf("#%d.#%d\n", cinfo.constant_interfaceMethodref.class_index, cinfo.constant_interfaceMethodref.name_and_type_index);
                break;

            case CONSTANT_String:
                printf("String\t\t");
                printf("#%d\n", cinfo.constant_string.string_index);
                break;

            case CONSTANT_Integer:
                printf("Integer\t\t");
                printf("#%d\n", cinfo.constant_integer.bytes);
                break;

            case CONSTANT_Float:
                printf("Float\t\t");
                printf("#%d\n", cinfo.constant_float.bytes);
                break;

            case CONSTANT_Long:
                printf("Long\t\t");
                printf("#%d.#%d\n", cinfo.constant_long.high_bytes, cinfo.constant_long.low_bytes);
                break;

            case CONSTANT_Double:
                printf("Double\t\t");
                printf("#%d.#%d\n", cinfo.constant_double.high_bytes, cinfo.constant_double.low_bytes);
                break;

            case CONSTANT_NameAndType:
                printf("NameAndType\t");
                printf("#%d.#%d\n", cinfo.constant_nameAndType.name_index, cinfo.constant_nameAndType.descriptor_index);
                break;

            case CONSTANT_Utf8:
                printf("Utf8\t\t");
                printf("%s\n", cinfo.constant_Utf8.bytes); //Não tem '\0' no final por isso pode dar erro!
                break;

            case CONSTANT_MethodHandle:
                printf("MethodHandle\t\t");
                printf("#%d.#%d\n", cinfo.constant_methodHandle.reference_kind, cinfo.constant_methodHandle.reference_index);
                break;

            case CONSTANT_MethodType:
                printf("MethodType\t\t");
                printf("#%d\n", cinfo.constant_methodType.descriptor_index);
                break;

            case CONSTANT_InvokeDynamic:
                printf("InvokeDynamic\t\t");
                printf("#%d.#%d\n", cinfo.constant_invokeDynamic.bootstrap_method_attr_index, cinfo.constant_invokeDynamic.name_and_type_index);
                break;
        }
    }
}
