#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265358979323846

long getDataSize(const char * path)
{
    FILE * fp = fopen(path, "r");
    long dataSize = 0;
    double data;

    while (!feof(fp) && (fscanf(fp, "%le", &data) == 1))
    {
        dataSize++;
    }
    fclose(fp);
    printf("%s Data Size - %d \n", path, dataSize);
    free(fp);
    return dataSize;
}

long getDataSize_col(const char * path, const int column)
{
    FILE * fp = fopen(path, "r");
    long dataSize = 0;
    double data, data_temp;

    switch (column)
    {
    case 1:
        while (!feof(fp) && (fscanf(fp, "%le", &data) == 1))
        {
            dataSize++;
        }
        fclose(fp);
        printf("%s Data Size - %d \n", path, dataSize);
        break;
    
    case 2:
        printf("getDataSize_col COLUMN 2 !!!\n");
        while (!feof(fp) && (fscanf(fp, "%le %le", &data_temp, &data) == 2))
        {
            dataSize++;
        }
        fclose(fp);
        printf("%s Data Size - %d \n", path, dataSize);
        break;

    default:
        dataSize = -1;
        break;
    }
    return dataSize;
}

void dataImport(const char * path, double data[])
{
    FILE * fp = fopen(path, "r");
    long dataSize = 0;

    while (!feof(fp) && (fscanf(fp, "%le", &data[dataSize]) == 1))
    {
        (dataSize)++;
    }
    fclose(fp);
    printf("%s Data Size - %d \n", path, dataSize);
    // for (long i = 0; i < 5; i++)
    //     printf("%20d %10.6f \n", i*10000, data[i*10000]);
}

void dataImport_col(const char * path, const int column, double data[])
{
    FILE * fp = fopen(path, "r");
    long dataSize = 0;
    double data_temp = 0;

    switch (column)
    {
    case 1:
        while (!feof(fp) && (fscanf(fp, "%le", &data[dataSize]) == 1))
        {
            (dataSize)++;
        }
        fclose(fp);
        printf("%s Data Size - %d \n", path, dataSize);
        // for (long i = 0; i < 5; i++)
        //     printf("%20d %10.6f \n", i*10000, data[i*10000]);
        break;
    
    case 2:
        while (!feof(fp) && (fscanf(fp, "%le %le", &data_temp, &data[dataSize]) == 2))
        {
            (dataSize)++;
        }
        fclose(fp);
        printf("%s Data Size - %d \n", path, dataSize);
        // for (long i = 0; i < 5; i++)
        //     printf("%20d %10.6f \n", i*10000, data[i*10000]);
        break;
    
    default:
        printf("dataImport Function Argument <columns> input errors!");
        break;
    }
}

void dataExpand(const double data[], double data_Expand[], const long ndft, const long size)
{
    long i = 0L;
    
    if (size < ndft)
    {
        for (i = 0; i < size; i++)
        {
            data_Expand[i] = data[i];
        }
        for (i = size; i < ndft; i++)
        {
            data_Expand[i] = 0;
        }
    }
    else
    {
        for (i = 0; i < ndft; i++)
        {
            data_Expand[i] = data[i];
        }
    }
    // for (i = 0; i < 5; i++)
    //     printf("%20d %10.6f \n", i*10000, data[i*10000]);
}

void dataSplit(double data[], double split[], int lower, int upper)
{
    for (int i = 0; i < upper - lower + 1; i++)
    {
        split[i] = data[i + lower - 1];
    }
}

void dataZeros(double data[], const long size)
{
    for (long i = 0; i < size; i++)
    {
        data[i] = 0;
    }
}

void dataCentralize(double data[], const long size)
{
    long i = 0;
    double mean = 0;

    for (i = 0; i < size; i++)
    {
        mean += data[i] / size;
    }       
    for (i = 0; i < size; i++)
    {
        data[i] -= mean;
    }        
    printf("Data Size - %d\n", size);
    // for (long i = 0; i < 5; i++)
    //     printf("%20d %10.6f \n", i*10000, data[i*10000]);
}

void dataABS(double data_real[], double data_imag[], double data_res[], int size)
{
    for (int i = 0; i < size; i++)
    {
        data_res[i] = sqrt(data_real[i] * data_real[i] + data_imag[i] * data_imag[i]);
    }
}

void dataFFT(double data_real[], double data_imag[], double fftRes_real[], double fftRes_imag[], int n, int k)
{ 
    clock_t start_time;
    long it, m, is, i, j, nv, l0;
    double p, q, s, vr, vi, poddr, poddi;

    start_time = clock();

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

    printf("-- [%.2f] --\n",(double)(clock() - start_time) / CLOCKS_PER_SEC);
    // for (i = 0; i <= n - 1; i++)
    // { 
	// 	    data_real[i] = sqrt(fftRes_imag[i] * fftRes_imag[i] + fftRes_imag[i] * fftRes_imag[i]);  //幅值计算
    // }
}

void dataIFFT(double data_real[], double data_imag[], double ifftRes_real[], double ifftRes_imag[], int n, int k)
{ 
    clock_t start_time;
    long it, m, is, i, j, nv, l0;
    double p, q, s, vr, vi, poddr, poddi;

    start_time = clock();
    for (i = 0; i < n; i++) //取共轭
    {
        data_imag[i] = -data_imag[i];
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
        ifftRes_real[it] = data_real[is]; 
        ifftRes_imag[it] = data_imag[is];
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
		vr = ifftRes_real[it]; 
		vi = ifftRes_imag[it];
		ifftRes_real[it] = vr + ifftRes_real[it + 1]; 
		ifftRes_imag[it] = vi + ifftRes_imag[it + 1];
		ifftRes_real[it + 1] = vr - ifftRes_real[it + 1]; 
		ifftRes_imag[it + 1] = vi - ifftRes_imag[it + 1];
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
				p = data_real[m * j] * ifftRes_real[it + j + nv / 2];
				q = data_imag[m * j] * ifftRes_imag[it + j + nv / 2];
				s = data_real[m * j] + data_imag[m * j];
				s = s * (ifftRes_real[it + j + nv / 2] + ifftRes_imag[it + j + nv / 2]);
				poddr = p - q; 
				poddi = s - p - q;
				ifftRes_real[it + j + nv / 2] = ifftRes_real[it + j] - poddr;
				ifftRes_imag[it + j + nv / 2] = ifftRes_imag[it + j] - poddi;
				ifftRes_real[it + j] = ifftRes_real[it + j] + poddr;
				ifftRes_imag[it + j] = ifftRes_imag[it + j] + poddi;
            }
        }    
    }

    for (i = 0; i < n; i++)
    {
        ifftRes_real[i] /= (double)n;
        ifftRes_imag[i] /= (double)(-n);
    }
    printf("-- [%.2f] --\n",(double)(clock() - start_time) / CLOCKS_PER_SEC);
    // for (i = 0; i <= n - 1; i++)
    // { 
	// 	    data_real[i] = sqrt(fftRes_imag[i] * fftRes_imag[i] + fftRes_imag[i] * fftRes_imag[i]);  //幅值计算
    // }
}

void dataHilbert(double data_real[], double data_imag[], double hilbertRes_real[], double hilbertRes_imag[], int n, int k)
{
    double *fft_real, *fft_imag;

    fft_real = (double *)malloc(n * sizeof(double));
    fft_imag = (double *)malloc(n * sizeof(double));
    
    dataZeros(fft_real, n);
    dataZeros(fft_imag, n);
    
    dataFFT(data_real, data_imag, fft_real, fft_imag, n, k);
    
    if ((int)(n/2) * 2 == n)    //even
    {
        for (int i = 0; i < n; i++)
        {
            if (i > 0 && i < n/2)
            {
                fft_real[i] *= 2;
                fft_imag[i] *= 2;
            }
            else if (i > n/2)
            {
                fft_real[i] = 0;
                fft_imag[i] = 0;
            }  
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (i > 0 && i < (n+1)/2)
            {
                fft_real[i] *= 2;
                fft_imag[i] *= 2;
            }
            else if (i >= (n+1)/2)
            {
                fft_real[i] = 0;
                fft_imag[i] = 0;
            }
        }
    }
    
    dataIFFT(fft_real, fft_imag, hilbertRes_real, hilbertRes_imag, n, k);

    free(fft_real);
    free(fft_imag);
}

void Hua_FFT(double data[], int n, int k, int fs, const char * path)
{
    FILE *fp = fopen(path, "w");
    double *zeros, *res_real, *res_imag, *freq, *res_fft, *res_p;

    zeros = (double *)malloc(n * sizeof(double));
    res_real = (double *)malloc(n * sizeof(double));
    res_imag = (double *)malloc(n * sizeof(double));
    freq = (double *)malloc(n/2 * sizeof(double));
    res_fft = (double *)malloc(n/2 * sizeof(double));
    res_p = (double *)malloc(n/2 * sizeof(double));
    
    dataZeros(zeros, n);
    dataZeros(res_real, n);
    dataZeros(res_imag, n);
    dataZeros(freq, n/2);
    dataZeros(res_fft, n/2);
    dataZeros(res_p, n/2);

    dataCentralize(data, n);
    dataFFT(data, zeros, res_real, res_imag, n, k);

    for (int i = 0; i < n/2; i++)
    {
        freq[i] = fs * i / (double)n;
        res_fft[i] = 2 * sqrt(res_real[i] * res_real[i] + res_imag[i] * res_imag[i]) / n;
        res_p[i] = (res_real[i] * res_real[i] + res_imag[i] * res_imag[i]) / n;
        fprintf(fp, "%f\t%.8e\t%.8e\n", freq[i], res_fft[i], res_p[i]);
    }
    
    fclose(fp);

    free(fp);
    free(zeros);
    free(res_real);
    free(res_imag);
    free(freq);
    free(res_fft);
    free(res_p);
}

double Total_Magnitude_Calculate(double data[], const int size, const int f1, const int f2, const double p0, const int fs)
{
    const int k = (log((double)size)/log(2.0)) + 1;
    const long nfft = pow(2, k);
    double freq = 0, count = 0, temp = 0;
    double *X, *zeros, *Y_real, *Y_imag, *Y;

    X = (double *)malloc(nfft * sizeof(double));
    zeros = (double *)malloc(nfft * sizeof(double));
    Y_real = (double *)malloc(nfft * sizeof(double));
    Y_imag = (double *)malloc(nfft * sizeof(double));
    Y = (double *)malloc(nfft * sizeof(double));

    dataExpand(data, X, nfft, size);
    dataZeros(zeros, nfft);

    printf("nfft = %d\nk = %d\n", nfft, k);
    dataFFT(X, zeros, Y_real, Y_imag, nfft, k);

    for (int i = 0; i < nfft; i++)
    {
        Y_real[i] = Y_real[i] * 2 / nfft;
        Y_imag[i] = Y_imag[i] * 2 / nfft;
        Y[i] = sqrt(Y_real[i] * Y_real[i] + Y_imag[i] * Y_imag[i]);
        // printf("%d\t%f\n", i, Y[i]);
    }
    
    for (int i = 0; i < nfft / 2; i++)
    {
        freq = (double)(i + 1) / (double)(nfft - 1) * fs;
        if (freq >= f1 && freq <= f2)
        {
            temp = 20 * log10(Y[i] / p0);
            count += pow(10, temp / 10.0);
            // printf("%d\t%f\n", i, Y[i]);
        }
    }

    count = 10 * log10(count);

    free(X);
    free(zeros);
    free(Y_real);
    free(Y_imag);
    free(Y);

    return count;
}

double Total_Magnitude_Calculate_File(char * path, int upper, int lower, const int f1, const int f2, const double p0, const int fs)
{
    const long dataSize = getDataSize_col(path, 2);
    const int splitSize = upper - lower + 1;
    
    const int k = (log((double)splitSize)/log(2.0)) + 1;
    const long nfft = pow(2, k);
    double freq = 0, count = 0, temp = 0;
    double *X1, *Xs;
    double *X, *zeros, *Y_real, *Y_imag, *Y;

    X1 = (double *)malloc(dataSize * sizeof(double));
    Xs = (double *)malloc(splitSize * sizeof(double));

    dataImport_col(path, 2, X1);
    dataSplit(X1, Xs, lower, upper);

    X = (double *)malloc(nfft * sizeof(double));
    zeros = (double *)malloc(nfft * sizeof(double));
    Y_real = (double *)malloc(nfft * sizeof(double));
    Y_imag = (double *)malloc(nfft * sizeof(double));
    Y = (double *)malloc(nfft * sizeof(double));

    dataExpand(Xs, X, nfft, splitSize);
    dataZeros(zeros, nfft);

    printf("nfft = %d\nk = %d\n", nfft, k);
    dataFFT(X, zeros, Y_real, Y_imag, nfft, k);

    for (int i = 0; i < nfft; i++)
    {
        Y_real[i] = Y_real[i] * 2 / nfft;
        Y_imag[i] = Y_imag[i] * 2 / nfft;
        Y[i] = sqrt(Y_real[i] * Y_real[i] + Y_imag[i] * Y_imag[i]);
        // printf("%d\t%f\n", i, Y[i]);
    }
    
    for (int i = 0; i < nfft / 2; i++)
    {
        freq = (double)(i + 1) / (double)(nfft - 1) * fs;
        if (freq >= f1 && freq <= f2)
        {
            temp = 20 * log10(Y[i] / p0);
            count += pow(10, temp / 10.0);
            // printf("%d\t%f\n", i, Y[i]);
        }
    }

    count = 10 * log10(count);

    free(X1);
    free(Xs);

    free(X);
    free(zeros);
    free(Y_real);
    free(Y_imag);
    free(Y);

    return count;
}