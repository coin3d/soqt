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

#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <soqtdefs.h>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoQtBasic.h>
#include <Inventor/Qt/devices/SoQtSpaceball.h>
#include <Inventor/Qt/devices/SoQtSpaceballP.h>
#include <Inventor/Qt/SoQtInternal.h>
#include <Inventor/events/SoMotion3Event.h>
#include <Inventor/events/SoSpaceballButtonEvent.h>
#include <qwidget.h>

/* The setting of this define needs to be added manually to
   configure.in for all relevant projects. */
#ifdef HAVE_X11_AVAILABLE
#include <Inventor/Qt/devices/spwinput.h>
#endif // HAVE_X11_AVAILABLE

// *************************************************************************

#ifndef DOXYGEN_SKIP_THIS

SoQtSpaceballP::SoQtSpaceballP(SoQtSpaceball * p)
  : SoGuiSpaceballP(p)
{
  this->rotationscale = .006f;
  this->translationscale = .006f;
  this->focustowindow = FALSE;
  this->motion3event = new SoMotion3Event;
  this->buttonevent = new SoSpaceballButtonEvent;
}

SoQtSpaceballP::~SoQtSpaceballP()
{
  delete this->motion3event;
  delete this->buttonevent;
}

SbRotation
SoQtSpaceballP::makeRotation(const float rx, const float ry, const float rz) const
{
  SbRotation xrot(SbVec3f(1, 0, 0), rx * this->rotationscale);
  SbRotation yrot(SbVec3f(0, 1, 0), ry * this->rotationscale);
  SbRotation zrot(SbVec3f(0, 0, 1), - rz * this->rotationscale);
  return xrot * yrot * zrot;
}

SbVec3f
SoQtSpaceballP::makeTranslation(const float tx, const float ty, const float tz) const
{
  return SbVec3f(tx * this->translationscale,
                 ty * this->translationscale,
                 - tz * this->translationscale);
}

#endif // !DOXYGEN_SKIP_THIS

// *************************************************************************

SoQtSpaceball::SoQtSpaceball(int mask)
{
  PRIVATE(this) = new SoQtSpaceballP(this);
  PRIVATE(this)->eventmask = mask;
}

SoQtSpaceball::~SoQtSpaceball()
{
  delete PRIVATE(this);
}

// *************************************************************************

void
SoQtSpaceball::enable(QWidget * widget, SoQtEventHandler * handler, void * closure)
{
#ifdef HAVE_X11_AVAILABLE
  if (SPW_CheckForSpaceballX11((void*) widget->x11Display(),
                               widget->winId(), "sbtestx") == TRUE) {
  }
#endif // HAVE_X11_AVAILABLE
}

void
SoQtSpaceball::disable(QWidget * widget, SoQtEventHandler * handler, void * closure)
{
// FIXME: SOQT_STUB();
}

// *************************************************************************

const SoEvent *
SoQtSpaceball::translateEvent(QEvent * event)
{
#ifdef HAVE_X11_AVAILABLE
  if (event->type() == (QEvent::Type) SoQtInternal::SPACEBALL_EVENT) {
    SPW_InputEvent * sbEvent = (SPW_InputEvent*) ((QCustomEvent*)event)->data();

    switch (sbEvent->type) {
    case SPW_InputMotionEvent:
      PRIVATE(this)->motion3event->setTranslation(PRIVATE(this)->makeTranslation(sbEvent->sData[0],
                                                                                 sbEvent->sData[1],
                                                                                 sbEvent->sData[2]));
      PRIVATE(this)->motion3event->setRotation(PRIVATE(this)->makeRotation(sbEvent->sData[3],
                                                                           sbEvent->sData[4],
                                                                           sbEvent->sData[5]));
      return PRIVATE(this)->motion3event;
    case SPW_InputButtonPressEvent:
      return (SoEvent*) NULL;
    case SPW_InputButtonReleaseEvent:
      return (SoEvent*) NULL;
    default:
      return (SoEvent*) NULL;
    }
  }
#endif // HAVE_X11_AVAILABLE
  return (SoEvent *) NULL;
}

// *************************************************************************

SbBool
SoQtSpaceball::exists(void)
{
#ifdef HAVE_X11_AVAILABLE
  return TRUE;
#else // ! HAVE_X11_AVAILABLE
  return FALSE;
#endif // ! HAVE_X11_AVAILABLE
}

// *************************************************************************

void
SoQtSpaceball::setFocusToWindow(SbBool flag)
{
  PRIVATE(this)->focustowindow = flag;
}

SbBool
SoQtSpaceball::isFocusToWindow(void) const
{
  return PRIVATE(this)->focustowindow;
}

// *************************************************************************
