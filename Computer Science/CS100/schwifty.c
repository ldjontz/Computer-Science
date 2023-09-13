#include <stdio.h>
#include <string.h>
#include <ctype.h>

void left(char word[]);
void right(char word[]);
void inc(char word[]);
void dec(char word[]);

int main(int argc, char *argv[]) {
   if(argc != 3){
      printf("Invalid number of arguments");
      return 1;
   }
   FILE *fp;
   char name[100] = argv[1];
   fp = fopen(name, "r");
   if(fp == NULL){
      printf("Could not open file '%s'", argv[1]);
      return 1;
   }
   int len = strlen(argv[2]);
   for(int i = 0; i < len; i++){
      if(argv[2][i] == 'L'){
         left(argv[2]);
      }
      else if(argv[2][i] == 'R'){
         right(argv[2]);
      }
      else if(argv[2][i] == 'I'){
         inc(argv[2]);
      }
      else if(argv[2][i] == 'D'){
         dec(argv[2]);
      }
      else{
         printf("You threw off my schwiftiness with schwifty '%c'", argv[2][i]);
      }
   }
   return 0;
}

void left(char word[]) {
   int len = strlen(word);
   char temp = word[0];
   for(int i = 0; i < len; i++){
      word[i] = word[i+1];
   }
   word[len-1] = temp;
}

void right(char word[]) {
   int len = strlen(word);
   char temp = word[len-1];
   for(int i = len-1; i >= 0; i--){
      word[i] = word[i - 1];
   }
   word[0] = temp;
}

void inc(char word[]) {
   
}

void dec(char word[]) {
   
}
