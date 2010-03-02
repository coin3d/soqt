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

#include <Inventor/Qt/SoQt.h>
#include <qapplication.h>

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoCone.h>
#include <qwidget.h>

// Demonstrates that a widget built without decorations scales
// correctly, as we've had some problems with this previously.
int main(int argc, char ** argv)
{
  QWidget * window = SoQt::init(argc, argv, argv[0]);

  SoQtExaminerViewer * viewer = new SoQtExaminerViewer
    (window, "Examiner Viewer" ,TRUE,
     SoQtFullViewer::BUILD_NONE);

  viewer->setSceneGraph(new SoCone);

  viewer->show();
  SoQt::show(window);

  window->resize(500, 500);

  SoQt::mainLoop();

  delete viewer;
  return 0;
}
