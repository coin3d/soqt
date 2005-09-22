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

// src/Inventor/Qt/viewers/SoQtFullViewer.cpp.  Generated from SoGuiFullViewer.cpp.in by configure.

// This file contains the generic, "templatize-able" parts of the
// So*FullViewer sourcecode.

/*!
  \class SoQtFullViewer SoQtFullViewer.h Inventor/Qt/viewers/SoQtFullViewer.h
  \brief The SoQtFullViewer class adds some user interface components to the viewer canvas.
  \ingroup components viewers

  The SoQtFullViewer is an abstract viewer class which extends it's
  superclass (the basic SoQtViewer class) with two major user
  interface additions:

  <ul>

  <li>decorations around the render canvas, with buttons and
  thumbwheels to control camera interaction and various other aspects
  of model / scene viewing</li>

  <li>a popup menu, invoked with the right mouse button, which
  controls yet more aspects of the rendering and the viewer</li>

  </ul>

  The user interface features listed above are the common parts of the
  user interfaces of the SoQtFullViewer's non-abstract subclasses.

  For "real" application programs, the viewers / components from this
  class onwards and further down in the inheritance hierarchy is
  usually not all that interesting, as they enforces too much extra
  user interface cruft not compatible with the look and feel of the
  other parts of the application user interface. So most "real"
  applications will use either the SoQtViewer or the
  SoQtRenderArea as their base-level component, and then inherit
  one of these down into one's own "proper" viewer classes.

  The non-abstract subclasses of the SoQtFullViewer class are
  viewer components often used as a test-bed for prototyping / rapid
  application development when doing quick testing of scenes,
  stand-alone 3D-models, animation techniques, etc etc.


  \sa SoQtConstrainedViewer, SoQtExaminerViewer, SoQtPlaneViewer
*/


// *************************************************************************

#include <float.h>

#include <Inventor/Qt/viewers/SoQtFullViewer.h>
#include <Inventor/Qt/viewers/SoQtFullViewerP.h>
#include <Inventor/Qt/widgets/SoQtPopupMenu.h>
#include <soqtdefs.h>

#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

// ************************************************************************

#define PRIVATE(o) (o->pimpl)
#define PUBLIC(o) (o->pub)

// ************************************************************************

// Note: the following function documentation block will also be used
// for all the miscellaneous viewer subclasses, so keep it general.
/*!
  \fn void SoQtFullViewer::createViewerButtons(QWidget * parent, SbPList * buttonlist)

  Set up the viewer buttons with pixmaps and event connections.


  One important note if you want to override this method to add your
  own buttons to the list (in the explanation below, it is assumed
  that you know how virtual function table pointers are handled by
  C++):

  createViewerButtons() is called (indirectly) from the constructors
  of the viewer classes. This means that you need to delay it's
  invocation until your own subclass's constructor is run, because
  otherwise your re-implementation won't have been added to the
  internal virtual function table yet.

  Delaying a superclass viewer from building it's decorations is done
  by passing build==FALSE as the last argument of the protected
  constructors. You will then have to explicitly trigger the building
  in your own constructor.

  Here's a minimal example that shows the steps needed to be able to
  override createViewerButtons() from SoQtExaminerViewer:

  \code
  class MyExaminerViewer : public SoQtExaminerViewer {
  
  public:
    MyExaminerViewer(QWidget * parent);
  
  protected:
    virtual void createViewerButtons(QWidget * parent, SbPList * buttonlist);
  };
  
  MyExaminerViewer::MyExaminerViewer(QWidget * parent)
    : SoQtExaminerViewer(parent, NULL, TRUE,
                            SoQtFullViewer::BUILD_ALL, SoQtFullViewer::BROWSER,
                            // build == FALSE, to delay creation of decorations
                            FALSE)
  {
    // Explicitly trigger the construction of viewer decorations.
    QWidget * widget = this->buildWidget(this->getParentWidget());
    this->setBaseWidget(widget);
  }
  
  void
  MyExaminerViewer::createViewerButtons(QWidget * parent, SbPList * buttonlist)
  {
    SoQtExaminerViewer::createViewerButtons(parent, buttonlist);
    // [now add your own button(s) to the buttonlist]
  }
  \endcode
*/

/*!
  \enum SoQtFullViewer::BuildFlag

  Valid values for the constructor argument that decides how much of
  the user interface features to set up. The enum values are bitflags
  that can be OR'ed together.
*/
/*!
  \var SoQtFullViewer::BuildFlag SoQtFullViewer::BUILD_NONE

  Do not add any of the user interface components.
*/
/*!
  \var SoQtFullViewer::BuildFlag SoQtFullViewer::BUILD_DECORATION

  Only build and set up the decorations around the OpenGL canvas.
*/
/*!
  \var SoQtFullViewer::BuildFlag SoQtFullViewer::BUILD_POPUP

  Only build the popup menu. (Activated with the right mousebutton.)
*/
/*!
  \var SoQtFullViewer::BuildFlag SoQtFullViewer::BUILD_ALL

  Build all user interface components of the SoQtFullViewer.
*/

/*!
  \var QWidget * SoQtFullViewer::leftDecoration
  The root widget for the left-side decorations.
*/

/*!
  \var QWidget * SoQtFullViewer::leftWheel
  The widget representing the thumbwheel left of the render canvas.
*/

/*!
  \var QWidget * SoQtFullViewer::leftWheelLabel
  Label widget of left wheel.
*/

/*!
  \var char * SoQtFullViewer::leftWheelStr
  Text of left thumbwheel's label.
*/

/*!
  \var float SoQtFullViewer::leftWheelVal
  Current value of the left thumbwheel.
*/

/*!
  \var QWidget * SoQtFullViewer::bottomDecoration
  The root widget for the bottom decorations.
*/

/*!
  \var QWidget * SoQtFullViewer::bottomWheel
  The widget representing the thumbwheel below the render canvas.
*/

/*!
  \var QWidget * SoQtFullViewer::bottomWheelLabel
  Label widget of bottom wheel.
*/

/*!
  \var char * SoQtFullViewer::bottomWheelStr
  Text of bottom thumbwheel's label.
*/

/*!
  \var float SoQtFullViewer::bottomWheelVal
  Current value of the bottom thumbwheel.
*/

/*!
  \var QWidget * SoQtFullViewer::rightDecoration
  The root widget for the right-side decorations.
*/

/*!
  \var QWidget * SoQtFullViewer::rightWheel
  The widget representing the thumbwheel on the right side of the render canvas.
*/

/*!
  \var QWidget * SoQtFullViewer::rightWheelLabel
  Label widget of right wheel.
*/

/*!
  \var char * SoQtFullViewer::rightWheelStr
  Text of right thumbwheel's label.
*/

/*!
  \var float SoQtFullViewer::rightWheelVal
  Current value of the right-side thumbwheel.
*/

/*!
  \var SoQtPopupMenu * SoQtFullViewer::prefmenu
  Pointer to the popup menu instance.
*/

/*!
  \fn SoQtFullViewer::SoQtFullViewer(QWidget * parent, const char * name, SbBool embed, SoQtFullViewer::BuildFlag buildFlag, SoQtViewer::Type type, SbBool build)

  Constructor. See parent class for explanation of arguments.

  Subclasses will probably usually call with the \a buildNow flag set
  to \c FALSE to be able to do delayed building of the OpenGL canvas
  after other setup tasks has been performed.
*/

/*!
  \fn SoQtFullViewer::~SoQtFullViewer()

  Destructor.
*/

/*!
  \fn void SoQtFullViewer::setDecoration(const SbBool enable)

  Turn the viewer decorations on or off.

  \sa isDecoration()
*/

/*!
  \fn SbBool SoQtFullViewer::isDecoration(void) const

  Return \c TRUE if the viewer decorations are on, otherwise \c FALSE.

  \sa setDecoration()
*/

/*!
  \fn void SoQtFullViewer::setPopupMenuEnabled(const SbBool enable)

  Decide whether or not if clicking with the right mouse button on
  the OpenGL canvas should reveal a preferences popup menu when in
  viewing mode.

  \sa isPopupMenuEnabled()
*/

/*!
  \fn SbBool SoQtFullViewer::isPopupMenuEnabled(void) const

  Return \c TRUE if the popup preferences menu is enabled,
  otherwise \c FALSE.

  \sa setPopupMenuEnabled()
*/

/*!
  \fn QWidget * SoQtFullViewer::getAppPushButtonParent(void) const

  Returns the widget which is used as the parent of application
  specified buttons. The row of application buttons (if any) will be
  placed in the upper left corner.

  \sa addAppPushButton(), insertAppPushButton(), removeAppPushButton()
*/

/*!
  \fn void SoQtFullViewer::addAppPushButton(QWidget * newButton)

  Add an application specific push button to the viewer decorations.
  Application buttons will be laid out in a vertical row from the
  upper left corner.

  The button will be added bottom-most.

  \sa insertAppPushButton(), removeAppPushButton(), getAppPushButtonParent()
*/

/*!
  \fn void SoQtFullViewer::insertAppPushButton(QWidget * newButton, int index)

  Insert an application specific push button to the viewer decorations
  at the given \c index.

  \sa addAppPushButton(), removeAppPushButton(), getAppPushButtonParent()
*/

/*!
  \fn void SoQtFullViewer::removeAppPushButton(QWidget * oldButton)

  Remove one of the application specific buttons.

  \sa addAppPushButton(), insertAppPushButton()
*/

/*!
  \fn int SoQtFullViewer::findAppPushButton(QWidget * oldButton) const

  Return the index of a particular button that has been specified by
  the application, or -1 of the button has not been added.

  \sa addAppPushButton()
*/

/*!
  \fn int SoQtFullViewer::lengthAppPushButton(void) const

  Return number of application specific buttons added.

  \sa addAppPushButton(), insertAddAppPushButton()
*/

/*!
  \fn QWidget * SoQtFullViewer::getRenderAreaWidget(void) const

  Returns the render area OpenGL canvas widget.
*/

/*!
  \fn void SoQtFullViewer::buildDecoration(QWidget * parent)

  Build viewer decorations.
*/

/*!
  \fn QWidget * SoQtFullViewer::buildLeftTrim(QWidget * parent)

  Build decorations on the left of the render canvas.  Override this
  method in subclasses if you want your own decorations on the viewer
  window.

  The decoration will be 30 pixels wide.
*/

/*!
  \fn QWidget * SoQtFullViewer::buildBottomTrim(QWidget * parent)

  Build decorations on the bottom of the render canvas. Override this
  method in subclasses if you want your own decorations on the viewer window.
*/

/*!
  \fn QWidget * SoQtFullViewer::buildRightTrim(QWidget * parent)

  Build decorations on the right side of the render canvas. Override this
  method in subclasses if you want your own decorations on the viewer window.
*/

/*!
  \fn QWidget * SoQtFullViewer::buildAppButtons(QWidget * parent)

  Build the application specified button row (if any buttons were
  set up).
*/

/*!
  \fn QWidget * SoQtFullViewer::buildViewerButtons(QWidget * parent)

  Build and layout viewer specified button row.
*/

/*!
  \fn void SoQtFullViewer::buildPopupMenu(void)

  Make a popup menu with preferences settings.

  One important note as for when you want to override this function in
  a subclass: be aware that it will usually be invoked (indirectly)
  from this class's constructor. That is \e before the table of
  virtual function pointers has been set up for the subclass, and
  because of this, the function will not be called in the subclass
  even though it is virtual.

  To make the overriding actually be in effect, you need to delay
  building the widgets of this class. For information on how to do
  that, see the documentation of
  SoQtFullViewer::createViewerButtons().
*/

/*!
  \fn void SoQtFullViewer::openPopupMenu(const SbVec2s position)

  NOTE: This method is not part of the original InventorXt API.
*/

/*!
  \fn void SoQtFullViewer::setLeftWheelString(const char * const string)

  Set label of the left thumbwheel.
*/

/*!
  \fn void SoQtFullViewer::setBottomWheelString(const char * const string)

  Set label of the bottom thumbwheel.
*/

/*!
  \fn void SoQtFullViewer::setRightWheelString(const char * const string)

  Set label of the right thumbwheel.
*/

// ************************************************************************

// Note: the following function documentation blocks for thumbwheel
// handling will also be used for all the miscellaneous viewer
// subclasses, so keep'em general.

/*!
  Called when the user start to drag the thumbwheel in the left
  frame.  Override this method in subclassed viewers to provide your
  own functionality on the thumbwheel.

  \sa leftWheelMotion(), leftWheelFinish()
  \sa bottomWheelStart(), rightWheelStart()
*/
void
SoQtFullViewer::leftWheelStart(void)
{
  this->interactiveCountInc();
}

/*!
  Called repeatedly as the user drags the thumbwheel in the left
  frame.  Override this method in subclassed viewers to provide your
  own functionality on the thumbwheel.

  \sa leftWheelStart(), leftWheelFinish()
  \sa bottomWheelStart(), rightWheelStart()
*/
void
SoQtFullViewer::leftWheelMotion(float value)
{
  this->leftWheelVal = value;
}

/*!
  Called as the user let go of the thumbwheel in the left frame
  after a drag operation. Override this method in subclassed viewers
  to provide your own functionality on the thumbwheel.

  \sa leftWheelStart(), leftWheelMotion()
  \sa bottomWheelStart(), rightWheelStart()
*/
void
SoQtFullViewer::leftWheelFinish(void)
{
  this->interactiveCountDec();
}

/*!
  Set a new value for the left thumbwheel.
*/
void
SoQtFullViewer::setLeftWheelValue(const float value)
{
  this->leftWheelVal = value;
  // Wheel may not be constructed yet, but we need to be robust, as
  // set*WheelValue() is used from subclasses.
  if (this->leftWheel) {
    SoQtFullViewerP::setThumbWheelValue(this->leftWheel, value);
  }
}

/*!
  Get current value of the left thumbwheel.

  \sa leftWheelMotion()
*/
float
SoQtFullViewer::getLeftWheelValue(void) const
{
  return this->leftWheelVal;
}

/*!
  Called when the user start to drag the thumbwheel in the bottom
  frame.  Override this method in subclassed viewers to provide your
  own functionality on the thumbwheel.

  \sa bottomWheelMotion(), bottomWheelFinish()
  \sa leftWheelStart(), rightWheelStart()
*/
void
SoQtFullViewer::bottomWheelStart(void)
{
  this->interactiveCountInc();
}

/*!
  Called repeatedly as the user drags the thumbwheel in the bottom
  frame.  Override this method in subclassed viewers to provide your
  own functionality on the thumbwheel.

  \sa bottomWheelStart(), bottomWheelFinish()
  \sa leftWheelStart(), rightWheelStart()
*/
void
SoQtFullViewer::bottomWheelMotion(float value)
{
  this->bottomWheelVal = value;
}

/*!
  Called as the user let go of the thumbwheel in the bottom frame
  after a drag operation. Override this method in subclassed viewers
  to provide your own functionality on the thumbwheel.

  \sa bottomWheelStart(), bottomWheelMotion()
  \sa leftWheelStart(), rightWheelStart()
*/
void
SoQtFullViewer::bottomWheelFinish(void)
{
  this->interactiveCountDec();
}

/*!
  Set a new value for the bottom thumbwheel.
*/
void
SoQtFullViewer::setBottomWheelValue(const float value)
{
  this->bottomWheelVal = value;
  // Wheel may not be constructed yet, but we need to be robust, as
  // set*WheelValue() is used from subclasses.
  if (this->bottomWheel) {
    SoQtFullViewerP::setThumbWheelValue(this->bottomWheel, value);
  }
}

/*!
  Get current value of the bottom thumbwheel.

  \sa bottomWheelMotion()
*/
float
SoQtFullViewer::getBottomWheelValue(void) const
{
  return this->bottomWheelVal;
}

/*!
  Called when the user start to drag the thumbwheel in the right
  frame.  Override this method in subclassed viewers to provide your
  own functionality on the thumbwheel.

  \sa rightWheelMotion(), rightWheelFinish()
  \sa leftWheelStart(), bottomWheelStart()
*/
void
SoQtFullViewer::rightWheelStart(void)
{
  this->interactiveCountInc();
}

/*!
  Called repeatedly as the user drags the thumbwheel in the right
  frame.  Override this method in subclassed viewers to provide your
  own functionality on the thumbwheel.

  \sa rightWheelStart(), rightWheelFinish()
  \sa leftWheelStart(), bottomWheelStart()
*/
void
SoQtFullViewer::rightWheelMotion(float value)
{
  this->rightWheelVal = value;
}

/*!
  Called as the user let go of the thumbwheel in the right frame
  after a drag operation. Override this method in subclassed viewers
  to provide your own functionality on the thumbwheel.

  \sa rightWheelStart(), rightWheelMotion()
  \sa leftWheelStart(), bottomWheelStart()
*/
void
SoQtFullViewer::rightWheelFinish(void)
{
  this->interactiveCountDec();
}

/*!
  Set a new value for the right thumbwheel.
*/
void
SoQtFullViewer::setRightWheelValue(const float value)
{
  this->rightWheelVal = value;
  // Wheel may not be constructed yet, but we need to be robust, as
  // set*WheelValue() is used from subclasses.
  if (this->rightWheel) {
    SoQtFullViewerP::setThumbWheelValue(this->rightWheel, value);
  }
}

/*!
  Get current value of the right thumbwheel.

  \sa rightWheelMotion()
*/
float
SoQtFullViewer::getRightWheelValue(void) const
{
  return this->rightWheelVal;
}

// *************************************************************************

/*!
  This method returns the native widget for the label below the left
  thumb wheel.
*/

QWidget *
SoQtFullViewer::getLeftWheelLabelWidget(void) const
{
  return this->leftWheelLabel;
}

/*!
  This method returns the native widget for the label below the right thumb
  wheel.
*/
QWidget *
SoQtFullViewer::getRightWheelLabelWidget(void) const
{
  return this->rightWheelLabel;
}

/*!
  This method returns the native widget for the label beside the
  bottom thumb wheel.
*/
QWidget *
SoQtFullViewer::getBottomWheelLabelWidget(void) const
{
  return this->bottomWheelLabel;
}

// ************************************************************************

/*!
  Set title of popup menu.
*/
void
SoQtFullViewer::setPopupMenuString(const char * name)
{
  PRIVATE(this)->popupmenutitle = name;
  if (this->prefmenu) { this->prefmenu->setMenuTitle(SoGuiFullViewerP::ROOT_MENU, name); }
}


// Documented in superclass.
SbBool
SoQtFullViewer::processSoEvent(const SoEvent * const ev)
{
  // We're in "interact" mode (ie *not* the camera modification mode),
  // so don't handle the event here. It should either be forwarded to
  // the scenegraph, or caught by SoQtViewer::processSoEvent() if
  // it's an ESC press (to switch modes).
  if (!this->isViewing()) { return inherited::processSoEvent(ev); }

  // Note: with the original SGI InventorXt, the popup menu is also
  // activated by RMB clicks in non-viewing mode. We want to allow RMB
  // clicks to pass through to the scenegraph in non-viewing mode, so
  // we don't copy that behavior.

  if (ev->getTypeId().isDerivedFrom(SoMouseButtonEvent::getClassTypeId())) {
    SoMouseButtonEvent * const e = (SoMouseButtonEvent *) ev;
    if ((e->getButton() == SoMouseButtonEvent::BUTTON2)) {
      if (this->isPopupMenuEnabled()) {
        if (e->getState() == SoButtonEvent::DOWN) {
          this->openPopupMenu(e->getPosition());
        }
        // Steal all RMB-events if the viewer uses the popup-menu.
        return TRUE;
      }
    }
  }

  return inherited::processSoEvent(ev);
}

// *************************************************************************

// FIXME: get rid of this hack and make this file truly
// "generic". 20020109 mortene.
#ifndef __COIN_SOWIN__

// *************************************************************************

// Doc in superclass.
void
SoQtFullViewer::setComponentCursor(const SoQtCursor & cursor)
{
  // Overridden to apply the new cursor only for the rendering canvas
  // widget. Otherwise, the default SoQtComponent
  // setComponentCursor() method will set the cursor for the top-most
  // parent widget, which makes it affect all sub-widgets, like the
  // decorations stuff.

  SoQtComponent::setWidgetCursor(this->getGLWidget(), cursor);
}

// *************************************************************************

#endif // ! __COIN_SOWIN__

// ************************************************************************

#ifndef DOXYGEN_SKIP_THIS

SoGuiFullViewerP::SoGuiFullViewerP(SoQtFullViewer * owner)
{
  this->pub = owner;
}

SoGuiFullViewerP::~SoGuiFullViewerP()
{
}

SoQtPopupMenu *
SoGuiFullViewerP::setupStandardPopupMenu(void)
{
  SoQtPopupMenu * menu = SoQtPopupMenu::createInstance();

  menu->newMenu("rootmenu", ROOT_MENU);
  // FIXME: none of the So*-toolkits so far uses the rootmenu title to
  // set up a title string at the top of the root popupmenu. 20010810 mortene.
  menu->setMenuTitle(ROOT_MENU, this->popupmenutitle.getString());

#if 0 // OBSOLETED: this looks ugly and confusing for the user. 20010810 mortene.
  // Simple hack for a common / generic way of setting up a title for
  // the popupmenu.
  menu->newMenuItem("rootmenutitle", ROOT_MENU_TITLE);
  menu->setMenuItemTitle(ROOT_MENU_TITLE, this->popupmenutitle.getString());
  menu->addMenuItem(ROOT_MENU, ROOT_MENU_TITLE);
  menu->setMenuItemEnabled(ROOT_MENU_TITLE, FALSE);
  menu->addSeparator(ROOT_MENU);
#endif // OBSOLETED

  menu->newMenu("functionsmenu", FUNCTIONS_MENU);
  menu->setMenuTitle(FUNCTIONS_MENU, _("Functions"));
  menu->newMenu("drawstylesmenu", DRAWSTYLES_MENU);
  menu->setMenuTitle(DRAWSTYLES_MENU, _("Draw Styles"));
  menu->newMenu("stereomenu", STEREO_MENU);
  menu->setMenuTitle(STEREO_MENU, _("Stereo Viewing"));
  menu->newMenuItem("examining", EXAMINING_ITEM);
  menu->setMenuItemTitle(EXAMINING_ITEM, _("Viewing"));
  menu->newMenuItem("decoration", DECORATION_ITEM);
  menu->setMenuItemTitle(DECORATION_ITEM, _("Decorations"));
  menu->newMenuItem("headlight", HEADLIGHT_ITEM);
  menu->setMenuItemTitle(HEADLIGHT_ITEM, _("Headlight"));
  menu->newMenuItem("fullscreen", FULLSCREEN_ITEM);
  menu->setMenuItemTitle(FULLSCREEN_ITEM, _("Fullscreen"));

  menu->addMenu(ROOT_MENU, FUNCTIONS_MENU);
  menu->addMenu(ROOT_MENU, DRAWSTYLES_MENU);
  menu->addMenu(ROOT_MENU, STEREO_MENU);
  menu->addMenuItem(ROOT_MENU, EXAMINING_ITEM);
  menu->addMenuItem(ROOT_MENU, DECORATION_ITEM);
  menu->addMenuItem(ROOT_MENU, HEADLIGHT_ITEM);
  menu->addMenuItem(ROOT_MENU, FULLSCREEN_ITEM);

  menu->newMenuItem("home", HOME_ITEM);
  menu->setMenuItemTitle(HOME_ITEM, _("Home"));
  menu->newMenuItem("set_home", SET_HOME_ITEM);
  menu->setMenuItemTitle(SET_HOME_ITEM, _("Set Home"));
  menu->newMenuItem("view_all", VIEW_ALL_ITEM);
  menu->setMenuItemTitle(VIEW_ALL_ITEM, _("View All"));
  menu->newMenuItem("seek", SEEK_ITEM);
  menu->setMenuItemTitle(SEEK_ITEM, _("Seek"));

  menu->addMenuItem(FUNCTIONS_MENU, HOME_ITEM);
  menu->addMenuItem(FUNCTIONS_MENU, SET_HOME_ITEM);
  menu->addMenuItem(FUNCTIONS_MENU, VIEW_ALL_ITEM);
  menu->addMenuItem(FUNCTIONS_MENU, SEEK_ITEM);

  menu->newMenu("drawstylesstill", DRAWSTYLES_STILL_MENU);
  menu->setMenuTitle(DRAWSTYLES_STILL_MENU, _("Still Drawstyle"));

  menu->newMenuItem("as_is", AS_IS_ITEM);
  menu->setMenuItemTitle(AS_IS_ITEM, _("as is"));
  menu->newMenuItem("hidden_line", HIDDEN_LINE_ITEM);
  menu->setMenuItemTitle(HIDDEN_LINE_ITEM, _("hidden line"));
  menu->newMenuItem("wireframe_overlay", WIREFRAME_OVERLAY_ITEM);
  menu->setMenuItemTitle(WIREFRAME_OVERLAY_ITEM, _("wireframe overlay"));
  menu->newMenuItem("no_textures", NO_TEXTURE_ITEM);
  menu->setMenuItemTitle(NO_TEXTURE_ITEM, _("no texture"));
  menu->newMenuItem("low_resolution", LOW_RESOLUTION_ITEM);
  menu->setMenuItemTitle(LOW_RESOLUTION_ITEM, _("low resolution"));
  menu->newMenuItem("wireframe", WIREFRAME_ITEM);
  menu->setMenuItemTitle(WIREFRAME_ITEM, _("wireframe"));
  menu->newMenuItem("points", POINTS_ITEM);
  menu->setMenuItemTitle(POINTS_ITEM, _("points"));
  menu->newMenuItem("bounding_box", BOUNDING_BOX_ITEM);
  menu->setMenuItemTitle(BOUNDING_BOX_ITEM, _("bounding box (no depth)"));

  menu->newRadioGroup(STILL_GROUP);
  menu->addRadioGroupItem(STILL_GROUP, AS_IS_ITEM);
  menu->addRadioGroupItem(STILL_GROUP, HIDDEN_LINE_ITEM);
  menu->addRadioGroupItem(STILL_GROUP, WIREFRAME_OVERLAY_ITEM);
  menu->addRadioGroupItem(STILL_GROUP, NO_TEXTURE_ITEM);
  menu->addRadioGroupItem(STILL_GROUP, LOW_RESOLUTION_ITEM);
  menu->addRadioGroupItem(STILL_GROUP, WIREFRAME_ITEM);
  menu->addRadioGroupItem(STILL_GROUP, POINTS_ITEM);
  menu->addRadioGroupItem(STILL_GROUP, BOUNDING_BOX_ITEM);

  menu->addMenuItem(DRAWSTYLES_STILL_MENU, AS_IS_ITEM);
  menu->addMenuItem(DRAWSTYLES_STILL_MENU, HIDDEN_LINE_ITEM);
  menu->addMenuItem(DRAWSTYLES_STILL_MENU, WIREFRAME_OVERLAY_ITEM);
  menu->addMenuItem(DRAWSTYLES_STILL_MENU, NO_TEXTURE_ITEM);
  menu->addMenuItem(DRAWSTYLES_STILL_MENU, LOW_RESOLUTION_ITEM);
  menu->addMenuItem(DRAWSTYLES_STILL_MENU, WIREFRAME_ITEM);
  menu->addMenuItem(DRAWSTYLES_STILL_MENU, POINTS_ITEM);
  menu->addMenuItem(DRAWSTYLES_STILL_MENU, BOUNDING_BOX_ITEM);

  menu->newMenu("drawstylesanimation", DRAWSTYLES_ANIMATING_MENU);
  menu->setMenuTitle(DRAWSTYLES_ANIMATING_MENU, _("Animating Drawstyle"));

  menu->newMenuItem("move_same_as_still", MOVE_SAME_AS_STILL_ITEM);
  menu->setMenuItemTitle(MOVE_SAME_AS_STILL_ITEM, _("same as still"));
  menu->newMenuItem("move_no_texture", MOVE_NO_TEXTURE_ITEM);
  menu->setMenuItemTitle(MOVE_NO_TEXTURE_ITEM, _("no texture"));
  menu->newMenuItem("move_low_res", MOVE_LOW_RES_ITEM);
  menu->setMenuItemTitle(MOVE_LOW_RES_ITEM, _("low resolution"));
  menu->newMenuItem("move_wireframe", MOVE_WIREFRAME_ITEM);
  menu->setMenuItemTitle(MOVE_WIREFRAME_ITEM, _("wireframe"));
  menu->newMenuItem("move_low_res_wireframe", MOVE_LOW_RES_WIREFRAME_ITEM);
  menu->setMenuItemTitle(MOVE_LOW_RES_WIREFRAME_ITEM,
    _("low res wireframe (no depth)"));
  menu->newMenuItem("move_points", MOVE_POINTS_ITEM);
  menu->setMenuItemTitle(MOVE_POINTS_ITEM, _("points"));
  menu->newMenuItem("move_low_res_points", MOVE_LOW_RES_POINTS_ITEM);
  menu->setMenuItemTitle(MOVE_LOW_RES_POINTS_ITEM,
    _("low res points (no depth)"));
  menu->newMenuItem("move_bounding_box", MOVE_BOUNDING_BOX_ITEM);
  menu->setMenuItemTitle(MOVE_BOUNDING_BOX_ITEM, _("bounding box (no depth)"));

  menu->newRadioGroup(MOVE_GROUP);
  menu->addRadioGroupItem(MOVE_GROUP, MOVE_SAME_AS_STILL_ITEM);
  menu->addRadioGroupItem(MOVE_GROUP, MOVE_NO_TEXTURE_ITEM);
  menu->addRadioGroupItem(MOVE_GROUP, MOVE_LOW_RES_ITEM);
  menu->addRadioGroupItem(MOVE_GROUP, MOVE_WIREFRAME_ITEM);
  menu->addRadioGroupItem(MOVE_GROUP, MOVE_LOW_RES_WIREFRAME_ITEM);
  menu->addRadioGroupItem(MOVE_GROUP, MOVE_POINTS_ITEM);
  menu->addRadioGroupItem(MOVE_GROUP, MOVE_LOW_RES_POINTS_ITEM);
  menu->addRadioGroupItem(MOVE_GROUP, MOVE_BOUNDING_BOX_ITEM);

  menu->addMenuItem(DRAWSTYLES_ANIMATING_MENU, MOVE_SAME_AS_STILL_ITEM);
  menu->addMenuItem(DRAWSTYLES_ANIMATING_MENU, MOVE_NO_TEXTURE_ITEM);
  menu->addMenuItem(DRAWSTYLES_ANIMATING_MENU, MOVE_LOW_RES_ITEM);
  menu->addMenuItem(DRAWSTYLES_ANIMATING_MENU, MOVE_WIREFRAME_ITEM);
  menu->addMenuItem(DRAWSTYLES_ANIMATING_MENU, MOVE_LOW_RES_WIREFRAME_ITEM);
  menu->addMenuItem(DRAWSTYLES_ANIMATING_MENU, MOVE_POINTS_ITEM);
  menu->addMenuItem(DRAWSTYLES_ANIMATING_MENU, MOVE_LOW_RES_POINTS_ITEM);
  menu->addMenuItem(DRAWSTYLES_ANIMATING_MENU, MOVE_BOUNDING_BOX_ITEM);

  menu->newMenu("transparencytype", TRANSPARENCY_TYPE_MENU);
  menu->setMenuTitle(TRANSPARENCY_TYPE_MENU, _("Transparency Type"));
  menu->newRadioGroup(TRANSPARENCY_GROUP);

  { // Fill in menu items in radiomenu with transparency selections.

    struct menutransparencyitem {
      const char * name, * title;
      int id;
    };

    struct menutransparencyitem items[] = {
#ifdef __COIN__
      { "none", _("none"), NONE_TRANSPARENCY_ITEM },
#endif // __COIN__
      { "screen_door", _("screen door"), SCREEN_DOOR_TRANSPARENCY_ITEM },
      { "add", _("add"), ADD_TRANSPARENCY_ITEM },
      { "delayed_add", _("delayed add"), DELAYED_ADD_TRANSPARENCY_ITEM },
      { "sorted_object_add", _("sorted object add"), SORTED_OBJECT_ADD_TRANSPARENCY_ITEM },
      { "blend", _("blend"), BLEND_TRANSPARENCY_ITEM },
      { "delayed_blend", _("delayed blend"), DELAYED_BLEND_TRANSPARENCY_ITEM },
      { "sorted_object_blend", _("sorted object blend"), SORTED_OBJECT_BLEND_TRANSPARENCY_ITEM }
#ifdef __COIN__ // Coin extensions
      ,
      { "sorted_object_sorted_triangle_add", _("sorted object sorted triangle add"), SORTED_OBJECT_SORTED_TRIANGLE_ADD_TRANSPARENCY_ITEM },
      { "sorted_object_sorted_triangle_blend", _("sorted object sorted triangle blend"), SORTED_OBJECT_SORTED_TRIANGLE_BLEND_TRANSPARENCY_ITEM }
#endif // __COIN__
#ifdef HAVE_SORTED_LAYERS_BLEND
      , { "sorted_layers_blend", _("sorted layers blend"), SORTED_LAYERS_BLEND_ITEM }
#endif // HAVE_SORTED_LAYERS_BLEND
    };

    int nritems = sizeof(items) / sizeof(struct menutransparencyitem);
    for (int i = 0; i < nritems; i++) {
      menu->newMenuItem(items[i].name, items[i].id);
      menu->setMenuItemTitle(items[i].id, items[i].title);
      menu->addRadioGroupItem(TRANSPARENCY_GROUP, items[i].id);
      menu->addMenuItem(TRANSPARENCY_TYPE_MENU, items[i].id);
    }
  }

  menu->newMenuItem("stereooff", STEREO_OFF_ITEM);
  menu->newMenuItem("stereoredcyan", STEREO_ANAGLYPH_ITEM);
  menu->newMenuItem("stereoquadbuffer", STEREO_QUADBUFFER_ITEM);
  menu->setMenuItemTitle(STEREO_OFF_ITEM, _("Off"));
  menu->setMenuItemTitle(STEREO_ANAGLYPH_ITEM, _("Red/Cyan Anaglyph"));
  menu->setMenuItemTitle(STEREO_QUADBUFFER_ITEM, _("Quad buffer"));

  menu->newMenuItem("stereointerleavedrows", STEREO_INTERLEAVED_ROWS_ITEM);
  menu->setMenuItemTitle(STEREO_INTERLEAVED_ROWS_ITEM, _("Interleaved Rows"));
  menu->newMenuItem("stereointerleavedcolumns", STEREO_INTERLEAVED_COLUMNS_ITEM);
  menu->setMenuItemTitle(STEREO_INTERLEAVED_COLUMNS_ITEM, _("Interleaved Columns"));

  menu->newRadioGroup(STEREO_GROUP);
  menu->addRadioGroupItem(STEREO_GROUP, STEREO_OFF_ITEM);
  menu->addRadioGroupItem(STEREO_GROUP, STEREO_ANAGLYPH_ITEM);
  menu->addRadioGroupItem(STEREO_GROUP, STEREO_QUADBUFFER_ITEM);
  menu->addRadioGroupItem(STEREO_GROUP, STEREO_INTERLEAVED_ROWS_ITEM);
  menu->addRadioGroupItem(STEREO_GROUP, STEREO_INTERLEAVED_COLUMNS_ITEM);

  menu->addMenuItem(STEREO_MENU, STEREO_OFF_ITEM);
  menu->addMenuItem(STEREO_MENU, STEREO_ANAGLYPH_ITEM);
  menu->addMenuItem(STEREO_MENU, STEREO_QUADBUFFER_ITEM);
  menu->addMenuItem(STEREO_MENU, STEREO_INTERLEAVED_ROWS_ITEM);
  menu->addMenuItem(STEREO_MENU, STEREO_INTERLEAVED_COLUMNS_ITEM);

  menu->newMenu("renderbuffertype", RENDER_BUFFER_TYPE_MENU);
  menu->setMenuTitle(RENDER_BUFFER_TYPE_MENU, _("Render Buffer Type"));

  menu->newMenuItem("single_buffer", SINGLE_BUFFER_ITEM);
  menu->setMenuItemTitle(SINGLE_BUFFER_ITEM, _("single"));
  menu->newMenuItem("double_buffer", DOUBLE_BUFFER_ITEM);
  menu->setMenuItemTitle(DOUBLE_BUFFER_ITEM, _("double"));
  menu->newMenuItem("interactive_buffer", INTERACTIVE_BUFFER_ITEM);
  menu->setMenuItemTitle(INTERACTIVE_BUFFER_ITEM, _("interactive"));

  menu->newRadioGroup(BUFFER_GROUP);
  menu->addRadioGroupItem(BUFFER_GROUP, SINGLE_BUFFER_ITEM);
  menu->addRadioGroupItem(BUFFER_GROUP, DOUBLE_BUFFER_ITEM);
  menu->addRadioGroupItem(BUFFER_GROUP, INTERACTIVE_BUFFER_ITEM);

  menu->addMenuItem(RENDER_BUFFER_TYPE_MENU, SINGLE_BUFFER_ITEM);
  menu->addMenuItem(RENDER_BUFFER_TYPE_MENU, DOUBLE_BUFFER_ITEM);
  menu->addMenuItem(RENDER_BUFFER_TYPE_MENU, INTERACTIVE_BUFFER_ITEM);

  menu->addMenu(DRAWSTYLES_MENU, DRAWSTYLES_STILL_MENU);
  menu->addMenu(DRAWSTYLES_MENU, DRAWSTYLES_ANIMATING_MENU);
  menu->addMenu(DRAWSTYLES_MENU, TRANSPARENCY_TYPE_MENU);
  menu->addMenu(DRAWSTYLES_MENU, RENDER_BUFFER_TYPE_MENU);

  int toggle;
  toggle = menu->newRadioGroup();
  menu->addRadioGroupItem(toggle, EXAMINING_ITEM);
  toggle = menu->newRadioGroup();
  menu->addRadioGroupItem(toggle, DECORATION_ITEM);
  toggle = menu->newRadioGroup();
  menu->addRadioGroupItem(toggle, HEADLIGHT_ITEM);
  toggle = menu->newRadioGroup();
  menu->addRadioGroupItem(toggle, FULLSCREEN_ITEM);

  menu->addMenuSelectionCallback(SoGuiFullViewerP::menuSelectionCallback,
                                 (void *) this);

  PUBLIC(this)->prefmenu = menu;
  return menu;
}

// ************************************************************************

void
SoGuiFullViewerP::prepareMenu(SoQtPopupMenu * menu)
{
  //// Misc. //////////////////////////////////////////////////////////
  menu->setMenuItemMarked(DECORATION_ITEM, PUBLIC(this)->isDecoration());
  menu->setMenuItemMarked(EXAMINING_ITEM, PUBLIC(this)->isViewing());
  menu->setMenuItemMarked(HEADLIGHT_ITEM, PUBLIC(this)->isHeadlight());
  menu->setMenuItemMarked(FULLSCREEN_ITEM, PUBLIC(this)->isFullScreen());

  //// Basic drawstyles. //////////////////////////////////////////////
  this->setDrawStyleMenuActivation(SoQtFullViewer::STILL,
                                   PUBLIC(this)->getDrawStyle(SoQtFullViewer::STILL));
  this->setDrawStyleMenuActivation(SoQtFullViewer::INTERACTIVE,
                                   PUBLIC(this)->getDrawStyle(SoQtFullViewer::INTERACTIVE));

  //// Transparency setting. //////////////////////////////////////////
  switch (PUBLIC(this)->getTransparencyType()) {
  case SoGLRenderAction::SCREEN_DOOR:
    menu->setMenuItemMarked(SCREEN_DOOR_TRANSPARENCY_ITEM, TRUE);
    break;
  case SoGLRenderAction::ADD:
    menu->setMenuItemMarked(ADD_TRANSPARENCY_ITEM, TRUE);
    break;
  case SoGLRenderAction::DELAYED_ADD:
    menu->setMenuItemMarked(DELAYED_ADD_TRANSPARENCY_ITEM, TRUE);
    break;
  case SoGLRenderAction::SORTED_OBJECT_ADD:
    menu->setMenuItemMarked(SORTED_OBJECT_ADD_TRANSPARENCY_ITEM, TRUE);
    break;
  case SoGLRenderAction::BLEND:
    menu->setMenuItemMarked(BLEND_TRANSPARENCY_ITEM, TRUE);
    break;
  case SoGLRenderAction::DELAYED_BLEND:
    menu->setMenuItemMarked(DELAYED_BLEND_TRANSPARENCY_ITEM, TRUE);
    break;
  case SoGLRenderAction::SORTED_OBJECT_BLEND:
    menu->setMenuItemMarked(SORTED_OBJECT_BLEND_TRANSPARENCY_ITEM, TRUE);
    break;
#ifdef __COIN__  // Coin extensions
  case SoGLRenderAction::NONE:
    menu->setMenuItemMarked(NONE_TRANSPARENCY_ITEM, TRUE);
    break;
  case SoGLRenderAction::SORTED_OBJECT_SORTED_TRIANGLE_ADD:
    menu->setMenuItemMarked(SORTED_OBJECT_SORTED_TRIANGLE_ADD_TRANSPARENCY_ITEM, TRUE);
    break;
  case SoGLRenderAction::SORTED_OBJECT_SORTED_TRIANGLE_BLEND:
    menu->setMenuItemMarked(SORTED_OBJECT_SORTED_TRIANGLE_BLEND_TRANSPARENCY_ITEM, TRUE);
    break;
#endif // __COIN__
#ifdef HAVE_SORTED_LAYERS_BLEND
  case SoGLRenderAction::SORTED_LAYERS_BLEND:
    menu->setMenuItemMarked(SORTED_LAYERS_BLEND_ITEM, TRUE);
    break;
#endif // HAVE_SORTED_LAYERS_BLEND
  default:
#if SOQT_DEBUG
    SoDebugError::postInfo("SoGuiFullViewerP::prepareMenu",
                           "Unknown transparency type");
#endif // SOQT_DEBUG
    break;
  }

  //// Stereo viewing. ////////////////////////////////////////////////

  const SoQtViewer::StereoType type = PUBLIC(this)->getStereoType();
  switch (type) {
  case SoQtViewer::STEREO_NONE:
    menu->setMenuItemMarked(STEREO_OFF_ITEM, TRUE);
    break;
  case SoQtViewer::STEREO_ANAGLYPH:
    menu->setMenuItemMarked(STEREO_ANAGLYPH_ITEM, TRUE);
    break;
  case SoQtViewer::STEREO_QUADBUFFER:
    menu->setMenuItemMarked(STEREO_QUADBUFFER_ITEM, TRUE);
    break;
  case SoQtViewer::STEREO_INTERLEAVED_ROWS:
    menu->setMenuItemMarked(STEREO_INTERLEAVED_ROWS_ITEM, TRUE);
    break;
  case SoQtViewer::STEREO_INTERLEAVED_COLUMNS:
    menu->setMenuItemMarked(STEREO_INTERLEAVED_COLUMNS_ITEM, TRUE);
    break;
  default:
    assert(FALSE); break;
  }

  //// GL canvas settings. ////////////////////////////////////////////
  switch (PUBLIC(this)->getBufferingType()) {
  case SoQtViewer::BUFFER_SINGLE:
    menu->setMenuItemMarked(SINGLE_BUFFER_ITEM, TRUE);
    break;
  case SoQtViewer::BUFFER_DOUBLE:
    menu->setMenuItemMarked(DOUBLE_BUFFER_ITEM, TRUE);
    break;
  case SoQtViewer::BUFFER_INTERACTIVE:
    menu->setMenuItemMarked(INTERACTIVE_BUFFER_ITEM, TRUE);
    break;
  default:
#if SOQT_DEBUG
    SoDebugError::postInfo("SoGuiFullViewerP::prepareMenu",
                           "Unknown buffer type");
#endif // SOQT_DEBUG
    break;
  }
}

// ************************************************************************

void
SoGuiFullViewerP::menuSelection(int menuitemid)
{
  SbBool ok;

  switch (menuitemid) {
  case -1:
    // means no item was selected
#if SOQT_DEBUG
    SoDebugError::postInfo("SoGuiFullViewerP::menuSelection",
                           "-1 not appropriate on callback usage");
#endif // SOQT_DEBUG
    break;

  case EXAMINING_ITEM:
    PUBLIC(this)->setViewing(PUBLIC(this)->isViewing() ? FALSE : TRUE);
    break;
  case DECORATION_ITEM:
    PUBLIC(this)->setDecoration(PUBLIC(this)->isDecoration() ? FALSE : TRUE);
    break;
  case HEADLIGHT_ITEM:
    PUBLIC(this)->setHeadlight(PUBLIC(this)->isHeadlight() ? FALSE : TRUE);
    break;
  case FULLSCREEN_ITEM:
    (void)PUBLIC(this)->setFullScreen(PUBLIC(this)->isFullScreen() ? FALSE : TRUE);
    break;

  case HOME_ITEM:
    PUBLIC(this)->resetToHomePosition();
    break;
  case SET_HOME_ITEM:
    PUBLIC(this)->saveHomePosition();
    break;
  case VIEW_ALL_ITEM:
    PUBLIC(this)->viewAll();
    break;
  case SEEK_ITEM:
    ((SoQtFullViewerP *)this)->seekbuttonClicked();
    break;

  case AS_IS_ITEM:
  case HIDDEN_LINE_ITEM:
  case WIREFRAME_OVERLAY_ITEM:
  case NO_TEXTURE_ITEM:
  case LOW_RESOLUTION_ITEM:
  case WIREFRAME_ITEM:
  case POINTS_ITEM:
  case BOUNDING_BOX_ITEM:
    this->drawstyleActivated(menuitemid);
    break;

  case MOVE_SAME_AS_STILL_ITEM:
  case MOVE_NO_TEXTURE_ITEM:
  case MOVE_LOW_RES_ITEM:
  case MOVE_WIREFRAME_ITEM:
  case MOVE_LOW_RES_WIREFRAME_ITEM:
  case MOVE_POINTS_ITEM:
  case MOVE_LOW_RES_POINTS_ITEM:
  case MOVE_BOUNDING_BOX_ITEM:
    this->drawstyleActivated(menuitemid);
    break;

  case SCREEN_DOOR_TRANSPARENCY_ITEM:
  case ADD_TRANSPARENCY_ITEM:
  case DELAYED_ADD_TRANSPARENCY_ITEM:
  case SORTED_OBJECT_ADD_TRANSPARENCY_ITEM:
  case BLEND_TRANSPARENCY_ITEM:
  case DELAYED_BLEND_TRANSPARENCY_ITEM:
  case SORTED_OBJECT_BLEND_TRANSPARENCY_ITEM:
  case SORTED_OBJECT_SORTED_TRIANGLE_ADD_TRANSPARENCY_ITEM:
  case SORTED_OBJECT_SORTED_TRIANGLE_BLEND_TRANSPARENCY_ITEM:
  case NONE_TRANSPARENCY_ITEM:
  case SORTED_LAYERS_BLEND_ITEM: // define test is not needed. This enum is always defined
    this->drawstyleActivated(menuitemid);
    PUBLIC(this)->scheduleRedraw();
    break;

  case SINGLE_BUFFER_ITEM:
  case DOUBLE_BUFFER_ITEM:
  case INTERACTIVE_BUFFER_ITEM:
    this->drawstyleActivated(menuitemid);
    break;

  case STEREO_OFF_ITEM:
    ok = PUBLIC(this)->setStereoType(SoQtViewer::STEREO_NONE);
    assert(ok);
    break;
  case STEREO_ANAGLYPH_ITEM:
    ok = PUBLIC(this)->setStereoType(SoQtViewer::STEREO_ANAGLYPH);
    assert(ok && "anaglyph stereo should always be possible");
    break;
  case STEREO_QUADBUFFER_ITEM:
    ok = PUBLIC(this)->setStereoType(SoQtViewer::STEREO_QUADBUFFER);
    if (!ok) { PUBLIC(this)->setStereoType(SoQtViewer::STEREO_NONE); }
    break;
  case STEREO_INTERLEAVED_ROWS_ITEM:
    ok = PUBLIC(this)->setStereoType(SoQtViewer::STEREO_INTERLEAVED_ROWS);
    if (!ok) { PUBLIC(this)->setStereoType(SoQtViewer::STEREO_NONE); }
    break;
  case STEREO_INTERLEAVED_COLUMNS_ITEM:
    ok = PUBLIC(this)->setStereoType(SoQtViewer::STEREO_INTERLEAVED_COLUMNS);
    if (!ok) { PUBLIC(this)->setStereoType(SoQtViewer::STEREO_NONE); }
    break;

  default:
    SoDebugError::postInfo("SoGuiFullViewerP::menuSelection",
                           "popup menu handling for item %d is not implemented", 
                           menuitemid);
    break;
  }
}


// ************************************************************************

void
SoGuiFullViewerP::menuSelectionCallback(int menuitemid,
                                        void * userdata)
{
  SoGuiFullViewerP * viewer = (SoGuiFullViewerP *) userdata;
  viewer->menuSelection(menuitemid);
}

// ************************************************************************

void
SoGuiFullViewerP::setDrawStyleMenuActivation(SoQtViewer::DrawType type,
                                             SoQtViewer::DrawStyle value)
{
  assert(PUBLIC(this)->prefmenu != NULL);

  switch (type) {
  case SoQtViewer::STILL:
    switch (value) {
    case SoQtViewer::VIEW_AS_IS:
      PUBLIC(this)->prefmenu->setMenuItemMarked(AS_IS_ITEM, TRUE);
      break;
    case SoQtViewer::VIEW_HIDDEN_LINE:
      PUBLIC(this)->prefmenu->setMenuItemMarked(HIDDEN_LINE_ITEM, TRUE);
      break;
    case SoQtViewer::VIEW_WIREFRAME_OVERLAY:
      PUBLIC(this)->prefmenu->setMenuItemMarked(WIREFRAME_OVERLAY_ITEM, TRUE);
      break;
    case SoQtViewer::VIEW_NO_TEXTURE:
      PUBLIC(this)->prefmenu->setMenuItemMarked(NO_TEXTURE_ITEM, TRUE);
      break;
    case SoQtViewer::VIEW_LOW_COMPLEXITY:
      PUBLIC(this)->prefmenu->setMenuItemMarked(LOW_RESOLUTION_ITEM, TRUE);
      break;
    case SoQtViewer::VIEW_LOW_RES_LINE:
#if SOQT_DEBUG
      SoDebugError::postWarning("SoQtFullViewer::setDrawStyleMenuActivation",
                                "Use VIEW_LINE, not VIEW_LOW_RES_LINE for the STILL drawstyle.");
#endif // debug
    case SoQtViewer::VIEW_LINE:
      PUBLIC(this)->prefmenu->setMenuItemMarked(WIREFRAME_ITEM, TRUE);
      break;
    case SoQtViewer::VIEW_LOW_RES_POINT:
#if SOQT_DEBUG
      SoDebugError::postWarning("SoQtFullViewer::setDrawStyleMenuActivation",
                                "Use VIEW_POINT, not VIEW_LOW_RES_POINT for the STILL drawstyle.");
#endif // debug
    case SoQtViewer::VIEW_POINT:
      PUBLIC(this)->prefmenu->setMenuItemMarked(POINTS_ITEM, TRUE);
      break;
    case SoQtViewer::VIEW_BBOX:
      PUBLIC(this)->prefmenu->setMenuItemMarked(BOUNDING_BOX_ITEM, TRUE);
      break;
    default:
#if SOQT_DEBUG
      SoDebugError::postWarning("SoQtFullViewer::setDrawStyleMenuActivation",
                                "Unsupporter still-drawstyle");
#endif // debug
      break;
    }
    break;

  case SoQtViewer::INTERACTIVE:
    switch (value) {
    case SoQtViewer::VIEW_SAME_AS_STILL:
      PUBLIC(this)->prefmenu->setMenuItemMarked(MOVE_SAME_AS_STILL_ITEM, TRUE);
      break;
    case SoQtViewer::VIEW_NO_TEXTURE:
      PUBLIC(this)->prefmenu->setMenuItemMarked(MOVE_NO_TEXTURE_ITEM, TRUE);
      break;
    case SoQtViewer::VIEW_LOW_COMPLEXITY:
      PUBLIC(this)->prefmenu->setMenuItemMarked(MOVE_LOW_RES_ITEM, TRUE);
      break;
    case SoQtViewer::VIEW_LINE:
      PUBLIC(this)->prefmenu->setMenuItemMarked(MOVE_WIREFRAME_ITEM, TRUE);
      break;
    case SoQtViewer::VIEW_LOW_RES_LINE:
      PUBLIC(this)->prefmenu->setMenuItemMarked(MOVE_LOW_RES_WIREFRAME_ITEM, TRUE);
      break;
    case SoQtViewer::VIEW_POINT:
      PUBLIC(this)->prefmenu->setMenuItemMarked(MOVE_POINTS_ITEM, TRUE);
      break;
    case SoQtViewer::VIEW_LOW_RES_POINT:
      PUBLIC(this)->prefmenu->setMenuItemMarked(MOVE_LOW_RES_POINTS_ITEM, TRUE);
      break;
    case SoQtViewer::VIEW_BBOX:
      PUBLIC(this)->prefmenu->setMenuItemMarked(MOVE_BOUNDING_BOX_ITEM, TRUE);
      break;
    default:
#if SOQT_DEBUG
      SoDebugError::postWarning("SoQtFullViewer::setDrawStyleMenuActivation",
                                "Unsupporter interactive drawstyle");
#endif // debug
      break;
    }
    break;

  default:
#if SOQT_DEBUG
    SoDebugError::postWarning("SoQtFullViewer::setDrawStyleMenuActivation",
                              "Unsupporter drawstyle type");
#endif // debug
    break;
  }
}

// ************************************************************************

void
SoGuiFullViewerP::drawstyleActivated(int menuitemid)
{
  switch (menuitemid) {
  case SINGLE_BUFFER_ITEM:
    PUBLIC(this)->setBufferingType(SoQtViewer::BUFFER_SINGLE);
    return;
  case DOUBLE_BUFFER_ITEM:
    PUBLIC(this)->setBufferingType(SoQtViewer::BUFFER_DOUBLE);
    return;
  case INTERACTIVE_BUFFER_ITEM:
    PUBLIC(this)->setBufferingType(SoQtViewer::BUFFER_INTERACTIVE);
    return;
  default:
    break;
  }

  // FIXME: should perhaps override transparency type to be screendoor
  // if we detect that the OpenGL canvas has 0 alpha bits available?
  // 20030626 mortene.
  switch (menuitemid) {
  case SCREEN_DOOR_TRANSPARENCY_ITEM:
    PUBLIC(this)->setTransparencyType(SoGLRenderAction::SCREEN_DOOR);
    return;
  case ADD_TRANSPARENCY_ITEM:
    PUBLIC(this)->setTransparencyType(SoGLRenderAction::ADD);
    return;
  case DELAYED_ADD_TRANSPARENCY_ITEM:
    PUBLIC(this)->setTransparencyType(SoGLRenderAction::DELAYED_ADD);
    return;
  case SORTED_OBJECT_ADD_TRANSPARENCY_ITEM:
    PUBLIC(this)->setTransparencyType(SoGLRenderAction::SORTED_OBJECT_ADD);
    return;
  case BLEND_TRANSPARENCY_ITEM:
    PUBLIC(this)->setTransparencyType(SoGLRenderAction::BLEND);
    return;
  case DELAYED_BLEND_TRANSPARENCY_ITEM:
    PUBLIC(this)->setTransparencyType(SoGLRenderAction::DELAYED_BLEND);
    return;
  case SORTED_OBJECT_BLEND_TRANSPARENCY_ITEM:
    PUBLIC(this)->setTransparencyType(SoGLRenderAction::SORTED_OBJECT_BLEND);
    return;
#ifdef __COIN__ // Coin extensions
  case NONE_TRANSPARENCY_ITEM:
    PUBLIC(this)->setTransparencyType(SoGLRenderAction::NONE);
    return;
  case SORTED_OBJECT_SORTED_TRIANGLE_ADD_TRANSPARENCY_ITEM:
    PUBLIC(this)->setTransparencyType(SoGLRenderAction::SORTED_OBJECT_SORTED_TRIANGLE_ADD);
    return;
  case SORTED_OBJECT_SORTED_TRIANGLE_BLEND_TRANSPARENCY_ITEM:
    PUBLIC(this)->setTransparencyType(SoGLRenderAction::SORTED_OBJECT_SORTED_TRIANGLE_BLEND);
    return;
#endif // __COIN__
#ifdef HAVE_SORTED_LAYERS_BLEND
  case SORTED_LAYERS_BLEND_ITEM:
    PUBLIC(this)->setTransparencyType(SoGLRenderAction::SORTED_LAYERS_BLEND);
    return;
#endif // HAVE_SORTED_LAYERS_BLEND
  default:
    // some other menu item, just continue
    break;
  }

  SoQtViewer::DrawStyle val = SoQtViewer::VIEW_AS_IS;
  switch (menuitemid) {
  case AS_IS_ITEM:
    val = SoQtViewer::VIEW_AS_IS;
    break;
  case HIDDEN_LINE_ITEM:
    val = SoQtViewer::VIEW_HIDDEN_LINE;
    break;
  case WIREFRAME_OVERLAY_ITEM:
    val = SoQtViewer::VIEW_WIREFRAME_OVERLAY;
    break;
  case NO_TEXTURE_ITEM:
    val = SoQtViewer::VIEW_NO_TEXTURE;
    break;
  case LOW_RESOLUTION_ITEM:
    val = SoQtViewer::VIEW_LOW_COMPLEXITY;
    break;
  case WIREFRAME_ITEM:
    val = SoQtViewer::VIEW_LINE;
    break;
  case POINTS_ITEM:
    val = SoQtViewer::VIEW_POINT;
    break;
  case BOUNDING_BOX_ITEM:
    val = SoQtViewer::VIEW_BBOX;
    break;

  case MOVE_SAME_AS_STILL_ITEM:
    val = SoQtViewer::VIEW_SAME_AS_STILL;
    break;
  case MOVE_NO_TEXTURE_ITEM:
    val = SoQtViewer::VIEW_NO_TEXTURE;
    break;
  case MOVE_LOW_RES_ITEM:
    val = SoQtViewer::VIEW_LOW_COMPLEXITY;
    break;
  case MOVE_WIREFRAME_ITEM:
    val = SoQtViewer::VIEW_LINE;
    break;
  case MOVE_LOW_RES_WIREFRAME_ITEM:
    val = SoQtViewer::VIEW_LOW_RES_LINE;
    break;
  case MOVE_POINTS_ITEM:
    val = SoQtViewer::VIEW_POINT;
    break;
  case MOVE_LOW_RES_POINTS_ITEM:
    val = SoQtViewer::VIEW_LOW_RES_POINT;
    break;
  case MOVE_BOUNDING_BOX_ITEM:
    val = SoQtViewer::VIEW_BBOX;
    break;

  default:
    assert(0);
    break;
  }

  SoQtViewer::DrawType type = SoQtViewer::STILL;

  switch (menuitemid) {
  case AS_IS_ITEM:
  case HIDDEN_LINE_ITEM:
  case WIREFRAME_OVERLAY_ITEM:
  case NO_TEXTURE_ITEM:
  case LOW_RESOLUTION_ITEM:
  case WIREFRAME_ITEM:
  case POINTS_ITEM:
  case BOUNDING_BOX_ITEM:
    type = SoQtViewer::STILL;
    break;

  case MOVE_SAME_AS_STILL_ITEM:
  case MOVE_NO_TEXTURE_ITEM:
  case MOVE_LOW_RES_ITEM:
  case MOVE_WIREFRAME_ITEM:
  case MOVE_LOW_RES_WIREFRAME_ITEM:
  case MOVE_POINTS_ITEM:
  case MOVE_LOW_RES_POINTS_ITEM:
  case MOVE_BOUNDING_BOX_ITEM:
    type = SoQtViewer::INTERACTIVE;
    break;

  default:
    assert(0);
    break;
  }

  PUBLIC(this)->setDrawStyle(type, val);
}

// ************************************************************************

// Move camera parallel with the plane orthogonal to the camera
// direction vector.
//
// Used from both SoGuiPlaneViewer and SoGuiExaminerViewer.
// Implemented in the SoGuiFullViewer private class to collect common
// code.
void
SoGuiFullViewerP::pan(SoCamera * cam,
                      float aspectratio, const SbPlane & panningplane,
                      const SbVec2f & currpos, const SbVec2f & prevpos)
{
  if (cam == NULL) return; // can happen for empty scenegraph
  if (currpos == prevpos) return; // useless invocation

#if SOQT_DEBUG && 0
  SoDebugError::postInfo("SoGuiFullViewerP::pan",
                         "was(%.3g, %.3g) -> now(%.3g, %.3g)",
                         prevpos[0], prevpos[1], currpos[0], currpos[1]);
#endif // SOQT_DEBUG

  // Find projection points for the last and current mouse coordinates.
  SbViewVolume vv = cam->getViewVolume(aspectratio);
  SbLine line;
  vv.projectPointToLine(currpos, line);
  SbVec3f current_planept;
  panningplane.intersect(line, current_planept);
  vv.projectPointToLine(prevpos, line);
  SbVec3f old_planept;
  panningplane.intersect(line, old_planept);

  // Reposition camera according to the vector difference between the
  // projected points.
  cam->position = cam->position.getValue() - (current_planept - old_planept);
}

// *************************************************************************

// Dependent on the camera type this will either shrink or expand the
// height of the viewport (orthogonal camera) or move the camera
// closer or further away from the focal point in the scene.
//
// Used from both SoGuiPlaneViewer and SoGuiExaminerViewer.
// Implemented in the SoGuiFullViewer private class to collect common
// code.
void
SoGuiFullViewerP::zoom(SoCamera * cam, const float diffvalue)
{
  if (cam == NULL) return; // can happen for empty scenegraph
  SoType t = cam->getTypeId();
  SbName tname = t.getName();

  // This will be in the range of <0, ->>.
  float multiplicator = float(exp(diffvalue));

  if (t.isDerivedFrom(SoOrthographicCamera::getClassTypeId())) {

    // Since there's no perspective, "zooming" in the original sense
    // of the word won't have any visible effect. So we just increase
    // or decrease the field-of-view values of the camera instead, to
    // "shrink" the projection size of the model / scene.
    SoOrthographicCamera * oc = (SoOrthographicCamera *)cam;
    oc->height = oc->height.getValue() * multiplicator;

  }
  else {
    // FrustumCamera can be found in the SmallChange CVS module (it's
    // a camera that lets you specify (for instance) an off-center
    // frustum (similar to glFrustum())
    if (!t.isDerivedFrom(SoPerspectiveCamera::getClassTypeId()) &&
        tname != "FrustumCamera") {
      static SbBool first = TRUE;
      if (first) {
        SoDebugError::postWarning("SoGuiFullViewerP::zoom",
                                  "Unknown camera type, "
                                  "will zoom by moving position, but this might not be correct.");
        first = FALSE;
      }
    }
    
    const float oldfocaldist = cam->focalDistance.getValue();
    const float newfocaldist = oldfocaldist * multiplicator;

    SbVec3f direction;
    cam->orientation.getValue().multVec(SbVec3f(0, 0, -1), direction);

    const SbVec3f oldpos = cam->position.getValue();
    const SbVec3f newpos = oldpos + (newfocaldist - oldfocaldist) * -direction;

    // This catches a rather common user interface "buglet": if the
    // user zooms the camera out to a distance from origo larger than
    // what we still can safely do floating point calculations on
    // (i.e. without getting NaN or Inf values), the faulty floating
    // point values will propagate until we start to get debug error
    // messages and eventually an assert failure from core Coin code.
    //
    // With the below bounds check, this problem is avoided.
    //
    // (But note that we depend on the input argument ''diffvalue'' to
    // be small enough that zooming happens gradually. Ideally, we
    // should also check distorigo with isinf() and isnan() (or
    // inversely; isinfite()), but those only became standardized with
    // C99.)
    const float distorigo = newpos.length();
    // sqrt(FLT_MAX) == ~ 1e+19, which should be both safe for further
    // calculations and ok for the end-user and app-programmer.
    if (distorigo > float(sqrt(FLT_MAX))) {
#if SOQT_DEBUG && 0 // debug
      SoDebugError::postWarning("SoGuiFullViewerP::zoom",
                                "zoomed too far (distance to origo==%f (%e))",
                                distorigo, distorigo);
#endif // debug
    }
    else {
      cam->position = newpos;
      cam->focalDistance = newfocaldist;
    }
  }
}

// ************************************************************************

#endif // DOXYGEN_SKIP_THIS

#undef PRIVATE
#undef PUBLIC

