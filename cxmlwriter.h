#ifndef CXMLWRITER_H
#define CXMLWRITER_H

#include <QString>
#include "cdigitneuron.h"

using namespace std;

class IBaseWriter {
 public:
  virtual ~IBaseWriter() {}

  virtual void write(ISerializable* obj) = 0;
};


class CXMLWriter: public IBaseWriter {
 public:
  CXMLWriter(const QString &fileName_):
    fileName(fileName_) {}

  void write(ISerializable *obj);
 private:
  QString fileName;
};

#endif // CXMLWRITER_H
