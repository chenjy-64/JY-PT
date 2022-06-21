#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Hilbert_Envelope_Spectrum.h"
#include "Data_Processing.h"

int main(void)
{
    const long dataSize1 = getDataSize(FNAME);
    const int k = (log(dataSize1)/log((double)2)) + 1;
    const long nfft = pow(2, k);

    double *X1, *X1_real, *X1_imag, *Y1_real, *Y1_imag, *Y1;

    X1 = (double *)malloc(dataSize1 * sizeof(double));
    X1_real = (double *)malloc(nfft * sizeof(double));
    X1_imag = (double *)malloc(nfft * sizeof(double));
    Y1_real = (double *)malloc(nfft * sizeof(double));
    Y1_imag = (double *)malloc(nfft * sizeof(double));
    Y1 = (double *)malloc(nfft * sizeof(double));

    dataImport(FNAME, X1);
    dataExpand(X1, X1_real, nfft, dataSize1);
    dataZeros(X1_imag, nfft);

    printf("nfft = %d\nk = %d\n", nfft, k);
    dataHilbert(X1_real, X1_imag, Y1_real, Y1_imag, nfft, k);
    printf("hilbert %f + %f i", Y1_real[1], Y1_imag[1]);

    dataABS(Y1_real, Y1_imag, Y1, nfft);
    Hua_FFT(Y1, nfft, k, FS, SFNAME);

    free(X1);
    free(X1_real);
    free(X1_imag);
    free(Y1_real);
    free(Y1_imag);
    free(Y1);
    
    return 0;
}