#ifndef _FFT_H
#define _FFT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PI 3.141592653589

void dataFFT(double data_real[], double data_imag[], double fftRes_real[], double fftRes_imag[], int n, int k, int isInverse);

#endif