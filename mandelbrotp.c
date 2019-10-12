#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif

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

void main(){
    //int k = mandelbrot(1,0,500);
    //printf("valor: %d\n",k);
    float reInf = -1;
    float reSup = 1;
    float imInf = -1;
    float imSup = 1;
    float depth = 500;
    float s = 0.001;
    char * filename = "salidap.raw";
    int reDim = ceil((reSup-reInf)/s+1);
    int imDim = ceil((imSup-imInf)/s+1);
    float ** matrix = (float**)malloc(sizeof(float*)*reDim);
    int i,j;
    for(i=0;i<reDim;i++){
        matrix[i] = (float*)malloc(sizeof(float)*imDim);
    }
    int nthreads = 4;
    #pragma omp parallel num_threads(nthreads) private(i,j)
    {
        #pragma omp for schedule(static,reDim/nthreads)
        for(i=0;i<reDim;i++){
            for(j=0;j<imDim;j++){
                float c_re = reInf + i*s;
                float c_im = imInf + j*s;
                float k = mandelbrot(c_re,c_im,depth);
                matrix[i][j] = log(k)+1;
            }
        }
    }
    FILE * fp = fopen(filename,"w");
    for(i=0;i<reDim;i++){
        fwrite(matrix[i],sizeof(float),imDim,fp);
    }
    fclose(fp);
}