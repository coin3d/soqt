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

// FIXME: overload the getClassName() type functions

#include <Inventor/SbPList.h>
#include <Inventor/SoSceneManager.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/actions/SoGLRenderAction.h>

#include <Inventor/Qt/SoAny.h>
#include <Inventor/Qt/nodes/SoGuiViewportFix.h>
#include <Inventor/Qt/nodes/SoGuiColorEditor.h>
#include <Inventor/Qt/editors/SoQtColorEditor.h>

/*
#include <Inventor/Qt/nodes/SoGuiPane.h>
#include <Inventor/Qt/nodes/SoGuiClickCounter.h>
#include <Inventor/Qt/nodes/SoGuiSlider1.h>
#include <Inventor/Qt/nodes/SoGuiSlider2.h>
*/


/*!
  \class SoQtColorEditor Inventor/Qt/editors/SoQtColorEditor.h
  \brief The SoQtColorEditor class is a GUI component for interactively
  editing color fields.
*/

/*!
  \enum SoQtColorEditor::Sliders
*/

/*!
  \val SoQtColorEditor::NONE
*/

/*!
  \val SoQtColorEditor::INTENSITY
*/

/*!
  \val SoQtColorEditor::RGB
*/

/*!
  \val SoQtColorEditor::HSV
*/

/*!
  \val SoQtColorEditor::RGB_V
*/

/*!
  \val SoQtColorEditor::RGB_HSV
*/

/*!
  \enum SoQtColorEditor::UpdateFrequency
*/

/*!
  \val SoQtColorEditor::CONTINUOUS
*/

/*!
  \val SoQtColorEditor::AFTER_ACCEPT
*/

// *************************************************************************

static const SbBool SGI_ATTACHMENT_REF_COMPATIBILITY = TRUE;

enum Attachment {
  DETACHED,
  SFCOLOR,
  MFCOLOR,
  MFUINT32
};

// Name suffix used to avoid conflict with private part of the ColorEditor
// node kit.

class ColorEditorComponent {
public:
  SoQtColorEditor * api;

  static const char * superscene[];

  SbPList callbacks;

  // attachment is redundant - the existence of the field sensor, and the
  // field type it is attached to is all the info needed really
  Attachment attachment;
  // the field pointers can actually be dropped since the sensor will have
  // that info
  SoSFColor * sfcolor;
  SoMFColor * mfcolor;
  SoMFUInt32 * mfuint32;
  int mfindex;

  SoFieldSensor * editor_sensor;
  static void editor_update_cb(void * closure, SoSensor * sensor);

  SoFieldSensor * attachment_sensor;
  static void attachment_update_cb(void * closure, SoSensor * sensor);

  SoGuiColorEditor * editor;

  void invokeColorChangeCallbacks(void);
  SbBool colorsEqual(void);
};

// *************************************************************************

SOQT_OBJECT_SOURCE(SoQtColorEditor);

#define PRIVATE(obj) ((ColorEditorComponent *) ((SoQtColorEditor *) obj)->internals)
#define PUBLIC(obj) (((ColorEditorComponent *) obj)->api)

SoQtColorEditor::SoQtColorEditor(QWidget * parent, const char * name, SbBool embed)
  : inherited(parent, name, embed)
{
  this->internals = (void *) new ColorEditorComponent;
  PRIVATE(this)->api = this;

  PRIVATE(this)->attachment = DETACHED;
  PRIVATE(this)->sfcolor = NULL;
  PRIVATE(this)->sfcolor = NULL;
  PRIVATE(this)->mfcolor = NULL;
  PRIVATE(this)->mfuint32 = NULL;
  PRIVATE(this)->mfindex = 0;

  PRIVATE(this)->editor_sensor = NULL;
  PRIVATE(this)->attachment_sensor = NULL;

  PRIVATE(this)->editor = NULL;

  this->setSize(SbVec2s(320, 256));

  SoNode * root = SoAny::loadSceneGraph(ColorEditorComponent::superscene);
  assert(root != NULL);
  assert(root->isOfType(SoSeparator::getClassTypeId()));
  SoSeparator * superscene = (SoSeparator *) root;

  PRIVATE(this)->editor = new SoGuiColorEditor;
  superscene->addChild(PRIVATE(this)->editor);
  this->setSceneGraph(superscene);

  PRIVATE(this)->attachment_sensor = new SoFieldSensor(ColorEditorComponent::attachment_update_cb, PRIVATE(this));

  PRIVATE(this)->editor_sensor = new SoFieldSensor(ColorEditorComponent::editor_update_cb, PRIVATE(this));
  PRIVATE(this)->editor_sensor->attach(&(PRIVATE(this)->editor->color));
}

SoQtColorEditor::~SoQtColorEditor(void)
{
  if ( PRIVATE(this)->attachment != DETACHED ) this->detach();
  delete PRIVATE(this)->attachment_sensor;
  delete PRIVATE(this)->editor_sensor;
  this->setSceneGraph(NULL);
  ColorEditorComponent * instance = PRIVATE(this);
  delete instance;
}

/*!
  Attach the editor to a color single field.  Any existing attachments are
  detached.

  The node argument defaults to NULL and is ignored.  It is part of the
  argument list for compatibility reasons.
*/

void
SoQtColorEditor::attach(SoSFColor * color, SoBase * node)
{
  if ( PRIVATE(this)->attachment != DETACHED ) this->detach();
  if ( color != NULL ) {
    if ( SGI_ATTACHMENT_REF_COMPATIBILITY ) {
      SoFieldContainer * container = color->getContainer();
      if ( container != NULL ) container->ref();
    }
    PRIVATE(this)->attachment = SFCOLOR;
    PRIVATE(this)->sfcolor = color;
    assert(PRIVATE(this)->attachment_sensor != NULL);
    PRIVATE(this)->attachment_sensor->attach(color);
    PRIVATE(this)->editor->color.setValue(color->getValue());
  }
}

/*!
  Attach the editor to an element in a color multi field.  Any existing attachments are
  detached.
  
  The node argument defaults to NULL and is ignored.  It is part of the
  argument list for compatibility reasons.
*/

void
SoQtColorEditor::attach(SoMFColor * color, int idx, SoBase * node)
{
  if ( PRIVATE(this)->attachment != DETACHED ) this->detach();
  if ( color != NULL ) {
    if ( SGI_ATTACHMENT_REF_COMPATIBILITY ) {
      SoFieldContainer * container = color->getContainer();
      if ( container != NULL ) container->ref();
    }
    PRIVATE(this)->attachment = MFCOLOR;
    PRIVATE(this)->mfcolor = color;
    PRIVATE(this)->mfindex = idx;
    assert(PRIVATE(this)->attachment_sensor != NULL);
    PRIVATE(this)->attachment_sensor->attach(color);
    PRIVATE(this)->editor->color.setValue(color->operator[](idx));
  }
}

/*!
  Attach the editor to an element in an uint32 multi field.  The field
  is assumed to be of the RGBA packed color format.  Any existing attachments are
  detached.
  
  The node argument defaults to NULL and is ignored.  It is part of the
  argument list for compatibility reasons.
*/

void
SoQtColorEditor::attach(SoMFUInt32 * color, int idx, SoBase * node)
{
  if ( PRIVATE(this)->attachment != DETACHED ) this->detach();
  if ( color != NULL ) {
    if ( SGI_ATTACHMENT_REF_COMPATIBILITY ) {
      SoFieldContainer * container = color->getContainer();
      if ( container != NULL ) container->ref();
    }
    PRIVATE(this)->attachment = MFUINT32;
    PRIVATE(this)->mfuint32 = color;
    PRIVATE(this)->mfindex = idx;
    assert(PRIVATE(this)->attachment_sensor != NULL);
    PRIVATE(this)->attachment_sensor->attach(color);
    SbColor col;
    float transparency = 0.0f;
    col.setPackedValue(color->operator[](idx), transparency);
    PRIVATE(this)->editor->color.setValue(col);
  }
}

/*!
  Detach the editor from the field it is attached to.
*/

void
SoQtColorEditor::detach(void)
{
  if ( PRIVATE(this)->attachment != DETACHED ) {
    SoField * field = NULL;
    switch ( PRIVATE(this)->attachment ) {
    case SFCOLOR:
      field = PRIVATE(this)->sfcolor;
      PRIVATE(this)->sfcolor = NULL;
      break;
    case MFCOLOR:
      field = PRIVATE(this)->mfcolor;
      PRIVATE(this)->mfcolor = NULL;
      break;
    case MFUINT32:
      field = PRIVATE(this)->mfuint32;
      PRIVATE(this)->mfuint32 = NULL;
      break;
    case DETACHED:
    default:
      assert(0 && "impossible switch case");
      break;
    }
    assert(field != NULL);
    if ( field != NULL ) {
      assert(PRIVATE(this)->attachment_sensor != NULL);
      PRIVATE(this)->attachment_sensor->detach();
      if ( SGI_ATTACHMENT_REF_COMPATIBILITY ) {
        SoFieldContainer * container = field->getContainer();
        if ( container != NULL ) container->unref();
      }
    }
    PRIVATE(this)->attachment = DETACHED;
  }
}

/*!
  This method returns whether or not the editor is currently attached to a field.
*/

SbBool
SoQtColorEditor::isAttached(void) const
{
  return (PRIVATE(this)->attachment != DETACHED) ? TRUE : FALSE;
}

/*
  Add a callback to be triggered when the color value is changed.

  \sa SoQtColorEditor::setUpdateFrequency
*/

void
SoQtColorEditor::addColorChangedCallback(SoQtColorEditorCB * callback, void * closure)
{
  PRIVATE(this)->callbacks.append((void *) callback);
  PRIVATE(this)->callbacks.append(closure);
}

/*!
  Remove all color change callbacks matching the given arguments.
*/

void
SoQtColorEditor::removeColorChangedCallback(SoQtColorEditorCB * callback, void * closure)
{
  const int len = PRIVATE(this)->callbacks.getLength();
  int i;
  for ( i = 0; i < len; i += 2 ) {
    SoQtColorEditorCB * cb =
      (SoQtColorEditorCB *) PRIVATE(this)->callbacks[i];
    if ( (callback == cb) && (closure == PRIVATE(this)->callbacks[i+1]) ) {
      PRIVATE(this)->callbacks.remove(i+1);
      PRIVATE(this)->callbacks.remove(i);
      i -= 2;
    }
  }
}

/*!
  Set a new color value.

  If the field value gets updated, the color change callbacks will be triggered.
*/

void
SoQtColorEditor::setColor(const SbColor & color)
{
  // callbacks are triggered on the sensor rebound...
  switch ( PRIVATE(this)->attachment ) {
  case DETACHED:
    break;
  case SFCOLOR:
    assert(PRIVATE(this)->sfcolor != NULL);
    if ( PRIVATE(this)->sfcolor->getValue() != color ) {
      PRIVATE(this)->sfcolor->setValue(color);
    }
    break;
  case MFCOLOR:
    assert(PRIVATE(this)->mfcolor != NULL);
    if ( PRIVATE(this)->mfcolor->operator[](PRIVATE(this)->mfindex) != color ) {
      PRIVATE(this)->mfcolor->set1Value(PRIVATE(this)->mfindex, color);
    }
    break;
  case MFUINT32:
    assert(PRIVATE(this)->mfuint32 != NULL);
    if ( PRIVATE(this)->mfuint32->operator[](PRIVATE(this)->mfindex) != color.getPackedValue() ) {
      PRIVATE(this)->mfuint32->set1Value(PRIVATE(this)->mfindex, color.getPackedValue());
    }
    break;
  }
  assert(PRIVATE(this)->editor != NULL);
  PRIVATE(this)->editor->color.setValue(color);
}

/*!
  Get the current color value.
*/

const SbColor &
SoQtColorEditor::getColor(void) const
{
  assert(PRIVATE(this)->editor != NULL);
  return PRIVATE(this)->editor->color.getValue();
}

/*!
  Not implemented yet.

  Sets whether or not the color sliders should be in WYSIWYG mode.
  When enabled, the color backgrounds in the sliders will be updated to
  reflect what the color will be, taken all color components into account.
  When disabled, the color backgrounds only reflect the component the slider
  controls.
*/

void
SoQtColorEditor::setWYSIWYG(SbBool enable)
{
  assert(PRIVATE(this)->editor != NULL);
  PRIVATE(this)->editor->wysiwyg.setValue(enable);
}

/*!
  Returns whether or not the editor sliders are in WYSIWYG mode.
*/

SbBool
SoQtColorEditor::isWYSIWYG(void) const
{
  assert(PRIVATE(this)->editor != NULL);
  return PRIVATE(this)->editor->wysiwyg.getValue();
}

/*!
  Sets which if the slider sets is to be used.

  \sa SoQtColorEditor::Sliders
*/

void
SoQtColorEditor::setCurrentSliders(SoQtColorEditor::Sliders which)
{
  assert(PRIVATE(this)->editor != NULL);
  PRIVATE(this)->editor->sliders.setValue((SoQtColorEditor::Sliders) which);
}

/*!
  Returns which slider sets is being used.

  \sa SoQtColorEditor::Sliders
*/

SoQtColorEditor::Sliders
SoQtColorEditor::getCurrentSliders(void) const
{
  assert(PRIVATE(this)->editor != NULL);
  return (SoQtColorEditor::Sliders) PRIVATE(this)->editor->sliders.getValue();
}

/*!
  Sets the update-frequency setting, which affects when color change callbacks
  will be triggered.

  \sa SoQtColorEditor::UpdateFrequency
*/

void
SoQtColorEditor::setUpdateFrequency(SoQtColorEditor::UpdateFrequency freq)
{
  assert(PRIVATE(this)->editor != NULL);
  PRIVATE(this)->editor->update.setValue((SoQtColorEditor::UpdateFrequency) freq);
}

/*!
  Returns the update-frequency setting.

  \sa SoQtColorEditor::UpdateFrequency
*/

SoQtColorEditor::UpdateFrequency
SoQtColorEditor::getUpdateFrequency(void) const
{
  assert(PRIVATE(this)->editor != NULL);
  return (SoQtColorEditor::UpdateFrequency) PRIVATE(this)->editor->update.getValue();
}

SoGuiColorEditor *
SoQtColorEditor::getEditor(void) const
{
  return PRIVATE(this)->editor;
}

// *************************************************************************

const char *
SoQtColorEditor::getDefaultWidgetName(void) const
{
  static const char widgetName[] = "SoQtColorEditor";
  return widgetName;
}

const char *
SoQtColorEditor::getDefaultTitle(void) const
{
  static const char title[] = "ColorEditor";
  return title;
}

const char *
SoQtColorEditor::getDefaultIconTitle(void) const
{
  static const char iconTitle[] = "ColEd";
  return iconTitle;
}

// *************************************************************************
// ColorEditorComponent
// *************************************************************************

const char *
ColorEditorComponent::superscene[] =
{
  "#Inventor V2.1 ascii",
  "",
  "Separator {",
  "  DirectionalLight { direction 0 0 -1 color 1 1 1 intensity 0.8 }",
  "  OrthographicCamera { }",
  "  DEF viewportfix SoGuiViewportFix { }",
  "  Material { ambientColor 0.8 0.8 0.8 }",
  "}",
  NULL
};

// *************************************************************************

void
ColorEditorComponent::invokeColorChangeCallbacks(void)
{
  int i;
  for ( i = 0; i < this->callbacks.getLength(); i += 2 ) {
    SoQtColorEditorCB * callback = (SoQtColorEditorCB *) this->callbacks[i];
    void * closure = this->callbacks[i+1];
    callback(closure, &this->editor->color.getValue());
  }
}

SbBool
ColorEditorComponent::colorsEqual(void)
{
  SbColor attachmentColor;
  switch ( this->attachment ) {
  case SFCOLOR:
    assert(this->sfcolor != NULL);
    attachmentColor = this->sfcolor->getValue();
    break;
  case MFCOLOR:
    assert(this->mfcolor != NULL);
    attachmentColor = this->mfcolor->operator[](this->mfindex);
    break;
  case MFUINT32:
    assert(this->mfcolor != NULL);
    do {
      float transparency = 0.0f;
      attachmentColor.setPackedValue(this->mfuint32->operator[](this->mfindex), transparency);
    } while ( FALSE );
    break;
  case DETACHED:
  default:
    return TRUE;
  }
  return (attachmentColor == this->editor->color.getValue()) ? TRUE : FALSE;
}

void
ColorEditorComponent::attachment_update_cb(void * closure, SoSensor * sensor)
{
  assert(closure != NULL);
  ColorEditorComponent * me = (ColorEditorComponent *) closure;
  if ( me->colorsEqual() ) return;

  switch ( me->attachment ) {
  case SFCOLOR:
    assert(me->sfcolor != NULL);
    me->editor->color.setValue(me->sfcolor->getValue());
    break;
  case MFCOLOR:
    assert(me->mfcolor != NULL);
    me->editor->color.setValue(me->mfcolor->operator[](me->mfindex));
    break;
  case MFUINT32:
    assert(me->mfcolor != NULL);
    do {
      SbColor color;
      float transparency = 0.0f;
      color.setPackedValue(me->mfuint32->operator[](me->mfindex), transparency);
      me->editor->color.setValue(color);
    } while ( FALSE );
    break;
  case DETACHED:
  default:
    break;
  }
}

void
ColorEditorComponent::editor_update_cb(void * closure, SoSensor * sensor)
{
  assert(closure != NULL);
  ColorEditorComponent * me = (ColorEditorComponent *) closure;
  if ( me->colorsEqual() ) return;

  SbColor color = me->editor->color.getValue();

  switch ( me->attachment ) {
  case SFCOLOR:
    assert(me->sfcolor != NULL);
    me->sfcolor->setValue(color);
    break;
  case MFCOLOR:
    assert(me->mfcolor != NULL);
    me->mfcolor->set1Value(me->mfindex, color);
    break;
  case MFUINT32:
    assert(me->mfuint32 != NULL);
    me->mfuint32->set1Value(me->mfindex, color.getPackedValue());
    break;
  case DETACHED:
  default:
    break;
  }

  if ( me->editor->update.getValue() == SoGuiColorEditor::CONTINUOUS )
    me->invokeColorChangeCallbacks();
}

// *************************************************************************

#undef PRIVATE
#undef PUBLIC

