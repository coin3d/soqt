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

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoRotationXYZ.h>

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoQtColorEditor.h>
#include <Inventor/Qt/nodes/SoGuiColorEditor.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>

static SoMaterial * material;

SoSeparator *
makescene(void)
{
  SoSeparator * root = new SoSeparator;
  root->addChild(material = new SoMaterial);
  root->addChild(new SoCube);
  return root;
}

int
main(int argc, char ** argv)
{
  QWidget * w = SoQt::init(argc, argv, "SoQtColorEditor");
  SoQtExaminerViewer * viewer = new SoQtExaminerViewer(w);
  SoSeparator * root;
  viewer->setSceneGraph(root = makescene());
  viewer->show();

  // we want ColorEditor in scene
  SoSeparator * editorscene = new SoSeparator;
  SoTranslation * trans = new SoTranslation;
  trans->translation.setValue(SbVec3f(2.0f, 0.0f, 0.0f));
  SoRotationXYZ * rot = new SoRotationXYZ;
  SoMaterial * mat = new SoMaterial;
  mat->diffuseColor.setValue(0.8, 0.8, 0.8);
  rot->axis = SoRotationXYZ::Y;
  rot->angle = 0.5;
  editorscene->addChild(trans);
  editorscene->addChild(rot);
  editorscene->addChild(mat);
  SoGuiColorEditor * inscene = new SoGuiColorEditor;
  inscene->wysiwyg.setValue(TRUE);
  inscene->color.connectFrom(&(material->diffuseColor));
  inscene->color.getValue(); // update field
  material->diffuseColor.connectFrom(&(inscene->color));
  editorscene->addChild(inscene);
  root->insertChild(editorscene, 0);

#if 0
  SoQtColorEditor * editor = new SoQtColorEditor;
  editor->attach(&(material->diffuseColor));
  editor->show();
#endif

  SoQt::show(w);
  SoQt::mainLoop();
  return 0;
}
