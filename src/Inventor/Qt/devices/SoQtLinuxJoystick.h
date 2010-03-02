/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) by Kongsberg Oil & Gas Technologies.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg Oil & Gas Technologies
 *  about acquiring a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg Oil & Gas Technologies, Bygdoy Alle 5, 0257 Oslo, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

#ifndef SOQT_LINUXJOYSTICK_H
#define SOQT_LINUXJOYSTICK_H

#include <Inventor/SbBasic.h>
#include <Inventor/events/SoButtonEvent.h>

#include <Inventor/Qt/devices/SoQtDevice.h>

class QSocketNotifier;
class SbPList;
class SoMotion3Event;
class SoSpaceballButtonEvent;

// *************************************************************************

#define SO_QT_ALL_LINUX_JOYSTICK_EVENTS SoQtLinuxJoystick::ALL_EVENTS

class SOQT_DLL_API SoQtLinuxJoystick : public SoQtDevice {
  SOQT_OBJECT_HEADER(SoQtLinuxJoystick, SoQtDevice);

public:
  enum Events {
    ALL_EVENTS = 0
  };

  SoQtLinuxJoystick(int events = ALL_EVENTS);
  virtual ~SoQtLinuxJoystick(void);

  virtual void enable(QWidget * widget, SoQtEventHandler * handler,
      void * closure);
  virtual void disable(QWidget * widget, SoQtEventHandler * handler,
      void * closure);

  virtual const SoEvent * translateEvent(QEvent * event);

  void setRotationScaleFactor(const float factor);
  float getRotationScaleFactor(void) const;
  void setTranslationScaleFactor(const float factor);
  float getTranslationScaleFactor(void) const;

  static SbBool exists(void);

  void setFocusToWindow(SbBool enable);
  SbBool isFocusToWindow(void) const;

  int getNumButtons(void) const;
  SbBool getButtonValue(const int button) const;

  int getNumAxes(void) const;
  float getAxisValue(const int axis) const;

private:
  class SoQtLinuxJoystickP * pimpl;
  friend class SoQtLinuxJoystickP;
};

// *************************************************************************

#endif // ! SOQT_LINUXJOYSTICK_H
