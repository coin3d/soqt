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

#if SOQT_DEBUG
static const char rcsid[] =
  "$Id$";
#endif // SOQT_DEBUG

/*!
  \class SoQtSpaceball SoQtSpaceball.h Inventor/Qt/devices/SoQtSpaceball.h
  \brief The SoQtSpaceball class ...
  \ingroup qtdevices

  FIXME: write class doc
*/

/*!
  TODO:
*/

#include <soqtdefs.h>
#include <Inventor/Qt/SoQtBasic.h>
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

