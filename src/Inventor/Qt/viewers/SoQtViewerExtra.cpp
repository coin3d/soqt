/**************************************************************************\
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
\**************************************************************************/

static const char rcsid[] =
  "$Id$";

#include <assert.h>

#include <qkeycode.h>
#if QT_VERSION >= 200
#include <q1xcompatibility.h>
#endif // Qt v2.x

#include <soqtdefs.h>
#include <Inventor/Qt/viewers/SoQtViewer.h>

// *************************************************************************

/*!
  This method should be called from subclasses to handle events
  with common interpretation for all viewer classes.
*/

SbBool
SoQtViewer::processCommonEvents(
  QEvent * event )
{
  if ( inherited::invokeAppCB( event ) )
    return TRUE;

  SbBool keypress = (event->type() == Event_KeyPress);

#if QT_VERSION >= 200
  // Qt 2 introduced "accelerator" type keyboard events. They should
  // be handled by SoQtGLWidget (that is: ignored), so we should
  // never see any accelerator events here.
  assert(event->type() != QEvent::Accel &&
         event->type() != QEvent::AccelAvailable);
#endif // Qt v2.0

  // ESC => toggle viewer between interact and examine mode
  if ( keypress && ((QKeyEvent *) event)->key() == Key_Escape ) {
    this->setViewing( this->isViewing() ? FALSE : TRUE );
    return TRUE;
  }

  // If we're in interact mode, don't catch anything else than ESC
  // presses, everything else should be passed on to the scene graph.
  if ( ! this->isViewing() ) {
    inherited::processEvent( event );
    return TRUE;
  }

  if ( keypress ) {
    QKeyEvent * keyevent = (QKeyEvent *) event;
    SbVec2f pos(0.0f, 0.0f);

    switch ( keyevent->key() ) {
    case Key_Home:
      this->resetToHomePosition();
      return TRUE;

    case Key_S:
      this->setSeekMode( this->isSeekMode() ? FALSE : TRUE );
      return TRUE;

    case Key_Left:
      pos.setValue( -0.1f, 0.0f );
      break;

    case Key_Down:
      pos.setValue( 0.0f, -0.1f );
      break;

    case Key_Right:
      pos.setValue( 0.1f, 0.0f );
      break;

    case Key_Up:
      pos.setValue( 0.0f, 0.1f );
      break;

    default:
      return FALSE;
    }

    // Arrow keys falls through to this code.
    assert( pos != SbVec2f( 0.0f, 0.0f ) );
    this->moveCameraScreen( pos );
    return TRUE;
  }

  return FALSE;
} // processCommonEvents()

// *************************************************************************
