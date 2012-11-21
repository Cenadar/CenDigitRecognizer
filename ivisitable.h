#ifndef IVISITABLE_H
#define IVISITABLE_H

class IVisiter {
 public:
  virtual ~IVisiter() = 0;

  virtual void VisitA();
  virtual void VisitB();
  virtual void VisitC();
};

class IVisitable {
 public:
  virtual ~IVisitable() = 0;

  virtual void Visit() = 0;
};

#endif // IVISITABLE_H
