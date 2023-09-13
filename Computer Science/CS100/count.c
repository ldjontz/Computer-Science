#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
    char *string;
    int uppers = 0, lowers = 0, digits = 0;
    string = (char*) malloc(sizeof(char));
    scanf("%s", string);
    int len = strlen(string);
    for(int i = 0; i < len; i++){
        if(isupper(*(string + i)) == 1){
            uppers += 1;
        }
        if(islower(*(string + i)) == 1){
            lowers += 1;
        }
        if(isdigit(*(string + i))){
            digits += 1;
        }
    }
    printf("Uppers = %d\nLowers = %d\nDigits = %d\n", uppers, lowers, digits);
}