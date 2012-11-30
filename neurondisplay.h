#ifndef NEURONDISPLAY_H
#define NEURONDISPLAY_H

#include <QDialog>
#include "cdigitneuron.h"

namespace Ui {
  class NeuronDisplay;
}

class NeuronDisplay: public QDialog {
  Q_OBJECT
  
public:
  explicit NeuronDisplay(QWidget* parent, QVector<IDigitNeuron*> neurons_);
  ~NeuronDisplay();
  
private slots:
  void on_buttonBox_accepted();

private:
  void paintEvent(QPaintEvent* /*event*/);

  Ui::NeuronDisplay* ui;
  QVector<IDigitNeuron*> neurons;
};

#endif // NEURONDISPLAY_H
