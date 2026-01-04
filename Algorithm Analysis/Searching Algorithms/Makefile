#-----------------------
# IMPORTANTE: The values of the parameters for exercise?_test have to be conveniently adjusted.
# It is assumed that the name of the source files is exercise1.c, exercise2.c,...,exercise.h
#-----------------------

CC = gcc -ansi -pedantic
CFLAGS = -Wall
EXE = exercise1 exercise2

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o sorting.o search.o times.o permutations.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -o $@ $@.o sorting.o search.o times.o permutations.o

permutations.o : permutations.c permutations.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

sorting.o : sorting.c sorting.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

search.o : search.c search.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

times.o : times.c times.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

exercise1_test:
	@echo Running exercise1
	@./exercise1 -size 8 -key 1

exercise2_test:
	@echo Running exercise2
	@./exercise2 -num_min 100 -num_max 1000 -incr 100 -n_times 1 -outputFile exercise5.log

exercise1_testval:
	@echo Running exercise1
	@valgrind --leak-check=full ./exercise1 -size 8 -key 1

exercise2_testval:
	@echo Running exercise2
	@valgrind --leak-check=full ./exercise2 -num_min 1 -num_max 5 -incr 1 -n_times 1 -outputFile exercise5.log