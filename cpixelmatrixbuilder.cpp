#include "cpixelmatrixbuilder.h"

#include <cassert>

CPixelMatrixBuilder::CPixelMatrixBuilder() {
  clear();
}


IPixelMatrix* CPixelMatrixBuilder::build() const {
  return new CPixelMatrix(matrix);
}


void CPixelMatrixBuilder::set_color(int row, int col, TColor color) {
  assert(0 <= row && row < matrix.size());
  assert(0 <= col && col < matrix[row].size());
  matrix[row][col] = max(color, matrix[row][col]);
}


TColor CPixelMatrixBuilder::get_color(int row, int col) const {
  assert(0 <= row && row < matrix.size());
  assert(0 <= col && col < matrix[row].size());
  return matrix[row][col];
}


void CPixelMatrixBuilder::clear() {
  matrix.fill(QVector<TColor>(RecognizerSettings::NeuronWidth(), 0),
              RecognizerSettings::NeuronHeight());
}
