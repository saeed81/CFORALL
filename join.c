#include<stdio.h>
#include<stdlib.h>

static int lenstr(char *str){

  int result=0;
  if (str){
    while(*str != '\0'){
      result++;
      str++;
    }
  }
  return result;
}

static char *join(char **ar, char FS){

  char *result = NULL;
  
  int len = 0;
  int nel  = 0;
  
  for (char **pt = ar; *pt;++pt){
    len += lenstr(*pt);
    nel++;
  }
  if (nel > 0){
    
    result = (char *)malloc(len + (nel-1) + 1);
    int i=0;
    
    for (char **pt = ar; *pt;++pt){
      while(**pt != '\0'){
	*(result +i) =**pt;
	(*pt)++;
	i++;
      }
      *(result +i) = FS;
      i++;
    }
    *(result +i-1) = '\0';
  }
  
  return result;
}


int main(void){

  char *vars[] = {"SSH","SSS","SST","ICECON","ICETHICKNESS",NULL};
  
  char *var_out = join(vars,'*');
  
  printf("%s\n",var_out);
  
  free(var_out);

  return 0;

}

