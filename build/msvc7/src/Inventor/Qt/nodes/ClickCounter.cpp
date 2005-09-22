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
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoTextureCoordinate2.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/SoLists.h>

#include <Inventor/SbColor.h>

#include <Inventor/Qt/nodes/SoGuiClickCounter.h>
#include <assert.h>

//  SO_KIT_CATALOG_ENTRY_HEADER(topSeparator);
//  SO_KIT_CATALOG_ENTRY_HEADER(surfaceMaterial);
//  SO_KIT_CATALOG_ENTRY_HEADER(surfaceTexture);
//  SO_KIT_CATALOG_ENTRY_HEADER(surfaceTexCoords);
//  SO_KIT_CATALOG_ENTRY_HEADER(surfaceCoords);
//  SO_KIT_CATALOG_ENTRY_HEADER(surfaceFaceSet);

//  SoSFVec3f size;
//  SoSFInt32 value;
//  SoSFTrigger click;
//  SoSFInt32 first;
//  SoSFInt32 last;

class ClickCounter {
public:
  SoGuiClickCounter * api;

  SoFieldSensor * sizesensor;
  static void sizeCB(void * closure, SoSensor * sensor);

  SoFieldSensor * firstsensor;
  static void firstCB(void * closure, SoSensor * sensor);

  ClickCounter(void);
  ~ClickCounter(void);
};

// *************************************************************************

void
SoGuiClickCounter::initClass(void)
{
  SO_KIT_INIT_CLASS(SoGuiClickCounter, SoBaseKit, "BaseKit");
}

SO_KIT_SOURCE(SoGuiClickCounter);

#define PRIVATE(obj) ((ClickCounter *) this->internals)

SoGuiClickCounter::SoGuiClickCounter(void)
{
  this->internals = new ClickCounter;
  PRIVATE(this)->api = this;

  SO_KIT_CONSTRUCTOR(SoGuiClickCounter);

  SO_KIT_ADD_FIELD(size, (SbVec3f(1.0f, 1.0f, 0.0f)));
  SO_KIT_ADD_FIELD(first, (0));
  SO_KIT_ADD_FIELD(last, (0));
  SO_KIT_ADD_FIELD(value, (0));
  SO_KIT_ADD_FIELD(click, ());

  SO_KIT_ADD_CATALOG_ENTRY(surfaceFaceSet, SoIndexedFaceSet, FALSE, topSeparator, "", FALSE);
  SO_KIT_ADD_CATALOG_ENTRY(surfaceCoords, SoCoordinate3, FALSE, topSeparator, surfaceFaceSet, FALSE);
  SO_KIT_ADD_CATALOG_ENTRY(surfaceTexCoords, SoTextureCoordinate2, FALSE, topSeparator, surfaceCoords, FALSE);
  SO_KIT_ADD_CATALOG_ENTRY(surfaceTexture, SoTexture2, TRUE, topSeparator, surfaceTexCoords, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(surfaceMaterial, SoMaterial, TRUE, topSeparator, surfaceTexture, TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(topSeparator, SoSeparator, FALSE, this, "", FALSE);

  SO_KIT_INIT_INSTANCE();

  static float surfacetexturecoordinates[][2] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };
  SoTextureCoordinate2 * surfacetexcoords = SO_GET_ANY_PART(this, "surfaceTexCoords", SoTextureCoordinate2);
  assert(surfacetexcoords);
  surfacetexcoords->point.setValues(0, 4, surfacetexturecoordinates);

  static int32_t surfaceindices[] = { 0, 1, 2, -1, 0, 2, 3, -1 };
  SoIndexedFaceSet * surfacefaceset = SO_GET_ANY_PART(this, "surfaceFaceSet", SoIndexedFaceSet);
  assert(surfacefaceset);
  surfacefaceset->textureCoordIndex.setValues(0, 8, surfaceindices);
  surfacefaceset->coordIndex.setValues(0, 8, surfaceindices);

  // SoMaterial * surfacematerial = SO_GET_ANY_PART(this, "surfaceMaterial", SoMaterial);
  // surfacematerial->diffuseColor.setValue(SbColor(0.0f, 0.0f, 0.0f));

  this->sizeUpdate();

  PRIVATE(this)->sizesensor = new SoFieldSensor(ClickCounter::sizeCB, PRIVATE(this));
  PRIVATE(this)->sizesensor->attach(&(this->size));
  PRIVATE(this)->firstsensor = new SoFieldSensor(ClickCounter::firstCB, PRIVATE(this));
  PRIVATE(this)->firstsensor->attach(&(this->first));
}

SoGuiClickCounter::~SoGuiClickCounter(void)
{
  ClickCounter * obj = PRIVATE(this);
  delete obj;
}

void
SoGuiClickCounter::handleEvent(SoHandleEventAction * action)
{
  const SoEvent * ev = action->getEvent();
  if ( ev->isOfType(SoMouseButtonEvent::getClassTypeId()) ) {
    const SoMouseButtonEvent * event = (SoMouseButtonEvent *) ev;
    if ( event->getState() == SoButtonEvent::DOWN ) {
      const SoPickedPointList & ppoints = action->getPickedPointList();
      SbBool hit = FALSE;
      int i = 0;
      SoIndexedFaceSet * target = SO_GET_ANY_PART(this, "surfaceFaceSet", SoIndexedFaceSet);
      assert(target);
      for ( i = 0; !hit && i < ppoints.getLength(); i++ ) {
        const SoPickedPoint * point = ppoints[i];
        const SoFullPath * path = (const SoFullPath *) point->getPath();
        assert(path);
        SoNode * node = path->getTail();
        if ( node == (SoNode *) target ) hit = TRUE;
      }
      if ( hit ) {
        int32_t firstval = this->first.getValue();
        int32_t lastval = this->last.getValue();
        if ( firstval < lastval ) {
          int32_t val = this->value.getValue() + 1;
          if ( val > lastval ) val = firstval;
          this->value.setValue(val);
        } else if ( firstval > lastval ) {
          int32_t val = this->value.getValue() - 1;
          if ( val < lastval ) val = firstval;
          this->value.setValue(val);
        }
        this->click.touch();
      }
    }
  }
}

void
SoGuiClickCounter::setSurfaceColor(const SbColor & valuearg)
{
}

void
SoGuiClickCounter::sizeUpdate(void)
{
  SbVec3f sizeval = this->size.getValue();
  if ( sizeval[0] != 0.0f && sizeval[1] != 0.0f ) {
    float coordinates[][3] = { {0.0f, 0.0f, 0.0f}, {sizeval[0], 0.0f, 0.0f}, {sizeval[0], sizeval[1], 0.0f}, {0.0f, sizeval[1], 0.0f} };
    SoCoordinate3 * coords = SO_GET_ANY_PART(this, "surfaceCoords", SoCoordinate3);
    assert(coords);
    coords->point.setValues(0, sizeof(coordinates) / sizeof(coordinates[0]), coordinates);
  }
}

void
SoGuiClickCounter::firstUpdate(void)
{
  this->value.setValue(this->first.getValue());
}

SbBool
SoGuiClickCounter::readInstance(SoInput * in, unsigned short flags)
{
  assert(PRIVATE(this)->firstsensor != NULL);
  PRIVATE(this)->firstsensor->detach();
  SbBool retval = inherited::readInstance(in, flags);
  PRIVATE(this)->firstsensor->attach(&(this->first));
  return retval;
}

// *************************************************************************

ClickCounter::ClickCounter(void)
{
  this->api = NULL;
  this->sizesensor = NULL;
  this->firstsensor = NULL;
}

ClickCounter::~ClickCounter(void)
{
}

void
ClickCounter::sizeCB(void * closure, SoSensor * sensor)
{
  assert(closure);
  ClickCounter * me = (ClickCounter *) closure;
  assert(me->api);
  me->api->sizeUpdate();
}

void
ClickCounter::firstCB(void * closure, SoSensor * sensor)
{
  assert(closure);
  ClickCounter * me = (ClickCounter *) closure;
  assert(me->api);
  me->api->firstUpdate();
}

// *************************************************************************

#undef PRIVATE

