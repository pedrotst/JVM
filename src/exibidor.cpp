#include "../include/exibidor.hpp"
using namespace std;
map<uint8_t, string> op_mapa = {
    {0X00 , "NOP"},
    {0X01 , "ACONST_NULL"},
    {0X02 , "ICONST_M1"},
    {0X03 , "ICONST_0"},
    {0X04 , "ICONST_1"},
    {0X05 , "ICONST_2"},
    {0X06 , "ICONST_3"},
    {0X07 , "ICONST_4"},
    {0X08 , "ICONST_5"},
    {0X09 , "LCONST_0"},
    {0X0A , "LCONST_1"},
    {0X0B , "FCONST_0"},
    {0X0C , "FCONST_1"},
    {0X0D , "FCONST_2"},
    {0X0E , "DCONST_0"},
    {0X0F , "DCONST_1"},
    {0X10 , "BIPUSH"},
    {0X11 , "SIPUSH"},
    {0X12 , "LDC"},
    {0X13 , "LDC_W"},
    {0X14 , "LDC2_W"},
    {0X15 , "ILOAD"},
    {0X16 , "LLOAD"},
    {0X17 , "FLOAD"},
    {0X18 , "DLOAD"},
    {0X19 , "ALOAD"},
    {0X1A , "ILOAD_0"},
    {0X1B , "ILOAD_1"},
    {0X1C , "ILOAD_2"},
    {0X1D , "ILOAD_3"},
    {0X1E , "LLOAD_0"},
    {0X1F , "LLOAD_1"},
    {0X20 , "LLOAD_2"},
    {0X21 , "LLOAD_3"},
    {0X22 , "FLOAD_0"},
    {0X23 , "FLOAD_1"},
    {0X24 , "FLOAD_2"},
    {0X25 , "FLOAD_3"},
    {0X26 , "DLOAD_0"},
    {0X27 , "DLOAD_1"},
    {0X28 , "DLOAD_2"},
    {0X29 , "DLOAD_3"},
    {0X2A , "ALOAD_0"},
    {0X2B , "ALOAD_1"},
    {0X2C , "ALOAD_2"},
    {0X2D , "ALOAD_3"},
    {0X2E , "IALOAD"},
    {0X2F , "LALOAD"},
    {0X30 , "FALOAD"},
    {0X31 , "DALOAD"},
    {0X32 , "AALOAD"},
    {0X33 , "BALOAD"},
    {0X34 , "CALOAD"},
    {0X35 , "SALOAD"},
    {0X36 , "ISTORE"},
    {0X37 , "LSTORE"},
    {0X38 , "FSTORE"},
    {0X39 , "DSTORE"},
    {0X3A , "ASTORE"},
    {0X3B , "ISTORE_0"},
    {0X3C , "ISTORE_1"},
    {0X3D , "ISTORE_2"},
    {0X3E , "ISTORE_3"},
    {0X3F , "LSTORE_0"},
    {0X40 , "LSTORE_1"},
    {0X41 , "LSTORE_2"},
    {0X42 , "LSTORE_3"},
    {0X43 , "FSTORE_0"},
    {0X44 , "FSTORE_1"},
    {0X45 , "FSTORE_2"},
    {0X46 , "FSTORE_3"},
    {0X47 , "DSTORE_0"},
    {0X48 , "DSTORE_1"},
    {0X49 , "DSTORE_2"},
    {0X4A , "DSTORE_3"},
    {0X4B , "ASTORE_0"},
    {0X4C , "ASTORE_1"},
    {0X4D , "ASTORE_2"},
    {0X4E , "ASTORE_3"},
    {0X4F , "IASTORE"},
    {0X50 , "LASTORE"},
    {0X51 , "FASTORE"},
    {0X52 , "DASTORE"},
    {0X53 , "AASTORE"},
    {0X54 , "BASTORE"},
    {0X55 , "CASTORE"},
    {0X56 , "SASTORE"},
    {0X57 , "POP"},
    {0X58 , "POP2"},
    {0X59 , "DUP"},
    {0X5A , "DUP_X1"},
    {0X5B , "DUP_X2"},
    {0X5C , "DUP2"},
    {0X5D , "DUP2_X1"},
    {0X5E , "DUP2_X2"},
    {0X5F , "SWAP"},
    {0X60 , "IADD"},
    {0X61 , "LADD"},
    {0X62 , "FADD"},
    {0X63 , "DADD"},
    {0X64 , "ISUB"},
    {0X65 , "LSUB"},
    {0X66 , "FSUB"},
    {0X67 , "DSUB"},
    {0X68 , "IMUL"},
    {0X69 , "LMUL"},
    {0X6A , "FMUL"},
    {0X6B , "DMUL"},
    {0X6C , "IDIv"},
    {0X6D , "LDIv"},
    {0X6E , "FDIv"},
    {0X6F , "DDIv"},
    {0X70 , "IREM"},
    {0X71 , "LREM"},
    {0X72 , "FREM"},
    {0X73 , "DREM"},
    {0X74 , "INEG"},
    {0X75 , "LNEG"},
    {0X76 , "FNEG"},
    {0X77 , "DNEG"},
    {0X78 , "ISHL"},
    {0X79 , "LSHL"},
    {0X7A , "ISHR"},
    {0X7B , "LSHR"},
    {0X7C , "IUSHR"},
    {0X7D , "LUSHR"},
    {0X7E , "IAND"},
    {0X7F , "LAND"},
    {0X80 , "IOR"},
    {0X81 , "LOR"},
    {0X82 , "IXOR"},
    {0X83 , "LXOR"},
    {0X84 , "IINC"},
    {0X85 , "I2L"},
    {0X86 , "I2F"},
    {0X87 , "I2D"},
    {0X88 , "L2I"},
    {0X89 , "L2F"},
    {0X8A , "L2D"},
    {0X8B , "F2I"},
    {0X8C , "F2L"},
    {0X8D , "F2D"},
    {0X8E , "D2I"},
    {0X8F , "D2L"},
    {0X90 , "D2F"},
    {0X91 , "I2B"},
    {0X92 , "I2C"},
    {0X93 , "I2S"},
    {0X94 , "LCMP"},
    {0X95 , "FCMPL"},
    {0X96 , "FCMPG"},
    {0X97 , "DCMPL"},
    {0X98 , "DCMPG"},
    {0X99 , "IFEQ"},
    {0X9A , "IFNE"},
    {0X9B , "IFLT"},
    {0X9C , "IFGE"},
    {0X9D , "IFGT"},
    {0X9E , "IFLE"},
    {0X9F , "IF_ICMPEQ"},
    {0XA0 , "IF_ICMPNE"},
    {0XA1 , "IF_ICMPLT"},
    {0XA2 , "IF_ICMPGE"},
    {0XA3 , "IF_ICMPGT"},
    {0XA4 , "IF_ICMPLE"},
    {0XA5 , "IF_ACMPEQ"},
    {0XA6 , "IF_ACMPNE"},
    {0XA7 , "GOTO"},
    {0XA8 , "JSR"},
    {0XA9 , "RET"},
    {0XAA , "TABLESWITCH"},
    {0XAB , "LOOKUPSWITCH"},
    {0XAC , "IRETURN"},
    {0XAD , "LRETURN"},
    {0XAE , "FRETURN"},
    {0XAF , "DRETURN"},
    {0XB0 , "ARETURN"},
    {0XB1 , "RETURN"},
    {0XB2 , "GETSTATIC"},
    {0XB3 , "PUTSTATIC"},
    {0XB4 , "GETFIELD"},
    {0XB5 , "PUTFIELD"},
    {0XB6 , "INVOKEVIRTUAL"},
    {0XB7 , "INVOKESPECIAL"},
    {0XB8 , "INVOKESTATIC"},
    {0XB9 , "INVOKEINTERFACE"},
    {0XBA , "INVOKEDYNAMIC"},
    {0XBB , "NEW"},
    {0XBC , "NEWARRAY"},
    {0XBD , "ANEWARRAY"},
    {0XBE , "ARRAYLENGTH"},
    {0XBF , "ATHROW"},
    {0XC0 , "CHECKCAST"},
    {0XC1 , "INSTANCEOF"},
    {0XC2 , "MONITORENTER"},
    {0XC3 , "MONITOREXIT"},
    {0XC4 , "WIDE"},
    {0XC5 , "MULTIANEWARRAY"},
    {0XC6 , "IFNULL"},
    {0XC7 , "IFNONNULL"},
    {0XC8 , "GOTO_W"},
    {0XC9 , "JSR_W"},
    {0XCA , "BREAKPOINT"},
    {0XFE , "IMPDEP1"},
    {0XFF , "IMPDEP2"},
    };

void print_access_flag(uint16_t access_flags){
    cout << showbase << internal << setfill('0');
    cout << "Access Flag: " << hex << setw(6) << access_flags;
    if((access_flags & 0x0001) == 0x0001){
        cout << "[ACC_PUBLIC]";
    }else if((access_flags & 0x0002) == 0x0002){
        cout << "[ACC_PRIVATE]";
    }else if((access_flags & 0x0004) == 0x0004){
        cout << "[ACC_PROTECTED]";
    }else if((access_flags & 0x0008) == 0x0008){
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
void exibeClass(ClassFile classF){
    uint8_t tag;
    int n, i,j, e, s, aux;
    int index;
    long l, m;
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
    printf("This Class: %d \t<%s>\n",classF.this_class, classF.constant_pool[index - 1].cp_union.constant_Utf8.bytes);
    index = classF.super_class; //indice da classe na cpool
    index = classF.constant_pool[index - 1].cp_union.constant_class.name_index; // indice do utf8
    printf("Super Class: %d <%s>\n", classF.super_class, classF.constant_pool[index - 1].cp_union.constant_Utf8.bytes);
    printf("Interface count: %d\n",classF.interfaces_count);
    printf("Fields count: %d\n", classF.fields_count);
    printf("Methods count: %d\n", classF.methods_count);
    printf("Attributes count: %d\n", classF.attributes_count);


    cout << endl << "Constant Pool: " << endl;
    for (j = 0, n = 0; j < classF.constant_pool_count - 1; n++, j++) {
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
                index = cinfo.constant_methodHandle.reference_kind;
                printf("#%d:#%d\t\t", cinfo.constant_methodHandle.reference_kind, cinfo.constant_methodHandle.reference_index);
                if (index <5){
                    if (index==1)
                        printf("// getField");
                    if (index==2)
                        printf("// getStatic");
                    if (index==3)
                        printf("// putField");
                    if (index==4)
                        printf("// putStatic");
                    index=cinfo.constant_methodHandle.reference_index;
                    index = classF.constant_pool[index-1].cp_union.constant_fieldref.class_index;           //encontreo fieldref
                    index = classF.constant_pool[index-1].cp_union.constant_class.name_index;               // encontre a class
                    printf("// %s.", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);           // imprime a string

                    index = index=cinfo.constant_methodHandle.reference_index;
                    index = classF.constant_pool[index-1].cp_union.constant_fieldref.class_index;           //encontreo fieldref                                 //encontra a name and type
                    index = classF.constant_pool[index-1].cp_union.constant_nameAndType.name_index;         // encontra o campo name
                    printf("%s:", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes );              // imprime a string

                    index = index=cinfo.constant_methodHandle.reference_index;
                    index = classF.constant_pool[index-1].cp_union.constant_fieldref.class_index;            //encontra o fieldRef
                    index = classF.constant_pool[index-1].cp_union.constant_nameAndType.descriptor_index;   // encontra o type
                    printf("%s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes );             //imprime o string

                    }
                else if ((index>4)&& (index<9)){
                    if (index==5)
                            printf("// invokeVirtual");
                    if (index==6)
                            printf("// invokeStatic");
                    if (index==7)
                            printf("// invokeSpecial");
                    if (index==8)
                            printf("// newInvokeSpecial");
                    index=cinfo.constant_methodHandle.reference_index;
                    index = classF.constant_pool[index-1].cp_union.constant_methodref.class_index;           //encontreo fieldref
                    index = classF.constant_pool[index-1].cp_union.constant_class.name_index;               // encontre a class
                    printf("// %s.", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);           // imprime a string

                    index = index=cinfo.constant_methodHandle.reference_index;
                    index = classF.constant_pool[index-1].cp_union.constant_methodref.class_index;           //encontreo fieldref                                 //encontra a name and type
                    index = classF.constant_pool[index-1].cp_union.constant_nameAndType.name_index;         // encontra o campo name
                    printf("%s:", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes );              // imprime a string

                    index = index=cinfo.constant_methodHandle.reference_index;
                    index = classF.constant_pool[index-1].cp_union.constant_methodref.class_index;            //encontra o fieldRef
                    index = classF.constant_pool[index-1].cp_union.constant_nameAndType.descriptor_index;   // encontra o type
                    printf("%s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes );             //imprime o string
                }

                else if (index==9){
                     printf("// invokeInterface");
                     index=cinfo.constant_methodHandle.reference_index;
                    index = classF.constant_pool[index-1].cp_union.constant_interfaceMethodref.class_index;           //encontreo fieldref
                    index = classF.constant_pool[index-1].cp_union.constant_class.name_index;               // encontre a class
                    printf("// %s.", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);           // imprime a string

                    index = index=cinfo.constant_methodHandle.reference_index;
                    index = classF.constant_pool[index-1].cp_union.constant_interfaceMethodref.class_index;           //encontreo fieldref                                 //encontra a name and type
                    index = classF.constant_pool[index-1].cp_union.constant_nameAndType.name_index;         // encontra o campo name
                    printf("%s:", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes );              // imprime a string

                    index = index=cinfo.constant_methodHandle.reference_index;
                    index = classF.constant_pool[index-1].cp_union.constant_interfaceMethodref.class_index;            //encontra o fieldRef
                    index = classF.constant_pool[index-1].cp_union.constant_nameAndType.descriptor_index;   // encontra o type
                    printf("%s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes );             //imprime o string
                }


                break;


            case CONSTANT_MethodType:
                printf("MethodType\t\t");
                index = cinfo.constant_methodType.descriptor_index;
                printf("#%d\t\t",index) ;
                printf("// %s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);
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
        printf("<%s>\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);
        index = classF.fields[n].descriptor_index;
        printf("Descriptor: cp_info#%d ", index);
        printf("<%s>\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);
        printf("Attributes Count: %d\n", classF.fields[n].attributes_count);
        cout << endl;
    }
    cout << "Methods: " << endl;
    printf("Methods Count: %d\n", classF.methods_count);
    for(n = 0; n< classF.methods_count; n++){
        printf("Method: %d\n", n+1);
        uint16_t access_flags = classF.methods[n].access_flags;
        index = classF.methods[n].name_index; //Name index
        printf("Name: #%d<%s>\n", index, classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);
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
        printf("Descritor: %s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);
        printf("Atribute count: %d\n", classF.methods[n].attributes_count);
        for(j=0; j < classF.methods[n].attributes_count; j++){
            int code_length;
            printf("\t Attribute number: %d\n", j + 1);
            index = classF.methods[n].attributes[j].attribute_name_index_l;
            printf("\t Attribute Name: %s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);
            printf("\t Attribute Length: %d\n", classF.methods[n].attributes[j].attribute_length_l);
            if(!strcmp(classF.constant_pool[index-1].cp_union.constant_Utf8.bytes, "Code")){
                printf("\t Max Stack: %d\n", classF.methods[n].attributes[j].attribute_union.attr_Code.max_stack);
                printf("\t Max Locals: %d\n", classF.methods[n].attributes[j].attribute_union.attr_Code.max_locals);
                code_length = classF.methods[n].attributes[j].attribute_union.attr_Code.code_length;
                printf("\t Code Length: %d\n", code_length);
                for(int k = 0; k < code_length; k++){
	            uint8_t opcode = classF.methods[n].attributes[j].attribute_union.attr_Code.code[k];

                    //printf("\t Code: %02x\n", opcode);
		      int arg_qnt = print_code(opcode);
                    cout << "\t"<< k << ":\t"<<  op_mapa[opcode] << "\t";
		    //printf("arg_qnt = %d\n", arg_qnt);
		    for(int u = 0 ; u < arg_qnt; u++){
			    printf(" #%d ",(uint8_t) classF.methods[n].attributes[j].attribute_union.attr_Code.code[k+u+1]);

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
        printf("Attribute name_index: #%d\t\t", index);
        printf(" %s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);
        printf("Attribute Length: %d\n", attributeElement.attribute_length_l);

        
        // Se o attribute for do tipo SourceFile
        if(!strcmp(classF.constant_pool[index-1].cp_union.constant_Utf8.bytes, "SourceFile")) {
            printf("Attribute: SourceFile\n");

            printf("attribute_name_index: #%d\n", attributeElement.attribute_union.attr_SourceFile.attribute_name_index);

            
            printf("attribute_length: %d\n", attributeElement.attribute_union.attr_SourceFile.attribute_length);

        
            printf("Sourcefile_index: #%d\t\t", attributeElement.attribute_union.attr_SourceFile.sourcefile_index);
            index = attributeElement.attribute_union.attr_SourceFile.sourcefile_index;
            printf(" %s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);
        
            }
              if(!strcmp(classF.constant_pool[index-1].cp_union.constant_Utf8.bytes, "InnerClasses")) {
                printf("Attribute: InnerClasses\n");
                printf("attribute_name_index:\n%d\n",attributeElement.attribute_union.attr_InnerClasses.attribute_name_index);

                  printf("attribute_length:\n%d\n",attributeElement.attribute_union.attr_InnerClasses.attribute_length);
                  printf("number of classes\n%d\n",attributeElement.attribute_union.attr_InnerClasses.number_of_classes);
                  
             /*     for (int n = 0; n < attributeElement.attribute_union.attr_InnerClasses.number_of_classes; n++) {
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
                        
                  }
            */
            }
             if(!strcmp(classF.constant_pool[index-1].cp_union.constant_Utf8.bytes, "Synthetic")) {
                  printf("Attribute: Synthetic\n");

                  
                  printf("attribute_name_index:\n%d\n", attributeElement.attribute_union.attr_Synthetic.attribute_name_index);
                  index = attributeElement.attribute_union.attr_Synthetic.attribute_name_index;
                  printf(" %s\n", classF.constant_pool[index-1].cp_union.constant_Utf8.bytes);
                  
                  printf("attribute_length:\n%d\n", attributeElement.attribute_union.attr_Synthetic.attribute_length);
            }
        }




}
