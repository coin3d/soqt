/**************************************************************************
 *
 *  Copyright (C) 2000 by Systems in Motion.  All rights reserved.
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
 **************************************************************************/

static const char rcsid[] =
  "$Id$";

/*!
  \class SoQtWalkViewer Inventor/Qt/viewers/SoQtWalkViewers.h
  \brief The SoQtWalkViewer class is yet to be documented...
  \ingroup soqtviewers
*/

#include <Inventor/Qt/viewers/SoQtWalkViewer.h>

// ************************************************************************

/*!
  The public constructor.
*/

SoQtWalkViewer::SoQtWalkViewer(
  QWidget * parent,
  const char * name,
  SbBool buildInsideParent,
  SoQtFullViewer::BuildFlag flag,
  SoQtViewer::Type type )
: inherited( parent, name, buildInsideParent, flag, type, TRUE )
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
  SbBool buildInsideParent,
  SoQtFullViewer::BuildFlag flag,
  SoQtViewer::Type type,
  SbBool buildNow )
: inherited( parent, name, buildInsideParent, flag, type, FALSE )
{
//  this->constructor( buildNow );
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
