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

/*
  This is just a simple test application to check that we can have
  SoQtComponent derived objects within other widgets.

  It also demonstrates having multiple views on a scene from multiple
  SoQtRenderArea instances.

  Note that this example doesn't work correctly with SoQt + TGS'
  Inventor for some reason. Looks like a TGS' Inventor bug to me. See
  also Bugzilla #20.

  mortene@sim.no
*/

/***********************************************************************/

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoQtRenderArea.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/SoDB.h>
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
#include <Inventor/actions/SoGLRenderAction.h>
#include <qapplication.h>
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

#ifndef __COIN__
  // IMPORTANT: make sure each GL context has a unique cache context
  // id.  this is needed for TGS/SGI Inventor. Coin handles this
  // automatically.
  static uint32_t contextcnt = 0;
  area->getGLRenderAction()->setCacheContext(contextcnt++);
#endif // !__COIN__

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
  SoRotation * scenerotate = new SoRotation;
  commonroot->addChild(scenerotate);

  if (argc == 2) {
    SoInput in;
    in.openFile(argv[1]);
    SoSeparator * fileroot = SoDB::readAll(&in);
    if (!fileroot) exit(1);
    commonroot->addChild(fileroot);
  }
  else {
    SoMaterial * mat = new SoMaterial;
    mat->diffuseColor.setValue(1, 1, 0);
    commonroot->addChild(mat);

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
  }

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
