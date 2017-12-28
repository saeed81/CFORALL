#include<stdio.h>
#include<stdlib.h>

#define with_alloc(type, varname, size, init, block)\
  do{\
  type *varname = NULL;\
  varname = (type *) malloc(sizeof(type)*size);\
  if (varname == NULL) return 1;\
  for(int ji=0; ji< size; ++ji){\
  varname[ji] = init;\
  }\
  block;\
  free(varname);\
  }while(0)

#define map(begin, end, block) (block)

int main(void){

  with_alloc(int, buffer, 10, 5, {FILE *fout =fopen("outbuff.dat","w");
      for (int ji=0; ji < 10; ++ji){
	fprintf(fout,"%d\n",buffer[ji]);
      };fclose(fout);});
 
  int aa[5] = {1,2,3,4,5};
  int *begin = aa;
  int *end = &aa[4];

  map(begin,end,{
      do {
	*begin *= 10;
	++begin;
      }while(begin != end);
    });

  for (int ji=0; ji < 5; ++ji) printf("%d\n",aa[ji]);


  return 0;
}


