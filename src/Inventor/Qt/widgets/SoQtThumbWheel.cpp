/**************************************************************************\
 *
 *  This file is part of the Coin GUI toolkit libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation.  See the
 *  file LICENSE.LGPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you want to use this library with software that is incompatible
 *  licensewise with the LGPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/


// FIXME: should strongly consider making the thumbwheel a public
// class, as we've had several requests for it. 20020226 mortene.

#include <math.h>
#include <assert.h>
#include <stdio.h>

#include <qpainter.h>
#include <qdrawutil.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qmetaobject.h>
#include <moc_SoQtThumbWheel.cpp>

#include <Inventor/SbBasic.h>

#include <soqtdefs.h>
#include <Inventor/Qt/widgets/SoAnyThumbWheel.h>
#include <Inventor/Qt/widgets/SoQtThumbWheel.h>

// *************************************************************************

static const int SHADEBORDERWIDTH = 0;

SoQtThumbWheel::SoQtThumbWheel(QWidget * parent,
                               const char * name)
  : QWidget(parent, name)
{
  this->constructor(SoQtThumbWheel::Vertical);
}

SoQtThumbWheel::SoQtThumbWheel(Orientation orientation,
                               QWidget * parent,
                               const char * name)
  : QWidget(parent, name)
{
  this->constructor(orientation);
}

void
SoQtThumbWheel::constructor(Orientation orientation)
{
  this->orient = orientation;
  this->state = SoQtThumbWheel::Idle;
  this->wheelValue = this->tempWheelValue = 0.0f;
  this->wheel = new SoAnyThumbWheel;
  this->wheel->setMovement(SoAnyThumbWheel::UNIFORM);
  this->wheel->setGraphicsByteOrder(SoAnyThumbWheel::ARGB);
  this->pixmaps = NULL;
  this->numPixmaps = 0;
  this->currentPixmap = -1;
}

SoQtThumbWheel::~SoQtThumbWheel()
{
  delete this->wheel;
  if (this->pixmaps) {
    for (int i = 0; i < this->numPixmaps; i++)
      delete this->pixmaps[i];
    delete [] this->pixmaps;
  }
}

void
SoQtThumbWheel::setOrientation(Orientation orientation)
{
  this->orient = orientation;
  this->repaint(FALSE);
}

void
SoQtThumbWheel::paintEvent(QPaintEvent * event)
{
  QPainter p(this);
  QRect paintRect = event->rect();
  p.setClipRect(paintRect);
  QColorGroup g = this->colorGroup();

  int w, d;
  if (this->orient == SoQtThumbWheel::Vertical) {
    w = this->width() - 12;
    d = this->height() - 6;
  } else {
    w = this->height() - 12;
    d = this->width() - 6;
  }

  // Handle resizing to too small dimensions gracefully.
  if ((d <= 0) || (w <= 0)) return;

  this->initWheel(d, w);

  int pixmap = this->wheel->getBitmapForValue(this->tempWheelValue,
                                              (this->state == SoQtThumbWheel::Disabled) ?
                                              SoAnyThumbWheel::DISABLED : SoAnyThumbWheel::ENABLED);

  QRect widgetrect(0, 0, this->width(), this->height());
  QRect wheelrect(widgetrect);

  if (this->orient == Vertical) {
    wheelrect.setTop(   wheelrect.top() + 2);
    wheelrect.setBottom(wheelrect.bottom() - 2);
    wheelrect.setLeft(  wheelrect.left() + 5);
    wheelrect.setRight( wheelrect.right() - 5);
  } else {
    wheelrect.setTop(   wheelrect.top() + 5);
    wheelrect.setBottom(wheelrect.bottom() - 5);
    wheelrect.setLeft(  wheelrect.left() + 2);
    wheelrect.setRight( wheelrect.right() - 2);
  }
  
  qDrawPlainRect(&p, wheelrect.left(), wheelrect.top(), wheelrect.width(),
                 wheelrect.height(), QColor(0, 0, 0), 1);
  
  wheelrect.setTop(   wheelrect.top() + 1);
  wheelrect.setBottom(wheelrect.bottom() - 1);
  wheelrect.setLeft(  wheelrect.left() + 1);
  wheelrect.setRight( wheelrect.right() - 1);
  // wheelrect is now wheel-only

  if (this->orient == Vertical)
    bitBlt(this, wheelrect.left(), wheelrect.top(), this->pixmaps[pixmap],
           0, 0, w, d, CopyROP);
  else
    bitBlt(this, wheelrect.left(), wheelrect.top(), this->pixmaps[pixmap],
           0, 0, d, w, CopyROP);
  this->currentPixmap = pixmap;
}

/*!
  \internal
*/

void
SoQtThumbWheel::mousePressEvent(QMouseEvent * event)
{
  if (this->state != SoQtThumbWheel::Idle)
    return;

  if (event->button() != LeftButton)
    return;

  QRect wheel;
  if (this->orient == Vertical) {
    wheel.setLeft(SHADEBORDERWIDTH + 3);
    wheel.setTop(SHADEBORDERWIDTH + 6);
    wheel.setRight(this->width() - SHADEBORDERWIDTH - 3);
    wheel.setBottom(this->height() - SHADEBORDERWIDTH - 6);
  } else {
    wheel.setLeft(SHADEBORDERWIDTH + 6);
    wheel.setTop(SHADEBORDERWIDTH + 3);
    wheel.setRight(this->width() - SHADEBORDERWIDTH - 6);
    wheel.setBottom(this->height() - SHADEBORDERWIDTH - 3);
  }

  if (! wheel.contains(event->pos()))
    return;

  this->state = SoQtThumbWheel::Dragging;

  if (this->orient == SoQtThumbWheel::Vertical)
    this->mouseDownPos = event->pos().y() - SHADEBORDERWIDTH - 6;
  else
    this->mouseDownPos = event->pos().x() - SHADEBORDERWIDTH - 6;

  this->mouseLastPos = this->mouseDownPos;

  emit wheelPressed();
}

/*!
  \internal
*/

void
SoQtThumbWheel::mouseMoveEvent(QMouseEvent * event)
{
  if (this->state != SoQtThumbWheel::Dragging)
    return;

  if (this->orient == SoQtThumbWheel::Vertical)
    this->mouseLastPos = event->pos().y() - SHADEBORDERWIDTH - 6;
  else
    this->mouseLastPos = event->pos().x() - SHADEBORDERWIDTH - 6;
 

  this->tempWheelValue = this->wheel->calculateValue(this->wheelValue,
      this->mouseDownPos, this->mouseLastPos - this->mouseDownPos);

  emit wheelMoved(this->tempWheelValue);

  this->repaint(FALSE);
}

/*!
  \internal
*/

void
SoQtThumbWheel::mouseReleaseEvent(QMouseEvent * event)
{
  if (this->state != SoQtThumbWheel::Dragging)
    return;

  if (event->button() != LeftButton)
    return;

  this->wheelValue = this->tempWheelValue;
  this->mouseLastPos = this->mouseDownPos;
  this->state = SoQtThumbWheel::Idle;
  emit wheelReleased();
}

/*
float
SoQtThumbWheel::getNormalizedValue(int pos) const
{
  int relativepos = pos - this->mouseDownPos;
  return (float) relativepos / (float)this->getWheelLength() * 2.0f;
}
*/

/*
int
SoQtThumbWheel::getWheelLength(void) const
{
  return this->orient == SoQtThumbWheel::Vertical ?
    this->height() : this->width();
}
*/

/*
int
SoQtThumbWheel::orientedCoord(const QPoint &p) const
{
  return (this->orient == SoQtThumbWheel::Horizontal) ?  p.x() : p.y();
}
*/

QSize
SoQtThumbWheel::sizeHint(void) const
{
  const int length = 122;
  int thick = 24;

  if (this->orient == SoQtThumbWheel::Horizontal)
    return QSize(length, thick);
  else
    return QSize(thick, length);
}

SoQtThumbWheel::Orientation
SoQtThumbWheel::orientation(void) const
{
  return this->orient;
}

float
SoQtThumbWheel::value(void) const
{
  return this->wheelValue;
}

// *************************************************************************

void
SoQtThumbWheel::initWheel(int diameter, int width)
{
  int d, w;
  this->wheel->getSize(d, w);
  if (d == diameter && w == width) return;

  this->wheel->setSize(diameter, width);

  int pwidth = width;
  int pheight = diameter;
  if (this->orient == Horizontal) {
    pwidth = diameter;
    pheight = width;
  }

  if (this->pixmaps != NULL) {
    for (int i = 0; i < this->numPixmaps; i++)
      delete this->pixmaps[i];
    delete [] this->pixmaps;
  }

  this->numPixmaps = this->wheel->getNumBitmaps();
  this->pixmaps = new QPixmap * [this->numPixmaps];
  QImage image(pwidth, pheight, 32, 0);
  for (int i = 0; i < this->numPixmaps; i++) {
    this->wheel->drawBitmap(i, image.bits(), (this->orient == Vertical) ?
                            SoAnyThumbWheel::VERTICAL : SoAnyThumbWheel::HORIZONTAL);
    this->pixmaps[i] = new QPixmap(QSize(pwidth, pheight));
    this->pixmaps[i]->convertFromImage(image);
  }
}

// *************************************************************************

void
SoQtThumbWheel::setEnabled(bool enable)
{
  if (enable)
    this->state = SoQtThumbWheel::Idle;
  else
    this->state = SoQtThumbWheel::Disabled;
  this->repaint(FALSE);
}

bool
SoQtThumbWheel::isEnabled(void) const
{
  return (this->state != SoQtThumbWheel::Disabled);
}

void
SoQtThumbWheel::setValue(float value)
{
  this->wheelValue = this->tempWheelValue = value;
  this->mouseDownPos = this->mouseLastPos;
  this->repaint(FALSE);
}

// *************************************************************************

void
SoQtThumbWheel::setRangeBoundaryHandling(boundaryHandling handling)
{
  switch (handling) {
  case CLAMP:
    this->wheel->setBoundaryHandling(SoAnyThumbWheel::CLAMP);
    break;
  case MODULATE:
    this->wheel->setBoundaryHandling(SoAnyThumbWheel::MODULATE);
    break;
  case ACCUMULATE:
    this->wheel->setBoundaryHandling(SoAnyThumbWheel::ACCUMULATE);
    break;
  default:
    assert(0 && "impossible");
  }
}

// *************************************************************************

SoQtThumbWheel::boundaryHandling
SoQtThumbWheel::getRangeBoundaryHandling(void) const
{
  switch (this->wheel->getBoundaryHandling()) {
  case SoAnyThumbWheel::CLAMP:
    return CLAMP;
  case SoAnyThumbWheel::MODULATE:
    return MODULATE;
  case SoAnyThumbWheel::ACCUMULATE:
    return ACCUMULATE;
  default:
    assert(0 && "impossible");
  }
  return CLAMP; // never reached
}

// *************************************************************************
