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
  \class SoQtFlyViewer Inventor/Qt/viewers/SoQtFlyViewer.h
  \brief The SoQtFlyViewer class is yet to be documented.
  \ingroup soqtviewers
*/

#include <soqtdefs.h>
#include <Inventor/Qt/viewers/SoQtFlyViewer.h>

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
