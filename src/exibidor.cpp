#include "../include/exibidor.hpp"
using namespace std;


void print_access_flag(uint16_t access_flags){
    cout << showbase << internal << setfill('0');
    cout << "Access Flag: " << hex << setw(6) << access_flags;
    if((access_flags & 0x0001) == 0x0001){
        cout << "[ACC_PUBLIC]";
    }else if((access_flags & 0x0002) == 0x0002){
        cout << "[ACC_PRIVATE]";
    }else if((access_flags & 0x0004) == 0x0004){
        cout << "[ACC_PROTECTED]";
    }if((access_flags & 0x0008) == 0x0008){
        cout << "[ACC_STATIC]";
    }if((access_flags & 0x0010) == 0x0010){
        cout << "[ACC_FINAL]";
    }else if((access_flags & 0x0020) == 0x0020){
        cout << "[ACC_SUPER]";
    }else if((access_flags & 0x0040) == 0x0040){
        cout << "[ACC_VOLATILE]";
    }else if((access_flags & 0x0080) == 0x0080){
        cout << "[ACC_TRANSIENT]";
    }if((access_flags & 0x0200) == 0x0200){
        cout << "[ACC_INTERFACE]";
    }else if((access_flags & 0x0400) == 0x0400){
        cout << "[ACC_ABSTRACT]";
    }if((access_flags & 0x1000) == 0x1000){
        cout << "[ACC_SYNTHETIC]";
    }else if((access_flags & 0x2000) == 0x2000){
        cout << "[ACC_ANNOTATION]";
    }else if((access_flags & 0x4000) == 0x4000){
        cout << "[ACC_ENUM]";
    }
    cout << "\n";
}

void print_comment(vector<cp_info_s> c, int n){
    cp_tag tag = c[n].tag;
    int index;
    cp_info_u cinfo = c[n].cp_union;

    switch(tag){
        case CONSTANT_String:
        case CONSTANT_Class:
            index = cinfo.constant_class.name_index;
            print_comment(c, index - 1);
            break;
        case CONSTANT_Fieldref:
            index = cinfo.constant_fieldref.class_index;                                            //encontre a class
            print_comment(c, index - 1);
            printf(".");
            index = cinfo.constant_fieldref.name_and_type_index;                                    //encontra a name and type
            print_comment(c, index - 1);
            break;
        case CONSTANT_Methodref:
            index = cinfo.constant_methodref.class_index;                                            //encontre a class
            print_comment(c, index-1);
            printf(".");
            index = cinfo.constant_methodref.name_and_type_index;                                    //encontra a name and type
            print_comment(c, index-1);
            break;
        case CONSTANT_NameAndType:
            index = cinfo.constant_nameAndType.name_index;
            print_comment(c, index-1);
            printf(":");
            index = cinfo.constant_nameAndType.descriptor_index;
            print_comment(c, index-1);
            break;
        case CONSTANT_Utf8:
            printf("%s", c[n].cp_union.constant_Utf8.bytes);
            break;
        default:
            break;

    }

}


void exibeClass(ClassFile classF){
    uint8_t tag;
    int n, j, e, s, aux;
    int index;
    uint64_t l, m;
    float f;
    double d;

    printf("General Information: \n");
    printf("Magic: %X\n", classF.magic);
    printf("Minor version: %d\n", classF.minor_version);
    printf("Major version: %d\n", classF.major_version);
    printf("Constant Pool Count: %d\n", classF.constant_pool_count);
    print_access_flag(classF.access_flags);


    index = classF.this_class; //indice da classe na cpool
    index = classF.constant_pool[index - 1].cp_union.constant_class.name_index; // indice do utf8
    printf("This Class: %d \t<%s>\n",classF.this_class, classF.getCpoolUtf8(index).c_str());
    index = classF.super_class; //indice da classe na cpool
    if(index != 0){
        index = classF.constant_pool[index - 1].cp_union.constant_class.name_index; // indice do utf8
        printf("Super Class: %d <%s>\n", classF.super_class, classF.getSuper().c_str());
    }
    printf("Interface count: %d\n",classF.interfaces_count);
    printf("Fields count: %d\n", classF.fields_count);
    printf("Methods count: %d\n", classF.methods_count);
    printf("Attributes count: %d\n", classF.attributes_count);


    cout << endl << "Constant Pool: " << endl;
    for (j = 0, n = 0; j < (int)classF.constant_pool_count - 1; n++, j++) {
        cp_info_u cinfo = classF.constant_pool[n].cp_union;
        tag = classF.constant_pool[n].tag;
        printf("#%d = ",j+1);

        // Todas as entradas da constant pool são obtidas de forma parecida,
        // então há um exemplo no primeiro case e o resto segue uma mesma
        // lógica.
        switch (tag) {
            case ZERO:
                printf("continuação numerica\n");
                break;

            case CONSTANT_Class:
                printf("Class\t\t");
                index = cinfo.constant_class.name_index;
                printf("#%d\t\t // ", index);
                print_comment(classF.constant_pool, n);
                printf("\n");
                break;

            case CONSTANT_Fieldref:
                printf("Fieldref\t\t");
                printf("#%d.#%d\t\t // ", cinfo.constant_fieldref.class_index, cinfo.constant_fieldref.name_and_type_index);
                print_comment(classF.constant_pool, n);
                printf("\n");
                break;

            case CONSTANT_Methodref:
                printf("Methodref\t\t");
                printf("#%d.#%d\t\t // ", cinfo.constant_methodref.class_index, cinfo.constant_methodref.name_and_type_index);
                print_comment(classF.constant_pool, n);
                printf("\n");
                break;


            case CONSTANT_InterfaceMethodref:
                printf("InterfaceMethodref\t\t");
                printf("#%d.#%d\t\t", cinfo.constant_interfaceMethodref.class_index, cinfo.constant_interfaceMethodref.name_and_type_index);
                index = cinfo.constant_interfaceMethodref.class_index;                                              //encontre a class
                index = classF.constant_pool[index-1].cp_union.constant_class.name_index;                           // encontre a string que a class referencia
                printf("// %s.", classF.getCpoolUtf8(index).c_str());                                              // imprime a string
                index = cinfo.constant_interfaceMethodref.name_and_type_index;                                      //encontra a name and type
                index = classF.constant_pool[index-1].cp_union.constant_nameAndType.name_index;                     // encontra o campo name
                printf("%s:", classF.getCpoolUtf8(index).c_str());                                                   // imprime a string
                index = cinfo.constant_interfaceMethodref.name_and_type_index;                                      //encontra a name and type
                index = classF.constant_pool[index-1].cp_union.constant_nameAndType.descriptor_index;               // encontra o campo descriptor
                printf("%s\n", classF.getCpoolUtf8(index).c_str());                                                         // imprime a string
                break;

            case CONSTANT_String:
                printf("String\t\t");
                index = cinfo.constant_string.string_index;
                printf("#%d\t\t", index);
                printf("// %s\n", classF.getCpoolUtf8(index).c_str());
                break;

            case CONSTANT_Integer:
                printf("Integer\t\t");
                printf("#%d\n", cinfo.constant_integer.bytes);
                break;

            case CONSTANT_Float:
                printf("Float\t\t");
                aux = cinfo.constant_float.bytes;
                s = ((aux >> 31) == 0) ? 1 : -1;
                e = ((aux >> 23) & 0xff);
                m = (e == 0) ?
                    (aux & 0x7fffff) << 1 :
                    (aux & 0x7fffff) | 0x800000;
                f = s*m*pow(2, (e-150));
                printf("#%gf\n", f);

                break;

            case CONSTANT_Long:
                printf("Long\t\t");
                l = cinfo.constant_long.high_bytes;
                l = l<<32;
                l = l + cinfo.constant_long.low_bytes;
                printf("%ldl\n", (long int) l);
                //j++; //ocupa 2 espaços na constant pool
                break;

            case CONSTANT_Double:
                printf("Double\t\t");
                l = cinfo.constant_double.high_bytes;
                l = l <<32;
                l = l +cinfo.constant_double.low_bytes;
                s = ((l >> 63) == 0) ? 1 : -1;
                e = (int)((l >> 52) & 0x7ffL);
                m = (e == 0) ?
                    (l & 0xfffffffffffffL) << 1 :
                    (l & 0xfffffffffffffL) | 0x10000000000000L;
                d = s*m*(pow(2, (e-1075)));
                printf("#%gd\n", d);
                //j++; // ocupa2
                break;

            case CONSTANT_NameAndType:
                printf("NameAndType\t");
                printf("#%d.#%d\t\t", cinfo.constant_nameAndType.name_index, cinfo.constant_nameAndType.descriptor_index);
                print_comment(classF.constant_pool, n);
                printf("\n");
                break;

            case CONSTANT_Utf8:
                printf("Utf8\t\t");
                printf("%s\n", cinfo.constant_Utf8.bytes);
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
    cout << endl << endl << "Fields: " << endl;
    for(n = 0; n < classF.fields_count; n++){
        printf("Field: %d\n", n + 1);
        print_access_flag(classF.fields[n].access_flags);
        index = classF.fields[n].name_index;
        printf("Name: cp_info#%d ", index);
        printf("<%s>\n", classF.getCpoolUtf8(index).c_str());
        index = classF.fields[n].descriptor_index;
        printf("Descriptor: cp_info#%d ", index);
        printf("<%s>\n", classF.getCpoolUtf8(index).c_str());
        printf("Attributes Count: %d\n", classF.fields[n].attributes_count);
        cout << endl;
    }
    printf("Methods_count: %d\n", classF.methods_count);
    cout << "Methods: " << endl;
    for(n = 0; n< classF.methods_count; n++){
        printf("Method: %d\n", n+1);
        uint16_t access_flags = classF.methods[n].access_flags;
        index = classF.methods[n].name_index; //Name index
        printf("Name: #%d<%s>\n", index, classF.getCpoolUtf8(index).c_str());
        cout << "Access Flag: "<< hex << setw(6) <<  access_flags;
        if((access_flags & 0x0001) == 0x0001){
            cout << "[ACC_PUBLIC]";
        }else if((access_flags & 0x0002) == 0x0002){
            cout << "[ACC_PRIVATE]";
        }else if((access_flags & 0x0004) == 0x0004){
            cout << "[ACC_PROTECTED]";
        }if((access_flags & 0x0008) == 0x0008){
            cout << "[ACC_STATIC]";
        }if((access_flags & 0x0010) == 0x0010){
            cout << "[ACC_FINAL]";
        }else if((access_flags & 0x0020) == 0x0020){
            cout << "[ACC_SYNCHRONIZED]";
        }else if((access_flags & 0x0040) == 0x0040){
            cout << "[ACC_BRIDGE]";
        }else if((access_flags & 0x0080) == 0x0080){
            cout << "[ACC_VARARGS]";
        }if((access_flags & 0x0100) == 0x0100){
            cout << "[ACC_NATIVE]";
        }else if((access_flags & 0x0400) == 0x0400){
            cout << "[ACC_ABSTRACT]";
        }else if((access_flags & 0x0800) == 0x0480){
            cout << "[ACC_STRICT]";
        }if((access_flags & 0x1000) == 0x1000){
            cout << "[ACC_SYNTHETIC]";
        }
        cout << endl;
        index = classF.methods[n].descriptor_index; //Descriptor index
        printf("Descritor: %s\n", classF.getCpoolUtf8(index).c_str());
        printf("Atribute count: %d\n", classF.methods[n].attributes_count);
        for(j=0; j < classF.methods[n].attributes_count; j++){
            int code_length;
            printf("\t Attribute number: %d\n", j + 1);
            index = classF.methods[n].attributes[j].attribute_name_index_l;
            printf("\t Attribute Name: %s\n", classF.getCpoolUtf8(index).c_str());
            printf("\t Attribute Length: %d\n", classF.methods[n].attributes[j].attribute_length_l);
            if(!strcmp(classF.getCpoolUtf8(index).c_str(), "Code")){
                printf("\t Max Stack: %d, ", classF.methods[n].attributes[j].attribute_union.attr_Code.max_stack);
                printf("\t Max Locals: %d, ", classF.methods[n].attributes[j].attribute_union.attr_Code.max_locals);
                code_length = classF.methods[n].attributes[j].attribute_union.attr_Code.code_length;
                printf("\t Code Length: %d\n", code_length);

                for(int k = 0; k < code_length; k++){
                    uint8_t opcode = classF.methods[n].attributes[j].attribute_union.attr_Code.code[k];

                    //printf("\t Code: %02x\n", opcode);
                    int arg_qnt = print_code(opcode);
                    cout << "\t"<< dec << k << ":\t"<<  OperationMap::getOperation((uint8_t)opcode) << "\t";
                    //printf("arg_qnt = %d\n", arg_qnt);
                    for(int u = 0 ; u < arg_qnt; u += (!(arg_qnt%2) + 1)){
                        uint16_t cp_ref;
                        if((arg_qnt%2) == 0)
                            cp_ref = (classF.methods[n].attributes[j].attribute_union.attr_Code.code[k+u+1] << 8) | classF.methods[n].attributes[j].attribute_union.attr_Code.code[k+u+2];
                        else
                            cp_ref = classF.methods[n].attributes[j].attribute_union.attr_Code.code[k+u+1];
                        printf(" #%d ",cp_ref);
                    }
                    if(arg_qnt > 0){
                        cout << "\t // ";
                    }
                    for(int u = 0 ; u < arg_qnt; u+= (!(arg_qnt%2) + 1)){
                        printf(" ");
                        uint16_t cp_ref;
                        if((arg_qnt%2) == 0)
                            cp_ref = (classF.methods[n].attributes[j].attribute_union.attr_Code.code[k+u+1] << 8) | classF.methods[n].attributes[j].attribute_union.attr_Code.code[k+u+2];
                        else
                            cp_ref = classF.methods[n].attributes[j].attribute_union.attr_Code.code[k+u+1];
                        print_comment(classF.constant_pool, cp_ref - 1);
                    }
                    cout << endl;
                    k += arg_qnt;
                }

            }
        }
        printf("\n");
    }

    printf("Attributes Count: %d\n", classF.attributes_count);

    for (n = 0; n < classF.attributes_count; n++){

        attribute_info attributeElement = classF.attributes[n];
        index = attributeElement.attribute_name_index_l;
        printf("Attribute Length: %d\n", attributeElement.attribute_length_l);


        // Se o attribute for do tipo SourceFile
        if(!strcmp(classF.getCpoolUtf8(index).c_str(), "SourceFile")) {
            printf("Attribute: SourceFile\n");

            printf("attribute_name_index: #%d\n", attributeElement.attribute_union.attr_SourceFile.attribute_name_index);


            printf("attribute_length: %d\n", attributeElement.attribute_union.attr_SourceFile.attribute_length);

            printf("Sourcefile_index: #%d\t\t//%s.java\n", attributeElement.attribute_union.attr_SourceFile.sourcefile_index, classF.getClassName().c_str());
            //index = attributeElement.attribute_union.attr_SourceFile.sourcefile_index;
            //cout << classF.getClassName() << endl;

        }
        if(!strcmp(classF.getCpoolUtf8(index).c_str(), "InnerClasses")) {
            printf("Attribute: InnerClasses\n");
            printf("attribute_name_index:\n%d\n",attributeElement.attribute_union.attr_InnerClasses.attribute_name_index);

            printf("attribute_length:\n%d\n",attributeElement.attribute_union.attr_InnerClasses.attribute_length);
            printf("number of classes\n%d\n",attributeElement.attribute_union.attr_InnerClasses.number_of_classes);

            /*for (int n = 0; n < attributeElement.attribute_union.attr_InnerClasses.number_of_classes; n++) {
                printf("inner_class_index:\n%d\t", classesElement.inner_class_info_index);
                index = classesElement.inner_class_info_index;
                printf(" %s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);
                printf("outer_class_index:\n%d\t", classesElement.outer_class_info_index) ; //class
                index = classesElement.outer_class_info_index;
                printf(" %s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);

                printf("inner_name_index:\n%d\t", classes_element.inner_name_index) ; //class
                index = classes_element.inner_name_index;
                printf(" %s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);

                print_access_flag(classesElement.inner_class_access_flags);

            }*/

        }
        if(!strcmp(classF.constant_pool[index-1].cp_union.constant_Utf8.bytes, "Synthetic")) {
            printf("Attribute: Synthetic\n");


            printf("attribute_name_index:\n%d\n", attributeElement.attribute_union.attr_Synthetic.attribute_name_index);
            index = attributeElement.attribute_union.attr_Synthetic.attribute_name_index;
            printf(" %s\n", classF.getCpoolUtf8(index).c_str());

            printf("attribute_length:\n%d\n", attributeElement.attribute_union.attr_Synthetic.attribute_length);
        }
    }




}
