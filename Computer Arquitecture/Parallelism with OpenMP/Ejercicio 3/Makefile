CC = gcc
LIBS = -lgomp -lm
LIB_DIR =  
FLAGS = -g -Wall -D_GNU_SOURCE -fopenmp

.PHONY: clean all

all: mult_normal_serie mult_normal_med mult_normal_int mult_normal_ext clear

mult_normal_serie: mult_normal_serie.c arqo3.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

mult_normal_med: mult_normal_med.c arqo3.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

mult_normal_int: mult_normal_int.c arqo3.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)

mult_normal_ext: mult_normal_ext.c arqo3.c
	$(CC) $(FLAGS) $(LIB_DIR) -o $@ $^ $(LIBS)



stb_image.h:
	@echo "Los ficheros de cabecera de stb se deberían descarga automáticamente"
	@echo "En caso de fallo, descargadlo de https://raw.githubusercontent.com/nothings/stb/master/stb_image.h"
	wget --no-check-certificate https://raw.githubusercontent.com/nothings/stb/master/stb_image.h

stb_image_write.h:
	@echo "Los ficheros de cabecera de stb se deberían descarga automáticamente"
	@echo "En caso de fallo, descargadlo de https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h"
	wget --no-check-certificate https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h

clean:
	rm -f *.o *~ mult_normal_serie mult_normal_med mult_normal_int mult_normal_ext
	
clear:
	rm -f *.o *~
