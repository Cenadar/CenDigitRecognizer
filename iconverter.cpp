#include "iconverter.h"
#include "domutils.h"

QDomElement CDigitNeuronConverter::convert(QDomDocument document) {
  QDomElement result = document.createElement("Neuron");

  QDomElement elem;
  QDomText text;
  elem = document.createElement("Height");
  text = document.createTextNode(QString::number(RSettings::neuronHeight()));
  elem.appendChild(text);
  result.appendChild(elem);

  elem = document.createElement("Width");
  text = document.createTextNode(QString::number(RSettings::neuronWidth()));
  elem.appendChild(text);
  result.appendChild(elem);

  for(int row = 0; row < RSettings::neuronHeight(); ++row) {
    for(int col = 0; col < RSettings::neuronWidth(); ++col) {
      elem = document.createElement("SynapseR" + QString::number(row) + "C" +
                                    QString::number(col));

      text = document.createTextNode(QString::number(
                                       neuron->getCoefficient(row, col)));
      elem.appendChild(text);
      result.appendChild(elem);
    }
  }

  return result;
}


QDomElement CPixelMatrixConverter::convert(QDomDocument document) {
  QDomElement result = document.createElement("PixelMatrix");

  QDomElement elem;
  QDomText text;
  elem = document.createElement("Height");
  text = document.createTextNode(QString::number(RSettings::neuronHeight()));
  elem.appendChild(text);
  result.appendChild(elem);

  elem = document.createElement("Width");
  text = document.createTextNode(QString::number(RSettings::neuronWidth()));
  elem.appendChild(text);
  result.appendChild(elem);

  for(int row = 0; row < RSettings::neuronHeight(); ++row) {
    for(int col = 0; col < RSettings::neuronWidth(); ++col) {
      QDomElement elem = document.createElement("PixelR" + QString::number(row) +
                                                "C" + QString::number(col));
      text = document.createTextNode(QString::number(
                                       image->getSignal(row, col)));
      elem.appendChild(text);
      result.appendChild(elem);
    }
  }

  return result;
}
