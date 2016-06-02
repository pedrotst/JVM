#ifndef LEITOR_HPP_INCLUDED
#define LEITOR_HPP_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string>
#include <cstring>

#include "../include/structs.hpp"
#include "../include/attributes.hpp"
#include "../include/little_to_big.hpp"
#include "../include/read_bytes.hpp"
#include "../include/read_attributes.hpp"
#include "../include/read_methods.hpp"
#define ByteCode "Puppy.class"
#define FileNameLen 30 //define o tamanho da string em abreArquivo

FILE* abreArquivo(int argc, char** argv);
int leituraHeader(ClassFile* classF, FILE *arquivoJava);
int leituraConstantPool(ClassFile *classF, FILE *arquivoJava);
int leituraAccessThisSuper(ClassFile *classF, FILE *arquivoJava);
int leituraInterfaces(ClassFile *classF, FILE *arquivoJava);
int leituraFields(ClassFile *classF, FILE *arquivoJava);
int leituraMethods(ClassFile *classF, FILE *arquivoJava);
int leituraAttributes(ClassFile *classF, FILE *arquivoJava);

#endif // LEITOR_HPP_INCLUDED
