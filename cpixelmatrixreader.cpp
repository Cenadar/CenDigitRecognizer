#include "cpixelmatrixreader.h"
#include "cpixelmatrixbuilder.h"
#include "settings.h"
#include "domutils.h"

IPixelMatrix* CPixelMatrixReader::read() {
  QDomElement root = parser->getRoot("PixelMatrix");
  if (findFirstElement(root, QString("Height")).text() !=
      QString::number(RSettings::neuronHeight())) {
    throw QString("Height is incorrect");
  }
  if (findFirstElement(root, QString("Width")).text() !=
      QString::number(RSettings::neuronWidth())) {
    throw QString("Width is incorrect");
  }

  IPixelMatrixBuilder* builder = new CPixelMatrixBuilder;
  for(int row = 0; row < RSettings::neuronHeight(); ++row) {
    for(int col = 0; col < RSettings::neuronWidth(); ++col) {
      try {
        QString tagname = QString("PixelR") + QString::number(row) +
                          "C" + QString::number(col);
        QDomElement elem = findFirstElement(root, tagname);

        TColor color = elem.text().toInt();
        builder->setColor(row, col, color);
      } catch (QString message) {
        delete builder;
        throw message;
      }
    }
  }

  IPixelMatrix* result = builder->build();
  delete builder;
  return result;
}
