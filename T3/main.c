#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cz_API.h"


int main(int argc, char const *argv[]) {

  FILE * file = fopen("simdiskfilled.bin", "r+");
  paint_bitmap(file, 368);
  // printf("%s\n", file->name);
  // printf("%c\n", file->mode);
  // printf("%i\n", file->pointer);
  return 0;
}
