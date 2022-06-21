#include "FFT.h"

/*
Function Name: dataFFT
Input Argument:
    data_real[n] - The real part of input data (Array, Size n)
    data_imag[n] - The imaginary part of input data array (Array, Size n)
    fftRes_real[n] - The real part of FFT/IFFT result (Array, Size n)
    fftRes_imag[n] - The imaginary part of FFT/IFFT result (Array, Size n)
    int n - n is the FFT/IFFT frequency resolution and also the size of input/output data array, which equals to interger power of 2 (n = pow(2, k))
    int k - k is the FFT/IFFT order and also the base 2 logarithm of a true number n (k = log2(n))
    int isInverse - , If isInverse is 1, the function executes IFFT. Else excutes FFT.
Return Value: void
*/

void dataFFT(double data_real[], double data_imag[], double fftRes_real[], double fftRes_imag[], int n, int k, int isInverse)
{
    clock_t start_time;
    long it, m, is, i, j, nv, l0;
    double p, q, s, vr, vi, poddr, poddi;

    start_time = clock();

    if (isInverse == 1)
    {
        for (i = 0; i < n; i++) //取共轭
        {
            data_imag[i] = -data_imag[i];
        }
    }

    for (it = 0; it <= n - 1; it++)  //将data_real[0]和data_imag[0]循环赋值给fftRes_imag[]和fftRes_imag[]
    { 
		m = it; 
		is = 0;
		for(i = 0; i <= k - 1; i++)
        { 
			j = m / 2; 
			is = 2 * is + (m - 2 * j); 
			m = j;
		}
        fftRes_real[it] = data_real[is]; 
        fftRes_imag[it] = data_imag[is];
    }
    data_real[0] = 1.0; 
    data_imag[0] = 0.0;
    p = 2 * PI / (1.0 * n);
    data_real[1] = cos(p); //将w=e^-j2data_imag/n用欧拉公式表示
    data_imag[1] = -sin(p);

    for (i = 2; i <= n - 1; i++)  //计算data_real[]
    { 
		p = data_real[i - 1] * data_real[1]; 
		q = data_imag[i - 1] * data_imag[1];
		s = (data_real[i - 1] + data_imag[i - 1]) * (data_real[1] + data_imag[1]);
		data_real[i] = p - q;
        data_imag[i] = s - p - q;
    }
    
    for (it = 0; it <= n - 2; it = it + 2)
    { 
		vr = fftRes_real[it]; 
		vi = fftRes_imag[it];
		fftRes_real[it] = vr + fftRes_real[it + 1]; 
		fftRes_imag[it] = vi + fftRes_imag[it + 1];
		fftRes_real[it + 1] = vr - fftRes_real[it + 1]; 
		fftRes_imag[it + 1] = vi - fftRes_imag[it + 1];
    }
	
    m = n / 2; 
	nv = 2;
    
    for (l0 = k - 2; l0 >= 0; l0--) //蝴蝶操作
    { 
		m = m / 2; 
		nv = 2 * nv;
        for (it = 0; it <= (m - 1) * nv; it = it + nv)
        {
            for (j = 0; j <= (nv / 2) - 1; j++)
            { 
				p = data_real[m * j] * fftRes_real[it + j + nv / 2];
				q = data_imag[m * j] * fftRes_imag[it + j + nv / 2];
				s = data_real[m * j] + data_imag[m * j];
				s = s * (fftRes_real[it + j + nv / 2] + fftRes_imag[it + j + nv / 2]);
				poddr = p - q; 
				poddi = s - p - q;
				fftRes_real[it + j + nv / 2] = fftRes_real[it + j] - poddr;
				fftRes_imag[it + j + nv / 2] = fftRes_imag[it + j] - poddi;
				fftRes_real[it + j] = fftRes_real[it + j] + poddr;
				fftRes_imag[it + j] = fftRes_imag[it + j] + poddi;
            }
        }    
    }

    if (isInverse == 1)
    {
        for (i = 0; i < n; i++)
        {
            fftRes_real[i] /= (double)n;
            fftRes_imag[i] /= (double)(-n);
        }
    }

    printf("-- [%.2f] --\n",(double)(clock() - start_time) / CLOCKS_PER_SEC);
}