/**************************************************************************
 *
 *  Copyright (C) 2000 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
 **************************************************************************/

//  $Id$

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

class SOQT_DLL_EXPORT SoQtLinuxJoystick : public SoQtDevice {
  typedef SoQtDevice inherited;
  Q_OBJECT

public:
  enum LinuxJoystickEvents {
    ALL_EVENTS = 0
  };

  SoQtLinuxJoystick( int events = SoQtLinuxJoystick::ALL_EVENTS );
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

#define SO_QT_ALL_LINUX_JOYSTICK_EVENTS SoQtLinuxJoystick::ALL_EVENTS

// *************************************************************************

#endif // ! SOQT_LINUXJOYSTICK_H
