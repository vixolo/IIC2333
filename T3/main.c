#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cz_API.h"


int main(int argc, char const *argv[]) {
  char nombre2[] = "aaaaa.gif";
  char nombre[] = "vixolo.mov";
  printf("%s\n", "estoy ejecutando");
  cz_ls();
  //printf("%i\n", cz_mv(nombre, nombre2));
  cz_rm(nombre2);
  //cz_cp(nombre, nombre2);
  return 0;
}
