#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoQtRenderArea.h>

#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoRotor.h>
#include <Inventor/nodes/SoArray.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSeparator.h>

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
