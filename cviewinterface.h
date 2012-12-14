#ifndef CVIEWINTERFACE_H
#define CVIEWINTERFACE_H

#include <QtGui>
#include "settings.h"

class IViewInterface {
 public:
  virtual ~IViewInterface() {}

  virtual void setHighest(int highest_) = 0;
  virtual void paint(QVector<TSignal> sign) = 0;
};


class CViewInterface: public IViewInterface {
 public:
  CViewInterface(QPoint baseCorner_, int height_, int width_,
                 QPaintDevice *device_, QWidget* widget_, QLabel* resultLabel_):
    baseCorner(baseCorner_), height(height_), width(width_), highest(-1),
    device(device_),resultLabel(resultLabel_), widget(widget_) {}
  ~CViewInterface() {}

  void setHighest(int highest_) {highest = highest_;}
  void paint(QVector<TSignal> sign);
 private:
  const QPoint baseCorner;
  const int height;
  const int width;
  int highest;
  QPaintDevice* device;  
  QLabel* resultLabel;
  QWidget* widget;
};

#endif // CVIEWINTERFACE_H
