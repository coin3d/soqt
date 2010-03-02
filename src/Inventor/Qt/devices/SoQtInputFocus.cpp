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

// FIXME: this device class has not been implemented yet. 20020625 mortene.

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <Inventor/errors/SoDebugError.h>

#include <soqtdefs.h>
#include <Inventor/Qt/devices/SoQtInputFocus.h>
#include <Inventor/Qt/devices/SoGuiInputFocusP.h>

#include <qglobal.h>

#define PRIVATE(obj) ((obj)->pimpl)
#define PUBLIC(obj) ((obj)->pub)

// *************************************************************************

class SoQtInputFocusP : public SoGuiInputFocusP {
public:
  SoQtInputFocusP(SoQtInputFocus * p) : SoGuiInputFocusP(p) { }
};

// *************************************************************************

SoQtInputFocus::SoQtInputFocus(int mask)
{
  PRIVATE(this) = new SoQtInputFocusP(this);
  PRIVATE(this)->eventmask = mask;
}

SoQtInputFocus::~SoQtInputFocus()
{
  delete PRIVATE(this);
}

// *************************************************************************

void
SoQtInputFocus::enable(QWidget * widget, SoQtEventHandler * handler, void * closure)
{
  SOQT_STUB();
}

void
SoQtInputFocus::disable(QWidget * widget, SoQtEventHandler * handler, void * closure)
{
  SOQT_STUB();
}

// *************************************************************************

const SoEvent *
SoQtInputFocus::translateEvent(QEvent *)
{
  SOQT_STUB();
  return NULL;
}

// *************************************************************************

#undef PRIVATE
#undef PUBLIC
