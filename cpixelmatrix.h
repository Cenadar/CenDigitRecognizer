#ifndef CPIXELMATRIX_H
#define CPIXELMATRIX_H

#include <QVector>
#include "iserializable.h"
#include "settings.h"

using namespace std;

class IPixelMatrix: public ISerializable {
 public:
  ~IPixelMatrix() {}

  virtual TColor get_pixel(int row, int col) const = 0;
};


class CPixelMatrix: public IPixelMatrix {
 public:  
  CPixelMatrix(QVector<QVector<TColor> > matrix_);
  ~CPixelMatrix() {}

  TColor get_pixel(int row, int col) const;
  QDomElement serialize(QDomDocument &document,
                        QMap<QString, QString> attributes) const;
 private:
  QVector<QVector<TColor> > matrix;
};

#endif // CPIXELMATRIX_H
