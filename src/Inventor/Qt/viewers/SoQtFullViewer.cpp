/**************************************************************************
 *
 *  This file is part of the Coin SoQt GUI binding library.
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License version
 *  2.1 as published by the Free Software Foundation.  See the file
 *  LICENSE.LGPL at the root directory of the distribution for all the
 *  details.
 *
 *  If you want to use Coin SoQt for applications not compatible with the
 *  LGPL, please contact SIM to acquire a Professional Edition License.
 *
 *  Systems in Motion, Prof Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
 **************************************************************************/

#if SOQT_DEBUG
static const char rcsid[] =
  "$Id$";
#endif

#include <qpushbutton.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qpixmap.h>
#include <qlineedit.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qframe.h>
#include <qslider.h>
#include <qcheckbox.h>
// FIXME: get rid of this before 1.0 release (convert everything to Qt
// version 2.x API). 19990630 mortene.
#if QT_VERSION >= 200
#include <q1xcompatibility.h>
#endif // Qt v2.x

#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/errors/SoDebugError.h>

#include <soqtdefs.h>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/widgets/SoQtThumbWheel.h>
#include <Inventor/Qt/widgets/SoAnyPopupMenu.h>
#include <Inventor/Qt/viewers/SoAnyFullViewer.h>
#include <Inventor/Qt/viewers/SoQtFullViewer.h>

// Button icons.
#include <Inventor/Qt/common/pixmaps/pick.xpm>
#include <Inventor/Qt/common/pixmaps/view.xpm>
#include <Inventor/Qt/common/pixmaps/help.xpm>
#include <Inventor/Qt/common/pixmaps/home.xpm>
#include <Inventor/Qt/common/pixmaps/set_home.xpm>
#include <Inventor/Qt/common/pixmaps/view_all.xpm>
#include <Inventor/Qt/common/pixmaps/seek.xpm>

/*!
  \class SoQtFullViewer SoQtFullViewer.h Inventor/Qt/viewers/SoQtFullViewer.h
  \brief The SoQtFullViewer class adds decorations to the simple viewer of the parent.
  \ingroup soqtviewers

  TODO: more doc
  ...overview of what this class provides over parent class...
  ...keyboard combinations...mousebutton combinations...explain pan,
  rotate, zoom, dolly, seek...explain the fact that we're moving the
  camera, not the scene...
  ...viewer modes (examine vs interact) w/ explanation of what they are
  useful for...

  \sa SoQtConstrainedViewer, SoQtExaminerViewer, SoQtPlaneViewer
*/

// *************************************************************************

SOQT_OBJECT_ABSTRACT_SOURCE(SoQtFullViewer);

// *************************************************************************

/*¡
  SoQtFullViewer is missing the class description documentation.

  TODO, low priority:
  <UL>
  <LI>add tooltips to the widgets?</LI>
  <LI>trim length of edit fields</LI>
  </UL>
*/

/*!
  \enum SoQtFullViewer::BuildFlag
  FIXME: write documentation for enum
*/
/*!
  \var SoQtFullViewer::BuildFlag SoQtFullViewer::BUILD_NONE
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtFullViewer::BuildFlag SoQtFullViewer::BUILD_DECORATION
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtFullViewer::BuildFlag SoQtFullViewer::BUILD_POPUP
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtFullViewer::BuildFlag SoQtFullViewer::BUILD_ALL
  FIXME: write documentation for enum definition
*/



static const int VIEWERBORDER = 2;
static const int ZOOMSLIDERRESOLUTION = 200;


///////// FIXME start //////////////////////////////////////////////////
// Do something clever about this Qt layout assistant code..
// 990222 mortene.

enum LayoutOrientation { LayoutVertical, LayoutHorizontal };

void
expandSize(QSize & result, const QSize & addend, LayoutOrientation o)
{
  if (o == LayoutHorizontal) {
    result.rwidth() += addend.width();
    if (result.height() < addend.height()) result.setHeight(addend.height());
  }
  else {
    result.rheight() += addend.height();
    if (result.width() < addend.width()) result.setWidth(addend.width());
  }
}

///////// FIXME end ////////////////////////////////////////////////////


// FIXME: rewrite as inline function? 990221 mortene.
#define VIEWERBUTTON(BUTTONIDX) \
((QPushButton *)((*(this->viewerbuttons))[BUTTONIDX]))

// Button index values.
enum {
  INTERACT_BUTTON = 0,
  EXAMINE_BUTTON,
  HELP_BUTTON,
  HOME_BUTTON,
  SET_HOME_BUTTON,
  VIEW_ALL_BUTTON,
  SEEK_BUTTON
};

// *************************************************************************

/*!
  Constructor. See parent class for explanation of arguments.

  Subclasses will probably usually call with the \c buildNow flag
  set to \c FALSE to be able to do delayed building of the OpenGL
  canvas after other setup tasks has been performed.
*/

SoQtFullViewer::SoQtFullViewer(
  QWidget * parent,
  const char * name,
  SbBool embed,
  SoQtFullViewer::BuildFlag buildFlag,
  SoQtViewer::Type type,
  SbBool build )
: inherited( parent, name, embed, type, FALSE )
, common( new SoAnyFullViewer( this ) )
{
  this->viewerwidget = NULL;
  this->canvas = NULL;
//  this->canvasparent = NULL;

  this->viewbutton = NULL;
  this->interactbutton = NULL;

  this->leftDecoration = NULL;
  this->bottomDecoration = NULL;
  this->rightDecoration = NULL;

  this->leftWheel = NULL;
  this->leftWheelLabel = NULL;
  this->leftWheelStr = NULL;
  this->leftWheelVal = 0.0f;

  this->bottomWheel = NULL;
  this->bottomWheelLabel = NULL;
  this->bottomWheelStr = NULL;
  this->bottomWheelVal = 0.0f;

  this->rightWheel = NULL;
  this->rightWheelLabel = NULL;
  this->rightWheelStr = NULL;
  this->rightWheelVal = 0.0f;

  this->setLeftWheelString( "Motion X" );
  this->setBottomWheelString( "Motion Y" );
  this->setRightWheelString( "Motion Z" );

  this->zoomrange = SbVec2f(1.0f, 140.0f);

  this->mainlayout = NULL;
  this->appbuttonlayout = NULL;

  this->prefwindow = NULL;
  this->prefwindowtitle = "Viewer Preference Sheet";

  this->menuenabled = buildFlag & SoQtFullViewer::BUILD_POPUP;
  this->decorations =
    (buildFlag & SoQtFullViewer::BUILD_DECORATION) ? TRUE : FALSE;

  this->prefmenu = NULL;
  this->menutitle = "Viewer Menu";

  this->viewerbuttons = new SbPList;
  this->appbuttonlist = new SbPList;
  this->appbuttonform = NULL;

  this->setSize( SbVec2s(500, 390) );

  if ( ! build ) return;

  this->setClassName("SoQtFullViewer");
  QWidget * viewer = this->buildWidget( this->getParentWidget() );
  this->setBaseWidget( viewer );
} // SoQtFullViewer()

// *************************************************************************

/*!
  Destructor.
*/

SoQtFullViewer::~SoQtFullViewer(
  void )
{
  delete this->viewerbuttons;
  delete this->appbuttonlist;
} // ~SoQtFullViewer()

// *************************************************************************

/*!
  Turn the viewer decorations on or off.

  \sa isDecoration()
*/

void
SoQtFullViewer::setDecoration(
  const SbBool enable )
{
#if SOQT_DEBUG
  if ( (enable  && this->isDecoration()) ||
       (!enable && !this->isDecoration())) {
    SoDebugError::postWarning("SoQtFullViewer::setDecoration",
                              "decorations already turned %s",
                              enable ? "on" : "off");
    return;
  }
#endif // SOQT_DEBUG

  this->decorations = enable;
  if ( this->prefmenu )
    this->prefmenu->SetMenuItemMarked( DECORATION_ITEM, enable );
  if ( this->viewerwidget )
    this->showDecorationWidgets( enable );
} // setDecoration()

// *************************************************************************

/*!
  Return \c TRUE if the viewer decorations are on, otherwise \c FALSE.

  \sa setDecoration()
*/

SbBool
SoQtFullViewer::isDecoration(
  void ) const
{
  return this->decorations;
} // isDecoration()

// *************************************************************************

/*!
  Decide whether or not if clicking with the right mouse button on the
  OpenGL canvas should reveal a preferences popup menu when in viewing
  mode.

  \sa isPopupMenuEnabled()
*/

void
SoQtFullViewer::setPopupMenuEnabled(
  const SbBool enable )
{
#if SOQT_DEBUG
  if ( (enable && this->isPopupMenuEnabled()) ||
       (!enable && !this->isPopupMenuEnabled()) ) {
    SoDebugError::postWarning("SoQtFullViewer::setPopupMenuEnabled",
                              "popup menu already turned %s",
                              enable ? "on" : "off");
    return;
  }
#endif // SOQT_DEBUG
  this->menuenabled = enable;
} // setPopupMenuEnabled()

// *************************************************************************

/*!
  Return \c TRUE if the popup preferences menu is enabled,
  otherwise \c FALSE.

  \sa setPopupMenuEnabled()
*/

SbBool
SoQtFullViewer::isPopupMenuEnabled(
  void ) const
{
  return this->menuenabled;
} // isPopupMenuEnabled()

// *************************************************************************

/*!
  Returns the widget which is used as the parent of application
  specified buttons. The row of application buttons (if any) will be
  placed in the upper left corner.

  \sa addAppPushButton(), insertAppPushButton(), removeAppPushButton()
*/

QWidget *
SoQtFullViewer::getAppPushButtonParent(void) const
{
  return this->appbuttonform;
} // getAppPushButtonParent()

// *************************************************************************

/*!
  Add an application specific push button to the viewer decorations.
  Application buttons will be laid out in a vertical row from the
  upper left corner.

  The button will be added bottom-most.

  \sa insertAppPushButton(), removeAppPushButton(), getAppPushButtonParent()
*/

void
SoQtFullViewer::addAppPushButton(QWidget * newButton)
{
  this->appbuttonlist->append(newButton);
  this->layoutAppButtons(this->getAppPushButtonParent());
} // addAppPushButton()

// *************************************************************************

/*!
  Insert an application specific push button to the viewer decorations
  at the given \c index.

  \sa addAppPushButton(), removeAppPushButton(), getAppPushButtonParent()
*/

void
SoQtFullViewer::insertAppPushButton(QWidget * newButton, int index)
{
#if SOQT_DEBUG
  if ((index < 0) || (index > this->lengthAppPushButton())) {
    SoDebugError::postWarning("SoQtFullViewer::insertAppPushButton",
                              "index %d out of bounds", index);
    return;
  }
#endif // SOQT_DEBUG
  this->appbuttonlist->insert(newButton, index);
  this->layoutAppButtons(this->getAppPushButtonParent());
} // insertAppPushButton()

// *************************************************************************

/*!
  Remove one of the application specific buttons.

  \sa addAppPushButton(), insertAppPushButton()
*/

void
SoQtFullViewer::removeAppPushButton(QWidget * oldButton)
{
  int idx = this->appbuttonlist->find(oldButton);

#if SOQT_DEBUG
  if (idx == -1) {
    SoDebugError::postWarning("SoQtFullViewer::removeAppPushButton",
                              "tried to remove non-existant button");
    return;
  }
#endif // SOQT_DEBUG

  this->appbuttonlist->remove(idx);
  this->layoutAppButtons(this->getAppPushButtonParent());
} // removeAppPushButton()

// *************************************************************************

/*!
  Return the index of a particular button that has been specified by
  the application, or -1 of the button has not been added.

  \sa addAppPushButton()
*/

int
SoQtFullViewer::findAppPushButton(QWidget * oldButton) const
{
  return this->appbuttonlist->find(oldButton);
} // findAppPushButton()

// *************************************************************************

/*!
  Return number of application specific buttons added.

  \sa addAppPushButton(), insertAddAppPushButton()
*/

int
SoQtFullViewer::lengthAppPushButton(void) const
{
  return this->appbuttonlist->getLength();
} // lengthAppPushButton()

// *************************************************************************

/*!
  Returns the render area OpenGL canvas widget.
*/

QWidget *
SoQtFullViewer::getRenderAreaWidget(void)
{
  return this->canvas;
} // getRenderAreaWidget()

// *************************************************************************

/*!
  Set a flag to indicate whether we're in viewing mode (where the
  user can drag the model or scene around), or in interaction mode (where
  all window events from mouse, keyboard, etc are sent to the scene graph).

  Overloaded from parent class to correctly set the user interface
  indicators on the current state, namely the upper right push buttons
  indicating interact or view mode, the respective item on the popup menu
  and to grey out the seek mode activation button while in interact mode.
*/

void
SoQtFullViewer::setViewing(
  SbBool enable )
{
  if ( (enable && this->isViewing()) ||
       (!enable && !this->isViewing())) {
#if SOQT_DEBUG && 0 // debug
    SoDebugError::postWarning("SoQtFullViewer::setViewing",
                              "view mode already %s", on ? "on" : "off");
#endif // debug
    return;
  }

  inherited::setViewing( enable );
  if ( this->prefmenu )
    this->prefmenu->SetMenuItemMarked( EXAMINING_ITEM, enable );
  VIEWERBUTTON(EXAMINE_BUTTON)->setOn( enable );
  VIEWERBUTTON(INTERACT_BUTTON)->setOn( enable ? FALSE : TRUE);
  VIEWERBUTTON(SEEK_BUTTON)->setEnabled( enable );
} // setViewing()

// *************************************************************************

/*!
  Overloaded from parent to update user interface indicator for headlight
  on or off in the popup menu.
*/

void
SoQtFullViewer::setHeadlight(
  SbBool enable )
{
  inherited::setHeadlight( enable );
  if ( this->prefmenu )
    this->prefmenu->SetMenuItemMarked( HEADLIGHT_ITEM, enable );
} // setHeadlight()

// *************************************************************************

/*!
  Overloaded from parent to make sure the user interface indicator in
  the popup menu is updated correctly.
*/

void
SoQtFullViewer::setDrawStyle(SoQtViewer::DrawType type,
                             SoQtViewer::DrawStyle style)
{
  inherited::setDrawStyle(type, style);
  if (this->prefmenu)
    common->setDrawStyleMenuActivation(type, style);
} // setDrawStyle()

// *************************************************************************

/*!
  Overloaded from parent to make sure the user interface indicators in
  the popup menu are updated correctly.
*/

void
SoQtFullViewer::setBufferingType(
  SoQtViewer::BufferType type )
{
  inherited::setBufferingType( type );
  if ( this->prefmenu ) {
    switch ( type ) {
    case SoQtViewer::BUFFER_SINGLE:
      this->prefmenu->SetMenuItemMarked( SINGLE_BUFFER_ITEM, TRUE );
      break;
    case SoQtViewer::BUFFER_DOUBLE:
      this->prefmenu->SetMenuItemMarked( DOUBLE_BUFFER_ITEM, TRUE );
      break;
    case SoQtViewer::BUFFER_INTERACTIVE:
      this->prefmenu->SetMenuItemMarked( INTERACTIVE_BUFFER_ITEM, TRUE );
      break;
    default:
      assert( 0 && "unsupported buffer type" );
      break;
    }
  }
} // setBufferingType()

// *************************************************************************

/*!
  Overloaded from parent to make sure the user interface indicators on
  the camera features in the preferences sheet are updated correctly.
*/

void
SoQtFullViewer::setCamera(SoCamera * newCamera)
{
  inherited::setCamera(newCamera);

  if (this->prefwindow) {
    this->setZoomSliderPosition(this->getCameraZoom());
    this->setZoomFieldString(this->getCameraZoom());

    SbBool on = newCamera ? TRUE : FALSE;
    this->zoomslider->setEnabled(on);
    this->zoomfield->setEnabled(on);
    this->zoomrangefrom->setEnabled(on);
    this->zoomrangeto->setEnabled(on);
  }
} // setCamera()

// *************************************************************************

/*!
  Overloaded from parent class to make sure the preferences window
  will be hidden automatically whenever the viewer window is hidden.
*/

void
SoQtFullViewer::hide(void)
{
  inherited::hide();
  if (this->prefwindow) this->prefwindow->hide();
} // hide()

// *************************************************************************

/*!
  \internal

  Catch close events on the preferences window (to convert to hide
  events) and right mouse button presses (to pop up the
  preferences menu).
*/

bool
SoQtFullViewer::eventFilter(QObject * obj, QEvent * e)
{
#if 0 // debug
  const char eventnaming[][50] = {
    "None", // 0
    "Timer",
    "MouseButtonPress",
    "MouseButtonRelease",
    "MouseButtonDblClick",
    "MouseMove",
    "KeyPress",
    "KeyRelease",
    "FocusIn",
    "FocusOut",
    "Enter",
    "Leave",
    "Paint",
    "Move",
    "Resize",
    "Create",
    "Destroy",
    "Show",
    "Hide",
    "Close",
    "Quit", // 20
    "*error*", "*error*", "*error*", "*error*", "*error*",
    "*error*", "*error*", "*error*", "*error*",
    "Accel", // 30
    "Wheel",
    "AccelAvailable", // 32
    "*error*", "*error*", "*error*", "*error*",
    "*error*", "*error*", "*error*",
    "Clipboard", // 40
    "*error*", "*error*", "*error*", "*error*", "*error*",
    "*error*", "*error*", "*error*", "*error*",
    "SockAct", // 50
    "*error*", "*error*", "*error*", "*error*", "*error*",
    "*error*", "*error*", "*error*", "*error*",
    "DragEnter", // 60
    "DragMove",
    "DragLeave",
    "Drop",
    "DragResponse", // 64
    "*error*", "*error*", "*error*", "*error*", "*error*",
    "ChildInserted", // 70
    "ChildRemoved",
    "LayoutHint", // 72
    "*error*", "*error*", "*error*", "*error*", "*error*",
    "*error*", "*error*",
    "ActivateControl", // 80
    "DeactivateControl"
  };
  
  SoDebugError::postInfo("SoQtFullViewer::eventFilter", "%p: %s",
                         obj, eventnaming[e->type()]);
#endif // debug

  inherited::eventFilter(obj, e);

  // Convert dblclick events to press events to get the "correct"
  // sequence of two press+release pairs under Qt 1.xx and Qt
  // 2.xx. (It has been confirmed with the Trolls that this Qt
  // behavior is actually a feature, not a bug.)
#if QT_VERSION < 200
  int eventtype = e->type();
#else // Qt 2.0
  QEvent::Type eventtype = e->type();
#endif // Qt 2.0
  eventtype = (eventtype == Event_MouseButtonDblClick ?
               Event_MouseButtonPress : eventtype);

  // Catch close events to avoid anything actually being destroyed.
  if (obj == this->prefwindow) {
    if (eventtype == Event_Close) {
      ((QCloseEvent *)e)->ignore();
      this->prefwindow->hide();
      return TRUE;
    }
  }

  // Show the popup menu when we detect rmb pressed on top of the
  // render area canvas.
  if (this->menuenabled && obj == this->getGLWidget() &&
      eventtype == Event_MouseButtonPress) {
    QMouseEvent * me = (QMouseEvent *)e;
    if (me->button() == RightButton) {
      if ( ! this->prefmenu )
        this->buildPopupMenu();
      QPoint pos;
#if (QT_VERSION > 140)
      pos = me->globalPos();
#else
      pos = me->pos();
#endif
      this->prefmenu->PopUp( this->getGLWidget(), pos.x(), pos.y() );
    }
  }

  return FALSE;
} // eventFilter()

// *************************************************************************

/*!
  This will build the main view widgets, along with the decorations
  widgets and popup menu if they are enabled.
*/

QWidget *
SoQtFullViewer::buildWidget(
  QWidget * parent )
{
#if SOQT_DEBUG && 0
  SoDebugError::postInfo( "SoQtFullViewer::buildWidget", "[invoked]" );
#endif // SOQT_DEBUG
  this->viewerwidget = new QWidget(parent);
  this->registerWidget( viewerwidget );
//  this->viewerwidget->installEventFilter( this );

  this->viewerwidget->move( 0, 0 );
#if SOQT_DEBUG && 0
  this->viewerwidget->setBackgroundColor( QColor( 250, 0, 0 ) );
#endif // SOQT_DEBUG

  // Build and layout the widget components of the viewer window on
  // top of the manager widget.

//  this->canvasparent = new QWidget(this->viewerwidget);
//  this->canvasparent->move( 0, 0 );

  this->canvas = inherited::buildWidget( this->viewerwidget );
  if ( this->decorations ) {
    this->canvas->move( 30, 0 );
    this->canvas->resize(
      QSize( this->viewerwidget->size().width() - 60,
             this->viewerwidget->size().height() - 30 ) );
  } else {
    this->canvas->move( 0, 0 );
    this->canvas->resize( this->viewerwidget->size() );
  }

  if ( this->decorations ) {
    this->buildDecoration(this->viewerwidget);
    this->showDecorationWidgets(TRUE);
  }

  if ( this->menuenabled )
    this->buildPopupMenu();

  return this->viewerwidget;
} // buildWidget()

// *************************************************************************

/*!
  Build viewer decorations.
*/

void
SoQtFullViewer::buildDecoration(
  QWidget * parent )
{
  this->leftDecoration = this->buildLeftTrim(parent);
  this->bottomDecoration = this->buildBottomTrim(parent);
  this->rightDecoration = this->buildRightTrim(parent);
} // buildDecoration()

// *************************************************************************

/*!
  Build decorations on the left of the render canvas.  Overload this
  method in subclasses if you want your own decorations on the viewer
  window.

  The decoration will be 30 pixels wide.
*/

QWidget *
SoQtFullViewer::buildLeftTrim(
  QWidget * parent )
{
  QWidget * w = new QWidget(parent);
  w->setFixedWidth( 30 );

  QGridLayout * gl = new QGridLayout( w, 3, 1, 2, -1 );
  gl->addWidget( this->buildAppButtons(w), 0, 0 );

  SoQtThumbWheel * t = new SoQtThumbWheel( SoQtThumbWheel::Vertical, w );
  this->leftWheel = t;
  t->setRangeBoundaryHandling( SoQtThumbWheel::ACCUMULATE );
  this->leftWheelVal = t->value();

  QObject::connect( t, SIGNAL(wheelMoved(float)), this, SLOT(leftWheelChanged(float)) );
  QObject::connect( t, SIGNAL(wheelPressed()), this, SLOT(leftWheelPressed()) );
  QObject::connect( t, SIGNAL(wheelReleased()), this, SLOT(leftWheelReleased()) );

  gl->addWidget( t, 2, 0, AlignBottom | AlignHCenter );
  gl->activate();

  return w;
} // buildLeftTrim()

// *************************************************************************

/*!
  Build decorations on the bottom of the render canvas. Overload this
  method in subclasses if you want your own decorations on the viewer window.
*/

QWidget *
SoQtFullViewer::buildBottomTrim(
  QWidget * parent )
{
  QWidget * w = new QWidget(parent);
  w->setFixedHeight( 30 );

  QLabel * label = new QLabel( this->leftWheelStr, w );
  label->adjustSize();
  label->setAlignment( AlignLeft | AlignTop );
  label->setMargin( 2 );
  this->leftWheelLabel = label;

  label = new QLabel( this->bottomWheelStr, w );
  label->adjustSize();
  label->setAlignment( AlignRight | AlignVCenter );
  label->setMargin( 2 );
  this->bottomWheelLabel = label;

  label = new QLabel( this->rightWheelStr, w );
  label->adjustSize();
  label->setAlignment( AlignRight | AlignTop );
  label->setMargin( 2 );
  this->rightWheelLabel = label;

  SoQtThumbWheel * t = new SoQtThumbWheel( SoQtThumbWheel::Horizontal, w );
  this->bottomWheel = t;
  t->setRangeBoundaryHandling( SoQtThumbWheel::ACCUMULATE );

  QObject::connect( t, SIGNAL(wheelMoved(float)),
                    this, SLOT(bottomWheelChanged(float)) );
  QObject::connect( t, SIGNAL(wheelPressed()),
                    this, SLOT(bottomWheelPressed()) );
  QObject::connect( t, SIGNAL(wheelReleased()),
                    this, SLOT(bottomWheelReleased()) );

  this->bottomWheelVal = t->value();

  QGridLayout * gl = new QGridLayout( w, 1, 5 );
  gl->setColStretch( 0, 0 );
  gl->setColStretch( 1, 0 );
  gl->setColStretch( 2, 0 );
  gl->setColStretch( 3, 1 );
  gl->setColStretch( 4, 0 );

  gl->addWidget( this->leftWheelLabel, 0, 0, AlignVCenter | AlignHCenter );
  gl->addWidget( this->bottomWheelLabel, 0, 1, AlignVCenter | AlignRight );
  gl->addWidget( t, 0, 2, AlignVCenter | AlignLeft );
  gl->addWidget( this->rightWheelLabel, 0, 4, AlignVCenter | AlignRight );

  gl->activate();

  return w;
} // buildBottomTrim()

// *************************************************************************

/*!
  Build decorations on the right side of the render canvas. Overload this
  method in subclasses if you want your own decorations on the viewer window.
*/

QWidget *
SoQtFullViewer::buildRightTrim(
  QWidget * parent )
{
  QWidget * w = new QWidget(parent);
  // FIXME: should be set according to width of viewer
  // buttons. 20000424 mortene.
  w->setFixedWidth( 30 );
  // FIXME: nope, trims are actually guaranteed to be 30 pixels wide

  SoQtThumbWheel * t = new SoQtThumbWheel(SoQtThumbWheel::Vertical, w);
  this->rightWheel = t;
  t->setRangeBoundaryHandling( SoQtThumbWheel::ACCUMULATE );
  this->rightWheelVal = t->value();

  QObject::connect(t, SIGNAL(wheelMoved(float)),
                   this, SLOT(rightWheelChanged(float)));
  QObject::connect(t, SIGNAL(wheelPressed()),
                   this, SLOT(rightWheelPressed()));
  QObject::connect(t, SIGNAL(wheelReleased()),
                   this, SLOT(rightWheelReleased()));

  QGridLayout * l = new QGridLayout(w, 3, 1, 2, -1 );
  l->setMargin( 0 );
  l->addWidget( this->buildViewerButtons(w), 0, 0 );
  l->addWidget( t, 2, 0, AlignBottom|AlignHCenter );
  l->activate();

  return w;
} // buildRightTrim()

// *************************************************************************

/*!
  Build the application specified button row (if any buttons were
  set up).
*/

QWidget *
SoQtFullViewer::buildAppButtons(QWidget * parent)
{
  this->appbuttonform = new QWidget(parent);

  if (this->lengthAppPushButton() > 0)
    this->layoutAppButtons(this->appbuttonform);

  return this->appbuttonform;
} // buildAppButtons()

// *************************************************************************

/*!
  Build and layout viewer specified button row.
*/

QWidget *
SoQtFullViewer::buildViewerButtons(QWidget * parent)
{
  QWidget * w = new QWidget( parent );
  this->createViewerButtons(w, this->viewerbuttons);
  w->move( 0, 0 );

  // assert(this->viewerbuttons->getLength() != 0);
  QGridLayout * l =
    new QGridLayout(w, this->viewerbuttons->getLength(), 1);
  l->setMargin( 0 );
  l->setSpacing( 0 );

  const int numViewerButtons = this->viewerbuttons->getLength();
  for ( int i = 0; i < numViewerButtons; i++ ) {
    QButton * b = VIEWERBUTTON(i);
    b->setFixedSize( 30, 30 );
    b->setFocusPolicy( QWidget::NoFocus );
    l->addWidget(b, i, 0);
  }

  l->activate();
  return w;
} // buildViewerButtons()

// *************************************************************************

/*!
  Set up the viewer buttons with pixmaps and event connections.
*/

void
SoQtFullViewer::createViewerButtons(QWidget * parent, SbPList * buttonlist)
{
  for (int i=0; i <= SEEK_BUTTON; i++) {
    QPushButton * p = new QPushButton(parent);
    // Button focus doesn't really make sense in the way we're using
    // the pushbuttons.
    p->setFocusPolicy(QWidget::NoFocus);

    // FIXME: its wrong to cast xpm data to (const char **), it
    // _should_ be (const char * const []), but this is not valid ANSI
    // C++. Not sure what to do about this (and the wrong cast can
    // (and has) in fact lead to bugs, so the situation should be
    // resolved). 20000505 mortene.

    switch (i) {
    case INTERACT_BUTTON:
      this->interactbutton = p;
      p->setToggleButton(TRUE);
      p->setPixmap(QPixmap((const char **)pick_xpm));
      p->setOn(this->isViewing() ? FALSE : TRUE);
      QObject::connect(p, SIGNAL(clicked()),
                       this, SLOT(interactbuttonClicked()));
      break;
    case EXAMINE_BUTTON:
      this->viewbutton = p;
      p->setToggleButton(TRUE);
      p->setPixmap(QPixmap((const char **)view_xpm));
      p->setOn(this->isViewing());
      QObject::connect(p, SIGNAL(clicked()),
                       this, SLOT(viewbuttonClicked()));
      break;
    case HELP_BUTTON:
      QObject::connect(p, SIGNAL(clicked()), this, SLOT(helpbuttonClicked()));
      p->setPixmap(QPixmap((const char **)help_xpm));
      break;
    case HOME_BUTTON:
      QObject::connect(p, SIGNAL(clicked()), this, SLOT(homebuttonClicked()));
      p->setPixmap(QPixmap((const char **)home_xpm));
      break;
    case SET_HOME_BUTTON:
      QObject::connect(p, SIGNAL(clicked()),
                       this, SLOT(sethomebuttonClicked()));
      p->setPixmap(QPixmap((const char **)set_home_xpm));
      break;
    case VIEW_ALL_BUTTON:
      QObject::connect(p, SIGNAL(clicked()),
                       this, SLOT(viewallbuttonClicked()));
      p->setPixmap(QPixmap((const char **)view_all_xpm));
      break;
    case SEEK_BUTTON:
      QObject::connect(p, SIGNAL(clicked()), this, SLOT(seekbuttonClicked()));
      p->setPixmap(QPixmap((const char **)seek_xpm));
      break;
    default:
      assert(0);
      break;
    }

    p->adjustSize();
    buttonlist->append(p);
  }
} // createViewerButtons()

// *************************************************************************

/*!
  Make a popup menu with preferences settings.
*/

void
SoQtFullViewer::buildPopupMenu(
  void )
{
  this->prefmenu = common->setupStandardPopupMenu();

  // Set initial checkmarks on drawstyle menus.
  this->setDrawStyle(
    SoQtViewer::STILL, this->getDrawStyle( SoQtViewer::STILL ) );
  this->setDrawStyle(
    SoQtViewer::INTERACTIVE, this->getDrawStyle( SoQtViewer::INTERACTIVE ) );
  this->setBufferingType( this->getBufferingType() );

  this->prefmenu->SetMenuItemMarked( EXAMINING_ITEM, this->isViewing() );
  this->prefmenu->SetMenuItemMarked( DECORATION_ITEM, this->decorations );
  this->prefmenu->SetMenuItemMarked( HEADLIGHT_ITEM, this->isHeadlight() );

} // buildPopupMenu()

// *************************************************************************

/*!
  Set title of popup menu.
*/

void
SoQtFullViewer::setPopupMenuString(const char * str)
{
/*
  this->menutitle = str ? str : "";
  if (this->prefmenu) this->prefmenu->changeItem(this->menutitle.getString(),
                                                 MENUTITLE_ITEM);
*/
} // setPopupMenuString()

// *************************************************************************

/*!
  Build the sub-popupmenu with miscellaneous functions.
*/

/*
QWidget *
SoQtFullViewer::buildFunctionsSubmenu(QWidget * popup)
{
  QPopupMenu * m = new QPopupMenu(popup);

  m->insertItem("Help", this, SLOT(helpbuttonClicked()), 0, HELP_ITEM);
  m->insertItem("Home", this, SLOT(homebuttonClicked()), 0, HOME_ITEM);
  m->insertItem("Set Home", this, SLOT(sethomebuttonClicked()), 0,
                SET_HOME_ITEM);
  m->insertItem("View All", this, SLOT(viewallbuttonClicked()), 0,
                VIEW_ALL_ITEM);
  m->insertItem("Seek", this, SLOT(seekbuttonClicked()), 0, SEEK_ITEM);

  m->insertSeparator();

  m->insertItem("Copy View", this, SLOT(copyviewSelected()), 0,
                COPY_VIEW_ITEM);
  m->insertItem("Paste View", this, SLOT(pasteviewSelected()), 0,
                PASTE_VIEW_ITEM);

  return m;
} // buildFunctionsSubmenu()
*/

// *************************************************************************

/*!
  Build the sub-popupmenu with the drawstyle settings.
*/

/*
QWidget *
SoQtFullViewer::buildDrawStyleSubmenu(QWidget * popup)
{
  QPopupMenu * m = new QPopupMenu(popup);

  m->insertItem("as is", AS_IS_ITEM);
  m->insertItem("hidden line", HIDDEN_LINE_ITEM);
  m->insertItem("no texture", NO_TEXTURE_ITEM);
  m->insertItem("low resolution", LOW_RESOLUTION_ITEM);
  m->insertItem("wireframe", WIREFRAME_ITEM);
  m->insertItem("points", POINTS_ITEM);
  m->insertItem("bounding box (no depth)", BOUNDING_BOX_ITEM);
  m->insertSeparator();

  m->insertItem("move same as still", MOVE_SAME_AS_STILL_ITEM);
  m->insertItem("move no texture", MOVE_NO_TEXTURE_ITEM);
  m->insertItem("move low res", MOVE_LOW_RES_ITEM);
  m->insertItem("move wireframe", MOVE_WIREFRAME_ITEM);
  m->insertItem("move low res wireframe (no depth)",
                MOVE_LOW_RES_WIREFRAME_ITEM);
  m->insertItem("move points", MOVE_POINTS_ITEM);
  m->insertItem("move low res points (no depth)", MOVE_LOW_RES_POINTS_ITEM);
  m->insertItem("move bounding box (no depth)", MOVE_BOUNDING_BOX_ITEM);
  m->insertSeparator();

  m->insertItem("single buffer", SINGLE_BUFFER_ITEM);
  m->insertItem("double buffer", DOUBLE_BUFFER_ITEM);
  m->insertItem("interactive buffer", INTERACTIVE_BUFFER_ITEM);

  QObject::connect(m, SIGNAL(activated(int)), SLOT(drawstyleActivated(int)));

  return m;
} // buildDrawStyleSubmenu()
*/

/*!
  NOTE: This method is not part of the original InventorXt API.
*/

void
SoQtFullViewer::openPopupMenu( // protected
  const SbVec2s position )
{
  if ( ! this->isPopupMenuEnabled() ) return;
  if ( this->prefmenu == NULL )
    this->buildPopupMenu();
  int x = 2 + position[0];
  int y = 2 + this->getGLSize()[1] - position[1];
  QPoint pos = this->getGLWidget()->mapToGlobal( QPoint(x,y) );
  this->prefmenu->PopUp( this->getGLWidget(), pos.x(), pos.y() );
} // openPopupMenu()

// *************************************************************************

/*!
  Overload this method in subclass viewers to append more widgets to
  the bottom of the preferences sheet window.
*/

QWidget *
SoQtFullViewer::makeSubPreferences(QWidget * /*parent*/)
{
  return NULL;
} // makeSubPreferences()

// *************************************************************************

/*!
  Set title of preferences sheet.
*/

void
SoQtFullViewer::setPrefSheetString(const char * title)
{
  this->prefwindowtitle = title ? title : "";
  if (this->prefwindow)
    this->prefwindow->setCaption(this->prefwindowtitle.getString());
} // setPrefSheetString()

// *************************************************************************

/*!
  Called when the user start to drag the thumbwheel in the left frame.
  Overload this method in subclassed viewers to provide your own
  functionality on the thumbwheel.

  \sa leftWheelMotion(), leftWheelFinish()
  \sa bottomWheelStart(), rightWheelStart()
*/

void
SoQtFullViewer::leftWheelStart(void)
{
  this->interactiveCountInc();
} // leftWheelStart()

/*!
  Called repeatedly as the user drags the thumbwheel in the left frame.
  Overload this method in subclassed viewers to provide your own
  functionality on the thumbwheel.

  \sa leftWheelStart(), leftWheelFinish()
  \sa bottomWheelStart(), rightWheelStart()
*/

void
SoQtFullViewer::leftWheelMotion(
  float value )
{
  this->leftWheelVal = value;
} // leftWheelMotion()

/*!
  Called as the user let go of the thumbwheel in the left frame after
  a drag operation. Overload this method in subclassed viewers to provide
  your own functionality on the thumbwheel.

  \sa leftWheelStart(), leftWheelMotion()
  \sa bottomWheelStart(), rightWheelStart()
*/

void
SoQtFullViewer::leftWheelFinish(void)
{
  this->interactiveCountDec();
} // leftWheelFinish()

/*!
  Get current value of the left thumbwheel.

  \sa leftWheelMotion()
*/

float
SoQtFullViewer::getLeftWheelValue(
  void ) const
{
  return this->leftWheelVal;
} // getLeftWheelValue()

void
SoQtFullViewer::setLeftWheelValue(
  const float value )
{
  this->leftWheelVal = value;
  ((SoQtThumbWheel *) this->leftWheel)->setValue( value );
} // setLeftWheelValue()

// *************************************************************************

/*!
  Called when the user start to drag the thumbwheel in the bottom frame.
  Overload this method in subclassed viewers to provide your own
  functionality on the thumbwheel.

  \sa bottomWheelMotion(), bottomWheelFinish()
  \sa leftWheelStart(), rightWheelStart()
*/

void
SoQtFullViewer::bottomWheelStart(void)
{
  this->interactiveCountInc();
} // bottomWheelStart()

/*!
  Called repeatedly as the user drags the thumbwheel in the bottom frame.
  Overload this method in subclassed viewers to provide your own
  functionality on the thumbwheel.

  \sa bottomWheelStart(), bottomWheelFinish()
  \sa leftWheelStart(), rightWheelStart()
*/

void
SoQtFullViewer::bottomWheelMotion(
  float value )
{
  this->bottomWheelVal = value;
} // bottomWheelMotion()

/*!
  Called as the user let go of the thumbwheel in the bottom frame after
  a drag operation. Overload this method in subclassed viewers to provide
  your own functionality on the thumbwheel.

  \sa bottomWheelStart(), bottomWheelMotion()
  \sa leftWheelStart(), rightWheelStart()
*/

void
SoQtFullViewer::bottomWheelFinish(void)
{
  this->interactiveCountDec();
} // bottomWheelFinish()

/*!
  Get current value of the bottom thumbwheel.

  \sa bottomWheelMotion()
*/

float
SoQtFullViewer::getBottomWheelValue(
  void ) const
{
  return this->bottomWheelVal;
} // getBottomWheelValue()

void
SoQtFullViewer::setBottomWheelValue(
  const float value )
{
  this->bottomWheelVal = value;
  ((SoQtThumbWheel *) this->bottomWheel)->setValue( value );
} // setBottomWheelValue()

// *************************************************************************

/*!
  Called when the user start to drag the thumbwheel in the right frame.
  Overload this method in subclassed viewers to provide your own
  functionality on the thumbwheel.

  \sa rightWheelMotion(), rightWheelFinish()
  \sa leftWheelStart(), bottomWheelStart()
*/

void
SoQtFullViewer::rightWheelStart(void)
{
  this->interactiveCountInc();
} // rightWheelStart()

/*!
  Called repeatedly as the user drags the thumbwheel in the right frame.
  Overload this method in subclassed viewers to provide your own
  functionality on the thumbwheel.

  \sa rightWheelStart(), rightWheelFinish()
  \sa leftWheelStart(), bottomWheelStart()
*/

void
SoQtFullViewer::rightWheelMotion(
  float value )
{
  this->rightWheelVal = value;
} // rightWheelMotion()

/*!
  Called as the user let go of the thumbwheel in the right frame after
  a drag operation. Overload this method in subclassed viewers to provide
  your own functionality on the thumbwheel.

  \sa rightWheelStart(), rightWheelMotion()
  \sa leftWheelStart(), bottomWheelStart()
*/

void
SoQtFullViewer::rightWheelFinish(void)
{
  this->interactiveCountDec();
} // rightWheelFinish()

/*!
  Get current value of the right thumbwheel.

  \sa rightWheelMotion()
*/

float
SoQtFullViewer::getRightWheelValue(
  void ) const
{
  return this->rightWheelVal;
} // getRightWheelValue()

void
SoQtFullViewer::setRightWheelValue(
  const float value )
{
  this->rightWheelVal = value;
  ((SoQtThumbWheel *) this->rightWheel)->setValue( value );
} // setRightWheelValue()

// *************************************************************************

// These are all private slots for catching Qt events.
void SoQtFullViewer::leftWheelPressed(void) { this->leftWheelStart(); }
void SoQtFullViewer::leftWheelChanged(float v) { this->leftWheelMotion(v); }
void SoQtFullViewer::leftWheelReleased(void) { this->leftWheelFinish(); }
void SoQtFullViewer::bottomWheelPressed(void) { this->bottomWheelStart(); }
void SoQtFullViewer::bottomWheelChanged(float v) { this->bottomWheelMotion(v);}
void SoQtFullViewer::bottomWheelReleased(void) { this->bottomWheelFinish(); }
void SoQtFullViewer::rightWheelPressed(void) { this->rightWheelStart(); }
void SoQtFullViewer::rightWheelChanged(float v) { this->rightWheelMotion(v); }
void SoQtFullViewer::rightWheelReleased(void) { this->rightWheelFinish(); }

// *************************************************************************

/*!
  Set label of the left thumbwheel.
*/

void
SoQtFullViewer::setLeftWheelString(
  const char * const string )
{
  if ( this->leftWheelStr ) {
    delete [] this->leftWheelStr;
    this->leftWheelStr = NULL;
  }
  if ( string )
    this->leftWheelStr = strcpy( new char [strlen(string)+1], string );
  if ( this->leftWheelLabel )
    ((QLabel *)this->leftWheelLabel)->setText( string ? string : "" );
} // setLeftWheelString()

// *************************************************************************

/*!
  Set label of the bottom thumbwheel.
*/

void
SoQtFullViewer::setBottomWheelString(
  const char * const string )
{
  if ( this->bottomWheelStr ) {
    delete [] this->bottomWheelStr;
    this->bottomWheelStr = NULL;
  }
  if ( string )
    this->bottomWheelStr = strcpy( new char [strlen(string)+1], string );
  if ( this->bottomWheelLabel )
    ((QLabel *)this->bottomWheelLabel)->setText( string ? string : "" );
} // setBottomWheelString()

// *************************************************************************

/*!
  Set label of the right thumbwheel.
*/

void
SoQtFullViewer::setRightWheelString(
  const char * const string )
{
  if ( this->rightWheelStr ) {
    delete [] this->rightWheelStr;
    this->rightWheelStr = NULL;
  }
  if ( string )
    this->rightWheelStr = strcpy( new char [strlen(string)+1], string );
  if ( this->rightWheelLabel )
    ((QLabel *)this->rightWheelLabel)->setText( string ? string : "" );
} // setRightWheelString()

// *************************************************************************

/*!
  Overload this method to provide functionality when the user clicks
  the Help button. Default implementation does nothing.
*/

void
SoQtFullViewer::openViewerHelpCard(void)
{
} // openViewerHelpCard()

// *************************************************************************

/*!
  \internal

  Show or hide decorations. Will make and activate a Qt layout grid
  if we're turning the decorations on.
*/

void
SoQtFullViewer::showDecorationWidgets(
  SbBool onOff )
{
#if SOQT_DEBUG && 0
  SoDebugError::postInfo( "SoQtFullViewer::showDecorationWidgets", "[invoked]" );
#endif // SOQT_DEBUG

  if (this->mainlayout) delete this->mainlayout;

  assert(this->viewerwidget);
//  assert(this->canvasparent);

  assert( this->leftDecoration && this->bottomDecoration && this->rightDecoration );
  if ( onOff ) {
    this->leftDecoration->show();
    this->bottomDecoration->show();
    this->rightDecoration->show();

    QGridLayout * g = new QGridLayout(this->viewerwidget, 2, 1, 0, -1 ); // VIEWERBORDER);

    g->addWidget(this->bottomDecoration, 1, 0);

    QGridLayout * subLayout = new QGridLayout( 1, 3, 0 );
    g->addLayout(subLayout, 0, 0);

    subLayout->addWidget(this->leftDecoration, 0, 0);
    subLayout->addWidget(this->canvas, 0, 1);
    subLayout->addWidget(this->rightDecoration, 0, 2);

//     subLayout->setColStretch(1, 1);
//     g->setRowStretch(0, 1);

    this->mainlayout = g;
  } else {
    QGridLayout * g = new QGridLayout(this->viewerwidget, 1, 1, 0, -1 );
    g->addWidget(this->canvas, 0, 0);
    this->mainlayout = g;

    this->leftDecoration->hide();
    this->bottomDecoration->hide();
    this->rightDecoration->hide();
  }

  this->mainlayout->activate();
  QSize size = this->viewerwidget->size();
  SbVec2s rasize = SbVec2s( size.width(), size.height() );
  SoQtFullViewer::sizeChanged( rasize );
} // showDecorationWidgets()

// *************************************************************************

/*!
  Layout application specified buttons.
*/

void
SoQtFullViewer::layoutAppButtons(QWidget * form)
{
  delete this->appbuttonlayout; this->appbuttonlayout = NULL;

  int nrbuttons = this->appbuttonlist->getLength();
  if (nrbuttons == 0) return;

  this->appbuttonlayout = new QGridLayout(form, nrbuttons, 1);

  for (int i=0; i < nrbuttons; i++) {
    QWidget * button = (QWidget *)((*(this->appbuttonlist))[i]);
    button->show();
    ((QGridLayout *)this->appbuttonlayout)->addWidget(button, i, 0);
  }

  this->appbuttonlayout->activate();
} // layoutAppButtons()

// *************************************************************************

/*!
  Create preferences sheet.
*/

QWidget *
SoQtFullViewer::makePreferencesWindow(void)
{
  QWidget * top = new QWidget(NULL);
  top->setCaption(this->prefwindowtitle.getString());
  top->setIconText(this->prefwindowtitle.getString());

  QVBoxLayout * layout = new QVBoxLayout(top, 10);

  QWidget * w;
  w = this->makeSeekPreferences(top);
  if (w) layout->addWidget(w, w->height());
  w = this->makeSeekDistancePreferences(top);
  if (w) layout->addWidget(w, w->height());
  w = this->makeZoomPreferences(top);
  if (w) layout->addWidget(w, w->height());
  w = this->makeAutoclipPreferences(top);
  if (w) layout->addWidget(w, w->height());

  w = this->makeSubPreferences(top);
  if (w) layout->addWidget(w, w->height());

  layout->activate();
  top->adjustSize();
  return top;
} // makePreferencesWindow()

// *************************************************************************

/*!
  Create the UI representation of the preferences' settings for the
  seek-to-point functionality.
*/

QWidget *
SoQtFullViewer::makeSeekPreferences(QWidget * parent)
{
  // FIXME: it'd be nice to show separation in the prefs sheet, but
  // this code doesn't work for some reason (because of the
  // layout objects?). 990221 mortene.
#if 0
  QFrame * w = new QFrame(parent);
  w->setFrameStyle(QFrame::Box | QFrame::Plain);
  w->setLineWidth(1);
#else
  QWidget * w = new QWidget(parent);
#endif

  // Initialize objects keeping track of geometry data.

  QSize tmpsize(0, 0);
  QSize totalsize(0, 0);

  QVBoxLayout * toplayout = new QVBoxLayout(w);

  // First, do the three widgets on the uppermost row (label,
  // lineedit, label).

  QLabel * l1 = new QLabel("Seek animation time:", w);
  l1->adjustSize();
  expandSize(tmpsize, l1->size(), LayoutHorizontal);

  QLineEdit * le = new QLineEdit(w);
#if QT_VERSION < 200 // Qt 2.xx
  QObject::connect(le, SIGNAL(textChanged(const char *)),
                   this, SLOT(seekAnimationTimeChanged(const char *)));
#else // Qt 1.xx
  QObject::connect(le, SIGNAL(textChanged(const QString &)),
                   this, SLOT(seekAnimationTimeChanged(const QString &)));
#endif // Qt 1.xx
  QString s;
  s.setNum(this->getSeekTime(), 'f', 2);
  le->setText(s);
  le->adjustSize();
  expandSize(tmpsize, le->size(), LayoutHorizontal);

  QLabel * l2 = new QLabel("seconds", w);
  l2->adjustSize();
  expandSize(tmpsize, l2->size(), LayoutHorizontal);

  // Layout row 1.
  QBoxLayout * layout = new QHBoxLayout;
  toplayout->addLayout(layout, tmpsize.height());
  layout->addWidget(l1, l1->width());
  layout->addWidget(le, le->width());
  layout->addWidget(l2, l2->width());
  expandSize(totalsize, tmpsize, LayoutVertical);


  // Do the three widgets on the second row (label, radiobutton,
  // radiobutton).

  tmpsize = QSize(0, 0);

  QLabel * l3 = new QLabel("Seek to:", w);
  l3->adjustSize();
  expandSize(tmpsize, l3->size(), LayoutHorizontal);

  QButtonGroup * bg = new QButtonGroup;
  QRadioButton * r1 = new QRadioButton("point", w);
  r1->setChecked(this->isDetailSeek());
  r1->adjustSize();
  expandSize(tmpsize, r1->size(), LayoutHorizontal);
  bg->insert(r1);

  QRadioButton * r2 = new QRadioButton("object", w);
  r2->setChecked(!this->isDetailSeek());
  r2->adjustSize();
  expandSize(tmpsize, r2->size(), LayoutHorizontal);
  bg->insert(r2);

  bg->setExclusive(TRUE);
  QObject::connect(bg, SIGNAL(clicked(int)),
                   this, SLOT(seekDetailToggled(int)));

  // Layout row 2.
  layout = new QHBoxLayout;
  toplayout->addLayout(layout, tmpsize.height());
  layout->addWidget(l3, l3->width());
  layout->addWidget(r1, r1->width());
  layout->addWidget(r2, r2->width());
  expandSize(totalsize, tmpsize, LayoutVertical);

  w->resize(totalsize);
  toplayout->activate();
  return w;
} // makeSeekPreferences()

// *************************************************************************

/*!
  Create the UI representation of the preferences' settings for the
  seek-to-point functionality.
*/

QWidget *
SoQtFullViewer::makeSeekDistancePreferences(QWidget * parent)
{
  QWidget * w = new QWidget(parent);

  // Initialize objects keeping track of geometry data.

  QSize tmpsize(0, 0);
  QSize totalsize(0, 0);

  QVBoxLayout * toplayout = new QVBoxLayout(w);

  // First, do the three widgets on the uppermost row (label,
  // thumbwheel, lineedit).

  QLabel * l = new QLabel("Seek distance:", w);
  l->adjustSize();
  expandSize(tmpsize, l->size(), LayoutHorizontal);

  this->seekdistancewheel = new SoQtThumbWheel(SoQtThumbWheel::Horizontal, w);
  this->seekdistancewheel->setRangeBoundaryHandling( SoQtThumbWheel::ACCUMULATE );
  this->seekdistancewheel->setValue(sqrt(this->getSeekDistance()));
  this->seekdistancewheel->adjustSize();
  expandSize(tmpsize, this->seekdistancewheel->size(),
                             LayoutHorizontal);
  QObject::connect(this->seekdistancewheel, SIGNAL(wheelMoved(float)),
                   this, SLOT(seekDistanceWheelChanged(float)));

  this->seekdistancefield = new QLineEdit(w);
  QString s;
  s.setNum(this->getSeekDistance(), 'f', 2);
  this->seekdistancefield->setText(s);
  this->seekdistancefield->adjustSize();
  expandSize(tmpsize, this->seekdistancefield->size(),
                             LayoutHorizontal);
  QObject::connect(this->seekdistancefield, SIGNAL(returnPressed()),
                   this, SLOT(seekDistanceEdit()));

  // Layout row 1.
  QBoxLayout * layout = new QHBoxLayout;
  toplayout->addLayout(layout, tmpsize.height());
  layout->addWidget(l, l->width());
  layout->addWidget(this->seekdistancewheel, this->seekdistancewheel->width());
  layout->addWidget(this->seekdistancefield, this->seekdistancefield->width());
  expandSize(totalsize, tmpsize, LayoutVertical);


  // Do the two widgets on the second row (radiobutton, radiobutton).

  tmpsize = QSize(0, 0);

  QButtonGroup * bg = new QButtonGroup;
  QRadioButton * r1 = new QRadioButton("percentage", w);
  r1->setChecked(this->isSeekValuePercentage());
  r1->adjustSize();
  expandSize(tmpsize, r1->size(), LayoutHorizontal);
  bg->insert(r1);

  QRadioButton * r2 = new QRadioButton("absolute", w);
  r2->setChecked(!this->isSeekValuePercentage());
  r2->adjustSize();
  expandSize(tmpsize, r2->size(), LayoutHorizontal);
  bg->insert(r2);

  bg->setExclusive(TRUE);
  QObject::connect(bg, SIGNAL(clicked(int)),
                   this, SLOT(seekDistanceTypeToggle(int)));

  // Layout row 2.
  layout = new QHBoxLayout;
  toplayout->addLayout(layout, tmpsize.height());
  layout->addWidget(r1, r1->width());
  layout->addWidget(r2, r2->width());
  expandSize(totalsize, tmpsize, LayoutVertical);

  w->resize(totalsize);
  toplayout->activate();

  return w;
} // makeSeekDistancePreferences()

// *************************************************************************

/*!
  Create the UI representation of the preferences' settings for the
  camera zoom functionality.
*/

QWidget *
SoQtFullViewer::makeZoomPreferences(QWidget * parent)
{
  QWidget * w = new QWidget(parent);

  // Initialize objects keeping track of geometry data.

  QSize tmpsize(0, 0);
  QSize totalsize(0, 0);

  QVBoxLayout * toplayout = new QVBoxLayout(w);

  // First, do the three widgets on the uppermost row (label,
  // slider, lineedit).

  QLabel * l1 = new QLabel("Camera zoom", w);
  l1->adjustSize();
  expandSize(tmpsize, l1->size(), LayoutHorizontal);

  this->zoomslider = new QSlider(0, ZOOMSLIDERRESOLUTION,
                                 1, 0, QSlider::Horizontal, w);
  this->zoomslider->adjustSize();
  expandSize(tmpsize, this->zoomslider->size(), LayoutHorizontal);
  QObject::connect(this->zoomslider, SIGNAL(sliderPressed()),
                   this, SLOT(increaseInteractiveCount()));
  QObject::connect(this->zoomslider, SIGNAL(valueChanged(int)),
                   this, SLOT(zoomSliderMoved(int)));
  QObject::connect(this->zoomslider, SIGNAL(sliderReleased()),
                   this, SLOT(decreaseInteractiveCount()));

  this->zoomfield = new QLineEdit(w);
  this->zoomfield->adjustSize();
  expandSize(tmpsize, this->zoomfield->size(), LayoutHorizontal);
  QObject::connect(this->zoomfield, SIGNAL(returnPressed()),
                   this, SLOT(zoomFieldChanged()));


  // Layout row 1.
  QBoxLayout * layout = new QHBoxLayout;
  toplayout->addLayout(layout, tmpsize.height());
  layout->addWidget(l1, l1->width());
  layout->addWidget(this->zoomslider, this->zoomslider->width());
  layout->addWidget(this->zoomfield, this->zoomfield->width());
  expandSize(totalsize, tmpsize, LayoutVertical);


  // Do the four widgets on the second row (label, lineedit, label,
  // lineedit).

  tmpsize = QSize(0, 0);

  QLabel * l2 = new QLabel("Zoom slider ranges from:", w);
  l2->adjustSize();
  expandSize(tmpsize, l2->size(), LayoutHorizontal);

  this->zoomrangefrom = new QLineEdit(w);
  QString s;
  s.setNum(this->zoomrange[0], 'f', 1);
  this->zoomrangefrom->setText(s);
  this->zoomrangefrom->adjustSize();
  expandSize(tmpsize, this->zoomrangefrom->size(), LayoutHorizontal);
  QObject::connect(this->zoomrangefrom, SIGNAL(returnPressed()),
                   this, SLOT(zoomRangeChanged1()));

  QLabel * l3 = new QLabel("to:", w);
  l3->adjustSize();
  expandSize(tmpsize, l3->size(), LayoutHorizontal);

  this->zoomrangeto = new QLineEdit(w);
  s.setNum(this->zoomrange[1], 'f', 1);
  this->zoomrangeto->setText(s);
  this->zoomrangeto->adjustSize();
  expandSize(tmpsize, this->zoomrangeto->size(), LayoutHorizontal);
  QObject::connect(this->zoomrangeto, SIGNAL(returnPressed()),
                   this, SLOT(zoomRangeChanged2()));


  // Layout row 2.
  layout = new QHBoxLayout;
  toplayout->addLayout(layout, tmpsize.height());
  layout->addWidget(l2, l2->width());
  layout->addWidget(this->zoomrangefrom, this->zoomrangefrom->width());
  layout->addWidget(l3, l3->width());
  layout->addWidget(this->zoomrangeto, this->zoomrangeto->width());
  expandSize(totalsize, tmpsize, LayoutVertical);


  SoCamera * cam = this->getCamera();
  if (cam) {
    this->setZoomSliderPosition(this->getCameraZoom());
    this->setZoomFieldString(this->getCameraZoom());
  }
  else {
    this->zoomslider->setEnabled(FALSE);
    this->zoomfield->setEnabled(FALSE);
    this->zoomrangefrom->setEnabled(FALSE);
    this->zoomrangeto->setEnabled(FALSE);
  }

  w->resize(totalsize);
  toplayout->activate();

  return w;
} // makeZoomPreferences()

// *************************************************************************

/*!
  Enable or disable interaction through the near and far clipping
  widgets.
*/

void
SoQtFullViewer::setEnabledClippingWidgets(SbBool flag)
{
  this->nearclippinglabel->setEnabled(flag);
  this->nearclippingwheel->setEnabled(flag);
  this->nearclippingedit->setEnabled(flag);
  this->farclippinglabel->setEnabled(flag);
  this->farclippingwheel->setEnabled(flag);
  this->farclippingedit->setEnabled(flag);

  SoCamera * cam = this->getCamera();
  if (!cam) return;

  this->nearclippingwheel->setValue(cam->nearDistance.getValue());
  this->farclippingwheel->setValue(cam->farDistance.getValue());

  QString s;
  s.setNum(cam->nearDistance.getValue(), 'f', 3);
  this->nearclippingedit->setText(s);
  s.setNum(cam->farDistance.getValue(), 'f', 3);
  this->farclippingedit->setText(s);
} // setEnabledClippingWidgets()

// *************************************************************************

/*!
  Create the UI representation of the preferences' settings for the
  manual control of the near and far clippping planes.
*/

QWidget *
SoQtFullViewer::makeAutoclipPreferences(QWidget * dialog)
{
  QWidget * w = new QWidget(dialog);

  // Initialize objects keeping track of geometry data.

  QSize totalsize(0, 0);

  QVBoxLayout * toplayout = new QVBoxLayout(w);

  // First, do the checkbutton widget.

  QCheckBox * c = new QCheckBox("Auto clipping planes", w);
  c->adjustSize();
  c->setChecked(this->isAutoClipping());
  QObject::connect(c, SIGNAL(toggled(bool)),
                   this, SLOT(clippingToggled(bool)));

  // Layout row 1.
  toplayout->addWidget(c, c->height());
  expandSize(totalsize, c->size(), LayoutVertical);

  // Do the three widgets on the second row (label, thumbwheel,
  // lineedit).

  QSize tmpsize = QSize(0, 0);

  this->nearclippinglabel = new QLabel("near plane", w);
  this->nearclippinglabel->adjustSize();
  expandSize(tmpsize, this->nearclippinglabel->size(), LayoutHorizontal);

  this->nearclippingwheel = new SoQtThumbWheel(SoQtThumbWheel::Horizontal, w);
  this->nearclippingwheel->setRangeBoundaryHandling( SoQtThumbWheel::ACCUMULATE );
  this->nearclippingwheel->adjustSize();
  this->nearclippingwheel->setEnabled( FALSE );
  expandSize(tmpsize, this->nearclippingwheel->size(), LayoutHorizontal);
  QObject::connect(this->nearclippingwheel, SIGNAL(wheelPressed()),
                   this, SLOT(increaseInteractiveCount()));
  QObject::connect(this->nearclippingwheel, SIGNAL(wheelMoved(float)),
                   this, SLOT(nearclippingwheelMoved(float)));
  QObject::connect(this->nearclippingwheel, SIGNAL(wheelReleased()),
                   this, SLOT(decreaseInteractiveCount()));

  this->nearclippingedit = new QLineEdit(w);
  this->nearclippingedit->adjustSize();
  expandSize(tmpsize, this->nearclippingedit->size(), LayoutHorizontal);
  QObject::connect(this->nearclippingedit, SIGNAL(returnPressed()),
                   this, SLOT(nearclipEditPressed()));


  // Layout row 2.
  QBoxLayout * layout = new QHBoxLayout;
  toplayout->addLayout(layout, tmpsize.height());
  layout->addWidget(this->nearclippinglabel, this->nearclippinglabel->width());
  layout->addWidget(this->nearclippingwheel, this->nearclippingwheel->width());
  layout->addWidget(this->nearclippingedit, this->nearclippingedit->width());
  expandSize(totalsize, tmpsize, LayoutVertical);


  // Do the three widgets on the third row (label, thumbwheel,
  // lineedit).

  tmpsize = QSize(0, 0);

  this->farclippinglabel = new QLabel("far plane", w);
  this->farclippinglabel->adjustSize();
  expandSize(tmpsize,
             QSize(QMAX(this->nearclippinglabel->width(),
                        this->farclippinglabel->width()),
                   this->farclippinglabel->height()),
             LayoutHorizontal);

  this->farclippingwheel = new SoQtThumbWheel(SoQtThumbWheel::Horizontal, w);
  this->farclippingwheel->setRangeBoundaryHandling( SoQtThumbWheel::ACCUMULATE );
  this->farclippingwheel->adjustSize();
  this->farclippingwheel->setEnabled( FALSE );
  expandSize(tmpsize, this->farclippingwheel->size(), LayoutHorizontal);
  QObject::connect(this->farclippingwheel, SIGNAL(wheelPressed()),
                   this, SLOT(increaseInteractiveCount()));
  QObject::connect(this->farclippingwheel, SIGNAL(wheelMoved(float)),
                   this, SLOT(farclippingwheelMoved(float)));
  QObject::connect(this->farclippingwheel, SIGNAL(wheelReleased()),
                   this, SLOT(decreaseInteractiveCount()));

  this->farclippingedit = new QLineEdit(w);
  this->farclippingedit->adjustSize();
  expandSize(tmpsize, this->farclippingedit->size(), LayoutHorizontal);
  QObject::connect(this->farclippingedit, SIGNAL(returnPressed()),
                   this, SLOT(farclipEditPressed()));

  // Layout row 3.
  layout = new QHBoxLayout;
  toplayout->addLayout(layout, tmpsize.height());
  layout->addWidget(this->farclippinglabel,
                    QMAX(this->nearclippinglabel->width(),
                         this->farclippinglabel->width()));
  layout->addWidget(this->farclippingwheel, this->farclippingwheel->width());
  layout->addWidget(this->farclippingedit, this->farclippingedit->width());
  expandSize(totalsize, tmpsize, LayoutVertical);

  this->setEnabledClippingWidgets(!this->isAutoClipping());

  w->resize(totalsize);
  toplayout->activate();

  return w;
} // makeAutoclipPreferences()

// *************************************************************************

/*!
  Set camera zoom value.
*/

void
SoQtFullViewer::setCameraZoom(const float val)
{
  SoCamera * cam = this->getCamera();
  if ( ! cam ) return; // can happen for empty scenegraph

  SoType t = cam->getTypeId();

  if (t.isDerivedFrom(SoPerspectiveCamera::getClassTypeId()))
    ((SoPerspectiveCamera *)cam)->heightAngle = val * 2.0f * M_PI / 360.0f;
  else if (t.isDerivedFrom(SoOrthographicCamera::getClassTypeId()))
    ((SoOrthographicCamera *)cam)->height = val;
#if SOQT_DEBUG
  else assert(0);
#endif // SOQT_DEBUG
} // setCameraZoom()

// *************************************************************************

/*!
  Return camera zoom value.
*/

float
SoQtFullViewer::getCameraZoom(void)
{
  SoCamera * cam = this->getCamera();
  if ( ! cam ) return 0.0f; // can happen for empty scenegraph

  SoType t = cam->getTypeId();

  if (t.isDerivedFrom(SoPerspectiveCamera::getClassTypeId()) )
    return ((SoPerspectiveCamera *)cam)->heightAngle.getValue() /
      2.0f * 360.0f / M_PI;
  else if (t.isDerivedFrom(SoOrthographicCamera::getClassTypeId()) )
    return ((SoOrthographicCamera *)cam)->height.getValue();

#if SOQT_DEBUG
  assert(0);
#endif // SOQT_DEBUG
  return 0.0f;
} // getCameraZoom()

// *************************************************************************

/*!
  Update the Qt slider representing the camera zoom.
*/

void
SoQtFullViewer::setZoomSliderPosition(float zoom)
{
  if (!this->prefwindow) return;

  float f =
    (zoom - this->zoomrange[0]) / (this->zoomrange[1] - this->zoomrange[0]);
  f = QMAX(0.0f, QMIN(f, 1.0f)) * ZOOMSLIDERRESOLUTION;

  this->zoomslider->setValue(f);
} // setZoomSliderPosition()

// *************************************************************************

/*!
  Set string in the camera zoom edit field.
*/

void
SoQtFullViewer::setZoomFieldString(float zoom)
{
  if (!this->prefwindow) return;

  QString s;
  s.setNum(zoom, 'f', 1);
  this->zoomfield->setText(s);
} // setZoomFieldString()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::interactbuttonClicked(
  void )
{
  if ( this->interactbutton )
    ((QPushButton *)this->interactbutton)->setOn(TRUE);
  if ( this->viewbutton )
    ((QPushButton *)this->viewbutton)->setOn(FALSE);
  if ( this->isViewing() )
    this->setViewing(FALSE);
} // interactbuttonToggled()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::viewbuttonClicked(
  void )
{
  if ( this->interactbutton )
    ((QPushButton *)this->interactbutton)->setOn(FALSE);
  if ( this->viewbutton )
    ((QPushButton *)this->viewbutton)->setOn(TRUE);
  if ( ! this->isViewing() )
    this->setViewing(TRUE);
} // viewbuttonToggled()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::helpbuttonClicked()
{
  this->openViewerHelpCard();
} // helpbuttonClicked()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::homebuttonClicked()
{
  this->resetToHomePosition();
} // homebuttonClicked()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::sethomebuttonClicked()
{
  this->saveHomePosition();
} // sethomebuttonClicked()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::viewallbuttonClicked()
{
  this->viewAll();
} // viewallbuttonClicked()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::seekbuttonClicked()
{
  this->setSeekMode(this->isSeekMode() ? FALSE : TRUE);
} // seekbuttonClicked()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::selectedViewing()
{
  this->setViewing(this->isViewing() ? FALSE : TRUE);
} // selectedViewing()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::selectedDecoration()
{
  this->setDecoration(this->isDecoration() ? FALSE : TRUE);
} // selectedDecoration()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::selectedHeadlight()
{
  this->setHeadlight(this->isHeadlight() ? FALSE : TRUE);
} // selectedHeadlight()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::copyviewSelected()
{
  this->copyView(SbTime::getTimeOfDay());
} // copyviewSelected()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::pasteviewSelected()
{
  this->pasteView(SbTime::getTimeOfDay());
} // pasteviewSelected()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::selectedPrefs(void)
{
  if (!this->prefwindow) this->prefwindow = this->makePreferencesWindow();
  this->prefwindow->show();
  this->prefwindow->raise();
} // selectedPrefs()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::seekAnimationTimeChanged(const char * s)
{
  float val;
  if ((sscanf(s, "%f", &val) == 1) && (val >= 0.0f)) this->setSeekTime(val);
} // seekAnimationTimeChanged()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::seekAnimationTimeChanged(const QString & s)
{
  bool ok;
  float val = s.toFloat(&ok);
  if (ok && (val >= 0.0f)) this->setSeekTime(val);
} // seekAnimationTimeChanged()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::seekDetailToggled(int id)
{
  if (id == 0) this->setDetailSeek(TRUE);
  else if (id == 1) this->setDetailSeek(FALSE);
  else assert(0);
} // seekDetailToggled()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::seekDistanceWheelChanged(float val)
{
  if (val < 0.1f) {
    val = 0.1f;
    this->seekdistancewheel->setValue( val );
  }

  this->setSeekDistance(val * val);

  QString s;
  s.setNum(this->getSeekDistance(), 'f', 2);
  this->seekdistancefield->setText(s);
} // seekDistanceWheelChanged()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::seekDistanceEdit()
{
  float val;
  if ((sscanf(this->seekdistancefield->text(), "%f", &val) == 1) &&
      (val > 0.0f)) {
    this->setSeekDistance(val);
    this->seekdistancewheel->setValue(sqrt(val));
  }
  else {
    QString s;
    s.setNum(this->getSeekDistance(), 'f', 2);
    this->seekdistancefield->setText(s);
  }
} // seekDistanceEdit()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::seekDistanceTypeToggle(int id)
{
  this->setSeekValueAsPercentage(id == 0 ? TRUE : FALSE);
} // seekDistanceTypeToggle()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::zoomSliderMoved(int val)
{
  float f = val / float(ZOOMSLIDERRESOLUTION);
  f = this->zoomrange[0] + f * (this->zoomrange[1] - this->zoomrange[0]);

  this->setCameraZoom(f);
  this->setZoomFieldString(f);
} // zoomSliderMoved()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::zoomFieldChanged()
{
  float val;
  if (sscanf(this->zoomfield->text(), "%f", &val) == 1) {
    val = QMIN(0.001f, QMAX(179.999f, val));
    this->setCameraZoom(val);
    this->setZoomSliderPosition(val);
  }
  else {
    QString s;
    s.setNum(this->getCameraZoom(), 'f', 1);
    this->zoomfield->setText(s);
  }
} // zoomFieldChanged()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::zoomRangeChanged1()
{
  float val;
  if (sscanf(this->zoomrangefrom->text(), "%f", &val) == 1) {
    if (val > 0.0f && val < 180.0f && val < this->zoomrange[1]) {
      this->zoomrange[0] = val;
      this->setZoomSliderPosition(this->getCameraZoom());
    }
  }
  else {
    QString s;
    s.setNum(this->zoomrange[0], 'f', 1);
    this->zoomrangefrom->setText(s);
  }
} // zoomRangeChanged1()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::zoomRangeChanged2()
{
  float val;
  if (sscanf(this->zoomrangeto->text(), "%f", &val) == 1) {
    if (val > 0.0f && val < 180.0f && val > this->zoomrange[0]) {
      this->zoomrange[1] = val;
      this->setZoomSliderPosition(this->getCameraZoom());
    }
  }
  else {
    QString s;
    s.setNum(this->zoomrange[1], 'f', 1);
    this->zoomrangeto->setText(s);
  }
} // zoomRangeChanged2()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::clippingToggled(bool flag)
{
  this->setAutoClipping(flag);
  this->setEnabledClippingWidgets(!flag);
} // clippingToggled()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::increaseInteractiveCount()
{
  this->interactiveCountInc();
} // increaseInteractiveCount()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::decreaseInteractiveCount()
{
  this->interactiveCountDec();
} // decreaseInteractiveCount()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::nearclippingwheelMoved(float val)
{
  assert( nearclippingwheel != NULL && this->farclippingwheel != NULL );
  if ( val < 0.001f ) {
    val = 0.001f;
    this->nearclippingwheel->setValue( val );
  }
  float farval = this->farclippingwheel->value();
  if ( val >= farval ) {
    val = farval - 0.001f;
    this->nearclippingwheel->setValue( val );
  }

  SoCamera * cam = this->getCamera();
  if (!cam) return;

  // FIXME: cut off at 0.0? And against far clipping value? 990223 mortene.
  cam->nearDistance = val;

  QString s;
  s.setNum(cam->nearDistance.getValue(), 'f', 3);
  this->nearclippingedit->setText(s);
} // nearclippingwheelMoved()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::farclippingwheelMoved(float val)
{
  assert( nearclippingwheel != NULL && this->farclippingwheel != NULL );
  float nearval = this->nearclippingwheel->value();
  if ( nearval < 0.001f ) nearval = 0.001f;
  if ( val <= nearval ) {
    val = nearval + 0.001f;
    this->farclippingwheel->setValue( val );
  }

  SoCamera * cam = this->getCamera();
  if (!cam) return;

  // FIXME: cut off at 0.0? And against near clipping value? 990223 mortene.
  cam->farDistance = val;

  QString s;
  s.setNum(cam->farDistance.getValue(), 'f', 3);
  this->farclippingedit->setText(s);
} // farclippingwheelMoved()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::nearclipEditPressed()
{
  SoCamera * cam = this->getCamera();
  if (!cam) return;

  float val;
  if (sscanf(this->nearclippingedit->text(), "%f", &val) == 1) {
    // FIXME: sanity check on val? 990223 mortene.
    cam->nearDistance = val;
    this->nearclippingwheel->setValue(val);
  }
  else {
    QString s;
    s.setNum(cam->nearDistance.getValue(), 'f', 3);
    this->nearclippingedit->setText(s);
  }
} // nearclipEditPressed()

// *************************************************************************

/*!
  \internal
  Qt slot.
*/

void
SoQtFullViewer::farclipEditPressed()
{
  SoCamera * cam = this->getCamera();
  if (!cam) return;

  float val;
  if (sscanf(this->farclippingedit->text(), "%f", &val) == 1) {
    // FIXME: sanity check on val? 990223 mortene.
    cam->farDistance = val;
    this->farclippingwheel->setValue(val);
  }
  else {
    QString s;
    s.setNum(cam->farDistance.getValue(), 'f', 3);
    this->farclippingedit->setText(s);
  }
} // farclipEditPressed()

// *************************************************************************

/*!
  This method is invoked when the component size has changed.
*/

void
SoQtFullViewer::sizeChanged( // virtual
  const SbVec2s size )
{
#if SOQT_DEBUG && 0
  SoDebugError::postInfo( "SoQtFullViewer::sizeChanged", "[invoked (%d, %d)]",
    size[0], size[1] );
#endif // SOQT_DEBUG

  if ( this->decorations ) {
    if ( size[0] <= 60 || size[1] <= 30 ) return; // bogus
    if ( this->viewerwidget ) {
      // SoDebugError::postInfo( "SoQtFullViewer::sizeChanged", "[resizing]" );
      this->viewerwidget->setGeometry( 0, 0, size[0], size[1] );
      this->canvas->setGeometry( 30, 0, size[0] - 60, size[1] - 30 );
      this->leftDecoration->resize( 30, size[1] - 30 );
      this->rightDecoration->setGeometry( size[0]-30, 0, size[0], size[1] - 30 );
      this->bottomDecoration->setGeometry( 0, size[1]-30, size[0], size[1] );
    }
    const SbVec2s rasize = SbVec2s( size[0] - 60, size[1] - 30 );
    inherited::sizeChanged( rasize );
  } else {
    if ( size[0] <= 0 || size[1] <= 0 ) return;
    if ( this->viewerwidget && this->canvas ) {
      // SoDebugError::postInfo( "SoQtFullViewer::sizeChanged", "[resizing]" );
      this->viewerwidget->setGeometry( 0, 0, size[0], size[1] );
      this->canvas->setGeometry( 0, 0, size[0], size[1] );
    }
    inherited::sizeChanged( size );
  }
} // sizeChanged()

// *************************************************************************

/*!
*/

SbBool
SoQtFullViewer::processSoEvent(
  const SoEvent * const event )
{
  if ( common->processSoEvent(event) ||
       inherited::processSoEvent(event) )
    return TRUE;
  return FALSE;
} // processSoEvent()

// *************************************************************************

void
SoQtFullViewer::afterRealizeHook( // virtual
  void )
{
  SoDebugError::postInfo( "SoQtFullViewer::afterRealizeHook", "[invoked]" );
  this->sizeChanged( this->getSize() );
  inherited::afterRealizeHook();
} // afterRealizeHook()

// *************************************************************************

#if SOQT_DEBUG
static const char * getSoQtFullViewerRCSId(void) { return rcsid; }
#endif // SOQT_DEBUG

