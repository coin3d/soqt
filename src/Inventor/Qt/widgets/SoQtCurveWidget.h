#ifndef SOQTCURVEWIDGET_H
#define SOQTCURVEWIDGET_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2003 by Systems in Motion.  All rights reserved.
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
 *  See <URL:http://www.coin3d.org> for more information.
 *
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no>.
 *
\**************************************************************************/

#include <QWidget.h>
#include <Inventor/system/inttypes.h>
#include "ColorCurve.h"

class SoQtCurveWidget : public QWidget {

public:
  SoQtCurveWidget(QWidget * parent = 0, const char * name = 0);
  ~SoQtCurveWidget(void);

  enum Mode {
    LUMINANCE = 1,
    LUMINANCE_ALPHA,
    RGB,
    RGBA
  };

  void setMode(Mode mode);
  void setColors(uint8_t * color, int num, Mode mode);
  void getColors(uint8_t * color, int num, Mode mode) const;
  void setCallBack(ColorCurve::ChangeCB * cb, void * userData);

private:
  class SoQtCurveWidgetP * pimpl;
};

#endif // SOQTCURVEWIDGET_H