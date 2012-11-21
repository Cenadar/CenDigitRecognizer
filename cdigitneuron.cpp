#include "cdigitneuron.h"
#include "settings.h"


CDigitNeuron::CDigitNeuron() {
  weight.fill(QVector<int>(RecognizerSettings::width(), 257),
                RecognizerSettings::height());
}


TSignal CDigitNeuron::get_output(IPixelMatrix *input) const {
  TSignal output = 0;

  for(int row = 0; row < RecognizerSettings::height(); ++row)
    for(int col = 0; col < RecognizerSettings::width(); ++col)
      output += weight[row][col] * input->get_pixel(row, col);

  return output;
}


QDomElement CDigitNeuron::serialize(QDomDocument &document,
                                    QMap<QString, QString> attributes) const {
  QDomElement result = document.createElement("Neuron");
  for(QMap<QString, QString>::Iterator it = attributes.begin();
      it != attributes.end(); ++it) {
    result.setAttribute(it.key(), *it);
  }

  for(int row = 0; row < weight.size(); ++row)
    for(int col = 0; col < weight[row].size(); ++col) {
      QDomElement elem = document.createElement("Synapse");
      elem.setAttribute("row", row);
      elem.setAttribute("col", col);
      QDomText text = document.createTextNode(QString::number(weight[row][col]));
      elem.appendChild(text);
      result.appendChild(elem);
    }

  return result;
}
