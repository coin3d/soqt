/**************************************************************************\
 *
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
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

/*!
  \class SoQtDevice SoQtDevice.h Inventor/Qt/devices/SoQtDevice.h
  \brief The SoQtDevice class ...
  \ingroup qtdevices

  FIXME: write class doc
*/

#include <Inventor/events/SoEvent.h>

#include <Inventor/Qt/devices/SoQtDevice.h>


/*!
  \typedef void (* SoQtDevice::SoQtEventHandler)(QWidget *, void *, QEvent *, bool *)
  FIXME: write doc
*/

/*!
  \fn void SoQtDevice::enable(QWidget * w, SoQtEventHandler f, void * data)
  FIXME: write doc
*/
/*!
  \fn void SoQtDevice::disable(QWidget * w, SoQtEventHandler f, void * data)
  FIXME: write doc
*/
/*!
  \fn const SoEvent * SoQtDevice::translateEvent(QEvent * event)
  FIXME: write doc
*/


QPoint * SoQtDevice::lasteventposition = NULL;

/*!
  FIXME: write function documentation
*/
void
SoQtDevice::setWindowSize(
  const SbVec2s size )
{
  this->widgetsize = size;
}


/*!
  FIXME: write function documentation
*/

SbVec2s
SoQtDevice::getWindowSize(void) const
{
  return this->widgetsize;
}

/*!
  FIXME: write function documentation
*/

void
SoQtDevice::setEventPosition( SoEvent * event, int x, int y ) const
{
  event->setPosition(SbVec2s(x, this->widgetsize[1] - y - 1));
}

/*!
  FIXME: write function documentation
*/

QPoint
SoQtDevice::getLastEventPosition(
  void ) // static
{
  return *SoQtDevice::lasteventposition;
}


void
SoQtDevice::setLastEventPosition( QPoint p ) // static
{
  if (!SoQtDevice::lasteventposition) {
    // FIXME: deallocate on exit. 20000311 mortene.
    SoQtDevice::lasteventposition = new QPoint;
  }
  *SoQtDevice::lasteventposition = p;
}

// *************************************************************************

static const char * getSoQtDeviceRCSId(void) { return rcsid; }

