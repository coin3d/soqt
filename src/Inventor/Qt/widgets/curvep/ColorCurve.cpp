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
#include "SbCubicSpline.h" // FIXME: the SbCubic spline should perhaps be made available in Coin 20031016 frodo
#include "ColorCurve.h"

ColorCurve::ColorCurve(CurveType type)
: numpts(128), maxctrlpts(20)
{
  this->type = type;
  this->curve = new SbCubicSpline;
  this->curve->setBasisMatrix(SbCubicSpline::CATMULL_ROM);
  this->ctrlpts = NULL;
  this->callBack = NULL;
  this->prevx = 0;
  this->needinterpol = FALSE;
  this->resetCtrlPts();
  this->updateCurvePoints();
}

ColorCurve::~ColorCurve()
{
  delete this->curve;
  delete [] this->ctrlpts;
}

void
ColorCurve::resetCtrlPts()
{
  this->numctrlpts = 2;

  if (this->ctrlpts) { delete [] this->ctrlpts; }
  this->ctrlpts = new SbVec3f[this->numctrlpts];
  this->ctrlpts[0] = (this->type == ColorCurve::CONSTANT) ? SbVec3f(0.0, 255.0, 0.0) : SbVec3f(0.0, 0.0, 0.0);
  this->ctrlpts[1] = SbVec3f(255.0, 255.0, 0.0);
  this->curve->setControlPoints(this->ctrlpts, this->numctrlpts);
  this->needinterpol = FALSE;
}  


int
ColorCurve::getNumPoints() const
{
  return 256;
}

int 
ColorCurve::getNumCtrlPoints() const
{
  return this->numctrlpts;
}

void
ColorCurve::setControlPoints(const SbVec3f * pts, int num)
{
  this->numctrlpts = num;
  if (this->ctrlpts) {
    delete [] this->ctrlpts;
  }
  this->ctrlpts = new SbVec3f[this->numctrlpts];
  for (int i = 0; i < this->numctrlpts; i++) this->ctrlpts[i] = pts[i];

  this->curve->setControlPoints(this->ctrlpts, this->numctrlpts);
  this->updateCurvePoints();
}

const SbVec3f *
ColorCurve::getCtrlPoints() const
{
  return this->ctrlpts;
}

void
ColorCurve::fill(int value)
{
  assert((value >= 0) && (value <= 255) && "value != [0, 255]");
  for (int i = 0; i < 256; i++) {
    this->colormap[i] = value;
  }
  this->needinterpol = TRUE;
  if (this->callBack) this->callBack(this->callbackdata);
}

void
ColorCurve::setColorMapping(int x, int y)
{
  assert((x <= 255) && (x >= 0) && "x != [0, 255]");
  assert((y <= 255) && (y >= 0) && "y != [0, 255]");

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
    int i;
    delete [] this->ctrlpts;
    this->ctrlpts = new SbVec3f[this->maxctrlpts];
    
    this->numctrlpts = 0;
    this->ctrlpts[this->numctrlpts] = SbVec3f(0, this->colormap[0], 0);
    this->numctrlpts++;

    for (i = 1; i < 255; i++) {
      if ((i % 32 == 0)) { // insert control point at fixed intervals
        if (this->numctrlpts < this->maxctrlpts) {
          this->ctrlpts[this->numctrlpts++] = SbVec3f(i, this->colormap[i], 0);
        }
      }
    }
    this->ctrlpts[this->numctrlpts] = SbVec3f(255, this->colormap[255], 0);
    this->numctrlpts++;

    this->curve->setControlPoints(this->ctrlpts, this->numctrlpts);
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
  if (cp[1] > 255.0f) cp[1] = 255.0f;
  if (cp[0] < 0.0f) cp[0] = 0.0f;

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
    if (py > 255.0f) py = 255.0f;
    this->curvepts[i] = SbVec2f(px, py);
  }
  // clamp to right border
  this->curvepts[this->numpts-1][0] = 255.0f;// = SbVec2f(255.0f, py);

  this->updateColorMap();
  if (this->callBack) {
    this->callBack(this->callbackdata);
  }
}

void 
ColorCurve::updateColorMap()
{
  for (int x = 0; x < 256; x++) {
    this->colormap[x] = this->y(float(x));
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
  // there is no point in asking for more than
  // 256 colors, but if you really want, you can.
  float fact = (float)num / 256.0f;
  for (int i = 0; i < num; i++) {
    const int j = float(i) / fact;
    colors[i] = this->colormap[j];
  }
}

void
ColorCurve::setColors(uint8_t * colors, int num)
{
  float fact = (float)num / 256.0f;
  for (int i = 0; i < 256; i++) {
    const int j = float(i) * fact;
    this->colormap[i] = colors[j];
  }
  this->needinterpol = TRUE;
}

int
ColorCurve::y(float x) const
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
  const int y = int(w0 * y0 + w1 * y1 + 0.5f);
  assert((y <= 255) && (y >= 0) && "invalid y value");
  return y;
}

void
ColorCurve::notify() const
{
  if (this->callBack) this->callBack(this->callbackdata);
}