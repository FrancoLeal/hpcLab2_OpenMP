#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
#include <omp.h>
#endif
#include "funciones.h"

void writeFile(float ** matrix, char * filename, int reDim, int imDim){
    int i;
    FILE * fp = fopen(filename,"w");
    for(i=0;i<reDim;i++){
        fwrite(matrix[i],sizeof(float),imDim,fp);
    }
}

float mandelbrot(float c_re, float c_im, float depth){
    float k=0;
    float z_re = 0 + c_re;
    float z_im = 0 + c_im;
    float z_re2 = z_re*z_re;
    float z_im2 = z_im*z_im;
    float dist = sqrt(z_re2 + z_im2);
    while(k<depth && dist < 2){
        z_im = 2*z_re*z_im + c_im;
        z_re = z_re2 - z_im2 + c_re;
        z_re2 = z_re*z_re;
        z_im2 = z_im*z_im;
        dist = sqrt(z_re2 + z_im2);
        k++;
    }
    return k;
}

void mandelbrotS(float depth, float reInf, float reSup, float imInf, float imSup, float s, char * filename){
    float reDim = ceil((reSup-reInf)/s+1);
    float imDim = ceil((imSup-imInf)/s+1);
    float ** matrix = (float**)malloc(sizeof(float*)*reDim);
    int i,j;
    for(i=0;i<reDim;i++){
        matrix[i] = (float*)malloc(sizeof(float)*imDim);
    }
    for(i=0;i<reDim;i++){
        for(j=0;j<imDim;j++){
            float c_re = reInf + i*s;
            float c_im = imInf + j*s;
            float k = mandelbrot(c_re,c_im,depth);
            matrix[i][j] = log(k)+1;
        }
    }
    writeFile(matrix,filename,reDim,imDim);
    for(i=0;i<reDim;i++){
        free(matrix[i]);
    }
    free(matrix);
}

void mandelbrotP(float depth, float reInf, float reSup, float imInf, float imSup, float s, char * filename, int nthreads){
    int reDim = (int)ceil((reSup-reInf)/s+1);
    float imDim = ceil((imSup-imInf)/s+1);
    float ** matrix = (float**)malloc(sizeof(float*)*reDim);
    int i,j;
    for(i=0;i<reDim;i++){
        matrix[i] = (float*)malloc(sizeof(float)*imDim);
    }
    #pragma omp parallel num_threads(nthreads) private(i,j)
    {
        #pragma omp for schedule(static)
        for(i=0;i<reDim;i++){
            for(j=0;j<imDim;j++){
                float c_re = reInf + i*s;
                float c_im = imInf + j*s;
                float k = mandelbrot(c_re,c_im,depth);
                matrix[i][j] = log(k)+1;
            }
        }
    }
    writeFile(matrix,filename,reDim,imDim);
    for(i=0;i<reDim;i++){
        free(matrix[i]);
    }
    free(matrix);
}