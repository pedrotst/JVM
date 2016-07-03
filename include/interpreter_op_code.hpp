#ifndef _INTERPRETER_OP_CODE_HPP
#define _INTERPRETER_OP_CODE_HPP

#include <stdint.h>
#include <stdio.h>
#include "../include/opcode.hpp"
#include "../include/frame.hpp"

int interpreter_code(std::vector<Frame> *jStack/*, heap*/);

#endif //  _INTERPRETER_OP_CODE_HPP
