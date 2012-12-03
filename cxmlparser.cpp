#include "cxmlparser.h"

QDomElement CFileXMLParser::getRoot(QString root_tagname) {
  QFile file(fileName);
  QDomDocument document;
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    throw QString("Cannot open to read ") + fileName;
  if (!document.setContent(&file))
    throw QString("Cannot parse content ") + fileName;
  file.close();

  QDomElement root = document.firstChildElement(root_tagname);
  return root;
}
