#include "qpointarray.h"
#include "TickMark.h"

TickMark::TickMark(QCanvas * canvas)
: QCanvasPolygon(canvas)
{
  QPointArray pa(3);
  pa[0] = QPoint(-6,15);
  pa[1] = QPoint(6,15);
  pa[2] = QPoint(0,0);
  this->setPoints(pa);

  this->isEnd = FALSE;
  this->isStart = FALSE;
}

TickMark::~TickMark()
{
} 

int
TickMark::rtti() const
{
  return TickMark::RTTI;
}

float TickMark::getPos() const
{
  return float(this->x()) / ((float)canvas()->width() + 0.5f);
}
