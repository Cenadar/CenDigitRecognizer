#include "cmessageshower.h"

void CVisualMessageShower::showMessage(const QString &message) {
  QMessageBox msgBox;
  msgBox.setText(message);
  msgBox.exec();
}
