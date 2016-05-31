#include "../include/exibidor.hpp"
#include <math.h>
#include <map>
#include <iostream>
#include <iomanip>


void exibeClass(ClassFile classF){
    using namespace std;
    uint8_t tag;
    int n, i,j, e, s, aux;
    long l, m;
    float f;
    double d;

    printf("Magic: %X\n", classF.magic);
    printf("Minor version: %d\n", classF.minor_version);
    printf("Major version: %d\n", classF.major_version);
    printf("Constant Pool Count: %d\n", classF.constant_pool_count);
    cout << showbase << internal << setfill('0');
    cout << "Access Flag:" << hex << setw(6) << classF.access_flags;
    if((classF.access_flags & 0x0001) == 0x0001){
        cout << "[ACC_PUBLIC]";
    }if((classF.access_flags & 0x0010) == 0x0010){
        cout << "[ACC_FINAL]";
    }else if((classF.access_flags & 0x0020) == 0x0020){
        cout << "[ACC_SUPER]";
    }if((classF.access_flags & 0x0200) == 0x0200){
        cout << "[ACC_INTERFACE]";
    }else if((classF.access_flags & 0x0400) == 0x0400){
        cout << "[ACC_ABSTRACT]";
    }if((classF.access_flags & 0x1000) == 0x1000){
        cout << "[ACC_SYNTHETIC]";
    }else if((classF.access_flags & 0x2000) == 0x2000){
        cout << "[ACC_ANNOTATION]";
    }else if((classF.access_flags & 0x4000) == 0x4000){
        cout << "[ACC_ENUM]";
    }
    cout << "\n";

    for (j = 0, n = 0; j < classF.constant_pool_count - 1; n++, j++) {
        int index;
        cp_info_u cinfo = classF.constant_pool[n].cp_union;
        tag = classF.constant_pool[n].tag;
        printf("#%d = ",j+1);

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
                printf("#%d.#%d\t\t", cinfo.constant_fieldref.class_index, cinfo.constant_fieldref.name_and_type_index);
                index = cinfo.constant_fieldref.class_index;                                            //encontre a class
                index = classF.constant_pool[index-1].cp_union.constant_class.name_index;               // encontre a string que a class referencia
                printf("// %s.", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);           // imprime a string
                index = cinfo.constant_fieldref.name_and_type_index;                                    //encontra a name and type
                index = classF.constant_pool[index-1].cp_union.constant_nameAndType.name_index;         // encontra o campo name
                printf("%s:", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes );              // imprime a string
                index = cinfo.constant_fieldref.name_and_type_index;                                    //encontra a name and type
                index = classF.constant_pool[index-1].cp_union.constant_nameAndType.descriptor_index;   // encontra o campo descriptor
                printf("%s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes );             // imprime a string
                break;

            case CONSTANT_Methodref:
                printf("Methodref\t\t");
                printf("#%d.#%d\t\t", cinfo.constant_methodref.class_index, cinfo.constant_methodref.name_and_type_index);
                index = cinfo.constant_methodref.class_index;                                            //encontre a class
                index = classF.constant_pool[index-1].cp_union.constant_class.name_index;               // encontre a string que a class referencia
                printf("// %s.", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);           // imprime a string
                index = cinfo.constant_methodref.name_and_type_index;                                    //encontra a name and type
                index = classF.constant_pool[index-1].cp_union.constant_nameAndType.name_index;         // encontra o campo name
                printf("%s:", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes );              // imprime a string
                index = cinfo.constant_methodref.name_and_type_index;                                    //encontra a name and type
                index = classF.constant_pool[index-1].cp_union.constant_nameAndType.descriptor_index;   // encontra o campo descriptor
                printf("%s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes );             // imprime a string
                break;
                

            case CONSTANT_InterfaceMethodref:
                printf("InterfaceMethodref\t\t");
                printf("#%d.#%d\t\t", cinfo.constant_interfaceMethodref.class_index, cinfo.constant_interfaceMethodref.name_and_type_index);
                index = cinfo.constant_interfaceMethodref.class_index;                                              //encontre a class
                index = classF.constant_pool[index-1].cp_union.constant_class.name_index;                           // encontre a string que a class referencia
                printf("// %s.", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);                       // imprime a string
                index = cinfo.constant_interfaceMethodref.name_and_type_index;                                      //encontra a name and type
                index = classF.constant_pool[index-1].cp_union.constant_nameAndType.name_index;                     // encontra o campo name
                printf("%s:", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes );                         // imprime a string
                index = cinfo.constant_interfaceMethodref.name_and_type_index;                                      //encontra a name and type
                index = classF.constant_pool[index-1].cp_union.constant_nameAndType.descriptor_index;               // encontra o campo descriptor
                printf("%s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes );                        // imprime a string
                break;

            case CONSTANT_String:
                printf("String\t\t");
                index = cinfo.constant_string.string_index;
                printf("#%d\t\t", index);
                printf("// %s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);
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
                printf("%ldl\n", l);
                j++; //ocupa 2 espaços na constant pool
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
                j++; // ocupa2 
                break;

            case CONSTANT_NameAndType:
                printf("NameAndType\t");
                printf("#%d.#%d\t\t", cinfo.constant_nameAndType.name_index, cinfo.constant_nameAndType.descriptor_index);
                index = cinfo.constant_nameAndType.name_index;
                printf("// %s:", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);
                index = cinfo.constant_nameAndType.descriptor_index;
                printf("%s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);


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
