#include<stdio.h>
#include<stdlib.h>
#include<netcdf.h>

#define nx (1046)
#define ny (1238)
#define nt (1)

int main(void){

  int ncid;
  int ilat = 0, ilon = 0, ibth = 0;
  
  char *filename =  "bfr_coef.nc";
  char *lat      = "Y";
  char *lon      = "X";
  char *varname  = "bfr_coef";
  
  size_t inlat[1] = {0};
  size_t inlon[1] = {0};
  size_t inbat[3] = {0};
  const size_t *ptlat = &inlat[0]; 
  const size_t *ptlon = &inlon[0];
  
  float vallat = 0.0f, vallon = 0.0f, valbat   = 0;
  int i1 = 190, i2 = 350, j1 = 350, j2 = 480;
  if ( (i2 < i1) || (j2 < j1) ) return 1;

  nc_open(filename, NC_WRITE,&ncid);
  nc_inq_varid(ncid, lat, &ilat);
  nc_inq_varid(ncid, lon, &ilon);
  nc_inq_varid(ncid, varname, &ibth);
  
#if 0
  for (int i=0; i < ny;++i){
    inlat[0] = i;
    ptlat= &inlat[0];
    nc_get_var1(ncid, ilat, ptlat , &vallat);
    printf("%f\n",vallat);
  }
  for (int j=0; j< nx;++j){
    inlon[0] = j;
    ptlon = &inlon[0];
    nc_get_var1(ncid, ilon, ptlon , &vallon);
    printf("%f\n",vallon);
 
  }
  #endif
  for (int k=0; k< nt;++k){
  for (int j=0; j< ny;++j){
  for (int i=0; i<nx ;++i){
  inbat[0] = k;
  inbat[1] = j;
  inbat[2] = i;
  if ( (i >= i1) && (i <= i2) && (j >= j1) && (j <= j2)){
    nc_get_var1(ncid, ibth, inbat, &valbat);
    valbat = -100;
    nc_put_var1(ncid, ibth, inbat,&valbat);
  }
	//printf("%d \t %d \t%f\n",j,i,(float)valbat);
  }
  }
}
  #if 0
  inbat[0] = 0;
  inbat[1] = 1114;
  inbat[2] = 760;
  nc_get_var1(ncid, ibth, inbat, &valbat);
  printf("%ld \t %ld \t%f\n",inbat[1],inbat[2],(float)valbat);
  printf("id lat is %d\n",ilat);
  printf("id lon is %d\n",ilon);
  printf("id bth is %d\n",ibth);
  #endif

  nc_close(ncid);

  return 0;
}

