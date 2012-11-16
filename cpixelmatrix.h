#ifndef CPIXELMATRIX_H
#define CPIXELMATRIX_H

#include <vector>

using namespace std;

typedef unsigned char TColor;

class IPixelMatrix {
 public:
  virtual ~IPixelMatrix() = 0;

  virtual TColor get_pixel(int x, int y) = 0;
};


class CPixelMatrix: public IPixelMatrix {
 public:
  CPixelMatrix();
  ~CPixelMatrix() {}

  TColor get_pixel(int x, int y);
 private:
  vector<vector<TColor> > matrix;
};

#endif // CPIXELMATRIX_H
