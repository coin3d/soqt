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
#include "SbGuiCubicSpline.h" // FIXME: the SbCubic spline should perhaps be made available in Coin or SoQt 20031016 frodo
#include "ColorCurve.h"

ColorCurve::ColorCurve(CurveType type, const int numcolors)
  : numpts(256), numcolors(numcolors)
{
  this->curvepts = new SbVec2f[this->numpts];
  this->colormap = new uint8_t[this->numcolors];
  this->type = type;
  this->curve = new SbGuiCubicSpline(numpts);
  this->curve->setBasisMatrix(SbGuiCubicSpline::CATMULL_ROM);
  this->callBack = NULL;
  this->prevx = 0;
  this->needinterpol = FALSE;
  this->resetCtrlPoints();
  this->updateCurvePoints();
}

ColorCurve::~ColorCurve()
{
  delete this->curve;
  delete [] this->curvepts;
  delete [] this->colormap;
}

void
ColorCurve::resetCtrlPoints()
{
  this->ctrlpts.truncate(0);
  this->ctrlpts.append((this->type == ColorCurve::CONSTANT) ? SbVec3f(0.0, 1.0, 0.0) : SbVec3f(0.0, 0.0, 0.0));
  this->ctrlpts.append(SbVec3f(1.0, 1.0, 0.0));
  this->curve->setControlPoints(this->ctrlpts.getArrayPtr(), this->ctrlpts.getLength());
  this->needinterpol = FALSE;
}  


int
ColorCurve::getNumColors() const
{
  return this->numcolors;
}

int 
ColorCurve::getNumCtrlPoints() const
{
  return this->ctrlpts.getLength();
}

void
ColorCurve::setCtrlPoints(const SbGuiList<SbVec3f> & pts)
{
  this->ctrlpts = pts;
  this->curve->setControlPoints(this->ctrlpts.getArrayPtr(), this->ctrlpts.getLength());
  this->updateCurvePoints();
}

const SbGuiList<SbVec3f> &
ColorCurve::getCtrlPoints() const
{
  return this->ctrlpts;
}

void
ColorCurve::fill(int value)
{
  assert((value >= 0) && (value <= this->numcolors-1) && "Color value out of range");
  for (int i = 0; i < this->numcolors; i++) {
    this->colormap[i] = value;
  }
  this->needinterpol = TRUE;
  if (this->callBack) this->callBack(this->callbackdata);
}

void
ColorCurve::setColorMapping(int x, int y)
{
  assert((x <= this->numcolors-1) && (x >= 0) && "Color value out of range");
  assert((y <= this->numcolors-1) && (y >= 0) && "Color value out of range");

  this->colormap[x] = y;
  if ((this->callBack) && (abs(this->prevx - x) > 1)) {
    this->callBack(this->callbackdata);
  }
  this->prevx = x;
  this->needinterpol = TRUE;
}

void
ColorCurve::interpolateColorMapping()
{
  if (this->needinterpol) {
    this->ctrlpts.truncate(0);

    float scale = float(this->numcolors-1);
    this->ctrlpts.append(SbVec3f(0, float(this->colormap[0]) / scale, 0));
    
    for (int i = 2; i < this->numcolors; i+=2) {
      // if the curve is very steep, we'll throw in an extra control point
      int dy = abs(this->colormap[i] - this->colormap[i-2]);
      if ((i % 32 == 0) || (dy > 16)) { 
          this->ctrlpts.append(SbVec3f(float(i) / scale, float(this->colormap[i]) / scale, 0));
        }
    }
    this->ctrlpts.append(SbVec3f(1, float(this->colormap[this->numcolors-1]) / scale, 0));
    this->curve->setControlPoints(this->ctrlpts.getArrayPtr(), this->ctrlpts.getLength());
    this->updateCurvePoints();
    this->needinterpol = FALSE;
  }
}

void
ColorCurve::setChangeCallBack(ColorCurve::ChangeCB * cb, void * userData)
{
  this->callBack = cb;
  this->callbackdata = userData;
}

void
ColorCurve::updateCurvePoints()
{
  SbVec3f cp = this->curve->getPoint(0.0f);
  if (cp[1] > 1.0f) cp[1] = 1.0f; // clamp
  if (cp[1] < 0.0f) cp[1] = 0.0f;

  // clamp to left border
  this->curvepts[0] = SbVec2f(0, cp[1]);

  for (int i = 1; i < this->numpts; i++) {
    float t = float(i) / float(this->numpts - 1);
    cp = this->curve->getPoint(t);
    const float prevx = this->curvepts[i-1][0];
    // ensures single valued function
    float px = (cp[0] < prevx) ? prevx : cp[0];
    float py = cp[1];
    // clamp
    if (py < 0.0f) py = 0.0f;
    if (py > 1.0f) py = 1.0f;
    this->curvepts[i] = SbVec2f(px, py);
  }
  // clamp to right border
  this->curvepts[this->numpts-1][0] = 1.0f;

  this->updateColorMap();
  if (this->callBack) {
    this->callBack(this->callbackdata);
  }
}

void 
ColorCurve::updateColorMap()
{
  for (int i = 0; i < this->numcolors; i++) {
    this->colormap[i] = this->eval(float(i) / float(this->numcolors-1));
  }
}

const uint8_t *
ColorCurve::getColorMap(void) const
{
  return this->colormap;
}

void 
ColorCurve::getColors(uint8_t * colors, int num) const
{
  if (num != this->numcolors) {
    for (int i = 0; i < num; i++) {
      colors[i] = this->eval(float(i) / float(this->numcolors-1));
    }
  } else {
    for (int i = 0; i < num; i++) {
      colors[i] = this->colormap[i];
    }
  }
}

void
ColorCurve::setColors(uint8_t * colors, int num)
{
  assert((num == this->numcolors) && "wrong number of colors");
  for (int i = 0; i < this->numcolors; i++) {
    this->colormap[i] = colors[i];
  }
  this->needinterpol = TRUE;
}

int
ColorCurve::eval(float x) const
{
  int i = 0;
  while((this->curvepts[++i][0] < x) && (i < this->numpts));

  const float x0 = this->curvepts[i-1][0];
  const float x1 = this->curvepts[i][0];

  const float y0 = this->curvepts[i-1][1];
  const float y1 = this->curvepts[i][1];

  const float dx = x1 - x0;

  float w0, w1;

  if (dx < 1e-6) { // too small for reliable floating point operations
    w0 = 0.5f;
    w1 = 0.5f;
  } else {
    w0 = (x1 - x) / dx;
    w1 = (x - x0) / dx;
  }
  const int y = int((w0 * y0 + w1 * y1) * float(this->numcolors-1) + 0.5f);
  assert((y <= this->numcolors-1) && (y >= 0) && "invalid y value");
  return y;
}

void
ColorCurve::notify() const
{
  if (this->callBack) this->callBack(this->callbackdata);
}
