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
