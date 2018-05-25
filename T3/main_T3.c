#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./cz_API.h"


/*
char *decimal_to_binary(int n)
{
   int c, d, count;
   char *pointer;

   count = 0;
   pointer = (char*)malloc(8+1);

   if (pointer == NULL)
      exit(EXIT_FAILURE);

   for (c = 8 ; c >= 0 ; c--)
   {
      d = n >> c;

      if (d & 1)
         *(pointer+count) = 1 + '0';
      else
         *(pointer+count) = 0 + '0';

      count++;
   }
   *(pointer+count) = '\0';

   return  pointer;
}
*/

int main(int argc, char const *argv[]) {
   printf("%s\n", "estoy ejecutando");
   diskinit("simdiskfilled.bin");
   printf("Este existe %d\n", cz_exists("texto.txt"));
   cz_open("lol.lol", 'r');
  return 0;
}
