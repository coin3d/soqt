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

/*!
  \class SoQtDevice SoQtDevice.h Inventor/Qt/devices/SoQtDevice.h
  \brief The SoQtDevice class ...
  \ingroup devices

  FIXME: write class doc
*/

#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

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
#endif // HAVE_JOYSTICK_LINUX

// *************************************************************************

struct SoQtDeviceHandlerInfo {
  QWidget * widget;
  SoQtEventHandler * handler;
  void * closure;
};

// *************************************************************************

class SoQtDeviceP {
public:
  SoQtDeviceP(void);
  ~SoQtDeviceP();

  static SbVec2s lasteventposition;
  SbVec2s widgetsize;
  SbPList * handlers;
};

SbVec2s SoQtDeviceP::lasteventposition;

SoQtDeviceP::SoQtDeviceP(void)
{
  this->handlers = NULL;
}

SoQtDeviceP::~SoQtDeviceP()
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

#define PRIVATE(p) (p->pimpl)

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
#endif // HAVE_JOYSTICK_LINUX
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

/*!
  Constructor.
*/

SoQtDevice::SoQtDevice(void)
{
  PRIVATE(this) = new SoQtDeviceP;
}

/*!
  Virtual destructor.
*/

SoQtDevice::~SoQtDevice()
{
  delete PRIVATE(this);
}

// *************************************************************************

/*!
  FIXME: write function documentation
*/

void
SoQtDevice::setWindowSize(const SbVec2s size)
{
  PRIVATE(this)->widgetsize = size;
}

/*!
  FIXME: write function documentation
*/

SbVec2s
SoQtDevice::getWindowSize(void) const
{
  return PRIVATE(this)->widgetsize;
}

// *************************************************************************

/*!
  FIXME: write function documentation
*/

void
SoQtDevice::setEventPosition(SoEvent * event, int x, int y) const
{
  SoQtDeviceP::lasteventposition = SbVec2s(x, y);
  event->setPosition(SbVec2s(x, PRIVATE(this)->widgetsize[1] - y - 1));
}

/*!
  FIXME: write function documentation
*/

SbVec2s
SoQtDevice::getLastEventPosition(void)
{
  return SoQtDeviceP::lasteventposition;
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
  if (PRIVATE(this)->handlers == NULL)
    PRIVATE(this)->handlers = new SbPList;
  SoQtDeviceHandlerInfo * info = new SoQtDeviceHandlerInfo;
  info->widget = widget;
  info->handler = handler;
  info->closure = closure;
  PRIVATE(this)->handlers->append(info);
}

/*!
  FIXME: write doc
*/

void
SoQtDevice::removeEventHandler(QWidget * widget,
                               SoQtEventHandler * handler,
                               void * closure)
{
  if (PRIVATE(this)->handlers) {
    for (int i = 0; i < PRIVATE(this)->handlers->getLength(); i++) {
      SoQtDeviceHandlerInfo * info =
        (SoQtDeviceHandlerInfo *) (*PRIVATE(this)->handlers)[i];
      if ((info->widget == widget) && (info->handler == handler) &&
           (info->closure == closure)) {
        delete info;
        PRIVATE(this)->handlers->remove(i);
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
  if (PRIVATE(this)->handlers) {
    bool dispatch = false;
    for (int i = 0; i < PRIVATE(this)->handlers->getLength(); i++) {
      SoQtDeviceHandlerInfo * info =
        (SoQtDeviceHandlerInfo *) (*PRIVATE(this)->handlers)[i];
      info->handler(info->widget, info->closure, event, &dispatch);
    }
  }
}

// *************************************************************************
