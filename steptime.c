#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void showtime(struct tm *tdate){
  printf("%04d%02d%02d%02d%02d%02d\n",tdate->tm_year+1900,tdate->tm_mon+1,tdate->tm_mday,tdate->tm_hour,tdate->tm_min,tdate->tm_sec);
  return;
}
  
int main(void){

  struct tm tbegin = {0,0,0,1,1,118};
  struct tm tend   = {0,0,0,2,1,118};
  struct tm *info  = NULL;
  tbegin.tm_isdst = -1;
  tend.tm_isdst   = -1;

  time_t t1 = mktime(&tbegin);
  time_t t2 = mktime(&tend);
  time_t tt = t1; 
  time_t incr = 3600;
  while (tt < t2){
    info = localtime(&tt);
    showtime(info);
    tt += incr;
  }
  
  return 0;
}
