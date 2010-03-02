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

#ifndef SOQT_6DOFEVENTS_H
#define SOQT_6DOFEVENTS_H

// *************************************************************************

#include <qevent.h>

// *************************************************************************

// temporary hacks for the spaceball/linux joystick support

enum SoQtCustomEvents {
  soqt6dofDeviceButtonPressedEvent   = (QEvent::User + 1),
  soqt6dofDeviceButtonReleasedEvent,
  soqt6dofDevicePressureEvent
};

class SoQt6dofDevicePressureEvent : public QEvent {
  typedef QEvent inherited;

public:
  SoQt6dofDevicePressureEvent(void);

  void setTranslation(float x, float y, float z);
  void getTranslation(float & x, float & y, float & z) const;

  void setRotation(float x, float y, float z);
  void getRotation(float & x, float & y, float & z) const;

private:
  float trans_x, trans_y, trans_z;
  float rot_x, rot_y, rot_z;

};

class SoQt6dofDeviceButtonEvent : public QEvent {
  typedef QEvent inherited;

public:
  SoQt6dofDeviceButtonEvent(void);

  void setButton(unsigned int button);
  unsigned int getButton(void) const;

  void setState(unsigned int state);
  unsigned int getState(void) const;

  void setNumButtons(unsigned int buttons);
  unsigned int getNumButtons(void) const;

  int isButtonPress(void) const;

private:
  unsigned int state;
  unsigned int button;
  unsigned int buttons;
};

#endif // !SOQT_6DOFEVENTS_H
