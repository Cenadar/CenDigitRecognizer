#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cworkinterface.h"
#include "cviewinterface.h"
#include "cdigitnetwork.h"
#include "cmessageshower.h"
#include "crecognizer.h"

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
  void on_actionShow_neurons_triggered();
  void on_actionFiles_triggered();
  void on_actionBase_directory_triggered();

private:
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

  Ui::MainWindow* ui;
  QRadioButton* digitRadioButtons[10];
  IRecognizer* recognizer;
};

#endif // MAINWINDOW_H
