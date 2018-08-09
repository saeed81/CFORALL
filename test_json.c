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
  char *con   = json_load("sshconfig.json");

  String sout = getvalue(con,"\"experiment\"","\"NS01_GEBCO\"","\"desig\"",NULL);
 
  dumpstring(&sout);

  if (con  != NULL)free(con);
  
  return 0;
}

    
