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

// $Id$

#ifndef SOQT_KEYBOARD_H
#define SOQT_KEYBOARD_H

#include <Inventor/Qt/devices/SoQtDevice.h>

class SbDict;
class SoKeyboardEvent;

// *************************************************************************

#define SO_QT_ALL_KEYBOARD_EVENTS SoQtKeyboard::ALL

class SOQT_DLL_API SoQtKeyboard : public SoQtDevice {
  SOQT_OBJECT_HEADER(SoQtKeyboard, SoQtDevice);
  Q_OBJECT

public:
  enum Events {
    KEY_PRESS    = 0x01,
    KEY_RELEASE  = 0x02,
    ALL_EVENTS   = 0x03
  };

  SoQtKeyboard(int eventmask = ALL_EVENTS);
  virtual ~SoQtKeyboard(void);

  virtual void enable(QWidget * widget, SoQtEventHandler * handler,
    void * closure);
  virtual void disable(QWidget * widget, SoQtEventHandler * handler,
    void * closure);

  virtual const SoEvent * translateEvent(QEvent * event);

private:
  int eventmask;
  SoKeyboardEvent * kbdevent;
}; // class SoQtKeyboard

// *************************************************************************

#endif // ! SOQT_KEYBOARD_H
