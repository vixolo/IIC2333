#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#include <string.h>

char * ordenar_cartas(char * cards);
bool sucesor(char carta_1, char carta_2);
int escala(char * cards);
bool color(char * cards);
int* pokar(char * cards, int * ret);
int* full(char * cards, int * ret);
int* trio(char * cards, int * ret);
int* dos_pares(char * cards, int * ret);
int* par(char * cards, int * ret);
int obtener_puntaje(char * cards);
int ganador(char * cards_j1, char * cards_j2);
int * robar_carta(int * deck, int * ret);
