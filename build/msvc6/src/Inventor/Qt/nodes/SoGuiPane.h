#ifndef COIN_SOGUIPANE_H
#define COIN_SOGUIPANE_H

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

#ifndef SOQT_INTERNAL
#error this is a private header file
#endif /* !SOQT_INTERNAL */

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoSeparator.h>

class SoState;

class SoGuiPane : public SoSeparator {
  typedef SoSeparator inherited;
  SO_NODE_HEADER(SoGuiPane);

public:
  static void initClass(void);

  SoGuiPane(void);

  SoSFVec3f worldSize;
  SoSFVec3f objectSize;

  virtual void doAction(SoAction * action);

  virtual void GLRenderBelowPath(SoGLRenderAction * action);
  virtual void GLRenderInPath(SoGLRenderAction * action);
  virtual void GLRenderOffPath(SoGLRenderAction * action);
  virtual void pick(SoPickAction * action);
  virtual void rayPick(SoRayPickAction * action);
  virtual void getMatrix(SoGetMatrixAction * action);
  virtual void getBoundingBox(SoGetBoundingBoxAction * action);
  virtual void handleEvent(SoHandleEventAction * action);

  SbVec2f getRayPickIntersectionPoint(void) const;

protected:
  friend class SoGuiPosition;
  friend class SoGuiTranslation;

  virtual ~SoGuiPane(void);

  void moveTo(SoState * state, SbVec3f position);
  void applyMoveTo(SoGetMatrixAction * action, SbVec3f position);
  void moveBy(SoState * state, SbVec3f translation);
  void applyMoveBy(SoGetMatrixAction * action, SbVec3f translation);

private:
  void * internals;

};

#endif // !COIN_SOGUIPANE_H
