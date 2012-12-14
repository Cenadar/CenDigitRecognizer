#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QTime>
#include <cassert>
#include "cxmlwriter.h"
#include "cdigitneuron.h"
#include "cdigitneuronreader.h"
#include "cdigitneuronbuilder.h"
#include "cpixelmatrixreader.h"
#include "cxmlparser.h"
#include "neurondisplay.h"
#include "iconverter.h"
#include "crecognizer.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
  ui->setupUi(this);  

  // initializing facade
  IWorkInterface* paintingInterface = new CVisualWorkInterface(
        ui->DrawPadWidget->geometry().topLeft(),
        RSettings::cellHeight(),
        RSettings::cellWidth(),
        new CPixelMatrixBuilder);

  IViewInterface* resultsInterface = new CViewInterface(
        ui->HistogramViewWidget->geometry().topLeft(),
        ui->HistogramViewWidget->geometry().height(),
        ui->HistogramViewWidget->geometry().width(), this, this,
        ui->ResultLabel);

  IDigitNetwork* network = new CDigitNetwork;
  IMessageShower* messager = new CVisualMessageShower;

  recognizer = new CRecognizer(paintingInterface, resultsInterface, network,
                               messager, this, this->palette());
  recognizer->init();  
  recognizer->loadNeuronsFromFile();

  // creating radio group
  QGridLayout* grid = new QGridLayout;
  for(int i = 0; i < 10; ++i) {
    QRadioButton *radio = new QRadioButton;
    digitRadioButtons[i] = radio;

    radio->setText(tr("Digit %1").arg(QString::number(i)));
    grid->addWidget(radio, i % 5, i / 5);
  }
  ui->DigitRadioBox->setLayout(grid);

  // initializing palette
  QPalette palette(MainWindow::palette());
  this->setPalette(palette);
}


MainWindow::~MainWindow() {
  delete ui;
  delete recognizer;
}


void MainWindow::paintEvent(QPaintEvent* event) {  
  recognizer->paintEvent(event);
}


void MainWindow::mousePressEvent(QMouseEvent *event) {
  recognizer->mouseEvent(event);
  repaint();
}


void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  recognizer->mouseEvent(event);
  repaint();
}


void MainWindow::on_RecognizeButton_clicked() {
  recognizer->recognizeDigit();
  repaint();
}


void MainWindow::on_actionExit_triggered() {
  close();
}


void MainWindow::on_actionLoad_triggered() {
  recognizer->loadNeuronsFromFile();
}


void MainWindow::on_TeachButton_clicked() {
  int digit = -1;
  for(int i = 0; i < 10; ++i)
    if (digitRadioButtons[i]->isChecked()) {
      assert(digit == -1);
      digit = i;
    }

  recognizer->teachNeurons(digit);
}


void MainWindow::on_ClearDrawButton_clicked() {
  recognizer->clearDrawPad();
  repaint();
}


void MainWindow::on_actionErase_neurons_triggered() {
  recognizer->eraseNeurons();
}


void MainWindow::on_SaveXMLButton_clicked() {
  recognizer->saveToXML();
}


void MainWindow::on_actionShow_neurons_triggered() {
  recognizer->displayNeurons();
}


void MainWindow::on_actionFiles_triggered() {
  bool ok;
  int digit = QInputDialog::getInt(this, tr("Digit to teach"),
                                   tr("What digit to teach"), 0, 0, 9, 1, &ok);
  if (!ok) return;

  QStringList examples = QFileDialog::getOpenFileNames(
        this, tr("Open File for teachings"), tr("%1/%2").arg(
          RSettings::databaseDir(), QString::number(digit)),
        tr("Files(*.xml)"));

  recognizer->teachFromFiles(examples, digit);
}


void MainWindow::on_actionBase_directory_triggered() {
  recognizer->teachFromBase();
}
