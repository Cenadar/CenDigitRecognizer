#ifndef CDIGITNETWORK_H
#define CDIGITNETWORK_H

#include "cdigitneuron.h"
#include "cdigitneuronreader.h"

class IDigitNetwork {
 public:
  virtual ~IDigitNetwork() {}

  virtual QVector<TSignal> recognize(IPixelMatrix* image) = 0;
  virtual int recognizeOne(QVector<TSignal> recognition) = 0;
  virtual int recognizeOne(IPixelMatrix* image) = 0;
  virtual void teach(IPixelMatrix* image, int digit) = 0;  

  virtual void setNeuron(int digit, IDigitNeuronReader* reader) = 0;
  virtual IDigitNeuron* getNeuron(int digit) = 0;
  virtual QVector<IDigitNeuron*> getNeurons() = 0;
};


class CDigitNetwork: public IDigitNetwork {
 public:
  CDigitNetwork(): neurons(10, NULL) {}
  ~CDigitNetwork();

  QVector<TSignal> recognize(IPixelMatrix* image);
  int recognizeOne(QVector<TSignal> recognition);
  int recognizeOne(IPixelMatrix* image);
  void teach(IPixelMatrix* image, int digit);

  void setNeuron(int digit, IDigitNeuronReader* reader);
  IDigitNeuron* getNeuron(int digit);
  QVector<IDigitNeuron*> getNeurons();
 private:
  QVector<IDigitNeuron*> neurons;
};

#endif // CDIGITNETWORK_H
