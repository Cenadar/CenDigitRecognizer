#include "cdigitneuronreader.h"
#include <QFile>
#include <cassert>
#include "settings.h"
#include "cdigitneuronbuilder.h"

IDigitNeuron* CDigitNeuronReader::read() {
  QDomElement root = parser->getRoot("Neuron");
  QDomElement elem;

  elem = XMLParser::findFirstElement(root, "Height");
  if (elem.text() != QString::number(RSettings::neuronHeight()))
    throw QString("Uncorrect height");

  elem = XMLParser::findFirstElement(root, "Width");
  if (elem.text() != QString::number(RSettings::neuronWidth()))
    throw QString("Uncorrect width");

  IDigitNeuronBuilder* builder = new CDigitNeuronBuilder;
  for(int row = 0; row < RSettings::neuronHeight(); ++row) {
    for(int col = 0; col < RSettings::neuronWidth(); ++col) {
      elem = XMLParser::findFirstElement(root, "SynapseR" +
                                           QString::number(row) +
                                          "C" + QString::number(col));
      builder->setValue(row, col, elem.text().toInt());
    }
  }

  IDigitNeuron* neuron = builder->build();
  delete builder;
  return neuron;
}
