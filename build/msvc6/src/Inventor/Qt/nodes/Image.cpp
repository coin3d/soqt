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

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/sensors/SoFieldSensor.h>

#include <Inventor/Qt/SoAny.h>
#include <Inventor/Qt/nodes/SoGuiImage.h>
#include <assert.h>

// *************************************************************************

class Image {
public:
  Image(void);

  SoGuiImage * api;

  SoFieldSensor * size_sensor;
  static void size_updated_cb(void * closure, SoSensor * sensor);

  SoCoordinate3 * coords;

  static const char * geometryscene[];
};

// *************************************************************************

#define PRIVATE(obj) ((Image *)obj->internals)

void
SoGuiImage::initClass(void)
{
  SO_KIT_INIT_CLASS(SoGuiImage, SoBaseKit, "BaseKit");
}

SO_KIT_SOURCE(SoGuiImage);

SoGuiImage::SoGuiImage(void)
{
  this->internals = new Image;
  PRIVATE(this)->api = this;

  SO_KIT_CONSTRUCTOR(SoGuiImage);
  SO_KIT_ADD_FIELD(size, (SbVec3f(1.0f, 1.0f, 0.0f)));

  SO_KIT_ADD_CATALOG_ENTRY(geometry, SoGroup, FALSE, topSeparator, "", FALSE);
  SO_KIT_ADD_CATALOG_ENTRY(texture, SoTexture2, FALSE, topSeparator, geometry, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(topSeparator, SoSeparator, FALSE, this, "", FALSE);

  SO_KIT_INIT_INSTANCE();

  SoNode * geometryroot = SoAny::loadSceneGraph(Image::geometryscene);
  assert(geometryroot);
  geometryroot->ref();
  geometryroot->isOfType(SoSeparator::getClassTypeId());
  SoNode * realgeometry = ((SoSeparator *) geometryroot)->getChild(0);
  assert(realgeometry);
  realgeometry->ref();

  PRIVATE(this)->coords = (SoCoordinate3 *) SoAny::scanSceneForName(realgeometry, "coords");
  assert(PRIVATE(this)->coords);
  assert(PRIVATE(this)->coords->isOfType(SoCoordinate3::getClassTypeId()));

  realgeometry->unrefNoDelete();
  SbBool ok = this->setAnyPart("geometry", realgeometry);
  assert(ok);
  geometryroot->unref();

  PRIVATE(this)->size_sensor = new SoFieldSensor(Image::size_updated_cb, PRIVATE(this));
  PRIVATE(this)->size_sensor->attach(&(this->size));
}

SoGuiImage::~SoGuiImage(void)
{
  delete PRIVATE(this)->size_sensor;
  Image * obj = PRIVATE(this);
  delete obj;
}

#undef PRIVATE

// *************************************************************************

#define PUBLIC(obj) (obj->api)

const char *
Image::geometryscene[] =
{
  "#Inventor V2.1 ascii",
  "",
  "Group {",
  "  DEF coords Coordinate3 {",
  "    point [ 0 0 0, 1 0 0, 1 1 0, 0 1 0 ]",
  "  }",
  "  TextureCoordinate2 {",
  "    point [ 0 0, 1 0, 1 1, 0 1 ]",
  "  }",
  "  IndexedFaceSet {",
  "    coordIndex [ 0 1 2 -1 0 2 3 -1 ]",
  "    textureCoordIndex [ 0 1 2 -1 0 2 3 -1 ]",
  "  }",
  "}",
  NULL
};

Image::Image(void)
{
  this->api = NULL;
  this->size_sensor = NULL;
  this->coords = NULL;
}

void
Image::size_updated_cb(void * closure, SoSensor * sensor)
{
  assert(closure);
  Image * me = (Image *) closure;
  SbVec3f size = PUBLIC(me)->size.getValue();
  SbBool save = me->coords->point.enableNotify(FALSE);
  me->coords->point.set1Value(1, SbVec3f(size[0], 0.0f, 0.0f));
  me->coords->point.set1Value(2, SbVec3f(size[0], size[1], 0.0f));
  me->coords->point.set1Value(3, SbVec3f(0.0f, size[1], 0.0f));
  me->coords->point.enableNotify(save);
  if ( save ) me->coords->point.touch();
}

#undef PUBLIC

// *************************************************************************
