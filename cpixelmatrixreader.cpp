#include "cpixelmatrixreader.h"
#include "cpixelmatrixbuilder.h"
#include "settings.h"
#include "domutils.h"

IPixelMatrix* CPixelMatrixReader::read() {
  QDomElement root = parser->getRoot("PixelMatrix");  
  QDomElement elem;

  elem = findFirstElement(root, QString("Height"));
  if (elem.text() != QString::number(RSettings::neuronHeight()))
    throw RMessages::incorrectExampleHeight();

  elem = findFirstElement(root, QString("Width"));
  if (elem.text() != QString::number(RSettings::neuronWidth()))
    throw RMessages::incorrectExampleWidth();


  IPixelMatrixBuilder* builder = new CPixelMatrixBuilder;
  QDomElement pixels = findFirstElement(root, "Pixels");
  QDomElement rowElem;
  for(int row = 0; row < RSettings::neuronHeight(); ++row) {
    rowElem = findFirstElement(pixels, "R" + QString::number(row));
    for(int col = 0; col < RSettings::neuronWidth(); ++col) {
      try {
        elem = findFirstElement(rowElem, "C" + QString::number(col));
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
