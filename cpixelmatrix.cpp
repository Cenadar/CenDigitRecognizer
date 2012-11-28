#include "cpixelmatrix.h"
#include "settings.h"

#include "cassert"

CPixelMatrix::CPixelMatrix(QVector<QVector<TColor> > matrix_): matrix(matrix_) {
  assert(matrix.size() == RecognizerSettings::NeuronHeight());
  for(QVector<QVector<TColor> >::ConstIterator it = matrix.begin();
      it != matrix.end(); ++it)
        assert(it->size() == RecognizerSettings::NeuronWidth());
}


TSignal CPixelMatrix::get_signal(int row, int col) const {
  return matrix[row][col] > 0 ? 1 : -1;
}


QDomElement CPixelMatrix::serialize(QDomDocument& document) const {
  QDomElement result = document.createElement("PixelMatrix");

  QDomElement elem;
  QDomText text;
  elem = document.createElement("Height");
  text = document.createTextNode(
        QString::number(RecognizerSettings::NeuronHeight()));
  elem.appendChild(text);
  result.appendChild(elem);

  elem = document.createElement("Width");
  text = document.createTextNode(
        QString::number(RecognizerSettings::NeuronWidth()));
  elem.appendChild(text);
  result.appendChild(elem);

  for(int row = 0; row < matrix.size(); ++row)
    for(int col = 0; col < matrix[row].size(); ++col) {
      QDomElement elem = document.createElement("PixelR" + QString::number(row) +
                                                "C" + QString::number(col));
      text = document.createTextNode(QString::number(matrix[row][col]));
      elem.appendChild(text);
      result.appendChild(elem);
    }

  return result;
}
