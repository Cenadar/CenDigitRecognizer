#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cworkinterface.h"
#include "cviewinterface.h"
#include "cdigitrecognizer.h"
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
  void on_actionTeach_from_base_triggered();

private:
  QString find_next_name(int digit);

  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

  Ui::MainWindow* ui;
  IWorkInterface* work_interface;
  IViewInterface* view_interface;
  IDigitRecognizer* recognizer;
  IMessageShower* messager;
  QRadioButton* digitRadioButtons[10];

  QVector<TSignal> last_recognition;
};

#endif // MAINWINDOW_H
