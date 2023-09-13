#include<stdio.h>
#include<stdlib.h>

int threes(int val) {
   if(val > 9){
    if(val % 10 == 3){
        return 1 + threes(val / 10);
    }
    else{
        threes(val / 10);
    }
   }
   else if(val > 0){
        if(val == 3){
            return 1;
        }
        else{
            return 0;
        }
   }
   else{
        return 0;
   }
}

int main(int argc, char *argv[]) {
    int val = atoi(argv[1]);

    printf("%d contains %d threes.\n", val, threes(val));

    return 0;
}
