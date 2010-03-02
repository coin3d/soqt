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

// Most of the class documentation is found within the file
// common/devices/SoGuiDevice.cpp.in.

// *************************************************************************

#include <Inventor/Qt/devices/SoQtDevice.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <soqtdefs.h>
#include <Inventor/Qt/devices/SoQtDeviceP.h>

#include <qglobal.h>

#define PRIVATE(obj) ((obj)->pimpl)
#define PUBLIC(obj) ((obj)->pub)

// *************************************************************************

/*!
  \typedef void SoQtEventHandler(QWidget *, void *, QEvent *, bool *)
  FIXME: write doc
*/

// *************************************************************************

SoQtDevice::SoQtDevice(void)
{
  PRIVATE(this) = new SoQtDeviceP(this);
}

SoQtDevice::~SoQtDevice()
{
  delete PRIVATE(this);
}

// *************************************************************************

void
SoQtDevice::invokeHandlers(QEvent * event)
{
  PRIVATE(this)->invokeHandlers(SoQtDeviceP::invokeHandlerCB, event);
}

// *************************************************************************

#ifndef DOXYGEN_SKIP_THIS

// Code and data for the internal, private hidden implementation
// class.

SbBool
SoQtDeviceP::invokeHandlerCB(SoQtEventHandler * handler,
                             QWidget * widget,
                             QEvent * event,
                             void * handlerclosure)
{
  bool dispatch = false;
  handler(widget, handlerclosure, event, &dispatch);
  return TRUE;
}

#endif // DOXYGEN_SKIP_THIS

// *************************************************************************

#undef PRIVATE
#undef PUBLIC
