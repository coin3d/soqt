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

#include <iostream.h>
#include <fstream.h>
#include <assert.h>
#include "Gradient.h"

Gradient::Gradient(const QColor& color0, const QColor& color1)
{
  Tick tick0;
  Tick tick1;
  tick0.t = 0.0f;
  tick1.t = 1.0f;

  if (color0.isValid() && color1.isValid()) {
    for (int i = 0; i < 4; i++) {
      tick0.right = color0.rgb();
      tick0.left = color1.rgb();
      tick1.right = color0.rgb();
      tick1.left = color1.rgb();
    }
  } 
  
  this->ticks.append(tick0);
  this->ticks.append(tick1);

  this->changeCB = NULL;
}

Gradient::Gradient(const Gradient & grad)
{
  this->operator=(grad);
}

Gradient::Gradient(const QString filename)
{
  this->load(filename);
  this->changeCB = NULL;
}

Gradient::~Gradient()
{
}

Gradient & Gradient::operator = (const Gradient & grad)
{
  this->ticks = grad.ticks;
  this->changeCB = grad.changeCB;
  return *this;
}

// evaluates the gradient at a given parameter
QRgb Gradient::eval(float t) const
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

  QRgb left = this->ticks[i].left;
  QRgb right = this->ticks[i-1].right;

  int r = int ((w0 * float(qRed(right)) + w1 * float(qRed(left)) + 0.5f));
  int g = int ((w0 * float(qGreen(right)) + w1 * float(qGreen(left)) + 0.5f));
  int b = int ((w0 * float(qBlue(right)) + w1 * float(qBlue(left)) + 0.5f));
  int a = int ((w0 * float(qAlpha(right)) + w1 * float(qAlpha(left)) + 0.5f));

  return qRgba(r, g, b, a);
}

int Gradient::numTicks() const
{
  return ticks.size();
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
  Tick tick;
  tick.t = t;
  QRgb color = this->eval(t);
  tick.left = color;
  tick.right = color;

  int i = 0;
  QValueList<Tick>::Iterator it = this->ticks.begin();
  while ((*it).t < t) { it++; i++; }

  this->ticks.insert(it, tick);

  return i;
}

void Gradient::removeTick(int i)
{
  QValueList<Tick>::Iterator it = this->ticks.begin();
  // the += operator wasn't available until Qt 3.1.0. Just interate
  // and use ++. pederb, 2003-09-22
  for (int j = 0; j < i; j++) {
    it++;
  }
  this->ticks.remove(it);
  
  if (this->changeCB) this->changeCB();
}

bool Gradient::leftEqualsRight(int i) const
{
  return (this->ticks[i].left == this->ticks[i].right);
}

void Gradient::setColor(int i, bool left, const QRgb color)
{
  int maxIndex = this->ticks.size() - 1;

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

QRgb Gradient::getColor(int i, bool left) const
{
  QRgb color;
  
  int maxIndex = this->ticks.size() - 1;
  if (i < 0) i = maxIndex;
  if (i > maxIndex) i = 0;

  if (left) color = this->ticks[i].left;
  else      color = this->ticks[i].right;

  return color;
}

void Gradient::setChangeCallback(void (*changeCB)(void))
{
  this->changeCB = changeCB;
}

void Gradient::handleChange() const
{
  if (this->changeCB)
    this->changeCB();
}

void Gradient::getColorArray(QRgb * colors, int num) const
{
  for (int i = 0; i < num; i++) {
    float t = float(i) / float(num - 1);
    colors[i] = this->eval(t);
  }
}

void Gradient::save(const QString& filename)
{
  fstream out(filename.ascii(), ios::out);
  out << this->ticks.size() << " ";
  for (unsigned int i = 0; i < this->ticks.size(); i++) {
    out << this->ticks[i].t << " ";
    out << this->ticks[i].left << " ";
    out << this->ticks[i].right << " ";
  }
  out.close();
}

void Gradient::load(const QString& filename)
{
  this->ticks.clear();
  fstream in(filename.ascii(), ios::in);

  int length;
  in >> length;

  for (int i = 0; i < length; i++) {
    Tick tick;
    in >> tick.t;
    in >> tick.left;
    in >> tick.right;
    this->ticks.append(tick);
  }
  in.close();
}


