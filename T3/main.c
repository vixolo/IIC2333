#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cz_API.h"


int main(int argc, char const *argv[]) {
<<<<<<< HEAD

  FILE * file = fopen("simdiskfilled.bin", "r+");
  paint_bitmap(file, 368);
  // printf("%s\n", file->name);
  // printf("%c\n", file->mode);
  // printf("%i\n", file->pointer);
=======
  char nombre2[] = "texto.txt";
  char nombre[] = "vixolo.mov";
  printf("%s\n", "estoy ejecutando");
  cz_ls();
  //printf("%i\n", cz_mv(nombre, nombre2));
  cz_rm(nombre2);
  //cz_cp(nombre, nombre2);
>>>>>>> a474f336fb579dc4dfb153aa724bec0fe9a7c475
  return 0;
}
