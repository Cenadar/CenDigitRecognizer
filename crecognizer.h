#ifndef CRECOGNIZER_H
#define CRECOGNIZER_H

#include "cworkinterface.h"
#include "cviewinterface.h"
#include "cdigitnetwork.h"
#include "cmessageshower.h"

class IRecognizer {
 public:
  virtual ~IRecognizer() {}

  virtual void init() = 0;
  virtual void paintEvent(QPaintEvent* event) = 0;
  virtual void mouseEvent(QMouseEvent* event) = 0;
  virtual void recognizeDigit() = 0;
  virtual void teachNeurons(int digit) = 0;
  virtual void loadNeuronsFromFile() = 0;
  virtual void clearDrawPad() = 0;
  virtual void eraseNeurons() = 0;
  virtual void saveToXML() = 0;
  virtual void displayNeurons() = 0;
  virtual void teachFromFiles(QStringList examples, int digit) = 0;
  virtual void teachFromBase() = 0;
};


class CRecognizer: public IRecognizer {
 public:
  CRecognizer(IWorkInterface* paintingInterface_,
              IViewInterface* resultsInterface_,
              IDigitNetwork* network_,
              IMessageShower* messager_,
              QPaintDevice* device_,
              QPalette palette_);
  ~CRecognizer();

  void init();
  void paintEvent(QPaintEvent* event);
  void mouseEvent(QMouseEvent* event);
  void recognizeDigit();
  void teachNeurons(int digit);
  void loadNeuronsFromFile();
  void clearDrawPad();
  void eraseNeurons();
  void saveToXML();
  void displayNeurons();
  void teachFromFiles(QStringList examples, int digit);
  void teachFromBase();  
 private:
  QString findNextName(int digit);

  IWorkInterface* paintingInterface;
  IViewInterface* resultsInterface;
  IDigitNetwork* network;
  IMessageShower* messager;  

  QWidget* parentWidget;
  QPaintDevice* device;
  QPalette palette;
  QVector<TSignal> lastRecognition;  
};

#endif // CRECOGNIZER_H
