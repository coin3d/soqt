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

#if SOQT_DEBUG
static const char rcsid[] =
  "$Id$";
#endif // SOQT_DEBUG

/*!
  \class SoQtDevice SoQtDevice.h Inventor/Qt/devices/SoQtDevice.h
  \brief The SoQtDevice class ...
  \ingroup qtdevices

  FIXME: write class doc
*/

#include <Inventor/SbPList.h>
#include <Inventor/events/SoEvent.h>
#include <Inventor/errors/SoDebugError.h>

#include <soqtdefs.h>
#include <Inventor/Qt/devices/SoQtDevice.h>

/*!
  \typedef void SoQtDevice::SoQtEventHandler(QWidget *, void *, QEvent *, bool *)
  FIXME: write doc
*/

/*!
  \fn void SoQtDevice::enable(QWidget * widget, SoQtEventHandler * handler, void * closure)
  FIXME: write doc
*/
/*!
  \fn void SoQtDevice::disable(QWidget * widget, SoQtEventHandler * handler, void * closure)
  FIXME: write doc
*/
/*!
  \fn const SoEvent * SoQtDevice::translateEvent(QEvent * event)
  FIXME: write doc
*/

// *************************************************************************
// static variables

QPoint * SoQtDevice::lasteventposition = NULL;

// *************************************************************************

struct SoQtDeviceHandlerInfo {
  QWidget * widget;
  SoQtDevice::SoQtEventHandler * handler;
  void * closure;
};

// *************************************************************************

/*!
  Constructor.
*/

SoQtDevice::SoQtDevice(
  void )
{
  this->handlers = NULL;
} // SoQtDevice()


/*!
  Virtual destructor.
*/

SoQtDevice::~SoQtDevice( // virtual
  void )
{
  if ( this->handlers ) {
    for ( int i = 0; i < this->handlers->getLength(); i++ ) {
      SoQtDeviceHandlerInfo * info =
        (SoQtDeviceHandlerInfo *) (*this->handlers)[i];
      delete info;
    }
    delete this->handlers;
  }
} // ~SoQtDevice()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

void
SoQtDevice::setWindowSize(
  const SbVec2s size )
{
  this->widgetsize = size;
} // setWindowSize()

/*!
  FIXME: write function documentation
*/

SbVec2s
SoQtDevice::getWindowSize(
  void ) const
{
  return this->widgetsize;
} // getWindowSize()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

void
SoQtDevice::setEventPosition(
   SoEvent * event,
   int x,
   int y ) const
{
  this->setLastEventPosition( QPoint(x, y) );
  event->setPosition(SbVec2s(x, this->widgetsize[1] - y - 1));
} // setEventPosition()

/*!
  FIXME: write function documentation
*/

QPoint
SoQtDevice::getLastEventPosition(
  void ) // static
{
  if ( SoQtDevice::lasteventposition == NULL ) {
#if SOQT_DEBUG && 0
    SoDebugError::postInfo( "SoQtDevice::getLastEventPosition", "not initialized" );
#endif // SOQT_DEBUG
    SoQtDevice::lasteventposition = new QPoint( -1, -1 );
  }
  return *SoQtDevice::lasteventposition;
} // getLastEventPosition()

/*!
  FIXME: write doc
*/

void
SoQtDevice::setLastEventPosition(
   QPoint p ) // static
{
  if (!SoQtDevice::lasteventposition) {
    // FIXME: deallocate on exit. 20000311 mortene.
    SoQtDevice::lasteventposition = new QPoint;
  }
  *SoQtDevice::lasteventposition = p;
} // setLastEventPosition()

// *************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtDevice::addEventHandler(
  QWidget * widget,
  SoQtEventHandler * handler,
  void * closure )
{
  if ( this->handlers == NULL )
    this->handlers = new SbPList;
  SoQtDeviceHandlerInfo * info = new SoQtDeviceHandlerInfo;
  info->widget = widget;
  info->handler = handler;
  info->closure = closure;
  this->handlers->append( info );
} // addEventHandler()

/*!
  FIXME: write doc
*/

void
SoQtDevice::removeEventHandler(
  QWidget * widget,
  SoQtEventHandler * handler,
  void * closure )
{
  if ( this->handlers ) {
    for ( int i = 0; i < this->handlers->getLength(); i++ ) {
      SoQtDeviceHandlerInfo * info =
        (SoQtDeviceHandlerInfo *) (*this->handlers)[i];
      if ( (info->widget == widget) && (info->handler == handler) &&
           (info->closure == closure) ) {
        delete info;
        this->handlers->remove(i);
        return;
      }
    }
  }
#if SOQT_DEBUG
  SoDebugError::post( "SoQtDevice::removeEventHandler",
    "tried to remove nonexisting handler" );
#endif // SOQT_DEBUG
} // removeEventHandler()

/*!
  FIXME: write doc
*/

void
SoQtDevice::invokeHandlers(
  QEvent * event )
{
  if ( this->handlers ) {
    bool dispatch = false;
    for ( int i = 0; i < this->handlers->getLength(); i++ ) {
      SoQtDeviceHandlerInfo * info =
        (SoQtDeviceHandlerInfo *) (*this->handlers)[i];
      info->handler( info->widget, info->closure, event, &dispatch );
    }
  }
} // invokeHandlers()

// *************************************************************************

SoQt6dofDevicePressureEvent::SoQt6dofDevicePressureEvent(
  void )
: inherited( QEvent::User, NULL )
{
  this->t = (QEvent::Type) soqt6dofDevicePressureEvent;
  this->trans_x = 0.0f;
  this->trans_y = 0.0f;
  this->trans_z = 0.0f;
  this->rot_x = 0.0f;
  this->rot_y = 0.0f;
  this->rot_z = 0.0f;
} // SoQt6dofDevicePressureEvent()

void
SoQt6dofDevicePressureEvent::setTranslation(
  float x,
  float y,
  float z )
{
  this->trans_x = x;
  this->trans_y = y;
  this->trans_z = z;
} // setTranslation()

void
SoQt6dofDevicePressureEvent::getTranslation(
  float & x,
  float & y,
  float & z ) const
{
  x = this->trans_x;
  y = this->trans_y;
  z = this->trans_z;
} // getTranslation()

void
SoQt6dofDevicePressureEvent::setRotation(
  float x,
  float y,
  float z )
{
  this->rot_x = x;
  this->rot_y = y;
  this->rot_z = z;
} // setRotation()

void
SoQt6dofDevicePressureEvent::getRotation(
  float & x,
  float & y,
  float & z ) const
{
  x = this->rot_x;
  y = this->rot_y;
  z = this->rot_z;
} // getRotation()

// *************************************************************************

SoQt6dofDeviceButtonEvent::SoQt6dofDeviceButtonEvent(
  void )
: inherited( QEvent::User, NULL )
{
  this->t = (QEvent::Type) soqt6dofDeviceButtonReleasedEvent;
  this->state = 0;
  this->button = 0;
  this->buttons = 0;
} // SoQt6dofDeviceButtonEvent()

void
SoQt6dofDeviceButtonEvent::setButton(
  unsigned int button )
{
  this->button = button;
  if ( (1 << this->button) & this->state )
    this->t = (QEvent::Type) soqt6dofDeviceButtonPressedEvent;
  else
    this->t = (QEvent::Type) soqt6dofDeviceButtonReleasedEvent;
} // setButton()

unsigned int
SoQt6dofDeviceButtonEvent::getButton(
  void) const
{
  return this->button;
} // getButton()

void
SoQt6dofDeviceButtonEvent::setState(
  unsigned int state )
{
  this->state = state;
  if ( (1 << this->button) & this->state )
    this->t = (QEvent::Type) soqt6dofDeviceButtonPressedEvent;
  else
    this->t = (QEvent::Type) soqt6dofDeviceButtonReleasedEvent;
} // setState()

unsigned int
SoQt6dofDeviceButtonEvent::getState(
  void) const
{
  return this->state;
} // getState()

void
SoQt6dofDeviceButtonEvent::setNumButtons(
  unsigned int buttons )
{
  this->buttons = buttons;
} // setNumButtons()

unsigned int
SoQt6dofDeviceButtonEvent::getNumButtons(
  void) const
{
  return this->buttons;
} // getNumButtons()

int
SoQt6dofDeviceButtonEvent::isButtonPress(
  void ) const
{
  if ( this->t == (QEvent::Type) soqt6dofDeviceButtonPressedEvent )
    return TRUE;
  return FALSE;
} // isButtonPress()

// *************************************************************************

#if SOQT_DEBUG
static const char * getSoQtDeviceRCSId(void) { return rcsid; }
#endif // SOQT_DEBUG

