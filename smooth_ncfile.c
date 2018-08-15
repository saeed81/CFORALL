#include<stdio.h>
#include<stdlib.h>
#include<netcdf.h>

#define nx (1046)
#define ny (1238)
#define nt (1)

int main(void){
  
  int ncid, ncio;
  int  ibth = 0, ibf = 0;
  char *filename  =  "bfr_coef_abborre_omkorning.nc";
  char *filenameo =  "bfr_coef_smooth.nc";
  char *varname   =  "bfr_coef";
  size_t inbat[3] = {0,0,0};
  int   ireduce  = 1;
  float vreduce  = 0.50;
  nc_open(filename  , NC_NOWRITE,&ncid);
  nc_open(filenameo , NC_WRITE ,&ncio);
  nc_inq_varid(ncid, varname, &ibth);
  nc_inq_varid(ncio, varname, &ibf);
 
  float v0    = 0.0;
  float vn[4] = {0.0, 0.0, 0.0, 0.0}; 
  int   mn[4] = {0,0,0,0};
  float sum = 0.0;
  int ncount = 0;
  
  int niter = 50;
	  
  for (int iter=0; iter < niter; ++iter){
    for (int k=0; k< nt;++k){
      for (int j=1; j< (ny-1);++j){
	for (int i=1; i<(nx-1) ;++i){
	  v0 = 0.0; 
	  vn[0] = 0.0; vn[1] = 0.0; vn[2] = 0.0; vn[3] = 0.0;
	  mn[0] = 0;  mn[1]= 0; mn[2] = 0; mn[3] = 0;
	  sum = 0.0;
	  ncount = 0;
	  
	  inbat[0] = k;
	  inbat[1] = j;
	  inbat[2] = i;
	  //if (iter == 0) nc_get_var1(ncid, ibth, inbat, &v0);
	  if (iter >= 0 ) nc_get_var1(ncio, ibth, inbat, &v0);
	  
	
	  if (v0 != -127.0) {
	    inbat[0] = k;
	    inbat[1] = j+1;
	    inbat[2] = i;
	    //if (iter == 0) nc_get_var1(ncid, ibth, inbat, &vn[0]);
	    if (iter >= 0 ) nc_get_var1(ncio, ibth, inbat, &vn[0]);
	
	    inbat[0] = k;
	    inbat[1] = j-1;
	    inbat[2] = i;
	  
	    //if (iter == 0) nc_get_var1(ncid, ibth, inbat, &vn[1]);
	    if (iter >= 0 ) nc_get_var1(ncio, ibth, inbat, &vn[1]);
	
	    inbat[0] = k;
	    inbat[1] = j;
	    inbat[2] = i+1;
	    //if (iter == 0) nc_get_var1(ncid, ibth, inbat, &vn[2]);
	    if (iter >= 0 ) nc_get_var1(ncio, ibth, inbat, &vn[2]);
	

	    inbat[0] = k;
	    inbat[1] = j;
	    inbat[2] = i-1;

	    //if (iter == 0) nc_get_var1(ncid, ibth, inbat, &vn[3]);
	    if (iter >= 0 ) nc_get_var1(ncio, ibth, inbat, &vn[3]);
	

	    if (vn[0] == -127.0) mn[0] = 1;
	    if (vn[1] == -127.0) mn[1] = 1;
	    if (vn[2] == -127.0) mn[2] = 1;
	    if (vn[3] == -127.0) mn[3] = 1;
	    for (int ii=0 ; ii < 4; ++ii){
	      if (mn[ii] == 0){
		sum += vn[ii];
		ncount++;
	      }
	    }
	    sum += v0; 
	    if (ncount > 0) v0 = sum / (float)(ncount+1);
	    
	  }
	  inbat[0] = k;
	  inbat[1] = j;
	  inbat[2] = i;
	  nc_put_var1(ncio, ibf, inbat,&v0);
	}
      }
    }
  }

  if (ireduce){
    printf("we are doing reduction now \n");
    for (int k=0; k< nt;++k){
      for (int j=1; j< (ny-1);++j){
	for (int i=1; i<(nx-1) ;++i){
	  inbat[0] = k;
	  inbat[1] = j;
	  inbat[2] = i;
	  nc_get_var1(ncio, ibth, inbat, &v0);
	  if (v0 != -127.0){
	    v0 = (1-vreduce) * v0;
	    nc_put_var1(ncio, ibf, inbat,&v0);
	  }
	}
      }
    }
  }

  nc_close(ncid);
  nc_close(ncio);

  return 0;
}

