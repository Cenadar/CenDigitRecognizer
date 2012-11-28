#include "cviewinterface.h"

#include "libs/nightcharts.h"
#include "cdigitneuron.h"
#include <cmath>
#include <cassert>

void CViewInterface::paint(QVector<TSignal> sign) {
  QPainter painter;
  painter.begin(widget);
  Nightcharts PieChart;
  PieChart.setType(Nightcharts::Histogramm);//{Histogramm,Pie,DPie};
  PieChart.setLegendType(Nightcharts::Vertical);//{Round,Vertical}
  PieChart.setCords(base_corner.x(), base_corner.y(),
                    width, height);

  assert(sign.size() == 10);
  TSignal sum = 0;
  for(int i = 0; i < 10; ++i) sum += sign.at(i);
  if (sum < 1e-6) {
    sum = 1;
    sign.fill(0, 10);    
  }

  for(int i = 0; i < 10; ++i) {
    int v = (10 - i)%5*30 + 50;
    PieChart.addPiece("Digit " + QString::number(i),                      
                      QColor(v, 200, v),
                      int(sign[i] * 100.0 / double(sum) + 0.5));
  }  
  PieChart.draw(&painter);
  PieChart.drawLegend(&painter);
  painter.end();
}
