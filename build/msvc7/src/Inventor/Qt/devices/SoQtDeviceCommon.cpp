/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
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
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

// This file contains common sourcecode and documentation for the
// So[Gui]Device classes, in template form.

/*!
  \class SoQtDevice SoQtDevice.h Inventor/Qt/devices/SoQtDevice.h
  \brief The SoQtDevice class is the base class for the translation devices.
  \ingroup devices

  The SoQt device classes provide glue functionality for
  translating native GUI events from the underlying toolkit to
  Inventor scenegraph SoEvent events.

  The device classes are mainly of interest to application programmers
  when writing extensions for new types of devices, and seldom in
  other contexts -- so they can most often be ignored.
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <Inventor/Qt/devices/SoQtDevice.h>
#include <Inventor/Qt/devices/SoQtDeviceP.h>
#include <Inventor/SbPList.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/events/SoEvent.h>

#include <Inventor/Qt/devices/SoQtInputFocus.h>
#include <Inventor/Qt/devices/SoQtKeyboard.h>
#include <Inventor/Qt/devices/SoQtMouse.h>
#include <Inventor/Qt/devices/SoQtSpaceball.h>

#ifdef HAVE_JOYSTICK_LINUX
#include <Inventor/Qt/devices/SoQtLinuxJoystick.h>
#endif // HAVE_JOYSTICK_LINUX

#define PRIVATE(p) (p->pimpl)
#define PUBLIC(p) (p->pub)

// *************************************************************************

/*!
  \fn SoQtDevice::SoQtDevice(void)
  Constructor.  Protected to only enable invocation from derived device
  classes.
*/
/*!
  \fn SoQtDevice::~SoQtDevice()
  Public virtual destructor.
*/

/*!
  \fn void SoQtDevice::enable(QWidget * widget, SoQtEventHandler * handler, void * closure)

  This method will enable the device for the widget.

  \a handler is invoked with the \a closure argument when an event
  occur in \a widget.
*/

/*!
  \fn void SoQtDevice::disable(QWidget * widget, SoQtEventHandler * handler, void * closure)

  This method will disable the handler for the device.
*/

/*!
  \fn const SoEvent * SoQtDevice::translateEvent(QEvent * event)

  This method translates from native events to Open Inventor SoEvent
  events.
*/

/*!
  \fn void SoQtDevice::invokeHandlers(QEvent * event)

  Invoke all handlers registered with SoQtDevice::addEventHandler().
*/

// *************************************************************************

SOQT_OBJECT_ABSTRACT_SOURCE(SoQtDevice);

// *************************************************************************

/*!
  This function initializes the type system for all the SoQt
  device classes.  It is called indirectly when calling
  SoQt::init(), so the application programmer doesn't have to
  bother with it.
*/
void
SoQtDevice::initClasses(void)
{
  SoQtDevice::initClass();
  SoQtInputFocus::initClass();
  SoQtKeyboard::initClass();
  SoQtMouse::initClass();
  SoQtSpaceball::initClass();
#ifdef HAVE_JOYSTICK_LINUX
  SoQtLinuxJoystick::initClass();
#endif // HAVE_JOYSTICK_LINUX
}

// *************************************************************************

/*!
  This method sets the cached size of the window the device is
  "attached" to.
*/
void
SoQtDevice::setWindowSize(const SbVec2s size)
{
  PRIVATE(this)->widgetsize = size;
}

/*!
  This method returns the cached window size.
*/
SbVec2s
SoQtDevice::getWindowSize(void) const
{
  return PRIVATE(this)->widgetsize;
}

// *************************************************************************

/*!
  This method fills in the position information of \a event,
  translating the coordinates into the correct coordinate system.
*/
void
SoQtDevice::setEventPosition(SoEvent * event, int x, int y) const
{
  SoGuiDeviceP::lasteventposition = SbVec2s(x, y);
  event->setPosition(SbVec2s(x, PRIVATE(this)->widgetsize[1] - y - 1));
}

/*!
  Returns last event position that was set with
  SoQtDevice::setEventPosition().
 */
SbVec2s
SoQtDevice::getLastEventPosition(void)
{
  return SoGuiDeviceP::lasteventposition;
}

// *************************************************************************

/*!
  Stores an event \a handler for the \a widget, which can later be
  invoked with SoQtDevice::invokeHandlers(). Used by extension
  device types.
 */
void
SoQtDevice::addEventHandler(QWidget * widget,
                               SoQtEventHandler * handler,
                               void * closure)
{
  PRIVATE(this)->addEventHandler(widget, handler, closure);
}

/*!
  Remove a \a handler registered with SoQtDevice::addEventHandler().
 */
void
SoQtDevice::removeEventHandler(QWidget * widget,
                                  SoQtEventHandler * handler,
                                  void * closure)
{
  PRIVATE(this)->removeEventHandler(widget, handler, closure);
}

// *************************************************************************

#ifndef DOXYGEN_SKIP_THIS

// Remaining code is for the internal, private hidden implementation
// class.

SbVec2s SoGuiDeviceP::lasteventposition;

struct SoGuiDevicePHandlerInfo {
  QWidget * widget;
  SoQtEventHandler * handler;
  void * closure;
};

SoGuiDeviceP::SoGuiDeviceP(SoQtDevice * p)
{
  PUBLIC(this) = p;
  this->handlers = NULL;
  this->widgetsize = SbVec2s(0, 0);
}

SoGuiDeviceP::~SoGuiDeviceP()
{
  if (this->handlers) {
    for (int i = 0; i < this->handlers->getLength(); i++) {
      SoGuiDevicePHandlerInfo * info =
        (SoGuiDevicePHandlerInfo *) (*this->handlers)[i];
      delete info;
    }
    delete this->handlers;
  }
}

void
SoGuiDeviceP::addEventHandler(QWidget * widget,
                              SoQtEventHandler * handler,
                              void * closure)
{
  if (this->handlers == NULL) { this->handlers = new SbPList; }
  SoGuiDevicePHandlerInfo * info = new SoGuiDevicePHandlerInfo;
  info->widget = widget;
  info->handler = handler;
  info->closure = closure;
  this->handlers->append(info);
}

void
SoGuiDeviceP::removeEventHandler(QWidget * widget,
                                 SoQtEventHandler * handler,
                                 void * closure)
{
  if (this->handlers) {
    for (int i = 0; i < this->handlers->getLength(); i++) {
      SoGuiDevicePHandlerInfo * info =
        (SoGuiDevicePHandlerInfo *) (*this->handlers)[i];
      if ((info->widget == widget) && (info->handler == handler) &&
           (info->closure == closure)) {
        delete info;
        this->handlers->remove(i);
        return;
      }
    }
  }
#if SOQT_DEBUG
  SoDebugError::post("SoGuiDeviceP::removeEventHandler",
                     "tried to remove nonexisting handler");
#endif // SOQT_DEBUG
}

void
SoGuiDeviceP::invokeHandlers(HandlerCB * cb, QEvent * event)
{
  if (this->handlers) {
    for (int i = 0; i < this->handlers->getLength(); i++) {
      SoGuiDevicePHandlerInfo * info =
        (SoGuiDevicePHandlerInfo *) (*this->handlers)[i];
      cb(info->handler, info->widget, event, info->closure);
    }
  }
}

#endif // DOXYGEN_SKIP_THIS

#undef PRIVATE
#undef PUBLIC

