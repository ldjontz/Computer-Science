#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "image.h"
void swap(Pixel *x, Pixel *y){
    Pixel temp = *x;
    *x = *y;
    *y = temp;
}

ImagePPM *readPPM(char *filename)
{
    FILE *fp = fopen(filename,"r");
    if(fp == NULL){
        return NULL;
    }
    ImagePPM* ptr = (ImagePPM*)malloc(sizeof(ImagePPM));
    char buffer[100];
    fgets(buffer, 100, fp);
    fscanf(fp, "%d %d %d", &ptr->width, &ptr->height, &ptr->max_value);
    ptr->pixels = (Pixel**)malloc(ptr->height * sizeof(Pixel*));
    for(int i = 0; i < ptr->height; i++){
        ptr->pixels[i] = (Pixel*)malloc(ptr->width * sizeof(Pixel));
    }
    for(int i = 0; i < ptr->height; i++){
        for(int j = 0; j < ptr->width; j++){
            fscanf(fp,"%d %d %d", &ptr->pixels[i][j].red, &ptr->pixels[i][j].green, &ptr->pixels[i][j].blue);
        }
    }
    fclose(fp);
    return ptr;
}

int writePPM(ImagePPM *pImagePPM, char *filename)
{
    FILE* fp = fopen(filename,"w");
    if(fp == NULL){
        return 0;
    }
    fprintf(fp,"P3\n");
    fprintf(fp,"%d %d %d\n", pImagePPM->width, pImagePPM->height, pImagePPM->max_value);
    for(int i = 0; i < pImagePPM->height; i++){
        for(int j = 0; j < pImagePPM->width; j++){
            fprintf(fp, "%d %d %d ", pImagePPM->pixels[i][j].red, pImagePPM->pixels[i][j].green, pImagePPM->pixels[i][j].blue);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
    return 1;
}

ImagePPM *rotatePPM(ImagePPM *pImagePPM)
{
    ImagePPM* ptr = (ImagePPM*)malloc(sizeof(ImagePPM));
	ptr->height = pImagePPM->width;
    ptr->width = pImagePPM->height;
    ptr->max_value = pImagePPM->max_value;
    ptr->pixels = (Pixel**)malloc(ptr->height * sizeof(Pixel*));
    for(int i = 0; i < ptr->height; i++){
        ptr->pixels[i] = (Pixel*)malloc(ptr->width * sizeof(Pixel));
    }
    ptr->pixels = pImagePPM->pixels;
    for(int i = 0; i < ptr->height; i++){
        for(int j = 0; j < ptr->width; j++){
            swap(&ptr->pixels[i][j], &ptr->pixels[j][i]);
        }
    }
    for(int i = 0; i < ptr->height; i++){
        for(int j = 0; j < ptr->width/2; j++){
            swap(&ptr->pixels[i][j], &ptr->pixels[i][ptr->width-j-1]);
        }
    }
    return ptr;
}

ImagePPM *flipPPM(ImagePPM *pImagePPM)
{
    ImagePPM* ptr = (ImagePPM*)malloc(sizeof(ImagePPM));
	ptr->height = pImagePPM->height;
    ptr->width = pImagePPM->width;
    ptr->max_value = pImagePPM->max_value;
    ptr->pixels = (Pixel**)malloc(ptr->height * sizeof(Pixel*));
    for(int i = 0; i < ptr->height; i++){
        ptr->pixels[i] = (Pixel*)malloc(ptr->width * sizeof(Pixel));
    }
    ptr->pixels = pImagePPM->pixels;
    for(int i = 0; i < ptr->height; i++){
        for(int j = 0; j < ptr->width/2; j++){
            swap(&ptr->pixels[i][j], &ptr->pixels[i][ptr->width-j-1]);
        }
    }
    return ptr;
}

ImagePPM *enlargePPM(ImagePPM *pImagePPM)
{
    ImagePPM* ptr = (ImagePPM*)malloc(sizeof(ImagePPM));
	ptr->height = ((pImagePPM->height) * 2);
    ptr->width = ((pImagePPM->width) * 2);
    ptr->pixels = (Pixel**)malloc(ptr->height * sizeof(Pixel*));
    for(int i = 0; i < ptr->height; i++){
        ptr->pixels[i] = (Pixel*)malloc(ptr->width * sizeof(Pixel));
    }
    ptr->max_value = pImagePPM->max_value;
    for(int i = 0; i < ptr->height/2; i++){
        for(int j = 0; j < ptr->width/2; j++){
            ptr->pixels[2*i][2*j] = pImagePPM->pixels[i][j];
            ptr->pixels[(2*i) + 1][2*j] = pImagePPM->pixels[i][j];
            ptr->pixels[2*i][(2*j) + 1] = pImagePPM->pixels[i][j];
            ptr->pixels[(2*i) + 1][(2*j) + 1] = pImagePPM->pixels[i][j];
        }
    }
    return ptr;
}

ImagePPM *shrinkPPM(ImagePPM *pImagePPM)
{
    ImagePPM* ptr = (ImagePPM*)malloc(sizeof(ImagePPM));
	ptr->height = pImagePPM->height / 2;
    ptr->width = pImagePPM->width / 2;
    ptr->pixels = (Pixel**)malloc(ptr->height * sizeof(Pixel*));
    for(int i = 0; i < ptr->height; i++){
        ptr->pixels[i] = (Pixel*)malloc(ptr->width * sizeof(Pixel));
    }
    ptr->max_value = pImagePPM->max_value;
    for(int i = 0; i < ptr->height; i++){
        for(int j = 0; j < ptr->width; j++){
            ptr->pixels[i][j].red = (pImagePPM->pixels[(2*i)][(2*j)].red + pImagePPM->pixels[(2*i) + 1][(2*j)].red + pImagePPM->pixels[(2*i)][(2*j) + 1].red + pImagePPM->pixels[(2*i)+1][(2*j)+1].red)/4;
            ptr->pixels[i][j].green = (pImagePPM->pixels[(2*i)][(2*j)].green + pImagePPM->pixels[(2*i) + 1][(2*j)].green + pImagePPM->pixels[(2*i)][(2*j) + 1].green + pImagePPM->pixels[(2*i)+1][(2*j)+1].green)/4;
            ptr->pixels[i][j].blue = (pImagePPM->pixels[(2*i)][(2*j)].blue + pImagePPM->pixels[(2*i) + 1][(2*j)].blue + pImagePPM->pixels[(2*i)][(2*j) + 1].blue + pImagePPM->pixels[(2*i)+1][(2*j)+1].blue)/4;
        }
    }
    return ptr;
}

ImagePPM *invertPPM(ImagePPM *pImagePPM)
{
    ImagePPM* ptr = (ImagePPM*)malloc(sizeof(ImagePPM));
	ptr->height = pImagePPM->height;
    ptr->width = pImagePPM->width;
    ptr->max_value = pImagePPM->max_value;
    ptr->pixels = (Pixel**)malloc(ptr->height * sizeof(Pixel*));
    for(int i = 0; i < ptr->height; i++){
        ptr->pixels[i] = (Pixel*)malloc(ptr->width * sizeof(Pixel));
    }
    ptr->pixels = pImagePPM->pixels;
    for(int i = 0; i < ptr->height; i++){
        for(int j = 0; j < ptr->width; j++){
            ptr->pixels[i][j].red = ptr->max_value - ptr->pixels[i][j].red;
            ptr->pixels[i][j].green = ptr->max_value - ptr->pixels[i][j].green;
            ptr->pixels[i][j].blue = ptr->max_value - ptr->pixels[i][j].blue;
        }
    }
    return ptr;
}

ImagePPM *cropPPM(ImagePPM *pImagePPM, int r1, int c1, int r2, int c2)
{
    ImagePPM* ptr = (ImagePPM*)malloc(sizeof(ImagePPM));
	ptr->height = abs(r1-r2) + 1;
    ptr->width = abs(c1-c2) + 1;
    ptr->pixels = (Pixel**)malloc(ptr->height * sizeof(Pixel*));
    for(int i = 0; i < ptr->height; i++){
        ptr->pixels[i] = (Pixel*)malloc(ptr->width * sizeof(Pixel));
    }
    ptr->max_value = pImagePPM->max_value;
    if(r1 > r2){
        if(c1 > c2){
            for(int i = 0; i < ptr->height; i++){
                for(int j = 0; j < ptr->width; j++){
                    ptr->pixels[i][j] = pImagePPM->pixels[r2+i][c2+j];
                }
            }
        }
        if(c1 < c2){
            for(int i = 0; i < ptr->height; i++){
                for(int j = 0; j < ptr->width; j++){
                    ptr->pixels[i][j] = pImagePPM->pixels[r2+i][c1+j];
                }
            }
        }
    }
    if(r2 > r1){
        if(c1 > c2){
            for(int i = 0; i < ptr->height; i++){
                for(int j = 0; j < ptr->width; j++){
                    ptr->pixels[i][j] = pImagePPM->pixels[r1+i][c2+j];
                }
            }
        }
        if(c1 < c2){
            for(int i = 0; i < ptr->height; i++){
                for(int j = 0; j < ptr->width; j++){
                    ptr->pixels[i][j] = pImagePPM->pixels[r1+i][c1+j];
                }
            }
        }
    }
    return ptr;
}

void freeSpacePPM(ImagePPM *pImagePPM)
{
    free
}

