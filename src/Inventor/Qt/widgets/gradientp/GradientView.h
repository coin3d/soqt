#ifndef GRADIENT_VIEW_H
#define GRADIENT_VIEW_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2003 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org> for more information.
 *
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no>.
 *
\**************************************************************************/

#include <qcanvas.h>
#include <Inventor/Qt/widgets/Gradient.h>

class TickMark;
class QPainter;
class QMouseEvent;
class QResizeEvent;
class ImageItem;
class QPopupMenu;

class GradientView : public QCanvasView
{
  Q_OBJECT

public:
  GradientView(QCanvas * c = 0,
               const Gradient & g = Gradient(), 
               QWidget * parent = 0, 
               const char * name = 0, 
               WFlags f = 0);
  
  ~GradientView();

  void setGradient(const Gradient & grad);
  const Gradient & getGradient(void) const;
  void insertTick(float t);
  float getSelectedPos(void);
  void setChangeCallback(Gradient::ChangeCB * cb, void * userdata);

public slots:
  void updateTicks(void);
  void updateView(void);
  
private slots:
  void setColorRight(void);
  void setColorLeft(void);
  void chooseColorLeft(void);
  void chooseColorRight(void);
  void insertTick(void);
  void centerTick(void);
  void deleteTick(void);
  
signals:
  void viewChanged(void);
  void tickSelected(void);
  void mouseMoved(int x);
  void ticksChanged(void);

protected:
  void contentsMousePressEvent(QMouseEvent *);
  void contentsMouseMoveEvent(QMouseEvent *);
  void viewportResizeEvent(QResizeEvent *);
  void keyPressEvent(QKeyEvent * e);
  void buildMenu();
  void unselectAll(void);

private:
  TickMark * newTick(int x);
  QCanvas * canvas;
  Gradient grad;
  ImageItem * gradItem;
  ImageItem * selectionMarker;
  QPopupMenu * menu;
  TickMark * movingItem;
  TickMark * selectedMark;
  QValueList<TickMark*> tickMarks;

  int startIndex;
  int endIndex;
  QPoint moving_start;
  QRgb leftcolor;
  QRgb rightcolor;
};

#endif // GRADIENT_EDITOR_H
