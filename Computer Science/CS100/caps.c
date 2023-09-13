#include <stdio.h>
#include <ctype.h>

int caps(char *str) {
   if(*str != NULL){
      if(isupper(*str)){
         return 1 + caps(str + 1);
      }
      else{
         caps(str+1);
      }
   }
   else{
      return 0;
   }
}

int main(int argc, char *argv[]) {
   printf("%s has %d capital letters\n", argv[1], caps(argv[1]));
   
   return 0;
}
