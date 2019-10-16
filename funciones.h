#ifndef _FUNCIONES_H_
#define _FUNCIONES_H_

#include <math.h>

float mandelbrot(float c_re, float c_im, float depth);

void mandelbrotS(float depth, float reInf, float reSup, float imInf, float imSup, float s, char * filename);

void mandelbrotP(float depth, float reInf, float reSup, float imInf, float imSup, float s, char * filename, int nthreads);

void writeFile(float ** matrix, char * filename, int reDim, int imDim);

#endif