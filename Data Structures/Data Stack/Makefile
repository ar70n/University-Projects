CC=gcc
CFLAGS=-Wall -ansi -pedantic
IFLAGS=-I./
LDFLAGS=-L./
LDLIBS=-lp2_e3
# -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca de hilos
LIBS = -lm -pthread

all:libp2_e3.a p2_e1a  p2_e1b p2_e2 clear
######################################################################
# $@ es el item que aparece a la izquierda de ':'
# $< es el primer item en la lista de dependencias
# $^ son todos los archivos que se encuentran a la derecha de ':'(dependencias)
########################################################################
p2_e1a:  p2_e1a.o libp2_e3.a
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(LIBS)

p2_e1b:  p2_e1b.o vertex.o graph.o algorithms.o libp2_e3.a
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(LIBS)

p2_e2:  p2_e2.o vertex.o graph.o algorithms.o libp2_e3.a
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(LIBS)

################################################################################

p2_e1a.o: p2_e1a.c
	$(CC) -c $(CFLAGS) $^

p2_e1b.o: p2_e1b.c vertex.h algorithms.h
	$(CC) -c $(CFLAGS) $^

p2_e2.o: p2_e2.c
	$(CC) -c $(CFLAGS) $^





vertex.o: vertex.c 
	$(CC) $(CFLAGS) -c vertex.c

graph.o: graph.c 
	$(CC) $(CFLAGS) -c graph.c
	
algorithms.o: algorithms.c
	$(CC) -c $(CFLAGS) $^
####################################################################################
###### Crea la biblioteca con las fuentes: stack.c creado por los alumnos en p2_e3
###################################################################################

file_utils.o: file_utils.c file_utils.h
	$(CC) -c $(CFLAGS) $^

stack.o: stack.c stack.h types.h
	$(CC) -c -o $@ $< $(CFLAGS)

libp2_e3.a: stack.o file_utils.o
	$(AR) rcs $@ $^

#####################################################################################

clear:
	rm -rf *.o *h.gch

clean:
	rm -rf *.o libp2_e3.a  p2_e2 p2_e1a p2_e1b

runp2_e1a:  p2_e1a 
	./p2_e1a grades1.txt grades2.txt

runvp2_e1a: p2_e1a
	valgrind --leak-check=full ./p2_e1a grades1.txt grades2.txt

runp2_e1b: p2_e1b
	./p2_e1b cities1.txt cities2.txt

runvp2_e1b: p2_e1b
	valgrind --leak-check=full ./p2_e1b cities1.txt cities2.txt

runp2_e2: p2_e2
	./p2_e2 g2.txt 100 700

runvp2_e2: p2_e2
	valgrind --leak-check=full ./p2_e2 g2.txt 100 700

