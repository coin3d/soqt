#ifndef TICKMARK_H
#define TICKMARK_H

#include <qcanvas.h>
#include <Inventor/C/basic.h>

class TickMark : public QCanvasPolygon
{
public:
  enum { RTTI = 3141598 };

  TickMark(QCanvas * canvas);
  ~TickMark();

  int rtti() const;
  float getPos() const;

  SbBool isStart;
  SbBool isEnd;
};



#endif
