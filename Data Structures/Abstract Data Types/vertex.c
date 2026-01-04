#include "vertex.h"
#include <string.h>
#include <stdlib.h>

#define TAG_LENGTH 64

struct _Vertex {
  long id;
  char tag[TAG_LENGTH];
  Label state;
};


/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/
Status vertex_setField (Vertex *v, char *key, char *value);

Status vertex_setField (Vertex *v, char *key, char *value) {
  if (!key || !value) return ERROR;

  if (strcmp(key, "id") == 0) {
    return vertex_setId(v, atol(value));
  } else if (strcmp(key, "tag") == 0) {
    return vertex_setTag(v, value);
  } else if (strcmp(key, "state") == 0) {
    return vertex_setState(v, (Label)atoi(value));
  }

  return ERROR;
}

/*----------------------------------------------------------------------------------------*/
Vertex *vertex_initFromString(char *descr){
  char buffer[1024];
  char *token;
  char *key;
  char *value;
  char *p;
  Vertex *v;

  /* Check args: */
  if (!descr) return NULL;

  /* Allocate memory for vertex: */
  v = vertex_init();
  if (!v) return NULL;

  /* Read and tokenize description: */
  sprintf(buffer, "%s", descr);
  token = strtok(buffer, " \t\n");
  while (token) {
    p = strchr(token, ':');
    if (!p) continue;

    *p = '\0';
    key = token;
    value = p+1;

    vertex_setField(v, key, value);

    token = strtok(NULL, " \t\n");
  }

  return v;
}

/**  rest of the functions in vertex.h **/

Vertex * vertex_init ()
{
  Vertex *v;

  v = (Vertex*) malloc(sizeof(Vertex));
  if (v==NULL)
  {
    return NULL;
  }
  v->id=0;
  strcpy(v->tag,"");
  v->state=WHITE;

  return v;
}

void vertex_free (void * v)
{
  
  free(v);

}
long vertex_getId (const Vertex * v)
{
  if (v==NULL)
  {
    return -1;
  }
  return v->id;
}
const char* vertex_getTag (const Vertex * v)
{
  if (v==NULL)
  {
    return NULL;
  }
  return v->tag;
}
Label vertex_getState (const Vertex * v)
{
  if (v==NULL)
  {
    return ERROR_VERTEX;
  }
  return v->state;
}
Status vertex_setId (Vertex * v, const long id)
{
  if (v==NULL)
  {
    return ERROR;
  }
  v->id = id;
  return OK;
}
Status vertex_setTag (Vertex * v, const char * tag)
{
  if (v==NULL||tag==NULL)
  {
    return ERROR;
  }
  strcpy(v->tag,tag);
  return OK;
}

Status vertex_setState (Vertex * v, const Label state)
{
  if (v==NULL)
  {
    return ERROR;
  }
  v->state = state;
  return OK;
}
int vertex_cmp (const void * v1, const void * v2)
{
  const Vertex *v1aux= v1;
  const Vertex *v2aux= v2;

  if (v1==NULL || v2==NULL)
  {
    return 0;
  }

  if((v1aux)->id < v2aux->id)
  {
    return -1;
  }
  else if (v1aux->id > v2aux->id)
  {
    return 1;
  }
  else 
  {
    return strcmp(v1aux->tag,v2aux->tag);
  }

}
void * vertex_copy (const void * src)
{
  const Vertex* v2=src;
  Vertex* v;
  if (src==NULL)
  {
    return NULL;
  }
  v = vertex_init ();
  v->id = v2->id;
  strcpy(v->tag,v2->tag);
  v->state=v2->state;

  return v;
}
int vertex_print (FILE * pf, const void * v){
    const Vertex *v1 = v;
    
    if(!v1){
      return -1;
    }

    fprintf(pf, "[%ld, %s, %d]", v1->id, v1->tag, v1->state); 
    return 3;
}