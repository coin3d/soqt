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
#include <Inventor/Qt/viewers/SoQtFlyViewer.h>

/*!
  \class SoQtFlyViewer Inventor/Qt/viewers/SoQtFlyViewer.h
  \brief The SoQtFlyViewer class is yet to be documented.
  \ingroup soqtviewers
*/

// ************************************************************************

SOQT_TYPED_OBJECT_SOURCE(SoQtFlyViewer, SoQtConstrainedViewer);

// ************************************************************************

/*!
*/

SoQtFlyViewer::SoQtFlyViewer( // protected
  QWidget * parent,
  const char * name, 
  SbBool embed, 
  SoQtFullViewer::BuildFlag flag,
  SoQtViewer::Type type )
: inherited( parent, name, embed, flag, type, TRUE )
{
} // SoQtFlyViewer()

// ************************************************************************

/*!
*/

SoQtFlyViewer::SoQtFlyViewer( // protected
  QWidget * parent,
  const char * const name,
  SbBool embed, 
  SoQtFullViewer::BuildFlag flag, 
  SoQtViewer::Type type, 
  SbBool build )
: inherited( parent, name, embed, flag, type, FALSE )
{
} // SoQtFlyViewer()

// ************************************************************************

/*!
*/

SoQtFlyViewer::~SoQtFlyViewer(
  void )
{
} // ~SoQtFlyViewer()

// ************************************************************************

/*!
*/

void
SoQtFlyViewer::setViewing( // virtual
  SbBool enable )
{
} // setViewing()

// ************************************************************************

/*!
*/

void
SoQtFlyViewer::resetToHomePosition( // virtual
  void )
{
} // resetToHomePosition()

// ************************************************************************

/*!
*/

void
SoQtFlyViewer::setCamera( // virtual
  SoCamera * camera )
{
} // setCamera()

// ************************************************************************

/*!
*/

void
SoQtFlyViewer::setCursorEnabled( // virtual
  SbBool enable )
{
} // setCursorEnabled()

// ************************************************************************

/*!
*/

void
SoQtFlyViewer::setCameraType( // virtual
  SoType type )
{
} // setCameraType()

// ************************************************************************

/*!
*/

const char *
SoQtFlyViewer::getDefaultWidgetName( // virtual
  void ) const
{
  static const char defaultWidgetName[] = "";
  return defaultWidgetName;
} // getDefaultWidgetName()

// ************************************************************************

/*!
*/

const char *
SoQtFlyViewer::getDefaultTitle( // virtual
  void ) const
{
  static const char defaultTitle[] = "Fly Viewer";
  return defaultTitle;
} // getDefaultTitle()

// ************************************************************************

/*!
*/

const char *
SoQtFlyViewer::getDefaultIconTitle( // virtual
  void ) const
{
  static const char defaultIconTitle[] = "";
  return defaultIconTitle;
} // getDefaultIconTitle()

// ************************************************************************

/*!
*/

void
SoQtFlyViewer::processEvent( // virtual
  QEvent * event )
{
} // processEvent()

// ************************************************************************

/*!
*/

void
SoQtFlyViewer::setSeekMode( // virtual
  SbBool enable )
{
} // setSeekMode()

// ************************************************************************

/*!
*/

void
SoQtFlyViewer::actualRedraw( // virtual
  void )
{
} // actualRedraw()

// ************************************************************************

/*!
*/

void
SoQtFlyViewer::rightWheelMotion( // virtual
  float value )
{
} // rightWheelMotion()

// ************************************************************************

/*!
*/

void
SoQtFlyViewer::createPrefSheet( // virtual
  void )
{
} // createPrefSheet()

// ************************************************************************

/*!
*/

void
SoQtFlyViewer::openViewerHelpCard( // virtual
  void )
{
} // openViewerHelpCard()

// ************************************************************************
