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

#ifndef SOQT_H
#define SOQT_H

#include <math.h>

#include <qapplication.h>

#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>

#include <Inventor/Qt/SoQtBasic.h>

class QTimer;
class SoSensor;

// *************************************************************************

class SOQT_DLL_EXPORT SoQt : public QObject {
  typedef QObject inherited;
  Q_OBJECT

public:
  static QWidget * init(const char * const appName,
                        const char * const className = "SoQt");

  static QWidget * init(int argc, char **argv,
                        const char * const appName,
                        const char * const className = "SoQt");

  static void init(QWidget * const topLevelWidget);

  static void mainLoop(void);
  static void exitMainLoop(void);

  static QApplication * getApplication(void);
  static QWidget * getTopLevelWidget(void);
  static QWidget * getShellWidget(const QWidget * const w);

  static void show(QWidget * const widget);
  static void hide(QWidget * const widget);

  static void setWidgetSize( QWidget * const widget, const SbVec2s size );
  static SbVec2s getWidgetSize( const QWidget * const widget );

  static void createSimpleErrorDialog( QWidget * const widget,
      const char * const dialogTitle, const char * const errorStr1,
      const char * const errorStr2 = NULL );

protected:
  bool eventFilter( QObject *, QEvent * );

private slots:
  void slot_timedOutSensor(void);
  void slot_idleSensor(void);
  void slot_delaytimeoutSensor(void);

private:
  static void sensorQueueChanged( void * cbdata );
  static void clean(void);

  static QWidget * mainWidget;
  static QApplication * appobject;
  static QTimer * timerqueuetimer;
  static QTimer * idletimer;
  static QTimer * delaytimeouttimer;

  static SoQt * soqt_instance(void);
  static SoQt * slotobj;

}; // class SoQt

// *************************************************************************

#endif // ! SOQT_H
