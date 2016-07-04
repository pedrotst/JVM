#include "../include/interpreter_op_code.hpp"

int interpreter_op_code(uint8_t opcode) {
      int n = 0;

      switch (opcode) {
            case (INVOKEINTERFACE):

            case (INVOKEDYNAMIC):

            case (GOTO_W):

            case (JSR_W):
                  return 4;

            // case (TABLESWITCH):

            // case (LOOKUPSWITCH):

            case (MULTIANEWARRAY):
                  return 3;

            // case (WIDE):

            case (ANEWARRAY):

            case (CHECKCAST):

            case (GETFIELD):

            case (GETSTATIC):

            case (INSTANCEOF):

            case (INVOKESPECIAL):

            case (INVOKESTATIC):

            case (INVOKEVIRTUAL):

            case (LDC2_W):

            case (LDC_W):

            case (NEW):
                  printf("NeW\n");

            case (PUTFIELD):

            case (PUTSTATIC):

            case (IINC):

            case (SIPUSH):

            case (GOTO):

            case (IF_ACMPEQ):

            case (IF_ACMPNE):

            case (IF_ICMPEQ):

            case (IF_ICMPGE):

            case (IF_ICMPGT):

            case (IF_ICMPLE):

            case (IF_ICMPLT):

            case (IF_ICMPNE):

            case (IFEQ):

            case (IFGE):

            case (IFGT):

            case (IFLE):

            case (IFLT):

            case (IFNE):

            case (IFNONNULL):

            case (IFNULL):

            case (JSR):
                  return 2;

            case (ALOAD):

            case (ASTORE):

            case (DLOAD):

            case (DSTORE):

            case (FLOAD):

            case (FSTORE):

            case (ILOAD):

            case (ISTORE):

            case (LDC):

            case (LLOAD):

            case (LSTORE):

            case (RET):

            case (BIPUSH):

            case (NEWARRAY):
                  return 1;

            default:
                  return 0;
      }
}
