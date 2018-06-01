#include"json.c"

int main(void){
  char *con  = json_load("goteborg.json");
  char *val1 = getvalue(con,"2017040611",NULL);
  char *st1  = val1;
  if (st1 != NULL ){
    while (*st1 != '\0'){
      printf("%c",*st1);
      st1++;
    }
  }
  printf("\n");
  if (val1 != NULL)free(val1);
  if (con  != NULL)free(con);
  
  return 0;
}

    
