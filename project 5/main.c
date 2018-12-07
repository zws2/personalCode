//Zachary Snyder
//DSA P5
//Code to calculate the LCS value for different sequences of DNA.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define len 1001
#define matrixLen 20

void readFile(char *input, int x, int y);
void printLCS(int i, int j);
void LCS(int m, int n);
char findSimilarity(int m, int n);
void createSimilarityMatrix();
void printMatrix();

int z = 0, lineNumber = 0, C[len][len];
char X[len], Y[len], lcs[len], similarityMatrix[matrixLen][matrixLen];

void readFile(char *input, int x, int y)
{
    FILE *fp;
    char temp[len];
    fp = fopen(input, "r");
    if(fp == NULL)
        printf("The file does not exist.\n");
    else if(!strcmp(input, "twoStrings.txt")){
        fscanf(fp, " %s", X);
        fscanf(fp, " %s", Y);}
    else if(!strcmp(input, "multiStrings.txt")){
        int i, lines = 0;
        fscanf(fp, "%d", &lines);
        if(lines == 0){
            printf("Invalid file.\n");
            return;
        }
        for(i=1;i<lines; i++){
            if(i==x)
                fscanf(fp, " %s", X);
            else if(i==y)
                fscanf(fp, " %s", Y);
            else fscanf(fp, " %s", temp);
        }
    }
    else printf("Error processing input file.\n");
    fclose(fp);
}

void printLCS(int i, int j)
{
    if(i==0 || j==0)
        return;
    else if(X[i-1]==Y[j-1]){
        printLCS(i-1,j-1);
        lcs[z] = X[i-1];
        z++;}
    else if(C[i-1][j] >= C[i][j-1])
        printLCS(i-1,j);
    else printLCS(i,j-1);
}

void LCS(int m, int n)
{
    int i,j;
    for (i=0; i<=m; i++)
    {
        for (j=0; j<=n; j++)
        {
        if (i==0 || j==0)
            C[i][j] = 0;
        else if (X[i-1] == Y[j-1])
            C[i][j] = C[i-1][j-1]+1;
        else if(C[i-1][j] >= C[i][j-1])
            C[i][j] = C[i-1][j];
        else C[i][j] = C[i][j-1];
        }
    }
}

char findSimilarity(int m, int n)
{
    char similarity;
    float lenX, lenY, lenLCS, lenComp, lcsComp;
    lenX = strlen(X);
    lenY = strlen(Y);
    lenLCS = strlen(lcs);

    if(lenX >= lenY){
        lcsComp = lenLCS/lenX;
        lenComp = lenY/lenX;}
    else{
        lcsComp = lenLCS/lenY;
        lenComp = lenX/lenY;}

    if(lenComp >= .9 && lcsComp >= .9){

        similarity = 'H';}

    else if(lenComp >= .8 && lcsComp >= .8){

        similarity = 'M';}

    else if(lenComp >= .4 && lcsComp >= .5){

        similarity = 'L';}

    else similarity = 'D';

    //printf("lenComp: %f\nlcsComp: %f\nLCS: %d\n", lenComp, lcsComp, strlen(lcs));

    return similarity;
}

void createSimilarityMatrix()
{
    int m, n, i, j;
    for(i=0;i<matrixLen;i++){
        for(j=0;j<matrixLen;j++){
            if(i!=j){
                readFile("multiStrings.txt",i+1,j+1);
                m = strlen(X);
                n = strlen(Y);
                z = 0;
                memset(lcs,0,strlen(lcs));
                LCS(m, n);
                printLCS(m,n);
                similarityMatrix[i][j] = findSimilarity(m, n);
            }
        }
    }
}

void printMatrix()
{
    int i, j;
    printf("Similarity Matrix for the strings found in multiStrings.txt:\n");
    for(i=-1;i<matrixLen; i++){
        if(i!=-1)
            printf("%2d ", i+1);
        else printf(" ");
        for(j=0;j<matrixLen; j++){
            if(i==-1)
                printf(" %2d", j+1);
            else if(similarityMatrix[i][j] == 0)
                printf("-  ");
            else if(i>=j)
                printf("-  ");
            else printf("%c  ", similarityMatrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    //PART 1
    readFile("twoStrings.txt",0,0);
    int m = strlen(X), n = strlen(Y);
    LCS(m, n);
    printLCS(m,n);
    printf("The LCS string is: %s\n", lcs);

    //PART 2
    createSimilarityMatrix();
    printMatrix();

    return 0;
}
