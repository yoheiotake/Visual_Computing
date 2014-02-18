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
  int M, N, Q,M1,N1,Q1;
  bool type;
  int val,val2;
  double thresh;

  // 引数が無い場合は使用法を表示．
  if (argc == 1) {
    cout << "用法: Threshold <入力ファイル名> <出力ファイル名>" << endl;
    cout << "      プログラムがしきい値を聞いてくるので入力する。" << endl;
    return 0;
  }

  // read image header
  readImageHeader(argv[1], N, M, Q, type);
  readImageHeader(argv[2], N1,M1,Q1, type);
  // N,Mは画像サイズ、Qは深さ。(値が0-255のPGMなら1)

  // allocate memory for the image array
  ImageType image(N, M, Q);
  ImageType image2(N1,M1,Q1);

  // read image
  readImage(argv[1], image); // 名前がargv[1]のpgm画像を読む．
  readImage(argv[2], image2);

  //cout << "Enter threshold: ";// 閾値を入力．
  //cin >> thresh;

  
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      image.getPixelVal(i,j,val);
      image2.getPixelVal(i,j,val2);
      image.setPixelVal(i,j,val - val2);
    }
  }

  writeImage(argv[3], image);

  return 0;
}
