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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <qmetaobject.h>
#include <moc_SoQtInputFocus.cpp>

#include <Inventor/errors/SoDebugError.h>

#include <soqtdefs.h>
#include <Inventor/Qt/SoQtBasic.h>
#include <Inventor/Qt/devices/SoQtInputFocus.h>

/*!
  \class SoQtInputFocus SoQtInputFocus.h Inventor/Qt/devices/SoQtInputFocus.h
  \brief The SoQtInputFocus class ...
  \ingroup devices

  FIXME: write class doc
*/

SOQT_OBJECT_SOURCE(SoQtInputFocus);

// *************************************************************************

/*!
  \enum SoQtInputFocus::Events
  FIXME: write doc
*/

/*!
  \var SoQtInputFocus::Events SoQtInputFocus::ENTER_WINDOW
  FIXME: write doc
*/

/*!
  \var SoQtInputFocus::Events SoQtInputFocus::LEAVE_WINDOW
  FIXME: write doc
*/

/*!
  \var SoQtInputFocus::Events SoQtInputFocus::ALL_EVENTS
  FIXME: write doc
*/

// *************************************************************************

/*!
  Constructor.
*/

SoQtInputFocus::SoQtInputFocus(int mask)
{
  this->eventmask = mask;
}

/*!
  Destructor.
*/

SoQtInputFocus::~SoQtInputFocus()
{
}

// *************************************************************************

/*!
  FIXME: write function documentation
*/

void
SoQtInputFocus::enable(QWidget *, // widget,
                       SoQtEventHandler *, // handler,
                       void *) // closure)
{
  SOQT_STUB();
}

/*!
  FIXME: write function documentation
*/

void
SoQtInputFocus::disable(QWidget *, // widget,
                        SoQtEventHandler *, // handler,
                        void *) // closure)
{
  SOQT_STUB();
}

// *************************************************************************

/*!
  FIXME: write function documentation
*/

const SoEvent *
SoQtInputFocus::translateEvent(QEvent *)
{
  SOQT_STUB();
  return NULL;
}

// *************************************************************************
