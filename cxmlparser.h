#ifndef CXMLREADER_H
#define CXMLREADER_H

#include <QtXml>

class XMLParser {
 public:
  static QDomElement find_first_element(QDomElement base, QString tagname,
                                        QMap<QString, QString> attr =
                                          QMap<QString, QString>());
};


class IXMLParser {
 public:
  virtual ~IXMLParser() {}

  virtual QDomElement get_root(QString root_tagname) = 0;
};


class CFileXMLParser: public IXMLParser {
 public:
  CFileXMLParser(QString file_name_): file_name(file_name_) {}

  QDomElement get_root(QString root_tagname = QString());
 private:
  QString file_name;
};

#endif // CXMLREADER_H
