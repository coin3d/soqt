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

#ifndef SOQT_DEVICE_H
#define SOQT_DEVICE_H

/*!
  \defgroup qtdevices Qt Device Classes
*/

#include <Inventor/SbLinear.h>

#include <Inventor/Qt/SoQtObject.h>

class QEvent;
class QWidget;

class SbPList;
class SoEvent;

typedef int soqtEventMask;

// *************************************************************************

class SOQT_DLL_API SoQtDevice : public SoQtObject {
  SOQT_OBJECT_ABSTRACT_HEADER(SoQtDevice, SoQtObject);
  Q_OBJECT

public:
  typedef void SoQtEventHandler( QWidget *, void *, QEvent *, bool * );

  SoQtDevice(void);
  virtual ~SoQtDevice(void);

  virtual void enable( QWidget * widget, SoQtEventHandler * handler,
    void * closure ) = 0;
  virtual void disable( QWidget * w, SoQtEventHandler * handler,
    void * closure ) = 0;

  virtual const SoEvent * translateEvent( QEvent * event ) = 0;

  void setWindowSize( const SbVec2s size );
  SbVec2s getWindowSize(void) const;

  static void initClasses(void);

protected:
  void setEventPosition( SoEvent * event, int x, int y ) const;
  static QPoint getLastEventPosition(void);

  void addEventHandler( QWidget *, SoQtEventHandler *, void * );
  void removeEventHandler( QWidget *, SoQtEventHandler *, void * );
  void invokeHandlers( QEvent * event );

private:
  static void setLastEventPosition(QPoint p);
  static QPoint * lasteventposition;
  SbVec2s widgetsize;

  SbPList * handlers;

  // For setting SoQtDevice::lasteventposition in
  // SoQtRenderArea::processEvents() (as a workaround for a Qt design
  // problem vs Xt).
  friend class SoQtRenderArea;

}; // class SoQtDevice

typedef void (*SoQtEventHandlerPtr)( QWidget *, void *, QEvent *, bool * );

// *************************************************************************

// temporary hacks for the spaceball/linux joystick support

enum SoQtCustomEvents {
  soqt6dofDeviceButtonPressedEvent   = (QEvent::User + 1),
  soqt6dofDeviceButtonReleasedEvent,
  soqt6dofDevicePressureEvent
};

class SOQT_DLL_API SoQt6dofDevicePressureEvent : public QCustomEvent {
  typedef QCustomEvent inherited;

public:
  SoQt6dofDevicePressureEvent(void);

  void setTranslation( float x, float y, float z );
  void getTranslation( float & x, float & y, float & z ) const;

  void setRotation( float x, float y, float z );
  void getRotation( float & x, float & y, float & z ) const;

private:
  float trans_x, trans_y, trans_z;
  float rot_x, rot_y, rot_z;

}; // class SoQt6dofDevicePressureEvent

class SOQT_DLL_API SoQt6dofDeviceButtonEvent : public QCustomEvent {
  typedef QCustomEvent inherited;

public:
  SoQt6dofDeviceButtonEvent(void);

  void setButton( unsigned int button );
  unsigned int getButton(void) const;

  void setState( unsigned int state );
  unsigned int getState(void) const;

  void setNumButtons( unsigned int buttons );
  unsigned int getNumButtons(void) const;

  int isButtonPress(void) const;

private:
  unsigned int state;
  unsigned int button;
  unsigned int buttons;

}; // class SoQt6dofDeviceButtonEvent

// *************************************************************************

#endif // ! SOQT_DEVICE_H
