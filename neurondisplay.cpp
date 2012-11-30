#include "neurondisplay.h"
#include "ui_neurondisplay.h"

NeuronDisplay::NeuronDisplay(QWidget *parent, QVector<IDigitNeuron*> neurons_):
  QDialog(parent), ui(new Ui::NeuronDisplay), neurons(neurons_) {
  ui->setupUi(this);
}


NeuronDisplay::~NeuronDisplay() {  
  delete ui;
}


void NeuronDisplay::on_buttonBox_accepted() {
  this->close();  
}


void NeuronDisplay::paintEvent(QPaintEvent* /*event*/) {
  INeuronPainter* painter = new CNeuronPainter(QPoint(20, 20), 6, 6, this);
  painter->paint(neurons);
  delete painter;
}
