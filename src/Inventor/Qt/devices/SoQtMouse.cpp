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

#include <qevent.h>

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>

#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <qmetaobject.h>
#include <moc_SoQtMouse.cpp>

#include <soqtdefs.h>
#include <Inventor/Qt/SoQtBasic.h>
#include <Inventor/Qt/devices/SoQtMouse.h>

/*!
  \class SoQtMouse SoQtMouse.h Inventor/Qt/devices/SoQtMouse.h
  \brief The SoQtMouse class ...
  \ingroup devices

  FIXME: write class doc
*/

// *************************************************************************

SOQT_OBJECT_SOURCE(SoQtMouse);

// *************************************************************************

/*!
  \enum SoQtMouse::Events
  FIXME: write documentation for enum
*/
/*!
  \var SoQtMouse::Events SoQtMouse::BUTTON_PRESS
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtMouse::Events SoQtMouse::BUTTON_RELEASE
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtMouse::Events SoQtMouse::POINTER_MOTION
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtMouse::Events SoQtMouse::BUTTON_MOTION
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtMouse::Events SoQtMouse::ALL_EVENTS
  FIXME: write documentation for enum definition
*/

// *************************************************************************

/*!
  Constructor.
*/
SoQtMouse::SoQtMouse(int mask)
{
  this->eventmask = mask;

  // Allocate system-neutral event objects once and reuse.
  this->buttonevent = new SoMouseButtonEvent;
  this->locationevent = new SoLocation2Event;
}

/*!
  Destructor.
*/
SoQtMouse::~SoQtMouse()
{
  delete this->buttonevent;
  delete this->locationevent;
}

// *************************************************************************

/*!
  FIXME: write function documentation
*/

void
SoQtMouse::enable(
  QWidget *, // widget,
  SoQtEventHandler *, // handler,
  void *) // closure)
{
// FIXME: SOQT_STUB();
} // enable()

/*!
  FIXME: write function documentation
*/

void
SoQtMouse::disable(
  QWidget *, // widget,
  SoQtEventHandler *, // handler,
  void *) // closure)
{
// FIXME: SOQT_STUB();
} // disable()

// *************************************************************************

/*!
  Translates a native event from the underlying Qt toolkit into a
  generic event.

  This is then returned in the form of an instance of a subclass of
  the Inventor API's SoEvent class, either an SoMouseButtonEvent or an
  SoLocation2Event, depending on whether the native event is a
  mousebutton press or release, or a mousecursor movement event.

  The mapping of the mousebuttons upon generation of
  SoMouseButtonEvent events will be done as follows:

  <ul>
  <li>left mousebutton: SoMouseButtonEvent::BUTTON1
  <li>right mousebutton: SoMouseButtonEvent::BUTTON2
  <li>middle mousebutton, if available: SoMouseButtonEvent::BUTTON3
  <li>forward motion on a wheel mouse: SoMouseButtonEvent::BUTTON4
  <li>backward motion on a wheel mouse: SoMouseButtonEvent::BUTTON5
  </ul>

  Note that right mousebutton will always map to
  SoMouseButtonEvent::BUTTON2, even on a 3-button mouse.
*/
const SoEvent *
SoQtMouse::translateEvent(QEvent * event)
{
  SoEvent * super = NULL;
  QMouseEvent * mouseevent = (QMouseEvent *)event;


  // Convert wheel mouse events to Coin SoMouseButtonEvents.

#ifdef HAVE_SOMOUSEBUTTONEVENT_BUTTON5
  if (event->type() == QEvent::Wheel) {
    QWheelEvent * const wevent = (QWheelEvent *) event;
    if (wevent->delta() > 0)
      this->buttonevent->setButton(SoMouseButtonEvent::BUTTON4);
    else if (wevent->delta() < 0)
      this->buttonevent->setButton(SoMouseButtonEvent::BUTTON5);
#if SOQT_DEBUG
    else
      SoDebugError::postInfo("SoQtMouse::translateEvent",
                             "event, but no movement");
#endif // SOQT_DEBUG
    this->buttonevent->setState(SoButtonEvent::DOWN);
    super = this->buttonevent;
  }
#endif // HAVE_SOMOUSEBUTTONEVENT_BUTTON5


  // Check for mousebutton press/release. Note that mousebutton
  // doubleclick events are handled by converting them to two
  // press/release events. In other words: it's the user's
  // responsibility to translate pairs of singleclicks to
  // doubleclicks, if doubleclicks have a special meaning in the
  // application.

  // Qt actually sends this series of events upon dblclick:
  // QEvent::MouseButtonPress, QEvent::MouseButtonRelease,
  // QEvent::MouseButtonDblClick, QEvent::MouseButtonRelease.
  //
  // This was reported to Troll Tech as a possible bug, but was
  // confirmed by TT support to be the intended behavior.

  if (((event->type() == QEvent::MouseButtonDblClick) ||
       (event->type() == QEvent::MouseButtonPress) ||
       (event->type() == QEvent::MouseButtonRelease)) &&
      (this->eventmask & (BUTTON_PRESS | BUTTON_RELEASE))) {

    // Which button?
    switch (mouseevent->button()) {
    case LeftButton:
      this->buttonevent->setButton(SoMouseButtonEvent::BUTTON1);
// emulate right mouse button on MacIntosh platform by ctrl-click
#ifdef Q_WS_MAC
      if (mouseevent->state() & ControlButton)
        this->buttonevent->setButton(SoMouseButtonEvent::BUTTON2);
#endif // Q_WS_MAC
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
  if ((event->type() == QEvent::MouseMove) &&
      (this->eventmask & (POINTER_MOTION | BUTTON_MOTION))) {
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

