/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2004 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

#include <assert.h>

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoPickAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/actions/SoGetMatrixAction.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/SoPath.h>

#include <Inventor/Qt/nodes/SoGuiPane.h>
#include <Inventor/Qt/nodes/SoGuiTranslation.h>

// *************************************************************************

SO_NODE_SOURCE(SoGuiTranslation);

void
SoGuiTranslation::initClass(void)
{
  SO_NODE_INIT_CLASS(SoGuiTranslation, SoTransformation, "Transformation");
}

SoGuiTranslation::SoGuiTranslation(void)
{
  SO_NODE_CONSTRUCTOR(SoGuiTranslation);
  SO_NODE_ADD_FIELD(translation, (SbVec3f(0.0f, 0.0f, 0.0f)));
}

SoGuiTranslation::~SoGuiTranslation(void)
{
}

void
SoGuiTranslation::doAction(SoAction * action)
{
  // SoDebugError::postInfo("SoGuiTranslation::doAction", "invoked by %s", action->getTypeId().getName().getString());
  int i;
  SoGuiPane * pane = NULL;
  const SoFullPath * path = (const SoFullPath *) action->getCurPath();
  for ( i = path->getLength() - 1; (i >= 0) && (pane == NULL); i-- ) {
    SoNode * node = path->getNode(i);
    assert(node);
    if ( node->isOfType(SoGuiPane::getClassTypeId()) ) pane = (SoGuiPane *) node;
  }
  if ( pane == NULL ) {
    SoDebugError::postInfo("SoGuiTranslation::doAction", "SoGuiTranslation only works below an SoGuiPane node");
    return;
  }
  SoModelMatrixElement::translateBy(action->getState(), this,
                                    this->translation.getValue());

//  pane->moveBy(action->getState(), this->translation.getValue());
}

void
SoGuiTranslation::GLRender(SoGLRenderAction * action)
{
  this->doAction(action);
}

void
SoGuiTranslation::pick(SoPickAction * action)
{
  this->doAction(action);
}

void
SoGuiTranslation::rayPick(SoRayPickAction * action)
{
  this->doAction(action);
}

void
SoGuiTranslation::getMatrix(SoGetMatrixAction * action)
{
  SoDebugError::postInfo("SoGuiTranslation::getMatrix", "invoked");
  int i;
  SoGuiPane * pane = NULL;
  const SoFullPath * path = (const SoFullPath *) action->getCurPath();
  for ( i = path->getLength() - 1; (i >= 0) && (pane == NULL); i-- ) {
    SoNode * node = path->getNode(i);
    assert(node);
    if ( node->isOfType(SoGuiPane::getClassTypeId()) ) pane = (SoGuiPane *) node;
  }
  if ( pane == NULL ) {
    SoDebugError::postInfo("SoGuiTranslation::getMatrix", "SoGuiTranslation only works below an SoGuiPane node");
    return;
  }
  pane->applyMoveBy(action, this->translation.getValue());
}

