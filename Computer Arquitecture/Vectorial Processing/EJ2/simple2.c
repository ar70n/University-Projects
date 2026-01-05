#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define ARRAY_SIZE 2048

#ifndef NUMBER_OF_TRIALS 
#pragma message("NUMBER_OF_TRIALS not defined. Check compile command")
#define NUMBER_OF_TRIALS 1000000
#endif

/*
 * Statically allocate our arrays.  Compilers can
 * align them correctly.
 */
static double a[ARRAY_SIZE], b[ARRAY_SIZE], c;

int main(int argc, char *argv[]) {
    int i,t;
    struct timeval start, end;


    double m = 1.0001;

    /* Populate A and B arrays */
    for (i=0; i < ARRAY_SIZE; i++) {
        b[i] = i;
        a[i] = i+1;
    }

    // Obtener el tiempo de inicio
    if (gettimeofday(&start, NULL) != 0)
    {
        perror("gettimeofday");
        exit(1);
    }

    /* Perform an operation a number of times */
    for (t=0; t < NUMBER_OF_TRIALS; t++) {
        for (i=0; i < ARRAY_SIZE; i++) {
            c += m*a[i] + b[i];
        }
    }
    //printf("%f\n", c);

    // Obtener el tiempo de finalización
    if (gettimeofday(&end, NULL) != 0)
    {
        perror("gettimeofday");
        exit(1);
    }
    


    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("%lf\t|\t%lf\n", c, elapsed);

    return 0;
}
