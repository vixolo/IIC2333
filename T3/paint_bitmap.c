#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include "cz_API.h"

int paint_bitmap(FILE * disk, int block_num){

  int byte_position = block_num/8;
  printf("Byte: %i\n", byte_position);
  int offset = block_num%8;
  printf("Offset: %i\n", offset);


  int * eight_blocks = (int*)malloc(9);
  fseek(disk, 1024+byte_position, SEEK_SET);
  fread(eight_blocks, 1, 1, disk);
  printf("eight_blocks: %x\n", eight_blocks[0]);
  char * bits;
  bits = decimal_to_binary(eight_blocks[0]);
  printf("old bits: %s\n", bits);
  char digit_char = bits[offset];
  int digit = atoi(&digit_char);
  printf("digit: %i\n", digit);
  int new_digit = 1-digit;
  printf("new digit: %i\n", new_digit);
  if (new_digit){
    bits[offset] = '1';
  } else {
    bits[offset] = '0';
  }
  printf("new bits: %s\n", bits);

  int new_byte;

  for (int i = 7; i >= 0; i--) {
    if (bits[i] == '1'){
      new_byte+= pow(2,7-i);
    }
  }
  printf("new byte: %x\n", new_byte);
  fseek(disk, 1024+byte_position, SEEK_SET);
  fwrite(&new_byte, 4, 1, disk);
  return 0;
}


int main(int argc, char const *argv[]) {
  FILE * disk = fopen("simdiskformat.bin", "r+");
  paint_bitmap(disk, 15);
  return 0;
}
