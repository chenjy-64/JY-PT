#ifndef _DATA_PROCESSING_H
#define _DATA_PROCESSING_H

long getDataSize(const char * path);
long getDataSize_col(const char * path, const int column);
void dataImport(const char * path, double data[]);
void dataImport_col(const char * path, const int column, double data[]);
void dataExpand(const double data[], double data_Expand[], const long ndft, const long size);
void dataSplit(double data[], double split[], int lower, int upper);
void dataZeros(double data[], const long size);
void dataCentralize(double data[], const long size);
void dataABS(double data_real[], double data_imag[], double data_res[], int size);
void dataFFT(double data_real[], double data_imag[], double fftRes_real[], double fftRes_imag[], int n, int k);
void dataIFFT(double data_real[], double data_imag[], double ifftRes_real[], double ifftRes_imag[], int n, int k);
void dataHilbert(double data_real[], double data_imag[], double hilbertRes_real[], double hilbertRes_imag[], int n, int k);

void Hua_FFT(double data[], int n, int k, int fs, const char * path);
double Total_Magnitude_Calculate(double data[], const int size, const int f1, const int f2, const double p0, const int fs);
double Total_Magnitude_Calculate_File(char * path, int upper, int lower, const int f1, const int f2, const double p0, const int fs);

#endif