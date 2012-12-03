#ifndef ICONVERTER_H
#define ICONVERTER_H

#include <QtXml>
#include "cdigitneuron.h"

class IConverter {
 public:
  virtual ~IConverter() {}

  virtual QDomElement convert(QDomDocument document) = 0;
};


class CDigitNeuronConverter: public IConverter {
 public:
  CDigitNeuronConverter(IDigitNeuron* neuron_): neuron(neuron_) {}

  QDomElement convert(QDomDocument document);
 private:
  IDigitNeuron* neuron;
};


class CPixelMatrixConverter: public IConverter {
 public:
  CPixelMatrixConverter(IPixelMatrix* image_): image(image_) {}

  QDomElement convert(QDomDocument document);
 private:
  IPixelMatrix* image;
};

#endif // ICONVERTER_H
