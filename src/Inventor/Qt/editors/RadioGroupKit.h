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

#ifndef COIN_RADIOGROUPKIT_H
#define COIN_RADIOGROUPKIT_H

#include <Inventor/nodekits/SoSubKit.h>
#include <Inventor/nodekits/SoInteractionKit.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFString.h>


class RadioGroupKit : public SoInteractionKit {
  typedef SoBaseKit inherited;

  friend class RadioGroupKitP;
  class RadioGroupKitP * pimpl;


  SO_KIT_HEADER(RadioGroupKit);
  SO_KIT_CATALOG_ENTRY_HEADER(radioGroupRoot);
  SO_KIT_CATALOG_ENTRY_HEADER(RadioBulletActive);
  SO_KIT_CATALOG_ENTRY_HEADER(RadioBullet);
  SO_KIT_CATALOG_ENTRY_HEADER(BulletColorActive);
  SO_KIT_CATALOG_ENTRY_HEADER(BulletColor);

public:

  SoSFInt32 selected;
  SoMFString labels;

  
  static void initClass();
  virtual SbBool affectsState() const;

  RadioGroupKit(void);  


protected:
  virtual ~RadioGroupKit();
};

#endif // !COIN_RADIOGROUPKIT_H
