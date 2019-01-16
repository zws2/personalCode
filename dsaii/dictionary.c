#include "main.h"

int hashFunction(char * id, char * password){
    return atoi(id)%SIZE;
}

void setTable(char * id, char * password, Entry table[]){
    Entry head;
    int address = hashFunction(id,password);
    while(head.next == NULL){
        head.next = table[SIZE].next;
    }
    strcpy(table[address].id, id);
    strcpy(table[address].password, password);

}
