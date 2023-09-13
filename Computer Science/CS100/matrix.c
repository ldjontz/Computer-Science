#include <stdio.h>
#include <stdlib.h>

int **allocateMatrix(int numRows, int numCols)
{
   int **matrix = (int **)malloc(numRows * sizeof(int *));
   for(int i = 0; i < numRows; i++){
      matrix[i] = malloc(numCols*sizeof(int));
   }
   return matrix;
}

void freeMatrix(int **matrix, int numRows, int numCols)
{
   for(int i = 0; i < numRows; i++){
      free(matrix[i]);
   }
   free(matrix);
}

void readMatrix(FILE *fp, int **matrix, int numRows, int numCols)
{
   int val = 0;
   fscanf(fp, "%d", &val);
   while(!feof(fp)){
      for(int i = 0; i < numRows; i++){
         for(int j = 0; j < numCols; j++){
            matrix[i][j] = val;
            fscanf(fp, "%d", &val);
         }
      }
   }
}

void printMatrix(int **matrix, int numRows, int numCols)
{
   for(int i = 0; i < numRows; i++){
      for(int j = 0; j < numCols; j++){
         printf("  %d", matrix[i][j]);
      }
      printf("\n");
   }
}

int rangeRow(int **matrix, int numRows, int numCols, int r)
{
   int range = 0, max = matrix[r][0], min = matrix[r][0];
   for(int i = 0; i < numCols; i++){
      if(matrix[r][i] > max){
         max = matrix[r][i];
      }
      else if(matrix[r][i] < min){
         min = matrix[r][i];
      }
   }
   range = max - min;
   return range;
}

void printCorners(int **matrix, int numRows, int numCols)
{
   printf("%d %d\n%d %d\n", matrix[0][0], matrix[0][numCols-1], matrix[numRows-1][0], matrix[numRows-1][numCols-1]);
}

int sumSubMatrix(int **matrix, int startRow, int endRow, int startCol, int endCol)
{
   int total = 0;
   for(int i = startRow; i <= endRow; i++){
      for(int j = startCol; j <= endCol; j++){
         total += matrix[i][j];
      }
   }
   return total;
}
