#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void showtime(struct tm *tdate){
  printf("%04d%02d%02d%02d%02d%02d\n",tdate->tm_year+1900,tdate->tm_mon+1,tdate->tm_mday,tdate->tm_hour,tdate->tm_min,tdate->tm_sec);
  return;
}

#define SHOWT(tdate) printf("%04d-%02d-%02d %02d%02d%02d\n",tdate->tm_year+1900,tdate->tm_mon+1,tdate->tm_mday,tdate->tm_hour,tdate->tm_min,tdate->tm_sec)


void advancedays(struct tm *tbegin,int nday){
  int secondperday = 24 * 3600;
  time_t t1 = mktime(tbegin);
  time_t tt = t1; 
  time_t incr = secondperday * nday;
  tt += incr;
  struct tm *info = localtime(&tt);
  SHOWT(info);
}

void advanceweeks(struct tm *tbegin,int nweek){
  int secondperweek = 24 * 3600 *7;
  time_t t1 = mktime(tbegin);
  time_t tt = t1; 
  time_t incr = secondperweek * nweek;
  tt += incr;
  struct tm *info = localtime(&tt);
  SHOWT(info);
}

int main(void){

  struct tm tbegin = {0,0,0,1,1,118};
  struct tm tend   = {0,0,0,1,1,118};
  struct tm *info  = NULL;
  tbegin.tm_isdst = -1;
  tend.tm_isdst   = -1;
  time_t t1 = mktime(&tbegin);
  time_t t2 = mktime(&tend);
  time_t tt = t1; 
  time_t incr = 3600;
  while (tt < t2){
    info = localtime(&tt);
    //showtime(info);
    SHOWT(info);
    tt += incr;
  }
  advancedays(&tbegin,28);
  advanceweeks(&tbegin,-1);
  
  return 0;
}
