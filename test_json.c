#include"json_begend.c"
//#include"json.c"

int main(void){
  char *con   = json_load("my.json");
  //printf("%s\n",con);
  String sout = getvalue(con,"\"lan\"", "\"program\"","1","C",NULL);
  dumpstring(&sout,1);
  //char * sout = getvalue(con,"\"lan\"","\"speak\"","2",NULL);
  //dumpstring(&sout);
  //writeonscreen(sout);
  //if (sout != NULL)free(sout);
  if (con  != NULL)free(con);
  return 0;
}

    
