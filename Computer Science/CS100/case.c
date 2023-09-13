#include <stdio.h>
#include <ctype.h>
#include <string.h>

void countCase(char str[], int *pNumUpper, int *pNumLower);

int main() {
   char string[50];
   int upper = 0, lower = 0;
   while(!feof(stdin)){
      scanf("%s", string);
      countCase(string, &upper, &lower);
      for(int i = 0; i < strlen(string); i++){
         printf("%c", string[i]);
      }
      printf(": %d uppercase, %d lowercase\n", upper, lower);
      upper = 0;
      lower = 0;
   }
   return 0;
}

void countCase(char str[], int *pNumUpper, int *pNumLower) {
   for(int i = 0; i < strlen(str); i++){
      char chara = str[i];
      if(isupper(chara)){
         *pNumUpper += 1;
      }
      else if(islower(chara)){
         *pNumLower += 1;
      }
   }
}
