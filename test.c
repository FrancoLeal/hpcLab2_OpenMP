#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif

void main(){
    int i,j;
    #pragma omp parallel num_threads(4)
    {
        #pragma omp for
        for(i=0;i<10;i++){
            printf("i: %d\n",i);
            for(j=0;j<10;j++);
        }
    }
}