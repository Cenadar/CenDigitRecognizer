#ifndef CPIXELMATRIX_H
#define CPIXELMATRIX_H

#include <QVector>
#include "settings.h"

using namespace std;

class IPixelMatrix {
 public:
  virtual ~IPixelMatrix() {}

  virtual TSignal getSignal(int row, int col) const = 0;
};


class CPixelMatrix: public IPixelMatrix {
 public:  
  CPixelMatrix(QVector<QVector<TColor> > matrix);
  ~CPixelMatrix() {}

  TSignal getSignal(int row, int col) const;  
 private:
  QVector<QVector<TColor> > matrix;
};

#endif // CPIXELMATRIX_H
