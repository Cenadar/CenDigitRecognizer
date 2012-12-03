#include "cpixelmatrix.h"
#include "settings.h"
#include <cassert>

CPixelMatrix::CPixelMatrix(QVector<QVector<TColor> > matrix_): matrix(matrix_) {
  assert(matrix.size() == RSettings::neuronHeight());
  for(QVector<QVector<TColor> >::ConstIterator it = matrix.begin();
      it != matrix.end(); ++it)
        assert(it->size() == RSettings::neuronWidth());
}


TSignal CPixelMatrix::getSignal(int row, int col) const {
  if (RSettings::useLinearSmoothingForPixelMatrix()) {
    return matrix[row][col] > 0 ? matrix[row][col] : -10;
  } else {
    return matrix[row][col] > 0 ? 1 : -1;
  }
}
