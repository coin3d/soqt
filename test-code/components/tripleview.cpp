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

/*
  This is just a simple test application to check that we can have
  SoQtComponent derived objects within other widgets.
*/

/***********************************************************************/

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoQtRenderArea.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <qgroupbox.h>
#include <qlayout.h>

/***********************************************************************/

// Timer callback function will rotate the scene according to the
// current time.
static void
timer_callback(void * data, SoSensor * sensor)
{
  static SbTime t = SbTime::getTimeOfDay().getValue();
  SbTime timediff = SbTime::getTimeOfDay() - t;

  SbRotation rotx(SbVec3f(1, 0, 0), 0.5 * timediff.getValue());
  SbRotation roty(SbVec3f(0, 1, 0), timediff.getValue());
  SbRotation rotz(SbVec3f(0, 0, 1), 1.5 * timediff.getValue());
  SoRotation * scenerotate = (SoRotation *)data;
  scenerotate->rotation.setValue(rotx * roty * rotz);
}

// Make a Qt renderarea as a child widget of viewparent, adding the
// scene under common and a camera with the given orientation.
void
add_view(QWidget * viewparent, SoGroup * common, SbRotation cameraorientation)
{
  SoSeparator * root = new SoSeparator;

  SoPerspectiveCamera * camera = new SoPerspectiveCamera;
  camera->orientation = cameraorientation;
  root->addChild(camera);
  
  root->addChild(common);
  
  SoQtRenderArea * area = new SoQtRenderArea(viewparent);
  area->setSceneGraph(root);
  camera->viewAll(root, area->getViewportRegion());
}

/***********************************************************************/

int
main(int argc, char ** argv)
{
  // Initialize system.

  QApplication app(argc, argv);
  QWidget * parent = new QWidget;
  app.setMainWidget(parent);
  SoQt::init(parent);

  parent->setMinimumSize(300, 200);


  // Set up the Qt widget layout data.

  QHBoxLayout * hlayout = new QHBoxLayout(parent);

  QGroupBox * view0 = new QGroupBox(parent);
  hlayout->addWidget(view0, 0.66);

  QVBoxLayout * vlayout = new QVBoxLayout();
  hlayout->addLayout(vlayout, 0.33);

  QGroupBox * view1 = new QGroupBox(parent);
  vlayout->addWidget(view1, 0.50);
  QGroupBox * view2 = new QGroupBox(parent);
  vlayout->addWidget(view2, 0.50);


  // Construct the common part of the scenegraph.

  SoGroup * commonroot = new SoGroup;
  SoDirectionalLight * light = new SoDirectionalLight;
  light->direction.setValue(-0.5, -0.5, -0.8);
  commonroot->addChild(light);

  SoMaterial * mat = new SoMaterial;
  mat->diffuseColor.setValue(1, 1, 0);
  commonroot->addChild(mat);

  SoRotation * scenerotate = new SoRotation;
  commonroot->addChild(scenerotate);

  SoCube * cube = new SoCube;
  commonroot->addChild(cube);

  mat = new SoMaterial;
  mat->diffuseColor.setValue(0, 0, 1);
  commonroot->addChild(mat);

  SoTranslation * trans = new SoTranslation;
  trans->translation.setValue(0, 0, 1);
  commonroot->addChild(trans);

  SoSphere * sphere = new SoSphere;
  sphere->radius = 0.5;
  commonroot->addChild(sphere);


  // Add the 3 renderareas.

  add_view(view0, commonroot, SbRotation(SbVec3f(0, 0, 1), 0));
  add_view(view1, commonroot, SbRotation(SbVec3f(0, 1, 0), M_PI / 2.0f));
  add_view(view2, commonroot, SbRotation(SbVec3f(1, 0, 0), -M_PI / 2.0f));


  // Set up a timer callback to do a simple animation.

  SoTimerSensor ts(timer_callback, scenerotate);
  ts.setInterval(0.02f); // max 50 fps
  ts.schedule();


  // Map window and start event loop.

  SoQt::show(parent);
  SoQt::mainLoop();

  return 0;
}
