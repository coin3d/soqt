#ifndef COLORCURVE_H
#define COLORCURVE_H

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