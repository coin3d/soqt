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

#include <assert.h>
#include <qfile.h>
#include <qimage.h>
#include "Gradient.h"

Gradient::Gradient(const QColor& color0, const QColor& color1)
{
  // parameter values will be in the range [0 - 1]
  this->parameters.append(0.0f);
  this->parameters.append(1.0f);
  this->colors.append(color0.rgb());
  this->colors.append(color1.rgb());

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
  this->changeCB = grad.changeCB;
  this->parameters = grad.parameters;
  this->colors = grad.colors;
  return *this;
}

bool Gradient::operator == (const Gradient & grad) const
{
  return (this->parameters == grad.parameters) &&
         (this->colors == grad.colors);
}

QRgb Gradient::eval(float t) const
{
  assert(t >= 0.0f && t <= 1.0f && 
    "Gradient::eval(float t): t must be in the interval [0,1]");

  int i = 0;
  // find the interval to evaluate in
  while (this->parameters[++i] < t);

  float t0 = this->parameters[i-1];
  float t1 = this->parameters[i];

  float dt = t1 - t0;

  // weights for linear interpolation
  float w0 = (t1 - t) / dt;
  float w1 = (t - t0) / dt;

  int j = (i-1)*2;

  const QRgb color0 =  this->colors[j];
  const QRgb color1 = this->colors[j+1];

  int r = int ((w0 * float(qRed(color0)) + w1 * float(qRed(color1)) + 0.5f));
  int g = int ((w0 * float(qGreen(color0)) + w1 * float(qGreen(color1)) + 0.5f));
  int b = int ((w0 * float(qBlue(color0)) + w1 * float(qBlue(color1)) + 0.5f));
  int a = int ((w0 * float(qAlpha(color0)) + w1 * float(qAlpha(color1)) + 0.5f));

  return qRgba(r, g, b, a);
}

int Gradient::numTicks() const
{
  return this->parameters.size();
}

float Gradient::getParameter(int i) const
{
  return this->parameters[i];
}

void Gradient::moveTick(int i, float t)
{
  if (this->parameters[i] != t) {
    this->parameters[i] = t;
    if (this->changeCB) this->changeCB();
  }
}

int Gradient::insertTick(float t)
{
  // we use the color of the gradient at this parameter value
  QRgb color = this->eval(t);
  
  // find the interval to evaluate in
  int i = 0;
  QValueList<float>::Iterator it = this->parameters.begin();
  QValueList<QRgb>::Iterator it2 = this->colors.begin();
  while ((*it) < t) { i++; it++; it2++; it2++; }
  it2--;

  this->parameters.insert(it, t);
  this->colors.insert(it2, 2, color);

  return i;

}

void Gradient::removeTick(int i)
{
  QValueList<float>::Iterator it = this->parameters.begin();
  QValueList<QRgb>::Iterator it2 = this->colors.begin();
  // the += operator wasn't available until Qt 3.1.0. Just iterate
  // and use ++. pederb, 2003-09-22
  for (int j = 0; j < i; j++) { it++; it2++; it2++; }
  this->parameters.remove(it);
  it2 = this->colors.remove(--it2);
  this->colors.remove(it2);

  if (this->changeCB) this->changeCB();
}

bool Gradient::leftEqualsRight(int i) const
{
  int maxIndex = this->colors.size() - 1;
  int colorIndex = i * 2 - 1;

  if (colorIndex < 0) colorIndex = maxIndex;

  return (this->colors[colorIndex] == this->colors[(colorIndex+1) % maxIndex]);
}

void Gradient::swapLeftAndRight(int i)
{
  
}

void Gradient::setColor(int i, bool left, const QRgb color)
{
  int colorIndex = i * 2 - 1;

  if (!left) colorIndex++;

  int maxIndex = this->colors.size() - 1;

  if (colorIndex > maxIndex) colorIndex = 0;
  if (colorIndex < 0) colorIndex = maxIndex;

  this->colors[colorIndex] = color;

  if (this->changeCB) this->changeCB();
}

QRgb Gradient::getColor(int i, bool left) const
{
  int colorIndex = i * 2 - 1;

  if (!left) colorIndex++;

  int maxIndex = this->colors.size() - 1;
  
  if (colorIndex > maxIndex) colorIndex = 0;
  if (colorIndex < 0) colorIndex = maxIndex;

  return this->colors[colorIndex];
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

void Gradient::getColorArray(QRgb * colorArray, int num) const
{
  for (int i = 0; i < num; i++) {
    float t = float(i) / float(num - 1);
    colorArray[i] = this->eval(t);
  }
}

QImage Gradient::getImage(int width, int height, int depth) const
{
  QImage gradImage(width, height, depth);
  QRgb * colors = new QRgb[width];
  this->getColorArray(colors, width);

  for (int i = 0; i < width; i ++) {
    float alpha = float(qAlpha(colors[i])) / 255.0f;
    for (int j = 0; j < height; j++) {
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

void Gradient::save(const QString& filename)
{
  QFile outfile(filename);
  if (outfile.open(IO_WriteOnly)) {
    QTextStream stream(&outfile);

    stream << this->parameters.size() << " ";

    QValueList<float>::Iterator it = this->parameters.begin();
    for (; it != this->parameters.end(); it++) {
      stream << (*it) << " ";
    }

    stream << this->colors.size() << " ";

    QValueList<QRgb>::Iterator it2 = this->colors.begin();
    for (; it2 != this->colors.end(); it2++) {
      stream << (*it2) << " ";
    }
    outfile.close();
  }
}

void Gradient::load(const QString& filename)
{
  this->colors.clear();
  this->parameters.clear();

  QFile infile(filename);
  if (infile.open(IO_ReadOnly)) {
    QTextStream stream(&infile);

    int i;

    int numParameters;
    stream >> numParameters;
    
    for (i = 0; i < numParameters; i++) {
      float t;
      stream >> t;
      this->parameters.append(t);
    }

    int numColors;
    stream >> numColors;

    for (i = 0; i < numColors; i++) {
      QRgb clr;
      stream >> clr;
      this->colors.append(clr);
    }
    infile.close();
  }
}


