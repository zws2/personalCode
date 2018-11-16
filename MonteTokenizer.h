#ifndef MONTETOKENIZER_H_INCLUDED
#define MONTETOKENIZER_H_INCLUDED

#define LEN 100

typedef struct Data{
    int days;
    int lines;
    char** dataMeasure;
    int frequency[LEN];
    char units[LEN];
} Data;//structure for storing specifications input from files

char* getMeasure(char * line, int which);
Data gather_input();
void monteTokenizer();

#endif // MONTETOKENIZER_H_INCLUDED
