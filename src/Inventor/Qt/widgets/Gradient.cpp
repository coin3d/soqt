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
#define PRIVATE(p) (p->pimpl)
#define PUBLIC(p) (p->pub)

#include <assert.h>
#include <qfile.h>
#include <qimage.h>
#include <Inventor/Qt/widgets/Gradient.h>

class GradientP {
public:
  GradientP(Gradient * publ);
  unsigned int getColorIndex(unsigned int i, SbBool left) const;
  Gradient * pub;
  QValueList<float> parameters;
  QValueList<QRgb> colors;
  Gradient::ChangeCB * callBack;
  void * callBackData;
};

GradientP::GradientP(Gradient * publ)
{
  PUBLIC(this) = publ;
}

unsigned int
GradientP::getColorIndex(unsigned int i, SbBool left) const
{
  unsigned int colidx;

  if (i==0 && left) { colidx = this->colors.size() - 1; } // wrap around
  // there are parameters times two minus one number of colors
  else { colidx = i * 2 - (left ? 1 : 0); }

  if (colidx == this->colors.size()) { colidx = 0; } // wrap around

  assert(colidx < this->colors.size() && "border violation");
  return colidx;
}

Gradient::Gradient(const QColor& color0, const QColor& color1)
{
  this->pimpl = new GradientP(this);
  PRIVATE(this)->callBack = NULL;
  
  // parameter values will be in the range [0 - 1]
  PRIVATE(this)->parameters.append(0.0f);
  PRIVATE(this)->parameters.append(1.0f);
  PRIVATE(this)->colors.append(color0.rgb());
  PRIVATE(this)->colors.append(color1.rgb());
}

Gradient::Gradient(const Gradient & grad)
{
  this->pimpl = new GradientP(this);
  this->operator=(grad);
}

Gradient::Gradient(const QString & filename)
{
  this->pimpl = new GradientP(this);
  PRIVATE(this)->callBack = NULL;
  this->load(filename);
}

Gradient::~Gradient()
{
}

Gradient &
Gradient::operator=(const Gradient & grad)
{
  // FIXME: copying of GradientP-data should happen in a method in
  // that class. 20031008 mortene.
  PRIVATE(this)->callBack = grad.pimpl->callBack;
  PRIVATE(this)->callBackData = grad.pimpl->callBackData;
  PRIVATE(this)->parameters = grad.pimpl->parameters;
  PRIVATE(this)->colors = grad.pimpl->colors;
  return *this;
}

SbBool Gradient::operator == (const Gradient & grad) const
{
  return (PRIVATE(this)->parameters == grad.pimpl->parameters) &&
         (PRIVATE(this)->colors == grad.pimpl->colors);
}

QRgb
Gradient::eval(float t) const
{
  assert(t >= 0.0f && t <= 1.0f && "t must be in the interval [0,1]");

  int i = 0;
  // find the interval to evaluate in
  while (PRIVATE(this)->parameters[++i] < t);

  int j = (i-1)*2;

  float t0 = PRIVATE(this)->parameters[i-1];
  float t1 = PRIVATE(this)->parameters[i];

  float dt = t1 - t0;

  // weights for linear interpolation
  float w0 = (t1 - t) / dt;
  float w1 = (t - t0) / dt;

  const QRgb color0 =  PRIVATE(this)->colors[j];
  const QRgb color1 = PRIVATE(this)->colors[j+1];

  // add 0.5 to get rounding
  int r = int(w0 * float(qRed(color0)) + w1 * float(qRed(color1)) + 0.5f);
  int g = int(w0 * float(qGreen(color0)) + w1 * float(qGreen(color1)) + 0.5f);
  int b = int(w0 * float(qBlue(color0)) + w1 * float(qBlue(color1)) + 0.5f);
  int a = int(w0 * float(qAlpha(color0)) + w1 * float(qAlpha(color1)) + 0.5f);

  return qRgba(r, g, b, a);
}

unsigned int
Gradient::numTicks(void) const
{
  return PRIVATE(this)->parameters.size();
}

float
Gradient::getParameter(unsigned int i) const
{
  return PRIVATE(this)->parameters[i];
}

void
Gradient::moveTick(unsigned int i, float t)
{
  if (PRIVATE(this)->parameters[i] != t) {
    PRIVATE(this)->parameters[i] = t;
    if (PRIVATE(this)->callBack) { PRIVATE(this)->callBack(*this, PRIVATE(this)->callBackData); }
  }
}

unsigned int
Gradient::insertTick(float t)
{
  // find position to insert before
  int i = 0;
  QValueList<float>::Iterator it = PRIVATE(this)->parameters.begin();
  QValueList<QRgb>::Iterator it2 = PRIVATE(this)->colors.begin();
  // it2 = it * 2 - 1, (+= operator wasnt available until Qt 3.1.0)
  while ((*it) < t) { i++; it++; it2++; it2++; }
  it2--;

  // we use the color of the gradient at this parameter value
  QRgb color = this->eval(t);
  PRIVATE(this)->parameters.insert(it, t);
  PRIVATE(this)->colors.insert(it2, 2, color);

  return i;

}

void
Gradient::removeTick(unsigned int i)
{
  QValueList<float>::Iterator it = PRIVATE(this)->parameters.begin();
  QValueList<QRgb>::Iterator it2 = PRIVATE(this)->colors.begin();
  // the += operator wasn't available until Qt 3.1.0. Just iterate
  // and use ++. pederb, 2003-09-22
  for (unsigned int j = 0; j < i; j++) { it++; it2++; it2++; }
  it2--;

  PRIVATE(this)->parameters.remove(it);
  it2 = PRIVATE(this)->colors.remove(it2);
  PRIVATE(this)->colors.remove(it2);

  if (PRIVATE(this)->callBack) { PRIVATE(this)->callBack(*this, PRIVATE(this)->callBackData); }
}

SbBool
Gradient::leftEqualsRight(unsigned int i) const
{
  i = PRIVATE(this)->getColorIndex(i, TRUE);
  unsigned int n = PRIVATE(this)->colors.size();
  return (PRIVATE(this)->colors[i] == PRIVATE(this)->colors[(i+1) % n]);
}

void
Gradient::setColor(unsigned int i, SbBool left, const QRgb & color)
{
  i = PRIVATE(this)->getColorIndex(i, left);
  PRIVATE(this)->colors[i] = color;

  if (PRIVATE(this)->callBack) { PRIVATE(this)->callBack(*this, PRIVATE(this)->callBackData); }
}

QRgb
Gradient::getColor(unsigned int i, SbBool left) const
{
  i = PRIVATE(this)->getColorIndex(i, left);
  return PRIVATE(this)->colors[i];
}

void
Gradient::setChangeCallback(Gradient::ChangeCB * callBack, void * userdata)
{
  PRIVATE(this)->callBack = callBack;
  PRIVATE(this)->callBackData = userdata;
}

void Gradient::getColorArray(QRgb * colorArray, int num) const
{
  for (int i = 0; i < num; i++) {
    float t = float(i) / float(num - 1);
    colorArray[i] = this->eval(t);
  }
}

QImage
Gradient::getImage(unsigned int width, unsigned int height, unsigned int depth) const
{
  QImage gradImage(width, height, depth);
  QRgb * colors = new QRgb[width];
  this->getColorArray(colors, width);

  for (unsigned int i = 0; i < width; i ++) {
    float alpha = float(qAlpha(colors[i])) / 255.0f;
    for (unsigned int j = 0; j < height; j++) {
      // produces a checkerboard pattern of black and white
      QRgb background = 0;
      if (((i & 0x8) == 0) ^ ((j & 0x8) == 0)) {
        background = 255;
      }
      int bg = int((1.0f - alpha) * float(background));
      int r = (int) (alpha * float(qRed(colors[i]) + bg));
      int g = (int) (alpha * float(qGreen(colors[i]) + bg));
      int b = (int) (alpha * float(qBlue(colors[i]) + bg));
      gradImage.setPixel(i, j, qRgb(r, g, b));
    }
  }
  delete [] colors;
  return gradImage;
}

void
Gradient::save(const QString & filename) const
{
  QFile outfile(filename);
  if (outfile.open(IO_WriteOnly)) {
    QTextStream stream(&outfile);

    stream << PRIVATE(this)->parameters.size() << " ";

    QValueList<float>::Iterator it = PRIVATE(this)->parameters.begin();
    for (; it != PRIVATE(this)->parameters.end(); it++) {
      stream << (*it) << " ";
    }

    stream << PRIVATE(this)->colors.size() << " ";

    QValueList<QRgb>::Iterator it2 = PRIVATE(this)->colors.begin();
    for (; it2 != PRIVATE(this)->colors.end(); it2++) {
      stream << (*it2) << " ";
    }
    outfile.close();
  }
}

void
Gradient::load(const QString & filename)
{
  PRIVATE(this)->colors.clear();
  PRIVATE(this)->parameters.clear();

  QFile infile(filename);
  if (infile.open(IO_ReadOnly)) {
    QTextStream stream(&infile);

    int i;

    int numParameters;
    stream >> numParameters;
    
    for (i = 0; i < numParameters; i++) {
      float t;
      stream >> t;
      PRIVATE(this)->parameters.append(t);
    }

    int numColors;
    stream >> numColors;

    for (i = 0; i < numColors; i++) {
      QRgb clr;
      stream >> clr;
      PRIVATE(this)->colors.append(clr);
    }
    infile.close();
  }
}

#undef PRIVATE
#undef PUBLIC
