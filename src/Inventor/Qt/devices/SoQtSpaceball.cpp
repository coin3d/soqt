/**************************************************************************
 *
 *  This file is part of the Coin SoQt GUI binding library.
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License version
 *  2.1 as published by the Free Software Foundation.  See the file
 *  LICENSE.LGPL at the root directory of the distribution for all the
 *  details.
 *
 *  If you want to use Coin SoQt for applications not compatible with the
 *  LGPL, please contact SIM to acquire a Professional Edition License.
 *
 *  Systems in Motion, Prof Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
 **************************************************************************/

#if SOQT_DEBUG
static const char rcsid[] =
  "$Id$";
#endif // SOQT_DEBUG

#include <soqtdefs.h>
#include <Inventor/Qt/SoQtBasic.h>
#include <Inventor/Qt/devices/SoQtSpaceball.h>

/*!
  \class SoQtSpaceball SoQtSpaceball.h Inventor/Qt/devices/SoQtSpaceball.h
  \brief The SoQtSpaceball class ...
  \ingroup qtdevices

  FIXME: write class doc
*/

// *************************************************************************

SOQT_TYPED_OBJECT_SOURCE(SoQtSpaceball, SoQtDevice);

// *************************************************************************

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

// *************************************************************************

/*!
  Constructor.
*/

SoQtSpaceball::SoQtSpaceball(
  SoQtSpaceball::Mask mask )
{
  this->mask = mask;
  this->rotationscale = .006f;
  this->translationscale = .006f;
  this->focustowindow = FALSE;
} // SoQtSpaceball()

/*!
  Destructor.
*/

SoQtSpaceball::~SoQtSpaceball(
  void )
{
} // ~SoQtSpaceball()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

void
SoQtSpaceball::enable(
  QWidget *, // widget,
  SoQtEventHandler *, // handler,
  void * ) // closure )
{
  SOQT_STUB();
} // enable()

/*!
  FIXME: write function documentation
*/

void
SoQtSpaceball::disable(
  QWidget *, // widget,
  SoQtEventHandler *, // handler,
  void * ) // closure )
{
  SOQT_STUB();
} // disable()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

const SoEvent *
SoQtSpaceball::translateEvent(QEvent * /*event*/)
{
  SOQT_STUB();
  return (SoEvent *) NULL;
} // translateEvent()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

void
SoQtSpaceball::setRotationScaleFactor(
  float f )
{
  this->rotationscale = f;
} // setRotationScaleFactor()

/*!
  FIXME: write function documentation
*/

float
SoQtSpaceball::getRotationScaleFactor(
  void ) const
{
  return this->rotationscale;
} // getRotationScaleFactor()

/*!
  FIXME: write function documentation
*/

void
SoQtSpaceball::setTranslationScaleFactor(
  float f )
{
  this->translationscale = f;
} // setTranslationScaleFactor()

/*!
  FIXME: write function documentation
*/

float
SoQtSpaceball::getTranslationScaleFactor(
  void ) const
{
  return this->translationscale;
} // getTranslationScaleFactor()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

SbBool
SoQtSpaceball::exists(
  void )
{
//  SOQT_STUB();
  return FALSE;
} // exists()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

void
SoQtSpaceball::setFocusToWindow(
  SbBool flag )
{
  this->focustowindow = flag;
}

/*!
  FIXME: write function documentation
*/

SbBool
SoQtSpaceball::isFocusToWindow(
  void ) const
{
  return this->focustowindow;
} // isFocusToWindow()

// *************************************************************************

#if SOQT_DEBUG
static const char * getSoQtSpaceballRCSId(void) { return rcsid; }
#endif // SOQT_DEBUG

