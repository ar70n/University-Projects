CC = gcc #-ansi -pedantic
CFLAGS = #-Wall
EXE = voting
LIBS = -lpthread
all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % :  main.o misc.o handler.o #votante.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -o $@  $^ $(LIBS)

# votante.o : votante.c
# 	@echo "#---------------------------"
# 	@echo "# Generating $@ "
# 	@echo "# Depepends on $^"
# 	@echo "# Has changed $<"
# 	$(CC) $(CFLAGS) -c $< $(LIBS)

misc.o : misc.c
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $< $(LIBS)

handler.o : handler.c
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $< $(LIBS)



run:
	@echo Running voting
#	@rm /dev/shm/sem.semaforo
	@./voting 10 5

