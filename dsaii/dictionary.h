#ifndef DICTIONARY_H_INCLUDED
#define DICTIONARY_H_INCLUDED

#define SIZE 280000

typedef struct Entry{
    char id[15];
    char password[10];
    struct Entry * next;
}Entry;

int hashFunction(char * id, char * password);
void setTable(char * id, char * password, Entry table[]);

#endif // DICTIONARY_H_INCLUDED
