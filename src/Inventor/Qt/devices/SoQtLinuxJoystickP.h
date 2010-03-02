#ifndef SOQT_LINUXJOYSTICKP_H
#define SOQT_LINUXJOYSTICKP_H

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

#ifndef SOQT_INTERNAL
#error this is a private header file
#endif /* !SOQT_INTERNAL */

#include <Inventor/SbBasic.h>
#include <Inventor/events/SoButtonEvent.h>
#include <Inventor/Qt/devices/SoQtDevice.h>

class QSocketNotifier;
class SbPList;
class SoMotion3Event;
class SoSpaceballButtonEvent;

// *************************************************************************

class SoQtLinuxJoystickP : public QObject {
  Q_OBJECT

public:
  int events;
  int joydev;
  QSocketNotifier * notifier;

  static SbBool enabled;

  char * name;
  int numaxes;
  int32_t * axisvalues;
  int numbuttons;
  SbBool * buttonvalues;

  SbBool focusToWindow;

  float rotationScaleFactor;
  float translationScaleFactor;

  SoMotion3Event * motion3Event;
  SoSpaceballButtonEvent * buttonEvent;

  SoMotion3Event * makeMotion3Event(SoQt6dofDevicePressureEvent * event);
  SoSpaceballButtonEvent * makeButtonEvent(SoQt6dofDeviceButtonEvent * event,
                                           SoButtonEvent::State state);

  static const char * getDevicePathName(void);

public slots:
  void device_event(int);

};

// *************************************************************************

#endif // ! SOQT_LINUXJOYSTICKP_H
