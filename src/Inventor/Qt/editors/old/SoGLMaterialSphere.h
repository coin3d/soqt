/**************************************************************************\
 *
 *  This file is part of the Coin family of 3D visualization libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and / or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.  See the
 *  file LICENSE.GPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you desire to use this library in software that is incompatible
 *  with the GNU GPL, and / or you would like to take advantage of the
 *  additional benefits with regard to our support services, please
 *  contact Systems in Motion about acquiring a Coin Professional
 *  Edition License.  See <URL:http://www.coin3d.org> for more
 *  information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#ifndef SOQT_GLMATERIALSPHERE_H
#define SOQT_GLMATERIALSPHERE_H

// FIXME: not in use yet. 19990620 mortene.

# include <qgl.h>
# include <qwidget.h>

class SoMaterial;

class SoGLMaterialSphere : public QGLWidget
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

#endif // ! SOQT_GLMATERIALSPHERE_H
