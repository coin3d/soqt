/**************************************************************************\
 *
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

#ifndef __QTTHUMBWHEEL_H__
#define __QTTHUMBWHEEL_H__

#include "qwidget.h"
#include "qrangecontrol.h"


class QtThumbwheel : public QWidget, public QRangeControl
{
  Q_OBJECT
public:
  enum Orientation { Horizontal, Vertical };

  QtThumbwheel(QWidget * parent=0, const char * name=0);
  QtThumbwheel(Orientation, QWidget * parent=0, const char * name=0);

  void setOrientation(Orientation);
  Orientation orientation(void) const;

  float getMidpointValue(void) const;
  void setMidpointValue(float val);

  float wheelValue(void) const;

  QSize sizeHint(void) const;

signals:
  void wheelPressed();
  void wheelMoved(float value);
  void wheelReleased();

protected:
  void paintEvent(QPaintEvent *);

  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);

private:
  enum State { Idle, Dragging };

  void init(void);
  int getWheelLength(void) const;
  int orientedCoord(const QPoint &) const;
  float getNormalizedValue(int pos) const;

  QCOORD clickOffset;
  State state;
  Orientation orient;
  float midpositionvalue, wheelvalue;

  QtThumbwheel(const QtThumbwheel &);
  QtThumbwheel & operator=(const QtThumbwheel &);
};

#endif // !__QTTHUMBWHEEL_H__
