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

#include <Inventor/Qt/viewers/SoQtPlaneViewer.h>

// ************************************************************************

SoQtPlaneViewer::SoQtPlaneViewer(
  QWidget * parent = NULL,
  const char * const name = NULL, 
  SbBool buildInsideParent = TRUE,
  SoQtFullViewer::BuildFlag flag = BUILD_ALL, 
  SoQtViewer::Type type = BROWSER )
{
}

SoQtPlaneViewer::~SoQtPlaneViewer(
  void )
{
}

void
SoQtPlaneViewer::setViewing( // virtual
  SbBool enable )
{
}

void
SoQtPlaneViewer::setCamera( // virtual
  SoCamera * camera )
{
}

void
SoQtPlaneViewer::setCursorEnabled( // virtual
  SbBool enable )
{
}

SoQtPlaneViewer::SoQtPlaneViewer(
  QWidget * parent,
  const char * const name, 
  SbBool buildInsideParent, 
  SoQtFullViewer::BuildFlag flag, 
  SoQtViewer::Type type, 
  SbBool buildNow )
{
}

QWidget *
SoQtPlaneViewer::buildWidget(
  QWidget * parent )
{
}

const char *
SoQtPlaneViewer::getDefaultWidgetName( // virtual
  void ) const
{
}

const char *
SoQtPlaneViewer::getDefaultTitle( // virtual
  void ) const
{
}

const char *
SoQtPlaneViewer::getDefaultIconTitle( // virtual
  void ) const
{
}

void
SoQtPlaneViewer::processEvent( // virtual
  QEvent * event )
{
}

void
SoQtPlaneViewer::setSeekMode( // virtual
  SbBool enable )
{
}

void
SoQtPlaneViewer::actualRedraw( // virtual
  void )
{
}

void
SoQtPlaneViewer::bottomWheelMotion( // virtual
  float value )
{
}

void
SoQtPlaneViewer::leftWheelMotion( // virtual
  float value )
{
}

void
SoQtPlaneViewer::rightWheelMotion( // virtual
  float value )
{
}

void
SoQtPlaneViewer::createPrefSheet( // virtual
  void )
{
}

void
SoQtPlaneViewer::createViewerButtons( // virtual
  QWidget * parent )
{
}

void
SoQtPlaneViewer::openViewerHelpCard( // virtual
  void )
{
}

void
SoQtPlaneViewer::computeSeekFinalOrientation( // virtual
  void )
{
}

