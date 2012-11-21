#ifndef CVIEWINTERFACE_H
#define CVIEWINTERFACE_H

class IViewInterface {
 public:
  virtual ~IViewInterface() {}

};


class CViewInterface: public IV {
 public:
  CViewInterface();
  ~CViewInterface() {}

 private:
  const QPoint base_corner;
  const int height;
  const int width;
  QPaintDevice *device;

};

#endif // CVIEWINTERFACE_H
