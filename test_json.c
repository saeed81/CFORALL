#include"json.c"

int main(void){
  char *con  = json_load("animals-1.json");
  char *val1 = getvalue(con,"content","2","foods","likes","0",NULL);
  writeonscreen(val1);
  if (val1 != NULL)free(val1);
  if (con  != NULL)free(con);
  
  return 0;
}

    
