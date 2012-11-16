#include "cpixelmatrix.h"
#include "settings.h"


CPixelMatrix::CPixelMatrix() {
  matrix.assign(RecognizerSettings::height,
                vector<TColor>(RecognizerSettings::width,
                               0));
}


TColor CPixelMatrix::get_pixel(int x, int y) {
  return matrix[x][y];
}
