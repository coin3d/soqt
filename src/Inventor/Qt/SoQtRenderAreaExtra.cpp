/**************************************************************************\
 *
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
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
\**************************************************************************/

static const char rcsid[] =
  "$Id$";

#include <assert.h>

#include <qwidget.h>
#include <qevent.h>
#include <q1xcompatibility.h>

#include <Inventor/SoSceneManager.h>
#include <Inventor/sensors/SoNodeSensor.h>
#if SOQT_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // SOQT_DEBUG

#include <Inventor/Qt/devices/SoQtMouse.h>
#include <Inventor/Qt/devices/SoQtKeyboard.h>
#include <Inventor/Qt/widgets/QtGLArea.h>

#include <Inventor/Qt/SoQtRenderArea.h>

// *************************************************************************

/*!
  FIXME: write function documentation
*/

void
SoQtRenderArea::processEvent(
  QEvent * event )
{
  // any event on this level will have to be interaction with the scene...
  const SoEvent * sceneEvent = NULL;

  QtGLArea * widget = this->getQtGLArea();
  SoQtDevice::setLastEventPosition( widget->mapFromGlobal( QCursor::pos() ) );

  if ( this->devices.extra != NULL ) {
    for ( int i = 0; i < this->devices.extra->getLength() && ! sceneEvent; i++ )
      sceneEvent = 
        ((SoQtDevice *)(*(this->devices.extra))[i])->translateEvent( event );
  }

  if ( ! sceneEvent && this->devices.mouse != NULL )
    sceneEvent = this->devices.mouse->translateEvent( event );

  if ( ! sceneEvent && this->devices.keyboard )
    sceneEvent = this->devices.keyboard->translateEvent( event );

  if ( sceneEvent != NULL ) {
    assert( this->overlayManager != NULL );
    assert( this->normalManager != NULL );
    if ( ! this->overlayManager->processEvent( sceneEvent ) )
      this->normalManager->processEvent( sceneEvent );
  }
} // processEvent()

// *************************************************************************
