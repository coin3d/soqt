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
#include <Inventor/Qt/viewers/SoQtWalkViewer.h>

/*!
  \class SoQtWalkViewer Inventor/Qt/viewers/SoQtWalkViewers.h
  \brief The SoQtWalkViewer class is yet to be documented...
  \ingroup soqtviewers
*/

// ************************************************************************

SOQT_TYPED_OBJECT_SOURCE(SoQtWalkViewer, SoQtConstrainedViewer);

// ************************************************************************

/*!
  The public constructor.
*/

SoQtWalkViewer::SoQtWalkViewer(
  QWidget * parent,
  const char * name,
  SbBool embed,
  SoQtFullViewer::BuildFlag flag,
  SoQtViewer::Type type )
: inherited( parent, name, embed, flag, type, TRUE )
{
//  this->constructor( TRUE );
} // SoQtWalkViewer()

// ************************************************************************

/*!
  A protected constructor.
*/

SoQtWalkViewer::SoQtWalkViewer( // protected
  QWidget * parent,
  const char * name,
  SbBool embed,
  SoQtFullViewer::BuildFlag flag,
  SoQtViewer::Type type,
  SbBool build )
: inherited( parent, name, embed, flag, type, FALSE )
{
//  this->constructor( build );
} // SoQtWalkViewer()

// ************************************************************************

/*!
  The destructor.
*/

SoQtWalkViewer::~SoQtWalkViewer(
  void )
{
} // ~SoQtWalkViewer()

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::setViewing( // virtual
  SbBool enable )
{
} // setViewing()

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::setCamera( // virtual
  SoCamera * camera )
{
} // setCamera()

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::setCursorEnabled( // virtual
  SbBool enable )
{
} // setCursorEnabled()

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::setCameraType( // virtual
  SoType type )
{
} // setCameraType()

// ************************************************************************

/*!
*/

const char *
SoQtWalkViewer::getDefaultWidgetName( // virtual
  void ) const
{
  static const char defaultWidgetName[] = "";
  return defaultWidgetName;
} // getDefaultWidgetName()

// ************************************************************************

/*!
*/

const char *
SoQtWalkViewer::getDefaultTitle( // virtual
  void ) const
{
  static const char defaultTitle[] = "Walk Viewer";
  return defaultTitle;
} // getDefaultTitle()

// ************************************************************************

/*!
*/

const char *
SoQtWalkViewer::getDefaultIconTitle( // virtual
  void ) const
{
  static const char defaultIconTitle[] = "";
  return defaultIconTitle;
} // getDefaultIconTitle()

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::processEvent( // virtual
  QEvent * event )
{
} // processEvent()

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::setSeekMode( // virtual
  SbBool enable )
{
} // setSeekMode()

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::actualRedraw( // virtual
  void )
{
} // actualRedraw()

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::rightWheelMotion( // virtual
  float value )
{
} // rightWheelMotion()

// ************************************************************************

/*!
*/

QWidget *
SoQtWalkViewer::buildLeftTrim( // virtual
  QWidget * parent )
{
  return NULL;
} // buildLeftTrim()

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::createPrefSheet( // virtual
  void )
{
} // createPrefSheet()

// ************************************************************************

/*!
*/

void
SoQtWalkViewer::openViewerHelpCard( // virtual
  void )
{
} // openViewerHelpCard()

// ************************************************************************
