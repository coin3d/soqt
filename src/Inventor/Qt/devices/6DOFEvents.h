/**************************************************************************\
 *
 *  This file is part of the Coin GUI toolkit libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation.  See the
 *  file LICENSE.LGPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you want to use this library with software that is incompatible
 *  licensewise with the LGPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
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

class SoQt6dofDevicePressureEvent : public QCustomEvent {
  typedef QCustomEvent inherited;

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

class SoQt6dofDeviceButtonEvent : public QCustomEvent {
  typedef QCustomEvent inherited;

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
