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
  Q_OBJECT

public:
  enum Events {
    ALL_EVENTS = 0
  };

  SoQtLinuxJoystick( int events = ALL_EVENTS );
  virtual ~SoQtLinuxJoystick(void);

  virtual void enable( QWidget * widget, SoQtEventHandler * handler,
      void * closure );
  virtual void disable( QWidget * widget, SoQtEventHandler * handler,
      void * closure );

  virtual const SoEvent * translateEvent( QEvent * event );

  void setRotationScaleFactor( const float factor );
  float getRotationScaleFactor(void) const;
  void setTranslationScaleFactor( const float factor );
  float getTranslationScaleFactor(void) const;

  static SbBool exists(void);

  void setFocusToWindow( SbBool enable );
  SbBool isFocusToWindow(void) const;

  int getNumButtons(void) const;
  SbBool getButtonValue( const int button ) const;

  int getNumAxes(void) const;
  float getAxisValue( const int axis ) const;

private:
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

  SoMotion3Event * makeMotion3Event( SoQt6dofDevicePressureEvent * event );
  SoSpaceballButtonEvent * makeButtonEvent( SoQt6dofDeviceButtonEvent * event,
      SoButtonEvent::State state );

  static const char * getDevicePathName(void);

private slots:
  void device_event(int);

}; // class SoQtLinuxJoystick

// *************************************************************************

#endif // ! SOQT_LINUXJOYSTICK_H
