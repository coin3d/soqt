/**************************************************************************
 *
 *  This file is part of the Coin SoQt GUI binding library.
 *  Copyright (C) 2000 by Systems in Motion.  All rights reserved.
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

#ifndef SOQTP_H
#define SOQTP_H

#include <qtimer.h>
#include <qapplication.h>
#include <qwidget.h>

// ************************************************************************

// This class contains common data and methods that we want to share
// among classes within SoQt, but which should not be publicly visible
// in the library API.

class SoQtP : public QObject
{
  Q_OBJECT

public:
  static void clean(void);
  static SoQtP * soqt_instance(void);

  static QWidget * mainwidget;
  static QApplication * appobject;
  static QTimer * timerqueuetimer;
  static QTimer * idletimer;
  static QTimer * delaytimeouttimer;

  static SoQtP * slotobj;

public slots:
  void slot_timedOutSensor(void);
  void slot_idleSensor(void);
  void slot_delaytimeoutSensor(void);
};

// ************************************************************************

#endif // ! SOQTP_H
