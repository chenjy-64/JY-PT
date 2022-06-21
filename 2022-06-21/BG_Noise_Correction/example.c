#include <stdio.h>
#include "BG_Noise_Correction.h"

int main(void)
{
    printf("La = 20, Lk = 10 => Li = %f\n", BG_Noise_Correction(20, 10));
    printf("La = 11, Lk = 10 => Li = %f\n", BG_Noise_Correction(11, 10));
    
    return 0;
}