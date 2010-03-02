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
  Demonstrates embedding of an SoQtExaminerViewer within a simple
  widget hierarchy.
*/

/***********************************************************************/

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoSeparator.h>
#include <qapplication.h>
#include <qsplitter.h>
#include <qmainwindow.h>
#include <qlistview.h>
#include <qgl.h>


class MyMainWindow : public QMainWindow {
public:
  MyMainWindow(void)
    {
      QSplitter * split = new QSplitter(this);

      QListView * listview = new QListView(split);
      QWidget * glw = new QWidget(split);

      // Construct a simple scenegraph.

      SoSeparator * root = new SoSeparator;

      SoCone * cone = new SoCone;
      root->addChild(cone);

      // Add the examinerviewer.

      SoQtExaminerViewer * examinerviewer = new SoQtExaminerViewer(glw);
      examinerviewer->setSceneGraph(root);

      split->resize(640, 480);
      this->resize(640, 480);
    }
};

/***********************************************************************/

int
main(int argc, char ** argv)
{
  // Initialize Qt and SoQt.

  // You should not create a QApplication instance if you want
  // to receive spaceball events.
  //  QApplication app(argc, argv);

  SoQt::init((QWidget *)NULL);

  // Set up scrollview window.
  MyMainWindow * vp = new MyMainWindow();

  // Map window.
  vp->show();
  // Set termination condition.
  QObject::connect(qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()));
  // Start event loop.
  SoQt::mainLoop();

  return 0;
}
