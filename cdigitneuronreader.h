#ifndef CDIGITNEURONREADER_H
#define CDIGITNEURONREADER_H

#include <QtXml>
#include <QtCore>
#include "cdigitneuron.h"
#include "cdigitneuronbuilder.h"
#include "cxmlparser.h"

class IDigitNeuronReader {
 public:
  virtual ~IDigitNeuronReader() {}

  virtual IDigitNeuron* read() = 0;
};


class CDigitNeuronReader: public IDigitNeuronReader {
 public:
  CDigitNeuronReader(IXMLParser* parser_): parser(parser_) {}

  IDigitNeuron* read();
 private:
  IXMLParser* parser;
};


class CEmptyDigitNeuronReader: public IDigitNeuronReader {
 public:
  IDigitNeuron* read() {
    return CDigitNeuronBuilder().build();
  }
};

#endif // CDIGITNEURONREADER_H
