#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>

#include "bstree.h"
#include "search_queue.h"
#include "types.h"
#include "vertex.h"
#include "file_utils.h"

#define MAX_LINE 150

int string_compare(const void *c1, const void *c2){
  if (!c1 || !c2)
    return 0;

  return (strcmp((char *)c1, (char *)c2));
}


int main(int argc, char const *argv[]) {
  FILE *f_in = NULL, *f_out = NULL;
  SearchQueue *cola = NULL;
  int len;
  char *copy;
  char line[MAX_LINE];
  Status st=OK;
  if (argc != 3) {
    printf("Usage: %s input_file output_file \n", argv[0]);
    exit(EXIT_FAILURE);
  }
  f_in = fopen(argv[1], "r");
  if (!f_in) {
    exit(EXIT_FAILURE);
  }
  f_out = fopen(argv[2], "w");
  if (!f_out) {
    exit(EXIT_FAILURE);
  }

  cola=search_queue_new(string_print,string_compare);
  if(!cola){
    return -1;
  }

  while ((fgets(line, MAX_LINE, f_in)!= NULL) && st==OK) {
    len=strlen(line);
    copy=(char*)malloc((len+1)*sizeof(char));
    if(!copy){
      return 1;
    }
    strcpy(copy,line);
    st=search_queue_push(cola, copy);
  }
  search_queue_print(f_out, cola);

  fclose(f_in);
  fclose(f_out);
  search_queue_clean(cola);

  return 0;
}