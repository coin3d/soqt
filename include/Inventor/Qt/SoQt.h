/**************************************************************************\
 * 
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

#ifndef __SOQT_H__
#define __SOQT_H__

#include <math.h>

#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>

#include <qapplication.h>

class QTimer;
class SoSensor;


class SoQt : public QObject
{
  Q_OBJECT

public:
  static QWidget * init(const char * const appName,
			const char * const className = "SoQt");

  static QWidget * init(int argc, char **argv,
			const char * const appName,
			const char * const className = "SoQt");

  static void init(QWidget * const topLevelWidget);

  static void mainLoop(void);

  static QApplication * getApplication(void);
  static QWidget * getTopLevelWidget(void);
  static QWidget * getShellWidget(const QWidget * const w);

  static void show(QWidget * const widget);
  static void hide(QWidget * const widget);

  static void setWidgetSize(QWidget * const w, const SbVec2s & size);
  static SbVec2s getWidgetSize(const QWidget * const w);

  static void createSimpleErrorDialog(QWidget * const widget, 
				      const char * const dialogTitle, 
				      const char * const errorStr1, 
				      const char * const errorStr2 = NULL);

protected:
  bool eventFilter(QObject *, QEvent *);

private slots:
  void slot_timedOutSensor();
  void slot_idleSensor();
  void slot_delaytimeoutSensor();

private:
  static void clean(void);
  static void sensorQueueChanged(void * cbdata);

  static QWidget * mainWidget;
  static QApplication * appobject;
  static QTimer * timerqueuetimer, * idletimer, * delaytimeouttimer;

  static SoQt * soqt_instance(void);
  static SoQt * slotobj;
};

#endif // !__SOQT_H__
