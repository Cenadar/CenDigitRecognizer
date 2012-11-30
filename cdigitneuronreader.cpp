#include "cdigitneuronreader.h"
#include <QFile>
#include <cassert>
#include "settings.h"
#include "cdigitneuronbuilder.h"


IDigitNeuron* CDigitNeuronReader::read() {
  QDomElement root = parser->get_root("Neuron");
  QDomElement elem;

  elem = XMLParser::find_first_element(root, "Height");
  if (elem.text() != QString::number(RecognizerSettings::NeuronHeight()))
    throw QString("Uncorrect height");

  elem = XMLParser::find_first_element(root, "Width");
  if (elem.text() != QString::number(RecognizerSettings::NeuronWidth()))
    throw QString("Uncorrect width");

  IDigitNeuronBuilder* builder = new CDigitNeuronBuilder;
  for(int row = 0; row < RecognizerSettings::NeuronHeight(); ++row) {
    for(int col = 0; col < RecognizerSettings::NeuronWidth(); ++col) {
      elem = XMLParser::find_first_element(root, "SynapseR" +
                                           QString::number(row) +
                                          "C" + QString::number(col));
      builder->set_value(row, col, elem.text().toInt());
    }
  }

  IDigitNeuron* neuron = builder->build();
  delete builder;
  return neuron;
}
