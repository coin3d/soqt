/**************************************************************************\
 *
 *  This file is part of the Coin family of 3D visualization libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and / or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.  See the
 *  file LICENSE.GPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you desire to use this library in software that is incompatible
 *  with the GNU GPL, and / or you would like to take advantage of the
 *  additional benefits with regard to our support services, please
 *  contact Systems in Motion about acquiring a Coin Professional
 *  Edition License.  See <URL:http://www.coin3d.org> for more
 *  information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
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
