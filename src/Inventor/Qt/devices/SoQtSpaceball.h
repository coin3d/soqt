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

#ifndef SOQT_SPACEBALL_H
#define SOQT_SPACEBALL_H

#include <Inventor/Qt/devices/SoQtDevice.h>

class SoQtSpaceball : public SoQtDevice
{
public:
  enum Mask {
    MOTION = 0x01,
    PRESS = 0x02,
    RELEASE = 0x04,
    ALL = 0x07
  };

  SoQtSpaceball(Mask mask = SoQtSpaceball::ALL);
  virtual ~SoQtSpaceball(void);

  virtual void enable(QWidget * w, SoQtEventHandler f, void * data);
  virtual void disable(QWidget * w, SoQtEventHandler f, void * data);

  virtual const SoEvent * translateEvent(QEvent * event);

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
