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

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoQtRenderArea.h>

#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoRotor.h>
#include <Inventor/nodes/SoArray.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSeparator.h>

/*
  This is a simple example, demonstrating proper behaviour for a
  SoQtRenderArea when built with the 'embed' flag set to TRUE.
*/

static SoSeparator * get_scene_graph(void)
{
  SoSeparator * root = new SoSeparator;

  SoGroup * group = new SoGroup;

  SoRotor * rotor = new SoRotor;
  rotor->rotation = SbRotation(SbVec3f(0.2, 0.5, 0.9), M_PI/4.0);
  group->addChild(rotor);

  SoCube * cube = new SoCube;
  group->addChild(cube);

  SoArray * array = new SoArray;
  array->origin = SoArray::CENTER;
  array->addChild(group);
  array->numElements1 = 2;
  array->numElements2 = 2;
  array->separation1 = SbVec3f(4, 0, 0);
  array->separation2 = SbVec3f(0, 4, 0);

  root->addChild(array);
  return root;
}

int main(int argc, char ** argv)
{
  QWidget * window = SoQt::init(argv[0]);

  SoSeparator * root = new SoSeparator;
  root->ref();
  SoPerspectiveCamera * camera;
  root->addChild(camera = new SoPerspectiveCamera);
  root->addChild(new SoDirectionalLight);
  SoSeparator * userroot = get_scene_graph();
  root->addChild(userroot);


  SoQtRenderArea * renderarea =
    new SoQtRenderArea(window, "Renderarea demonstration", FALSE);
  camera->viewAll( userroot, renderarea->getViewportRegion() );
  renderarea->setSceneGraph(root);
  renderarea->setBackgroundColor(SbColor(0.0f, 0.2f, 0.3f));
  renderarea->show();

  SoQt::show(window);
  SoQt::mainLoop();

  delete renderarea;
  root->unref();
  return 0;
}
