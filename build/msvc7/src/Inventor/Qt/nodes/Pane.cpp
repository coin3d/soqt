/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
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
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <Inventor/SbLinear.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/bundles/SoMaterialBundle.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/actions/SoGetMatrixAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/misc/SoChildList.h>

#include <Inventor/Qt/common/gl.h>

#include <Inventor/Qt/nodes/SoGuiPane.h>

#define ZSCALE (1.0f)

// *************************************************************************

// FIXME: can't cache model matrix like this - use in multiple scene
// graphs doesn't work then...

class Pane {
public:
  SbMatrix modelmatrix;
  SbVec3f position;
  SbVec2f raypickpos;

};

// *************************************************************************

#define PRIVATE(obj) ((Pane *) obj->internals)

SO_NODE_SOURCE(SoGuiPane);

void
SoGuiPane::initClass(void)
{
  SO_NODE_INIT_CLASS(SoGuiPane, SoSeparator, "Separator");
}

SoGuiPane::SoGuiPane(void)
{
  this->internals = (void *) new Pane;
  SO_NODE_CONSTRUCTOR(SoGuiPane);
  SO_NODE_ADD_FIELD(worldSize, (SbVec3f(1.0f, 1.0f, 0.0f)));
  SO_NODE_ADD_FIELD(objectSize, (SbVec3f(100.0f, 100.0f, 0.0f)));
}

SoGuiPane::~SoGuiPane(void)
{
  Pane * obj = PRIVATE(this);
  delete obj;
  this->internals = NULL;
}

void
SoGuiPane::doAction(SoAction * action)
{
  SoState * state = action->getState();

  state->push();

  if ( state->isElementEnabled(SoModelMatrixElement::getClassStackIndex()) ) {
    SbVec3f world = this->worldSize.getValue();
    SbVec3f object = this->objectSize.getValue();
    SbVec3f scalefactor(world[0] / object[0], world[1] / object[1], ZSCALE);
    SoModelMatrixElement::scaleBy(state, this, scalefactor);
    PRIVATE(this)->modelmatrix = SoModelMatrixElement::get(state);
  }

  SbBool backface = FALSE;
  if ( state->isElementEnabled(SoViewVolumeElement::getClassStackIndex()) ) {
    SbVec3f normal(0.0f, 0.0f, 1.0f);
    PRIVATE(this)->modelmatrix.multDirMatrix(normal, normal);
    normal.normalize();
    SbVec3f campos = SoViewVolumeElement::get(state).getProjectionPoint();
    SbVec3f center = (SbVec3f(0.0f, 0.0f, 0.0f) + this->objectSize.getValue()) / 2.0f;
    PRIVATE(this)->modelmatrix.multVecMatrix(center, center);
    SbVec3f camdir = center - campos;
    camdir.normalize();
    backface = (normal.dot(camdir) >= 0.0f) ? TRUE : FALSE;
  }

  if ( action->isOfType(SoHandleEventAction::getClassTypeId()) ) {
    if ( backface ) {
      // we don't react to events when facing away
      goto culled;
    }
  }

  if ( action->isOfType(SoRayPickAction::getClassTypeId()) ) {
    SoRayPickAction * rpaction = (SoRayPickAction *) action;
    rpaction->setObjectSpace();

    SbPlane plane(SbVec3f(0.0f, 0.0f, 1.0f), 0.0f);
    SbLine line(rpaction->getLine());
    // find intersection with SbPlane
    SbVec3f point;
    PRIVATE(this)->raypickpos.setValue(-1.0f, -1.0f);
    if ( plane.intersect(line, point) ) {
      SbVec3f object = this->objectSize.getValue();
      SbVec2f pos(point[0], point[1]);
      if ( pos[0] < 0.0f || pos[1] < 0.0f || pos[0] > object[0] || pos[1] > object[1] ) {
        goto culled;
      } else {
        PRIVATE(this)->raypickpos = pos;
      }
    }
    else goto culled;
  }
  inherited::doAction(action);
culled:
  state->pop();
}

void
SoGuiPane::GLRenderBelowPath(SoGLRenderAction * action)
{
  SoState * state = action->getState();
  state->push();

  SbVec3f world = this->worldSize.getValue();
  SbVec3f object = this->objectSize.getValue();

  // adjust scale for new object space
  SbVec3f scalefactor(world[0] / object[0], world[1] / object[1], ZSCALE);
  SoModelMatrixElement::scaleBy(state, this, scalefactor);

  // store current model matrix
  PRIVATE(this)->modelmatrix = SoModelMatrixElement::get(state);
  PRIVATE(this)->position = SbVec3f(0.0f, 0.0f, 0.0f);


  SbVec3f normal(0.0f, 0.0f, 1.0f);
  PRIVATE(this)->modelmatrix.multDirMatrix(normal, normal);
  normal.normalize();

  SbVec3f campos = SoViewVolumeElement::get(state).getProjectionPoint();
  SbVec3f center = (SbVec3f(0.0f, 0.0f, 0.0f) + this->objectSize.getValue()) / 2.0f;
  PRIVATE(this)->modelmatrix.multVecMatrix(center, center);

  SbVec3f camdir = SoViewVolumeElement::get(state).getProjectionDirection();
  camdir = center - campos;
  camdir.normalize();

  const float dot = normal.dot(camdir);

  const SbBool backface = (dot >= 0.0f) ? TRUE : FALSE;

  SoMaterialBundle mb(action);
  mb.sendFirst();

  if ( object[0] != 0.0f && object[1] != 0.0f ) { // draw pane
    if ( backface ) glNormal3f(0.0f, 0.0f, -1.0f);
    else glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, object[1], 0.0f);
    glVertex3f(object[0], object[1], 0.0f);
    glVertex3f(object[0], 0.0f, 0.0f);
    glEnd(); // GL_QUADS
  }

  if ( backface ) goto finish;

  glDisable(GL_DEPTH_TEST);
  glDepthMask(FALSE);

  // TODO: it would probably be a good idea to set up clipping around the pane
  inherited::GLRenderBelowPath(action);

  glDepthMask(TRUE);
  glEnable(GL_DEPTH_TEST);

finish:
  state->pop();
}

void
SoGuiPane::GLRenderInPath(SoGLRenderAction * action)
{
  SoDebugError::postInfo("SoGuiPane::GLRenderInPath", "implementation is out of date");
  SoState * state = action->getState();
  state->push();

  SbVec3f world = this->worldSize.getValue();
  SbVec3f object = this->objectSize.getValue();

  SoMaterialBundle mb(action);
  mb.sendFirst();

  // draw pane
  glBegin(GL_QUADS);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, world[1], 0.0f);
  glVertex3f(world[0], world[1], 0.0f);
  glVertex3f(world[0], 0.0f, 0.0f);
  glEnd(); // GL_QUADS

  // adjust scale for new object space
  SbVec3f scalefactor(world[0] / object[0], world[1] / object[1], ZSCALE);
  SoModelMatrixElement::scaleBy(state, this, scalefactor);

  // store current model matrix
  PRIVATE(this)->modelmatrix = SoModelMatrixElement::get(state);
  PRIVATE(this)->position = SbVec3f(0.0f, 0.0f, 0.0f);

  GLint olddepthfunc = 0;
  glGetIntegerv(GL_DEPTH_FUNC, &olddepthfunc);
  glDepthFunc(GL_LEQUAL);

  // FIXME: set up clipping around pane
  inherited::GLRenderInPath(action);

  glDepthFunc((GLenum) olddepthfunc);
  state->pop();
}

void
SoGuiPane::GLRenderOffPath(SoGLRenderAction * action)
{
  // is this one ever invoked?
  SoDebugError::postInfo("SoGuiPane::GLRenderOffPath", "no implementation yet");
  inherited::GLRenderOffPath(action);
}

void
SoGuiPane::pick(SoPickAction * action)
{
  this->doAction(action);
}

void
SoGuiPane::rayPick(SoRayPickAction * action)
{
  this->doAction(action);
}

void
SoGuiPane::getMatrix(SoGetMatrixAction * action)
{
  SoDebugError::postInfo("SoGuiPane::getMatrix", "invoked");
  SbVec3f world = this->worldSize.getValue();
  SbVec3f object = this->objectSize.getValue();
  SbVec3f scalefactor(world[0] / object[0], world[1] / object[1], ZSCALE);
  SbMatrix matrix = SbMatrix::identity();
  matrix.setScale(scalefactor);
  action->getMatrix().multLeft(matrix);
  // FIXME: update inverse matrix
  inherited::getMatrix(action);
}

void
SoGuiPane::handleEvent(SoHandleEventAction * action)
{
  this->doAction(action);
}

void
SoGuiPane::getBoundingBox(SoGetBoundingBoxAction * action)
{
  SbVec3f min = SbVec3f(0.0f, 0.0f, 0.0f);
  SbVec3f max = this->worldSize.getValue();
  min[2] = 0.0f; // -0.001f;
  max[2] = 0.0f; // 0.001f;
  SbBox3f box(min, max);
  action->extendBy(box);
}

SbVec2f
SoGuiPane::getRayPickIntersectionPoint(void) const
{
  return PRIVATE(this)->raypickpos;
}

void
SoGuiPane::moveTo(SoState * state, SbVec3f position)
{
  SbVec3f object = this->objectSize.getValue();
  if ( position[0] < 0.0f ) position[0] = object[0] + position[0];
  if ( position[1] < 0.0f ) position[1] = object[1] + position[1];
  PRIVATE(this)->position = position;
  SbVec3f translation(0.0f, 0.0f, 0.0f);
  translation[0] = PRIVATE(this)->position[0];
  translation[1] = PRIVATE(this)->position[1];
  SoModelMatrixElement::set(state, this, PRIVATE(this)->modelmatrix);
  // SoDebugError::postInfo("SoGuiPane::moveTo", "origo in %g %g", translation[0], translation[1]);
  SoModelMatrixElement::translateBy(state, this, translation);
}

void
SoGuiPane::applyMoveTo(SoGetMatrixAction * action, SbVec3f position)
{
  // FIXME: support negative coordinates
  SoDebugError::postInfo("SoGuiPane::applyMoveTo", "target %g %g", position[0], position[1]);
  action->getMatrix() = PRIVATE(this)->modelmatrix;
  SbMatrix matrix = SbMatrix::identity();
  matrix.setTranslate(position);
  action->getMatrix().multLeft(matrix);
  // FIXME: update inverse matrix
}

void
SoGuiPane::moveBy(SoState * state, SbVec3f offset)
{
  PRIVATE(this)->position += offset;
  SbVec3f translation(0.0f, 0.0f, 0.0f);
  translation[0] = PRIVATE(this)->position[0];
  translation[1] = PRIVATE(this)->position[1];
  SoModelMatrixElement::set(state, this, PRIVATE(this)->modelmatrix);
  // SoDebugError::postInfo("SoGuiPane::moveBy", "origo in %g %g", translation[0], translation[1]);
  SoModelMatrixElement::translateBy(state, this, translation);
}

void
SoGuiPane::applyMoveBy(SoGetMatrixAction * action, SbVec3f offset)
{
  SoDebugError::postInfo("SoGuiPane::applyMoveBy", "offset %g %g", offset[0], offset[1]);
  action->getMatrix() = PRIVATE(this)->modelmatrix;
  SbMatrix matrix = SbMatrix::identity();
  SbVec3f position = PRIVATE(this)->position + offset;
  matrix.setTranslate(position);
  action->getMatrix().multLeft(matrix);
  // FIXME: update inverse matrix
}

#undef ZSCALE
#undef PRIVATE

