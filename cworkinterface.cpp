#include "cworkinterface.h"

CVisualWorkInterface::CVisualWorkInterface(QPoint base_corner_,
                                           int cell_height_, int cell_width_,
                                           IPixelMatrixBuilder* builder_):
    base_corner(base_corner_), cell_height(cell_height_),
    cell_width(cell_width_), builder(builder_) {
}


void CVisualWorkInterface::paintEvent(QPaintEvent* /*event*/,
                                      QPaintDevice* device,
                                      const QPalette& palette) {
  QPainter painter(device);

  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen(Qt::darkGreen);
  for(int row = 0; row < RecognizerSettings::NeuronHeight(); ++row)
    for(int col = 0; col < RecognizerSettings::NeuronWidth(); ++col) {
      if (builder->get_color(row, col) >= 160) // TODO formalize constants
        painter.setBrush(Qt::darkGreen);
      else if (builder->get_color(row, col) >= 96)
        painter.setBrush(Qt::darkGray);
      else if (builder->get_color(row, col) >= 48)
        painter.setBrush(Qt::gray);
      else if (builder->get_color(row, col) >= 1)
        painter.setBrush(Qt::lightGray);
      else if (builder->get_color(row, col) <= 0)
        painter.setBrush(palette.background().color());

      painter.drawRect(base_corner.x() + cell_width*col,
                       base_corner.y() + cell_height*row,
                       cell_width, cell_height);
    }
}


void CVisualWorkInterface::mouseEvent(QMouseEvent *event) {
  int col = (event->x() - base_corner.x()) / cell_width;
  int row = (event->y() - base_corner.y()) / cell_height;
  int radiusSq = RecognizerSettings::PenRadiusSq();
  int radius = 0;
  while(radius*radius < radiusSq) ++radius;
  if (0 <= row && row < RecognizerSettings::NeuronHeight() &&
      0 <= col && col < RecognizerSettings::NeuronWidth()) {
    builder->set_color(row, col, event->buttons() != Qt::RightButton/* ? 1 : 0*/);
    for(int dx = -radius; dx <= radius; ++dx)
      for(int dy = -radius; dy <= radius; ++dy)
        if (dx*dx + dy*dy < radiusSq)
          if (0 <= row + dy && row + dy < RecognizerSettings::NeuronHeight() &&
              0 <= col + dx && col + dx < RecognizerSettings::NeuronWidth())
            builder->set_color(row + dy, col + dx,
                               event->buttons() != Qt::RightButton ?
                  min(256*(radiusSq - (dx*dx + dy*dy))/radiusSq, 256) : 0);
    // TODO: Solve problem with Qt::LeftButton and KDE moving.
  }
}


IPixelMatrix* CVisualWorkInterface::make_pixel_matrix() const {
  return builder->build();
}

void CVisualWorkInterface::clear() {
  builder->clear();
}
