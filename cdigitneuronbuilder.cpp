#include "cdigitneuronbuilder.h"

CDigitNeuronBuilder::CDigitNeuronBuilder() {
  weight.fill(QVector<int>(RSettings::neuronWidth(), 0),
              RSettings::neuronHeight());
}


void CDigitNeuronBuilder::setValue(int row, int col, int value) {
  weight[row][col] = value;
}


IDigitNeuron* CDigitNeuronBuilder::build() const {
  return new CDigitNeuron(weight);
}
