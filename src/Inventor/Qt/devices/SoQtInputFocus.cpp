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
#include <Inventor/Qt/SoQtBasic.h>
#include <Inventor/Qt/devices/SoQtInputFocus.h>

/*!
  \class SoQtInputFocus SoQtInputFocus.h Inventor/Qt/devices/SoQtInputFocus.h
  \brief The SoQtInputFocus class ...
  \ingroup devices

  FIXME: write class doc
*/

SOQT_OBJECT_SOURCE(SoQtInputFocus);

// *************************************************************************

/*!
  \enum SoQtInputFocus::Events
  FIXME: write doc
*/

/*!
  \var SoQtInputFocus::Events SoQtInputFocus::ENTER_WINDOW
  FIXME: write doc
*/

/*!
  \var SoQtInputFocus::Events SoQtInputFocus::LEAVE_WINDOW
  FIXME: write doc
*/

/*!
  \var SoQtInputFocus::Events SoQtInputFocus::ALL_EVENTS
  FIXME: write doc
*/

// *************************************************************************

/*!
  Constructor.
*/

SoQtInputFocus::SoQtInputFocus(
  int mask )
{
  this->eventmask = mask;
} // SoQtInputFocus()

/*!
  Destructor.
*/

SoQtInputFocus::~SoQtInputFocus(
  void )
{
} // ~SoQtInputFocus()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

void
SoQtInputFocus::enable(
  QWidget *, // widget,
  SoQtEventHandler *, // handler,
  void * ) // closure )
{
  SOQT_STUB();
} // enable()

/*!
  FIXME: write function documentation
*/

void
SoQtInputFocus::disable(
  QWidget *, // widget,
  SoQtEventHandler *, // handler,
  void * ) // closure )
{
  SOQT_STUB();
} // disable()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

const SoEvent *
SoQtInputFocus::translateEvent(
  QEvent * ) // event )
{
  SOQT_STUB();
  return NULL;
} // translateEvent()

// *************************************************************************

#if SOQT_DEBUG
static const char * getSoQtInputFocusRCSId(void) { return rcsid; }
#endif // SOQT_DEBUG

