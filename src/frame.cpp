#include "../include/frame.hpp"

Frame::Frame(int max_stack, int max_locals, uint16_t descriptor_index, std::vector<cp_info> *constant_pool_pt){
	this->max_stack = max_stack;
	this->max_locals = max_locals;
	this->constant_pool_pt = constant_pool_pt;
	this->pc = 0;
}
