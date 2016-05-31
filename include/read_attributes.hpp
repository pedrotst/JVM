#ifndef _READ_ATTRIBUTES
#define _READ_ATTRIBUTES

#include <stdlib.h>
#include <stdio.h>
#include "../include/structs.hpp"
#include "../include/attributes.hpp"
#include "../include/read_bytes.hpp"

attribute_info read_attributes(FILE *fp, std::vector<cp_info> constant_pool);

#endif // _READ_ATTRIBUTES
