#include <stdio.h>
#include <string.h>

int isPositiveInteger(char token[]){
    int size = strlen(token);
    for(int i = 0; i < size-1; i++){
        if(token[i] == '.'){
            return 0;
        }
        if(token[i] == '-'){
            return 0;
        }
        if(token[i] == 'b'){
            return 0;
        }
        if(token[i] > 57 || token[i] < 48){
            return 0;
        }
    }
    return 1;
}
int isNegativeInteger(char token[]){
    int size = strlen(token);
    int count = 0;
    int notnumcount = 0;
    for(int i = 0; i < size-1; i++){
        if(token[i] == '.'){
            return 0;
        }
        if(token[i] == 'b'){
            return 0;
        }
        if(token[i] == '-'){
            count += 1;
        }
        if(token[i] > 57 || token[i] < 48){
            notnumcount += 1;
        }
    }
    if(count > 1){
        return 0;
    }
    if(count == 0 && notnumcount > 0){
        return 0;
    }
    if(count == 1 && notnumcount > 1){
        return 0;
    }
    return 1;
}
int isBinaryNumber(char token[]){
    int size = strlen(token);
    for(int i = 0; i < size-1; i++){
        if(token[i] == '-'){
            return 0;
        }
        if(token[i] == '.'){
            return 0;
        }
    }
    if(token[0] == '0' && token[1] == 'b'){
        return 1;
    }
    return 0;
}
int isGuid(char token[]){
    int size = strlen(token);
    int count = 0;
    for(int i = 0; i < size-1; i++){
        if(token[i] == '.'){
            return 0;
        }
        if(token[i] == '-'){
            count += 1;
        }
    }
    if(count > 1){
        return 1;
    }
    return 0;
}
int isPositiveFloatingPoint(char token[]){
    int size = strlen(token);
    int count = 0;
    for(int i = 0; i < size-1; i++){
        if(token[i] == '-'){
            return 0;
        }
        if(token[i] == '.'){
            count += 1;
        }
    }
    if(count == 1){
        return 1;
    }
    return 0;
}
int isNegativeFloatingPoint(char token[]){
    int size = strlen(token);
    int dotcount = 0;
    int negcount = 0;
    for(int i = 0; i < size-1; i++){
        if(token[i] == '.'){
            dotcount += 1;
        }
        if(token[i] == '-'){
            negcount += 1;
        }
    }
    if(dotcount == 1 && negcount == 1){
        return 1;
    }
    else{
        return 0;
    }
}
int main(){
    char token[100];
    while(!feof(stdin)){
        printf("Enter a token to identify, EOF to stop:\n");
        scanf("%s", token);
        if(feof(stdin)){
            return 0;
        }
        if(isPositiveInteger(token) == 1){
            printf("The token is a positive integer\n");
        }
        else if(isNegativeInteger(token) == 1){
            printf("The token is a negative integer\n");
        }
        else if(isBinaryNumber(token) == 1){
            printf("The token is a binary number\n");
        }
        else if(isGuid(token) == 1){
            printf("The token is a guid\n");
        }
        else if(isPositiveFloatingPoint(token) == 1){
            printf("The token is a positive floating-point number\n");
        }
        else if(isNegativeFloatingPoint(token) == 1){
            printf("The token is a negative floating-point number\n");
        }
        else{
            printf("The token cannot be identified\n");
        }
    }
}