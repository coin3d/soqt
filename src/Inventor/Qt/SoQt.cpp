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

// *************************************************************************

// Class documentation in common/SoGuiCommon.cpp.in.

// *************************************************************************

/*!
  \mainpage

  %SoQt is a C++ GUI toolkit for using Coin with the Qt library.  It
  can also be used on top of Open Inventor from SGI and TGS.  The API
  is based on the InventorXt API originally from SGI.

  For a small and simple example on how it is used, see the example
  code in the class documentation of the SoQt class.

  Qt is a C++ toolkit for primarily the GUI parts of application
  development. Qt is a multi-platform library, available for X11-based
  systems (UNIX, Linux and *BSDs, for instance), MSWindows, Mac OS X
  and embedded systems.

  For more information on the Qt GUI toolkit, see the web site for
  Troll Tech (makers of Qt): <http://www.trolltech.com>.

  The corresponding documentation for Coin is located 
  <a href="http://doc.coin3d.org/Coin/">here</a>.
*/

// *************************************************************************


#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <stdlib.h>

/* The setting of this define needs to be added manually to
   configure.in for all relevant projects. */
#ifdef HAVE_X11_AVAILABLE
#include <Inventor/Qt/devices/spwinput.h>
#endif // HAVE_X11_AVAILABLE

#include <qmainwindow.h>
#include <qmessagebox.h>
#include <qtimer.h>
#include <qevent.h>
#include <qapplication.h>
#include <qmetaobject.h>

#include <moc_SoQtP.cpp>
#include <SoQtP.h>

#include <Inventor/SoDB.h>
#include <Inventor/SoInteraction.h>
#include <Inventor/nodekits/SoNodeKit.h>
#include <Inventor/SbTime.h>
#include <Inventor/errors/SoDebugError.h>

#include <soqtdefs.h>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoQtObject.h>
#include <Inventor/Qt/devices/SoQtDevice.h>
#include <Inventor/Qt/SoQtComponent.h>
#include <Inventor/Qt/SoAny.h>
#include <Inventor/Qt/SoQtInternal.h>

// *************************************************************************

// The private data for the SoQt class.

#ifndef DOXYGEN_SKIP_THIS // Skip internal classes SoQtP and SoQtApplication.

QWidget * SoQtP::mainwidget = NULL;
QApplication * SoQtP::appobject = NULL;
QTimer * SoQtP::idletimer = NULL;
QTimer * SoQtP::timerqueuetimer = NULL;
QTimer * SoQtP::delaytimeouttimer = NULL;
SoQtP * SoQtP::slotobj = NULL;
bool SoQtP::didcreatemainwidget = FALSE;

// We're using the singleton pattern to create a single SoQtP object
// instance (a dynamic object is needed for attaching slots to signals
// -- this is really a workaround for some silliness in the Qt
// design).
SoQtP *
SoQtP::soqt_instance(void)
{
  if (!SoQtP::slotobj) { SoQtP::slotobj = new SoQtP; }
  return SoQtP::slotobj;
}

// A timer sensor is ready for triggering, so tell the sensor manager
// object to process the queue.
void
SoQtP::slot_timedOutSensor()
{
  if (SOQT_DEBUG && 0) { // debug
    SoDebugError::postInfo("SoQt::timedOutSensor",
                           "processing timer queue");
    SoDebugError::postInfo("SoQt::timedOutSensor",
                           "is %s",
                           SoQtP::delaytimeouttimer->isActive() ?
                           "active" : "inactive");
  }

  SoDB::getSensorManager()->processTimerQueue();

  // The change callback is _not_ called automatically from
  // SoSensorManager after the process methods, so we need to
  // explicitly trigger it ourselves here.
  SoGuiP::sensorQueueChanged(NULL);
}

// The system is idle, so we're going to process the queue of delay
// type sensors.
void
SoQtP::slot_idleSensor()
{
  if (SOQT_DEBUG && 0) { // debug
    SoDebugError::postInfo("SoQt::idleSensor", "processing delay queue");
    SoDebugError::postInfo("SoQt::idleSensor", "is %s",
                           SoQtP::idletimer->isActive() ? "active" : "inactive");
  }

  SoDB::getSensorManager()->processTimerQueue();
  SoDB::getSensorManager()->processDelayQueue(TRUE);

  // The change callback is _not_ called automatically from
  // SoSensorManager after the process methods, so we need to
  // explicitly trigger it ourselves here.
  SoGuiP::sensorQueueChanged(NULL);
}

// The delay sensor timeout point has been reached, so process the
// delay queue even though the system is not idle.
void
SoQtP::slot_delaytimeoutSensor()
{
  if (SOQT_DEBUG && 0) { // debug
    SoDebugError::postInfo("SoQt::delaytimeoutSensor",
                           "processing delay queue");
    SoDebugError::postInfo("SoQtP::delaytimeouttimer", "is %s",
                           SoQtP::delaytimeouttimer->isActive() ?
                           "active" : "inactive");
  }

  SoDB::getSensorManager()->processTimerQueue();
  SoDB::getSensorManager()->processDelayQueue(FALSE);

  // The change callback is _not_ called automatically from
  // SoSensorManager after the process methods, so we need to
  // explicitly trigger it ourselves here.
  SoGuiP::sensorQueueChanged(NULL);
}

// This function gets called whenever something has happened to any of
// the sensor queues. It starts or reschedules a timer which will
// trigger when a sensor is ripe for plucking.
void
SoGuiP::sensorQueueChanged(void *)
{
  // We need three different mechanisms to interface Coin with Qt, 
  // which are:
  // 1. detect when application is idle (and then empty the delay-queue
  //    completely for delay-sensors) -- handled by SoQtP::idletimer;
  // 2. detect when one or more timer-sensors are ripe and trigger those
  //    -- handled by SoQtP::timerqueuetimer;
  // 3. on the "delay-sensor timeout interval, empty all highest
  //    priority delay-queue sensors to avoid complete starvation in
  //    continually busy applications -- handled by
  //    SoQTP::delaytimeouttimer


  // Allocate Qt timers on first call.

  if (!SoQtP::timerqueuetimer) {
    SoQtP::timerqueuetimer = new QTimer;
    QObject::connect(SoQtP::timerqueuetimer, SIGNAL(timeout()),
                     SoQtP::soqt_instance(), SLOT(slot_timedOutSensor()));
    SoQtP::idletimer = new QTimer;
    QObject::connect(SoQtP::idletimer, SIGNAL(timeout()),
                     SoQtP::soqt_instance(), SLOT(slot_idleSensor()));
    SoQtP::delaytimeouttimer = new QTimer;
    QObject::connect(SoQtP::delaytimeouttimer, SIGNAL(timeout()),
                     SoQtP::soqt_instance(), SLOT(slot_delaytimeoutSensor()));
  }

  SoSensorManager * sm = SoDB::getSensorManager();

  // Set up timer queue timeout if necessary.

  SbTime t;
  if (sm->isTimerSensorPending(t)) {
    SbTime interval = t - SbTime::getTimeOfDay();
    // Qt v2.1.1 (at least) on MSWindows will fail to trigger the
    // timer if the interval is < 0.0. (And 0 has special meaning:
    // trigger only when the application is idle and event queue is
    // empty).
    if (interval.getValue() <= 0.0) { interval.setValue(1.0/5000.0); }

    if (SOQT_DEBUG && 0) { // debug
      SoDebugError::postInfo("SoQt::sensorQueueChanged",
                             "timersensor pending, interval %f",
                             interval.getValue());
    }

    // Change interval of timerqueuetimer when head node of the
    // timer-sensor queue of SoSensorManager changes. 
    if (!SoQtP::timerqueuetimer->isActive())
      SoQtP::timerqueuetimer->start((int)interval.getMsecValue(), TRUE);
    else
      SoQtP::timerqueuetimer->changeInterval((int)interval.getMsecValue());
  }
  // Stop timerqueuetimer if queue is completely empty.
  else if (SoQtP::timerqueuetimer->isActive()) {
    SoQtP::timerqueuetimer->stop();
  }


  // Set up idle notification for delay queue processing if necessary.

  if (sm->isDelaySensorPending()) {
    if (SOQT_DEBUG && 0) { // debug
      SoDebugError::postInfo("SoQt::sensorQueueChanged",
                             "delaysensor pending");
    }

    // Start idletimer at 0 seconds in the future. -- That means it will 
    // trigger when the Qt event queue has been run through, i.e. when 
    // the application is idle.
    if (!SoQtP::idletimer->isActive()) SoQtP::idletimer->start(0, TRUE);

    if (!SoQtP::delaytimeouttimer->isActive()) {
      unsigned long timeout = SoDB::getDelaySensorTimeout().getMsecValue();
      SoQtP::delaytimeouttimer->start((int)timeout, TRUE);
    }
  }
  else {
    if (SoQtP::idletimer->isActive()) SoQtP::idletimer->stop();
    if (SoQtP::delaytimeouttimer->isActive()) SoQtP::delaytimeouttimer->stop();
  }
}

// *************************************************************************

// We overload the QApplication class to be able to get hold of the
// X11 events directly. (This is necessary to handle Spacetec
// spaceball devices.)
class SoQtApplication : public QApplication {
public:
  SoQtApplication(int argc, char ** argv) : QApplication(argc, argv) { }
#ifdef HAVE_X11_AVAILABLE
  virtual bool x11EventFilter(XEvent * e) {
    SPW_InputEvent sbEvent;
    QWidget * topw = SoQt::getTopLevelWidget();
    if (topw && SPW_TranslateEventX11(topw->x11Display(), e, &sbEvent)) {
      QWidget * focus = this->focusWidget();
      if (!focus) focus = this->activeWindow();
      if (focus) {
        QCustomEvent qevent((QEvent::Type)SoQtInternal::SPACEBALL_EVENT,
                            (void *)&sbEvent);
        QApplication::sendEvent(focus, &qevent);
      }
    }
    return QApplication::x11EventFilter(e);
  }
#endif // HAVE_X11_AVAILABLE
};

#endif // DOXYGEN_SKIP_THIS

// *************************************************************************

// documented in common/SoGuiCommon.cpp.in
void
SoQt::init(QWidget * toplevelwidget)
{
  // This init()-method is called by the other 2 init()'s, so place
  // common code here.

  if (SOQT_DEBUG && SoQtP::mainwidget) {
    SoDebugError::postWarning("SoQt::init",
                              "This method should be called only once.");
    return;
  }

  SoDB::init();
  SoNodeKit::init();
  SoInteraction::init();
  SoQtObject::init();

  SoDB::getSensorManager()->setChangedCallback(SoGuiP::sensorQueueChanged, NULL);
  SoQtP::mainwidget = toplevelwidget;
}

// documented in common/SoGuiCommon.cpp.in
QWidget *
SoQt::init(int & argc, char ** argv, const char * appname, const char * classname)
{
  if (SOQT_DEBUG && (SoQtP::appobject || SoQtP::mainwidget)) {
    SoDebugError::postWarning("SoQt::init",
                              "This method should be called only once.");
    return SoQtP::mainwidget;
  }

  if (qApp == NULL) {
    // Set up the QApplication instance which we have derived into a
    // subclass to catch spaceball events.
    SoQtP::appobject = new SoQtApplication(argc, argv);
  }
  else {
    // The user already set one up for us.
    //
    // FIXME: should somehow warn about the fact that spaceball events
    // will not be caught, if a spaceball is attempted used. 20020619 mortene.
    SoQtP::appobject = qApp;
  }

  QWidget * mainw = new QWidget(NULL, classname);
  SoQtP::didcreatemainwidget = TRUE;
  SoQt::init(mainw);

  if (appname) { SoQtP::mainwidget->setCaption(appname); }
  SoQtP::appobject->setMainWidget(SoQtP::mainwidget);
  return SoQtP::mainwidget;
}

/*!
  This is the event dispatch loop. It doesn't return until
  \a QApplication::quit() or \a QApplication::exit() is called (which
  is also done automatically by Qt whenever the user closes an application's
  main widget).
*/
void
SoQt::mainLoop(void)
{
  (void) qApp->exec();

  // The invocation of SoQt::done() used to be triggered from
  // atexit(), but this was changed as we were getting mysterious
  // crashes. No wonder, perhaps, as for all we know the Qt library is
  // cleaned up _before_ our atexit() methods are invoked.
  SoQt::done();
}

/*!
  This function will make the main event loop finish looping.

  NOTE: exitMainLoop() is not present in the original API for SGI's
  InventorXt library.
*/
void
SoQt::exitMainLoop(void)
{
  qApp->exit(0);
}

// documented in common/SoGuiCommon.cpp.in
void
SoQt::done(void)
{
  delete SoQtP::timerqueuetimer; SoQtP::timerqueuetimer = NULL;
  delete SoQtP::idletimer; SoQtP::idletimer = NULL;
  delete SoQtP::delaytimeouttimer; SoQtP::delaytimeouttimer = NULL;

  if (SoQtP::didcreatemainwidget) {
    delete SoQtP::mainwidget;
    SoQtP::mainwidget = NULL;
    SoQtP::didcreatemainwidget = FALSE;
  }

  // Notice that we *don't* delete the QApplication object, even
  // though it originated with us, as it might be used someplace else
  // in the application.
  //
  // (Keep this disabled code in place here, so we don't reactivate
  // this by mistake again.)
  //
  // delete SoQtP::appobject; SoQtP::appobject = NULL;

  delete SoQtP::slotobj; SoQtP::slotobj = NULL;
}


/*!
  Returns a pointer to the Qt QWidget which is the main widget for the
  application. When this widget gets closed, SoQt::mainLoop() will
  return (unless the close event is caught by the user).

  \sa getShellWidget()
*/
QWidget *
SoQt::getTopLevelWidget(void)
{
  return SoQtP::mainwidget;
}

/*!
  Returns a pointer to the Qt QWidget which is the top level widget for the
  given QWidget \a w. This is just a convenience function provided for
  easier porting of Open Inventor applications based on SoXt components,
  as you can do the same thing by calling the QWidget::topLevelWidget()
  method directly on \a w.

  \sa getTopLevelWidget()
*/

QWidget *
SoQt::getShellWidget(const QWidget * w)
{
  if (SOQT_DEBUG && !w) {
    SoDebugError::postWarning("SoQt::getShellWidget",
                              "Called with NULL pointer.");
    return NULL;
  }

  return w->topLevelWidget();
}

/*!
  This method is provided for easier porting/compatibility with the
  Open Inventor SoXt component classes. It will call QWidget::show() and
  QWidget::raise() on the provided \a widget pointer.

  \sa hide()
*/

void
SoQt::show(QWidget * const widget)
{
  assert(widget && "called with NULL pointer");
  widget->show();
  widget->raise();
}

/*!
  This method is provided for easier porting/compatibility with the
  Open Inventor SoXt component classes. It will call QWidget::hide() on the
  provided \a widget pointer.

  \sa show()
*/

void
SoQt::hide(QWidget * const widget)
{
  assert(widget && "called with NULL pointer");
  widget->hide();
}

/*!
  This method is provided for easier porting of applications based on the
  Open Inventor SoXt component classes. It will call QWidget::resize() on the
  provided \a w widget pointer.

  \sa getWidgetSize()
*/

void
SoQt::setWidgetSize(QWidget * const w, const SbVec2s size)
{
  if (SOQT_DEBUG && !w) {
    SoDebugError::postWarning("SoQt::setWidgetSize",
                              "Called with NULL pointer.");
    return;
  }
  if (SOQT_DEBUG && ((size[0] <= 0) || (size[1] <= 0))) {
    SoDebugError::postWarning("SoQt::setWidgetSize",
                              "Called with invalid dimension(s): (%d, %d).",
                              size[0], size[1]);
    return;
  }

#if 0 // debug
  SoDebugError::postInfo("SoQt::setWidgetSize",
                         "resize %p: (%d, %d)",
                         w, size[0], size[1]);
#endif // debug

  w->resize(size[0], size[1]);
}

/*!
  This method is provided for easier porting/compatibility with the
  Open Inventor SoXt component classes. It will do the same as calling
  QWidget::size() (except that we're returning an SbVec2s).

  \sa setWidgetSize()
*/

SbVec2s
SoQt::getWidgetSize(const QWidget * w)
{
  if (SOQT_DEBUG && !w) {
    SoDebugError::postWarning("SoQt::getWidgetSize",
                              "Called with NULL pointer.");
    return SbVec2s(0, 0);
  }

  return SbVec2s(w->width(), w->height());
}

// Documented in common/SoGuiCommon.cpp.in.
//
// Just a simple wrap-around for the Qt QMessageBox::warning() call,
// provided for easier porting from applications using the Open
// Inventor SoXt component classes.
void
SoQt::createSimpleErrorDialog(QWidget * widget,
                              const char * title,
                              const char * string1,
                              const char * string2)
{
  if (SOQT_DEBUG && !title) {
    SoDebugError::postWarning("SoQt::createSimpleErrorDialog",
                              "Called with NULL title pointer.");
  }
  if (SOQT_DEBUG && !string1) {
    SoDebugError::postWarning("SoQt::createSimpleErrorDialog",
                              "Called with NULL error string pointer.");
  }

  SbString t(title ? title : "");
  SbString errstr(string1 ? string1 : "");

  if (string2) {
    errstr += '\n';
    errstr += string2;
  }

  QMessageBox::warning(widget, t.getString(), errstr.getString());
}

// *************************************************************************
