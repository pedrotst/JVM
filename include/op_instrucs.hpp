#ifndef OPCODE
#define OPCODE

#include <map>

class InstructionTranslator{
public:
    std::map<uint8_t, std::string> op_mapa;
    InstructionTranslator();

};

#endif // OPCODE