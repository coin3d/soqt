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

//  $Id$

#ifndef SOQT_SPACEBALL_H
#define SOQT_SPACEBALL_H

#include <Inventor/Qt/devices/SoQtDevice.h>

class SOQT_DLL_EXPORT SoQtSpaceball : public SoQtDevice {
  SOQT_TYPED_OBJECT_HEADER(SoQtSpaceball);
  typedef SoQtDevice inherited;
  Q_OBJECT

public:
  enum Mask {
    MOTION = 0x01,
    PRESS = 0x02,
    RELEASE = 0x04,
    ALL = 0x07
  };

  SoQtSpaceball(Mask mask = SoQtSpaceball::ALL);
  virtual ~SoQtSpaceball(void);

  virtual void enable( QWidget * widget, SoQtEventHandler * handler,
    void * closure );
  virtual void disable( QWidget * widget, SoQtEventHandler * handler,
    void * closure );

  virtual const SoEvent * translateEvent( QEvent * event );

  void setRotationScaleFactor(float f);
  float getRotationScaleFactor(void) const;
  void setTranslationScaleFactor(float f);
  float getTranslationScaleFactor(void) const;

  static SbBool exists(void);

  void setFocusToWindow(SbBool flag);
  SbBool isFocusToWindow(void) const;

private:
  float rotationscale, translationscale;
  SbBool focustowindow;
  Mask mask;

}; // class SoQtSpaceball

#endif // ! SOQT_SPACEBALL_H
