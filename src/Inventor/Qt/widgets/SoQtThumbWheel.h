/**************************************************************************
 *
 *  This file is part of the Coin SoQt GUI binding library.
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License version
 *  2.1 as published by the Free Software Foundation.  See the file
 *  LICENSE.LGPL at the root directory of the distribution for all the
 *  details.
 *
 *  If you want to use Coin SoQt for applications not compatible with the
 *  LGPL, please contact SIM to acquire a Professional Edition License.
 *
 *  Systems in Motion, Prof Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
 **************************************************************************/

//  $Id$

#ifndef SOQT_THUMBWHEEL_H
#define SOQT_THUMBWHEEL_H

#include <qwidget.h>
#include <qrangecontrol.h>

#include <Inventor/Qt/SoQtBasic.h>

class QPixmap;
class SoAnyThumbWheel;

// *************************************************************************

class SoQtThumbWheel : public QWidget, public QRangeControl
{
  Q_OBJECT

public:
  enum Orientation { Horizontal, Vertical };

  SoQtThumbWheel(QWidget * parent = 0, const char * name = 0);
  SoQtThumbWheel(Orientation, QWidget * parent = 0, const char * name = 0);
  ~SoQtThumbWheel(void);

  void setOrientation(Orientation);
  Orientation orientation(void) const;

  void setValue(float value);
  float value(void) const;

  void setEnabled(bool enable);
  bool isEnabled(void) const;

  enum boundaryHandling {
    CLAMP,
    MODULATE,
    ACCUMULATE
  };
  void setRangeBoundaryHandling(boundaryHandling handling);
  boundaryHandling getRangeBoundaryHandling(void) const;

  QSize sizeHint(void) const;

signals:
  void wheelPressed(void);
  void wheelMoved(float value);
  void wheelReleased(void);

protected:
  void paintEvent(QPaintEvent *);

  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);

private:
  void constructor(Orientation);

  SoQtThumbWheel(const SoQtThumbWheel & wheel);
  SoQtThumbWheel & operator = (const SoQtThumbWheel & wheel);

  enum State { Idle, Dragging, Disabled } state;

  Orientation orient;
  float wheelValue, tempWheelValue;
  int mouseDownPos, mouseLastPos;

  void initWheel(int diameter, int width);

  SoAnyThumbWheel * wheel;
  QPixmap ** pixmaps;
  int numPixmaps;
  int currentPixmap;

}; // class SoQtThumbWheel

// *************************************************************************

#endif // ! SOQT_THUMBWHEEL_H
