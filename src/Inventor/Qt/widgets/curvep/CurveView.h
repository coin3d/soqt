#ifndef CURVEVIEW_H
#define CURVEVIEW_H

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
#include <qimage.h>
#include <Inventor/SbBasic.h>
#include <Inventor/Qt/widgets/SoQtCurveWidget.h>

class ColorCurve;
class QCanvasItemList;
class QMouseEvent;
class QCanvasItem;
class QPoint;
class QKeyEvent;
class QFocusEvent;
class QResizeEvent;

class CurveView : public QCanvasView 
{
    Q_OBJECT // for signals and slots

public:
  CurveView(SoQtCurveWidget::Mode mode, 
            QCanvas * canvas, 
            QWidget * parent = 0, 
            const char * name = 0, 
            WFlags flags = 0);
  
  ~CurveView();

  enum CurveType { SMOOTH, FREE };
  
  void setMode(SoQtCurveWidget::Mode mode);
  void setColors(uint8_t * colors, int num);
  void getColors(uint8_t * colors, int num) const;
  void setCallBack(ColorCurve::ChangeCB * cb, void * userData);

public slots:
  void changeColorMode(int mode);
  void changeCurveMode(int mode);
  void setConstantValue(int value);
  void resetActive(void);

  QPixmap getPixmap(int width, int height) const;
  QPixmap getGradient(int width, int height) const;

signals:
  void curveChanged(void);
  
protected:
  void contentsMousePressEvent(QMouseEvent * e);
  void contentsMouseReleaseEvent(QMouseEvent * e);
  void contentsMouseMoveEvent(QMouseEvent * e);
  void drawContents(QPainter * p, int cx, int cy, int cw, int ch);

private:
  void interpolateFromColors();
  void initColorCurves(void);
  void initCanvasCurve(void);
  void hideUnselected(void);
  void updateCurve(void);
  void initGrid(void);
  
  QPixmap makePixmap(int w, int h, const uint8_t * r, const uint8_t * g, const uint8_t * b, int num) const;
  QCanvasRectangle * newControlPoint(int x, int y);
  QCanvasItemList newCanvasCtrlPtList(void);
  QCanvasItem * smallestItem(QCanvasItemList * list);

  SbBool mousepressed;
  QPoint movingstart;
  QPoint lastpos;
  QCanvas * canvas;
  QCanvasItem * movingitem;

  int colorindex;
  CurveType curvemode;
  SoQtCurveWidget::Mode colormode;
  
  const int ptsize;

  QValueList<QCanvasItemList> canvasctrlpts;
  QValueList<ColorCurve*> colorcurves;
    
  QCanvasItemList curvesegments;
  QCanvasItemList grid;
};

#endif // CURVEVIEW_H