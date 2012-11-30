#ifndef CDIGITNEURON_H
#define CDIGITNEURON_H

class IDigitNeuron;

#include "cpixelmatrix.h"
#include "iserializable.h"
#include "cneuronpainter.h"

using namespace std;

class IDigitNeuron: public ISerializable {
 public:
  virtual ~IDigitNeuron() {}

  virtual TSignal get_output(IPixelMatrix *input) const = 0;
  virtual void teach(IPixelMatrix *input, bool correctness) = 0;

  friend class CNeuronPainter;
 private:
  virtual int getCoefficient(int row, int col) = 0;
};


class CDigitNeuron: public IDigitNeuron {
 public:
  CDigitNeuron(QVector<QVector<int> > weight_): weight(weight_) {}
  ~CDigitNeuron() {}

  TSignal get_output(IPixelMatrix *input) const;
  void teach(IPixelMatrix *input, bool correctness);

  QDomElement serialize(QDomDocument &document) const;
 private:
  int getCoefficient(int row, int col);

  QVector<QVector<int> > weight;
};

#endif // CDIGITNEURON_H
