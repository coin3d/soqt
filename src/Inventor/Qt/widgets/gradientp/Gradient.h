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

class Tick {
public:
  QRgb left;
  QRgb right;
  float t;
};
 
class Gradient
{
public:
  Gradient(const QColor& color0 = Qt::red, const QColor& color1 = Qt::blue);
  Gradient(const Gradient& grad);
  Gradient(const QString filename);
  ~Gradient();

  int numTicks() const;
  float getParameter(int i) const;
  QRgb eval(float t) const;
  
  void moveTick(int i, float t);
  void removeTick(int i);
  int insertTick(float t);

  void setChangeCallback(void (*changeCB)(void));

  QRgb getColor(int i, bool left) const;
  void setColor(int i, bool left, const QRgb color);

  void getColorArray(QRgb * colors, int num) const;

  void save(const QString& filename);
  void load(const QString& filename);

  Gradient & operator = (const Gradient & grad);
  void handleChange() const;

private:
  QValueList<Tick> ticks;
  void (*changeCB)(void);
};




#endif // GRADIENT_H
