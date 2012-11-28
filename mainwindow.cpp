#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QTime>
#include "cxmlwriter.h"
#include "cdigitneuron.h"
#include "cdigitneuronbuilder.h"
#include "cpixelmatrixreader.h"
#include "cxmlparser.h"
#include <cassert>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    messager(new CVisualMessageShower)
     {
  ui->setupUi(this);

  work_interface = new CVisualWorkInterface(ui->DrawPadWidget->geometry().topLeft(),
                                            RecognizerSettings::CellHeight(),
                                            RecognizerSettings::CellWidth(),
                                            new CPixelMatrixBuilder);

  view_interface = new CViewInterface(
        ui->HistogramViewWidget->geometry().topLeft(),
        ui->HistogramViewWidget->geometry().height(),
        ui->HistogramViewWidget->geometry().width(), this, this);
  recognizer = new CDigitRecognizer();

  // creating radio group
  QGridLayout* grid = new QGridLayout;
  for(int i = 0; i < 10; ++i) {
    QRadioButton *radio = new QRadioButton;
    digitRadioButtons[i] = radio;

    radio->setText("Digit " + QString::number(i));
    grid->addWidget(radio, i % 5, i / 5);
  }
  ui->DigitRadioBox->setLayout(grid);

  // initializing palette
  QPalette palette(MainWindow::palette());
  this->setPalette(palette);

  //
  last_recognition.fill(0, 10);
}


MainWindow::~MainWindow() {
  delete ui;
  delete work_interface;
  delete view_interface;
  delete recognizer;
  delete messager;
}


void MainWindow::paintEvent(QPaintEvent *event) {
  work_interface->paintEvent(event, this, this->palette());
  view_interface->paint(last_recognition);
  //qDebug() << QTime::currentTime().toString("hh:mm:ss::zzz") << "painted";
}


void MainWindow::mousePressEvent(QMouseEvent *event) {  
  work_interface->mouseEvent(event);
  repaint();
}


void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  work_interface->mouseEvent(event);
  repaint();
}


void MainWindow::on_RecognizeButton_clicked() {
  last_recognition = recognizer->recognize(work_interface->make_pixel_matrix());
  //view_interface->paint(last_recognition);
  repaint();
}


void MainWindow::on_actionExit_triggered() {
  close();
}


void MainWindow::on_actionLoad_triggered() {  
  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(procEvents()));
  timer->setInterval(40);
  timer->start();

  IDigitNeuronReader* reader;  
  for(int i = 0; i < 10; ++i) {
    qDebug() << "Loading neuron " + QString::number(i);

    try {
      reader = new CFileDigitNeuronReader("weights/Neuron" +
                                          QString::number(i) + ".xml");
      try {
        recognizer->set_neuron(i, reader);
      } catch (QString message) {
        messager->show_message(message);
      }
    } catch (QString message) {
      messager->show_message(message);
    }

    if (reader != NULL) delete reader;

    qDebug() << "Done!";
  }

  delete timer;

  qDebug() << "Loaded";
}


void MainWindow::on_TeachButton_clicked() {
  int digit = -1;
  for(int i = 0; i < 10; ++i)
    if (digitRadioButtons[i]->isChecked()) {
      assert(digit == -1);
      digit = i;
    }

  if (digit == -1) {
    messager->show_message("Select digit, please.");
    return;
  }

  IPixelMatrix* image = work_interface->make_pixel_matrix();
  try {
    recognizer->teach(image, digit);
  } catch(QString message) {
    messager->show_message(message);
  }

  QString next_free_name = find_next_name(digit);
  IBaseWriter* writer = new CXMLWriter(next_free_name);
  try {
    writer->write(image);
  } catch(QString message) {
    messager->show_message(message);
  }
  delete writer;
  delete image;

  qDebug() << "Teaching digit " + QString::number(digit) + " done";
}


QString MainWindow::find_next_name(int digit) {
  QString path = "base/" + QString::number(digit) + "/example";
  for(int i = 0; ; ++i) {
    QString name = QString::number(i);
    while(name.size() < 5) name = "0" + name;
    QFile file(path + name + ".xml");
    if (!file.exists()) return file.fileName();
  }
}


void MainWindow::on_ClearDrawButton_clicked() {
  work_interface->clear();
  repaint();
}


void MainWindow::procEvents() {
  this->repaint();
  QApplication::processEvents();
}


void MainWindow::on_actionErase_neurons_triggered() {
  IDigitNeuronReader* empty_reader = new CEmptyDigitNeuronReader;
  for(int i = 0; i < 10; ++i) {
    qDebug() << i;
    recognizer->set_neuron(i, empty_reader);
  }
  qDebug() << "Erased";
  delete empty_reader;
}


void MainWindow::on_SaveXMLButton_clicked() {
  try {
    for(int i = 0; i < 10; ++i) {
      IBaseWriter* writer = new CXMLWriter("weights/Neuron" +
                                          QString::number(i) + ".xml");
      writer->write(recognizer->get_neuron(i));
      delete writer;
    }
  } catch(QString message) {
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
  }

  qDebug() << "Saved all!";
}


void MainWindow::on_actionTeach_from_base_triggered() {
  bool ok;
  int digit = QInputDialog::getInt(this, tr("Digit to teach"),
                                   tr("What digit to teach"), 0, 0, 9, 1, &ok);
  if (!ok) return;

  QStringList examples = QFileDialog::getOpenFileNames(
        this, tr("Open File for teachings"), "base/" + QString::number(digit),
        tr("Files (*.xml)"));
  if (examples.empty()) return;

  QString message = "Examples \n";
  for(QStringList::Iterator it = examples.begin(); it != examples.end(); ++it) {
    IPixelMatrixReader* reader = new CPixelMatrixReader(new CFileXMLParser(*it));
    recognizer->teach(reader->read(), digit);
    message += "  " + *it + "\n";
    delete reader;
  }
  message += "successfully teached.";
  messager->show_message(message);
}
