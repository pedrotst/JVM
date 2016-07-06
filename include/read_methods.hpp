#ifndef READ_METHODS_HPP_INCLUDED
#define READ_METHODS_HPP_INCLUDED

#include "structs.hpp"
#include "read_attributes.hpp"

/** \fn read_method
*   \brief le um metodo e empacota na method_info
*/
method_info read_method(FILE *fp, std::vector<cp_info> constant_pool);

#endif // READ_METHODS_HPP_INCLUDED
