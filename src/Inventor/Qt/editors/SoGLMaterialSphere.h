/**************************************************************************\
 *
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

//  $Id$

#ifndef __SOGLMATERIALSPHERE_H__
#define __SOGLMATERIALSPHERE_H__

// FIXME: not in use yet. 19990620 mortene.

# include <qgl.h>
# include <qwidget.h>

class SoMaterial;

class SOQT_DLL_EXPORT SoGLMaterialSphere : public QGLWidget
{
  Q_OBJECT

public:
  SoGLMaterialSphere(QWidget * parent = NULL, const char * name = NULL);

  void setRepaint(bool whatever);

public slots:
  void setAmbient(float);
  void setDiffuse(float);
  void setSpecular(float);
  void setEmission(float);
  void setShininess(float);
  void setTransparency(float);
  void setMaterial(SoMaterial * mat);
  void repaintSphere();

protected:
  void paintGL();
  void resizeGL(int w, int h);
  void initializeGL();

private:
  void drawSphere();
  void drawBackground();
  void calculateSpherePoints(float * points, int max_points);

  SoMaterial * material;
  float ambientLight[4];
  float diffuseLight[4];
  float specularLight[4];
  bool doRepaint;
};

#endif // !__SOGLMATERIALSPHERE_H__
