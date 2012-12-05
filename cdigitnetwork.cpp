#include "cdigitnetwork.h"
#include <cassert>

CDigitNetwork::~CDigitNetwork() {
  for(int i = 0; i < 10; ++i)
    if (neurons[i] != NULL)
      delete neurons[i];
}


void CDigitNetwork::setNeuron(int digit, IDigitNeuronReader *reader) {
  assert(0 <= digit && digit < 10);
  if (neurons[digit] != NULL) delete neurons[digit];
  neurons[digit] = reader->read();
}


QVector<TSignal> CDigitNetwork::recognize(IPixelMatrix *image) {
  QVector<TSignal> result(10);
  for(int i = 0; i < 10; ++i)
    if (neurons[i] == NULL) {
      result[i] = 0;
    } else {
      try {
        result[i] = neurons[i]->getOutput(image);
      } catch (QString message) {
        result[i] = 0;
      }
    }
  delete image;
  return result;
}


int CDigitNetwork::recognizeOne(QVector<TSignal> recognition) {
  int digit = -1;
  for(int i = 0; i < 10; ++i)
    if (recognition[i] > 0 && recognition[i] > recognition[digit])
      digit = i;
  return digit;
}


int CDigitNetwork::recognizeOne(IPixelMatrix* image) {
  return recognizeOne(recognize(image));
}


void CDigitNetwork::teach(IPixelMatrix *image, int digit) {
  for(int i = 0; i < 10; ++i)
    if (neurons[i] != NULL)
      neurons[i]->teach(image, digit == i);
}


IDigitNeuron* CDigitNetwork::getNeuron(int digit) {
  assert(0 <= digit && digit < 10);
  return neurons[digit];
}


QVector<IDigitNeuron*> CDigitNetwork::getNeurons() {
  return neurons;
}
