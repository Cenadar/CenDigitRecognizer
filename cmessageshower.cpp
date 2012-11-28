#include "cmessageshower.h"

void CVisualMessageShower::show_message(const QString &message) {
  QMessageBox msgBox;
  msgBox.setText(message);
  msgBox.exec();
}
