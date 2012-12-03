#include "cdigitneuron.h"
#include "settings.h"
#include <cmath>

TSignal CDigitNeuron::getOutput(IPixelMatrix *input) const {
  TSignal output = 0, total = 0;

  for(int row = 0; row < RSettings::neuronHeight(); ++row)
    for(int col = 0; col < RSettings::neuronWidth(); ++col) {
      TSignal add = input->getSignal(row, col) * pow(abs(weight[row][col]), 0.5);
      if (weight[row][col] < 1e-9) add = -add;
      output += add;
      total += abs(weight[row][col]);
    }

  if (output < 1e-9) {
    return 0;
  } else {
    return output/total;
  }
}


void CDigitNeuron::teach(IPixelMatrix *input, bool correctness) {
  int modifier;
  if (correctness)
    modifier = RSettings::neuronTeachCorrectModifier();
  else
    modifier = RSettings::neuronTeachIncorrectModifier();

  for(int row = 0; row < RSettings::neuronHeight(); ++row)
    for(int col = 0; col < RSettings::neuronWidth(); ++col)
      weight[row][col] += modifier*input->getSignal(row, col);
}


int CDigitNeuron::getCoefficient(int row, int col) {
  return weight[row][col];
}
