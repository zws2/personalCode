#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include "dictionary.h"

char* generatePassword();
void readFile();
void checkFile(FILE * fp, Entry table[]);

#endif // FILE_H_INCLUDED
