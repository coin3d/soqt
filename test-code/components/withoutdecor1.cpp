/**************************************************************************\
 *
 *  This file is part of a set of demo programs for the SoQt library.
 *  Copyright (C) 2000-2002 by Systems in Motion. All rights reserved.
 *
 *  This sourcecode can be redistributed and/or modified under the
 *  terms of the GNU General Public License version 2 as published by
 *  the Free Software Foundation. See the file COPYING at the root
 *  directory of the distribution for more details.
 *
 *  As a special exception, all sourcecode of the demo examples can be
 *  used for any purpose for licensees of the Coin Professional
 *  Edition License, without the restrictions of the GNU GPL. See our
 *  web pages for information about how to acquire a Professional Edition
 *  License.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  http://www.sim.no support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
\**************************************************************************/


#include <Inventor/Qt/SoQt.h>
#include <qapplication.h>

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoCone.h>
#include <qwidget.h>

// This makes sure that building a widget with BUILD_NONE, and then
// calling setDecoration( TRUE ) works. 
int main(int argc, char ** argv)
{
  QWidget * window = SoQt::init(argc, argv, argv[0]);
  
  SoQtExaminerViewer * viewer = new SoQtExaminerViewer
    (window, "Examiner Viewer" ,TRUE,
     SoQtFullViewer::BUILD_NONE);

  viewer->setSceneGraph(new SoCone);
  viewer->setDecoration( TRUE );
  viewer->show();
  SoQt::show(window);
  
  window->resize(500, 500);
  
  SoQt::mainLoop();
  
  delete viewer;
  return 0;
}

