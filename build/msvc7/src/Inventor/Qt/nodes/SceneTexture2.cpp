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

/*
 * TODO
 * - field "SoSFFloat delay" for making node wait a certain time after
 *   last scene change before re-rendering the texture
 * - field "SoSFBool dirty" for making texture show itself as dirty
 *   (stippled?) until it has been rerendered (in case it takes time to
 *   rerender scene).
 */

#include <assert.h>
#include <string.h>

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/sensors/SoOneShotSensor.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/SoOffscreenRenderer.h>
#include <Inventor/misc/SoNotification.h>

#include <Inventor/Qt/nodes/SoGuiSceneTexture2.h>

// *************************************************************************

class SceneTexture2 {
public:
  SceneTexture2(void);

  SoGuiSceneTexture2 * api;

  SbVec2s prevsize;
  SoOffscreenRenderer * renderer;

  SoFieldSensor * size_sensor;
  static void size_updated_cb(void * closure, SoSensor * sensor);

  SoOneShotSensor * render_sensor;
  static void render_cb(void * closure, SoSensor * sensor);
};

// *************************************************************************

#define PRIVATE(obj) ((SceneTexture2 *) obj->internals)

void
SoGuiSceneTexture2::initClass(void)
{
  SO_NODE_INIT_CLASS(SoGuiSceneTexture2, SoTexture2, "Texture2");
}

SO_NODE_SOURCE(SoGuiSceneTexture2);

SoGuiSceneTexture2::SoGuiSceneTexture2(void)
{
  this->internals = new SceneTexture2;
  PRIVATE(this)->api = this;

  SO_NODE_CONSTRUCTOR(SoGuiSceneTexture2);
  SO_NODE_ADD_FIELD(size, (SbVec2f(256.0f, 256.0f)));
  SO_NODE_ADD_FIELD(scene, (NULL));

  PRIVATE(this)->size_sensor = new SoFieldSensor(SceneTexture2::size_updated_cb, PRIVATE(this));
  PRIVATE(this)->size_sensor->attach(&(this->size));
  PRIVATE(this)->render_sensor = new SoOneShotSensor(SceneTexture2::render_cb, PRIVATE(this));
}

SoGuiSceneTexture2::~SoGuiSceneTexture2(void)
{
  delete PRIVATE(this)->size_sensor;
  delete PRIVATE(this)->render_sensor;
  if ( PRIVATE(this)->renderer != NULL ) {
    delete PRIVATE(this)->renderer;
  }
}

// We overload notify() because we need to know when the scene graph has
// been updated, but want to stop that notification from propagating
// through the external scene graph.  We only want the texture update to
// trigger re-rendering.
void
SoGuiSceneTexture2::notify(SoNotList * list)
{
  if ( list->getLastField() == &(this->scene) ) {
    PRIVATE(this)->render_sensor->schedule();
    return;
  }
  inherited::notify(list);
}

//
// we don't want to write out the image and filename fields.
//
void
SoGuiSceneTexture2::write(SoWriteAction * action)
{
  this->image.setDefault(TRUE);
  this->filename.setDefault(TRUE);
  inherited::write(action);
}


#undef PRIVATE

// *************************************************************************

#define PUBLIC(obj) (((SceneTexture2 *) obj)->api)

SceneTexture2::SceneTexture2(void)
{
  this->api = NULL;
  this->prevsize = SbVec2s(-1, -1);
  this->renderer = NULL;
  this->size_sensor = NULL;
  this->render_sensor = NULL;
}

void
SceneTexture2::size_updated_cb(void * closure, SoSensor * sensor)
{
  assert(closure);
  SceneTexture2 * me = (SceneTexture2 *) closure;
  SbVec2f tempsize = PUBLIC(me)->size.getValue();
  SbVec2s size;
  size[0] = (short) tempsize[0];
  size[1] = (short) tempsize[1];
  if ( size != me->prevsize ) {
    if ( me->renderer != NULL ) {
      me->renderer->setViewportRegion(SbViewportRegion(size));
      PUBLIC(me)->image.setValue(size, 3, NULL);
      me->render_sensor->schedule();
    }
    me->prevsize = size;
  }
}

void
SceneTexture2::render_cb(void * closure, SoSensor * sensor)
{
  assert(closure);
  SceneTexture2 * me = (SceneTexture2 *) closure;
  SbVec2f tempsize = PUBLIC(me)->size.getValue();
  SbVec2s size;
  size[0] = (short) tempsize[0];
  size[1] = (short) tempsize[1];
  int nc = 3;
  SoNode * scene = PUBLIC(me)->scene.getValue();
  SbBool save = PUBLIC(me)->image.enableNotify(FALSE);
  if ( scene != NULL ) {
    if ( me->renderer == NULL ) {
      me->renderer = new SoOffscreenRenderer(SbViewportRegion(size));
      me->renderer->setComponents(SoOffscreenRenderer::RGB);
      me->renderer->getGLRenderAction()->setTransparencyType(SoGLRenderAction::BLEND);
      me->prevsize = size;
      PUBLIC(me)->image.setValue(size, nc, NULL);
    }
    me->renderer->render(scene);
    unsigned char * renderbuffer = me->renderer->getBuffer();
    unsigned char * imagebytes = PUBLIC(me)->image.startEditing(size, nc);
    memcpy(imagebytes, renderbuffer, size[0] * size[1] * nc);
    PUBLIC(me)->image.finishEditing();
  } else {
    unsigned char * imagebytes = PUBLIC(me)->image.startEditing(size, nc);
    memset(imagebytes, 0, size[0] * size[1] * nc);
    PUBLIC(me)->image.finishEditing();
  }
  PUBLIC(me)->image.enableNotify(save);
  if ( save ) PUBLIC(me)->image.touch();
}

#undef PUBLIC

// *************************************************************************
