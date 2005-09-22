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

/*!
  \class SoQtInputFocus SoQtInputFocus.h Inventor/Qt/devices/SoQtInputFocus.h
  \brief The SoQtInputFocus class is an abstraction for widget focus events as an input device.
  \ingroup devices

  This device class is a "virtual device" which can be used to get
  events when the mouse pointer enters or leaves a specific widget.
*/

// *************************************************************************

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <Inventor/Qt/devices/SoQtInputFocus.h>
#include <Inventor/Qt/devices/SoGuiInputFocusP.h>

// *************************************************************************

SOQT_OBJECT_SOURCE(SoQtInputFocus);

// *************************************************************************

/*!
  \enum SoQtInputFocus::Events

  Bit-wise enumeration over events handled by the SoQtInputFocus
  device class.  Used in the SoQtInputFocus constructor.
*/

/*!
  \var SoQtInputFocus::Events SoQtInputFocus::ENTER_WINDOW

  Maskbit for receiving events when focus comes to a widget.
*/

/*!
  \var SoQtInputFocus::Events SoQtInputFocus::LEAVE_WINDOW

  Maskbit for receiving events when focus leaves a widget.
*/

/*!
  \var SoQtInputFocus::Events SoQtInputFocus::ALL_EVENTS

  Combined bitmask for all possible events.
*/

/*!
  \fn SoQtInputFocus::SoQtInputFocus(int mask)

  Constructor. The \a mask specifies which focus-related events to
  handle. Others will just be ignored.
*/

// *************************************************************************

SoGuiInputFocusP::SoGuiInputFocusP(SoQtInputFocus * p)
{
  this->pub = p;
}

SoGuiInputFocusP::~SoGuiInputFocusP()
{
}

// *************************************************************************
