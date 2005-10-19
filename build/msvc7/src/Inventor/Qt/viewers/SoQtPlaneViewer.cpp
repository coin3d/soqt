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

// src/Inventor/Qt/viewers/SoQtPlaneViewer.cpp.  Generated from SoGuiPlaneViewer.cpp.in by configure.

// This file contains the generic, "templatize-able" parts of the
// So*PlaneViewer sourcecode.

/*!
  \class SoQtPlaneViewer Inventor/Qt/viewers/SoQtPlaneViewer.h
  \brief The SoQtPlaneViewer class is for examining 3D models by moving the camera in orthogonal planes.
  \ingroup components viewers

  The SoQtPlaneViewer is a viewer that is useful for "CAD-style"
  applications, where you want the end-user to examine your model with
  the viewpoint set from one of the three principal axes.

  <center>
  <img src="http://doc.coin3d.org/images/SoLibs/viewers/planeviewer.png">
  </center>


  Controls:
  <ul>

  <li>hold down left mousebutton and move mouse pointer to dolly (or
  hold both left and middle mousebuttons)</li>

  <li>hold middle mousebutton to pan (or a CTRL-key plus left
  mousebutton, or a SHIFT-key plus left mousebutton)</li>

  <li>hold down CTRL + middle mousebutton to rotate (or CTRL + SHIFT +
  the left mousebutton)</li>

  <li>click 's', then pick with the left mousebutton to seek</li>

  <li>right mousebutton open the popup menu</li>

  <li>click 'ESC' key to switch to and from 'view' mode and
  'scenegraph interaction' mode (see setViewing() documentation)</li>

  <!-- 
    FIXME: This functionality has been disabled. See FIXME comment
    20050202 larsa below.

  <li>hold down the 'ALT' key to temporary toggle from  
      camera-interaction mode to scenegraph-interaction mode</li>  

  //-->

  </ul>

  Hitting any of the X, Y or Z buttons in the panel on the right side
  of the render canvas will "flip" the current camera direction around
  it's focal point to point along the selected axis (towards negative
  infinity).

  The SoQtPlaneViewer also provides a user decoration's button for
  toggling between orthographic or perspective camera view volumes and
  projection methods. This is the bottom-most click button on the
  right decoration border.

  It also inherits the decoration buttons from the SoQtFullViewer:
  the arrow for switching to "scenegraph interaction" mode, the hand
  for setting back to "camera interaction" mode, the house for "reset
  camera to home position", the blueprint house for "set new camera
  home position", the eye for "zoom camera out to view full scene" and
  the flashlight for setting "click to seek" mode.

  Note that a common faulty assumption about all the viewer-classes is
  that user interaction (in the "examine"-mode, not the
  scenegraph-interaction mode) influences the model or 3D-scene in the
  view. This is not correct, as it is always the viewer's \e camera
  that is translated and rotated.

  The initial position of the camera is placed such that all of the
  scenegraph's geometry fits within it's view.
*/

// *************************************************************************

#include <Inventor/Qt/viewers/SoQtPlaneViewer.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <assert.h>
#include <math.h>

#include <Inventor/Qt/common/gl.h>
#include <Inventor/Qt/SoQtCursor.h>

#include <Inventor/SbLinear.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoKeyboardEvent.h>

#include <soqtdefs.h>

#include <Inventor/Qt/viewers/SoGuiFullViewerP.h> // for pan() and zoom()
#include <Inventor/Qt/viewers/SoQtPlaneViewerP.h>

// *************************************************************************

// To access SoGuiPlaneViewerP "private implementation" class.

#define PRIVATE(ptr) (ptr->pimpl)

// *************************************************************************

SOQT_OBJECT_SOURCE(SoQtPlaneViewer);

// ************************************************************************

/*!
  \fn SoQtPlaneViewer::SoQtPlaneViewer(QWidget * parent, const char * const name, SbBool embed, SoQtFullViewer::BuildFlag flag, SoQtViewer::Type type)

  The public constructor, to be used by application programmers who
  want to instantiate the plain, standard SoQtPlaneViewer.
*/
SoQtPlaneViewer::SoQtPlaneViewer(QWidget * parent,
                                       const char * const name,
                                       SbBool embed,
                                       SoQtFullViewer::BuildFlag flag,
                                       SoQtViewer::Type type)
  : inherited(parent, name, embed, flag, type, FALSE)
{
  PRIVATE(this) = new SoQtPlaneViewerP(this);
  PRIVATE(this)->constructor(TRUE);
}

/*!
  \fn SoQtPlaneViewer::SoQtPlaneViewer(QWidget * parent, const char * const name, SbBool embed, SoQtFullViewer::BuildFlag flag, SoQtViewer::Type type, SbBool build)

  A protected constructor, to be used by application programmers who
  want to extend the SoQtPlaneViewer.
*/
SoQtPlaneViewer::SoQtPlaneViewer(QWidget * parent,
                                       const char * const name,
                                       SbBool embed,
                                       SoQtFullViewer::BuildFlag flag,
                                       SoQtViewer::Type type,
                                       SbBool build)
  : inherited(parent, name, embed, flag, type, FALSE)
{
  PRIVATE(this) = new SoQtPlaneViewerP(this);
  PRIVATE(this)->constructor(build);
}

/*!
  \fn SoQtPlaneViewer::~SoQtPlaneViewer()

  The destructor. Cleans up all internal resources used by the
  SoQtPlaneViewer instance.
*/
SoQtPlaneViewer::~SoQtPlaneViewer()
{
  delete PRIVATE(this);
}

// ************************************************************************

// Documented in superclass.
SbBool
SoQtPlaneViewer::processSoEvent(const SoEvent * const ev)
{
#if SOQT_DEBUG && 0 // debug
  SoDebugError::postInfo("SoQtPlaneViewer::processSoEvent",
                          "[invoked], event '%s' "
                         "(isViewing()==%d, isSeekMode()==%d, mode==%d)",
                         ev->getTypeId().getName().getString(),
                         this->isViewing(), this->isSeekMode(),
                         PRIVATE(this)->mode);
#endif // debug

#if 0
  // [copied from common/viewers/SoGuiExaminerViewer.cpp.in]
  // 
  // 20050202 larsa: I have disabled the below functionality because it
  // caused "alt" to stick - the release never got sent to the scene - the
  // alt key was rendered useless for the Coin envronment  - and I don't
  // think this is compatible behaviour with SGI SoXt either.  end larsa.
  //
  // UPDATE 20050310 mortene: IIRC, pressing the ALT key is a way to
  // temporarily switch between examine mode and view mode in SGI's
  // InventorXt, which is then reversed when the ALT key is
  // released. So this functionality shouldn't simply be disabled, but
  // rather debugged and fixed.
  // 
  // Note: All changes made here should also be applied to
  // common/viewers/SoGuiExaminerViewer.cpp.in

  // Let the end-user toggle between camera-interaction mode
  // ("viewing") and scenegraph-interaction mode with ALT key(s).
  if (ev->getTypeId().isDerivedFrom(SoKeyboardEvent::getClassTypeId())) {
    SoKeyboardEvent * ke = (SoKeyboardEvent *)ev;
    switch (ke->getKey()) {
    case SoKeyboardEvent::LEFT_ALT:
    case SoKeyboardEvent::RIGHT_ALT:
      if (this->isViewing() && (ke->getState() == SoButtonEvent::DOWN)) {
        this->setViewing(FALSE);
        return TRUE;
      }
      else if (!this->isViewing() && (ke->getState() == SoButtonEvent::UP)) {
        this->setViewing(TRUE);
        return TRUE;
      }
    default:
      break;
    }
  }
#endif // 0 - alt-key

  // We're in "interact" mode (ie *not* the camera modification mode),
  // so don't handle the event here. It should either be forwarded to
  // the scenegraph, or caught by SoQtViewer::processSoEvent() if
  // it's an ESC press (to switch modes).
  if (!this->isViewing()) { return inherited::processSoEvent(ev); }
    
  // Events when in "ready-to-seek" mode are ignored, except those
  // which influence the seek mode itself -- these are handled further
  // up the inheritance hierarchy.
  if (this->isSeekMode()) { return inherited::processSoEvent(ev); }


  SbBool processed = FALSE;
  const SoGuiPlaneViewerP::PlaneViewerMode currentmode = PRIVATE(this)->mode;
  SoGuiPlaneViewerP::PlaneViewerMode newmode = currentmode;

  const SoType type(ev->getTypeId());

  const SbVec2s size(this->getGLSize());
  const SbVec2s pos(ev->getPosition());
  const SbVec2f posn((float)pos[0] / (float) SoQtMax(size[0], (short int)1),
                     (float)pos[1] / (float) SoQtMax(size[1], (short int)1));

#if 0 // FIXME: this is used in the examinerviewer, should do the same here. 20020618 mortene.
  // Mismatches in state of the modifier keys happens if the user
  // presses or releases them outside the viewer window.
  if (PRIVATE(this)->ctrldown != ev->wasCtrlDown()) {
    PRIVATE(this)->ctrldown = ev->wasCtrlDown();
  }
  if (PRIVATE(this)->shiftdown != ev->wasShiftDown()) {
    PRIVATE(this)->shiftdown = ev->wasShiftDown();
  }
#endif // FIXME

  if (type.isDerivedFrom(SoMouseButtonEvent::getClassTypeId())) {
    processed = TRUE;
    const SoMouseButtonEvent * event = (const SoMouseButtonEvent *) ev;
    const SbBool press = (event->getState() == SoButtonEvent::DOWN) ? TRUE : FALSE;

    if (press) {
      // Called twice to initialize both "now" (current) and "then"
      // (previous) pointer location.
      PRIVATE(this)->setPointerLocation(pos);
      PRIVATE(this)->setPointerLocation(pos);
    }

    switch (event->getButton()) {
      case SoMouseButtonEvent::BUTTON1:
        PRIVATE(this)->button1down = press;

        if (press && (currentmode == SoGuiPlaneViewerP::SEEK_WAIT_MODE)) {
          newmode = SoGuiPlaneViewerP::SEEK_MODE;
          this->seekToPoint(pos); // implicitly calls interactiveCountInc()
        }
        break;

      case SoMouseButtonEvent::BUTTON2:
        processed = FALSE; // pass on to superclass, so popup menu is shown
        break;

      case SoMouseButtonEvent::BUTTON3:
        PRIVATE(this)->button3down = press;
        break;

#ifdef HAVE_SOMOUSEBUTTONEVENT_BUTTON5
      case SoMouseButtonEvent::BUTTON4:
        if (press) SoGuiFullViewerP::zoom(this->getCamera(), 0.1f);
        break;

      case SoMouseButtonEvent::BUTTON5:
        if (press) SoGuiFullViewerP::zoom(this->getCamera(), -0.1f);
        break;
#endif // HAVE_SOMOUSEBUTTONEVENT_BUTTON5

      default:
        break;
    } // switch (event->getButton())
  } // SoMouseButtonEvent::getClassTypeId()

  if (type.isDerivedFrom(SoKeyboardEvent::getClassTypeId())) {
    const SoKeyboardEvent * event = (const SoKeyboardEvent *) ev;
    const SbBool press = (event->getState() == SoButtonEvent::DOWN) ? TRUE : FALSE;

#if SOQT_DEBUG && 0 // debug
    SoDebugError::postInfo("SoQtPlaneViewer::processSoEvent",
                           "keyboard %s: \"%c\"",
                           press ? "press" : "release",
                           event->getPrintableCharacter());
#endif // debug

    switch (event->getKey()) {
    case SoKeyboardEvent::LEFT_CONTROL:
      processed = TRUE;
      PRIVATE(this)->leftcontroldown = press;
      break;
    case SoKeyboardEvent::RIGHT_CONTROL:
      processed = TRUE;
      PRIVATE(this)->rightcontroldown = press;
      break;
    case SoKeyboardEvent::LEFT_SHIFT:
      processed = TRUE;
      PRIVATE(this)->leftshiftdown = press;
      break;
    case SoKeyboardEvent::RIGHT_SHIFT:
      processed = TRUE;
      PRIVATE(this)->rightshiftdown = press;
      break;

    default:
      break;
    }

  } // SoKeyboardEvent::getClassTypeId()


  if (type.isDerivedFrom(SoLocation2Event::getClassTypeId())) {
    processed = TRUE;
    const SoLocation2Event * event = (const SoLocation2Event *) ev;
    PRIVATE(this)->setPointerLocation(pos);
    const SbVec2f prevn((float) PRIVATE(this)->pointer.then[0] / (float) SoQtMax(size[0], (short int)1),
                        (float) PRIVATE(this)->pointer.then[1] / (float) SoQtMax(size[1], (short int)1));

    do {
      if (currentmode == SoGuiPlaneViewerP::ROTZ_MODE) {
        PRIVATE(this)->rotateZ(PRIVATE(this)->getPointerOrigoMotionAngle());
        break;
      }

      if (currentmode == SoGuiPlaneViewerP::TRANSLATE_MODE) {
        if (posn != prevn) {
          SoGuiFullViewerP::pan(this->getCamera(), this->getGLAspectRatio(),
                                PRIVATE(this)->panningplane, posn, prevn);
        }
        break;
      }

      if (currentmode == SoGuiPlaneViewerP::DOLLY_MODE) {
        if (posn[1] != prevn[1]) {
          float value = this->getRightWheelValue() + (prevn[1] - posn[1]) * 10.0f;
          this->rightWheelMotion(value);
          this->setRightWheelValue(value);
        }
        break;
      }

    } while (FALSE);
  } // SoLocation2Event::getClassTypeId()

  SbBool ctrldown = PRIVATE(this)->leftcontroldown || PRIVATE(this)->rightcontroldown;
  SbBool shiftdown = PRIVATE(this)->leftshiftdown || PRIVATE(this)->rightshiftdown;
  enum {
    BUTTON1DOWN = 1 << 0,
    BUTTON3DOWN = 1 << 1,
    CTRLDOWN =    1 << 2,
    SHIFTDOWN =   1 << 3
  };
  unsigned int combo =
    (PRIVATE(this)->button1down ? BUTTON1DOWN : 0) |
    (PRIVATE(this)->button3down ? BUTTON3DOWN : 0) |
    (ctrldown ? CTRLDOWN : 0) |
    (shiftdown ? SHIFTDOWN : 0);

#if SOQT_DEBUG && 0 // debug
  SoDebugError::postInfo("SoQtPlaneViewer::processSoEvent",
                         "button1==%d, button3==%d, "
                         "lctrl==%d, rctrl==%d, lshift==%d, rshift==%d",
                         PRIVATE(this)->button1down, PRIVATE(this)->button3down,
                         PRIVATE(this)->leftcontroldown, PRIVATE(this)->rightcontroldown,
                         PRIVATE(this)->leftshiftdown, PRIVATE(this)->rightshiftdown);
#endif // debug
  

  switch (combo) {
  case BUTTON1DOWN:
  case BUTTON1DOWN|BUTTON3DOWN:
    newmode = SoGuiPlaneViewerP::DOLLY_MODE;
    break;
  case BUTTON3DOWN:
  case CTRLDOWN|BUTTON1DOWN:
  case SHIFTDOWN|BUTTON1DOWN:
    newmode = SoGuiPlaneViewerP::TRANSLATE_MODE;
    break;
  case CTRLDOWN|BUTTON3DOWN:
  case CTRLDOWN|SHIFTDOWN|BUTTON1DOWN:
    newmode = SoGuiPlaneViewerP::ROTZ_MODE;
    break;
  case CTRLDOWN:
  case CTRLDOWN|SHIFTDOWN:
    newmode = SoGuiPlaneViewerP::ROTZ_WAIT_MODE;
    break;
  default:
    if ((currentmode != SoGuiPlaneViewerP::SEEK_WAIT_MODE) &&
        (currentmode != SoGuiPlaneViewerP::SEEK_MODE)) {
      newmode = SoGuiPlaneViewerP::IDLE_MODE;
    }
    break;
  }

  if (newmode != currentmode) {
    if (newmode == SoGuiPlaneViewerP::ROTZ_MODE) {
      PRIVATE(this)->setCanvasSize(size);
      PRIVATE(this)->setPointerLocation(pos);
      PRIVATE(this)->setPointerLocation(pos);
    }

    PRIVATE(this)->changeMode(newmode);
  }

  // If not handled in this class, pass on upwards in the inheritance
  // hierarchy.
  return processed || inherited::processSoEvent(ev);
}

// ************************************************************************

// Documented in superclass.
void
SoQtPlaneViewer::actualRedraw(void)
{
  if (PRIVATE(this)->mode == SoGuiPlaneViewerP::ROTZ_MODE) {
    PRIVATE(this)->updateAnchorScenegraph();
  }

  inherited::actualRedraw();
}

// ************************************************************************

// documented in superclass
void
SoQtPlaneViewer::setSeekMode(SbBool on)
{
#if SOQT_DEBUG
  if (!!on == !!this->isSeekMode()) {
    SoDebugError::postWarning("SoQtPlaneViewer::setSeekMode",
                              "seek mode already %sset", on ? "" : "un");
    return;
  }
#endif // SOQT_DEBUG

  inherited::setSeekMode(on);

  PRIVATE(this)->changeMode(on ?
                            SoGuiPlaneViewerP::SEEK_WAIT_MODE :
                            (this->isViewing() ?
                             SoGuiPlaneViewerP::IDLE_MODE :
                             SoGuiPlaneViewerP::SCENEGRAPH_INTERACT_MODE));
}

// ************************************************************************

// Documented in superclass.
void
SoQtPlaneViewer::setCursorEnabled(SbBool enable)
{
  inherited::setCursorEnabled(enable);
  PRIVATE(this)->setCursorRepresentation(PRIVATE(this)->mode);
}

// ************************************************************************

// Documented in superclass.
void
SoQtPlaneViewer::setViewing(SbBool enable)
{
  if (!!enable == !!this->isViewing()) {
#if SOQT_DEBUG
    SoDebugError::postWarning("SoQtPlaneViewer::setViewing",
                              "unnecessary invocation");
#endif // SOQT_DEBUG
    return;
  }

  inherited::setViewing(enable);

  PRIVATE(this)->changeMode(this->isViewing() ? 
                            SoGuiPlaneViewerP::IDLE_MODE :
                            SoGuiPlaneViewerP::SCENEGRAPH_INTERACT_MODE);
}

// ************************************************************************

// Documented in superclass.
const char *
SoQtPlaneViewer::getDefaultWidgetName(void) const
{
  return "SoQtPlaneViewer";
}

// Documented in superclass.
const char *
SoQtPlaneViewer::getDefaultTitle(void) const
{
  return "Plane Viewer";
}

// Documented in superclass.
const char *
SoQtPlaneViewer::getDefaultIconTitle(void) const
{
  return "Plane Viewer";
}

// ************************************************************************

// Documented in superclass.
void
SoQtPlaneViewer::bottomWheelStart(void)
{
  PRIVATE(this)->changeMode(SoGuiPlaneViewerP::TRANSLATE_MODE);
}

// Documented in superclass.
void
SoQtPlaneViewer::bottomWheelMotion(float value)
{
  // This method set up the bottom wheel to control camera translation
  // in the horizontal direction.

  if (value != this->getBottomWheelValue()) {
    SoGuiFullViewerP::pan(this->getCamera(), this->getGLAspectRatio(),
                          PRIVATE(this)->panningplane,
                          SbVec2f(value, 0),
                          SbVec2f(this->getBottomWheelValue(), 0));
  }
  inherited::bottomWheelMotion(value);
}

// Documented in superclass.
void
SoQtPlaneViewer::bottomWheelFinish(void)
{
  PRIVATE(this)->changeMode(SoGuiPlaneViewerP::IDLE_MODE);
}


// Documented in superclass.
void
SoQtPlaneViewer::leftWheelStart(void)
{
  PRIVATE(this)->changeMode(SoGuiPlaneViewerP::TRANSLATE_MODE);
}

// Documented in superclass.
void
SoQtPlaneViewer::leftWheelMotion(float value)
{
  // This method set up the left wheel to control camera translation
  // in the vertical direction.

  if (value != this->getLeftWheelValue()) {
    SoGuiFullViewerP::pan(this->getCamera(), this->getGLAspectRatio(),
                          PRIVATE(this)->panningplane,
                          SbVec2f(0, this->getLeftWheelValue()),
                          SbVec2f(0, value));
  }

  inherited::leftWheelMotion(value);
}

// Documented in superclass.
void
SoQtPlaneViewer::leftWheelFinish(void)
{
  PRIVATE(this)->changeMode(SoGuiPlaneViewerP::IDLE_MODE);
}

// Documented in superclass.
void
SoQtPlaneViewer::rightWheelStart(void)
{
  PRIVATE(this)->changeMode(SoGuiPlaneViewerP::DOLLY_MODE);
}

// Documented in superclass.
void
SoQtPlaneViewer::rightWheelMotion(float value)
{
  // This method set up the right wheel to control camera movement in
  // the inwards direction.

  SoGuiFullViewerP::zoom(this->getCamera(), this->getRightWheelValue() - value);
  inherited::rightWheelMotion(value);
}

// Documented in superclass.
void
SoQtPlaneViewer::rightWheelFinish(void)
{
  PRIVATE(this)->changeMode(SoGuiPlaneViewerP::IDLE_MODE);
}

// ************************************************************************

// Documented in superclass.
void
SoQtPlaneViewer::afterRealizeHook(void)
{
  PRIVATE(this)->setCursorRepresentation(PRIVATE(this)->mode);
  inherited::afterRealizeHook();
}

// ************************************************************************

#ifndef DOXYGEN_SKIP_THIS

// Remaining code is for the SoGuiPlaneViewerP "private
// implementation" class.

#define PUBLIC(ptr) (ptr->pub)

SoGuiPlaneViewerP::SoGuiPlaneViewerP(SoQtPlaneViewer * publ)
{
  PUBLIC(this) = publ;
}

SoGuiPlaneViewerP::~SoGuiPlaneViewerP()
{
  if (this->superimposition != NULL) {
    PUBLIC(this)->removeSuperimposition(this->superimposition);
    this->superimposition->unref();
  }
}

// This method locates a named node in the superimposed scene.
static SoNode *
get_scenegraph_node(SoSearchAction * search, SoNode * root, const char * name)
{
  search->reset();
  search->setName(SbName(name));
  search->setInterest(SoSearchAction::FIRST);
  search->setSearchingAll(TRUE);
  search->apply(root);
  assert(search->getPath());
  return search->getPath()->getTail();
}

void
SoGuiPlaneViewerP::commonConstructor(void)
{
  this->mode = SoGuiPlaneViewerP::IDLE_MODE;

  this->canvas = SbVec2s(0, 0);
  this->pointer.now = SbVec2s(0, 0);
  this->pointer.then = SbVec2s(0, 0);
  this->leftcontroldown = FALSE;
  this->rightcontroldown = FALSE;
  this->leftshiftdown = FALSE;
  this->rightshiftdown = FALSE;
  this->button1down = FALSE;
  this->button3down = FALSE;


  static const char * superimposed = {
    "#Inventor V2.1 ascii\n\n"
    ""
    "Separator {"
    "  DEF soqt->orthocam OrthographicCamera {"
    "    height 1"
    "    nearDistance 0"
    "    farDistance 1"
    "  }"
    "  LightModel {"
    "    model BASE_COLOR"
    "  }"
    ""
    "  Separator {"
    "    DEF soqt->geometry Coordinate3 {"
    "      point ["  // coordinates set from code
    "       0 0 0,"
    "       0 0 0," 
    "       0 0 0,"
    "       0 0 0"
    "      ]"
    "    }"
    "    BaseColor { rgb 1 1 1 }"
    "    DEF soqt->style0 DrawStyle { }" // lineWidth set in code
    "    DEF soqt->mainline IndexedLineSet {" // fat line (exterior)
    "      coordIndex ["
    "        0, 1, -1, 1, 2, -1, 1, 3, -1"
    "      ]"
    "    }"
    "    BaseColor { rgb 0.5 0.5 0.5 }"
    "    DEF soqt->style1 DrawStyle { }" // lineWidth set in code
    "    USE soqt->mainline" // thin line (interior)
    "  }"
    "}"
  };

  SoInput * input = new SoInput;
  input->setBuffer((void *)superimposed, strlen(superimposed));
  SbBool ok = SoDB::read(input, this->superimposition);
  assert(ok && "error in superimposed scenegraph");
  delete input;
  this->superimposition->ref();

  SoSearchAction s;
  this->super.coords = (SoCoordinate3 *)
    get_scenegraph_node(&s, this->superimposition, "soqt->geometry");
  this->super.camera = (SoOrthographicCamera *)
    get_scenegraph_node(&s, this->superimposition, "soqt->orthocam");

  PUBLIC(this)->addSuperimposition(this->superimposition);
  PUBLIC(this)->setSuperimpositionEnabled(this->superimposition, FALSE);
}

void
SoGuiPlaneViewerP::rotateZ(const float angle) const
{
  SoCamera * const camera = PUBLIC(this)->getCamera();
  if (! camera) return; // probably a scene-less viewer

  SbVec3f dir;
  camera->orientation.getValue().multVec(SbVec3f(0, 0, -1), dir);
  camera->orientation =
    camera->orientation.getValue() * SbRotation(dir, angle);
}

void
SoGuiPlaneViewerP::viewPlaneX(void) const
{
  SoCamera * const camera = PUBLIC(this)->getCamera();
  if (! camera) return; // probably a scene-less viewer

  SbVec3f dir;
  camera->orientation.getValue().multVec(SbVec3f(0, 0, -1), dir);
  SbVec3f focalpoint = camera->position.getValue() +
    camera->focalDistance.getValue() * dir;
  camera->position = focalpoint +
    camera->focalDistance.getValue() * SbVec3f(1, 0, 0);
  camera->orientation = SbRotation(SbVec3f(0, 1, 0), float(M_PI) / 2.0f);
}

void
SoGuiPlaneViewerP::viewPlaneY(void) const
{
  SoCamera * const camera = PUBLIC(this)->getCamera();
  if (! camera) return; // probably a scene-less viewer

  SbVec3f dir;
  camera->orientation.getValue().multVec(SbVec3f(0, 0, -1), dir);
  SbVec3f focalpoint = camera->position.getValue() +
    camera->focalDistance.getValue() * dir;
  camera->position = focalpoint +
    camera->focalDistance.getValue() * SbVec3f(0, 1, 0);
  camera->orientation = SbRotation(SbVec3f(1, 0, 0), -float(M_PI) / 2.0f);
}

void
SoGuiPlaneViewerP::viewPlaneZ(void) const
{
  SoCamera * const camera = PUBLIC(this)->getCamera();
  if (! camera) return; // probably a scene-less viewer

  SbVec3f dir;
  camera->orientation.getValue().multVec(SbVec3f(0, 0, -1), dir);
  SbVec3f focalpoint = camera->position.getValue() +
    camera->focalDistance.getValue() * dir;
  camera->position = focalpoint +
    camera->focalDistance.getValue() * SbVec3f(0, 0, 1);
  camera->orientation = SbRotation(SbVec3f(0, 1, 0), 0);
}

void
SoGuiPlaneViewerP::setCanvasSize(const SbVec2s size)
{
  this->canvas = size;
}

void
SoGuiPlaneViewerP::setPointerLocation(const SbVec2s position)
{
  this->pointer.then = this->pointer.now;
  this->pointer.now = position;
}

int
SoGuiPlaneViewerP::getPointerXMotion(void) const
{
  return this->pointer.now[0] - this->pointer.then[0];
}

int
SoGuiPlaneViewerP::getPointerYMotion(void) const
{
  return this->pointer.now[1] - this->pointer.then[1];
}

float
SoGuiPlaneViewerP::getPointerOrigoAngle(void) const
{
  SbVec2s now = this->pointer.now;
  now[0] -= this->canvas[0] / 2;
  now[1] -= this->canvas[1] / 2;

  double nowradval = (now[0] != 0) ? atan(fabs((double) (now[1] / now[0]))) : 0.0;

  if (now[0] < 0) nowradval = M_PI - nowradval;
  if (now[1] < 0) nowradval = 2 * M_PI - nowradval;

  return (float)nowradval;
}

float
SoGuiPlaneViewerP::getPointerOrigoMotionAngle(void) const
{
  if (this->pointer.then == this->pointer.now)
    return 0.0f;

  SbVec2s now = this->pointer.now;
  now[0] -= this->canvas[0] / 2;
  now[1] -= this->canvas[1] / 2;

  SbVec2s then = this->pointer.then;
  then[0] -= this->canvas[0] / 2;
  then[1] -= this->canvas[1] / 2;

  double nowradval = (now[0] != 0) ? atan(fabs((double) (now[1] / now[0]))) : 0.0;
  if (now[0] < 0) nowradval = M_PI - nowradval;
  if (now[1] < 0) nowradval = 2 * M_PI - nowradval;

  double thenradval = (then[0] != 0) ? atan(fabs((double) (then[1] / then[0]))) : 0.0;
  if (then[0] < 0) thenradval = M_PI - thenradval;
  if (then[1] < 0) thenradval = 2 * M_PI - thenradval;

  return (float)(nowradval - thenradval);
}

// This method updates the contents of the scenegraph which renders
// the rotate-"anchor".
void
SoGuiPlaneViewerP::updateAnchorScenegraph(void) const
{
  static SbBool first = TRUE;
  if (first) {
    // Can't be done in constructor, as we need a valid OpenGL canvas
    // for the getLineWidthLimits() call.
    first = FALSE;
    SbVec2f range;
    float granularity;
    PUBLIC(this)->getLineWidthLimits(range, granularity);

    SoSearchAction s;
    SoDrawStyle * ds0 = (SoDrawStyle *)
      get_scenegraph_node(&s, this->superimposition, "soqt->style0");
    SoDrawStyle * ds1 = (SoDrawStyle *)
      get_scenegraph_node(&s, this->superimposition, "soqt->style1");

    // Draw a thinner line on top of a fat line, to make an outline.
    ds0->lineWidth = SoQtMin(5.0f, range[1]);
    ds1->lineWidth = SoQtMax(3.0f, range[0]);
  }

  float x = float(this->pointer.now[0]) / float(this->canvas[0]);
  float y = float(this->pointer.now[1]) / float(this->canvas[1]);

  float aspectratio = PUBLIC(this)->getViewportRegion().getViewportAspectRatio();
  SbViewVolume vv = this->super.camera->getViewVolume(aspectratio);
  // know we have ADJUST_CAMERA mapping
  if (aspectratio < 1.0f) vv.scale(1.0f / aspectratio);

  SbVec3f p = vv.getPlanePoint(1.0, SbVec2f(x, y));

  this->super.coords->point.set1Value(0, SbVec3f(0, 0, 0));
  this->super.coords->point.set1Value(1, SbVec3f(p[0], p[1], 0));

  float angle = this->getPointerOrigoAngle();
  SbRotation r(SbVec3f(0, 0, 1), angle);

  SbVec3f xarrow(-0.02f, -0.1f, 0.0f);
  r.multVec(xarrow, xarrow);
  SbVec3f pa = SbVec3f(p[0] + xarrow[0], p[1] + xarrow[1], 0);
  this->super.coords->point.set1Value(2, SbVec3f(pa[0], pa[1], 0));

  SbVec3f yarrow(-0.02f, 0.1f, 0.0f);
  r.multVec(yarrow, yarrow);
  pa = SbVec3f(p[0] + yarrow[0], p[1] + yarrow[1], 0);
  this->super.coords->point.set1Value(3, SbVec3f(pa[0], pa[1], 0));
}

// Set cursor graphics according to mode.
void
SoGuiPlaneViewerP::setCursorRepresentation(PlaneViewerMode modearg)
{
#if SOQT_DEBUG && 0 // debug
  SoDebugError::postInfo("SoQtPlaneViewer::setCursorRepresentation",
                         "mode==%d", mode);
#endif // debug

  assert(PUBLIC(this)->getGLWidget());

  if (!PUBLIC(this)->isCursorEnabled()) {
    PUBLIC(this)->setComponentCursor(SoQtCursor::getBlankCursor());
    return;
  }

  switch (modearg) {
  case SoGuiPlaneViewerP::SCENEGRAPH_INTERACT_MODE:
    PUBLIC(this)->setComponentCursor(SoQtCursor(SoQtCursor::DEFAULT));
    break;

  case SoGuiPlaneViewerP::IDLE_MODE:
  case SoGuiPlaneViewerP::DOLLY_MODE:
    PUBLIC(this)->setComponentCursor(SoQtCursor(SoQtCursor::UPARROW));
    break;
  case SoGuiPlaneViewerP::ROTZ_WAIT_MODE:
  case SoGuiPlaneViewerP::ROTZ_MODE:
    PUBLIC(this)->setComponentCursor(SoQtCursor::getRotateCursor());
    break;
  case SoGuiPlaneViewerP::SEEK_WAIT_MODE:
  case SoGuiPlaneViewerP::SEEK_MODE:
    PUBLIC(this)->setComponentCursor(SoQtCursor(SoQtCursor::CROSSHAIR));
    break;
  case SoGuiPlaneViewerP::TRANSLATE_MODE:
    PUBLIC(this)->setComponentCursor(SoQtCursor::getPanCursor());
    break;
  default:
    assert(0 && "unknown PlaneViewer mode");
    break;
  }
}

void
SoGuiPlaneViewerP::changeMode(PlaneViewerMode newmode)
{
  if (newmode == this->mode) { return; }

  switch (newmode) {
  case SoGuiPlaneViewerP::TRANSLATE_MODE:
  case SoGuiPlaneViewerP::DOLLY_MODE:
    PUBLIC(this)->interactiveCountInc();
    break;

  case SoGuiPlaneViewerP::ROTZ_MODE:
    PUBLIC(this)->interactiveCountInc();
    PUBLIC(this)->setSuperimpositionEnabled(this->superimposition, TRUE);
    PUBLIC(this)->scheduleRedraw();
    break;

  default:
    break;
  }

  switch (this->mode) {
  case SoGuiPlaneViewerP::ROTZ_MODE:
    PUBLIC(this)->setSuperimpositionEnabled(this->superimposition, FALSE);
    PUBLIC(this)->scheduleRedraw();
    // fall through

  case SoGuiPlaneViewerP::TRANSLATE_MODE:
  case SoGuiPlaneViewerP::DOLLY_MODE:
    PUBLIC(this)->interactiveCountDec();
    break;
  default:
    break;
  }

  if (newmode == SoGuiPlaneViewerP::TRANSLATE_MODE) {
    // The plane we're projecting the mouse coordinates to get 3D
    // coordinates should stay the same during the whole pan
    // operation, so we should calculate this value here.
    SoCamera * cam = PUBLIC(this)->getCamera();
    if (cam == NULL) { // can happen for empty scenegraph
      this->panningplane = SbPlane(SbVec3f(0, 0, 1), 0);
    }
    else {
      SbViewVolume vv = cam->getViewVolume(PUBLIC(this)->getGLAspectRatio());
      this->panningplane = vv.getPlane(cam->focalDistance.getValue());
    }
  }

  this->setCursorRepresentation(newmode);
  this->mode = newmode;
}

#endif // DOXYGEN_SKIP_THIS

// *************************************************************************

#undef PRIVATE
#undef PUBLIC

