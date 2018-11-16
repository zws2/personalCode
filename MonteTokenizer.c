#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "MonteTokenizer.h"

//Zachary Snyder part 2 of project 4

char* getMeasure(char * line, int which)
{
  char *token;
  char *search = "-:";
   token = strtok(line, search);
  if (which==1)
    return token;
  else
  {
    token = strtok(NULL, search);
    return token;
  }
}

Data gather_input()
{
    Data r = {0};
    FILE *fp;
    int temp;
    fp = fopen("readings.txt", "r");
    int i;
    r.frequency[-1] = 0;

    fscanf(fp, " %d\n", &r.days);
    fscanf(fp, " %d\n", &r.lines);
    r.dataMeasure = malloc(r.lines * sizeof(char*));
    for (int i = 0; i < r.lines; i++)
        r.dataMeasure[i] = malloc((LEN+1) * sizeof(char));
    for(i=0; i<r.lines; i++){
        fscanf(fp, " %s", r.dataMeasure[i]);
        fscanf(fp, " %d", &temp);
        r.frequency[i] = temp + r.frequency[i-1];
    }

    fclose(fp);

    return r;
}

int get_rand_interval(int min, int max)
{
    int r;
    int range = 1 + max - min;
    int x = RAND_MAX / range;
    int limit = x * range;
    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / x);
}

void monteTokenizer()
{
    Data r = {0};
    int i, j;
    r.dataMeasure = malloc(r.lines * sizeof(char*));
    for (int i = 0; i < r.lines; i++)
        r.dataMeasure[i] = malloc((LEN+1) * sizeof(char));

    char measure[LEN];
    char temp[LEN];
    char* val;
    int min, max;
    int chance;
    int selected = -1;
    float expected_value = 0;

    r = gather_input(r);


    for(j = 0; j < r.days; j++){

        chance = rand() % r.days;
        for(i = 0; i < r.lines; i++){
            if(chance <= r.frequency[i]){
                selected = i;
            }
            strcpy(measure, r.dataMeasure[selected]);
            strcpy(temp, measure);
            val = getMeasure(temp,1);
            min = atoi(val);
            strcpy(temp, measure);
            val = getMeasure(temp,2);
            max = atoi(val);

            expected_value += get_rand_interval(min, max);
        }
    }
    expected_value /= (float)r.days;
    printf("\nAnalytical model: 8500.0 Expected value is in the 8000-12000ml range.\n");
    printf("Simulation: %.1f. Expected value is in the 8000-12000ml range.\n", expected_value);
}


