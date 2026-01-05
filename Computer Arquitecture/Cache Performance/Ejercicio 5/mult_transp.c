// P3 arq 2024-2025
// Suma elementos de una matríz por filas
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "arqo3.h"

void multiply(tipo **m1, tipo **m2, tipo **res, int n);

void traspose(tipo **m, int n);

void printMatrix(tipo **matrix, int n);


int main( int argc, char *argv[])
{
	int n;
	tipo **m1=NULL, **m2=NULL, **res=NULL;
	struct timeval fin,ini;

	printf("Word size: %ld bits\n",8*sizeof(tipo));

	if( argc!=2 )
	{
		printf("Error! Use: ./%s <matrix size>\n", argv[0]);
		return -1;
	}

	n=atoi(argv[1]);
	m1=generateMatrix(n);
	m2=generateMatrix(n);
    res = generateEmptyMatrix(n);
    
	if( !m1 || !m2 || !res)
	{
		return -1;
	}

    traspose(m2, n);

    /*printf("=== m1: ===\n");
    printMatrix(m1, n);
    printf("=== m2: ===\n");
    printMatrix(m2, n);*/

	gettimeofday(&ini,NULL);

	/* Main computation */
    multiply(m1, m2, res, n);
	/* End of computation */

	gettimeofday(&fin,NULL);
	printf("Execution time: %f\n", ((fin.tv_sec*1000000+fin.tv_usec)-(ini.tv_sec*1000000+ini.tv_usec))*1.0/1000000.0);
	
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
	
	for(i = 0;i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			for(k = 0; k < n; k++)
            {
                res[i][j] += m1[i][k] * m2[j][k];
            }
		}
	}

    }


void traspose(tipo **m, int n)
{
    int i, j;
    tipo aux;

    for(i = 0; i < n; i++)
    {
        for(j = i; j < n; j++)
        {
            aux = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = aux;
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