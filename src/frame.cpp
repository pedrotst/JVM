#include "../include/frame.hpp"

<<<<<<< HEAD
Frame::Frame(int method_index, ClassFile *cf){
	this->method_index = method_index;
	this->cf = cf;
=======
Frame::Frame(){
    this->opStack = new op_stack();
    this->pc = 0;
>>>>>>> 4ae5775c31374efc6b2deface7b50b2bf9f61355
}
