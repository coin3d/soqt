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
 *  http://www.sim.no/ sales@sim.no Voice: +47 73540378 Fax: +47 73943861
 *
\**************************************************************************/

/*!
  \class SoQtDevice SoQtDevice.h Inventor/Qt/devices/SoQtDevice.h
  \brief The SoQtDevice class ...
  \ingroup qtdevices

  FIXME: write class doc
*/

#include <Inventor/Qt/devices/SoQtDevice.h>
#include <Inventor/events/SoEvent.h>

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


QPoint SoQtDevice::lasteventposition;

/*!
  FIXME: write function documentation
*/
void
SoQtDevice::setWindowSize(const SbVec2s & size)
{
  this->widgetsize = size;
}


/*!
  FIXME: write function documentation
*/
const SbVec2s &
SoQtDevice::getWindowSize(void) const
{
  return this->widgetsize;
}
  
/*!
  FIXME: write function documentation
*/
void
SoQtDevice::setEventPosition(SoEvent * event, int x, int y) const
{
  event->setPosition(SbVec2s(x, this->widgetsize[1] - y - 1));
}

/*!
  FIXME: write function documentation
*/
QPoint
SoQtDevice::getLastEventPosition(void)
{
  return SoQtDevice::lasteventposition;
}
