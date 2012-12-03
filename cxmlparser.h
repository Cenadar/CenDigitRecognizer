#ifndef CXMLREADER_H
#define CXMLREADER_H

#include <QtXml>

class IXMLParser {
 public:
  virtual ~IXMLParser() {}

  virtual QDomElement getRoot(QString root_tagname) = 0;
};


class CFileXMLParser: public IXMLParser {
 public:
  CFileXMLParser(QString fileName_): fileName(fileName_) {}

  QDomElement getRoot(QString root_tagname = QString());
 private:
  QString fileName;
};

#endif // CXMLREADER_H
