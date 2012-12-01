#include "cpixelmatrixbuilder.h"

#include <cassert>

CPixelMatrixBuilder::CPixelMatrixBuilder() {
  clear();
}


IPixelMatrix* CPixelMatrixBuilder::build() const {
  return new CPixelMatrix(matrix);
}


void CPixelMatrixBuilder::setColor(int row, int col, TColor color) {
  assert(0 <= row && row < matrix.size());
  assert(0 <= col && col < matrix[row].size());
  matrix[row][col] = max(color, matrix[row][col]);
}


TColor CPixelMatrixBuilder::getColor(int row, int col) const {
  assert(0 <= row && row < matrix.size());
  assert(0 <= col && col < matrix[row].size());
  return matrix[row][col];
}


void CPixelMatrixBuilder::clear() {
  matrix.fill(QVector<TColor>(RSettings::neuronWidth(), 0),
              RSettings::neuronHeight());
}
