/*
 * Press mouse button in viewer canvas to trigger assert deep in Coin for
 * checking that debug symbols are available in the libraries.
 *
 * Jotted down 2002-01-11 by Lars J. Aas <larsa@sim.no>
 */

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>

#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoCallback.h>
#include <Inventor/nodes/SoSeparator.h>

#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>

#include <stdlib.h>
#include <stdio.h>

void
callback(void * closure, SoAction * action)
{
  if ( action->isOfType(SoHandleEventAction::getClassTypeId()) ) {
    SoHandleEventAction * heaction =
      (SoHandleEventAction *) action;
    if ( heaction->getEvent()->isOfType(SoMouseButtonEvent::getClassTypeId()) ) {
      SoSeparator * sep = (SoSeparator *) closure;
      sep->addChild(NULL); // trigger assert inside Coin
    }
  }
}

int
main(int argc, char ** argv)
{
  QWidget * win = SoQt::init("Debug Test");
  SoQtExaminerViewer * viewer = new SoQtExaminerViewer(win);
  viewer->show();
  SoQt::show(win);
  SoSeparator * sep = new SoSeparator;
  SoCallback * cb = new SoCallback;
  cb->setCallback(callback, sep);
  sep->addChild(cb);
  sep->addChild(new SoCube);
  viewer->setSceneGraph(sep);
  viewer->setViewing(FALSE);
  SoQt::mainLoop();
  viewer->hide();
  // delete viewer;
  return 0;
}

