// P3 arq 2024-2025
// Multiplica dos matrices cuadradas convencionalmente
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "arqo3.h"

void multiply(tipo **m1, tipo **m2, tipo **res, int n);
void printMatrix(tipo **matrix, int n);

int main( int argc, char *argv[])
{
	int n;
	tipo **m1=NULL, **m2=NULL, **res=NULL;
	struct timeval fin,ini;

	//printf("Word size: %ld bits\n",8*sizeof(tipo));

	if( argc!=2 )
	{
		printf("Error! Use: ./%s <matrix size>\n", argv[0]);
		return -1;
	}

	n=atoi(argv[1]);
	m1=generateMatrix(n);
	m2=generateMatrix(n);
    res = generateEmptyMatrix(n);
    
	if( !m1 || !m2)
	{
		return -1;
	}

    /*printf("=== m1: ===\n");
    printMatrix(m1, n);
    printf("=== m2: ===\n");
    printMatrix(m2, n);*/
	
	gettimeofday(&ini,NULL);    

	/* Main computation */
    multiply(m1, m2, res, n);
	/* End of computation */    

	gettimeofday(&fin,NULL);
	printf("%f\n", ((fin.tv_sec*1000000+fin.tv_usec)-(ini.tv_sec*1000000+ini.tv_usec))*1.0/1000000.0);

	/*printf("=== res: ===\n");
    printMatrix(res, n);*/
	
	freeMatrix(m1);
    freeMatrix(m2);
    freeMatrix(res);
	return 0;
}


void multiply(tipo **m1, tipo **m2, tipo **res, int n)
{
	int i,j,k;
	tipo tmp;
	
	#pragma omp parallel for private(j,k,tmp)
	for(i = 0;i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			tmp = 0;
			for(k = 0; k < n; k++)
            {
                tmp += m1[i][k] * m2[k][j];
            }
			res[i][j] = tmp;
		}
		
	}

}

void printMatrix(tipo **matrix, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}