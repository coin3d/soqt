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

#include <assert.h>
#include <qpoint.h>
#include <qpainter.h>
#include <qcursor.h>
#include <Inventor/SbLinear.h>
#include "ColorCurve.h"
#include "CurveView.h"

CurveView::CurveView(QCanvas * c, QWidget* parent,	const char * name, WFlags f)
 : QCanvasView(c,parent,name,f), ptsize(3)
{
  this->canvas = c;

  // initialize the 5 curves
  for (int i = 0; i < 5; i++) {
    this->colormode = (ColorMode)i;
    ColorCurve::CurveType type = 
      (CurveView::ALPHA == (ColorMode)i) ? ColorCurve::CONSTANT : ColorCurve::LINEAR;
    this->colorcurves.append(new ColorCurve(type));
    this->canvasctrlpts.append(this->newCanvasCtrlPtList());
  }
  
  this->curvemode = CurveView::SMOOTH;
  this->colormode = CurveView::RED;

  this->mousepressed = FALSE;
  this->hideUnselected();
  this->insertGrid();
  this->initCurve();
  this->viewport()->setMouseTracking(TRUE);
}

CurveView::~CurveView()
{
  for (int i = 0; i < 5; i++) {
    delete this->colorcurves[i];
  }
}

void 
CurveView::initCurve()
{
  const uint8_t * curvepts = this->colorcurves[this->colormode]->getColorMap();

  for (int i = 2; i < this->colorcurves[this->colormode]->getNumPoints(); i+=2) {
    QCanvasLine * line = new QCanvasLine(this->canvas);
    line->setPoints(i-2, 255-curvepts[i-2], i, 255-curvepts[i]);
    line->setZ(1); // to make the curve be drawn on top of the grid
    line->show();
    this->curvesegments.append(line);
  }
}

void CurveView::insertGrid()
{
  int step = 256/4;
  QPen pen(Qt::gray);

  for (int i = step; i < 255; i+=step) {
    QCanvasLine * line = new QCanvasLine(this->canvas);
    line->setPoints(i, 0, i, 255);
    line->setPen(pen);
    line->show();
    this->grid.append(line);
  }

  for (int j = step; j < 255; j+=step) {
    QCanvasLine * line = new QCanvasLine(this->canvas);
    line->setPoints(0, j, 255, j);
    line->setPen(pen);
    line->show();
    this->grid.append(line);
  }  
}

void CurveView::contentsMousePressEvent(QMouseEvent* e)
{
  if (e->button() == Qt::LeftButton) {
    this->mousepressed = TRUE;
  }
  QPoint p = inverseWorldMatrix().map(e->pos());
  this->movingstart = p;
  this->lastpos = p;
  QCanvasItemList list = this->canvas->collisions(p);

  if (this->curvemode == CurveView::SMOOTH) {

    QCanvasItemList::Iterator it = list.begin();

    if ((it != list.end()) && ((*it)->rtti() == QCanvasRectangle::RTTI)) {
      if (e->button() == Qt::LeftButton) {
        this->movingitem = (*it);
      } else {
        if (this->canvasctrlpts[this->colormode].size() > 2) {
          delete (*it);
          this->canvasctrlpts[this->colormode].remove(*it);
        }
      }
    } else {
      if (e->button() == Qt::LeftButton) {
        QCanvasRectangle * ctrlpt = this->newControlPoint(p.x(), p.y());
        this->movingitem = ctrlpt;
        this->canvasctrlpts[this->colormode].append(ctrlpt);
      }
    }
    this->updateCurve();
  }

  this->canvas->update();
}

void
CurveView::contentsMouseReleaseEvent(QMouseEvent * e)
{
  this->mousepressed = FALSE;
  this->colorcurves[this->colormode]->notify();
}

void 
CurveView::contentsMouseMoveEvent(QMouseEvent* e)
{
	QPoint p = inverseWorldMatrix().map(e->pos());

  if (this->curvemode == CurveView::SMOOTH) {
    // change the cursor if it is over a control point
    QCanvasItemList list = this->canvas->collisions(p);
    QCanvasItemList::Iterator it = list.begin();

    if ((it != list.end()) && ((*it)->rtti() == QCanvasRectangle::RTTI)) {
      this->setCursor(QCursor::SizeAllCursor);
    } else {
      this->setCursor(QCursor::ArrowCursor);
    }
  
    if (this->movingitem && this->mousepressed) {
      int x = p.x();
      int y = p.y();
    
      if (x > 255 - this->ptsize) x = 255 - this->ptsize;
      if (y > 255 - this->ptsize) y = 255 - this->ptsize;
      if (x < this->ptsize) x = this->ptsize;
      if (y < this->ptsize) y = this->ptsize;

      this->movingitem->moveBy(x - movingstart.x(), y - movingstart.y());
	    this->movingstart = QPoint(x, y);
      this->updateCurve();
    }
  } else {
    if (this->mousepressed) {
      int lastx = lastpos.x();
      int lasty = lastpos.y();
      int currentx = p.x();
      int currenty = p.y();
      if ((lastx >= 0) && (lastx <= 255) && (currentx >= 0) && (currentx <= 255)) {

        if (currentx < lastx) { // swap
          currentx ^= lastx ^= currentx ^= lastx;
          currenty ^= lasty ^= currenty ^= lasty;
        }
        float x0 = float(lastx);
        float y0 = float(lasty);
        float x1 = float(currentx);
        float y1 = float(currenty);
        float dx = x1 - x0;

        // fill in the points between p and lastpos,
        // linearly interpolate the position
        for (int i = lastx; i < currentx; i++) {
          float w0 = (x1 - float(i)) / dx;
          float w1 = (float(i) - x0) / dx;
          int y = int(w0 * y0 + w1 * y1 + 0.5f);
          if (y > 255) y = 255;
          if (y < 0) y = 0;
          this->colorcurves[this->colormode]->setColorMapping(i, 255-y);
        }
        this->lastpos = p;
        this->updateCurve();
      }
    }
  }
  this->canvas->update();
}

void 
CurveView::drawContents(QPainter * p, int cx, int cy, int cw, int ch)
{
  QCanvasItemList::Iterator it;
  
    // draw the grid in the background
  it = this->grid.begin();
  for (; it != this->grid.end(); it++) {
    (*it)->draw(*p);
  }
  // draw the curve
  it = this->curvesegments.begin();
  for (; it != this->curvesegments.end(); it++) {
    (*it)->draw(*p);
  }
  // draw the control points
  it = this->canvasctrlpts[this->colormode].begin();
  for (; it != this->canvasctrlpts[this->colormode].end(); ++it) {
    if (this->curvemode == CurveView::SMOOTH) {
      (*it)->draw(*p);
    }
  }
}

void 
CurveView::hideUnselected()
{
  QCanvasItemList::Iterator it;

  for (int i = 0; i < 5; i++) {
    it = this->canvasctrlpts[i].begin();
    for (; it != this->canvasctrlpts[i].end(); ++it) {
      if ((this->colormode == i) && (this->curvemode != CurveView::FREE)) {
        (*it)->show();
      } else {
        (*it)->hide();
      }
    }
  }
}

void
CurveView::resetActive() 
{
  this->colorcurves[this->colormode]->resetCtrlPts();
  // QCanvasItemList::clear() only removes the items from the list, 
  // but they need to be deleted also.
  QCanvasItemList::Iterator it = this->canvasctrlpts[this->colormode].begin();
  for (; it != this->canvasctrlpts[this->colormode].end(); it++) {
    delete (*it);
  }
  this->canvasctrlpts[this->colormode].clear();
  this->canvasctrlpts[this->colormode] = this->newCanvasCtrlPtList();

  this->curvemode = CurveView::SMOOTH;

  this->updateCurve();
  this->canvas->update();
  emit this->curveChanged();

}

QCanvasItemList
CurveView::newCanvasCtrlPtList()
{
  QCanvasItemList list;
  int numpts = this->colorcurves[this->colormode]->getNumCtrlPoints();
  const SbVec3f * ctrlpts = this->colorcurves[this->colormode]->getCtrlPoints();

  for (int i = 0; i < numpts; i++) {
    list.append(this->newControlPoint(ctrlpts[i][0], 255.0f - ctrlpts[i][1]));
  }
  return list;
}

QCanvasRectangle *
CurveView::newControlPoint(int x, int y)
{
  QCanvasRectangle * rect
    = new QCanvasRectangle(x-this->ptsize, y-this->ptsize,
                           this->ptsize*2, this->ptsize*2,
                           this->canvas);
  rect->setZ(2); // the control points will be on top of the curve
  rect->show();
  return rect;
}

void 
CurveView::updateCurve()
{
  QCanvasItemList::iterator it;

  int i = 0;
  if (this->curvemode == CurveView::SMOOTH) { 
    QCanvasItemList list = this->canvasctrlpts[this->colormode];
    QCanvasItemList sortedlist;
    
    // Sort the list of control points
    while ((it = list.begin()) != list.end()) {
      QCanvasRectangle * smallest =
        (QCanvasRectangle *) this->smallestItem(&list);
      smallest->setBrush(Qt::black);
      sortedlist.append(smallest);
      list.remove(smallest);
    }
    
    int numpts = sortedlist.size();
    SbVec3f * ctrlpts = new SbVec3f[numpts];

    for (it =  sortedlist.begin(); it != sortedlist.end(); it++) {
        ctrlpts[i++] = SbVec3f((*it)->x() + this->ptsize, 255.0f - (*it)->y() - this->ptsize, 0.0f);
    }
    this->colorcurves[this->colormode]->setControlPoints(ctrlpts, numpts);
    delete [] ctrlpts;
  }

  i = 2;
  const uint8_t * curvepts = this->colorcurves[this->colormode]->getColorMap();
  it = this->curvesegments.begin();
  for (; it != this->curvesegments.end(); it++) {
    QCanvasLine* line = (QCanvasLine*)(*it);
    line->setPoints(i-2, 255-curvepts[i-2], i, 255-curvepts[i]);
    i+=2;
  }    
  emit this->curveChanged();
}

QCanvasItem * 
CurveView::smallestItem(QCanvasItemList * list)
{
  QCanvasItemList::Iterator it = list->begin();
  QCanvasItem * smallest = (*it);

  it++;
  for (; it != list->end(); ++it) {
    if ((*it)->x() < smallest->x()) {
      smallest = (*it);
    }
  }
  int x = smallest->x();
  return smallest;
}

void 
CurveView::changeColorMode(int mode)
{
  if (mode != this->colormode) {
    this->colormode = (ColorMode)mode;
    this->hideUnselected();
    this->updateCurve();
    this->canvas->update();
  }
}

void
CurveView::changeCurveMode(int mode)
{
  if (mode != this->curvemode) {
    this->curvemode = (CurveMode) mode;
    if (this->curvemode == CurveView::SMOOTH) {
      this->interpolateFromColors();
    }
    this->hideUnselected();
    this->updateCurve();
    this->canvas->update();
  }
}

void
CurveView::interpolateFromColors()
{
  for (int i = 0; i < 5; i++) {
    this->colorcurves[i]->interpolateColorMapping();
    const SbVec3f * ctrlpts = this->colorcurves[i]->getCtrlPoints();

    QCanvasItemList::Iterator it = this->canvasctrlpts[i].begin();
    for (; it != this->canvasctrlpts[i].end(); it++) {
      delete (*it);
    }
    this->canvasctrlpts[i].clear();
    for (int j = 0; j < this->colorcurves[i]->getNumCtrlPoints(); j++) {
      this->canvasctrlpts[i].append(this->newControlPoint(ctrlpts[j][0], 255.0f-ctrlpts[j][1]));
    }
  }
}

void
CurveView::setConstantValue(int value)
{
  this->colorcurves[this->colormode]->fill(value);
  this->updateCurve();
  this->canvas->update();
}

void 
CurveView::getColors(uint8_t * colors, int num, SoQtCurveWidget::Mode mode) const
{
  switch (mode) {
    case SoQtCurveWidget::RGB:
    case SoQtCurveWidget::RGBA: {
      uint8_t * rgba = new uint8_t[num];
      for (int i = 0; i < mode; i++) {
        this->colorcurves[i]->getColors(rgba, num);
        for (int j = 0; j < num; j++) {
          colors[j*mode + i] = rgba[j];
        }
      }
      delete [] rgba;
      break;
    }

    case SoQtCurveWidget::LUMINANCE_ALPHA: {
      uint8_t * luminance = new uint8_t[num];
      uint8_t * alpha= new uint8_t[num];
      
      this->colorcurves[CurveView::LUMINANCE]->getColors(luminance, num);
      this->colorcurves[CurveView::ALPHA]->getColors(alpha, num);

      for (int i = 0; i < num; i++) {
        colors[i*2 + 0] = luminance[i];
        colors[i*2 + 1] = alpha[i];
      }
      delete [] luminance;
      delete [] alpha;
      break;
    }

    case SoQtCurveWidget::LUMINANCE: {
      this->colorcurves[CurveView::LUMINANCE]->getColors(colors, num);
      break;
    }

    default:
      break;

  }
}

void 
CurveView::setColors(uint8_t * colors, int num, SoQtCurveWidget::Mode mode)
{

  switch (mode) {
  case SoQtCurveWidget::RGB:
  case SoQtCurveWidget::RGBA: {
    uint8_t * rgba = new uint8_t[num];
    for (int i = 0; i < mode; i++) {
      for (int j = 0; j < num; j++) {
        rgba[j] = colors[j*mode + i];
      }
      this->colorcurves[i]->setColors(rgba, num);
    }
    delete [] rgba;
    break;
  }

  case SoQtCurveWidget::LUMINANCE_ALPHA: {
    uint8_t * luminance = new uint8_t[num];
    uint8_t * alpha= new uint8_t[num];
    for (int i = 0; i < num; i++) {
      luminance[i] = colors[i*2 + 0];
      alpha[i]     = colors[i*2 + 1];
    }
    this->colorcurves[CurveView::LUMINANCE]->setColors(luminance, num);
    this->colorcurves[CurveView::ALPHA]->setColors(alpha, num);

    delete [] luminance;
    delete [] alpha;
    break;
  }        

  case SoQtCurveWidget::LUMINANCE: 
    this->colorcurves[CurveView::LUMINANCE]->setColors(colors, num);
    break;

  default:
    break;
  }

  this->changeCurveMode(CurveView::FREE);
}

QPixmap
CurveView::getPixmap(int width, int height) const
{
  QImage img(width, height, 32);
  QPixmap pm;
  if (this->colormode == CurveView::LUMINANCE) {
    const uint8_t * gray = this->colorcurves[CurveView::LUMINANCE]->getColorMap();
    pm = this->makePixmap(width, height, gray, gray, gray, width);
  } else {
    const uint8_t * red = this->colorcurves[CurveView::RED]->getColorMap();
    const uint8_t * green = this->colorcurves[CurveView::GREEN]->getColorMap();
    const uint8_t * blue = this->colorcurves[CurveView::BLUE]->getColorMap();
    pm = this->makePixmap(width, height, red, green, blue, width);
  }
  return pm;
}

QPixmap
CurveView::makePixmap(int w, int h, const uint8_t * r, const uint8_t * g, const uint8_t * b, int num) const
{
  // use an image since it is optimized for direct pixel access
  QImage img(w, h, 32);
  for (int i = 0; i < w; i++) {
    int original = (int) ((float(i) / float(w)) * 255.0f);
    for (int j = 0; j < h/2; j++) {
      img.setPixel(i, j, qRgb(r[i], g[i], b[i]));
    }
    // we'll split the image in half, making the bottom
    // half show the original color mapping for comparison
    for (j = h/2; j < h; j++) {
      img.setPixel(i, j, qRgb(original, original, original));
    }
  }
  return QPixmap(img);
}

QPixmap
CurveView::getGradient(int width, int height) const
{
  QImage img(width, height, 32);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      img.setPixel(j, i, qRgb(255-i, 255-i, 255-i));
    }
  }
  return QPixmap(img);
}

void
CurveView::setCallBack(ColorCurve::ChangeCB * cb, void * userData)
{
  for (int i = 0; i < 5; i++) {
    this->colorcurves[i]->setChangeCallBack(cb, userData);
  }
}