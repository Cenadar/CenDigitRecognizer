#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "cweightswriter.h"
#include "cdigitneuron.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    work_interface(new CVisualWorkInterface(QPoint(60, 80),
                                            RecognizerSettings::cell_height(),
                                            RecognizerSettings::cell_width(),
                                            new CPixelMatrixBuilder())) {
  ui->setupUi(this);

  QPalette palette(MainWindow::palette());  
  //palette.setColor(backgroundRole(), Qt::white);
  this->setPalette(palette);

  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
  timer->start(1000/RecognizerSettings::FPS());
}


MainWindow::~MainWindow() {
  delete ui;
  delete work_interface;
}


void MainWindow::paintEvent(QPaintEvent *event) {
  work_interface->paintEvent(event, this, this->palette());
}


void MainWindow::mousePressEvent(QMouseEvent *event) {  
  work_interface->mouseEvent(event);
  //repaint();
}


void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  work_interface->mouseEvent(event);
  //repaint();
}


void MainWindow::on_CreateXMLButton_clicked() {
  IDigitNeuron* neur1 = new CDigitNeuron();

  IWeightsWriter* FWW = new CFileWeightsWriter(neur1, "example_.xml");
  FWW->Write();
  delete FWW;

  qDebug() << "Done!";
}
