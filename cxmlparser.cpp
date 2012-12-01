#include "cxmlparser.h"

QDomElement XMLParser::findFirstElement(QDomElement base,
                                          QString tagname,
                                          QMap<QString, QString> attr) {
  QDomNodeList list = base.elementsByTagName(tagname);
  QDomNode node;
  QDomElement elem;
  for(int i = 0; i < list.size(); ++i) {
    node = list.at(i);
    if (node.isElement()) {
      elem = node.toElement();
      bool coincides = true;
      for(QMap<QString, QString>::Iterator it = attr.begin();
          coincides && it != attr.end(); ++it) {
        if (elem.attribute(it.key()) != it.value()) coincides = false;
      }
      if (coincides) return elem;
    }
  }

  QString exceptionMessage = "Cannot find " + tagname + " element\n";
  for(QMap<QString, QString>::Iterator it = attr.begin();
      it != attr.end(); ++it) {
    exceptionMessage += "Attibute: " + it.key() + "; ";
    exceptionMessage += "Value: " + it.value() + ";\n";
  }
  throw exceptionMessage;
}


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
