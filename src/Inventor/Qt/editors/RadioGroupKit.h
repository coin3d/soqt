/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
