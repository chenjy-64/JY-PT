obj = Total_Magnitude.o Data_Processing.o

INCFLAG = -I ./header

Total_Magnitude: $(obj)
	gcc $(obj) -o Total_Magnitude

Total_Magnitude.o: Total_Magnitude.c
	gcc -c $(INCFLAG) Total_Magnitude.c

Data_Processing.o: Data_Processing.c
	gcc -c Data_Processing.c

.PHONY: clean
clean:
	del $(obj)