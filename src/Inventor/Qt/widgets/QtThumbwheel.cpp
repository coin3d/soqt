/**************************************************************************\
 *
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
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
#include <qimage.h>
#include <qpixmap.h>

#include <Inventor/SbBasic.h>

#include <Inventor/Qt/common/ThumbWheel.h>

#include <Inventor/Qt/widgets/QtThumbwheel.h>

// *************************************************************************

static const int SHADEBORDERWIDTH = 2;

QtThumbwheel::QtThumbwheel(
  QWidget * parent,
  const char * name )
: QWidget( parent, name )
{
  this->constructor( QtThumbwheel::Vertical );
} // QtThumbwheel()

QtThumbwheel::QtThumbwheel(
  Orientation orientation,
  QWidget * parent,
  const char * name )
: QWidget( parent, name )
{
  this->constructor( orientation );
} // QtThumbwheel()

void
QtThumbwheel::constructor( // private
  Orientation orientation )
{
  this->orient = orientation;
  this->state = QtThumbwheel::Idle;
  this->wheelValue = this->tempWheelValue = 0.0f;
  this->wheel = new ThumbWheel;
  this->wheel->SetWheelMotionMethod( ThumbWheel::UNIFORM );
  this->wheel->SetWheelRangeBoundaryHandling( ThumbWheel::MODULATE );
  this->pixmaps = NULL;
  this->numPixmaps = 0;
  this->currentPixmap = -1;
} // constructor()

QtThumbwheel::~QtThumbwheel(
  void )
{
  delete this->wheel;
  if ( this->pixmaps ) {
    for ( int i = 0; i < this->numPixmaps; i++ )
      delete this->pixmaps[i];
    delete [] this->pixmaps;
  }
} // ~QtThumbwheel()

void
QtThumbwheel::setOrientation(
  Orientation orientation )
{
  this->orient = orientation;
  this->repaint();
} // setOrientation()

void
QtThumbwheel::paintEvent(
  QPaintEvent * event )
{
  QPainter p( this );
  QRect paintRect = event->rect();
  p.setClipRect(paintRect);
  QColorGroup g = this->colorGroup();
  QBrush fill( g.background() );

  int w, d;
  if ( this->orient == QtThumbwheel::Vertical ) {
    w = this->width() - 2*SHADEBORDERWIDTH - 6;
    d = this->height() - 2*SHADEBORDERWIDTH - 12;
  } else {
    w = this->height() - 2*SHADEBORDERWIDTH - 6;
    d = this->width() - 2*SHADEBORDERWIDTH - 12;
  }
  this->initWheel( d, w );

  int pixmap = this->wheel->GetBitmapForValue( this->tempWheelValue,
     (this->state == QtThumbwheel::Disabled) ? 0 : THUMBWHEEL_ENABLED );


  QRect wheelrect( SHADEBORDERWIDTH, SHADEBORDERWIDTH,
                   this->width() - 2*SHADEBORDERWIDTH,
                   this->height() - 2*SHADEBORDERWIDTH );

  qDrawShadePanel( &p, 0, 0, this->width(), this->height(),
                   g, FALSE, SHADEBORDERWIDTH, &fill );

  if ( this->orient == Vertical ) {
    wheelrect.setTop(    wheelrect.top() + 5 );
    wheelrect.setBottom( wheelrect.bottom() - 5 );
    wheelrect.setLeft(   wheelrect.left() + 2 );
    wheelrect.setRight(  wheelrect.right() - 2 );
  } else {
    wheelrect.setTop(    wheelrect.top() + 2 );
    wheelrect.setBottom( wheelrect.bottom() - 2 );
    wheelrect.setLeft(   wheelrect.left() + 5 );
    wheelrect.setRight(  wheelrect.right() - 5 );
  }
  
  qDrawPlainRect( &p, wheelrect.left(), wheelrect.top(), wheelrect.width(),
                  wheelrect.height(), QColor( 0, 0, 0 ), 1 );
  
  wheelrect.setTop(    wheelrect.top() + 1 );
  wheelrect.setBottom( wheelrect.bottom() - 1 );
  wheelrect.setLeft(   wheelrect.left() + 1 );
  wheelrect.setRight(  wheelrect.right() - 1 );
  // wheelrect is now wheel-only

  if ( this->orient == Vertical )
    bitBlt( this, wheelrect.left(), wheelrect.top(), this->pixmaps[pixmap],
            0, 0, w, d, CopyROP );
  else
    bitBlt( this, wheelrect.left(), wheelrect.top(), this->pixmaps[pixmap],
            0, 0, d, w, CopyROP );
  this->currentPixmap = pixmap;
} // paintEvent()

/*!
  \internal
*/

void
QtThumbwheel::mousePressEvent(
  QMouseEvent * event )
{
  if ( this->state != QtThumbwheel::Idle )
    return;

  if ( event->button() != LeftButton )
    return;

  QRect wheel;
  if ( this->orient == Vertical ) {
    wheel.setLeft( SHADEBORDERWIDTH + 3 );
    wheel.setTop( SHADEBORDERWIDTH + 6 );
    wheel.setRight( this->width() - SHADEBORDERWIDTH - 3 );
    wheel.setBottom( this->height() - SHADEBORDERWIDTH - 6 );
  } else {
    wheel.setLeft( SHADEBORDERWIDTH + 6 );
    wheel.setTop( SHADEBORDERWIDTH + 3 );
    wheel.setRight( this->width() - SHADEBORDERWIDTH - 6 );
    wheel.setBottom( this->height() - SHADEBORDERWIDTH - 3 );
  }

  if ( ! wheel.contains( event->pos() ) )
    return;

  this->state = QtThumbwheel::Dragging;

  if ( this->orient == QtThumbwheel::Vertical )
    this->mouseDownPos = event->pos().y() - SHADEBORDERWIDTH - 6;
  else
    this->mouseDownPos = event->pos().x() - SHADEBORDERWIDTH - 6;

  emit wheelPressed();
} // mousePressEvent()

/*!
  \internal
*/

void
QtThumbwheel::mouseMoveEvent(
  QMouseEvent * event )
{
  if ( this->state != QtThumbwheel::Dragging )
    return;

  int pos;
  if ( this->orient == QtThumbwheel::Vertical )
    pos = event->pos().y() - SHADEBORDERWIDTH - 6;
  else
    pos = event->pos().x() - SHADEBORDERWIDTH - 6;

  this->tempWheelValue = this->wheel->CalculateValue( this->wheelValue,
      this->mouseDownPos, pos - this->mouseDownPos );

  emit wheelMoved( this->tempWheelValue );

  this->repaint();
} // mouseMoveEvent()

/*!
  \internal
*/

void
QtThumbwheel::mouseReleaseEvent(
  QMouseEvent * event )
{
  if ( this->state != QtThumbwheel::Dragging )
    return;

  if ( event->button() != LeftButton )
    return;

  this->wheelValue = this->tempWheelValue;
  this->state = QtThumbwheel::Idle;
  emit wheelReleased();
} // mouseReleaseEvent()

/*
float
QtThumbwheel::getNormalizedValue(int pos) const
{
  int relativepos = pos - this->mouseDownPos;
  return (float) relativepos / (float)this->getWheelLength() * 2.0f;
} // getNormalizedValue()
*/

/*
int
QtThumbwheel::getWheelLength(void) const
{
  return this->orient == QtThumbwheel::Vertical ?
    this->height() : this->width();
} // getWheelLength()
*/

/*
int
QtThumbwheel::orientedCoord(const QPoint &p) const
{
  return (this->orient == QtThumbwheel::Horizontal) ?  p.x() : p.y();
} // orientedCoord()
*/

QSize
QtThumbwheel::sizeHint(void) const
{
  const int length = 88;
  int thick = 24;

  if (this->orient == QtThumbwheel::Horizontal)
    return QSize(length, thick);
  else
    return QSize(thick, length);
} // sizeHint()

QtThumbwheel::Orientation
QtThumbwheel::orientation(void) const
{
  return this->orient;
} // orientation()

float
QtThumbwheel::value(void) const
{
  return this->wheelValue;
} // value()

// *************************************************************************

void
QtThumbwheel::initWheel(
  int diameter,
  int width )
{
  int d, w;
  this->wheel->GetWheelSize( d, w );
  if ( d == diameter && w == width ) return;

  this->wheel->SetWheelSize( diameter, width );

  int pwidth = width;
  int pheight = diameter;
  if ( this->orient == Horizontal ) {
    pwidth = diameter;
    pheight = width;
  }

  if ( this->pixmaps != NULL ) {
    for ( int i = 0; i < this->numPixmaps; i++ )
      delete this->pixmaps[i];
    delete [] this->pixmaps;
  }

  this->numPixmaps = this->wheel->BitmapsRequired();
  this->pixmaps = new QPixmap * [this->numPixmaps];
  QImage image( pwidth, pheight, 32 );
  for ( int i = 0; i < this->numPixmaps; i++ ) {
    this->wheel->DrawBitmap( i, image.bits(),
        ((this->orient == Vertical) ? THUMBWHEEL_VERTICAL : 0) );
    this->pixmaps[i] = new QPixmap( QSize( pwidth, pheight) );
    this->pixmaps[i]->convertFromImage( image );
  }
} // initWheel()

// *************************************************************************

void
QtThumbwheel::setEnabled(
  bool enable )
{
  if ( enable )
    this->state = QtThumbwheel::Idle;
  else
    this->state = QtThumbwheel::Disabled;
  this->repaint();
} // setEnabled()

bool
QtThumbwheel::isEnabled(
  void ) const
{
  return ( this->state != QtThumbwheel::Disabled );
} // isEnabled()

void
QtThumbwheel::setValue(
  float value )
{
  this->wheelValue = this->tempWheelValue = value;
  this->repaint();
}

// *************************************************************************

enum boundaryHandling { 
  CLAMP, 
  MODULATE, 
  ACCUMULATE 
};

void
QtThumbwheel::setRangeBoundaryHandling(
  boundaryHandling handling )
{
  switch ( handling ) {
  case CLAMP:
    this->wheel->SetWheelRangeBoundaryHandling( ThumbWheel::CLAMP );
    break;
  case MODULATE:
    this->wheel->SetWheelRangeBoundaryHandling( ThumbWheel::MODULATE );
    break;
  case ACCUMULATE:
    this->wheel->SetWheelRangeBoundaryHandling( ThumbWheel::ACCUMULATE );
    break;
  default:
    assert( 0 && "impossible" );
  }
} // setRangeBoundaryHandling()

// *************************************************************************

QtThumbwheel::boundaryHandling
QtThumbwheel::getRangeBoundaryHandling(
  void ) const
{
  switch ( this->wheel->GetWheelRangeBoundaryHandling() ) {
  case ThumbWheel::CLAMP:
    return CLAMP;
  case ThumbWheel::MODULATE:
    return MODULATE;
  case ThumbWheel::ACCUMULATE:
    return ACCUMULATE;
  default:
    assert( 0 && "impossible" );
  }
  return CLAMP; // never reached
} // getRangeBoundaryHandling()

// *************************************************************************
