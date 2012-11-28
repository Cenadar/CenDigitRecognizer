#include "cdigitneuron.h"
#include "settings.h"
#include <cmath>

TSignal CDigitNeuron::get_output(IPixelMatrix *input) const {
  TSignal output = 0;  

  for(int row = 0; row < RecognizerSettings::NeuronHeight(); ++row)
    for(int col = 0; col < RecognizerSettings::NeuronWidth(); ++col) {
      TSignal add = weight[row][col] * pow(abs(input->get_signal(row, col)), 0.5);
      if (input->get_signal(row, col) < 1e-9) add = -add;
      output += add;
    }

  if (output < 0) return 0;
  return output;
}


void CDigitNeuron::teach(IPixelMatrix *input, bool correctness) {
  int modifier;
  if (correctness)
    modifier = RecognizerSettings::NeuronTeachCorrectModifier();
  else
    modifier = RecognizerSettings::NeuronTeachIncorrectModifier();

  for(int row = 0; row < RecognizerSettings::NeuronHeight(); ++row)
    for(int col = 0; col < RecognizerSettings::NeuronWidth(); ++col)
      weight[row][col] += modifier*input->get_signal(row, col);
}


QDomElement CDigitNeuron::serialize(QDomDocument &document) const {
  QDomElement result = document.createElement("Neuron");

  QDomElement elem;
  QDomText text;
  elem = document.createElement("Height");
  text = document.createTextNode(
        QString::number(RecognizerSettings::NeuronHeight()));
  elem.appendChild(text);
  result.appendChild(elem);

  elem = document.createElement("Width");
  text = document.createTextNode(
        QString::number(RecognizerSettings::NeuronWidth()));
  elem.appendChild(text);
  result.appendChild(elem);

  for(int row = 0; row < weight.size(); ++row)
    for(int col = 0; col < weight[row].size(); ++col) {
      elem = document.createElement("SynapseR" + QString::number(row) + "C" +
                                    QString::number(col));

      text = document.createTextNode(QString::number(weight[row][col]));
      elem.appendChild(text);
      result.appendChild(elem);
    }

  return result;
}
