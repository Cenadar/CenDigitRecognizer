#ifndef CDIGITNEURONBUILDER_H
#define CDIGITNEURONBUILDER_H

#include "cdigitneuron.h"
#include "settings.h"

class IDigitNeuronBuilder {
 public:
  virtual ~IDigitNeuronBuilder() {}

  virtual void setValue(int row, int col, int value) = 0;
  virtual IDigitNeuron* build() const = 0;
};


class CDigitNeuronBuilder: public IDigitNeuronBuilder {
 public:
  CDigitNeuronBuilder();

  void setValue(int row, int col, int value);
  IDigitNeuron* build() const;
 private:
  QVector<QVector<int> > weight;
};

#endif // CDIGITNEURONBUILDER_H
