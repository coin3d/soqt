#ifndef COIN_SOGUISCENETEXTURE2_H
#define COIN_SOGUISCENETEXTURE2_H

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

#ifndef SOQT_INTERNAL
#error this is a private header file
#endif // !SOQT_INTERNAL

#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/nodes/SoTexture2.h>

class SoGuiSceneTexture2 : public SoTexture2 {
  typedef SoTexture2 inherited;
  SO_NODE_HEADER(SoGuiSceneTexture2);
public:
  static void initClass(void);
  SoGuiSceneTexture2(void);

  SoSFVec2f size;
  SoSFNode scene;

  virtual void notify(SoNotList * list);
  virtual void write(SoWriteAction * action);

protected:
  virtual ~SoGuiSceneTexture2(void);

private:
  void * internals;

};

#endif // !COIN_SOGUISCENETEXTURE2_H
