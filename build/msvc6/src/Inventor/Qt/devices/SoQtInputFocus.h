/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2004 by Systems in Motion.  All rights reserved.
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
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

#ifndef SOQT_INPUTFOCUS_H
#define SOQT_INPUTFOCUS_H

#include <Inventor/Qt/devices/SoQtDevice.h>

// *************************************************************************

class SOQT_DLL_API SoQtInputFocus : public SoQtDevice {
  SOQT_OBJECT_HEADER(SoQtInputFocus, SoQtDevice);

public:
  enum Events {
    ENTER_WINDOW = 1 << 0,
    LEAVE_WINDOW = 1 << 1,
    ALL_EVENTS   = ENTER_WINDOW | LEAVE_WINDOW
  };

  SoQtInputFocus(int mask = ALL_EVENTS);
  virtual ~SoQtInputFocus();

  virtual void enable(QWidget * widget, SoQtEventHandler * handler, void * closure);
  virtual void disable(QWidget * widget, SoQtEventHandler * handler, void * closure);

  virtual const SoEvent * translateEvent(QEvent * event);

private:
  class SoQtInputFocusP * pimpl;
  friend class SoGuiInputFocusP;
  friend class SoQtInputFocusP;
};

#define SO_QT_ALL_FOCUS_EVENTS SoQtInputFocus::ALL_EVENTS;

// *************************************************************************

#endif // ! SOQT_INPUTFOCUS_H
