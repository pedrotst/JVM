#ifndef _OPCODE_HPP
#define _OPCODE_HPP

#define NOP 0X00
#define  ACONST_NULL  0X01
#define  ICONST_M1  0X02
#define  ICONST_0  0X03
#define  ICONST_1  0X04
#define  ICONST_2  0X05
#define  ICONST_3  0X06
#define  ICONST_4  0X07
#define  ICONST_5  0X08
#define  LCONST_0  0X09
#define  LCONST_1  0X0A
#define  FCONST_0  0X0B
#define  FCONST_1  0X0C
#define  FCONST_2  0X0D
#define  DCONST_0  0X0E
#define  DCONST_1  0X0F
#define  BIPUSH  0X10
#define  SIPUSH  0X11
#define  LDC  0X12
#define  LDC_W  0X13
#define  LDC2_W  0X14
#define  ILOAD  0X15
#define  LLOAD  0X16
#define  FLOAD  0X17
#define  DLOAD  0X18
#define  ALOAD  0X19
#define  ILOAD_0  0X1A
#define  ILOAD_1  0X1B
#define  ILOAD_2  0X1C
#define  ILOAD_3  0X1D
#define  LLOAD_0  0X1E
#define  LLOAD_1  0X1F
#define  LLOAD_2  0X20
#define  LLOAD_3  0X21
#define  FLOAD_0  0X22
#define  FLOAD_1  0X23
#define  FLOAD_2  0X24
#define  FLOAD_3  0X25
#define  DLOAD_0  0X26
#define  DLOAD_1  0X27
#define  DLOAD_2  0X28
#define  DLOAD_3  0X29
#define  ALOAD_0  0X2A
#define  ALOAD_1  0X2B
#define  ALOAD_2  0X2C
#define  ALOAD_3  0X2D
#define  IALOAD  0X2E
#define  LALOAD  0X2F
#define  FALOAD  0X30
#define  DALOAD  0X31
#define  AALOAD  0X32
#define  BALOAD  0X33
#define  CALOAD  0X34
#define  SALOAD  0X35
#define  ISTORE  0X36
#define  LSTORE  0X37
#define  FSTORE  0X38
#define  DSTORE  0X39
#define  ASTORE  0X3A
#define  ISTORE_0  0X3B
#define  ISTORE_1  0X3C
#define  ISTORE_2  0X3D
#define  ISTORE_3  0X3E
#define  LSTORE_0  0X3F
#define  LSTORE_1  0X40
#define  LSTORE_2  0X41
#define  LSTORE_3  0X42
#define  FSTORE_0  0X43
#define  FSTORE_1  0X44
#define  FSTORE_2  0X45
#define  FSTORE_3  0X46
#define  DSTORE_0  0X47
#define  DSTORE_1  0X48
#define  DSTORE_2  0X49
#define  DSTORE_3  0X4A
#define ASTORE_0 0X4B
#define  ASTORE_1  0X4C
#define  ASTORE_2  0X4D
#define  ASTORE_3  0X4E
#define  IASTORE  0X4F
#define  LASTORE  0X50
#define  FASTORE  0X51
#define  DASTORE  0X52
#define  AASTORE  0X53
#define  BASTORE  0X54
#define  CASTORE  0X55
#define  SASTORE  0X56
#define  POP  0X57
#define  POP2  0X58
#define  DUP  0X59
#define  DUP_X1  0X5A
#define  DUP_X2  0X5B
#define  DUP2  0X5C
#define  DUP2_X1  0X5D
#define  DUP2_X2  0X5E
#define  SWAP  0X5F
#define  IADD  0X60
#define  LADD  0X61
#define  FADD  0X62
#define  DADD  0X63
#define  ISUB  0X64
#define  LSUB  0X65
#define  FSUB  0X66
#define  DSUB  0X67
#define  IMUL  0X68
#define  LMUL  0X69
#define  FMUL  0X6A
/** \file opcode.hpp
*   \brief este arquivo define os opcodes como sendo macros, assim podemos
* referenciar as opcodes de forma mais legivel
*
*/

#define  DMUL  0X6B
#define  IDIV  0X6C
#define  LDIV  0X6D
#define  FDIV  0X6E
#define  DDIV  0X6F
#define  IREM  0X70
#define  LREM  0X71
#define  FREM  0X72
#define  DREM  0X73
#define  INEG  0X74
#define  LNEG  0X75
#define  FNEG  0X76
#define  DNEG  0X77
#define  ISHL  0X78
#define  LSHL  0X79
#define  ISHR  0X7A
#define  LSHR  0X7B
#define  IUSHR  0X7C
#define  LUSHR  0X7D
#define  IAND  0X7E
#define  LAND  0X7F
#define  IOR  0X80
#define  LOR  0X81
#define  IXOR  0X82
#define  LXOR  0X83
#define  IINC  0X84
#define  I2L  0X85
#define  I2F  0X86
#define  I2D  0X87
#define  L2I  0X88
#define  L2F  0X89
#define  L2D  0X8A
#define  F2I  0X8B
#define  F2L  0X8C
#define  F2D  0X8D
#define  D2I  0X8E
#define  D2L  0X8F
#define  D2F  0X90
#define  I2B  0X91
#define  I2C  0X92
#define  I2S  0X93
#define  LCMP  0X94
#define  FCMPL  0X95
#define  FCMPG  0X96
#define  DCMPL  0X97
#define  DCMPG  0X98
#define  IFEQ  0X99
#define  IFNE  0X9A
#define  IFLT  0X9B
#define  IFGE  0X9C
#define  IFGT  0X9D
#define  IFLE  0X9E
#define  IF_ICMPEQ  0X9F
#define  IF_ICMPNE  0XA0
#define  IF_ICMPLT  0XA1
#define  IF_ICMPGE  0XA2
#define  IF_ICMPGT  0XA3
#define  IF_ICMPLE  0XA4
#define  IF_ACMPEQ  0XA5
#define  IF_ACMPNE  0XA6
#define  GOTO  0XA7
#define  JSR  0XA8
#define  RET  0XA9
#define  TABLESWITCH  0XAA
#define  LOOKUPSWITCH  0XAB
#define  IRETURN  0XAC
#define  LRETURN  0XAD
#define  FRETURN  0XAE
#define  DRETURN  0XAF
#define  ARETURN  0XB0
#define  RETURN  0XB1
#define  GETSTATIC  0XB2
#define  PUTSTATIC  0XB3
#define  GETFIELD  0XB4
#define  PUTFIELD  0XB5
#define  INVOKEVIRTUAL  0XB6
#define  INVOKESPECIAL  0XB7
#define  INVOKESTATIC  0XB8
#define  INVOKEINTERFACE  0XB9
#define  INVOKEDYNAMIC  0XBA
#define  NEW  0XBB
#define  NEWARRAY  0XBC
#define  ANEWARRAY  0XBD
#define  ARRAYLENGTH  0XBE
#define  ATHROW  0XBF
#define  CHECKCAST  0XC0
#define  INSTANCEOF  0XC1
#define  MONITORENTER  0XC2
#define  MONITOREXIT  0XC3
#define  WIDE  0XC4
#define  MULTIANEWARRAY  0XC5
#define  IFNULL  0XC6
#define  IFNONNULL  0XC7
#define  GOTO_W  0XC8
#define  JSR_W  0XC9
#define  BREAKPOINT  0XCA
#define  IMPDEP1  0XFE
#define  IMPDEP2  0XFF

#endif //  _OPCODE_HPP
