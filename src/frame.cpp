#include "../include/frame.hpp"

Frame::Frame(){
    this->opStack = new op_stack();
    this->pc = 0;
}
