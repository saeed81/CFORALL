#include<stdlib.h>
#include<stdio.h>

typedef struct vector{
  int *aa;
  int size;
  int counter;
}vector; 


void vector_init(vector *vv){
  vv->size = 0;
  vv->counter = 0;
  vv->aa = NULL;
  return;
}


void vector_add(vector *vv, int b){
  if (vv->aa == NULL){
    vv->size = 2;
    vv->aa = (int *)malloc(vv->size * sizeof(int));
    if (vv->aa == NULL) return;
    vv->aa[vv->counter] = b;
    vv->counter += 1;
  }
  else{
    if (vv->counter < vv->size ){
      vv->aa[vv->counter] = b;
      vv->counter += 1;
    }
    else{
      vv->size *= 2;
      int *temp = NULL;
      int *temp = (int *) realloc(vv->aa, vv->size * sizeof(int));
      if (temp == NULL) return;
      vv->aa = temp;
      vv->aa[vv->counter] = b;
      vv->counter += 1;
    }
  }
}

void vector_remove(vector *vv, int index){
  if (vv->aa == NULL)  return;
  if (index > (vv->counter -1)) return;
  if (index == (vv->counter -1)){
    vv->counter -= 1;
    return;
  }
  for (int ii=index; ii < (vv->counter-1);++ii){
    vv->aa[ii] = vv->aa[ii+1];
  }
  vv->counter -= 1;

  return;
}
  
void vector_replace(vector *vv, int index, int newvalue){
  if (vv->aa == NULL)  return;
  if (index > (vv->counter -1)) return;
  vv->aa[index] = newvalue;
  return;
}

int vector_counter(vector *vv){
  return vv->counter;
}

int vector_size(vector *vv){
  return vv->size;
}

void vector_free(vector *vv){

  if (vv->aa != NULL)free(vv->aa);
  vv->aa = NULL;

  return;
}


void vector_dump(vector *vv){
  printf("=============================================\n");
  printf("vector_size = %-8d vector_counter = %-8d\n", vv->size, vv->counter);
  if(vv->aa == NULL){
    printf("input vector is empty\n");
    printf("=============================================\n");
  }else{
    for(int ii=0; ii < vv->counter; ++ii){
      printf("%d\n",vv->aa[ii]);
    }
    printf("=============================================\n");
  }
  return;
}

int main(void){

  vector vv;

  vector_init(&vv);

  for (int ii=0; ii < 16; ++ii){
    vector_add(&vv, ii);
  }
  
  printf("vector_size = %-8d vector_counter = %-8d\n", vector_size(&vv), vector_counter(&vv));  

  vector_dump(&vv);

  vector_replace(&vv,16,999);

  vector_remove(&vv,10);

  vector_dump(&vv);

  vector_remove(&vv,11);

  vector_replace(&vv,3,999);

  
  vector_replace(&vv,15,999);

  vector_dump(&vv);

  vector_free(&vv);

  return 0;
}
