obj = Magnitude_Drop.o Data_Processing.o

INCFLAG = -I ./header

Magnitude_Drop: $(obj)
	gcc $(obj) -o Magnitude_Drop

Magnitude_Drop.o: Magnitude_Drop.c
	gcc -c $(INCFLAG) Magnitude_Drop.c

Data_Processing.o: Data_Processing.c
	gcc -c Data_Processing.c

.PHONY: clean
clean:
	del $(obj)