#include"json.c"

int main(void){
  char *con  = json_load("example_2.json");
  char *val1 = getvalue(con,"quiz","sport","q1","options",NULL);
  writeonscreen(val1);
  if (val1 != NULL)free(val1);
  if (con  != NULL)free(con);
  
  return 0;
}

    
