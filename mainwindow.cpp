#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QTime>
#include "cxmlwriter.h"
#include "cdigitneuron.h"
#include "cdigitneuronreader.h"
#include "cdigitneuronbuilder.h"
#include "cpixelmatrixreader.h"
#include "cxmlparser.h"
#include "neurondisplay.h"
#include <cassert>
#include "iconverter.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    messager(new CVisualMessageShower) {
  ui->setupUi(this);

  paintingInterface = new CVisualWorkInterface(ui->DrawPadWidget->geometry().topLeft(),
                                            RSettings::cellHeight(),
                                            RSettings::cellWidth(),
                                            new CPixelMatrixBuilder);

  resultsInterface = new CViewInterface(
        ui->HistogramViewWidget->geometry().topLeft(),
        ui->HistogramViewWidget->geometry().height(),
        ui->HistogramViewWidget->geometry().width(), this, this);

  network = new CDigitNetwork;

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
  lastRecognition.fill(0, 10);
  on_actionLoad_triggered();
}


MainWindow::~MainWindow() {
  delete ui;
  delete paintingInterface;
  delete resultsInterface;
  delete network;
  delete messager;
}


void MainWindow::paintEvent(QPaintEvent* event) {
  paintingInterface->paintEvent(event, this, this->palette());
  resultsInterface->paint(lastRecognition);

  assert(lastRecognition.size() == 10);
  int highest = -1;
  for(int digit = 0; digit < 10; ++digit) {
    if (highest == -1 || lastRecognition[highest] < lastRecognition[digit])
      highest = digit;
  }
  if (lastRecognition[highest] > 1e-9)
    ui->ResultLabel->setText("Result of recognition: " + QString::number(highest));
  else
    ui->ResultLabel->setText("No recognition");
}


void MainWindow::mousePressEvent(QMouseEvent *event) {  
  paintingInterface->mouseEvent(event);
  repaint();
}


void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  paintingInterface->mouseEvent(event);
  repaint();
}


void MainWindow::on_RecognizeButton_clicked() {
  lastRecognition = network->recognize(paintingInterface->makePixelMatrix());
  assert(lastRecognition.size() == 10);
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

  IXMLParser* parser;
  IDigitNeuronReader* reader;
  for(int i = 0; i < 10; ++i) {
    qDebug() << "Loading neuron " + QString::number(i);

    try {
      parser = new CFileXMLParser(RSettings::neuronsDir() + "/Neuron" +
                                     QString::number(i) + ".xml");
      reader = new CDigitNeuronReader(parser);
      try {
        network->setNeuron(i, reader);
      } catch (QString message) {
        messager->showMessage(message);
      }
      delete reader;
      delete parser;
    } catch (QString message) {
      messager->showMessage(message);
    }

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
    messager->showMessage("Select digit, please.");
    return;
  }

  IPixelMatrix* image = paintingInterface->makePixelMatrix();
  try {
    network->teach(image, digit);
  } catch(QString message) {
    messager->showMessage(message);
  }

  QString nextFreeName = find_next_name(digit);
  IBaseWriter* writer = new CXMLWriter(nextFreeName);
  try {
    writer->write(new CPixelMatrixConverter(image));
  } catch(QString message) {
    messager->showMessage(message);
  }
  delete writer;
  delete image;

  qDebug() << "Teaching digit " + QString::number(digit) + " done";
}


QString MainWindow::find_next_name(int digit) {
  QString path = RSettings::databaseDir() + "/" + QString::number(digit) + "/example";
  for(int i = 0; ; ++i) {
    QString name = QString::number(i);
    while(name.size() < 5) name = "0" + name;
    QFile file(path + name + ".xml");
    if (!file.exists()) return file.fileName();
  }
}


void MainWindow::on_ClearDrawButton_clicked() {
  paintingInterface->clear();
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
    network->setNeuron(i, empty_reader);
  }
  qDebug() << "Erased!";
  delete empty_reader;
}


void MainWindow::on_SaveXMLButton_clicked() {
  try {
    for(int i = 0; i < 10; ++i) {
      IBaseWriter* writer = new CXMLWriter(RSettings::neuronsDir() + "/Neuron" +
                                          QString::number(i) + ".xml");
      writer->write(new CDigitNeuronConverter(network->getNeuron(i)));
      delete writer;
    }
  } catch(QString message) {
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
  }

  qDebug() << "Saved all!";
}


void MainWindow::on_actionShow_neurons_triggered() {
  NeuronDisplay display(this, network->getNeurons());
  display.exec();
}


void MainWindow::on_actionFiles_triggered() {
  bool ok;
  int digit = QInputDialog::getInt(this, tr("Digit to teach"),
                                   tr("What digit to teach"), 0, 0, 9, 1, &ok);
  if (!ok) return;

  QStringList examples = QFileDialog::getOpenFileNames(
        this, tr("Open File for teachings"), RSettings::databaseDir() + "/"
        + QString::number(digit), tr("Files (*.xml)"));

  teachFromFiles(examples, digit);
}


void MainWindow::on_actionBase_directory_triggered() {
  bool ok = true;
  QString examplesDirectory = QFileDialog::getExistingDirectory(
      this, tr("Open base for teachings"));
  if (!ok) return;

  QStringList examples[10];
  for(int digit = 0; digit < 10; ++digit) {
    try {
      QDir dir(examplesDirectory + "/" + QString::number(digit));
      if (dir.exists()) {
        QStringList filters;
        filters << "*.xml";
        examples[digit] = dir.entryList(filters, QDir::Files);
      }

      for(QStringList::Iterator file = examples[digit].begin(); file != examples[digit].end();
          ++file) {
        *file = examplesDirectory + "/" + QString::number(digit) + "/" + *file;
      }
    } catch(QString message) {
      messager->showMessage(message);
    }
  }
  QString databaseInfo;
  for(int digit = 0; digit < 10; ++digit) {
    databaseInfo += QString::number(digit) + " have " +
        QString::number(examples[digit].size()) + " examples\n";
  }
  if (QMessageBox::information(
      this, "Teachings", "Teach these database?\n" + databaseInfo,
      QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
    for(int digit = 0; digit < 10; ++digit) {
      try {
        teachFromFiles(examples[digit], digit, false);
      } catch(QString message) {
        messager->showMessage(message);
      }
    }
  }
  messager->showMessage("Done teaching from database");
}


void MainWindow::teachFromFiles(QStringList examples, int digit,
                                bool showMessage) {
  if (examples.empty()) return;

  QString message = "Examples \n";
  for(QStringList::Iterator it = examples.begin(); it != examples.end(); ++it) {
    IPixelMatrixReader* reader = new CPixelMatrixReader(new CFileXMLParser(*it));
    network->teach(reader->read(), digit);
    message += "  " + *it + "\n";
    delete reader;
  }
  message += "successfully teached.";
  if (showMessage) messager->showMessage(message);
}
