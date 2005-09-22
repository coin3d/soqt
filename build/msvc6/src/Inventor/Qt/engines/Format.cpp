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

#include <Inventor/SbString.h>
#include <Inventor/errors/SoDebugError.h>
#include <stdio.h>

#include <Inventor/Qt/engines/SoGuiFormat.h>

void
SoGuiFormat::initClass(void)
{
  SO_ENGINE_INIT_CLASS(SoGuiFormat, SoEngine, "Engine");
}

SO_ENGINE_SOURCE(SoGuiFormat);

SoGuiFormat::SoGuiFormat(void)
{
  this->internals = NULL;

  SO_ENGINE_CONSTRUCTOR(SoGuiFormat);

  SO_ENGINE_ADD_INPUT(float1, (0.0f));
  SO_ENGINE_ADD_INPUT(format, (""));

  SO_ENGINE_ADD_OUTPUT(output, SoSFString);
}

SoGuiFormat::~SoGuiFormat(void)
{
}

void
SoGuiFormat::evaluate(void)
{
#ifdef __COIN__
  SbString result;
  result.sprintf(this->format.getValue().getString(), this->float1.getValue());
#else // __COIN__
  char buf[4096]; // FIXME: temporary workaround
  sprintf(buf, this->format.getValue().getString(), this->float1.getValue());
  SbString result = buf;
#endif // ! __COIN__
 
  // SoDebugError::postInfo("SoGuiFormat::evaluate", "%s", result.getString());
  SO_ENGINE_OUTPUT(output, SoSFString, setValue(result));
}

