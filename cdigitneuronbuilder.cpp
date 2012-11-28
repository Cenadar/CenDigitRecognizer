#include "cdigitneuronbuilder.h"

CDigitNeuronBuilder::CDigitNeuronBuilder() {
  weight.fill(QVector<int>(RecognizerSettings::NeuronWidth(), 0),
              RecognizerSettings::NeuronHeight());
}


void CDigitNeuronBuilder::set_value(int row, int col, int value) {
  weight[row][col] = value;
}


IDigitNeuron* CDigitNeuronBuilder::build() const {
  return new CDigitNeuron(weight);
}
