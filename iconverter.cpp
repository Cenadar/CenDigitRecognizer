#include "iconverter.h"
#include "domutils.h"
#include <cassert>

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

  QDomElement synapses = document.createElement("Synapses");
  QDomElement rowElem;
  for(int row = 0; row < RSettings::neuronHeight(); ++row) {
    rowElem = document.createElement("R" + QString::number(row));
    for(int col = 0; col < RSettings::neuronWidth(); ++col) {
      elem = document.createElement("C" + QString::number(col));

      text = document.createTextNode(QString::number(
                                       neuron->getCoefficient(row, col)));
      elem.appendChild(text);
      rowElem.appendChild(elem);
    }
    synapses.appendChild(rowElem);
  }
  assert(!synapses.isNull());
  assert(!result.isNull());
  result.appendChild(synapses);  

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

  QDomElement pixels = document.createElement("Pixel");
  QDomElement rowElem;
  for(int row = 0; row < RSettings::neuronHeight(); ++row) {
    rowElem = document.createElement("R" + QString::number(row));
    for(int col = 0; col < RSettings::neuronWidth(); ++col) {
      elem = document.createElement("C" + QString::number(col));
      text = document.createTextNode(QString::number(
                                       image->getSignal(row, col)));
      elem.appendChild(text);
      rowElem.appendChild(elem);
    }
    pixels.appendChild(rowElem);
  }
  result.appendChild(pixels);

  return result;
}
