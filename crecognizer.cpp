#include "crecognizer.h"
#include <cassert>
#include <QString>
#include "cxmlwriter.h"
#include "neurondisplay.h"
#include "cpixelmatrix.h"
#include "cpixelmatrixreader.h"

CRecognizer::CRecognizer(IWorkInterface* paintingInterface_,
                         IViewInterface* resultsInterface_,
                         IDigitNetwork* network_,
                         IMessageShower* messager_,
                         QPaintDevice* device_,
                         QPalette palette_) {
  paintingInterface = paintingInterface_;
  resultsInterface = resultsInterface_;
  network = network_;
  messager = messager_;
  device = device_;
  palette = palette_;

  parentWidget = NULL;
}


CRecognizer::~CRecognizer() {
  delete paintingInterface;
  delete resultsInterface;
  delete network;
  delete messager;
}


void CRecognizer::init() {
  lastRecognition.fill(0, 10);
}


void CRecognizer::paintEvent(QPaintEvent* event) {
  paintingInterface->paintEvent(event, device, palette);
  assert(lastRecognition.size() == 10);
  resultsInterface->paint(lastRecognition);
}


void CRecognizer::mouseEvent(QMouseEvent* event) {
  paintingInterface->mouseEvent(event);
}


void CRecognizer::recognizeDigit() {
  lastRecognition = network->recognize(paintingInterface->makePixelMatrix());
  assert(lastRecognition.size() == 10);

  int highest = -1;
  for(int digit = 0; digit < 10; ++digit) {
    if (lastRecognition[digit] > 0 && (
          highest == -1 || lastRecognition[highest] < lastRecognition[digit]))
      highest = digit;
  }

  resultsInterface->setHighest(highest);
}


void CRecognizer::teachNeurons(int digit) {
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

  QString nextFreeName = findNextName(digit);
  IBaseWriter* writer = new CXMLWriter(nextFreeName);
  try {
    writer->write(new CPixelMatrixConverter(image));
  } catch(QString message) {
    messager->showMessage(message);
  }
  delete writer;
  delete image;

  qDebug() << QObject::tr("Teaching digit %1 done").arg(QString::number(digit));
}


void CRecognizer::loadNeuronsFromFile() {
  IXMLParser* parser;
  IDigitNeuronReader* reader;
  for(int i = 0; i < 10; ++i) {
    qDebug() << QObject::tr("Loading neuron %1").arg(QString::number(i));

    try {
      parser =
          new CFileXMLParser(QObject::tr("%1/Neuron%2.xml").arg(
                               RSettings::neuronsDir(), QString::number(i)));
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

  qDebug() << "Loaded";
}


void CRecognizer::clearDrawPad() {
  paintingInterface->clear();
}


void CRecognizer::eraseNeurons() {
  IDigitNeuronReader* emptyReader = new CEmptyDigitNeuronReader;
  for(int i = 0; i < 10; ++i) {
    qDebug() << i;
    network->setNeuron(i, emptyReader);
  }
  qDebug() << "Erased!";
  delete emptyReader;
}


void CRecognizer::saveToXML() {
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


void CRecognizer::displayNeurons() {
  NeuronDisplay display(parentWidget, network->getNeurons());
  display.exec();
}


void CRecognizer::teachFromFiles(QStringList examples, int digit) {
  if (examples.empty()) return;

  QString message = "Examples \n";
  for(QStringList::Iterator it = examples.begin(); it != examples.end(); ++it) {
    IPixelMatrixReader* reader = new CPixelMatrixReader(new CFileXMLParser(*it));
    network->teach(reader->read(), digit);
    message += "  " + *it + "\n";
    delete reader;
  }
  message += "successfully teached.";
  messager->showMessage(message);
}


void CRecognizer::teachFromBase() {
  bool ok = true;
  QString examplesDirectory = QFileDialog::getExistingDirectory(
      parentWidget, QObject::tr("Open base for teachings"));
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
        parentWidget, QObject::tr("Teachings"),
        QObject::tr("Teach these database?\n%1").arg(databaseInfo),
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
    for(int digit = 0; digit < 10; ++digit) {
      try {
        teachFromFiles(examples[digit], digit);
      } catch(QString message) {
        messager->showMessage(message);
      }
    }
  }
}


QString CRecognizer::findNextName(int digit) {
  QString path = QObject::tr("%1/%2/example").arg(
        RSettings::databaseDir(), QString::number(digit));

  for(int i = 0; ; ++i) {
    QString name = QString::number(i);
    while(name.size() < 5) name = "0" + name;
    QFile file(path + name + ".xml");
    if (!file.exists()) return file.fileName();
  }
}
