#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include "cz_API.h"

int little_hex_to_int(char ch){
  if (ch <= 9){
    return ch;
  }
  if (ch == '\xA'){
    return 10;
  }
  if (ch == '\xB'){
    return 11;
  }
  if (ch == '\xC'){
    return 12;
  }
  if (ch == '\xD'){
    return 13;
  }
  if (ch == '\xE'){
    return 14;
  }
  if (ch == '\xF'){
    return 15;
  }
};

int hex_to_int(char* hex){
  int ret = 0;
  ret = ret + little_hex_to_int(hex[3]);
  ret = ret + 256*little_hex_to_int(hex[2]);
  ret = ret + 256*256*little_hex_to_int(hex[1]);
  ret = ret + 256*256*256*little_hex_to_int(hex[0]);
  return ret;
};

int paint_bitmap(FILE * disk, int block_num){

  int byte_position = block_num/8;
  int offset = block_num%8;
  int * eight_blocks = (int*)malloc(9);
  fseek(disk, 1024+byte_position, SEEK_SET);
  fread(eight_blocks, 1, 1, disk);
  char * bits;
  bits = decimal_to_binary(eight_blocks[0]);
  char digit_char = bits[offset];
  int digit = atoi(&digit_char);
  int new_digit = 1-digit;
  if (new_digit){
    bits[offset] = '1';
  } else {
    bits[offset] = '0';
  }
<<<<<<< HEAD


  printf("New bits %s\n", bits);
  char new_byte;
=======
  char new_byte = malloc(1);
>>>>>>> a474f336fb579dc4dfb153aa724bec0fe9a7c475
  new_byte = '\x00';
  for (int i = 7; i >= 1; i--) {
    if (bits[i] == '1'){
      new_byte += (char)pow(2,7-i);
    }
  }
  if (bits[0] == '1'){
    new_byte += '\x80';
  }
  fseek(disk, 1024+byte_position, SEEK_SET);
  fwrite(&new_byte, 1, 1, disk);
  return 0;
}

int cz_exists(char* filename){ //Search for the filename and tell if it's there
  FILE * disco = fopen("simdiskfilled.bin", "r");
  int max_file_storage = 64;
  for (int i = 0; i < max_file_storage; i++) {
    fseek(disco, 0+16*i, SEEK_SET);
    char validity[1];
    fread(validity, 1, 1, disco);
    if(validity[0]=='\x00'){
    continue;
    }
    else if(validity[0]=='\x01'){
      char name[12];
      name[11] = '\x00';
      fread(name, 1, 11, disco);
      if(!strcmp(name, filename)){
        fclose(disco);
        return 1;
      }
    } else{
      printf("There is a problem with the validity byte of entry #%i. Please\
      check the directory block of disk \"%s\" \n", i, "simdiskfilled.bin");
    }
  }
  printf("El archivo no existe%s\n", "");
  fclose(disco);
  return 0;
}

char * decimal_to_binary(int n){

  /* MÉTODO OBTENIDO DE https://www.programmingsimplified.com/c/source-code/\
  c-program-convert-decimal-to-binary */

   int c, d, count;
   char *pointer;

   count = 0;
   pointer = (char*)malloc(8+1);

   if (pointer == NULL)
      exit(EXIT_FAILURE);

   for (c = 7 ; c >= 0 ; c--)
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

int get_available_block_from_byte(char byte){
  char * binary = decimal_to_binary((int)(byte));
  for (int bit = 0; bit <8; bit++) {
    if (binary[bit] == '0'){
      free(binary);
      return bit;
    }
  }
  return 42;
}

int get_next_available_block(){
  FILE * disco = fopen("simdiskfilled.bin", "r");
  fseek(disco, 1024, SEEK_SET);
  char eight_blocks[1];
  for (int byte = 0; byte < 1024*8; byte++) {
    fread(eight_blocks, 1, 1, disco);
    if (*eight_blocks != '\xFF'){
      int bit = get_available_block_from_byte(*eight_blocks);
      return (byte)*8+bit;
    }
  }
  return 42;
}

int get_next_dir_number(){
  FILE * disco = fopen("simdiskfilled.bin", "r");
  int max_file_storage = 64;
  for (int index = 0; index < max_file_storage; index++) {
    fseek(disco, 16*index, SEEK_SET);
    char validity[1];
    fread(validity, 1, 1, disco);
    if(*validity=='\x00'){
      return index;
    }
  }
  return -1;
}

czFILE* cz_open(char* filename, char mode){

  czFILE * open_file = (czFILE *)malloc(sizeof(czFILE));
  strcpy(open_file->name, filename);
  open_file->mode = mode;
  if(mode=='r'){
    printf("%s\n", "modo lectura");
    if(!cz_exists(filename)){
      printf("%s doesn't exist. Can't read what's not there bruh.\n", filename);
      return NULL;
    } else {
      printf("%s\n", "El archivo existe");
      FILE * disco = fopen("simdiskfilled.bin", "r");
      int max_file_storage = 64;
      int index = 0;
      for (int i = 0; i < max_file_storage; i++) {
        fseek(disco, 16*i, SEEK_SET);
        char validity;
        fread(&validity, 1, 1, disco);
        if(validity=='\x00'){
          continue;
        }else if(validity=='\x01'){
          printf("Se encuentra entrada válida %s\n", "");
          char name[11];
          fread(name, 1, 11, disco);
          printf("Nombre leído %s\n", name);
          if(!strcmp(name, filename)){
            printf("Se encuentra archivo %s\n", name);
            printf("índice encontrado: %i\n", i);
            index = i;
            break;
          }
        }
      }
      int ptr1;
      int ptr2;

      printf("Indice busqueda: %i\n", index);
      fseek(disco, 16*index+15, SEEK_SET);
      fread(&ptr1, 1, 1, disco);
      printf("ultimo byte: %i\n", ptr1);
      fseek(disco, 16*index+14, SEEK_SET);
      fread(&ptr2, 1, 1, disco);
      printf("penultimo byte: %i\n", ptr2);

      // open_file->pointer = ptr;
      fclose(disco);

    }
  }
  /*
  } else if (mode == 'w'){
    if (cz_exists(filename)){
      return NULL;
    }else{
    */
      /*Initialize new file in disk and create czFILE*/
    //  int assigned_block = get_next_available_block(); //returns block number
    //  int assigned_dir_number = get_next_dir_number();
      /* TODO 1. Add to directory
              2. Paint Bitmap
              3. Initialize index block */
      /*char * directory = (char *)malloc(16);
      directory[0] = '\x01';
      strcpy(&directory[1], filename);
      directory[12] = '\x00';
      directory[13] = '\x00';
      FILE * disco = fopen("simdiskfilled.bin", "r");
      fseek(disco, assigned_dir_number*16, SEEK_SET);
      fwrite(directory, 1, 14, disco);
      if (assigned_block < pow(2, 15)) {
        int dir_number[2] = {0, assigned_dir_number};
        fwrite(dir_number, 1, 2, disco);
      } else{
        unsigned int dir_number = (unsigned int)assigned_dir_number;
        fwrite(&dir_number, 1, 1, disco);
      }
    }
  }else{
    printf("%s\n", "Invalid mode. Please use 'r' for read mode or 'w' for \
     write mode");
  }*/
  return open_file;
}

void cz_ls(){
  FILE * disco = fopen("simdiskfilled.bin", "r");
  int max_file_storage = 64;
  for (int i = 0; i < max_file_storage; i++) {
    fseek(disco, 0+16*i, SEEK_SET);
    char validity[1];
    fread(validity, 1, 1, disco);
    if(validity[0]=='\x01'){
      char name[12];
      fread(name, 1, 11, disco);
      printf("%s\n", name);
    }
  }
  fclose(disco);
  return;
}

int cz_mv(char* orig, char *dest){
  if(!cz_exists(orig) || cz_exists(dest)){
    return 1;
  }
  FILE * disco = fopen("simdiskfilled.bin", "r+");
  int max_file_storage = 64;
  for (int i = 0; i < max_file_storage; i++) {
    fseek(disco, 16*i, SEEK_SET);
    char validity[1];
    fread(validity, 1, 1, disco);
    if(validity[0]=='\x01'){
      char name[12];
      name[11] = '\x00';
      fread(name, 1, 11, disco);
      if(!strcmp(name, orig)){
          fseek(disco, 16*i+1, SEEK_SET);
          fwrite(dest, 1, 11, disco);
        break;
      }
    }
  }
  fclose(disco);
  return 0;
}

int cz_rm(char* filename){
  if(!cz_exists(filename)){
    return 1;
  }
  FILE * disco = fopen("simdiskfilled.bin", "r+");
  int max_file_storage = 64;
  char pointer[4];
  for (int i = 0; i < max_file_storage; i++) {
    fseek(disco, 16*i, SEEK_SET);
    char validity[1];
    fread(validity, 1, 1, disco);
    if(validity[0]=='\x01'){
      char name[12];
      name [11] = '\x00';
      fread(name, 1, 11, disco);
      if(!strcmp(name, filename)){
          fseek(disco, 16*i, SEEK_SET);
          validity[0] = '\x00';
          fwrite(validity, 1, 1, disco);
          fseek(disco, 16*i+12, SEEK_SET);
          fread(pointer, 4, 1, disco);
          break;
      }
    }
  }
  fseek(disco, hex_to_int(pointer), SEEK_SET); // Nos paramos en el bloque indice
  paint_bitmap(disco, hex_to_int(pointer)); //libero el bloque indice
  char size[4];
  fseek(disco, hex_to_int(pointer)*1024, SEEK_SET);
  fread(size, 1, 4, disco);
  fseek(disco, hex_to_int(pointer)*1024+12, SEEK_SET);
  for (int i = 0; (i < 252 && i < (hex_to_int(size)/1024)+1); i++){
    fread(pointer, 1, 4, disco); //guardo el siguiente bloque a liberar en el bitmap
    paint_bitmap(disco, hex_to_int(pointer));   // lo libero
    }
  if (hex_to_int(size)/1024 > 252){
    fread(pointer, 1, 4, disco); //guardo el puntero al bloque de direccionamiento indirecto
    paint_bitmap(disco, hex_to_int(pointer));   // lo libero
    fseek(disco, hex_to_int(pointer)*1024, SEEK_SET); //voy hacia el
    for (int i = 252; i < hex_to_int(size)/1024; ++i){
      fread(pointer, 1, 4, disco); //guardo el siguiente bloque a liberar en el bitmap
      paint_bitmap(disco, hex_to_int(pointer));   // lo libero
      }
    }
  fclose(disco);
  return 0;
}

int cz_cp(char* orig, char *dest){
  int bloque_disponible = get_next_dir_number();
  if(!cz_exists(orig) || cz_exists(dest) || bloque_disponible == -1){
    return 1;
  }
  /*
  char * size;
  char * created_at;
  char * modified_at;
  char * data;
  char * pointer;
  char * indirect;
  for (int i = 0; i < max_file_storage; i++) {
    fseek(disco, 16*i, SEEK_SET);
    char * validity;
    fread(validity, 1, 1, disco);
    if(*validity=='\x01'){
      char * name;
      fread(name, 1, 11, disco);
      fread(pointer, 1, 4, disco);
      if(!strcmp(name, orig)){
        fseek(disco, 0, pointer); //esta sintaxis no estoy seguro
        fread(&size, 4, 1, disco);
        fseek(disco, 16*i + 12, SEEK_SET);
        fread(data, 1, 1008, disco);
        fread(pointer, 1, 4, disco);
        fseek(disco, 0, pointer);   //esta sintaxis no estoy seguro
        fread(indirect, 1, 1024, disco);
        break;
      }
    }
  }
  Luego hay que escribir y marcar el directorio como usado
  eso falta. No estoy seguro si habia que veriicar que hubiesen dos espacios disponibles
  en disco para asi meter el bloque de direccionamiento indirecto.
fclose(disco);
*/

  return 0;
}
