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

#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <qpoint.h>
#include <qevent.h>

#include <Inventor/SbPList.h>
#include <Inventor/events/SoEvent.h>
#include <Inventor/errors/SoDebugError.h>

#include <soqtdefs.h>
#include <Inventor/Qt/devices/SoQtDevice.h>
#include <Inventor/Qt/devices/SoQtInputFocus.h>
#include <Inventor/Qt/devices/SoQtKeyboard.h>
#include <Inventor/Qt/devices/SoQtMouse.h>
#include <Inventor/Qt/devices/SoQtSpaceball.h>

#ifdef HAVE_JOYSTICK_LINUX
#include <Inventor/Qt/devices/SoQtLinuxJoystick.h>
#endif

/*!
  \class SoQtDevice SoQtDevice.h Inventor/Qt/devices/SoQtDevice.h
  \brief The SoQtDevice class ...
  \ingroup devices

  FIXME: write class doc
*/

// *************************************************************************

SOQT_OBJECT_ABSTRACT_SOURCE(SoQtDevice);

/*!
  \internal
  This function initializes the type system for all the SoQt device
  classes.  It is called indirectly when calling SoQt::init().
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
#endif
}

// *************************************************************************

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

SoQtDevice::SoQtDevice(void)
{
  this->handlers = NULL;
}


/*!
  Virtual destructor.
*/

SoQtDevice::~SoQtDevice()
{
  if (this->handlers) {
    for (int i = 0; i < this->handlers->getLength(); i++) {
      SoQtDeviceHandlerInfo * info =
        (SoQtDeviceHandlerInfo *) (*this->handlers)[i];
      delete info;
    }
    delete this->handlers;
  }
}

// *************************************************************************

/*!
  FIXME: write function documentation
*/

void
SoQtDevice::setWindowSize(const SbVec2s size)
{
  this->widgetsize = size;
}

/*!
  FIXME: write function documentation
*/

SbVec2s
SoQtDevice::getWindowSize(void) const
{
  return this->widgetsize;
}

// *************************************************************************

/*!
  FIXME: write function documentation
*/

void
SoQtDevice::setEventPosition(SoEvent * event, int x, int y) const
{
  this->setLastEventPosition(QPoint(x, y));
  event->setPosition(SbVec2s(x, this->widgetsize[1] - y - 1));
}

/*!
  FIXME: write function documentation
*/

QPoint
SoQtDevice::getLastEventPosition(void)
{
  if (SoQtDevice::lasteventposition == NULL) {
#if SOQT_DEBUG && 0
    SoDebugError::postInfo("SoQtDevice::getLastEventPosition", "not initialized");
#endif // SOQT_DEBUG
    SoQtDevice::lasteventposition = new QPoint(-1, -1);
  }
  return *SoQtDevice::lasteventposition;
}

/*!
  FIXME: write doc
*/

void
SoQtDevice::setLastEventPosition(QPoint p)
{
  if (!SoQtDevice::lasteventposition) {
    // FIXME: deallocate on exit. 20000311 mortene.
    SoQtDevice::lasteventposition = new QPoint;
  }
  *SoQtDevice::lasteventposition = p;
}

// *************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtDevice::addEventHandler(QWidget * widget,
                            SoQtEventHandler * handler,
                            void * closure)
{
  if (this->handlers == NULL)
    this->handlers = new SbPList;
  SoQtDeviceHandlerInfo * info = new SoQtDeviceHandlerInfo;
  info->widget = widget;
  info->handler = handler;
  info->closure = closure;
  this->handlers->append(info);
}

/*!
  FIXME: write doc
*/

void
SoQtDevice::removeEventHandler(QWidget * widget,
                               SoQtEventHandler * handler,
                               void * closure)
{
  if (this->handlers) {
    for (int i = 0; i < this->handlers->getLength(); i++) {
      SoQtDeviceHandlerInfo * info =
        (SoQtDeviceHandlerInfo *) (*this->handlers)[i];
      if ((info->widget == widget) && (info->handler == handler) &&
           (info->closure == closure)) {
        delete info;
        this->handlers->remove(i);
        return;
      }
    }
  }
#if SOQT_DEBUG
  SoDebugError::post("SoQtDevice::removeEventHandler",
                     "tried to remove nonexisting handler");
#endif // SOQT_DEBUG
}

/*!
  FIXME: write doc
*/

void
SoQtDevice::invokeHandlers(QEvent * event)
{
  if (this->handlers) {
    bool dispatch = false;
    for (int i = 0; i < this->handlers->getLength(); i++) {
      SoQtDeviceHandlerInfo * info =
        (SoQtDeviceHandlerInfo *) (*this->handlers)[i];
      info->handler(info->widget, info->closure, event, &dispatch);
    }
  }
}

// *************************************************************************

#include <6dofEvents.h>

SoQt6dofDevicePressureEvent::SoQt6dofDevicePressureEvent(void)
  : inherited(QEvent::User, NULL)
{
  this->t = (QEvent::Type) soqt6dofDevicePressureEvent;
  this->trans_x = 0.0f;
  this->trans_y = 0.0f;
  this->trans_z = 0.0f;
  this->rot_x = 0.0f;
  this->rot_y = 0.0f;
  this->rot_z = 0.0f;
}

void
SoQt6dofDevicePressureEvent::setTranslation(float x, float y, float z)
{
  this->trans_x = x;
  this->trans_y = y;
  this->trans_z = z;
}

void
SoQt6dofDevicePressureEvent::getTranslation(float & x,
                                            float & y,
                                            float & z) const
{
  x = this->trans_x;
  y = this->trans_y;
  z = this->trans_z;
}

void
SoQt6dofDevicePressureEvent::setRotation(float x, float y, float z)
{
  this->rot_x = x;
  this->rot_y = y;
  this->rot_z = z;
}

void
SoQt6dofDevicePressureEvent::getRotation(float & x, float & y, float & z) const
{
  x = this->rot_x;
  y = this->rot_y;
  z = this->rot_z;
}

// *************************************************************************

SoQt6dofDeviceButtonEvent::SoQt6dofDeviceButtonEvent(void)
  : inherited(QEvent::User, NULL)
{
  this->t = (QEvent::Type) soqt6dofDeviceButtonReleasedEvent;
  this->state = 0;
  this->button = 0;
  this->buttons = 0;
}

void
SoQt6dofDeviceButtonEvent::setButton(unsigned int button)
{
  this->button = button;
  if ((1 << this->button) & this->state)
    this->t = (QEvent::Type) soqt6dofDeviceButtonPressedEvent;
  else
    this->t = (QEvent::Type) soqt6dofDeviceButtonReleasedEvent;
}

unsigned int
SoQt6dofDeviceButtonEvent::getButton(void) const
{
  return this->button;
}

void
SoQt6dofDeviceButtonEvent::setState(unsigned int state)
{
  this->state = state;
  if ((1 << this->button) & this->state)
    this->t = (QEvent::Type) soqt6dofDeviceButtonPressedEvent;
  else
    this->t = (QEvent::Type) soqt6dofDeviceButtonReleasedEvent;
}

unsigned int
SoQt6dofDeviceButtonEvent::getState(void) const
{
  return this->state;
}

void
SoQt6dofDeviceButtonEvent::setNumButtons(unsigned int buttons)
{
  this->buttons = buttons;
}

unsigned int
SoQt6dofDeviceButtonEvent::getNumButtons(void) const
{
  return this->buttons;
}

int
SoQt6dofDeviceButtonEvent::isButtonPress(void) const
{
  if (this->t == (QEvent::Type) soqt6dofDeviceButtonPressedEvent)
    return TRUE;
  return FALSE;
}

// *************************************************************************
