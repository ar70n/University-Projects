CC = gcc
LIBS = -lgomp -lm
LIB_DIR =  
FLAGS = -g -Wall -D_GNU_SOURCE -fopenmp
OPT_FLAGS = -O3

.PHONY: clean all 

all: edgeDetector_MEDIAN edgeDetector_GAUSSIAN edgeDetector_serie_MEDIAN edgeDetector_serie_GAUSSIAN edgeDetector_MEDIAN_O3 edgeDetector_GAUSSIAN_O3 edgeDetector_serie_MEDIAN_O3 edgeDetector_serie_GAUSSIAN_O3

edgeDetector_MEDIAN: edgeDetector.c stb_image_write.h stb_image.h
	$(CC) $(FLAGS) -std=gnu99 $(LIB_DIR) -DTYPE_FILTER=MEDIAN -o edgeDetector_MEDIAN edgeDetector.c $(LIBS)

edgeDetector_GAUSSIAN: edgeDetector.c stb_image_write.h stb_image.h
	$(CC) $(FLAGS) -std=gnu99 $(LIB_DIR) -DTYPE_FILTER=GAUSSIAN -o edgeDetector_GAUSSIAN edgeDetector.c $(LIBS)

edgeDetector_serie_MEDIAN: edgeDetector_serie.c stb_image_write.h stb_image.h
	$(CC) $(FLAGS) -std=gnu99 $(LIB_DIR) -DTYPE_FILTER=MEDIAN -o edgeDetector_serie_MEDIAN edgeDetector_serie.c $(LIBS)

edgeDetector_serie_GAUSSIAN: edgeDetector_serie.c stb_image_write.h stb_image.h
	$(CC) $(FLAGS) -std=gnu99 $(LIB_DIR) -DTYPE_FILTER=GAUSSIAN -o edgeDetector_serie_GAUSSIAN edgeDetector_serie.c $(LIBS)

edgeDetector_MEDIAN_O3: edgeDetector.c stb_image_write.h stb_image.h
	$(CC) $(FLAGS) $(OPT_FLAGS) -fopt-info -std=gnu99 $(LIB_DIR) -DTYPE_FILTER=MEDIAN -o edgeDetector_MEDIAN_O3 edgeDetector.c $(LIBS)

edgeDetector_GAUSSIAN_O3: edgeDetector.c stb_image_write.h stb_image.h
	$(CC) $(FLAGS) $(OPT_FLAGS) -std=gnu99 $(LIB_DIR) -DTYPE_FILTER=GAUSSIAN -o edgeDetector_GAUSSIAN_O3 edgeDetector.c $(LIBS)

edgeDetector_serie_MEDIAN_O3: edgeDetector_serie.c stb_image_write.h stb_image.h
	$(CC) $(FLAGS) $(OPT_FLAGS) -fopt-info -std=gnu99 $(LIB_DIR) -DTYPE_FILTER=MEDIAN -o edgeDetector_serie_MEDIAN_O3 edgeDetector_serie.c $(LIBS)

edgeDetector_serie_GAUSSIAN_O3: edgeDetector_serie.c stb_image_write.h stb_image.h
	$(CC) $(FLAGS) $(OPT_FLAGS) -std=gnu99 $(LIB_DIR) -DTYPE_FILTER=GAUSSIAN -o edgeDetector_serie_GAUSSIAN_O3 edgeDetector_serie.c $(LIBS)

stb_image.h:
	@echo "Los ficheros de cabecera de stb se deberían descarga automáticamente"
	@echo "En caso de fallo, descargadlo de https://raw.githubusercontent.com/nothings/stb/master/stb_image.h"
	wget --no-check-certificate https://raw.githubusercontent.com/nothings/stb/master/stb_image.h

stb_image_write.h:
	@echo "Los ficheros de cabecera de stb se deberían descarga automáticamente"
	@echo "En caso de fallo, descargadlo de https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h"
	wget --no-check-certificate https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h

clean:
	rm -f *.o *~ edgeDetector_MEDIAN edgeDetector_GAUSSIAN edgeDetector_serie_MEDIAN edgeDetector_serie_GAUSSIAN edgeDetector_MEDIAN_O3 edgeDetector_GAUSSIAN_O3 edgeDetector_serie_MEDIAN_O3 edgeDetector_serie_GAUSSIAN_O3
    
clear:
	rm -f *.o *~ images/*_grad.jpg images/*_grad_denoised.jpg images/*_grey.jpg