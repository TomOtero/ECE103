CC=gcc
IDIR = ./include/
FILES = super_star_trek.c $(IDIR)sst_functions.c
OUT_EXE = sst.exe

build: $(FILES)
		$(CC) -o $(OUT_EXE) $(FILES)

super_star_trek: super_star_trek.o sst_functions.o
	$(CC) super_star_trek.o sst_functions.o -o sst.exe

super_star_trek.o: super_star_trek.c ./include/sst_functions.h
	$(CC) -c super_star_trek.c

sst_functions.o: ./include/sst_functions.c ./include/sst_functions.h
	$(CC) -c ./include/sst_functions.c


.PHONY: clean
clean:
	rm -f *.o $(OUT_EXE)

rebuild: clean build