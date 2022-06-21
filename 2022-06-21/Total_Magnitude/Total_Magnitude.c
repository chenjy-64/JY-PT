#include <stdio.h>
#include <stdlib.h>

#include "Data_Processing.h"
#include "Total_Magnitude.h"

int main(void)
{
    // const long dataSize = getDataSize_col(FNAME, 2);
    // const int splitSize = UPPER - LOWER + 1;
    double tMagnitude = 0;
    // double *X1, *Xs;

    // X1 = (double *)malloc(dataSize * sizeof(double));
    // Xs = (double *)malloc(splitSize * sizeof(double));

    // dataImport_col(FNAME, 2, X1);

    // dataSplit(X1, Xs, LOWER, UPPER);

    // tMagnitude = Total_Magnitude_Calculate(Xs, splitSize, F1, F2, P0, FS);

    // printf("%f\n", tMagnitude);

    tMagnitude = Total_Magnitude_Calculate_File(FNAME, UPPER, LOWER, F1, F2, P0, FS);

    printf("%f\n", tMagnitude);

    // free(X1);
    // free(Xs);

    return 0;
}