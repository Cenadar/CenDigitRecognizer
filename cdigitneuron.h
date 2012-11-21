#ifndef CDIGITNEURON_H
#define CDIGITNEURON_H

#include "cpixelmatrix.h"
#include "iserializable.h"

using namespace std;

typedef int TSignal;

class IDigitNeuron: public ISerializable {
 public:
  virtual ~IDigitNeuron() {}

  virtual TSignal get_output(IPixelMatrix *input) const = 0;
};


class CDigitNeuron: public IDigitNeuron {
 public:
  CDigitNeuron();
  ~CDigitNeuron() {}

  TSignal get_output(IPixelMatrix *input) const;
  QDomElement serialize(QDomDocument &document,
                        QMap<QString, QString> attributes) const;
 private:
  QVector<QVector<int> > weight;
};

#endif // CDIGITNEURON_H
