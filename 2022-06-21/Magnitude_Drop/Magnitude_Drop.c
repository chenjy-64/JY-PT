#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Data_Processing.h"
#include "Magnitude_Drop.h"

int main(void)
{
    Magnitude_FileSet fileSet[6] = {{FNAME1_1, FNAME1_2}, {FNAME2_1, FNAME2_2}, {FNAME3_1, FNAME3_2}, {FNAME4_1, FNAME4_2}, {FNAME5_1, FNAME5_2}, {FNAME6_1, FNAME6_2}};
    double tMagnitude1[6], tMagnitude2[6];

    for (int i = 0; i < 6; i++)
    {
        tMagnitude1[i] = Total_Magnitude_Calculate_File(fileSet[i].topLayer_DFile, UPPER, LOWER, F1, F2, P0, FS);
        printf("Magnitude 1 %d = %f\n", i + 1, tMagnitude1[i]);
        tMagnitude2[i] = Total_Magnitude_Calculate_File(fileSet[i].bottomLayer_DFile, UPPER, LOWER, F1, F2, P0, FS);
        printf("Magnitude 2 %d = %f\n", i + 1, tMagnitude2[i]);
    }

    for (int i = 0; i < 6; i++)
    {
        printf("Magnitude_Drop %d = %f\n", i + 1, tMagnitude2[i] - tMagnitude1[i]);
    }

    return 0;
}