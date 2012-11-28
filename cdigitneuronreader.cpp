#include "cdigitneuronreader.h"
#include <QFile>
#include <cassert>
#include "settings.h"
#include "cdigitneuronbuilder.h"


IDigitNeuron* CFileDigitNeuronReader::read() {
  QFile file(file_name);
  QDomDocument document;
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    throw QString("Cannot open to read ") + file_name;
  if (!document.setContent(&file))
    throw QString("Cannot parse content ") + file_name;
  file.close();

  QDomElement root = document.firstChildElement("Neuron");
  QDomElement elem;  
  QMap<QString, QString> attr;

  elem = find_first_element(root, "Height", attr);
  if (elem.text() != QString::number(RecognizerSettings::NeuronHeight()))
    throw QString("Uncorrect height");

  elem = find_first_element(root, "Width", attr);
  if (elem.text() != QString::number(RecognizerSettings::NeuronWidth()))
    throw QString("Uncorrect width");

  IDigitNeuronBuilder* builder = new CDigitNeuronBuilder;
  for(int row = 0; row < RecognizerSettings::NeuronHeight(); ++row) {
    for(int col = 0; col < RecognizerSettings::NeuronWidth(); ++col) {
      elem = find_first_element(root, "SynapseR" + QString::number(row) +
                                "C" + QString::number(col), attr);
      if (elem.text().toInt() != 0)
      builder->set_value(row, col, elem.text().toInt());
    }
  }
  document.clear();

  IDigitNeuron* neuron = builder->build();
  delete builder;
  return neuron;
}


QDomElement CFileDigitNeuronReader::find_first_element(
    QDomElement root, QString tagname, QMap<QString, QString> attr) {
  QDomNodeList list = root.elementsByTagName(tagname);
  QDomNode node;
  QDomElement elem;
  for(int i = 0; i < list.size(); ++i) {
    node = list.at(i);
    if (node.isElement()) {
      elem = node.toElement();
      bool coincides = true;
      for(QMap<QString, QString>::Iterator it = attr.begin();
          coincides && it != attr.end(); ++it) {
        if (elem.attribute(it.key()) != it.value()) coincides = false;
      }
      if (coincides) return elem;
    }
  }

  QString exception_message = "Cannot find " + tagname + " element\n";
  for(QMap<QString, QString>::Iterator it = attr.begin();
      it != attr.end(); ++it) {
    exception_message += "Attibute: " + it.key() + "; ";
    exception_message += "Value: " + it.value() + ";\n";
  }
  throw exception_message;
}
