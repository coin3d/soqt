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

