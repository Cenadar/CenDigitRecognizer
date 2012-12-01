#ifndef CWORKINTERFACE_H
#define CWORKINTERFACE_H

#include <QtGui>
#include "cpixelmatrix.h"
#include "cpixelmatrixbuilder.h"

class IWorkInterface {
 public:
  virtual ~IWorkInterface() {}

  virtual void paintEvent(QPaintEvent* event, QPaintDevice* device,
                          const QPalette& palette) = 0;
  virtual void mouseEvent(QMouseEvent* event) = 0;
  virtual IPixelMatrix* makePixelMatrix() const = 0;
  virtual void clear() = 0;
};


class CVisualWorkInterface: public IWorkInterface {
 public:
  CVisualWorkInterface(QPoint baseCorner_, int cell_height_, int cell_width_,
                       IPixelMatrixBuilder* builder_);
  ~CVisualWorkInterface() {delete builder;}

  void paintEvent(QPaintEvent* /*event*/, QPaintDevice *device,
                  const QPalette& palette);
  void mouseEvent(QMouseEvent* event);
  IPixelMatrix* makePixelMatrix() const;
  void clear();
 private:
  QPoint base_corner;
  int cell_height;
  int cell_width;
  IPixelMatrixBuilder *builder;
};

#endif // CWORKINTERFACE_H
