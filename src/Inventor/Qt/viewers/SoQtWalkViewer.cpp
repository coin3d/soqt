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

#include <Inventor/Qt/viewers/SoQtWalkViewers.h>

// ************************************************************************

SoQtWalkViewer::SoQtWalkViewer(
  QWidget * parent,
  const char * name,
  SbBool buildInsideParent,
  SoQtFullViewer::BuildFlag flag,
  SoQtViewer::Type type )
{
}

SoQtWalkViewer::~SoQtWalkViewer(
  void )
{
}

void
SoQtWalkViewer::setViewing( // virtual
  SbBool enable )
{
}

void
SoQtWalkViewer::setCamera( // virtual
  SoCamera * camera )
{
}

void
SoQtWalkViewer::setCursorEnabled( // virtual
  SbBool enable )
{
}

void
SoQtWalkViewer::setCameraType( // virtual
  SoType type )
{
}

// ************************************************************************

SoQtWalkViewer::SoQtWalkViewer(
  QWidget * parent,
  const char * name,
  SbBool buildInsideParent,
  SoQtFullViewer::BuildFlag flag,
  SoQtViewer::Type type,
  SbBool buildNow )
{
}

const char *
SoQtWalkViewer::getDefaultWidgetName( // virtual
  void ) const
{
}

const char *
SoQtWalkViewer::getDefaultTitle( // virtual
  void ) const
{
}

const char *
SoQtWalkViewer::getDefaultIconTitle( // virtual
  void ) const
{
}

void
SoQtWalkViewer::processEvent( // virtual
  QEvent * event )
{
}

void
SoQtWalkViewer::setSeekMode( // virtual
  SbBool enable )
{
}

void
SoQtWalkViewer::actualRedraw( // virtual
  void )
{
}

void
SoQtWalkViewer::rightWheelMotion( // virtual
  float value )
{
}

QWidget *
SoQtWalkViewer::buildLeftTrim( // virtual
  QWidget * parent )
{
}

void
SoQtWalkViewer::createPrefSheet( // virtual
  void )
{
}

void
SoQtWalkViewer::openViewerHelpCard( // virtual
  void )
{
}
