#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>


char * diskname; 

void diskinit(char * disk_name){
    char * diskname = disk_name;
    return;
}

typedef struct czFILE {
  char modo; // 'r' or 'w'
  char* name; //11 characters for the name. 10 letters plus "\0"
  char pointer[2]; //Pointer to index block of file which contains all info
} czFILE;

int cz_exists(char* filename){ //Search for the filename and tell if it's there
  FILE * disco = fopen("simdiskfilled.bin", "r");
  int max_file_storage = 64;
  for (int i = 0; i < max_file_storage; i++) {
    int pos = 0+16*i;
    fseek(disco, pos, SEEK_SET);
    char * validity;
    fread(validity, 1, 1, disco);
    if(validity[0]=='\x00'){
    continue;
    }
    else if(validity[0]=='\x01'){
      char name[12];
      name[11] = "\0";
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
  fclose(disco);
  return 0;
}

char *decimal_to_binary(int n){

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
      return bit;
    }
  }
}

int get_next_available_block(){
  FILE * disco = fopen("simdiskfilled.bin", "r");
  fseek(disco, 1024, SEEK_SET);
  char * eight_blocks;
  for (int byte = 0; byte < 1024*8; byte++) {
    fread(eight_blocks, 1, 1, disco);
    if (*eight_blocks != '\xFF'){
      int bit = get_available_block_from_byte(*eight_blocks);
      return (byte)*8+bit;
    }
  }
}

int get_next_dir_number(){
  FILE * disco = fopen("simdiskfilled.bin", "r");
  int max_file_storage = 64;
  int index = 0;
  for (int i = 0; i < max_file_storage; i++) {
    fseek(disco, 16*i, SEEK_SET);
    char * validity;
    fread(validity, 1, 1, disco);
    if(*validity=='\x00'){
      return index;
    }
  }
}

czFILE* cz_open(char* filename, char mode){

  czFILE * open_file;
  strcpy(open_file->name, filename);
  printf("%d\n", sizeof(char*));
  sleep(4);
  //open_file->modo = mode;
  /*
  if(mode=='r'){
    printf("%s\n", "modo lectura");
    if(!cz_exists(filename)){
      printf("%s doesn't exist. Can't read what's not there bruh.\n", filename);
      sleep(10);
      return NULL;
    } else {
      FILE * disco = fopen("simdiskfilled.bin", "r");
      int max_file_storage = 64;
      int index = 0;
      for (int i = 0; i < max_file_storage; i++) {
        fseek(disco, 16*i, SEEK_SET);
        char * validity;
        fread(validity, 1, 1, disco);
        if(*validity=='\x00'){
        continue;
        }
        else if(*validity=='\x01'){
          char * name;
          fread(name, 1, 11, disco);
          if(!strcmp(name, filename)){
            index = i;
            break;
          }
        }
      }
      char * ptr;
      fseek(disco, 16*index+14, SEEK_SET);
      fread(ptr, 1, 2, disco);
      fclose(disco);
      strcpy(open_file->pointer, ptr);
    }
  */
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
      FILE * disco = fopen(diskname, "r");
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

  FILE * disco = fopen(diskname, "r");
  int max_file_storage = 64;
  for (int i = 0; i < max_file_storage; i++) {
    fseek(disco, 0+16*i, SEEK_SET);
    char * validity;
    fread(validity, 1, 1, disco);
    if(validity[0]=='\x01'){
      char * name;
      fread(name, 1, 11, disco);
      printf("%s\n", name);
    } 
  }

  fclose(disco);
  return;
}

int cz_mv(char* orig, char *dest){
  czFILE* open_file;
  strcpy(open_file->name, orig);
  if(!cz_exists(orig) || cz_exists(dest)){
    return 1;
  } 
  FILE * disco = fopen(diskname, "r+");
  int max_file_storage = 64;
  int index = 0;
  for (int i = 0; i < max_file_storage; i++) {
    fseek(disco, 16*i, SEEK_SET);
    char * validity;
    fread(validity, 1, 1, disco);
    if(*validity=='\x01'){
      char * name;
      fread(name, 1, 11, disco);
      if(strcmp(name, orig)){
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
  czFILE* open_file;
  strcpy(open_file->name, filename);
  if(!cz_exists(filename)){
    return 1;
  } 
  FILE * disco = fopen(diskname, "r+");
  int max_file_storage = 64;
  int index = 0;
  for (int i = 0; i < max_file_storage; i++) {
    fseek(disco, 16*i, SEEK_SET);
    char * validity;
    fread(validity, 1, 1, disco);
    if(*validity=='\x01'){
      char * name;
      fread(name, 1, 11, disco);
      if(!strcmp(name, filename)){
          fseek(disco, 16*i, SEEK_SET);
          fwrite('\x00', 1, 1, disco);
        break;
      }
    }
  }
  fclose(disco);
  return 0;
}

int cz_cp(char* orig, char *dest){
  czFILE* open_file;
  strcpy(open_file->name, orig);
  if(!cz_exists(orig) || cz_exists(dest)){
    return 1;
  } 
  FILE * disco = fopen(diskname, "r+");
  int max_file_storage = 64;
  int index = 0;
  bool space = 0;
  for (int i = 0; i < max_file_storage; i++) {
    fseek(disco, 16*i, SEEK_SET);
    char * validity;
    fread(validity, 1, 1, disco);
    if(*validity=='\x01'){
      space = true; 
      break;
    }
  }
  if(!space){
    fclose(disco);
    return 1;
  }
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
        fread(size, 1, 4, disco);
        fseek(disco, 16*i + 12, SEEK_SET);
        fread(data, 1, 1008, disco);
        fread(pointer, 1, 4, disco);
        fseek(disco, 0, pointer);   //esta sintaxis no estoy seguro
        fread(indirect, 1, 1024, disco);
        break;
      }
    }
  }
  /*
  Luego hay que escribir y marcar el directorio como usado
  eso falta. No estoy seguro si habia que veriicar que hubiesen dos espacios disponibles
  en disco para asi meter el bloque de direccionamiento indirecto. 
  */
  fclose(disco);
  return 0;
}
