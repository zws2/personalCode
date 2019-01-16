#include "main.h"
char * encrypt(char * password){
    char key[] = "jones";
    int size = 9, i;
    int temp;
    for(i=0; i<size; i++){
        temp = password[i] + key[i%sizeof(key)]-96;
        if(temp >= 123 && temp <= 123+9){
            temp -= 75;
        }
        else if(temp >= 133){
            temp -= 36;
        }
        else if(temp >= 58 && temp <=96){
            temp += 39;
        }
        password[i] = temp;
    }
    return password;
}
