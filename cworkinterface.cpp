#include "cworkinterface.h"

CVisualWorkInterface::CVisualWorkInterface(QPoint baseCorner_,
                                           int cellHeight_, int cellWidth_,
                                           IPixelMatrixBuilder* builder_):
    baseCorner(baseCorner_), cellHeight(cellHeight_),
    cellWidth(cellWidth_), builder(builder_) {
}


void CVisualWorkInterface::paintEvent(QPaintEvent* /*event*/,
                                      QPaintDevice* device,
                                      const QPalette& palette) {
  QPainter painter(device);

  QVector<QPair<TColor, Qt::GlobalColor> > grad;
  grad.append(qMakePair(160, Qt::darkGreen));
  grad.append(qMakePair(96, Qt::darkGray));
  grad.append(qMakePair(48, Qt::gray));
  grad.append(qMakePair(1, Qt::lightGray));

  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen(Qt::darkGreen);
  for(int row = 0; row < RSettings::neuronHeight(); ++row)
    for(int col = 0; col < RSettings::neuronWidth(); ++col) {
      bool chosen = false;
      for(QVector<QPair<TColor, Qt::GlobalColor> >::Iterator it = grad.begin();
          !chosen && it != grad.end(); ++it) {
        if (builder->getColor(row, col) >= it->first) {
          painter.setBrush(it->second);
          chosen = true;
        }
      }

      if (!chosen) painter.setBrush(palette.background().color());

      painter.drawRect(baseCorner.x() + cellWidth*col,
                       baseCorner.y() + cellHeight*row,
                       cellWidth, cellHeight);
    }
}


void CVisualWorkInterface::mouseEvent(QMouseEvent *event) {
  int col = (event->x() - baseCorner.x()) / cellWidth;
  int row = (event->y() - baseCorner.y()) / cellHeight;
  int radiusSq = RSettings::penRadiusSq();
  int radius = 0;
  while(radius*radius < radiusSq) ++radius;
  if (0 <= row && row < RSettings::neuronHeight() &&
      0 <= col && col < RSettings::neuronWidth()) {
    builder->setColor(row, col, event->buttons() != Qt::RightButton);
    for(int dx = -radius; dx <= radius; ++dx)
      for(int dy = -radius; dy <= radius; ++dy)
        if (dx*dx + dy*dy < radiusSq)
          if (0 <= row + dy && row + dy < RSettings::neuronHeight() &&
              0 <= col + dx && col + dx < RSettings::neuronWidth())
            builder->setColor(row + dy, col + dx,
                               event->buttons() != Qt::RightButton ?
                  min(256*(radiusSq - (dx*dx + dy*dy))/radiusSq, 256) : 0);
  }
}


IPixelMatrix* CVisualWorkInterface::makePixelMatrix() const {
  return builder->build();
}

void CVisualWorkInterface::clear() {
  builder->clear();
}
