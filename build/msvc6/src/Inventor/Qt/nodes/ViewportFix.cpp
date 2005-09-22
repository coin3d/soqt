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

#include <assert.h>

#include <Inventor/SbViewportRegion.h>
#include <Inventor/SbLinear.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoPickAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/actions/SoGetMatrixAction.h>
#include <Inventor/elements/SoModelMatrixElement.h>

#include <Inventor/Qt/nodes/SoGuiViewportFix.h>

// *************************************************************************

SO_NODE_SOURCE(SoGuiViewportFix);

void
SoGuiViewportFix::initClass(void)
{
  SO_NODE_INIT_CLASS(SoGuiViewportFix, SoTransformation, "Transformation");
}

SoGuiViewportFix::SoGuiViewportFix(void)
{
  this->internals = NULL;

  SO_NODE_CONSTRUCTOR(SoGuiViewportFix);

  SO_NODE_ADD_FIELD(corner, (SoGuiViewportFix::LEFT_BOTTOM));
  SO_NODE_ADD_FIELD(viewportSize, (SbVec3f(0.0f, 0.0f, 0.0f)));

  SO_NODE_DEFINE_ENUM_VALUE(Corner, LEFT_TOP);
  SO_NODE_DEFINE_ENUM_VALUE(Corner, RIGHT_TOP);
  SO_NODE_DEFINE_ENUM_VALUE(Corner, LEFT_BOTTOM);
  SO_NODE_DEFINE_ENUM_VALUE(Corner, RIGHT_BOTTOM);

  SO_NODE_SET_SF_ENUM_TYPE(corner, Corner);
}

SoGuiViewportFix::~SoGuiViewportFix(void)
{
}

void
SoGuiViewportFix::doAction(SoAction * action)
{
  SoState * state = action->getState();
  if ( ! state->isElementEnabled(SoModelMatrixElement::getClassStackIndex()) ) return;

  SbVec3f vpsize = this->viewportSize.getValue();
  if ( vpsize[0] <= 0.0f || vpsize[1] <= 0.0f ) return;

  SoModelMatrixElement::makeIdentity(state, this);

  switch ( this->corner.getValue() ) {
  case SoGuiViewportFix::LEFT_BOTTOM:
    do {
      SbVec3f translation(-1.0f, -1.0f, 0.0f);
      SbVec3f scale(2.0f, 2.0f, 1.0f);
      if ( vpsize[0] > vpsize[1] ) {
	translation[0] = translation[0] * (vpsize[0] / vpsize[1]);
	scale[0] = scale[0] * (vpsize[0] / vpsize[1]);
      } else {
	translation[1] = translation[1] * (vpsize[1] / vpsize[0]);
	scale[1] = scale[1] * (vpsize[1] / vpsize[0]);
      }
      SoModelMatrixElement::translateBy(state, this, translation);
      SoModelMatrixElement::scaleBy(state, this, scale);
      // FIXME: scale
    } while ( FALSE );
    break;
  default:
    do {
      SoDebugError::postInfo("SoGuiViewportFix::GLRender", "unimplemented corner");
    } while ( FALSE );
    break;
  }
}

void
SoGuiViewportFix::GLRender(SoGLRenderAction * action)
{
  const SbViewportRegion & vp = action->getViewportRegion();
  SbVec2s vpsize = vp.getViewportSizePixels();

  SbVec3f viewport(vpsize[0], vpsize[1], 0.0f);
  if ( viewport != this->viewportSize.getValue() )
    this->viewportSize.setValue(vpsize[0], vpsize[1], 0.0f);

  this->doAction(action);
}

void
SoGuiViewportFix::pick(SoPickAction * action)
{
  this->doAction(action);
}

void
SoGuiViewportFix::rayPick(SoRayPickAction * action)
{
  this->doAction(action);
}

void
SoGuiViewportFix::getMatrix(SoGetMatrixAction * action)
{
  SoDebugError::postInfo("SoGuiViewportFix::getMatrix", "not implemented yet");

  SbVec3f vpsize = this->viewportSize.getValue();
  if ( vpsize[0] <= 0.0f || vpsize[1] <= 0.0f ) return;

  action->getMatrix() = SbMatrix::identity();

  switch ( this->corner.getValue() ) {
  case SoGuiViewportFix::LEFT_BOTTOM:
    do {
      SbVec3f translation(-1.0f, -1.0f, 0.0f);
      SbVec3f scale(2.0f, 2.0f, 1.0f);
      if ( vpsize[0] > vpsize[1] ) {
	translation[0] = translation[0] * (vpsize[0] / vpsize[1]);
	scale[0] = scale[0] * (vpsize[0] / vpsize[1]);
      } else {
	translation[1] = translation[1] * (vpsize[1] / vpsize[0]);
	scale[1] = scale[1] * (vpsize[1] / vpsize[0]);
      }
      SbMatrix matrix = SbMatrix::identity();
      matrix.setTranslate(translation);
      action->getMatrix().multLeft(matrix);

      matrix = SbMatrix::identity();
      matrix.setScale(scale);
      action->getMatrix().multLeft(matrix);
    } while ( FALSE );
    break;
  default:
    do {
      SoDebugError::postInfo("SoGuiViewportFix::GLRender", "unimplemented corner");
    } while ( FALSE );
    break;
  }
}

