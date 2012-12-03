#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cworkinterface.h"
#include "cviewinterface.h"
#include "cdigitnetwork.h"
#include "cmessageshower.h"

namespace Ui {
  class MainWindow;
}

class MainWindow: public QMainWindow {
  Q_OBJECT
  
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
   
private slots:
  void on_RecognizeButton_clicked();
  void on_actionExit_triggered();
  void on_actionLoad_triggered();
  void on_TeachButton_clicked();
  void on_ClearDrawButton_clicked();
  void on_actionErase_neurons_triggered();
  void on_SaveXMLButton_clicked();
  void procEvents();
  void on_actionShow_neurons_triggered();
  void on_actionFiles_triggered();
  void on_actionBase_directory_triggered();

private:
  QString find_next_name(int digit);
  void teachFromFiles(QStringList examples, int digit, bool shoeMessage = true);

  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

  Ui::MainWindow* ui;
  IWorkInterface* paintingInterface;
  IViewInterface* resultsInterface;
  IDigitNetwork* network;
  IMessageShower* messager;
  QRadioButton* digitRadioButtons[10];

  QVector<TSignal> lastRecognition;
};

#endif // MAINWINDOW_H
