/**************************************************************************\
 *
 *  This file is part of the Coin GUI toolkit libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation.  See the
 *  file LICENSE.LGPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you want to use this library with software that is incompatible
 *  licensewise with the LGPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#ifndef COIN_RGBCUBEEDITORKIT_H
#define COIN_RGBCUBEEDITORKIT_H

#include <Inventor/nodekits/SoSubKit.h>
#include <Inventor/nodekits/SoInteractionKit.h>

static const char RGBCUBE_draggergeometry[] =
"#Inventor V2.1 ascii\n"
"\n"
" DEF DraggerX Scale1Dragger { }\n"
" DEF DraggerY Scale1Dragger { }\n"
" DEF DraggerZ Scale1Dragger { }\n";


class RGBCubeEditorKit : public SoInteractionKit {
  typedef SoInteractionKit inherited;

  friend class RGBCubeEditorKitP;
  class RGBCubeEditorKitP * pimpl;


  SO_KIT_HEADER(RGBCubeEditorKit);
  SO_KIT_CATALOG_ENTRY_HEADER(RGBCubeRoot);
  SO_KIT_CATALOG_ENTRY_HEADER(DraggerX);
  SO_KIT_CATALOG_ENTRY_HEADER(DraggerY);
  SO_KIT_CATALOG_ENTRY_HEADER(DraggerZ);

public:

  // Constants
  static const int CUBE_SIZE_X = 2;
  static const int CUBE_SIZE_Y = 2;
  static const int CUBE_SIZE_Z = 2;

  // Variables
  float draggerXValue;
  float draggerYValue;
  float draggerZValue;
  SoMFColor rgb;

  // Methods
  void initRgbCube();
  void draggerCallback();
  static void initClass();
  virtual SbBool affectsState() const;

  // Constructor
  RGBCubeEditorKit(void);


protected:
  virtual ~RGBCubeEditorKit();
};

#endif // !COIN_RGBCUBEEDITORKIT_H
