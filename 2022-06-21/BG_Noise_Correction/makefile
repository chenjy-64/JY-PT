obj = example.o BG_Noise_Correction.o

INCFLAG = -I ./header

example: $(obj)
	gcc $(obj) -o example

example.o: example.c
	gcc -c $(INCFLAG) example.c

BG_Noise_Correction.o: BG_Noise_Correction.c
	gcc -c BG_Noise_Correction.c

.PHONY: clean
clean:
	del $(obj)