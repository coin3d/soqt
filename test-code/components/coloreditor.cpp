#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoCube.h>

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoQtColorEditor.h>
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
  viewer->setSceneGraph(makescene());
  SoQtColorEditor * editor = new SoQtColorEditor;
  editor->attach(&(material->diffuseColor));
  editor->setCurrentSliders(SoQtColorEditor::RGB_HSV);
  viewer->show();
  editor->show();
  SoQt::show(w);
  SoQt::mainLoop();
  return 0;
}

