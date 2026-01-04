CC=gcc
CFLAGS=-Wall -ansi -pedantic
IFLAGS=-I./
LDFLAGS=-L./
LDLIBS=-lqueue
# -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca de hilos
LIBS = -lm -pthread

all: p4_e1 p4_e2 
######################################################################
# $@ es el item que aparece a la izquierda de ':'
# $< es el primer item en la lista de dependencias
# $^ son todos los archivos que se encuentran a la derecha de ':'(dependencias)
########################################################################
p4_e1:  p4_e1.o bstree.o vertex.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

p4_e2:  p4_e2.o vertex.o bstree.o search_queue.o file_utils.o
	$(CC) -o $@ $^ $(LDFLAGS)  $(LIBS)

################################################################################

p4_e1.o: p4_e1.c
	$(CC) -c $(CFLAGS) $^

p4_e2.o: p4_e2.c
	$(CC) -c $(CFLAGS) $^






vertex.o: vertex.c 
	$(CC) $(CFLAGS) -c vertex.c

	


file_utils.o: file_utils.c file_utils.h
	$(CC) -c $(CFLAGS) $^

queue.o: queue.c queue.h types.h
	$(CC) -c -o $@ $< $(CFLAGS)

stack.o: stack.c stack.h types.h
	$(CC) -c -o $@ $< $(CFLAGS)

list.o: list.c list.h types.h
	$(CC) -c -o $@ $< $(CFLAGS)

bstree.o:bstree.c bstree.h types.h
	$(CC) -c -o $@ $< $(CFLAGS)

search_queue.o: search_queue.c search_queue.h bstree.c bstree.h types.h
	$(CC) -c -o $@ $< $(CFLAGS)






#####################################################################################

clear:
	rm -rf *.o *h.gch

clean:
	rm -rf *.o p4_e1 

# This file can be included in the main Makefile with the command:
# include Makefile_ext

DATA = ./data
OUT = ./out

run_e1: p4_e1
	./p4_e1 ./data/data_vertex_50K.txt "id:88997 tag:Golf_de_Ibiza" normal
	@echo ""
	./p4_e1 ./data/data_vertex_50K.txt "id:88997 tag:Golf_de_Ibiza" sorted
	@echo ""
	./p4_e1 ./data/data_vertex_50K.txt "id:889907 tag:Golf_de_Ibiza" normal
	@echo ""
	./p4_e1 ./data/data_vertex_50K.txt "id:889907 tag:Golf_de_Ibiza" sorted

run_e2: p4_e2
	./p4_e2 $(DATA)/data_string_10.txt $(OUT)/data_string_10.out
	./p4_e2 $(DATA)/data_string_1K.txt $(OUT)/data_string_1K.out
	./p4_e2 $(DATA)/data_string_2K.txt $(OUT)/data_string_2K.out

# Remaining rules must be in main Makefile.
