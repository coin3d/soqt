#ifndef GRADIENT_H
#define GRADIENT_H

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

#include <qcolor.h>
#include <qvaluelist.h>
#include <Inventor/Qt/SoQtBasic.h>
#include <Inventor/SbBasic.h>

class SOQT_DLL_API Gradient {

public:
  Gradient(const QColor & color0 = Qt::red, const QColor & color1 = Qt::blue);
  Gradient(const Gradient & grad);
  Gradient(const QString & filename);

  ~Gradient();

  unsigned int numTicks(void) const;
  unsigned int insertTick(float t);
  float getParameter(unsigned int i) const;
  SbBool leftEqualsRight(unsigned int i) const;
  QRgb eval(float t) const;

  enum TickSide { LEFT, RIGHT };
  QRgb getColor(unsigned int i, TickSide s) const;
  void setColor(unsigned int i, TickSide s, const QRgb & color);

  void moveTick(unsigned int i, float t);
  void removeTick(unsigned int i);

  void getColorArray(QRgb * colors, unsigned int num) const;
  void save(const QString & filename) const;
  void load(const QString & filename);

  QImage getImage(unsigned int w, unsigned int h, unsigned int d) const;

  Gradient & operator = (const Gradient & grad);
  SbBool operator == (const Gradient & grad) const;

  typedef void ChangeCB(const Gradient & grad, void * userdata);
  void setChangeCallback(Gradient::ChangeCB * callBack, void * userdata);
  
private:
  class GradientP * pimpl;
};

#endif // ! GRADIENT_H
