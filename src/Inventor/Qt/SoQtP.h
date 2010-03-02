#ifndef SOQTP_H
#define SOQTP_H

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

#include <qtimer.h>
#include <qapplication.h>
#include <qwidget.h>

#include <Inventor/Qt/SoGuiP.h>
#include <Inventor/SbBasic.h>

// ************************************************************************

typedef int SoQtP_XErrorHandler(void *, void *);

// This class contains private data and methods used within the SoQt
// class.
class SoQtSignalThread;
class SoQtImageReader;

class SoQtP : public QObject, public SoGuiP
{
  Q_OBJECT

public:
  static SoQtP * soqt_instance(void);

  static SoQtImageReader * imagereader;
  static int DEBUG_X11SYNC;
  static const char * SOQT_XSYNC;
  static int X11_ERRORHANDLER;
  static const char * SOQT_X11_ERRORHANDLER;
  static SoQtP_XErrorHandler * previous_handler;
  static int X11Errorhandler(void * d, void * ee);

  static int DEBUG_LISTMODULES;

  static int BRIL_X11_SILENCER;

  static QWidget * mainwidget;
  static bool didcreatemainwidget;
  static QApplication * appobject;
  static SbBool madeappobject;
  static QTimer * timerqueuetimer;
  static QTimer * idletimer;
  static QTimer * delaytimeouttimer;
  static SoQtSignalThread * signalthread;

  static unsigned long original_thread;
  static SoQtP * slotobj;

public slots:
  void slot_sensorQueueChanged(void);

  void slot_timedOutSensor(void);
  void slot_idleSensor(void);
  void slot_delaytimeoutSensor(void);

};

// ************************************************************************

#endif // ! SOQTP_H
