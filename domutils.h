#ifndef DOMUTILS_H
#define DOMUTILS_H

#include <QtXml>

QDomElement findFirstElement(QDomElement base, QString tagname,
                             QMap<QString, QString> attr =
                             QMap<QString, QString>());

#endif // DOMUTILS_H
