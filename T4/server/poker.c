#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include "poker.h"

char * ordenar_cartas(char * cards){
  char * cartas_ordenadas;
  int count = 0;
  for (int j = 0; j < 10; j += 2) {
    if(cards[j] == '1'){
      cartas_ordenadas[8-count*2] = cards[j];
      cartas_ordenadas[9-count*2] = cards[j+1];
      count += 1;
    }
  }
  for (int i = 13+48; i < 2+48; i--) {
    for (int j = 0; j <10; j +=2){
      if(atoi(cards[j]) == i){
        cartas_ordenadas[8-count*2] = cards[j];
        cartas_ordenadas[9-count*2] = cards[j+1];
        count += 1;
      }
    }
  }
  return cartas_ordenadas;
}

bool sucesor(char carta_1, char carta_2){
  if (atoi(carta_1) + 1 == atoi(carta_2) || atoi(carta_1) - 12 == atoi(carta_2)){
    return 1;
  }
  return 0;
}

int escala(char * cards){
  char * cartas = malloc(10);
  int aux = 0;
  cartas = ordenar_cartas(cartas);
  if(sucesor(cartas[0], cartas[2]) && sucesor(cartas[2], cartas[4]) &&
     sucesor(cartas[4], cartas[6]) && sucesor(cartas[6], cartas[8])){
       aux = (int)cartas[8];
       free(cartas);
       return aux;
     }
  free(cartas);
  return aux;
}

bool color(char * cards){
 char * cartas = malloc(10);
 cartas = ordenar_cartas(cards);
 if(cartas[1] == cartas[3] && cartas[3] == cartas[5] &&
    cartas[5] == cartas[7] && cartas[7] == cartas[9]){
      free(cartas);
      return 1;
    }
    free(cartas);
 return 0;
}

int* pokar(char * cards, int * ret){
  char * cartas = malloc(10);
  cartas = ordenar_cartas(cards);
  if(cartas[0] == cartas[2] && cartas[2] == cartas[4] && cartas[4] == cartas[6]){
    ret[0] = (int)cartas[4];
    ret[1] = (int)cartas[8];
    }
  else if(cartas[2] == cartas[4] && cartas[4] == cartas[6] && cartas[6] == cartas[8]){
    ret[0] = (int)cartas[4];
    ret[1] = (int)cartas[0];
    }
  else{
    ret[0] = 0;
    ret[1] = 0;
  }
  free(cartas);
  return ret;
}

int* full(char * cards, int * ret){
  char * cartas = malloc(10);
  cartas = ordenar_cartas(cards);
  if(cartas[0] == cartas[2] && cartas[2] == cartas[4] && cartas[6] == cartas[8]){
    ret[0] = (int)cartas[4];
    ret[1] = (int)cartas[8];
    }
  else if(cartas[0] == cartas[2] && cartas[4] == cartas[6] && cartas[6] == cartas[8]){
    ret[0] = (int)cartas[8];
    ret[1] = (int)cartas[4];
    }
  else{
    ret[0] = 0;
    ret[1] = 0;
  }
  free(cartas);
  return ret;
}

int* trio(char * cards, int * ret){
  char * cartas = malloc(10);
  cartas = ordenar_cartas(cards);
  if(cartas[0] == cartas[2] && cartas[2] == cartas[4]){
    ret[0] = (int)cartas[4];
    ret[1] = (int)cartas[8];
    ret[2] = (int)cartas[6];
    }
  else if(cartas[2] == cartas[4] && cartas[4] == cartas[6]){
    ret[0] = (int)cartas[4];
    ret[1] = (int)cartas[8];
    ret[2] = (int)cartas[0];
    }
  else if(cartas[4] == cartas[6] && cartas[6] == cartas[8]){
    ret[0] = (int)cartas[4];
    ret[1] = (int)cartas[2];
    ret[2] = (int)cartas[0];
    }
  else{
    ret[0] = 0;
    ret[1] = 0;
    ret[2] = 0;
  }
  free(cartas);
  return ret;
}

int* dos_pares(char * cards, int * ret){
  char * cartas = malloc(10);
  cartas = ordenar_cartas(cards);
  if(cartas[0] == cartas[2] && cartas[4] == cartas[6]){
    ret[0] = (int)cartas[4];
    ret[1] = (int)cartas[2];
    ret[2] = (int)cartas[8];
    }
  else if(cartas[2] == cartas[4] && cartas[6] == cartas[8]){
    ret[0] = (int)cartas[8];
    ret[1] = (int)cartas[4];
    ret[2] = (int)cartas[0];
    }
  else if(cartas[0] == cartas[2] && cartas[6] == cartas[8]){
    ret[0] = (int)cartas[8];
    ret[1] = (int)cartas[2];
    ret[2] = (int)cartas[4];
    }
  else{
    ret[0] = 0;
    ret[1] = 0;
    ret[2] = 0;
  }
  free(cartas);
  return ret;
}

int* par(char * cards, int * ret){
  char * cartas = malloc(10);
  cartas = ordenar_cartas(cards);
  if(cartas[0] == cartas[2]){
    ret[0] = (int)cartas[0];
    ret[1] = (int)cartas[8];
    ret[2] = (int)cartas[6];
    ret[3] = (int)cartas[4];
    }
  else if(cartas[2] == cartas[4]){
    ret[0] = (int)cartas[2];
    ret[1] = (int)cartas[8];
    ret[2] = (int)cartas[6];
    ret[3] = (int)cartas[0];
    }
  else if(cartas[4] == cartas[6]){
    ret[0] = (int)cartas[4];
    ret[1] = (int)cartas[8];
    ret[2] = (int)cartas[2];
    ret[3] = (int)cartas[0];
    }
  else if(cartas[6] == cartas[8]){
    ret[0] = (int)cartas[6];
    ret[1] = (int)cartas[4];
    ret[2] = (int)cartas[2];
    ret[3] = (int)cartas[0];
    }
  else{
    ret[0] = 0;
    ret[1] = 0;
    ret[2] = 0;
    ret[3] = 0;
  }
  free(cartas);
  return ret;
}

int obtener_puntaje(char * cards){
  int stack = 0;
  int * int_aux = malloc(4*sizeof(int));
  int * ret_aux = malloc(4*sizeof(int));
  char * char_aux = malloc(5);
  if(escala(cards) == (int)'1' && color(cards)){ //Escala real
    stack = log(100000000000000000000000000*escala(cards));
  }
  else if(escala(cards) && color(cards)){ //Escala de color
    stack = log(1000000000000000000000000*escala(cards));
  }
  else if(*pokar(cards, ret_aux)){ //Poker
    int_aux = pokar(cards, ret_aux);
    stack = log(10000000000000000000000*int_aux[0] + int_aux[1]);
  }
  else if(*full(cards, ret_aux)){ //Full
    int_aux = full(cards, ret_aux);
    stack = log(100000000000000000000*int_aux[0] + 1000000000000000000*int_aux[1]);
  }
  else if(color(cards)){ //Color
    char_aux = ordenar_cartas(cards);
    stack = log(1000000000000000000*char_aux[4] + 10000000000000000*char_aux[3] +
            100000000000000*char_aux[2] + 1000000000000*char_aux[1] +
            10000000000*char_aux[0]);
  }
  else if(escala(cards)){ //Escala
    stack = log(10000000000000000*escala(cards));
  }
  else if(*trio(cards, ret_aux)){ //Trio
    int_aux = trio(cards, ret_aux);
    stack = log(100000000000000*int_aux[0] + 1000000000000*int_aux[1] +
            10000000000*int_aux[2]);
  }
  else if(*dos_pares(cards, ret_aux)){ //Dos Pares
    int_aux = dos_pares(cards, ret_aux);
    stack = log(1000000000000*int_aux[0] + 10000000000*int_aux[1] +
            100000000*int_aux[2]);
  }
  else if(*par(cards, ret_aux)){ //Par
    int_aux = par(cards, ret_aux);
    stack = log(10000000000*int_aux[0] + 100000000*int_aux[1] + 1000000*int_aux[2] +
            10000*int_aux[3]);
  }
  else{
    char_aux = ordenar_cartas(cards);
    stack = log(100000000*char_aux[4] + 1000000*char_aux[3] + 10000*char_aux[2] +
            100*char_aux[1] + char_aux[0]);
  }
  free(int_aux);
  free(char_aux);
  free(ret_aux);
  return stack;
}

int ganador(char * cards_j1, char * cards_j2){
  if (obtener_puntaje(cards_j1) > obtener_puntaje(cards_j2)){
    return 1;
  }
  return 2;
}

int * crear_mazo(int * deck){
  for (int j = 1; j < 5; j ++) {
    for (int i = 1; i < 14; i++){
      deck[(i+(j-1)*13)*3 - 3] = i;
      deck[(i+(j-1)*13)*3 - 2] = j;
      deck[(i+(j-1)*13)*3 - 1] = 0;
    }
  }
  return deck;
}

int * robar_carta(int * deck, int * ret){
  bool used = true;
  int randy;
  time_t t;
  srand((unsigned) time(&t));
  while (used) {
    randy = rand() % 52;
    used = deck[randy*3 + 2];
  }
  ret[0] = deck[randy*3];
  ret[1] = deck[randy*3 + 1];
  deck[randy*3 + 2] = 1;
  return ret;
}
/*
int main(){
  int * ret = malloc(2*sizeof(int));
  int * mazo = malloc(3*52*sizeof(int));
  int * foo_bar = malloc(8);
  crear_mazo(mazo);
  for (int i = 0; i < 52*3; i+=3) {
    printf("%i %i %i\n", mazo[i], mazo[i+1], mazo[i+2]);
  }
  printf("\n", 'c');
  for(int k=0; k<10;k++){
    foo_bar = robar_carta(mazo, ret);
    printf("%i %i\n", foo_bar[0], foo_bar[1]);
  }
  printf("\n", 'c');

  for (int i = 0; i < 52*3; i+=3) {
    printf("%i %i %i\n", mazo[i], mazo[i+1], mazo[i+2]);
  }
  free(mazo);
  free(ret);
  //free(foo_bar);
  return 0;
}*/
