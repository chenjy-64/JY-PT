#include <math.h>

double BG_Noise_Correction(double La, double Lk)
{
    if (La - Lk >= 10)
    {
        return La;
    }
    else
    {
        return 10 * log10(pow(10, 0.1*La) - pow(10, 0.1*Lk));
    }
}