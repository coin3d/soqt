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

//  $Id$

#ifndef SOQT_DEVICE_H
#define SOQT_DEVICE_H

/*!
  \defgroup qtdevices Qt Device Classes
*/

#include <qpoint.h>

#include <Inventor/SbLinear.h>

#include <Inventor/Qt/SoQtBasic.h>

class QWidget;
class QEvent;
class SoEvent;

typedef int soqtEventMask;

// *************************************************************************

class SOQT_DLL_EXPORT SoQtDevice {
public:
  typedef void (*SoQtEventHandler)( QWidget *, void *, QEvent *, bool * );

  virtual void enable( QWidget * w, SoQtEventHandler f, void * data ) = 0;
  virtual void disable( QWidget * w, SoQtEventHandler f, void * data ) = 0;

  virtual const SoEvent * translateEvent(QEvent * event) = 0;
  void setWindowSize( const SbVec2s size );
  SbVec2s getWindowSize(void) const;

protected:
  void setEventPosition( SoEvent * event, int x, int y ) const;
  static QPoint getLastEventPosition(void);

private:
  static void setLastEventPosition(QPoint p);
  static QPoint * lasteventposition;
  SbVec2s widgetsize;

  // For setting SoQtDevice::lasteventposition in
  // SoQtRenderArea::processEvents() (as a workaround for a Qt design
  // problem vs Xt).
  friend class SoQtRenderArea;

}; // class SoQtDevice

// *************************************************************************

#endif // ! SOQT_DEVICE_H
