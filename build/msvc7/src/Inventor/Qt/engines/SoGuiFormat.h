#ifndef COIN_SOGUIFORMAT_H
#define COIN_SOGUIFORMAT_H

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

#ifndef SOQT_INTERNAL
#error this is a private header file
#endif // !SOQT_INTERNAL

#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/engines/SoSubEngine.h>
#ifdef __COIN__
#include <Inventor/engines/SoEngineOutput.h>
#endif // __COIN__
#include <Inventor/engines/SoEngine.h>

class SoGuiFormat : public SoEngine {
  typedef SoEngine inherited;
  SO_ENGINE_HEADER(SoGuiFormat);

public:
  static void initClass(void);
  SoGuiFormat(void);

  SoSFFloat float1;

  SoSFString format;

  SoEngineOutput output;

protected:
  virtual ~SoGuiFormat(void);
  virtual void evaluate(void);

private:
  void * internals;

};

#endif // !COIN_SOGUIFORMAT_H
