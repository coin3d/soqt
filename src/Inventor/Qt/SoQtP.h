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

#ifndef SOQTP_H
#define SOQTP_H

#include <qtimer.h>
#include <qapplication.h>
#include <qwidget.h>

#include <SoGuiP.h>

// ************************************************************************

// This class contains private data and methods used within the SoQt
// class.

class SoQtP : public QObject, public SoGuiP
{
  Q_OBJECT

public:
  static SoQtP * soqt_instance(void);

  static QWidget * mainwidget;
  static bool didcreatemainwidget;
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
