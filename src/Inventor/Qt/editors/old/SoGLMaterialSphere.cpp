/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) by Kongsberg Oil & Gas Technologies.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg Oil & Gas Technologies
 *  about acquiring a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg Oil & Gas Technologies, Bygdoy Alle 5, 0257 Oslo, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

// FIXME: not in use yet. 19990620 mortene.

#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>

#include <GL/glaux.h>

#include <Inventor/SbColor.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/fields/SoMFColor.h>

#include <soqtdefs.h>
#include <Inventor/Qt/editors/SoGLMaterialSphere.h>


#define NUM_POINTS 10000
#define BG_COLOR 0.5f, 0.5f, 0.5f, 0.0f
#define BG_COLOR2 0.4f, 0.4f, 0.4f, 1.0f

#define FLAT_SHADING


#ifndef _GCC_
# define true TRUE
# define false FALSE
#endif

#ifdef WIN32
#define random() rand()
#pragma warning(once: 4305)
#endif

//
// first some data for a Icosahedron (sphere with 20 faces)
//
#define X .525731112119133606
#define Z .850650808352039932

static float vdata[12][3] =
{
  {-X, 0, Z}, {X, 0, Z}, {-X, 0, -Z}, {X, 0, -Z},
  {0, Z, X}, {0, Z, -X}, {0, -Z, X}, {0, -Z, -X},
  {Z, X, 0}, {-Z, X, 0}, {Z, -X, 0}, {-Z, -X, 0}
};

static int tindices[20][3] = {
  {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},
  {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},
  {7,10,3,}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6},
  {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11}};

//
// normalize a vector
//
void normalize(float *v)
{
  float d = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
  if (d == 0.0f) return;
  d = 1.0f / d;
  v[0] *= d;
  v[1] *= d;
  v[2] *= d;
}

//
// the average of three vectors
//
void average_vector(float *v, float *v1, float *v2, float *v3)
{
  for (int i = 0; i < 3; i++)
    v[i] = v1[i] + v2[i] + v3[i];
  normalize(v);
}

//
// draws a triangle using OpenGL. Assumes glBegin(GL_TRIANGLES)
// has been called.
//
void drawtriangle(float *v1, float *v2, float *v3)
{
#if defined(FLATSHADING)
  float v[3];
  average_vector(v, v1, v2, v3);
  glNormal3fv(v);
  glVertex3fv(v1);
  glVertex3fv(v2);
  glVertex3fv(v3);
#else
  glNormal3fv(v1); glVertex3fv(v1);
  glNormal3fv(v2); glVertex3fv(v2);
  glNormal3fv(v3); glVertex3fv(v3);
#endif
}

//
// subdivide this triangle into smaller triangles until depth = 0
//
void subdivide(float *v1, float *v2, float *v3, int depth)
{
  float v12[3], v23[3], v31[3];
  int i;

  if (depth == 0) {
    drawtriangle(v1, v2, v3);
    return; // end recursion
  }
  for (i = 0; i < 3; i++) {
    v12[i] = v1[i] + v2[i];
    v23[i] = v2[i] + v3[i];
    v31[i] = v3[i] + v1[i];
  }
  normalize(v12);
  normalize(v23);
  normalize(v31);

  // continue recursion
  subdivide(v1, v12, v31, depth-1);
  subdivide(v2, v23, v12, depth-1);
  subdivide(v3, v31, v23, depth-1);
  subdivide(v12, v23, v31, depth-1);
}

//
// draws a sphere with resolution (number of subdivisions) depth.
//
void draw_sphere(int depth)
{
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < 20; i++) {
    subdivide(&vdata[tindices[i][0]][0],
              &vdata[tindices[i][1]][0],
              &vdata[tindices[i][2]][0], depth);
  }
  glEnd();
}


SoGLMaterialSphere::SoGLMaterialSphere(QWidget *parent, const char *name)
: QGLWidget(parent, name)
{
  material = NULL;
  doRepaint = true;
  makeCurrent();
  QGLFormat format;
  format.setRgba(TRUE);
  format.setDepth(TRUE);
  this->setFormat(format);
  initializeGL();
}

void SoGLMaterialSphere::paintGL()
{
  glClearColor(BG_COLOR);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  drawBackground();
  drawSphere();
}

void SoGLMaterialSphere::resizeGL(int w, int h)
{
  printf("resizegl: %d %d\n", w, h);
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (w <= h)
    glOrtho(-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
            1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
  else
    glOrtho(-1.5*(GLfloat)w/(GLfloat)h,
            1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  initializeGL();
  paintGL();
}


void SoGLMaterialSphere::initializeGL()
{
  printf("initGL\n");
#define SPOT_LIGHT
#ifdef SPOT_LIGHT
  static float light0_pos[4] = { -1.0, 1.5, 1.5, 0.0 };
  static float light1_pos[4] = { 1.0, 1.5, 1.5, 0.0 };
#else
  static float light0_pos[4] = { -2.0, 0.5, 1.5, 1.0 };
  static float light1_pos[4] = { 2.0, 0.5, 1.5, 1.0 };
#endif
  static float specular[] = { 1.0, 1.0, 1.0, 1.0 };
  static float spotDir0[] = { 0.9, -1.5, -1.5 , 1.0 };
  static float spotDir1[] = { -0.9, -1.5, -1.5 , 1.0 };

//  glColor3f(0.0, 0.0, 0.7);
//  glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, &0.5);
//  glLightfv(GL_LIGHT1, GL_AMBIENT, &0.0);
//  glEnable(GL_LIGHT1);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_BLEND);

  glDepthFunc(GL_LEQUAL);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CW);

  glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
  glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);

  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

#ifdef SPOT_LIGHT
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10.0f);
  glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 100.0f);
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10.0f);
  glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 100.0f);

  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir0);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir1);
#endif


  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
}

void SoGLMaterialSphere::drawBackground()
{

  glColor4f(BG_COLOR2);
  glDisable(GL_LIGHTING);
  glBegin(GL_QUADS);
        glVertex3f(-1.5,  1.5, -1.0);
        glVertex3f(0.0,  1.5, -1.0);
        glVertex3f(0.0,  0.0, -1.0);
        glVertex3f(-1.5,  0.0, -1.0);
        glVertex3f(0.0,  0.0, -1.0);
        glVertex3f(1.5,  0.0, -1.0);
        glVertex3f(1.5, -1.5, -1.0);
        glVertex3f(0.0, -1.5, -1.0);
  glEnd();
  glEnable(GL_LIGHTING);
}

void SoGLMaterialSphere::drawSphere()
{
#if 0
  float *point;
  point = new float[3 * NUM_POINTS];
  calculateSpherePoints(point, NUM_POINTS);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBegin(GL_POINTS);
        for (int i = 0; i < NUM_POINTS; i++)
                glVertex3f(point[i*3],point[i*3+1],point[i*3+2]);
  glEnd();
  delete [] point;
#else
  glLoadIdentity();
  glTranslatef(0,0,-5);
  draw_sphere(2);
  glFlush();
#endif
}

void SoGLMaterialSphere::calculateSpherePoints(float *points, int max_points)
{
  float theta, angle2;
  int i, pos;
  /*
   * Generate random point on the surface of a sphere
   */
  for (i = 0, pos = 0;i < max_points; i++, pos+=3)
  {
    theta = acos(1.0 - 2.0*(float)random()/(float)LONG_MAX);
    angle2 = 2.0*M_PI*(float)random()/(float)LONG_MAX;
    points[pos]   = sin(theta)*cos(angle2);
    points[pos+1] = sin(theta)*sin(angle2);
    points[pos+2] = cos(theta);
  }
}

#if 1
#define CopyColor(color)                                                \
        color##Light[0] = material->color##Color.getValues(0)[0].getValue()[0];                 \
        color##Light[1] = material->color##Color.getValues(0)[0].getValue()[1];                 \
        color##Light[2] = material->color##Color.getValues(0)[0].getValue()[2];                 \
        color##Light[3] = material->transparency.getValues(0)[0];
#else
#define CopyColor(color)
#endif

void SoGLMaterialSphere::setAmbient(float val)
{
  assert(material);
  printf("setAmbient(%f)\n", val);
//  memcpy(ambientLight, material->ambientColor.values, 3 * sizeof(float));
//  ambientLight[0] = material->ambientColor;


  CopyColor(ambient);

  fprintf(stderr, "ambientLight = [%f,%f,%f,%f]\n", ambientLight[0],ambientLight[1],ambientLight[2],ambientLight[3]);
  ambientLight[0] *= val;
  ambientLight[1] *= val;
  ambientLight[2] *= val;
//  ambientLight[3] *= val;

//  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
 // glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambientLight);

  if (doRepaint) repaint(false);
}

void SoGLMaterialSphere::setDiffuse(float val)
{
  assert(material);
//  memcpy(diffuseLight, material->diffuseColor.values, 3 * sizeof(float));
  CopyColor(diffuse);
  diffuseLight[0] *= val;
  diffuseLight[1] *= val;
  diffuseLight[2] *= val;
  printf("diffuseLight[] = %f, %f, %f, %f\n", diffuseLight[0], diffuseLight[1],
        diffuseLight[2], diffuseLight[3]);

//  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
//  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseLight);
  if (doRepaint) repaint(false);
}

void SoGLMaterialSphere::setSpecular(float val)
{

  printf("setSpecular(%f)\n", val);
  assert(material);
//  memcpy(specularLight, material->specularColor.values, 3 * sizeof(float));
  CopyColor(specular);
  specularLight[0] *= val;
  specularLight[1] *= val;
  specularLight[2] *= val;

//  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
//  glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);

  glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);
  if (doRepaint) repaint(false);
}

void SoGLMaterialSphere::setEmission(float val)
{
  /* */
  printf("setEmission(%f)\n", val);
  assert(material);
  float emissiveLight[4];
//  memcpy(emission, material->emissiveColor.values, 3 * sizeof(float));
  CopyColor(emissive);
  emissiveLight[0] *= val;
  emissiveLight[1] *= val;
  emissiveLight[2] *= val;
  glMaterialfv(GL_FRONT, GL_EMISSION, emissiveLight);
  if (doRepaint) repaint(false);
}

void SoGLMaterialSphere::setShininess(float val)
{
  printf("setShininess %f (%f)\n", val, (1.0f - val) * 128.0f);
  glMaterialf(GL_FRONT, GL_SHININESS, (1.0f - val) * 128.0f);
  if (doRepaint) repaint(false);
}

void SoGLMaterialSphere::setTransparency(float val)
{
  printf("setTransparency(%f)\n", val);
  assert(material);

  material->transparency = /*.setValue*/ (1.0f - val);

  setDiffuse(1.0f);

//  repaint(false);
}

void SoGLMaterialSphere::setMaterial(SoMaterial *mat)
{
  material = mat;
  if (doRepaint) repaint(false);
}

void SoGLMaterialSphere::repaintSphere()
{
  repaint(false);
}

void SoGLMaterialSphere::setRepaint(bool whatever)
{
  doRepaint = whatever;
}
