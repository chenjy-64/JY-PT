obj = Hilbert_Envelope_Spectrum.o Data_Processing.o

INCFLAG = -I ./header

Hilbert_Envelope_Spectrum: $(obj)
	gcc $(obj) -o Hilbert_Envelope_Spectrum

Hilbert_Envelope_Spectrum.o: Hilbert_Envelope_Spectrum.c
	gcc -c $(INCFLAG) Hilbert_Envelope_Spectrum.c

Data_Processing.o: Data_Processing.c
	gcc -c Data_Processing.c

.PHONY: clean
clean:
	del $(obj)