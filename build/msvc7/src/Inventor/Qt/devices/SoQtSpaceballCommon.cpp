/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2004 by Systems in Motion.  All rights reserved.
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
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

/*!
  \class SoQtSpaceball SoQtSpaceball.h Inventor/Qt/devices/SoQtSpaceball.h
  \brief The SoQtSpaceball class is the spaceball input device abstraction.
  \ingroup devices

  The SoQtSpaceball class is the glue between native spaceball
  handling and how those events translates to generic events for the
  Inventor API scenegraph.
*/

// *************************************************************************

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <Inventor/Qt/devices/SoQtSpaceball.h>
#include <Inventor/Qt/devices/SoQtSpaceballP.h>

#define PRIVATE(p) (p->pimpl)
#define PUBLIC(p) (p->pub)

// *************************************************************************

SOQT_OBJECT_SOURCE(SoQtSpaceball);

// *************************************************************************

/*!
  \enum SoQtSpaceball::DeviceType

  Enumeration of spaceball input device types.
*/
/*!
  \enum SoQtSpaceball::Mask
  Enumeration of spaceball input device event types.
*/

/*!
  \fn SoQtSpaceball::SoQtSpaceball(int mask)

  Public constructor. The \a mask argument specifies which events we
  are interested in.
*/

/*!
  \fn SoQtSpaceball::~SoQtSpaceball()
  Destructor.
*/

// *************************************************************************

/*!
  This method sets the scale factor for the spaceball rotation vectors.
*/
void
SoQtSpaceball::setRotationScaleFactor(float f)
{
  PRIVATE(this)->rotationscale = f;
}

/*!
  This method returns the scale factor for the spaceball rotation vectors.
*/
float
SoQtSpaceball::getRotationScaleFactor(void) const
{
  return PRIVATE(this)->rotationscale;
}

/*!
  This method sets the scale factor for the spaceball translation vectors.
*/
void
SoQtSpaceball::setTranslationScaleFactor(float f)
{
  PRIVATE(this)->translationscale = f;
}

/*!
  This method returns the scale factor for the spaceball translation vectors.
*/
float
SoQtSpaceball::getTranslationScaleFactor(void) const
{
  return PRIVATE(this)->translationscale;
}

// *************************************************************************

/*!
  \fn SbBool SoQtSpaceball::exists(void)

  Returns \c TRUE iff there could be a device of this type available
  on the system.

  Note that a return value of \c TRUE does \e not signify that there
  is such a device active.
*/

// *************************************************************************

/*!
  \fn void SoQtSpaceball::setFocusToWindow(SbBool flag)

  Set to \c TRUE if you want spaceball events to be received even when
  the component does not have focus.
*/

/*!
  \fn SbBool SoQtSpaceball::isFocusToWindow(void) const

  Returns whether or not spaceball events are caught even when the
  component does not have focus.
*/

// *************************************************************************

#ifndef DOXYGEN_SKIP_THIS

SoGuiSpaceballP::SoGuiSpaceballP(SoQtSpaceball * p)
{
  this->pub = p;
}

SoGuiSpaceballP::~SoGuiSpaceballP()
{
}

#endif // !DOXYGEN_SKIP_THIS

// *************************************************************************

#undef PRIVATE
#undef PUBLIC

