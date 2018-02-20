#include<stdio.h>
#include<stdlib.h>
#include<math.h>


float sfmin(float *y, int N){
  float zm = y[0];
  for (int i=1; i < N; ++i){
    if (y[i] < zm) zm = y[i];
  }
  return zm;
}

float sfmax(float *y, int N){
  float zm = y[0];
  for (int i=1; i < N; ++i){
    if (y[i] > zm) zm = y[i];
  }
  return zm;
}

typedef struct{
  int w, h;
  float left, right, top, bottom;
}svgmeta;

FILE *svg_init(int w, int h, float xmin, float xmax, float ymin, float ymax, const char *filename, svgmeta *svgm){

  float left, right, top, bottom;

  left   = xmin - 0.1*(xmax-xmin);
  right  = xmax + 0.1*(xmax-xmin);
  bottom = ymin - 0.1*(ymax-ymin);
  top    = ymax + 0.1*(ymax-ymin);

  svgm->w = w;
  svgm->h = h;
  svgm->left  = left;
  svgm->right = right;
  svgm->top = top;
  svgm->bottom = bottom;
  
// Begin SVG file
  FILE *f = NULL;
  f = fopen(filename, "w");
  if (f == NULL) {
    return NULL;
  }
  fprintf(f, "<html><head><meta charset='UTF-8'></head><body><svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\"");
  fprintf(f, " width=\"%dpx\" height=\"%dpx\"", w, h);
  fprintf(f, " viewBox=\"%f %f %f %f\"", left, bottom, right-left, top-bottom);
  fprintf(f, " preserveAspectRatio=\"none\">\n");
  fprintf(f, "<g transform=\"scale(1.0 -1.0)\">\n\n");
  
// Create axes
   fprintf(f, "<polyline points=\"%f,%f %f,%f\"", left, 0.0, right, 0.0);
   fprintf(f, " style=\"fill:none;stroke:red;stroke-width:%f\" />\n", (top-bottom)/h);
   fprintf(f, "<polyline points=\"%f,%f %f,%f\"", 0.0, bottom, 0.0, top);
   fprintf(f, " style=\"fill:none;stroke:red;stroke-width:%f\" />\n\n", (right-left)/w);
   return f;
}

void svg_add(FILE *f, float *x, float *y, int N, svgmeta *svg){
  

   fprintf(f, "<polyline points=\"");
   for (int n=0; n<N ; ++n) fprintf(f, "%f,%f ", x[n], y[n]);
   fprintf(f, "\" style=\"fill:none;stroke:red;stroke-width:%f\" />", (svg->right-svg->left)/svg->w);
   // Complete the HTML file
   return;
}


void svg_close(FILE *f){
  
  fprintf(f,"\n\n</g></svg></body></html>\n");
  fclose(f);
  return;
}

int main(void){

  float PI = 4.0*atan(1.0);
  printf("PI %f\n",PI);
  
  int   nx = 101;
  int   nz = 101;
  float dx = (2.0*PI)/(nx -1);
  float dz = (1.0*PI)/(nz -1);

  float *x = (float*)malloc(nx *sizeof(float));
  float *y = (float*)malloc(nx *sizeof(float));
  float *z = (float*)malloc(nz *sizeof(float));
  float *xz = (float*)malloc(nz *sizeof(float));

  for (int i=0; i < nx;++i){
    x[i]  = i*dx;
    xz[i] = i*dz; 
    y[i]  = sin(i*dx) * cos(i*dx);
    z[i]  = cos(i*dz);
  }
  
  svgmeta svgm;

  FILE * file = svg_init(640, 400, 0.0,7.0,-1.2,1.2,"sincos.html",&svgm);
  if ( file != NULL){
    svg_add(file,x,y,nx,&svgm);
    svg_add(file,xz,z,nz,&svgm);
    svg_close(file);
  }
  
  free(x);
  free(y);
  free(z);
  free(xz);
  
  return 0;
}









