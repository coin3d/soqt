#ifndef SOQTSIGNALTHREAD_H
#define SOQTSIGNALTHREAD_H

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

#include <qobject.h>

// FIXME: i had to make this hack to work around different versions of
// Qt. We could consider adding a test-for-QThread configure test, but
// we'd still need a hack to avoid that moc complains about this file
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
