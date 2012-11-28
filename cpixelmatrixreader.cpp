#include "cpixelmatrixreader.h"
#include "cpixelmatrixbuilder.h"
#include "settings.h"

IPixelMatrix* CPixelMatrixReader::read() {
  QDomElement root = parser->get_root("PixelMatrix");
  if (XMLParser::find_first_element(root, QString("Height")).text() !=
      QString::number(RecognizerSettings::NeuronHeight())) {
    throw QString("Height is incorrect");
  }
  if (XMLParser::find_first_element(root, QString("Width")).text() !=
      QString::number(RecognizerSettings::NeuronWidth())) {
    throw QString("Width is incorrect");
  }

  IPixelMatrixBuilder* builder = new CPixelMatrixBuilder;
  for(int row = 0; row < RecognizerSettings::NeuronHeight(); ++row) {
    for(int col = 0; col < RecognizerSettings::NeuronWidth(); ++col) {
      try {
        QString tagname = QString("PixelR") + QString::number(row) +
                          "C" + QString::number(col);
        QDomElement elem = XMLParser::find_first_element(root, tagname);

        TColor color = elem.text().toInt();
        builder->set_color(row, col, color);
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
