/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) by Kongsberg Oil & Gas Technologies.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg Oil & Gas Technologies
 *  about acquiring a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg Oil & Gas Technologies, Bygdoy Alle 5, 0257 Oslo, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <qevent.h>

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/Qt/devices/SoQtMouse.h>
#include <Inventor/Qt/devices/SoGuiMouseP.h>

#define PRIVATE(obj) ((obj)->pimpl)
#define PUBLIC(obj) ((obj)->pub)

// *************************************************************************

#ifndef DOXYGEN_SKIP_THIS

class SoQtMouseP : public SoGuiMouseP {
public:
  SoQtMouseP(SoQtMouse * p) : SoGuiMouseP(p) { }
};

#endif // !DOXYGEN_SKIP_THIS

// *************************************************************************

SoQtMouse::SoQtMouse(int mask)
{
  PRIVATE(this) = new SoQtMouseP(this);
  PRIVATE(this)->eventmask = mask;
}

SoQtMouse::~SoQtMouse()
{
  delete PRIVATE(this);
}

// *************************************************************************

void
SoQtMouse::enable(QWidget * widget, SoQtEventHandler * handler, void * closure)
{
  // FIXME: should add some magic here so Qt events are actually
  // enabled or disabled for the widget in question. 20020625 mortene.
}

void
SoQtMouse::disable(QWidget * widget, SoQtEventHandler * handler, void * closure)
{
  // FIXME: should add some magic here so Qt events are actually
  // enabled or disabled for the widget in question. 20020625 mortene.
}

// *************************************************************************

const SoEvent *
SoQtMouse::translateEvent(QEvent * event)
{
  SoEvent * conv = NULL;

  QWheelEvent * wheelevent =
    (event->type() == QEvent::Wheel) ? (QWheelEvent *)event : NULL;

  QMouseEvent * mouseevent =
    ((event->type() == QEvent::MouseButtonDblClick) ||
     (event->type() == QEvent::MouseButtonPress) ||
     (event->type() == QEvent::MouseButtonRelease) ||
     (event->type() == QEvent::MouseMove)) ?
    (QMouseEvent *)event : NULL;

  if (!wheelevent && !mouseevent) return NULL;

  // Convert wheel mouse events to Coin SoMouseButtonEvents.
  //
  // FIXME: should consider adding an SoMouseWheel event to Coin?
  // 20020821 mortene. (idea mentioned by Florian Link on
  // coin-discuss.)

#ifdef HAVE_SOMOUSEBUTTONEVENT_BUTTON5
  if (wheelevent) {
    if (wheelevent->delta() > 0)
      PRIVATE(this)->buttonevent->setButton(SoMouseButtonEvent::BUTTON4);
    else if (wheelevent->delta() < 0)
      PRIVATE(this)->buttonevent->setButton(SoMouseButtonEvent::BUTTON5);
#if SOQT_DEBUG
    else {
      SoDebugError::postInfo("SoQtMouse::translateEvent",
                             "event, but no movement");
    }
#endif // SOQT_DEBUG
    PRIVATE(this)->buttonevent->setState(SoButtonEvent::DOWN);
    conv = PRIVATE(this)->buttonevent;
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
      (PRIVATE(this)->eventmask & (BUTTON_PRESS | BUTTON_RELEASE))) {

    // Which button?
    switch (mouseevent->button()) {
    case Qt::LeftButton:
      // We default to setting BUTTON1 for LMB, but this can be
      // overridden below by another invocation of
      // SoButtonEvent::setButton() if modifier keys are used.
      PRIVATE(this)->buttonevent->setButton(SoMouseButtonEvent::BUTTON1);

// Emulate right mouse button on Mac OS X platform by ctrl-click.

// In Qt/Mac versions 3.0.x and all Qt/X11 versions (even when
// compiled on Mac OS X), Qt::ControlButton is mapped to the "Ctrl"
// key. Since Qt/Mac version 3.1.x, Qt::ControlButton is mapped to the
// "Apple" key. (According to qt-support, this is intended
// and not a bug.)

// Since the standard way of emulating right-click in the Mac world is
// ctrl-click, we have to check for "meta" on Qt/Mac >= 3.1.x

#if (defined(__APPLE__) && defined(Q_WS_X11)) || (defined(Q_WS_MAC) && QT_VERSION < 0x030100)
      if (mouseevent->state() & Qt::ControlButton)
        PRIVATE(this)->buttonevent->setButton(SoMouseButtonEvent::BUTTON2);
#elif (defined(Q_WS_MAC) && QT_VERSION >= 0x030100)

#if QT_VERSION >= 0x040000
      if (mouseevent->modifiers() & Qt::MetaModifier)
#else
      if (mouseevent->state() & Qt::MetaButton)
#endif
        PRIVATE(this)->buttonevent->setButton(SoMouseButtonEvent::BUTTON2);
#endif
      break;

    case Qt::RightButton:
      PRIVATE(this)->buttonevent->setButton(SoMouseButtonEvent::BUTTON2);
      break;

    case Qt::MidButton:
      PRIVATE(this)->buttonevent->setButton(SoMouseButtonEvent::BUTTON3);
      break;

      // Not sure if this can actually happen.
    case Qt::NoButton:
      PRIVATE(this)->buttonevent->setButton(SoMouseButtonEvent::ANY);
      break;

    default:
      // There used to be an assert here, but in Qt 3.1.1, at least,
      // QMouseEvent::button() can return with a value 0x0010 or
      // 0x0020 -- values that are not covered in the Qt::ButtonState
      // enum. This is reported to happen for an IntelliMouse with a
      // button 4 and 5 (for up/down navigation).
      //
      // Update: according to Troll Tech, the enums will be added to
      // the official API for the next release.
      PRIVATE(this)->buttonevent->setButton(SoMouseButtonEvent::ANY);
      break;
    }

    // Press or release?
    if (mouseevent->type() == QEvent::MouseButtonRelease)
      PRIVATE(this)->buttonevent->setState(SoButtonEvent::UP);
    else // QEvent::MouseButtonPress
      PRIVATE(this)->buttonevent->setState(SoButtonEvent::DOWN);

    conv = PRIVATE(this)->buttonevent;
  }


  // Check for mouse movement.
  if ((event->type() == QEvent::MouseMove) &&
      // FIXME: is this correct? BUTTON_MOTION means "motion with
      // buttons down". 20020625 mortene.
      (PRIVATE(this)->eventmask & (POINTER_MOTION | BUTTON_MOTION))) {
    conv = PRIVATE(this)->locationevent;
  }


  // Common settings for SoEvent superclass.
  if (conv) {
    // Modifiers
    if (mouseevent) {
#if QT_VERSION >= 0x040000
      conv->setShiftDown(mouseevent->modifiers() & Qt::ShiftModifier);
      conv->setCtrlDown(mouseevent->modifiers() & Qt::ControlModifier);
      conv->setAltDown(mouseevent->modifiers() & Qt::AltModifier);
#else
      conv->setShiftDown(mouseevent->state() & Qt::ShiftButton);
      conv->setCtrlDown(mouseevent->state() & Qt::ControlButton);
      conv->setAltDown(mouseevent->state() & Qt::AltButton);
#endif
      this->setEventPosition(conv, mouseevent->x(), mouseevent->y());
    }
    else { // wheelevent
#if QT_VERSION >= 0x040000
      conv->setShiftDown(wheelevent->modifiers() & Qt::ShiftModifier);
      conv->setCtrlDown(wheelevent->modifiers() & Qt::ControlModifier);
      conv->setAltDown(wheelevent->modifiers() & Qt::AltModifier);
#else
      conv->setShiftDown(wheelevent->state() & Qt::ShiftButton);
      conv->setCtrlDown(wheelevent->state() & Qt::ControlButton);
      conv->setAltDown(wheelevent->state() & Qt::AltButton);
#endif
      this->setEventPosition(conv, wheelevent->x(), wheelevent->y());
    }

    // FIXME: should be time of Qt event. 19990211 mortene.
    conv->setTime(SbTime::getTimeOfDay());
  }

  return conv;
}

// *************************************************************************

#undef PRIVATE
#undef PUBLIC
