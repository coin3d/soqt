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
#include <Inventor/nodekits/SoBaseKit.h>

class RadioGroupKit : public SoBaseKit {
  typedef SoBaseKit inherited;

  SO_KIT_HEADER(RadioGroupKit);

  SoSFInt32 selected;
  SoMFString labels;

public:
  RadioGroupKit(void);
  static void initClass(void);

protected:
  virtual ~RadioGroupKit();
  virtual void handleEvent(SoHandleEventAction * action);
};

#endif // !COIN_RADIOGROUPKIT_H
