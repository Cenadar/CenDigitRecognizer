#ifndef CDIGITNEURONREADER_H
#define CDIGITNEURONREADER_H

#include <QtXml>
#include <QtCore>
#include "cdigitneuron.h"
#include "cdigitneuronbuilder.h"

class IDigitNeuronReader {
 public:
  virtual ~IDigitNeuronReader() {}

  virtual IDigitNeuron* read() = 0;
};


class CFileDigitNeuronReader: public IDigitNeuronReader {
 public:
  CFileDigitNeuronReader(QString file_name_): file_name(file_name_) {}

  IDigitNeuron* read();
 private:
  QDomElement find_first_element(QDomElement root, QString tagname,
                                 QMap<QString, QString> attr);

  QString file_name;  
};


class CEmptyDigitNeuronReader: public IDigitNeuronReader {
 public:
  IDigitNeuron* read() {
    return CDigitNeuronBuilder().build();
  }
};

#endif // CDIGITNEURONREADER_H
