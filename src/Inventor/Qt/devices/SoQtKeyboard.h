/**************************************************************************\
 *
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
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

//  $Id$

#ifndef SOQT_KEYBOARD_H
#define SOQT_KEYBOARD_H

#include <Inventor/Qt/devices/SoQtDevice.h>
#include <Inventor/SbDict.h>

class SoKeyboardEvent;

#define soqtKeyPressMask   0x01
#define soqtKeyReleaseMask 0x02

#define SO_QT_ALL_KEYBOARD_EVENTS (soqtKeyPressMask | soqtKeyReleaseMask)

class SOQT_DLL_EXPORT SoQtKeyboard : public SoQtDevice {
  typedef SoQtDevice inherited;
  Q_OBJECT

public:
  SoQtKeyboard(soqtEventMask mask = SO_QT_ALL_KEYBOARD_EVENTS);
  virtual ~SoQtKeyboard(void);

  virtual void enable( QWidget * widget, SoQtEventHandler * handler,
    void * closure );
  virtual void disable( QWidget * widget, SoQtEventHandler * handler,
    void * closure );

  virtual const SoEvent * translateEvent( QEvent * event );

private:
  static void makeTranslationTable(void);

  soqtEventMask eventmask;
  SoKeyboardEvent * kbdevent;
  static SbDict * translatetable;

}; // class SoQtKeyboard

#endif // ! SOQT_KEYBOARD_H
