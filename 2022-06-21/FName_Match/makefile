obj = FName_Match.o Data_Processing.o

INCFLAG = -I ./header

FName_Match: $(obj)
	gcc $(obj) -o FName_Match

FName_Match.o: FName_Match.c
	gcc -c $(INCFLAG) FName_Match.c

Data_Processing.o: Data_Processing.c
	gcc -c Data_Processing.c

.PHONY: clean
clean:
	del $(obj)