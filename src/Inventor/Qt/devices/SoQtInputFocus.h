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

#ifndef SOQT_INPUTFOCUS_H
#define SOQT_INPUTFOCUS_H

#include <Inventor/Qt/devices/SoQtDevice.h>

// *************************************************************************

#define soqtEnterWindowMask 0x01
#define soqtLeaveWindowMask 0x02

#define SO_QT_ALL_FOCUS_EVENTS SoQtInputFocus::ALL_EVENTS;

class SOQT_DLL_API SoQtInputFocus : public SoQtDevice {
  SOQT_OBJECT_HEADER(SoQtInputFocus, SoQtDevice);
  Q_OBJECT

public:
  enum EventMask {
    ENTER_WINDOW = 0x01,
    LEAVE_WINDOW = 0x02,
    ALL_EVENTS = 0x03
  };

  SoQtInputFocus( int mask = ALL_EVENTS );
  virtual ~SoQtInputFocus(void);

  virtual void enable( QWidget * widget, SoQtEventHandler * handler,
    void * closure );
  virtual void disable( QWidget * widget, SoQtEventHandler * handler,
    void * closure );

  virtual const SoEvent * translateEvent( QEvent * event );

private:
  int eventmask;

}; // class SoQtInputFocus

// *************************************************************************

#endif // ! SOQT_INPUTFOCUS_H
