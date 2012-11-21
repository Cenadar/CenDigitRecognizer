#ifndef CPIXELMATRIXBUILDER_H
#define CPIXELMATRIXBUILDER_H

#include "cpixelmatrix.h"

class IPixelMatrixBuilder {
 public:
  virtual ~IPixelMatrixBuilder() {}

  virtual IPixelMatrix* build() const = 0;
  virtual void set_color(int row, int col, TColor color) = 0;
  virtual TColor get_color(int row, int col) const = 0;
};


class CPixelMatrixBuilder: public IPixelMatrixBuilder {
 public:
  CPixelMatrixBuilder();

  IPixelMatrix* build() const;
  void set_color(int row, int col, TColor color);
  TColor get_color(int row, int col) const;
 private:
  QVector<QVector<TColor> > matrix;
};

#endif // CPIXELMATRIXBUILDER_H
