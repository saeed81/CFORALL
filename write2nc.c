#include<stdio.h>
#include<stdlib.h>
#include<netcdf.h>

void write2dnc(char *filename, double *value, char *varname, int ny, int nx){
  int ncid;
  int idlat;
  int idlon;
  int idvar;
  int dimvar[2] = {0,0};
  nc_create(filename, NC_CLOBBER, &ncid);
  nc_def_dim(ncid, "y",  ny, &idlat);
  nc_def_dim(ncid, "x",  nx, &idlon);
  dimvar[0] = idlat;
  dimvar[1] = idlon;
  nc_def_var(ncid, varname,  NC_DOUBLE, 2, dimvar, &idvar);
  nc_enddef(ncid);
  nc_put_var(ncid,idvar,&value[0]);
  nc_close(ncid);
  return;
}

int main(void){

  int nx = 10, ny = 20;
  double *value = (double *)malloc(nx *ny *sizeof(double));
  int ncount = 0; 
  for (int j=0; j < ny; ++j){
    for (int i=0; i < nx; ++i){
      value[ncount] = (double)(i *j);
      ncount++;
    }
  }
  
  write2dnc("test.nc", value, "rainfall",ny, nx);
  
  
  free(value);
  return 0;
}

  


