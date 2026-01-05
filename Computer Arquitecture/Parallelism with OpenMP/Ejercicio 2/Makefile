CC = gcc
LIBS = -lgomp -lm
LIB_DIR =  
FLAGS = -g -Wall -D_GNU_SOURCE -fopenmp

.PHONY: clean all

all: pescalar_serie pescalar_par1 pescalar_par2 pescalar_par3 pescalar_threshold_automated clear

pescalar_serie: pescalar_serie.c arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

pescalar_par1: pescalar_par1.c arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

pescalar_par2: pescalar_par2.c arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)
	
pescalar_par3: pescalar_par3.c arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

pescalar_threshold_automated: pescalar_threshold_automated.c arqo4.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

edgeDetector: edgeDetector.c stb_image_write.h stb_image.h
	$(CC) $(FLAGS) -std=gnu99 $(LIB_DIR) -o $@ edgeDetector.c $(LIBS)

clean:
	rm -f *.o *~ pescalar_serie pescalar_par1 pescalar_par2 pescalar_par3 pescalar_threshold_automated
	
clear:
	rm -f *.o *~
