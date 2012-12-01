#include "cworkinterface.h"

CVisualWorkInterface::CVisualWorkInterface(QPoint baseCorner_,
                                           int cell_height_, int cell_width_,
                                           IPixelMatrixBuilder* builder_):
    base_corner(baseCorner_), cell_height(cell_height_),
    cell_width(cell_width_), builder(builder_) {
}


void CVisualWorkInterface::paintEvent(QPaintEvent* /*event*/,
                                      QPaintDevice* device,
                                      const QPalette& palette) {
  QPainter painter(device);

  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen(Qt::darkGreen);
  for(int row = 0; row < RSettings::neuronHeight(); ++row)
    for(int col = 0; col < RSettings::neuronWidth(); ++col) {
      if (builder->getColor(row, col) >= 160) // TODO formalize constants
        painter.setBrush(Qt::darkGreen);
      else if (builder->getColor(row, col) >= 96)
        painter.setBrush(Qt::darkGray);
      else if (builder->getColor(row, col) >= 48)
        painter.setBrush(Qt::gray);
      else if (builder->getColor(row, col) >= 1)
        painter.setBrush(Qt::lightGray);
      else if (builder->getColor(row, col) <= 0)
        painter.setBrush(palette.background().color());

      painter.drawRect(base_corner.x() + cell_width*col,
                       base_corner.y() + cell_height*row,
                       cell_width, cell_height);
    }
}


void CVisualWorkInterface::mouseEvent(QMouseEvent *event) {
  int col = (event->x() - base_corner.x()) / cell_width;
  int row = (event->y() - base_corner.y()) / cell_height;
  int radiusSq = RSettings::penRadiusSq();
  int radius = 0;
  while(radius*radius < radiusSq) ++radius;
  if (0 <= row && row < RSettings::neuronHeight() &&
      0 <= col && col < RSettings::neuronWidth()) {
    builder->setColor(row, col, event->buttons() != Qt::RightButton/* ? 1 : 0*/);
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
