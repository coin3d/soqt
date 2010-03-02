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
