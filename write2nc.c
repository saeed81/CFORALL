#include<stdio.h>
#include<stdlib.h>
#include<netcdf.h>

void write2dnc(char *filename, double *value, char *varname, int nt, int ny, int nx){
  int ncid;
  int idlat;
  int idlon;
  int idvar;
  int idt;
  int dimvar[3] = {0,0,0};
  nc_create(filename, NC_CLOBBER, &ncid);
  nc_def_dim(ncid, "t", nt, &idt);
  nc_def_dim(ncid, "y",  ny, &idlon);
  nc_def_dim(ncid, "x",  nx, &idlat);
  dimvar[0] = idt;
  dimvar[1] = idlat;
  dimvar[2] = idlon;
  nc_def_var(ncid, varname,  NC_DOUBLE, 3, dimvar, &idvar);
  nc_enddef(ncid);
  nc_put_var(ncid,idvar,&value[0]);
  nc_close(ncid);
  return;
}

int main(void){

  int nx = 10, ny = 20, nt = 1;
  double *value = (double *)malloc(nx *ny *sizeof(double));
  int ncount = 0; 
  for (int j=0; j < ny; ++j){
    for (int i=0; i < nx; ++i){
      value[ncount] = (double)(i *j);
      ncount++;
    }
  }
  
  write2dnc("test.nc", value, "rainfall",1, 10, 20);
  
  
  free(value);
  return 0;
}

  


