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

#include <Inventor/Qt/viewers/SoQtFlyViewer.h>

// ************************************************************************

SoQtFlyViewer::SoQtFlyViewer(
  QWidget * parent,
  const char * name, 
  SbBool buildInsideParent, 
  SoQtFullViewer::BuildFlag flag,
  SoQtViewer::Type type )
{
}

SoQtFlyViewer::~SoQtFlyViewer(
  void )
{
}

void
SoQtFlyViewer::setViewing( // virtual
  SbBool enable )
{
}

void
SoQtFlyViewer::resetToHomePosition( // virtual
  void )
{
}

void
SoQtFlyViewer::setCamera( // virtual
  SoCamera * camera )
{
}

void
SoQtFlyViewer::setCursorEnabled( // virtual
  SbBool enable )
{
}

void
SoQtFlyViewer::setCameraType( // virtual
  SoType type )
{
}

SoQtFlyViewer::SoQtFlyViewer(
  QWidget * parent,
  const char * const name,
  SbBool buildInsideParent, 
  SoQtFullViewer::BuildFlag flag, 
  SoQtViewer::Type type, 
  SbBool buildNow )
{
}

const char *
SoQtFlyViewer::getDefaultWidgetName( // virtual
  void ) const
{
}

const char *
SoQtFlyViewer::getDefaultTitle( // virtual
  void ) const
{
}

const char *
SoQtFlyViewer::getDefaultIconTitle( // virtual
  void ) const
{
}

void
SoQtFlyViewer::processEvent( // virtual
  QEvent * event )
{
}

void
SoQtFlyViewer::setSeekMode( // virtual
  SbBool enable )
{
}

void
SoQtFlyViewer::actualRedraw( // virtual
  void )
{
}

void
SoQtFlyViewer::rightWheelMotion( // virtual
  float value )
{
}

void
SoQtFlyViewer::createPrefSheet( // virtual
  void )
{
}

void
SoQtFlyViewer::openViewerHelpCard( // virtual
  void )
{
}
