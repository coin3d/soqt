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
#include <Inventor/Qt/common/SbGuiList.h>

class SbCubicSpline;

class ColorCurve {
public:
  enum CurveType { LINEAR, CONSTANT };
  ColorCurve(CurveType type = LINEAR, const int numcolors = 256);
  ~ColorCurve();

  void setColors(uint8_t * colors, int num);
  void getColors(uint8_t * colors, int num) const;

  int getNumColors(void) const;
  int getNumCtrlPoints(void) const;

  void setCtrlPoints(const SbGuiList<SbVec3f> & pts);
  const SbGuiList<SbVec3f> & getCtrlPoints(void) const;
  void resetCtrlPoints(void);

  void setColorMapping(int x, int y);
  const uint8_t * getColorMap(void) const;
  void interpolateColorMapping(void);

  typedef void ChangeCB(void * userdata);
  void setChangeCallBack(ColorCurve::ChangeCB * cb, void * userData);

  void notify(void) const;
  void fill(int value);
  
private:
  void updateColorMap(void);
  void updateCurvePoints(void);
  int eval(float x) const;
  
  CurveType type;

  int prevx;
  const int numcolors;
  const int numpts;
  SbBool needinterpol;
  
  SbVec2f * curvepts;
  uint8_t * colormap;

  SbCubicSpline * curve;
  SbGuiList<SbVec3f> ctrlpts;
  ColorCurve::ChangeCB * callBack;
  void * callbackdata;
};


#endif // COLORCURVE_H
