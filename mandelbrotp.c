#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>
#include "funciones.h"

int main(int argc, char ** argv){
    if(argc<17){
        printf("Argumentos insuficientes.\n");
        exit(1);
    }
    /*
    i: número máximo de iteraciones
    a: valor inferior de la parte real
    c: valor superior de la parte real
    b: valor inferior de la parte imaginaria
    d: valor superior de la parte imaginaria
    s: frecuencia de muestreo
    f: nombre del archivo de salida
    */
    float reInf;
    float reSup;
    float imInf;
    float imSup;
    float depth;
    float s;
    char * filename;
    int nthreads;
    int c;


    opterr=0;

    while((c=getopt(argc,argv,"i:a:c:b:d:s:f:t:"))!=-1){
        switch (c){
            case 'i':
                sscanf(optarg,"%f",&depth);
                break;
            case 'a':
                sscanf(optarg,"%f",&reInf);
                break;
            case 'c':
                sscanf(optarg,"%f",&reSup);
                break;
            case 'b':
                sscanf(optarg,"%f",&imInf);
                break;
            case 'd':
                sscanf(optarg,"%f",&imSup);
                break;
            case 's':
                sscanf(optarg,"%f",&s);
                break;
            case 'f':
                filename = optarg;
                break;
            case 't':
                sscanf(optarg,"%d",&nthreads);
            case '?':
                break;
        }
    }
    //printf("depth: %f, reInf: %f, reSup: %f, imInf: %f, imSup: %f, s: %f, f: %s, t: %d\n",depth,reInf,reSup,imInf,imSup,s,filename,nthreads);
    mandelbrotP(depth,reInf,reSup,imInf,imSup, s, filename,nthreads);
    return 0;
}