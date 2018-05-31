#include"json.c"

int main(void){


  char *con = json_load("complex.json");

  if (0) getvalue(con,"properties","recording_artists",NULL);
  getvalue(con,"properties","id","type",NULL);

  if (con != NULL) free(con);

  return 0;
}

    
