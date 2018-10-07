#include<stdio.h>
#include<stdlib.h>

int  isleapyear(int year){
  return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}



int getlastday(int year, int month){
  int lastday_noleap[]  =  {31,28,31,30,31,30,31,31,30,31,30,31};
  int lastday_leap  []  =  {31,29,31,30,31,30,31,31,30,31,30,31};
  if (isleapyear(year) ) return lastday_leap  [month-1];
  if (!isleapyear(year)) return lastday_noleap[month-1];
  return 0;
}


int main(void){

  FILE *file = NULL;
  file = fopen("start_end.dat","w+");
  int y1 = 2016;
  int m1 = 1;
  int d1 = 16;
  int y2 = 2016;
  int m2 = 2;
  int d2 = 25;
  int yt = y1, mt = m1;
  int lastday = 0;
  int nfirst = 0;
  if (y1 < y2){
    while (yt < y2){
      lastday= getlastday(yt, mt);
      if (mt == m1 && nfirst == 0){
	fprintf(file,"%04d%02d%02d\t%04d%02d%02d\n",yt, mt,d1,yt, mt,lastday);
	nfirst = 1;
      }
      else if (mt == m1 && nfirst == 1){
	fprintf(file,"%04d%02d%02d\t%04d%02d%02d\n",yt, mt,1,yt, mt,lastday);
      }
      else if (mt != m1){
	fprintf(file,"%04d%02d%02d\t%04d%02d%02d\n",yt, mt,1,yt, mt,lastday);
      }
      mt++;
      if (mt > 12) {
	yt++;
	mt = 1;
      }
    }
    yt = y2;
    mt = 1;
    while (mt < m2){
      lastday= getlastday(yt, mt);
      fprintf(file,"%04d%02d%02d\t%04d%02d%02d\n",yt, mt,1,yt, mt,lastday);
      mt++;
    }
    mt = m2;
    lastday = d2;
    fprintf(file,"%04d%02d%02d\t%04d%02d%02d\n",yt, mt,1,yt, mt,lastday);
  }

  if (y1 == y2){
    if (m1 < m2){
      while(mt < m2){
	lastday= getlastday(y1, mt);
	fprintf(file,"%04d%02d%02d\t%04d%02d%02d\n",y1, mt,1,y1, mt,lastday);
	mt++;
      }
      mt = m2;
      lastday = d2;
      fprintf(file,"%04d%02d%02d\t%04d%02d%02d\n",y1, mt,1,y1, mt,lastday);
    }
  }
  if (y1 == y2){
    if (m1 == m2){
      fprintf(file,"%04d%02d%02d\t%04d%02d%02d\n",y1, m1,d1,y1, m1,d2);
    }
  }
  
  fclose(file);    
  
  return 0;
}
  
