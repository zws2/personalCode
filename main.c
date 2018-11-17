#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <sys/stat.h>
//Zachary Snyder project 4 main file.
//Initiates both parts of the program.

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

typedef struct Specs{
    int batches;//Number of batches of items
    int items;//Number of items in each batch
    int bad_batches;//Percentage of batches containing bad items
    int bad_items;//Percentage of items that are bad in a bad batch
    int samples;//Items sampled from each batch
} Specs;//structure for storing specifications input from files

Specs gather_specs(int n_file);
void write_data(Specs c, int n_file);
Specs generate_data(Specs c, int n_file);
void analyze_data(Specs c, Specs s, int n_file);
void make_directory(const char* name);

//Zachary Snyder part 1 of project 4
//calculate error of monte carlo sim

Specs gather_specs(int n_file){

    Specs c;
    FILE *fp;
    char filename[PATH_MAX];

    sprintf(filename, "c%d.txt", n_file);
    fp = fopen(filename, "r");

    fscanf(fp, " %d\n", &c.batches);
    fscanf(fp, " %d\n", &c.items);
    fscanf(fp, " %d\n", &c.bad_batches);
    fscanf(fp, " %d\n", &c.bad_items);
    fscanf(fp, " %d\n", &c.samples);

    fclose(fp);

    return c;
}

void write_data(Specs c, int n_file){

    FILE *fp;
    char filename[PATH_MAX], cwd[PATH_MAX];
    int n_batches, n_items, is_bad = 0;

    sprintf(filename, "c%d", n_file);
    make_directory(filename);

    for(n_batches = 1; n_batches < c.batches; n_batches++){

        is_bad = 0;

        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            sprintf(filename, "%s/c%d/ds%d.txt", cwd, n_file, n_batches);
        }

        fp = fopen(filename, "w");

        if(((rand() % 100)+1) <= c.bad_batches)
            is_bad = 1;

        if(is_bad){
            for(n_items = 1; n_items < c.items; n_items++){
                if((rand() % 100)+1 <= c.bad_items && is_bad)
                    fprintf(fp, "b\n");
                else fprintf(fp, "g\n");
            }
        }

        else{
            for(n_items = 1; n_items < c.items; n_items++)
                fprintf(fp, "g\n");
        }

        fclose(fp);
    }
}

Specs generate_data(Specs c, int n_file){

    FILE *fp;
    char filename[PATH_MAX], cwd[PATH_MAX];
    char data_in;
    Specs d = {0};

    printf("Simulation %d:\n", n_file);
    printf("\tNumber of batches of items:\t\t\t%d\n", c.batches);
    printf("\tNumber of items in each batch:\t\t\t%d\n", c.items);
    printf("\tPercentage of batches containing bad items:\t%d%%\n", c.bad_batches);
    printf("\tPercentage of items that are bad in a bad set:\t%d%%\n", c.bad_items);
    printf("\tItems sampled from each set\t\t\t%d\n", c.samples);
    printf("\nGenerating data sets:\n");

    for(d.batches = 1; d.batches < c.batches; d.batches++){
        d.bad_items = 0;
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            sprintf(filename, "%s/c%d/ds%d.txt", cwd, n_file, d.batches);
        }
        fp = fopen(filename, "r");
        for(d.items = 1; d.items < c.items; d.items++){
            data_in = fgetc(fp);
            fgetc(fp);
            if((data_in == 'b')){
                d.bad_items++;
                d.samples++;
            }
        }
        fclose(fp);
        if(d.bad_items > 0){
            d.bad_batches++;

            printf("\tCreate bad set batch #%3d, totBad = %3d total = %3d badpct = %0.f\n", d.batches, d.bad_items, c.items, (float)d.bad_items/c.items*100);
        }
    }
    printf("\tTotal bad sets = %d\n\n", d.bad_batches);
    return d;
}

void analyze_data(Specs c, Specs s, int n_file){

    FILE *fp;
    char filename[PATH_MAX], cwd[PATH_MAX];
    char data_in;
    Specs d = {0};
    float base, failure_to_detect, batch_is_good, bad_batch_detected;

    printf("Analyzing data sets:\n");

    for(d.batches = 1; d.batches < c.batches; d.batches++){
        d.bad_items = 0;
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            sprintf(filename, "%s/c%d/ds%d.txt", cwd, n_file, d.batches);
        }
        fp = fopen(filename, "r");
        for(d.samples = 1; d.samples < c.samples; d.samples++){
            d.items = (rand() % c.items) + 1;
            data_in = fgetc(fp);
            fgetc(fp);
            if((data_in == 'b')){
                d.bad_items++;
            }
        }
        fclose(fp);
        if(d.bad_items > 0){
            d.bad_batches++;
            printf("\tBatch #%3d is bad.\n", d.batches);
        }
    }
    base = 1.0 - (float)c.bad_items/100;
    printf("Base = %.2f exponent = %d\n", base , c.samples);
    failure_to_detect = pow(base, c.samples);
    printf("P(failure to detect bad item) = %.3f\n", failure_to_detect);
    batch_is_good = 1.0 - failure_to_detect;
    printf("P(batch is good) = %.3f\n", batch_is_good);
    bad_batch_detected = (float)d.bad_batches/(s.bad_batches)*100;
    printf("Percentage of bad batches detected = %.2f%%\n", bad_batch_detected);
}

void make_directory(const char* name){

    #ifdef __linux__
        mkdir(name, 777);
    #else
        _mkdir(name);
    #endif
}

//Zachary Snyder part 2 of project 4
//calculate expected value from a range of data given frequency

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
    r.dataMeasure = (char**)malloc(r.lines * sizeof(char*));
    for (i = 0; i < r.lines; i++)
        r.dataMeasure[i] = malloc((LEN+1) * sizeof(char));
    for(i=0; i<r.lines; i++){
        fscanf(fp, " %s", r.dataMeasure[i]);
        fscanf(fp, " %d", &temp);
        r.frequency[i] = temp + r.frequency[i-1];
    }
    fscanf(fp, " %s", r.units);

    fclose(fp);

    return r;
}

//creates a random number over the interval min to max
int get_rand_interval(int min, int max)
{
    int r, range, x, limit;

    range = 1 + max - min;
    x = RAND_MAX / range;
    limit = x * range;

    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / x);
}

int main(){

    srand(time(NULL));

    Specs c1, c2, c3, c4;
    Specs d1, d2, d3, d4;

    //assign the specifications gathered from files
    //and places them in their associated structure
    c1 = gather_specs(1);
    c2 = gather_specs(2);
    c3 = gather_specs(3);
    c4 = gather_specs(4);

    //create the files holding the data
    write_data(c1, 1);
    write_data(c2, 2);
    write_data(c3, 3);
    write_data(c4, 4);

    //generate the data sets
    d1 = generate_data(c1, 1);
    analyze_data(c1, d1, 1);
    d2 = generate_data(c2, 2);
    analyze_data(c2, d2, 2);
    d3 = generate_data(c3, 3);
    analyze_data(c3, d3, 3);
    d4 = generate_data(c4, 4);
    analyze_data(c4, d4, 4);

    Data r = {0};
    int i, j;
    r.dataMeasure = malloc(r.lines * sizeof(char*));
    for (i = 0; i < r.lines; i++)
        r.dataMeasure[i] = malloc((LEN+1) * sizeof(char));

    char measure[LEN];
    char temp[LEN];
    char* val;
    int min, max;
    int chance;
    int selected = -1;
    float expected_value = 0;

    r = gather_input();


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
    printf("\nAnalytical model: 8500.0 Expected value is in the %s%s range.\n", r.dataMeasure[r.lines/2], r.units);
    printf("Simulation: %.1f. Expected value is in the %s%s range.\n", expected_value, r.dataMeasure[r.lines/2], r.units);


    return 0;
}
