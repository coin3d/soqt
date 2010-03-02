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
  Demonstrates embedding of an SoQtRenderArea within a QScrollView.
*/

/***********************************************************************/

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoQtRenderArea.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSeparator.h>
#include <qapplication.h>
#include <qpainter.h>
#include <qscrollview.h>
#include <qpushbutton.h>


class MyScrollView : public QScrollView {
public:
  MyScrollView(QWidget * parent) : QScrollView(parent)
    {
      this->resizeContents(10000, 10000);
      this->enableClipper(TRUE);

      // Container widget for the SoQtRenderArea.

      QWidget * container = new QWidget(this);
      container->resize(1000, 1000);

      // Construct a simple scenegraph.

      SoSeparator * root = new SoSeparator;

      SoDirectionalLight * light = new SoDirectionalLight;
      light->direction.setValue(-0.5, -0.5, -0.8);
      root->addChild(light);

      SoPerspectiveCamera * camera = new SoPerspectiveCamera;
      camera->orientation = SbRotation(SbVec3f(0, 0, 1), 0);
      root->addChild(camera);

      SoCone * cone = new SoCone;
      root->addChild(cone);

      // Add the renderarea.

      renderarea = new SoQtRenderArea(container);
      renderarea->setSceneGraph(root);
      camera->viewAll(root, renderarea->getViewportRegion());

      this->addChild(container, 100, 100);
      this->showChild(container);
    }

protected:
  void drawContents(QPainter * p, int cx, int cy, int cw, int ch)
    {
      p->fillRect(cx, cy, cw, ch, QColor(40, 80, 0));
      // FIXME: should redraw only when necessary. 20001127 mortene.
      renderarea->scheduleRedraw();
    }

private:
  SoQtRenderArea * renderarea;
};

/***********************************************************************/

int
main(int argc, char ** argv)
{
  // Initialize Qt and SoQt.
  QApplication app(argc, argv);
  SoQt::init((QWidget *)NULL);

  // Set up scrollview window.
  MyScrollView * vp = new MyScrollView(NULL);
  vp->viewport()->setBackgroundMode(QWidget::NoBackground);

  // Map window.
  vp->show();
  // Set termination condition.
  QObject::connect(qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()));
  // Start event loop.
  SoQt::mainLoop();

  return 0;
}
