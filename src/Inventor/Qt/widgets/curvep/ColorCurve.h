#ifndef COLORCURVE_H
#define COLORCURVE_H

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

#include <Inventor/SbLinear.h>

class SbCubicSpline;

class ColorCurve {
public:
  enum CurveType { LINEAR, CONSTANT };

  ColorCurve(CurveType type = LINEAR);
  ~ColorCurve();
  

  void getColors(uint8_t * colors, int num) const;
  void setColors(uint8_t * colors, int num);

  int getNumPoints(void) const;
  int getNumCtrlPoints(void) const;
  void setControlPoints(const SbVec3f * pts, int num);
  const SbVec3f * getCtrlPoints(void) const;
  void resetCtrlPts(void);

  const uint8_t * getColorMap(void) const;
  void setColorMapping(int x, int y);
  void interpolateColorMapping(void);
  void updateColorMap(void);

  typedef void ChangeCB(void * userdata);
  void setChangeCallBack(ColorCurve::ChangeCB * cb, void * userData);

  void notify(void) const;
  void fill(int value);
  
private:
  void updateCurvePoints(void);
  int y(float x) const;
  
  CurveType type;

  const int numpts;
  const int maxctrlpts;

  int numctrlpts;
  int prevx;
  SbBool needinterpol;
  
  SbVec2f curvepts[128];
  uint8_t colormap[256];
  SbVec3f * ctrlpts;
  SbCubicSpline * curve;
  ColorCurve::ChangeCB * callBack;
  void * callbackdata;
};


#endif // COLORCURVE_H