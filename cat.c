#include<stdio.h>
#include<stdlib.h>


int main(int argc, char *argv[]){

  if (argc == 1){
    printf("Usage: %s filename\n",argv[0]);
    return 1;
  }
  FILE *file = NULL;
  int ii = 1;
  char buffer[2048] = {'\0'};
  while (argc--){
    
    file = fopen(argv[ii],"r");

    if (file == NULL) return 1;
    
    while (fgets(buffer,2048,file) != NULL){
      printf("%s",buffer);
    }

    fclose(file);

    ii++;
  }

  return 0;
}
    
  
