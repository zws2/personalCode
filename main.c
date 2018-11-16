#include "MonteChips.h"
#include "MonteTokenizer.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
//Zachary Snyder project 4 main file.
//Initiates both parts of the program.

int main(){


    srand(time(NULL));
    monteChips();
    monteTokenizer();

    return 0;
}
