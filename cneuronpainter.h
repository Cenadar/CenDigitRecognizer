#ifndef CNEURONPAINTER_H
#define CNEURONPAINTER_H

class INeuronPainter;

#include "cdigitneuron.h"
#include <QtGui>

class INeuronPainter {
 public:
  virtual ~INeuronPainter() {}

  virtual void paint(QVector<IDigitNeuron*> neurons) = 0;
};


class CNeuronPainter: public INeuronPainter {
 public:
  CNeuronPainter(QPoint baseCorner_, int cellHeight_, int cellWidth_,
                 QPaintDevice* device_):
    baseCorner(baseCorner_), cellHeight(cellHeight_), cellWidth(cellWidth_),
    device(device_) {}

  void paint(QVector<IDigitNeuron*> neurons);
 private:
  QPoint baseCorner;
  int cellHeight;
  int cellWidth;
  QPaintDevice* device;
};

#endif // CNEURONPAINTER_H
