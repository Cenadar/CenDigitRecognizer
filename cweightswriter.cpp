#include "cweightswriter.h"

#include <QtCore>
#include <QtXml>
#include "settings.h"

void CFileWeightsWriter::Write() {
  QDomDocument document;

  QMap<QString, QString> M;
  M["idx"] = "1";
  document.appendChild(neuron->serialize(document, M));

  if (!QDir().exists(RecognizerSettings::default_weights_dir()))
    QDir().mkdir(RecognizerSettings::default_weights_dir());

  QFile file(RecognizerSettings::default_weights_dir() + "/" + file_name);

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    throw QString("Cannot open file: ") + file.fileName();

  QTextStream stream(&file);
  stream << document.toString(2);
  file.close();
}
