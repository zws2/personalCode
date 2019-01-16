#include "main.h"

char* generatePassword(char *str){
    int size = 10;
    int i, key;
    char charset[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    if (size){
        --size;
        for (i = 0; i < size; i++){
            key = rand() % (int) (sizeof charset - 1);
            str[i] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}

void readFile(){

    FILE *fp1;
    FILE *fp2;
    FILE *fp3;
    //Entry table[SIZE];

    char id[15], password[10];
    int i=0, j=0, k=0;

    fp1 = fopen("lastNames.txt", "r");
    fp2 = fopen("rawData.dat", "w");
    fp3 = fopen("encryptedData.txt", "w");

    while(fscanf(fp1, " %s", id) == 1){
        if(j%4 == 0){
            k=0;
            while(id[k] != 0){
                id[k] = tolower(id[k]);
                k++;
            }
            fprintf(fp2, "%-15s %s\n", id, generatePassword(password));
            strcpy(password, encrypt(password));
            fprintf(fp3, "%-15s %s\n", id, generatePassword(password));
            //setTable(id,password,table);
        }
        else i++;
        j++;
    }

    printf("hello");
    //checkFile(fp2, table);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
}

void checkFile(FILE * fp, Entry table[]){

    int i;
    char id[15], password[10];
    for(i=0;i<=80000;i++){
        fscanf(fp, " %s %s", id, password);
        if(i%10000 == 0){
            if(strcmp(encrypt(password),table[i].password) == 0)
                printf("success");
            else printf("failure");
        }
    }
}
