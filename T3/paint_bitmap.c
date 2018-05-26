#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include "cz_API.h"


int main(int argc, char const *argv[]) {
  FILE * disk = fopen("simdiskformat.bin", "r+");
  paint_bitmap(disk, 15);
  return 0;
}
