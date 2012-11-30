#ifndef CDIGITRECOGNIZER_H
#define CDIGITRECOGNIZER_H

#include "cdigitneuron.h"
#include "cdigitneuronreader.h"

class IDigitRecognizer {
 public:
  virtual ~IDigitRecognizer() {}

  virtual QVector<TSignal> recognize(IPixelMatrix* image) = 0;
  virtual void set_neuron(int digit, IDigitNeuronReader* reader) = 0;
  virtual void teach(IPixelMatrix* image, int digit) = 0;
  virtual IDigitNeuron* get_neuron(int digit) = 0;
  virtual QVector<IDigitNeuron*> get_neurons() = 0;
};


class CDigitRecognizer: public IDigitRecognizer {
 public:
  CDigitRecognizer(): neurons(10, NULL) {}
  ~CDigitRecognizer();

  QVector<TSignal> recognize(IPixelMatrix* image);
  void set_neuron(int digit, IDigitNeuronReader* reader);
  void teach(IPixelMatrix* image, int digit);
  IDigitNeuron* get_neuron(int digit);
  QVector<IDigitNeuron*> get_neurons();
 private:
  QVector<IDigitNeuron*> neurons;
};

#endif // CDIGITRECOGNIZER_H
