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

#include <fstream.h>
#include <qcolor.h>
#include "Gradient.h"

Gradient::Gradient(SbColor4f * color0, SbColor4f * color1)
{
  Tick tick0;
  Tick tick1;
  tick0.t = 0.0f;
  tick1.t = 1.0f;

  if (color0 != NULL && color1 != NULL) {
    tick0.right = *color0;
    tick0.left = *color1;
    tick1.right = *color0;
    tick1.left = *color1;

  } else {
    // default is black -> white
    tick0.right = SbColor4f(1.0,0.0,0.0,1.0);
    tick0.left = SbColor4f(0.0,0.0,1.0,1.0);
    tick1.right = SbColor4f(1.0,0.0,0.0,1.0);
    tick1.left = SbColor4f(0.0,0.0,1.0,1.0);
  }
  this->ticks.append(tick0);
  this->ticks.append(tick1);

  this->changeCB = NULL;
}

Gradient::Gradient(const Gradient & grad)
{
  this->operator=(grad);
}

Gradient::Gradient(const SbString filename)
{
  this->load(filename);
  this->changeCB = NULL;
}

Gradient::~Gradient()
{
}

Gradient & Gradient::operator = (const Gradient & grad)
{
  this->ticks = grad.getTicks();
  if (this->changeCB)
    this->changeCB();
  return *this;
}

// evaluates the gradient at a given parameter
SbColor4f Gradient::eval(float t) const
{
  assert(t >= 0.0f && t <= 1.0f && 
    "Gradient::eval(float t): t must be in the interval [0,1]");

  // find the interval to evaluate in
  int i = 0;
  while (this->ticks[++i].t < t);

  float t0 = this->ticks[i-1].t;
  float t1 = this->ticks[i].t;
  float dt = t1 - t0;

  // weights for linear interpolation
  float w0 = (t1 - t) / dt;
  float w1 = (t - t0) / dt;

  SbColor4f left = this->ticks[i].left;
  SbColor4f right = this->ticks[i-1].right;

  SbColor4f result;
  // to make sure the alpha values are interpolated aswell
  for (i = 0; i < 4; i++) {
    result[i] = w0 * right[i] + w1 * left[i];
  }
  return result;
}

int Gradient::numTicks() const
{
  return ticks.getLength();
}

float Gradient::getParameter(int i) const
{
  return ticks[i].t;
}

void Gradient::moveTick(int i, float t)
{
  if (this->ticks[i].t != t) {
    this->ticks[i].t = t;
    if (this->changeCB) this->changeCB();
  }
}

int Gradient::insertTick(float t)
{
  SbColor4f color = this->eval(t);
  Tick tick;
  tick.t = t;
  tick.left = color;
  tick.right = color;

  // find index to insert before
  int i = 0;
  while (ticks[++i].t < t);

  this->ticks.insert(tick, i);

  return i;
}

void Gradient::removeTick(int i)
{
  this->ticks.remove(i);
  if (this->changeCB) this->changeCB();
}

void Gradient::setColor(int i, SbBool left, const SbColor4f & color)
{
  int maxIndex = this->ticks.getLength() - 1;

  if (i == 0) {
    this->ticks[i].right = color;
    this->ticks[i].left = this->ticks[maxIndex].left;
    this->ticks[maxIndex].right = color;
  } 
  else if (i == maxIndex) {
    this->ticks[i].left = color;
    this->ticks[i].right = this->ticks[0].right;
    this->ticks[0].left = color;
  }
  else {
    if (left) this->ticks[i].left = color;
    else this->ticks[i].right = color;
  }

  if (this->changeCB) this->changeCB();
}

unsigned int Gradient::getColor(int i, SbBool left) const
{
  SbColor4f color;
  
  int maxIndex = this->ticks.getLength() - 1;
  if (i < 0) i = maxIndex;
  if (i > maxIndex) i = 0;

  if (left) color = this->ticks[i].left;
  else      color = this->ticks[i].right;

  return color.getPackedValue();
}

void Gradient::setChangeCallback(void (*changeCB)(void))
{
  this->changeCB = changeCB;
}

void Gradient::getColorArray(SbColor4f * colors, int num) const
{
  for (int i = 0; i < num; i++) {
    float t = float(i) / float(num-1);
    colors[i] = this->eval(t);
  }
}

void Gradient::save(const SbString& filename)
{
  fstream out(filename.getString(), ios::out);
  out << this->ticks.getLength() << " ";
  for (int i = 0; i < this->ticks.getLength(); i++) {
    out << this->ticks[i].t << " ";
    int j;
    for (j = 0; j < 4; j ++) {
      out << this->ticks[i].left[j] << " ";
    }
    for (j = 0; j < 4; j++) {
      out << this->ticks[i].right[j] << " ";
    }
  }
  out.close();
}

void Gradient::load(const SbString& filename)
{
  this->ticks.truncate(0);
  fstream in(filename.getString(), ios::in);

  int length;
  in >> length;

  for (int i = 0; i < length; i++) {
    Tick tick;
    in >> tick.t;
    
    int j;
    for (j = 0; j < 4; j++) {
      in >> tick.left[j];
    }
    for (j = 0; j < 4; j++) {
      in >> tick.right[j];
    }
  
    this->ticks.append(tick);
  }
  in.close();
}

const SbList<Tick> & Gradient::getTicks() const
{
  return this->ticks;
}
