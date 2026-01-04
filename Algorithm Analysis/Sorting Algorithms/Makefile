#-----------------------
# IMPORTANTE: The values of the parameters for exercise?_test have to be conveniently adjusted.
# It is assumed that the name of the source files is exercise1.c, exercise2.c,...,exercise.h
#-----------------------

CC = gcc -ansi -pedantic
CFLAGS = -Wall
EXE = exercise1 exercise2 exercise3 exercise4 exercise5 exercise4Inv exercise5Inv

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o sorting.o times.o permutations.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -o $@ $@.o sorting.o times.o permutations.o

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

 times.o : times.c times.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<
	
exercise1_testval:
	@echo Running exercise1
	@valgrind --leak-check=full ./exercise1 -limInf 5 -limSup 14 -numN 1000000

exercise2_testval:
	@echo Running exercise2
	@valgrind --leak-check=full ./exercise2 -size 5 -numP 1000000

exercise3_testval:
	@echo Running exercise3
	@valgrind --leak-check=full ./exercise3 -size 5 -numP 1000000

exercise4_testval:
	@echo Running exercise4
	@valgrind --leak-check=full ./exercise4 -size 15

exercise5_testval:
	@echo Running exercise5
	@valgrind --leak-check=full ./exercise5 -num_min 2000 -num_max 50000 -incr 2000 -numP 1 -outputFile exercise5.log

exercise1_test:
	@echo Running exercise1
	@./exercise1 -limInf 5 -limSup 14 -numN 1000000

exercise2_test:
	@echo Running exercise2
	@./exercise2 -size 5 -numP 1000000

exercise3_test:
	@echo Running exercise3
	@./exercise3 -size 5 -numP 1000000

exercise4_test:
	@echo Running exercise4
	@./exercise4 -size 15

exercise5_test:
	@echo Running exercise5
	@./exercise5 -num_min 100 -num_max 10000 -incr 100 -numP 1 -outputFile exercise5.log

exercise4Inv_test:
	@echo Running exercise4Inv
	@./exercise4Inv -size 15

exercise5Inv_test:
	@echo Running exercise5Inv
	@./exercise5Inv -num_min 100 -num_max 10000 -incr 100 -numP 1 -outputFile exercise5.log
