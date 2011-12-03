/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
