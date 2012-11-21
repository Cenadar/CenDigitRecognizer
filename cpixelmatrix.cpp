#include "cpixelmatrix.h"
#include "settings.h"

#include "cassert"

CPixelMatrix::CPixelMatrix(QVector<QVector<TColor> > matrix_): matrix(matrix_) {
  assert(matrix.size() == RecognizerSettings::height());
  for(QVector<QVector<TColor> >::ConstIterator it = matrix.begin();
      it != matrix.end(); ++it)
        assert(it->size() == RecognizerSettings::width());
}


TColor CPixelMatrix::get_pixel(int row, int col) const {
  return matrix[row][col];
}


QDomElement CPixelMatrix::serialize(QDomDocument &document,
                                    QMap<QString, QString> attributes) const {
  //TODO: include attributes

  QDomElement result = document.createElement("PixelMatrix");
  for(int row = 0; row < matrix.size(); ++row)
    for(int col = 0; col < matrix[row].size(); ++col) {
      QDomElement elem = document.createElement("Pixel");
      elem.setAttribute("row", row);
      elem.setAttribute("col", col);
      elem.setNodeValue(QString(matrix[row][col]));
      result.appendChild(elem);
    }

  return result;
}
