/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

#ifndef SOQT_KEYBOARD_H
#define SOQT_KEYBOARD_H

#include <Inventor/Qt/devices/SoQtDevice.h>

class SoKeyboardEvent;

// *************************************************************************

#define SO_QT_ALL_KEYBOARD_EVENTS SoQtKeyboard::ALL

class SOQT_DLL_API SoQtKeyboard : public SoQtDevice {
  SOQT_OBJECT_HEADER(SoQtKeyboard, SoQtDevice);

public:
  enum Events {
    KEY_PRESS = 0x01,
    KEY_RELEASE = 0x02,
    ALL_EVENTS = KEY_PRESS | KEY_RELEASE
  };

  SoQtKeyboard(int eventmask = ALL_EVENTS);
  virtual ~SoQtKeyboard(void);

  virtual void enable(QWidget * widget, SoQtEventHandler * handler, void * closure);
  virtual void disable(QWidget * widget, SoQtEventHandler * handler, void * closure);

  virtual const SoEvent * translateEvent(QEvent * event);

private:
  class SoQtKeyboardP * pimpl;
  friend class SoQtKeyboardP;
  friend class SoGuiKeyboardP;
};

// *************************************************************************

#endif // ! SOQT_KEYBOARD_H
