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

#include <qevent.h>

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>

#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

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
SoQtMouse::enable(QWidget *, // widget,
                  SoQtEventHandler *, // handler,
                  void *) // closure)
{
// FIXME: SOQT_STUB();
}

/*!
  FIXME: write function documentation
*/

void
SoQtMouse::disable(QWidget *, // widget,
                   SoQtEventHandler *, // handler,
                   void *) // closure)
{
// FIXME: SOQT_STUB();
}

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
    case Qt::LeftButton:
      this->buttonevent->setButton(SoMouseButtonEvent::BUTTON1);
// emulate right mouse button on MacIntosh platform by ctrl-click
#ifdef Q_WS_MAC
      if (mouseevent->state() & ControlButton)
        this->buttonevent->setButton(SoMouseButtonEvent::BUTTON2);
#endif // Q_WS_MAC
      break;
    case Qt::RightButton:
      this->buttonevent->setButton(SoMouseButtonEvent::BUTTON2);
      break;
    case Qt::MidButton:
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
    super->setShiftDown(mouseevent->state() & Qt::ShiftButton);
    super->setCtrlDown(mouseevent->state() & Qt::ControlButton);
    super->setAltDown(mouseevent->state() & Qt::AltButton);

    this->setEventPosition(super, mouseevent->x(), mouseevent->y());
    // FIXME: should be time of Qt event. 990211 mortene.
    super->setTime(SbTime::getTimeOfDay());
  }

  return super;
}

// *************************************************************************
