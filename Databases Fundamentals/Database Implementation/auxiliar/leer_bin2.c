#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define BILLION  1E9
#define MAX 100000000

int main()
{

    FILE *f=NULL;
    struct timespec start, stop;
    double accum=0;
    long *x=NULL;

    /* abre el fichero en modo escritura de texto */
    if (!(f=fopen("datos.bin","rb"))) {
        printf("Error al abrir el fichero\n");
        return 1;
    }

    /*reserva memoria */
    if (!(x=(long *)calloc(MAX,sizeof(long)))) {
      printf("Error al alocar\n");
      fclose(f);
      return 2;
    }
  

    /* inicializa el tiempo */
    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
      fclose(f);
      free(x);
      return 3;
    }

    /* escribe datos */
    if (fread(x,sizeof(long),MAX,f)!=MAX) {
        fclose(f);
        free(x);
        return 4;
    }
    printf("ultimo: %ld\n",x[MAX-1]);

    /* vuelve a medir el tiempo */
    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      fclose(f);
      free(x);
      return 3;
    }

    /* imprime el tiempo de ejecucion */
    accum = ( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec )/BILLION;
    printf( "%.10lf segundos\n", accum );

    /* cierro el fichero y sale */
    fclose(f);
    free(x);
    return 0;
}