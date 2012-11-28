#include "cxmlparser.h"

QDomElement CFileXMLParser::get_root(QString root_tagname) {
  QFile file(file_name);
  QDomDocument document;
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    throw QString("Cannot open to read ") + file_name;
  if (!document.setContent(&file))
    throw QString("Cannot parse content ") + file_name;
  file.close();

  QDomElement root = document.firstChildElement(root_tagname);
  return root;
}


QDomElement XMLParser::find_first_element(QDomElement base,
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

  QString exception_message = "Cannot find " + tagname + " element\n";
  for(QMap<QString, QString>::Iterator it = attr.begin();
      it != attr.end(); ++it) {
    exception_message += "Attibute: " + it.key() + "; ";
    exception_message += "Value: " + it.value() + ";\n";
  }
  throw exception_message;
}
