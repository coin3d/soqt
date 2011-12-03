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
