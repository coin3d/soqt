#ifndef COIN_SOGUISLIDER2_H
#define COIN_SOGUISLIDER2_H

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
#endif /* !SOQT_INTERNAL */

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFVec3f.h>

#include <Inventor/nodekits/SoBaseKit.h>

class SoGuiSlider2 : public SoBaseKit {
  typedef SoBaseKit inherited;

  SO_KIT_HEADER(SoGuiSlider2);

  SO_KIT_CATALOG_ENTRY_HEADER(topSeparator);
  SO_KIT_CATALOG_ENTRY_HEADER(surfaceGeometry);
  SO_KIT_CATALOG_ENTRY_HEADER(surfaceTexture);
  SO_KIT_CATALOG_ENTRY_HEADER(surfaceMaterial);
  SO_KIT_CATALOG_ENTRY_HEADER(surfaceTexCoords);
  SO_KIT_CATALOG_ENTRY_HEADER(surfaceCoords);
  SO_KIT_CATALOG_ENTRY_HEADER(surfaceFaceSet);
  SO_KIT_CATALOG_ENTRY_HEADER(knobGeometry);

public:
  static void initClass(void);

  SoGuiSlider2(void);

  SoSFVec3f size;

  SoSFVec2f min;
  SoSFVec2f max;
  SoSFVec2f value;

  SoSFBool alwaysHook;

  virtual void handleEvent(SoHandleEventAction * action);

  void sizeUpdate(void);
  void valueUpdate(void);

protected:
  virtual ~SoGuiSlider2(void);

private:
  void * internals;

};

#endif // !COIN_SOGUISLIDER2_H
