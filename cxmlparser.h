#ifndef CXMLREADER_H
#define CXMLREADER_H

#include <QtXml>

class XMLParser {
 public:
  static QDomElement findFirstElement(QDomElement base, QString tagname,
                                        QMap<QString, QString> attr =
                                          QMap<QString, QString>());
};


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
