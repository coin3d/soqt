/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
