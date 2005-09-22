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

#include <Inventor/Qt/engines/SoGuiRadioGroup.h>
#include <assert.h>

SO_ENGINE_SOURCE(SoGuiRadioGroup);

void
SoGuiRadioGroup::initClass(void)
{
  SO_ENGINE_INIT_CLASS(SoGuiRadioGroup, SoEngine, "Engine");
}

SoGuiRadioGroup::SoGuiRadioGroup(void)
{
  this->index = -1;

  SO_ENGINE_CONSTRUCTOR(SoGuiRadioGroup);

  SO_ENGINE_ADD_INPUT(in0, (FALSE));
  SO_ENGINE_ADD_INPUT(in1, (FALSE));
  SO_ENGINE_ADD_INPUT(in2, (FALSE));
  SO_ENGINE_ADD_INPUT(in3, (FALSE));
  SO_ENGINE_ADD_INPUT(in4, (FALSE));
  SO_ENGINE_ADD_INPUT(in5, (FALSE));
  SO_ENGINE_ADD_INPUT(in6, (FALSE));
  SO_ENGINE_ADD_INPUT(in7, (FALSE));

  SO_ENGINE_ADD_OUTPUT(out0, SoSFBool);
  SO_ENGINE_ADD_OUTPUT(out1, SoSFBool);
  SO_ENGINE_ADD_OUTPUT(out2, SoSFBool);
  SO_ENGINE_ADD_OUTPUT(out3, SoSFBool);
  SO_ENGINE_ADD_OUTPUT(out4, SoSFBool);
  SO_ENGINE_ADD_OUTPUT(out5, SoSFBool);
  SO_ENGINE_ADD_OUTPUT(out6, SoSFBool);
  SO_ENGINE_ADD_OUTPUT(out7, SoSFBool);
}

SoGuiRadioGroup::~SoGuiRadioGroup(void)
{
}

void
SoGuiRadioGroup::inputChanged(SoField * which)
{
  SoSFBool * fields[] = {
    &(this->in0),
    &(this->in1),
    &(this->in2),
    &(this->in3),
    &(this->in4),
    &(this->in5),
    &(this->in6),
    &(this->in7),
    NULL
  };
  int i;
  for ( i = 0; which != fields[i] && fields[i] != NULL; i++ ) { }
  assert(fields[i] != NULL );
  if ( ((SoSFBool *)which)->getValue() != FALSE ) {
    this->index = i;
  } else {
    if ( this->index == i ) this->index = -1;
  }
}

void
SoGuiRadioGroup::evaluate(void)
{
  if ( this->index == -1 ) return; // avoid update
  SoSFBool * fields[] = {
    &(this->in0), &(this->in1), &(this->in2), &(this->in3),
    &(this->in4), &(this->in5), &(this->in6), &(this->in7),
    NULL
  };
  SoEngineOutput * outputs[] = {
    &(this->out0), &(this->out1), &(this->out2), &(this->out3),
    &(this->out4), &(this->out5), &(this->out6), &(this->out7),
    NULL
  };
  int i;
  for ( i = 0; i < 8; i++ ) {
    if ( i == this->index ) {
      SO_ENGINE_OUTPUT((*outputs[i]), SoSFBool, setValue(TRUE));
    } else {
      SO_ENGINE_OUTPUT((*outputs[i]), SoSFBool, setValue(FALSE));
    }
  }
}

