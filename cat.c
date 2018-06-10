#include<stdio.h>
#include<stdlib.h>


int main(int argc, char *argv[]){

  if (argc == 1){
    printf("Usage: %s filename\n",argv[0]);
    return 1;
  }

  FILE *file = NULL;
  #if 0
  file = fopen(argv[1],"rb");
  fseek(file,0,SEEK_END);
  long int pos = ftell(file);
  fseek(file,0,SEEK_SET);
  char *content = (char *)malloc((pos+1));
  content[pos] = '\0';
  fread(content,1,pos,file);
  fclose(file);
  for(int i=0;i < pos;++i) printf("%c",content[i]);
  free(content);
  #endif
  
  int ii = 1;
  char buffer[2048] = {'\0'};
  while (argc--){
    
    file = fopen(argv[ii],"r");

    if (file == NULL) return 1;
    
    while (fgets(buffer,2048,file) != NULL){
      printf("%s",buffer);
    }

    //while ((c = fgetc(file)) != EOF){
    //  printf("%c",c);
    //}

    fclose(file);

    ii++;
  }

  return 0;
}
    
  
