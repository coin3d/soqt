#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtViewer.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include "SoQtSuperViewer.h"
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSeparator.h>

int
main(int argc, char **argv)
{
  QWidget * svWindow = SoQt::init(argv[0]);
  //if (myWindow == NULL) exit(1);
  
  SoSeparator * root = new SoSeparator;

  SoQtSuperViewer * superViewer = new SoQtSuperViewer(svWindow);

  superViewer->setSceneGraph(root);
  superViewer->init(); 
  superViewer->viewAll();

  superViewer->show();  

  SoQt::show(svWindow);
  SoQt::mainLoop();

  return 0;
}
