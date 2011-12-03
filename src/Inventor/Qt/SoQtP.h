#ifndef SOQTP_H
#define SOQTP_H

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
