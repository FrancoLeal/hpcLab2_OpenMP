CC=gcc

all: mandelbrot mandelbrotp

mandelbrot: mandelbrot.c funciones.c
	$(CC) -o mandelbrot mandelbrot.c funciones.c -lm

mandelbrotp: mandelbrotp.c funciones.c
	$(CC) -o mandelbrotp mandelbrotp.c funciones.c -lm -fopenmp