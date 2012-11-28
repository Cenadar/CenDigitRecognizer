#ifndef CVIEWINTERFACE_H
#define CVIEWINTERFACE_H

#include <QtGui>
#include "settings.h"

class IViewInterface {
 public:
  virtual ~IViewInterface() {}

  virtual void paint(QVector<TSignal> sign) = 0;
};


class CViewInterface: public IViewInterface {
 public:
  CViewInterface(QPoint base_corner_, int height_, int width_,
                 QPaintDevice *device_, QWidget* widget_):
    base_corner(base_corner_), height(height_), width(width_), device(device_),
    widget(widget_) {}
  ~CViewInterface() {}

  void paint(QVector<TSignal> sign);

 private:
  const QPoint base_corner;
  const int height;
  const int width;
  QPaintDevice* device;
  QWidget* widget;
};

#endif // CVIEWINTERFACE_H
