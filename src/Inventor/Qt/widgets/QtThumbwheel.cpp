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

static const char rcsid[] =
  "$Id$";

#include <math.h>
#include <assert.h>
#include <stdio.h>

#include <qpainter.h>
#include <qdrawutil.h>

#include <Inventor/SbBasic.h>

#include <Inventor/Qt/widgets/QtThumbwheel.h>


static const int SHADEBORDERWIDTH = 2;


QtThumbwheel::QtThumbwheel(QWidget *parent, const char *name)
  : QWidget(parent, name)
{
  this->orient = QtThumbwheel::Vertical;
  this->init();
}

QtThumbwheel::QtThumbwheel(Orientation orientation, QWidget *parent,
                           const char *name)
  : QWidget(parent, name)
{
  this->orient = orientation;
  this->init();
}

void
QtThumbwheel::init(void)
{
  this->clickOffset = 0;
  this->state = QtThumbwheel::Idle;
  this->midpositionvalue = 0.0f;
  this->wheelvalue = 0.0f;
}

void
QtThumbwheel::setOrientation(Orientation orientation)
{
  this->orient = orientation;
  this->repaint();
}


//
// remaps values using a cosine func
//
static int
cosmap(const float pos, const int maxval, float offset)
{
#if 0 // linear mapping
  return pos;
#else // cosine mapping
  float t = pos/((float)maxval); // [0,1]

  t *= (1.0f-2*offset);
  t += offset;
  t *= M_PI;
  t = cos(t);

  t /= cos(offset); // normalize [-1, 1]

  t = -t;
  t += 1.0f;

  t *= 0.5f;

  return (int)(maxval * t);
#endif
}

void
QtThumbwheel::paintEvent(QPaintEvent *e)
{
  QPainter p(this);
  QRect paintRect = e->rect();
  p.setClipRect(paintRect);
  QColorGroup g = this->colorGroup();
  QBrush fill(g.background());


  // FIXME: make this effect look a little better... 990418 mortene.

  qDrawShadePanel(&p, 0, 0, this->width(), this->height(),
                  g, FALSE, SHADEBORDERWIDTH, &fill);

  QRect wheelrect(SHADEBORDERWIDTH, SHADEBORDERWIDTH,
                  this->width() - 2*SHADEBORDERWIDTH,
                  this->height() - 2*SHADEBORDERWIDTH);

//    const int numLines =
//        (this->orient == QtThumbwheel::Vertical) ?
//        wheelrect.height()/16 : wheelrect.width()/16;


  const int numLines = 10;

  for (int i=0; i < numLines+1; i++) {
    QPoint topleft, botright;
    int length =
      (this->orient == QtThumbwheel::Vertical) ?
      wheelrect.height() : wheelrect.width();
    float space = float(length) / float(numLines);
    int offset = int(this->wheelvalue * length) % int(space);

    float pos;

    switch (this->orient) {
    case QtThumbwheel::Vertical:
      pos = wheelrect.top()  +
        cosmap(float(wheelrect.height())/float(numLines) * i + offset,
               length, 0.08);
      topleft.setX(wheelrect.left());
      topleft.setY(pos);
      botright.setX(wheelrect.right());
      botright.setY(pos);
      break;
    case QtThumbwheel::Horizontal:
      pos = wheelrect.left() +
        cosmap(float(wheelrect.width())/float(numLines) * i + offset,
               length, 0.08);
      topleft.setX(pos);
      topleft.setY(wheelrect.top());
      botright.setX(pos);
      botright.setY(wheelrect.bottom());
      break;
    default:
      assert(0); // shouldn't happen
      break;
    }

    qDrawShadeLine(&p,
                   topleft.x(),
                   topleft.y(),
                   botright.x(),
                   botright.y(),
                   g, FALSE, 1, 1);
  }
}

void
QtThumbwheel::mousePressEvent(QMouseEvent *e)
{
  if (e->button() != LeftButton) return;

  this->state = QtThumbwheel::Dragging;
  this->clickOffset = (QCOORD)(this->orientedCoord(e->pos()));
  emit wheelPressed();
}

void
QtThumbwheel::mouseMoveEvent(QMouseEvent *e)
{
  if (this->state != QtThumbwheel::Dragging) return;

  float val = this->getNormalizedValue(this->orientedCoord(e->pos()));

  // Need to remember this for the paint().
  this->wheelvalue = val + this->midpositionvalue;

  emit wheelMoved(this->wheelvalue);
  this->repaint();
}

void
QtThumbwheel::mouseReleaseEvent(QMouseEvent *e)
{
  if (e->button() != LeftButton) return;

  this->midpositionvalue +=
    this->getNormalizedValue(this->orientedCoord(e->pos()));

  this->state = QtThumbwheel::Idle;
  emit wheelReleased();
}

float
QtThumbwheel::getMidpointValue(void) const
{
  return this->midpositionvalue;
}

void
QtThumbwheel::setMidpointValue(float val)
{
  this->midpositionvalue = val;
}

float
QtThumbwheel::getNormalizedValue(int pos) const
{
  int relativepos = pos - this->clickOffset;
  return (float)relativepos/(float)this->getWheelLength() * 2.0f;
}

int
QtThumbwheel::getWheelLength(void) const
{
  return this->orient == QtThumbwheel::Vertical ?
    this->height() : this->width();
}

int
QtThumbwheel::orientedCoord(const QPoint &p) const
{
  return (this->orient == QtThumbwheel::Horizontal) ?  p.x() : p.y();
}

QSize
QtThumbwheel::sizeHint(void) const
{
  const int length = 84;
  int thick = 20;

  if (this->orient == QtThumbwheel::Horizontal)
    return QSize(length, thick);
  else
    return QSize(thick, length);
}

QtThumbwheel::Orientation
QtThumbwheel::orientation(void) const
{
  return this->orient;
}

float
QtThumbwheel::wheelValue(void) const
{
  return this->wheelvalue;
}
