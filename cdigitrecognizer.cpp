#include "cdigitrecognizer.h"
#include <cassert>

CDigitRecognizer::~CDigitRecognizer() {
  for(int i = 0; i < 10; ++i)
    if (neurons[i] != NULL)
      delete neurons[i];
}


void CDigitRecognizer::set_neuron(int digit, IDigitNeuronReader *reader) {
  assert(0 <= digit && digit < 10);
  if (neurons[digit] != NULL)
    delete neurons[digit];
  neurons[digit] = reader->read();
}


QVector<TSignal> CDigitRecognizer::recognize(IPixelMatrix *image) {
  QVector<TSignal> result(10);
  for(int i = 0; i < 10; ++i)
    if (neurons[i] == NULL) {
      result[i] = 0;
    } else {
      try {
        result[i] = neurons[i]->get_output(image);
      } catch (QString message) {
        result[i] = 0;
      }
    }
  delete image;
  return result;
}


void CDigitRecognizer::teach(IPixelMatrix *image, int digit) {
  for(int i = 0; i < 10; ++i)
    if (neurons[i] != NULL)
      neurons[i]->teach(image, digit == i);
}


IDigitNeuron* CDigitRecognizer::get_neuron(int digit) {
  assert(0 <= digit && digit < 10);
  return neurons[digit];
}
