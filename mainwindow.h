#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cworkinterface.h>

namespace Ui {
  class MainWindow;
}

class MainWindow: public QMainWindow {
  Q_OBJECT
  
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
   
private slots:
  void on_CreateXMLButton_clicked();

private:
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

  Ui::MainWindow *ui;
  IWorkInterface* work_interface;
};

#endif // MAINWINDOW_H
