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

#include <assert.h>

#include <qevent.h>
// FIXME: get rid of this before 1.0 release (convert everything to Qt
// version 2.x API). 19990630 mortene.
#if QT_VERSION >= 200
#include <q1xcompatibility.h>
#endif // Qt v2.x

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>

#include <soqtdefs.h>
#include <Inventor/Qt/SoQtBasic.h>
#include <Inventor/Qt/devices/SoQtMouse.h>

#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

/*!
  \class SoQtMouse SoQtMouse.h Inventor/Qt/devices/SoQtMouse.h
  \brief The SoQtMouse class ...
  \ingroup qtdevices

  FIXME: write class doc
*/

// *************************************************************************

SOQT_TYPED_OBJECT_SOURCE(SoQtMouse, SoQtDevice);

// *************************************************************************

/*!
  \enum SoQtMouse::SoQtMouseEventMask
  FIXME: write documentation for enum
*/
/*!
  \var SoQtMouse::SoQtMouseEventMask SoQtMouse::ButtonPressMask
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtMouse::SoQtMouseEventMask SoQtMouse::ButtonReleaseMask
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtMouse::SoQtMouseEventMask SoQtMouse::PointerMotionMask
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtMouse::SoQtMouseEventMask SoQtMouse::ButtonMotionMask
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtMouse::SoQtMouseEventMask SoQtMouse::SO_QT_ALL_MOUSE_EVENTS
  FIXME: write documentation for enum definition
*/

// *************************************************************************

/*!
  Constructor.
*/

SoQtMouse::SoQtMouse(
  SoQtMouseEventMask mask )
{
  this->eventmask = mask;
  this->buttonevent = NULL;
  this->locationevent = NULL;
} // SoQtMouse()

/*!
  Destructor.
*/

SoQtMouse::~SoQtMouse(
  void )
{
  delete this->buttonevent;
  delete this->locationevent;
} // ~SoQtMouse()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

void
SoQtMouse::enable(
  QWidget *, // widget,
  SoQtEventHandler *, // handler,
  void * ) // closure )
{
  SOQT_STUB();
} // enable()

/*!
  FIXME: write function documentation
*/

void
SoQtMouse::disable(
  QWidget *, // widget,
  SoQtEventHandler *, // handler,
  void * ) // closure )
{
  SOQT_STUB();
} // disable()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

const SoEvent *
SoQtMouse::translateEvent(
  QEvent * event )
{
  SoEvent * super = NULL;
  QMouseEvent * mouseevent = (QMouseEvent *)event;

  // Check for mousebutton press/release. Note that mousebutton
  // doubleclick events are ignored, as double clicks also generate 2
  // pairs of press and release events. In other words: it's the
  // user's responsibility to translate pairs of singleclicks to
  // doubleclicks, if doubleclicks have a special meaning.

  // FIXME: check if the above statement is actually correct, as Qt
  // sends this series of events upon dblclick:
  // press,release,dblclick,release. Reported to Troll Tech as a
  // possible bug. 19991001 mortene.

#ifdef HAVE_SOMOUSEBUTTONEVENT_BUTTONS
  if ( event->type() == QEvent::Wheel ) {
    if ( !this->buttonevent )
      this->buttonevent = new SoMouseButtonEvent;
    QWheelEvent * const wevent = (QWheelEvent *) event;
    if ( wevent->delta() > 0 )
      this->buttonevent->setButton(SoMouseButtonEvent::BUTTON4);
    else if ( wevent->delta() < 0 )
      this->buttonevent->setButton(SoMouseButtonEvent::BUTTON5);
#if SOQT_DEBUG
    else
      SoDebugError::postInfo( "SoQtMouse::translateEvent",
        "event, but no movement" );
#endif // SOQT_DEBUG
    this->buttonevent->setState(SoButtonEvent::DOWN);
    super = this->buttonevent;
  }
#endif // HAVE_SOMOUSEBUTTONEVENT_BUTTONS

  if (((event->type() == Event_MouseButtonPress) ||
       (event->type() == Event_MouseButtonRelease)) &&
      (this->eventmask & (SoQtMouse::ButtonPressMask |
                          SoQtMouse::ButtonReleaseMask))) {

    // Allocate system-neutral event object once and reuse.
    if (!this->buttonevent) this->buttonevent = new SoMouseButtonEvent;

    // Which button?
    switch (mouseevent->button()) {
    case LeftButton:
      this->buttonevent->setButton(SoMouseButtonEvent::BUTTON1);
      break;
    case RightButton:
      this->buttonevent->setButton(SoMouseButtonEvent::BUTTON2);
      break;
    case MidButton:
      this->buttonevent->setButton(SoMouseButtonEvent::BUTTON3);
      break;
    default:
      assert(0 && "no such SoQtMouse button");
      break;
    }

    // Press or release?
    if (mouseevent->button() & mouseevent->state())
      this->buttonevent->setState(SoButtonEvent::UP);
    else
      this->buttonevent->setState(SoButtonEvent::DOWN);

    super = this->buttonevent;
  }


  // Check for mouse movement.
  if ((event->type() == Event_MouseMove) &&
      (this->eventmask & (SoQtMouse::PointerMotionMask |
                          SoQtMouse::ButtonMotionMask))) {
    // Allocate system-neutral event object once and reuse.
    if (!this->locationevent) this->locationevent = new SoLocation2Event;

    super = this->locationevent;
  }


  // Common settings for SoEvent superclass.
  if (super) {
    // Modifiers
    super->setShiftDown(mouseevent->state() & ShiftButton);
    super->setCtrlDown(mouseevent->state() & ControlButton);
    super->setAltDown(mouseevent->state() & AltButton);

    this->setEventPosition(super, mouseevent->x(), mouseevent->y());
    // FIXME: should be time of Qt event. 990211 mortene.
    super->setTime(SbTime::getTimeOfDay());
  }

  return super;
} // translateEvent()

// *************************************************************************

#if SOQT_DEBUG
static const char * getSoQtMouseRCSId(void) { return rcsid; }
#endif // SOQT_DEBUG

