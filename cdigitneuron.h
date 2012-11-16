#ifndef CDIGITNEURON_H
#define CDIGITNEURON_H

#include "cpixelmatrix.h"

typedef int TSignal;

class IDigitNeuron {
 public:
  virtual ~IDigitNeuron() = 0;

  virtual TSignal get_output(IPixelMatrix *input) = 0;
};


class CDigitNeuron: public IDigitNeuron {
 public:
  CDigitNeuron();
  ~CDigitNeuron() {}

  TSignal get_output(IPixelMatrix *input);
 private:
  vector<vector<int> > w;
};

#endif // CDIGITNEURON_H
