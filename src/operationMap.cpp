#include "../include/operationMap.hpp"

namespace OperationMap{
    std::map<uint8_t, std::string> op_mapa = {
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
        {0XB6 , "INvOKEvIRTUAL"},
        {0XB7 , "INvOKESPECIAL"},
        {0XB8 , "INvOKESTATIC"},
        {0XB9 , "INvOKEINTERFACE"},
        {0XBA , "INvOKEDYNAMIC"},
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

    std::string getOperation(uint8_t opcode){
        return(OperationMap::op_mapa[opcode]);
    }
}