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

#if SOQT_DEBUG
static const char rcsid[] =
  "$Id$";
#endif // SOQT_DEBUG

#include <qmetaobject.h>
#include <moc_SoQtWalkViewer.cpp>

#include <soqtdefs.h>
#include <Inventor/Qt/viewers/SoQtWalkViewer.h>

/*!
  \class SoQtWalkViewer Inventor/Qt/viewers/SoQtWalkViewers.h
  \brief The SoQtWalkViewer class is yet to be documented...
  \ingroup soqtviewers
*/

// ************************************************************************

SOQT_OBJECT_SOURCE(SoQtWalkViewer);

// ************************************************************************

/*!
  The public constructor.
*/

SoQtWalkViewer::SoQtWalkViewer(
  QWidget * parent,
  const char * name,
  SbBool embed,
  SoQtFullViewer::BuildFlag flag,
  SoQtViewer::Type type)
: inherited(parent, name, embed, flag, type, TRUE)
{
//  this->constructor(TRUE);
} // SoQtWalkViewer()

// ************************************************************************

/*!
  A protected constructor.
*/

SoQtWalkViewer::SoQtWalkViewer(// protected
  QWidget * parent,
  const char * name,
  SbBool embed,
  SoQtFullViewer::BuildFlag flag,
  SoQtViewer::Type type,
  SbBool build)
: inherited(parent, name, embed, flag, type, FALSE)
{
//  this->constructor(build);
} // SoQtWalkViewer()

// ************************************************************************

/*!
  The destructor.
*/

SoQtWalkViewer::~SoQtWalkViewer(
  void)
{
} // ~SoQtWalkViewer()

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::setViewing(// virtual
  SbBool enable)
{
} // setViewing()

// ************************************************************************

// Documented in superclass.
void
SoQtWalkViewer::setCamera(SoCamera * camera)
{
}

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::setCursorEnabled(// virtual
  SbBool enable)
{
} // setCursorEnabled()

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::setCameraType(// virtual
  SoType type)
{
} // setCameraType()

// ************************************************************************

/*!
*/

const char *
SoQtWalkViewer::getDefaultWidgetName(// virtual
  void) const
{
  static const char defaultWidgetName[] = "";
  return defaultWidgetName;
} // getDefaultWidgetName()

// ************************************************************************

/*!
*/

const char *
SoQtWalkViewer::getDefaultTitle(// virtual
  void) const
{
  static const char defaultTitle[] = "Walk Viewer";
  return defaultTitle;
} // getDefaultTitle()

// ************************************************************************

/*!
*/

const char *
SoQtWalkViewer::getDefaultIconTitle(// virtual
  void) const
{
  static const char defaultIconTitle[] = "";
  return defaultIconTitle;
} // getDefaultIconTitle()

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::processEvent(// virtual
  QEvent * event)
{
} // processEvent()

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::setSeekMode(// virtual
  SbBool enable)
{
} // setSeekMode()

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::actualRedraw(// virtual
  void)
{
} // actualRedraw()

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::rightWheelMotion(// virtual
  float value)
{
} // rightWheelMotion()

// ************************************************************************

/*!
*/

QWidget *
SoQtWalkViewer::buildLeftTrim(// virtual
  QWidget * parent)
{
  return NULL;
} // buildLeftTrim()

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::createPrefSheet(// virtual
  void)
{
} // createPrefSheet()

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::openViewerHelpCard(// virtual
  void)
{
} // openViewerHelpCard()

// ************************************************************************
