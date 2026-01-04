/***********************************************/
/* Program: exercise1     Date: 22-09-2023     */
/* Authors: Miguel Campo, Antonio Moroño       */
/*                                             */
/* Program that generates two random nunmbers  */
/* between two given numbers                   */
/*                                             */
/* Input: Command Line                         */
/* -limInf: lower limit                        */
/* -limSup: upper limit                        */
/* -numN: ammount of numbers                   */
/* Output: 0: OK, -1: ERR                      */
/***********************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutations.h"

int main(int argc, char **argv)
{
  int i, *barras, random, sum;
  unsigned int inf, sup, num, j;
  FILE *f;

  srand(time(NULL));

  if (argc != 7)
  {
    fprintf(stderr, "Input parameter error:\n\n");
    fprintf(stderr, "%s -limInf <int> -limSup <int> -numN <int>\n", argv[0]);
    fprintf(stderr, "Where:\n");
    fprintf(stderr, " -limInf : Lower limit.\n");
    fprintf(stderr, " -limSup : Upper limit.\n");
    fprintf(stderr, " -numN : ammout of mumbers to generate.\n");
    exit(-1);
  }
  printf("Practice no 1, Section 1\n");
  printf("Done by: Miguel Campo and Antonio Moroño\n");
  printf("Group: 1202\n");

  /* check command line */
  for (i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-limInf") == 0)
    {
      inf = atoi(argv[++i]);
    }
    else if (strcmp(argv[i], "-limSup") == 0)
    {
      sup = atoi(argv[++i]);
    }
    else if (strcmp(argv[i], "-numN") == 0)
    {
      num = atoi(argv[++i]);
    }
    else
    {
      fprintf(stderr, "Wrong Parameter %s \n", argv[i]);
    }
  }

  barras = (int *)malloc(sizeof(int) * (sup - inf + 1));
  if (!barras)
  {
    return -1;
  }

  for (j = 0; j < (sup - inf + 1); j++)
  {
    barras[j] = 0;
  }

  /* print data */
  for (j = 0; j < num; j++)
  {

    random = random_num(inf, sup);
    printf("%d\n", random);
    barras[random - inf]++;
  }

  if ((f = fopen("exercise1.log", "w")) == NULL)
  {
    return -1;
  }

  for (j = 0, sum = 0; j < (sup - inf + 1); j++)
  {
    fprintf(f, "%d\n", barras[j]);
    sum = barras[j] + sum;
  }

  printf("\nNumero de elementos totales %d\n", sum);

  fclose(f);

  free(barras);

  return 0;
}
