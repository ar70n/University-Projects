#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define BILLION  1E9

int main()
{

    FILE *f=NULL;
    struct timespec start, stop;
    double accum=0;
    long i,j;

    /* abre el fichero en modo escritura de texto */
    if (!(f=fopen("datos.bin","rb"))) {
        printf("Error al abrir el fichero\n");
        return 1;
    }

    /* inicializa el tiempo */
    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
      return 0;
    }

    /* escribe datos */
    for (i=0;i<100000000;i++) {
        if (fread(&j,sizeof(long),1,f)!=1) {
            fclose(f);
            return 1;
        }
    }

    /* vuelve a medir el tiempo */
    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      return 0;
    }

    /* imprime el tiempo de ejecucion */
    accum = ( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec )/BILLION;
    printf( "%.10lf segundos\n", accum );

    /* cierro el fichero y sale */
    fclose(f);
    return 0;
}