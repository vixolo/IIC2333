#ifndef T3_cz_API_H
#define T3_cz_API_H
#include <stdio.h>
/* Method declarations */

typedef struct czFILE {
  char modo; // 'r' or 'w'
  char* name; //11 characters for the name. 10 letters plus "\0"
  char pointer[2]; //Pointer to index block of file which contains all info
} czFILE;

int little_hex_to_int(char ch);
int hex_to_int(char* hex);
int paint_bitmap(FILE * disk, int block_num);
int cz_exists(char* filename);
char *decimal_to_binary(int n);
int get_available_block_from_byte(char byte);
int get_next_available_block();
int get_next_dir_number();
czFILE* cz_open(char* filename, char mode);
void cz_ls();
int cz_mv(char* orig, char *dest);
int cz_rm(char* filename);
int cz_cp(char* orig, char *dest);

#endif
