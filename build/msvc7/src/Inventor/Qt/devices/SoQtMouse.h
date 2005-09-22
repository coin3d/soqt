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

#ifndef SOQT_MOUSE_H
#define SOQT_MOUSE_H

#include <Inventor/Qt/devices/SoQtDevice.h>

class SoMouseButtonEvent;
class SoLocation2Event;

// *************************************************************************

class SOQT_DLL_API SoQtMouse : public SoQtDevice {
  SOQT_OBJECT_HEADER(SoQtMouse, SoQtDevice);

public:
  enum Events {
    BUTTON_PRESS    = 0x01,
    BUTTON_RELEASE  = 0x02,
    POINTER_MOTION  = 0x04,
    BUTTON_MOTION   = 0x08,

    ALL_EVENTS = BUTTON_PRESS | BUTTON_RELEASE | POINTER_MOTION | BUTTON_MOTION
  };

  SoQtMouse(int eventmask = ALL_EVENTS);
  virtual ~SoQtMouse(void);

  virtual void enable(QWidget * widget, SoQtEventHandler * handler, void * closure);
  virtual void disable(QWidget * widget, SoQtEventHandler * handler, void * closure);

  virtual const SoEvent * translateEvent(QEvent * event);

private:
  class SoQtMouseP * pimpl;
  friend class SoQtMouseP;
  friend class SoGuiMouseP;
};

// *************************************************************************

#endif // ! SOQT_MOUSE_H
