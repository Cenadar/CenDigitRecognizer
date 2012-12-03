#include "cxmlwriter.h"

#include <QtCore>
#include <QtXml>
#include "settings.h"

void CXMLWriter::write(IConverter* obj) {
  if (obj == NULL) throw ("Cannot write: uninitialized object");

  QDomDocument document;

  QDomElement elem = obj->convert(document);
  document.appendChild(elem);

  QFile file(fileName);

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    throw QString("Cannot open file: ") + file.fileName();

  QTextStream stream(&file);
  stream << document.toString(2/*indent*/);
  file.close();
  delete obj;
}
