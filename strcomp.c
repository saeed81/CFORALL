int Strlen(char *sa){
  int len = 0;
  while(*sa != '\0'){
    len += 1;
    sa++;
  }
  return len;
}

int Strcmp(char *sa, char *sb){

  if (Strlen(sa) != Strlen(sb)){
    return 0;
  }
  while ((*sa == *sb) && *sa != '\0' && *sb != '\0' ){
    sa++;
    sb++;
  }

  if (*sa == '\0'){
    return 1;
  }
  else{
    return 0;
  }
}




