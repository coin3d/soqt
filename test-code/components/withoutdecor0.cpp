/**************************************************************************\
 *
 *  This file is part of a set of demo programs for the SoQt library.
 *  Copyright (C) 1998-2003 by Systems in Motion.  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using this code with software that can not be combined with
 *  the GNU GPL, and for taking advantage of the additional benefits
 *  of our support services, please contact Systems in Motion about
 *  acquiring a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org> for more information.
 *
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no>.
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

