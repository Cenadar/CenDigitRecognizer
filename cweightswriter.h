#ifndef CWEIGHTSWRITER_H
#define CWEIGHTSWRITER_H

#include <QString>
#include "cdigitneuron.h"

using namespace std;

class IWeightsWriter {
 public:
  virtual ~IWeightsWriter() {}

  virtual void Write() = 0;
};

class CFileWeightsWriter: public IWeightsWriter {
 public:
  CFileWeightsWriter(IDigitNeuron* neuron_, const QString &file_name_):
    file_name(file_name_),
    neuron(neuron_) {}

  void Write();
 private:
  QString file_name;
  IDigitNeuron* neuron;
};

#endif // CWEIGHTSWRITER_H
