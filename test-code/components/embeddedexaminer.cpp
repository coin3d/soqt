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
  QApplication app(argc, argv);
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
