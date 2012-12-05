#ifndef CDIGITNEURON_H
#define CDIGITNEURON_H

class IDigitNeuron;

#include "cpixelmatrix.h"
#include "cneuronpainter.h"

using namespace std;

class IDigitNeuron {
 public:
  virtual ~IDigitNeuron() {}

  virtual TSignal getOutput(IPixelMatrix *input) const = 0;
  virtual void teach(IPixelMatrix *input, bool correctness) = 0;
  virtual int getCoefficient(int row, int col) = 0;
};


class CDigitNeuron: public IDigitNeuron {
 public:
  CDigitNeuron(QVector<QVector<int> > weight_): weight(weight_) {}
  ~CDigitNeuron() {}

  TSignal getOutput(IPixelMatrix* input) const;
  void teach(IPixelMatrix* input, bool correctness);  
  int getCoefficient(int row, int col);
 private:
  QVector<QVector<int> > weight;
};

#endif // CDIGITNEURON_H
