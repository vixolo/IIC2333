#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * decimal_to_binary(int n){
  /* MÉTODO OBTENIDO DE https://www.programmingsimplified.com/c/source-code/\
  c-program-convert-decimal-to-binary */
   int c, d, count;
   char *pointer;
   count = 0;
   pointer = (char*)malloc(8+1);
   if (pointer == NULL)
      exit(EXIT_FAILURE);
   for (c = 7 ; c >= 0 ; c--){
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

char * text_to_binary(char * text){
  char * aux;
  char * aux2 = malloc(8);
  for (int i = 0; i < strlen(text); i++) {
    printf("%s\n",  decimal_to_binary((int)text[i]));
    strncpy(aux2, decimal_to_binary((int)text[i]), 8);
    strcat(aux, aux2);
    aux2 = malloc(8);
  }
  return text;
}

int toint(char * data, int offset){
  int pot = 1;
  int sum = 0;
  for (int i = 15+offset*8; i >= 8+offset*8; i--) {
    if(data[i] == '1'){
      sum = sum + pot;
    }
    pot = pot * 2;
  }
  return sum;
}

char * traducir(char* buffer, int n){
  char * aux = malloc(n+1);
  char * foo = malloc(1);
  for (int i = 1; i <= n; i++) {
    foo = toint(buffer, i);
    aux[i-1] = foo;
    printf("%c\n", foo);
  }
  aux[n] = '\0';
  return aux;
}



int main(){
  printf("%s\n", traducir("0000010000000110011000110110111101101110011011100110111101110010\0", 6));
  return 0;
}
