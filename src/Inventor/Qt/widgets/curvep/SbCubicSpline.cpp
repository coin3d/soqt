/**************************************************************************\
 *
 *  This file is part of the SmallChange extension library for Coin.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.  See the
 *  file LICENSE.GPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you desire to use SmallChange with software that is incompatible
 *  licensewise with the GPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#include "SbCubicSpline.h"

SbCubicSpline::SbCubicSpline(const int approxcount)
  : needinit(TRUE),
    loop(FALSE),
    approxcount(approxcount),    
    currsegment(-1)
{
  this->setBasisMatrix(B_SPLINE);
}

SbCubicSpline::~SbCubicSpline()
{
}

void 
SbCubicSpline::setBasisMatrix(const Type type)
{
  switch(type) {
  case CATMULL_ROM:
    this->setBasisMatrix(SbMatrix(-1.0f/2.0f, 3.0f/2.0f, -3.0f/2.0f, 1.0f/2.0f,
                                  2.0f/2.0f, -5.0f/2.0f, 4.0f/2.0f, -1.0f/2.0f,
                                  -1.0f/2.0f, 0.0f, 1.0f/2.0f, 0.0f,
                                  0.0f, 2.0f/2.0f, 0.0f, 0.0f));
    break;
  case B_SPLINE:
    this->setBasisMatrix(SbMatrix(-1.0f/6.0f, 3.0f/6.0f, -3.0f/6.0f, 1.0f/6.0f,
                                  3.0f/6.0f, -6.0f/6.0f, 3.0f/6.0f, 0.0f,
                                  -3.0f/6.0f, 0.0f, 3.0f/6.0f, 0.0f,
                                  1.0f/6.0f, 4.0f/6.0f, 1.0f/6.0f, 0.0f));
    break;
  case BEZIER:
    this->setBasisMatrix(SbMatrix(-1.0f, 3.0f, -3.0f, 1.0f,
                                  3.0f, -6.0f, 3.0f, 0.0f,
                                  -3.0f, 3.0f, 0.0f, 0.0f,
                                  1.0f, 0.0f, 0.0f, 0.0f));
    break;
  }
}

void 
SbCubicSpline::setBasisMatrix(const SbMatrix & m)
{
  if (m != this->basismatrix) {
    this->basismatrix = m;
    this->needinit = TRUE;
  }
}

const SbMatrix & 
SbCubicSpline::getBasisMatrix(void) const
{
  return this->basismatrix;
}

void 
SbCubicSpline::setLoop(const SbBool loop)
{
  if (loop != this->loop) {
    this->loop = loop;
    this->needinit = TRUE;
  }
}

void 
SbCubicSpline::setControlPoints(const SbVec3f * pts, const int num)
{
  this->ctrlpts.truncate(0);
  for (int i = 0; i < num; i++) {
    this->ctrlpts.append(SbVec4f(pts[i][0], pts[i][1], pts[i][2], 1.0f));
  }
  this->needinit = TRUE;
}

void 
SbCubicSpline::setControlPoints(const SbVec4f * pts, const int num)
{
  this->ctrlpts.truncate(0);
  for (int i = 0; i < num; i++) {
    this->ctrlpts.append(pts[i]);
  }
  this->needinit = TRUE;
}

SbVec3f 
SbCubicSpline::getPoint(const float t)
{
  float segt;
  this->getSegdata(t, segt); 
  return this->getPoint(this->currmatrix, segt);
}

SbVec3f 
SbCubicSpline::getTangent(const float t)
{
  float segt;
  this->getSegdata(t, segt); 
  return this->getTangent(this->currmatrix, segt);
}

float 
SbCubicSpline::getSegmentLength(const int idx)
{
  return this->seglens[idx];
}

int 
SbCubicSpline::getSegdata(const float t, float & segt)
{
  if (this->needinit) this->initialize();
  int seg = this->getSegnum(t);
  if (seg != this->currsegment) {
    this->initMatrix(seg, this->currmatrix);
    this->currsegment = seg;
  }
  if (this->loop) {
    segt = float(fmod((double)t, 1.0)) - this->segstarttimes[seg];
  }
  else {
    segt = SbClamp(t, 0.0f, 1.0f) - this->segstarttimes[seg];
  }
  segt /= this->segdurations[seg];
  return seg;
}

void
SbCubicSpline::initialize(void)
{
  this->currsegment = -1;
  int i, n = this->ctrlpts.getLength();

  if (!this->loop) n--;
  
  // calculate an approximation of the length of the curve
  this->seglens.truncate(0);
  float len;
  float totallen = 0.0;

  for (i = 0; i < n; i++) {
    SbMatrix m;
    this->initMatrix(i, m);
    SbVec3f prev = this->getPoint(m, 0.0f);
    len = 0.0;
    for (int j = 1; j < this->approxcount; j++) {
      SbVec3f p = this->getPoint(m, float(j) / float(this->approxcount));
      len += (float) (p-prev).length();
      prev = p;
    }
    this->seglens.append(len);
    totallen += len;
  }

  this->segstarttimes.truncate(0);
  this->segdurations.truncate(0);

  float acctime = 0.0;
  this->segstarttimes.append(acctime);
    
  for (i = 0; i < n; i++) {
    len = this->seglens[i];
    float time = len / totallen;
    this->segdurations.append(time);
    acctime += time;
    this->segstarttimes.append(acctime);

  }
  this->needinit = FALSE;
#if 0
  myfprintf(stdout,
          "#Inventor V2.1 ascii\n"
          "Separator {\n"
          "Coordinate3 {\n"
          "point [\n");
          

  for (int i = 0; i < 400; i++) {
            
    SbVec3f p = this->getPoint(float(i)/float(400));
    myfprintf(stdout, "%g %g %g,\n", p[0], p[1], p[2]); 
    myfprintf(stderr,"currseg: %d\n", this->currsegment);
  }
  myfprintf(stdout,"]\n}\nPointSet { numPoints 400 }\n}\n");
  fflush(stdout);
#endif
}

SbVec3f 
SbCubicSpline::getPoint(const SbMatrix & m, const float t)
{
#if 0
  float t2, t3;
  t2 = t*t; t3 = t2*t;
  return 
    SbVec3f(m[0][0] * t3 + m[1][0] * t2 + m[2][0] * t + m[3][0],
            m[0][1] * t3 + m[1][1] * t2 + m[2][1] * t + m[3][1],
            m[0][2] * t3 + m[1][2] * t2 + m[2][2] * t + m[3][2]);

#else
  double t1 = (double) t;
  double t2 = t*t;
  double t3 = t2*t;

  return 
    SbVec3f(double(m[0][0]) * t3 + double(m[1][0]) * t2 + double(m[2][0]) * t + double(m[3][0]),
            double(m[0][1]) * t3 + double(m[1][1]) * t2 + double(m[2][1]) * t + double(m[3][1]),
            double(m[0][2]) * t3 + double(m[1][2]) * t2 + double(m[2][2]) * t + double(m[3][2]));
  
#endif
}

SbVec3f
SbCubicSpline::getTangent(const SbMatrix &m, const float t)
{
  float t2;
  t2 = t*t;
  SbVec3f vec(3.0f * m[0][0] * t2 + 2.0f * m[1][0] * t + m[2][0],
              3.0f * m[0][1] * t2 + 2.0f * m[1][1] * t + m[2][1],
              3.0f * m[0][2] * t2 + 2.0f * m[1][2] * t + m[2][2]);
  vec.normalize();
  return vec;
}

void 
SbCubicSpline::initMatrix(const int q, SbMatrix & m)
{
  int pnr[4], i;
  pnr[0] = this->clampSegnum(q-1);
  pnr[1] = this->clampSegnum(q-0);
  pnr[2] = this->clampSegnum(q+1);
  pnr[3] = this->clampSegnum(q+2);
  
  for(i = 0; i < 4; i++) {
    m[i][0] = this->ctrlpts[pnr[i]][0];
    m[i][1] = this->ctrlpts[pnr[i]][1];
    m[i][2] = this->ctrlpts[pnr[i]][2];
    m[i][3] = this->ctrlpts[pnr[i]][3]; 
  }
  m.multLeft(this->basismatrix);
}

int 
SbCubicSpline::getSegmentInfo(const float t, float & segt) const
{
  if (t > 1.0f) {
    assert(0);
  }
  int segnum = this->getSegnum(t);
  segt = t - this->segstarttimes[segnum];
  segt /= this->segdurations[segnum];
  return segnum;
}

int 
SbCubicSpline::getSegnum(const float time) const
{
  int i = this->currsegment;
  if (i >= 0 && time >= this->segstarttimes[i] && 
      time <= this->segstarttimes[i] + this->segdurations[i])
    return i;

  int n = this->segstarttimes.getLength();
  if (!this->loop) n--;
  // do binary search
  int currlen = n / 2;
  i = currlen;
  while (currlen >= 4) {
    currlen >>= 1;
    if (this->segstarttimes[i] == time) return i;
    else if (time < this->segstarttimes[i]) {
      i -= currlen;
    }
    else {
      i += currlen;
    }
    assert(i >= 0 && i < n);
  }
  // do linear search for the last bit
  i -= currlen;
  for (; i < n; i++) {
    if (this->segstarttimes[i] > time) return i-1;
  }
  return n-1;
}

int 
SbCubicSpline::clampSegnum(const int q) const
{
  int ret = q;
  int n = this->ctrlpts.getLength();
  if (this->loop) {
    while (ret < 0) ret += n;
    ret %= n;
  }
  else {
    //    n--;
    if (ret < 0) ret = 0;
    if (ret >= n) ret = n-1;
  }
  return ret;
}
