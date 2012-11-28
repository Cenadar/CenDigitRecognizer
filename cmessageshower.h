#ifndef CMESSAGESHOWER_H
#define CMESSAGESHOWER_H

#include <QString>
#include <QMessageBox>

class IMessageShower {
 public:
  virtual ~IMessageShower() {}

  virtual void show_message(const QString &message) = 0;
};


class CVisualMessageShower: public IMessageShower {
  virtual void show_message(const QString &message);
};

#endif // CMESSAGESHOWER_H
