/**************************************************/
/* Program: exercise3       Date: 29-09-2023      */
/* Authors: Miguel Campo, Antonio Moroño          */
/*                                                */
/* Program that generates N random permutations   */
/* with M elementos each                          */
/*                                                */
/* Input: Command line                            */
/* -size: nomber of elements in each permutation  */
/* -numP: numero of permutations                  */
/* Output: 0: OK, -1: ERR                         */
/**************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutations.h"

int main(int argc, char **argv)
{
  int i;
  unsigned int n_perms, tamanio, j, k;
  int **perms = NULL, **histograma = NULL;
  FILE *f = NULL;

  srand(time(NULL));

  if (argc != 5)
  {
    fprintf(stderr, "Error in input parameters:\n\n");
    fprintf(stderr, "%s -size <int> -numP <int>\n", argv[0]);
    fprintf(stderr, "Where:\n");
    fprintf(stderr, " -size : number of elements in each permutation.\n");
    fprintf(stderr, " -numP : number of permutations.\n");
    exit(-1);
  }

  printf("Practice number 1, section 3\n");
  printf("Done by: Miguel Campo and Antonio Moroño\n");
  printf("Group: 1202\n");

  /* check command line la linea de comandos */
  for (i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-size") == 0)
    {
      tamanio = atoi(argv[++i]);
    }
    else if (strcmp(argv[i], "-numP") == 0)
    {
      n_perms = atoi(argv[++i]);
    }
    else
    {
      fprintf(stderr, "Wrong paramenter %s\n", argv[i]);
    }
  }

  histograma = (int **)malloc(sizeof(int *) * tamanio);

  if (histograma == NULL)
  {
    exit(-1);
  }

  for (j = 0; j < tamanio; j++)
  {

    histograma[j] = (int *)malloc(sizeof(unsigned int) * tamanio);
    if (histograma[j] == NULL)
    {
      for (j--; j >= 0; j--)
      {
        free(histograma[j]);
      }
      free(histograma);
      exit(-1);
    }

    for (k = 0; k < tamanio; k++)
    {
      histograma[j][k] = 0;
    }
  }

  perms = generate_permutations(n_perms, tamanio);

  if (perms == NULL)
  { /* error */
    printf("Error: Out of memory\n");
    for (j = 0; j < tamanio; j++)
    {
      for (k = 0; k < tamanio; k++)
      {
        fprintf(f, "%u\t", histograma[j][k]);
      }
      fprintf(f, "\n");
      free(histograma[j]);
    }
    free(histograma);
    exit(-1);
  }
  else
  {
    for (j = 0; j < n_perms; j++)
    { /* for each permutation */
      for (k = 0; k < tamanio; k++)
      {
        printf("%d ", perms[j][k]); /* print each element */
        histograma[k][perms[j][k] - 1]++;
      }
      printf("\n");
      free(perms[j]); /* free permutation */
    }

    free(perms); /* free permutations array */
  }

  if ((f = fopen("exercise3.log", "w")) == NULL)
  {
    for (j = 0; j < tamanio; j++)
    {
      free(histograma[j]);
    }
    free(histograma);
    for (j=0; j<tamanio; j++){
      free(perms[j]);
    }
    free(perms);
    exit(-1);
  }

  for (j = 0; j < tamanio; j++)
  {
    for (k = 0; k < tamanio; k++)
    {
      fprintf(f, "%u\t", histograma[j][k]);
    }
    fprintf(f, "\n");
    free(histograma[j]);
  }
  free(histograma);
  fclose(f);
  return 0;
}
