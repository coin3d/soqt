/**************************************************************************\
 *
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

/*!
  \class SoQtSpaceball SoQtSpaceball.h Inventor/Qt/devices/SoQtSpaceball.h
  \brief The SoQtSpaceball class ...
  \ingroup qtdevices

  FIXME: write class doc
*/


/*!
  TODO:
  - not implemented yet! no spaceball available
  - idea: maybe we could make device classes for other available cheap
  PC equipment? wheel mice, joysticks, ....
*/

#include <Inventor/Qt/devices/SoQtSpaceball.h>

/*!
  \enum SoQtSpaceball::Mask
  FIXME: write documentation for enum
*/
/*!
  \var SoQtSpaceball::Mask SoQtSpaceball::MOTION
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtSpaceball::Mask SoQtSpaceball::PRESS
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtSpaceball::Mask SoQtSpaceball::RELEASE
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtSpaceball::Mask SoQtSpaceball::ALL
  FIXME: write documentation for enum definition
*/


/*!
  Constructor.
*/
SoQtSpaceball::SoQtSpaceball(SoQtSpaceball::Mask mask)
{
  this->mask = mask;
  this->rotationscale = .006f;
  this->translationscale = .006f;
  this->focustowindow = FALSE;
}

/*!
  Destructor.
*/
SoQtSpaceball::~SoQtSpaceball()
{
}

/*!
  FIXME: write function documentation
*/
void
SoQtSpaceball::enable(QWidget * w, SoQtEventHandler f, void * data)
{
  // TODO: implement
}

/*!
  FIXME: write function documentation
*/
void
SoQtSpaceball::disable(QWidget * w, SoQtEventHandler f, void * data)
{
  // TODO: implement
}

/*!
  FIXME: write function documentation
*/
const SoEvent *
SoQtSpaceball::translateEvent(QEvent * event)
{
  // TODO: implement
  return NULL;
}

/*!
  FIXME: write function documentation
*/
void
SoQtSpaceball::setRotationScaleFactor(float f)
{
  this->rotationscale = f;
}

/*!
  FIXME: write function documentation
*/
float
SoQtSpaceball::getRotationScaleFactor(void) const
{
  return this->rotationscale;
}

/*!
  FIXME: write function documentation
*/
void
SoQtSpaceball::setTranslationScaleFactor(float f)
{
  this->translationscale = f;
}

/*!
  FIXME: write function documentation
*/
float
SoQtSpaceball::getTranslationScaleFactor(void) const
{
  return this->translationscale;
}

/*!
  FIXME: write function documentation
*/
SbBool
SoQtSpaceball::exists(void)
{
  // TODO: implement
  return FALSE;
}

/*!
  FIXME: write function documentation
*/
void
SoQtSpaceball::setFocusToWindow(SbBool flag)
{
  this->focustowindow = flag;
}

/*!
  FIXME: write function documentation
*/
SbBool
SoQtSpaceball::isFocusToWindow(void) const
{
  return this->focustowindow;
}
