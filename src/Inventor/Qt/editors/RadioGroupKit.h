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

#ifndef COIN_RADIOGROUPKIT_H
#define COIN_RADIOGROUPKIT_H

#include <Inventor/nodekits/SoSubKit.h>
#include <Inventor/nodekits/SoInteractionKit.h>


#define RADIO_BUTTON_SIZE .2

typedef struct {
  void *thisClass;
  int button;
} paramPackage;

static const char RADIOBULLET_radiobulletgeometry[] =
"#Inventor V2.1 ascii\n"
"\n"
"DEF RadioButtons Separator {\n"
"\n"
" DEF BulletColorActive BaseColor { rgb 0 1 1 }\n"
" DEF BulletColor BaseColor { rgb 1 1 1 }\n"
"\n"
" DEF RadioBulletActive TransformSeparator {\n"
"   USE BulletColorActive\n"
"   Cube { width 0.2 height 0.2 depth 0.2 }\n"
" }\n"
" \n"
" DEF RadioBullet TransformSeparator {\n"
"   USE BulletColor\n"
"   Cube { width 0.2 height 0.2 depth 0.2 }\n"
" }\n"
"}\n"
"\n";


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

  // Vars
  SoSFInt32 selected;
  SoMFString *labels;
  SoTranslation *buttonSpacingX;
  SoTranslation *buttonSpacingY;

  // Methods
  void addRadioButton(SbString label);
  
  // Nodekit functions
  static void initClass();
  virtual SbBool affectsState() const;

  // Constructor
  RadioGroupKit(void);  


protected:
  virtual ~RadioGroupKit();
};

#endif // !COIN_RADIOGROUPKIT_H
