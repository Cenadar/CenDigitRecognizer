#include "cneuronpainter.h"
#include <cassert>

void CNeuronPainter::paint(QVector<IDigitNeuron*> neurons) {
  assert(neurons.size() == 10);
  QPainter painter(device);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen(Qt::darkGreen);

  int maxAbs = 0;
  for(QVector<IDigitNeuron*>::Iterator neuron = neurons.begin();
      neuron != neurons.end(); ++neuron) {
    for(int row = 0; row < RecognizerSettings::NeuronHeight(); ++row)
      for(int col = 0; col < RecognizerSettings::NeuronWidth(); ++col)
        maxAbs = max(maxAbs, abs((*neuron)->getCoefficient(row, col)));
  }
  if (maxAbs == 0) maxAbs = 1; // Empty neurons

  QVector<QPoint> basePoints;
  for(int row = 0; row < 2; ++row)
    for(int col = 0; col < 5; ++col)
      basePoints << QPoint(col*(RecognizerSettings::NeuronWidth()*cellWidth + 10),
                           row*(RecognizerSettings::NeuronHeight()*cellHeight + 10));

  QVector<QPoint>::Iterator basePoint = basePoints.begin();
  for(QVector<IDigitNeuron*>::Iterator neuron = neurons.begin();
      neuron != neurons.end(); ++neuron, ++basePoint) {
    for(int row = 0; row < RecognizerSettings::NeuronHeight(); ++row)
      for(int col = 0; col < RecognizerSettings::NeuronWidth(); ++col) {
        int coefficient = (*neuron)->getCoefficient(row, col);
        bool sgnPos = coefficient > 0;
        coefficient = abs(coefficient) * 255 / maxAbs;

        QColor curColor;
        if (sgnPos) {
          curColor = QColor(255, 255 - coefficient, 255 - coefficient);
        } else {
          curColor = QColor(255 - coefficient, 255 - coefficient, 255);
        }

        painter.setBrush(curColor);
        painter.drawRect(basePoint->x() + col*cellWidth,
                         basePoint->y() + row*cellHeight,
                         cellWidth,
                         cellHeight);
      }
  }
}
