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

#include <Inventor/SbColor4f.h>
#include <Inventor/lists/SbList.h>
#include <Inventor/system/inttypes.h>
#include <Inventor/SbString.h>

class SbColor4f;

class Tick {
public:
  SbColor4f left;
  SbColor4f right;
  float t;
};

class Gradient
{
public:
  Gradient(SbColor4f * color0 = NULL, SbColor4f * color1 = NULL);
  Gradient(const Gradient& grad);
  Gradient(const SbString filename);
  ~Gradient();

  int numTicks() const;
  float getParameter(int i) const;
  SbColor4f eval(float t) const;
  
  void moveTick(int i, float t);
  void removeTick(int i);
  int insertTick(float t);

  const SbList<Tick> & getTicks(void) const;

  void setChangeCallback(void (*changeCB)(void));

  uint32_t getColor(int i, SbBool left) const;
  void setColor(int i, SbBool left, const SbColor4f &);

  void getColorArray(SbColor4f * colors, int num) const;

  void save(const SbString& filename);
  void load(const SbString& filename);

  Gradient & operator = (const Gradient & grad);

private:
  SbList<Tick> ticks;
  void (*changeCB)(void);
};




#endif // GRADIENT_H
