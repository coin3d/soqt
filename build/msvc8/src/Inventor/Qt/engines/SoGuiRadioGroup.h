#ifndef COIN_SOGUIRADIOGROUP_H
#define COIN_SOGUIRADIOGROUP_H

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

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/engines/SoSubEngine.h>
#ifdef __COIN__
#include <Inventor/engines/SoEngineOutput.h>
#endif // __COIN__
#include <Inventor/engines/SoEngine.h>

class SoGuiRadioGroup : public SoEngine {
  typedef SoEngine inherited;
  SO_ENGINE_HEADER(SoGuiRadioGroup);

public:
  static void initClass(void);
  SoGuiRadioGroup(void);

  SoSFBool in0;
  SoSFBool in1;
  SoSFBool in2;
  SoSFBool in3;
  SoSFBool in4;
  SoSFBool in5;
  SoSFBool in6;
  SoSFBool in7;

  SoEngineOutput out0;
  SoEngineOutput out1;
  SoEngineOutput out2;
  SoEngineOutput out3;
  SoEngineOutput out4;
  SoEngineOutput out5;
  SoEngineOutput out6;
  SoEngineOutput out7;

protected:
  virtual ~SoGuiRadioGroup(void);

private:
  virtual void inputChanged(SoField * which);
  virtual void evaluate(void);

  int index;
};

#endif // !COIN_SOGUIRADIOGROUP_H
