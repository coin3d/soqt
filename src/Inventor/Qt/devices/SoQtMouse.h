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

#ifndef SOQT_MOUSE_H
#define SOQT_MOUSE_H

#include <Inventor/Qt/devices/SoQtDevice.h>

class SoMouseButtonEvent;
class SoLocation2Event;

class SOQT_DLL_EXPORT  SoQtMouse : public SoQtDevice {
  typedef SoQtDevice inherited;
  Q_OBJECT

public:
  // FIXME: remove "SoQtMouse" in name, as its redundant. 19990620 mortene.
  enum SoQtMouseEventMask {
    ButtonPressMask = 0x01,
    ButtonReleaseMask = 0x02,
    PointerMotionMask = 0x04,
    ButtonMotionMask = 0x08,

    SO_QT_ALL_MOUSE_EVENTS = 0x0f
  };

  SoQtMouse(SoQtMouseEventMask mask = SO_QT_ALL_MOUSE_EVENTS);
  virtual ~SoQtMouse(void);

  virtual void enable( QWidget * widget, SoQtEventHandler * handler,
    void * closure );
  virtual void disable( QWidget * widget, SoQtEventHandler * handler,
    void * closure );

  virtual const SoEvent * translateEvent( QEvent * event );

private:
  SoMouseButtonEvent * buttonevent;
  SoLocation2Event * locationevent;
  SoQtMouseEventMask eventmask;

}; // class SoQtMouse

#endif // ! SOQT_MOUSE_H
