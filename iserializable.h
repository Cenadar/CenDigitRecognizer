#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <QtXml>

class ISerializable {
 public:
  virtual ~ISerializable() {}

  virtual QDomElement serialize(QDomDocument& document) const = 0;
};

#endif // ISERIALIZABLE_H
