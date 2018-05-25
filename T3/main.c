#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cz_API.h"


int main(int argc, char const *argv[]) {
  printf("%s\n", "estoy ejecutando");
  printf("Next available block: %i\n", get_available_block_from_byte('\xFF'));
  //cz_open("lol.lol", 'r');
  return 0;
}
