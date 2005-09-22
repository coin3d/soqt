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

#include <assert.h>

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoAsciiText.h>
#include <Inventor/sensors/SoFieldSensor.h>

#include <Inventor/Qt/SoAny.h>
#include <Inventor/Qt/nodes/SoGuiLabel.h>

// *************************************************************************

class Label {
public:
  Label(void);

  SoGuiLabel * api;

  SoAsciiText * text;

  SoFieldSensor * text_sensor;
  SoFieldSensor * which_sensor;
  static void text_updated_cb(void * closure, SoSensor * sensor);

  static const char * scene[];
};

// *************************************************************************

#define PRIVATE(obj) ((Label *)this->internals)

void
SoGuiLabel::initClass(void)
{
  SO_KIT_INIT_CLASS(SoGuiLabel, SoBaseKit, "BaseKit");
}

SO_KIT_SOURCE(SoGuiLabel);

SoGuiLabel::SoGuiLabel(void)
{
  this->internals = new Label;
  PRIVATE(this)->api = this;

  SO_KIT_CONSTRUCTOR(SoGuiLabel);
  SO_KIT_ADD_FIELD(text, (""));
  SO_KIT_ADD_FIELD(which, (0));

  SO_KIT_ADD_CATALOG_ENTRY(scene, SoSeparator, FALSE, this, "", FALSE);

  SO_KIT_INIT_INSTANCE();

  SoNode * thescene = SoAny::loadSceneGraph(Label::scene);
  assert(thescene);
  thescene->ref();

  PRIVATE(this)->text = (SoAsciiText *) SoAny::scanSceneForName(thescene, "text");
  assert(PRIVATE(this)->text);

  thescene->unrefNoDelete();
  SbBool ok = this->setAnyPart("scene", thescene);
  assert(ok);

  PRIVATE(this)->text_sensor = new SoFieldSensor(Label::text_updated_cb, PRIVATE(this));
  PRIVATE(this)->text_sensor->attach(&(this->text));
  PRIVATE(this)->which_sensor = new SoFieldSensor(Label::text_updated_cb, PRIVATE(this));
  PRIVATE(this)->which_sensor->attach(&(this->which));
  Label::text_updated_cb(PRIVATE(this), NULL);
}

SoGuiLabel::~SoGuiLabel(void)
{
  delete PRIVATE(this)->text_sensor;
  delete PRIVATE(this)->which_sensor;
  Label * obj = PRIVATE(this);
  delete obj;
}

#undef PRIVATE

// *************************************************************************

#define PUBLIC(obj) (obj->api)

const char *
Label::scene[] =
{
  "#Inventor V2.1 ascii",
  "",
  "Separator {",
  "  SoGuiTranslation { translation 1 1 0 }",
  "  Scale { scaleFactor 1.5 1.5 1 }",
  "  BaseColor { rgb 0 0 0 }",
  "  DEF text AsciiText { }",
  "}",
  NULL
};

Label::Label(void)
{
  this->api = NULL;
  this->text = NULL;
  this->which_sensor = NULL;
}

void
Label::text_updated_cb(void * closure, SoSensor * sensor)
{
  assert(closure);
  Label * me = (Label *) closure;
  assert(me->text);
  int which = PUBLIC(me)->which.getValue();
  // SbString string = PUBLIC(me)->text.getValue();
  SbString string = PUBLIC(me)->text[which];
  me->text->string.setValue(string);
}

#undef PUBLIC

// *************************************************************************
