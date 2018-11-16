#ifndef MONTECHIPS_H_INCLUDED
#define MONTECHIPS_H_INCLUDED

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
void monteChips();

#endif // MONTECHIPS_H_INCLUDED
