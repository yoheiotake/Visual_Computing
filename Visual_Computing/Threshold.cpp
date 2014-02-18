#include <iostream>
#include <fstream>
//#include <stdlib.h>

using namespace std;

#include "image.h"

void readImageHeader(char[], int&, int&, int&, bool&);
void readImage(char[], ImageType&);
void writeImage(char[], ImageType&);

int main(int argc, char *argv[])
{
  int i, j; 
  int M, N, Q;
  bool type;
  int val;
  double thresh;

  // 引数が無い場合は使用法を表示．
  if (argc == 1) {
    cout << "用法: Threshold <入力ファイル名> <出力ファイル名>" << endl;
    cout << "      プログラムがしきい値を聞いてくるので入力する。" << endl;
    return 0;
  }

  // read image header
  readImageHeader(argv[1], N, M, Q, type);
  // N,Mは画像サイズ、Qは深さ。(値が0-255のPGMなら1)

  // allocate memory for the image array
  ImageType image(N, M, Q);

  // read image
  readImage(argv[1], image); // 名前がargv[1]のpgm画像を読む．

  //cout << "Enter threshold: ";// 閾値を入力．
  //cin >> thresh;

  int max = 0;
  int sum = 0;
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      image.getPixelVal(i,j,val);
      sum += val;
      if(max < val)
	max = val;
    }
  }

  thresh = (double)sum/(N*M);
  cout <<"File Name: "<< argv[1] << endl;
  cout <<"Pixel Heights: "<< N << endl;
  cout <<"Pixel Widths: "<< M << endl;
  cout <<"Max: "<< max << endl;
  cout <<"Average: "<< (int)(thresh + 0.5) << endl;
  // threshold image 
  for(i=0; i<N; i++)
    for(j=0; j<M; j++) {
      image.getPixelVal(i, j, val);
      if(val < thresh) 
	image.setPixelVal(i, j, 255);//White
      else
	image.setPixelVal(i, j, 0);//Black
    }

  // write image
  writeImage(argv[2], image);

  return 0;
}
