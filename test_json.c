#include"json_begend.c"


void dumpstring(String *str){
  if ((str->beg != NULL) && (str->end != NULL)){
    printf("TYPE is %c\n",str->type);
    printf("Value is = \t");
    for (char *it =str->beg; it <= str->end;++it)printf("%c",*it);
  }
  printf("\n");
}

int main(void){
  char *con   = json_load("complex.json");
  String sout = getvalue(con,"\"medications\"","0","\"aceInhibitors\"","0","\"dose\"",NULL);
dumpstring(&sout);
//writeonscreen(sout);
if (con  != NULL)free(con);
//if (sout  != NULL)free(sout);
  
  return 0;
}

    
