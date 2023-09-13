#include <stdio.h>

void shift(int *refX, int *refY, int *refZ);

int main() {
   int x, y, z;
   printf("Enter any three integers:\n");
   scanf("%d%d%d", &x, &y, &z);
   shift(&x, &y, &z);
   printf("The results after one shift: %d %d %d\n", x, y, z);
   shift(&x, &y, &z);
   printf("The results after another shift: %d %d %d\n", x, y, z);

   return 0;
}

void shift(int *refX, int *refY, int *refZ) {
   int temp1 = 0, temp2 = 0, temp3 = 0;
   temp1 = *refX;
   temp2 = *refY;
   temp3 = *refZ;
   *refX = temp3;
   *refY = temp1;
   *refZ = temp2;
}
