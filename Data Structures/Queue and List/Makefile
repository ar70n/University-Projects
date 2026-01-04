CC=gcc
CFLAGS=-Wall -ansi -pedantic
IFLAGS=-I./
LDFLAGS=-L./
LDLIBS=-lqueue
# -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca de hilos
LIBS = -lm -pthread

all: p3_e1 p3_e2a p3_e3 clear #p2_e1b p2_e2 
######################################################################
# $@ es el item que aparece a la izquierda de ':'
# $< es el primer item en la lista de dependencias
# $^ son todos los archivos que se encuentran a la derecha de ':'(dependencias)
########################################################################
p3_e1:  p3_e1.o vertex.o delivery.o libp3_e2a.a
	$(CC) -o $@ $^ $(LDFLAGS) -lp3_e2a $(LIBS)

p3_e2a:  p3_e2a.o vertex.o delivery.o graph.o algorithms.o stack.o libp3_e2a.a
	$(CC) -o $@ $^ $(LDFLAGS) -lp3_e2a $(LIBS)

p3_e3:  p3_e3.o  list.o file_utils.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(LIBS)
################################################################################

p3_e1.o: p3_e1.c
	$(CC) -c $(CFLAGS) $^

p3_e2a.o: p3_e2a.c
	$(CC) -c $(CFLAGS) $^

p3_e3.o: p3_e3.c
	$(CC) -c $(CFLAGS) $^






vertex.o: vertex.c 
	$(CC) $(CFLAGS) -c vertex.c

graph.o: graph.c 
	$(CC) $(CFLAGS) -c graph.c
	
algorithms.o: algorithms.c
	$(CC) -c $(CFLAGS) $^

delivery.o: delivery.c
	$(CC) $(CFLAGS) -c delivery.c

###################################################################################################
###### Crea la biblioteca con las fuentes: stack.c creado por los alumnos en p2_e3. Y otros TADS
###################################################################################################

file_utils.o: file_utils.c file_utils.h
	$(CC) -c $(CFLAGS) $^

queue.o: queue.c queue.h types.h
	$(CC) -c -o $@ $< $(CFLAGS)

stack.o: stack.c stack.h types.h
	$(CC) -c -o $@ $< $(CFLAGS)

list.o: list.c list.h types.h
	$(CC) -c -o $@ $< $(CFLAGS)

libp3_e2a.a: queue.o file_utils.o
	$(AR) rcs $@ $^




#####################################################################################

clear:
	rm -rf *.o *h.gch

clean:
	rm -rf *.o p3_e1 

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

run:  p3_e2a 
	./p3_e2a city_graph.txt 100 700

runv:  p3_e2a 
	valgrind --leak-check=full ./p3_e2a city_graph.txt 100 700 -s

run2:  p3_e3 
	./p3_e3 grades.txt 1

