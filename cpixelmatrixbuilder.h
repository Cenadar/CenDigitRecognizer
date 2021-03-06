#ifndef CPIXELMATRIXBUILDER_H
#define CPIXELMATRIXBUILDER_H

#include "cpixelmatrix.h"

class IPixelMatrixBuilder {
 public:
  virtual ~IPixelMatrixBuilder() {}

  virtual IPixelMatrix* build() const = 0;
  virtual void setColor(int row, int col, TColor color) = 0;
  virtual TColor getColor(int row, int col) const = 0;
  virtual void clear() = 0;
};


class CPixelMatrixBuilder: public IPixelMatrixBuilder {
 public:
  CPixelMatrixBuilder();

  IPixelMatrix* build() const;
  void setColor(int row, int col, TColor color);
  TColor getColor(int row, int col) const;
  void clear();
 private:
  QVector<QVector<TColor> > matrix;
};

#endif // CPIXELMATRIXBUILDER_H
