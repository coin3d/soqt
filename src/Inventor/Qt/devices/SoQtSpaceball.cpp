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
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoQtBasic.h>
#include <Inventor/Qt/devices/SoQtSpaceball.h>
#include <Inventor/events/SoMotion3Event.h>
#include <Inventor/events/SoSpaceballButtonEvent.h>
#include <qwidget.h>

#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H


#ifndef X_DISPLAY_MISSING
#include <Inventor/Qt/devices/spwinput.h>
#endif // ! X_DISPLAY_MISSING

/*!
  \class SoQtSpaceball SoQtSpaceball.h Inventor/Qt/devices/SoQtSpaceball.h
  \brief The SoQtSpaceball class ...
  \ingroup devices

  FIXME: write class doc
*/

// *************************************************************************

SOQT_OBJECT_SOURCE(SoQtSpaceball);

// *************************************************************************

/*!
  \enum SoQtSpaceball::Events
  FIXME: write documentation for enum
*/
/*!
  \var SoQtSpaceball::Events SoQtSpaceball::MOTION
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtSpaceball::Events SoQtSpaceball::PRESS
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtSpaceball::Events SoQtSpaceball::RELEASE
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtSpaceball::Events SoQtSpaceball::ALL_EVENTS
  FIXME: write documentation for enum definition
*/

// *************************************************************************

/*!
  Constructor.
*/

SoQtSpaceball::SoQtSpaceball(
  int mask)
{
  this->eventmask = mask;
  this->rotationscale = .006f;
  this->translationscale = .006f;
  this->focustowindow = FALSE;
  this->motion3Event = new SoMotion3Event;
  this->buttonEvent = new SoSpaceballButtonEvent; 
} // SoQtSpaceball()

/*!
  Destructor.
*/

SoQtSpaceball::~SoQtSpaceball(
  void)
{
  delete this->motion3Event;
  delete this->buttonEvent;
} // ~SoQtSpaceball()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

void
SoQtSpaceball::enable(
  QWidget * widget,
  SoQtEventHandler *, // handler,
  void *) // closure)
{
#ifndef X_DISPLAY_MISSING
  if (SPW_CheckForSpaceballX11((void*) widget->x11Display(), 
                               widget->winId(), "sbtestx") == TRUE) {
  }
#endif // !X_DISPLAY_MISSING
} // enable()

/*!
  FIXME: write function documentation
*/

void
SoQtSpaceball::disable(
  QWidget *, // widget,
  SoQtEventHandler *, // handler,
  void *) // closure)
{
// FIXME: SOQT_STUB();
} // disable()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

const SoEvent *
SoQtSpaceball::translateEvent(QEvent * event)
{
#ifndef X_DISPLAY_MISSING
  if (event->type() == (QEvent::Type) SoQt::SPACEBALL_EVENT) {
    SPW_InputEvent * sbEvent = (SPW_InputEvent*) ((QCustomEvent*)event)->data();
    
    switch (sbEvent->type) {
    case SPW_InputMotionEvent:
      this->motion3Event->setTranslation(this->makeTranslation(sbEvent->sData[0],
                                                               sbEvent->sData[1],
                                                               sbEvent->sData[2]));
      this->motion3Event->setRotation(this->makeRotation(sbEvent->sData[3],
                                                         sbEvent->sData[4],
                                                         sbEvent->sData[5]));
      return this->motion3Event;
    case SPW_InputButtonPressEvent:
      return (SoEvent*) NULL;
    case SPW_InputButtonReleaseEvent:
      return (SoEvent*) NULL;
    default:
      return (SoEvent*) NULL;
    }
  }
#endif // ! X_DISPLAY_MISSING
  return (SoEvent *) NULL;
} // translateEvent()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

void
SoQtSpaceball::setRotationScaleFactor(
  float f)
{
  this->rotationscale = f;
} // setRotationScaleFactor()

/*!
  FIXME: write function documentation
*/

float
SoQtSpaceball::getRotationScaleFactor(
  void) const
{
  return this->rotationscale;
} // getRotationScaleFactor()

/*!
  FIXME: write function documentation
*/

void
SoQtSpaceball::setTranslationScaleFactor(
  float f)
{
  this->translationscale = f;
} // setTranslationScaleFactor()

/*!
  FIXME: write function documentation
*/

float
SoQtSpaceball::getTranslationScaleFactor(
  void) const
{
  return this->translationscale;
} // getTranslationScaleFactor()

// *************************************************************************

/*!
  Returns \c TRUE iff there could be a device of this type available
  on the system.

  Note that a return value of \c TRUE does \e not signify that there
  is such a device active.
*/

SbBool
SoQtSpaceball::exists(
  void)
{
#ifdef X_DISPLAY_MISSING
  return FALSE;
#else // ! X_DISPLAY_MISSING
  return TRUE;
#endif // X_DISPLAY_MISSING 
} // exists()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

void
SoQtSpaceball::setFocusToWindow(
  SbBool flag)
{
  this->focustowindow = flag;
}

/*!
  FIXME: write function documentation
*/

SbBool
SoQtSpaceball::isFocusToWindow(
  void) const
{
  return this->focustowindow;
} // isFocusToWindow()

SbRotation 
SoQtSpaceball::makeRotation(const float rx, const float ry, const float rz) const
{
  SbRotation xrot(SbVec3f(1, 0, 0), rx * this->rotationscale);
  SbRotation yrot(SbVec3f(0, 1, 0), ry * this->rotationscale);
  SbRotation zrot(SbVec3f(0, 0, 1), - rz * this->rotationscale);
  return xrot * yrot * zrot;
}

SbVec3f 
SoQtSpaceball::makeTranslation(const float tx, const float ty, const float tz) const
{
  return SbVec3f(tx*this->translationscale,
                 ty*this->translationscale,
                 - tz*this->translationscale);
}


// *************************************************************************

#if SOQT_DEBUG
static const char * getSoQtSpaceballRCSId(void) { return rcsid; }
#endif // SOQT_DEBUG

