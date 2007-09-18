#ifndef SOQTSIGNALTHREAD_H
#define SOQTSIGNALTHREAD_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

#ifndef SOQT_INTERNAL
#error this is a private header file
#endif /* !SOQT_INTERNAL */

#include <qobject.h>

// FIXME: i had to make this hack to work around different versions of
// Qt. We could consider adding a test-for-QThread configure test, but
// we'd still need a hack to avoid that moc comlains about this file
// if we're unable to inherit from QThread. pederb, 2008-09-18

#if QT_VERSION > 0x040000 && !defined(QT_NO_THREAD)
#include <qthread.h>
#include <qwaitcondition.h>
#include <qmutex.h>
#define SOQT_SIGNAL_THREAD_ACTIVE 1
#define SOQT_TMP_QTHREAD_NAME QThread
#else // Qt 4 and thread subsystem
#define SOQT_TMP_QTHREAD_NAME QObject
#endif // no QThread

class SoQtP;

class SoQtSignalThread : public SOQT_TMP_QTHREAD_NAME {
  Q_OBJECT
public:
  SoQtSignalThread(void);
  virtual ~SoQtSignalThread();

  virtual void run(void);
  void trigger(void);
  void stopThread(void);

signals:

  void triggerSignal(void);

private:
#ifdef SOQT_SIGNAL_THREAD_ACTIVE
  QWaitCondition waitcond;
  QMutex mutex;
#endif // SOQT_SIGNAL_THREAD_ACTIVE
  bool isstopped;
};

#endif // SOQTSIGNALTHREAD_H

