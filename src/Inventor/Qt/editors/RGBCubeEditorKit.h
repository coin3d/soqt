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

#ifndef COIN_RGBCUBEEDITORKIT_H
#define COIN_RGBCUBEEDITORKIT_H

#include <Inventor/nodekits/SoInteractionKit.h>
#include <Inventor/fields/SoMFColor.h>


class RGBCubeEditorKit : public SoInteractionKit {
  typedef SoInteractionKit inherited;

  SO_KIT_HEADER(RGBCubeEditorKit);

  SO_KIT_CATALOG_ENTRY_HEADER(RGBCubeRoot);

public:
  SoMFColor rgb;

  RGBCubeEditorKit(void);
  static void initClass(void);
  virtual SbBool affectsState(void) const;

  // FIXME: This is only temporary
  static const int CUBE_SIZE_X = 2;
  static const int CUBE_SIZE_Y = 2;
  static const int CUBE_SIZE_Z = 2;

protected:
  virtual ~RGBCubeEditorKit();

private:
  friend class RGBCubeEditorKitP;
  class RGBCubeEditorKitP * pimpl;
};

#endif // !COIN_RGBCUBEEDITORKIT_H
