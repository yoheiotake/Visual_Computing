#include <iostream>
#include <fstream>
//#include <stdlib.h>
#include <math.h>

using namespace std;

#include "image.h"

void readImageHeader(char[], int&, int&, int&, bool&);
void readImage(char[], ImageType&);
void writeImage(char[], ImageType&);

int main(int argc, char *argv[])
{
  int i, j, x, y; 
  int M, N, Q;
  bool type;
  int val;
  int sigma;
  double mval,vval;
  int m;
  mval = 0.0;
  vval = 0.0;
  m = 0;

  // read image header
  readImageHeader(argv[1], N, M, Q, type);
 
  // allocate memory for the image array
  ImageType image(N, M, Q);

  // read image
  readImage(argv[1], image);


  cout << "sigma:";
  cin >> sigma;

  m = 3 * sigma;
  double weight[2*m-1][2*m-1];

  for(i=-m+1; i < m; i++){
    for(j= -m+1; j< m; j++) {
      weight[i+(m-1)][j+(m-1)] = exp(-((i*i)+(j*j))/(2*(sigma*sigma)));
    }
  }
  
  for(y=0; y<N; y++){
    for(x=0; x<M; x++) {
      mval = 0.0;
      vval = 0.0;
  
      for(i=-m+1; i<m; i++){
	for(j=-m+1; j<m; j++) {
	  if((i+y >= 0 && i+y < N) && (j+x >= 0 && j+x < M)){
      	    image.getPixelVal(i+y, j+x, val);
	  }
	  else{
	    image.getPixelVal(y, x, val);
	  }
    	  mval += weight[i+(m-1)][j+(m-1)] * val;
	  vval += weight[i+(m-1)][j+(m-1)];
	}
      }

      val = (unsigned int)mval / vval;
      image.setPixelVal(y, x, val);
    }
  }

  //write image
  writeImage(argv[2], image);

  return 0;
}
