#include "cdigitneuronreader.h"
#include <QFile>
#include <cassert>
#include "settings.h"
#include "cdigitneuronbuilder.h"
#include "domutils.h"

IDigitNeuron* CDigitNeuronReader::read() {
  QDomElement root = parser->getRoot("Neuron");
  QDomElement elem;

  elem = findFirstElement(root, "Height");
  if (elem.text() != QString::number(RSettings::neuronHeight()))
    throw RMessages::incorrectNeuronHeight();

  elem = findFirstElement(root, "Width");
  if (elem.text() != QString::number(RSettings::neuronWidth()))
    throw RMessages::incorrectNeuronWidth();

  IDigitNeuronBuilder* builder = new CDigitNeuronBuilder;
  QDomElement synapses = findFirstElement(root, "Synapses");
  QDomElement rowElem;
  for(int row = 0; row < RSettings::neuronHeight(); ++row) {
    rowElem = findFirstElement(synapses, "R" + QString::number(row));
    for(int col = 0; col < RSettings::neuronWidth(); ++col) {
      try {
        elem = findFirstElement(rowElem, "C" + QString::number(col));
        builder->setValue(row, col, elem.text().toInt());
      } catch (QString message) {
        delete builder;
        throw message;
      }
    }
  }

  IDigitNeuron* neuron = builder->build();
  delete builder;
  return neuron;
}
