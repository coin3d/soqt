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

/*!
  \class SoQtComponent SoQtComponent.h Inventor/Qt/SoQtComponent.h
  \brief The SoQtComponent class is the base class for all GUI components.

  Components in the SoQt component library all inherit this abstract base
  class. It provides basic methods for setting and querying about the
  relationship between the component object and its underlying Qt object(s).

  Users should not need to interface any code against this class, unless
  they want to extend the SoQt library in entirely new directions. For
  making new viewer components, for instance, other classes further down
  the inheritance hierarchy would be better suited for subclassing.

  Note that the relationship between all SoQtComponent derived classes and
  Qt widgets is one of "has-A", \e not "is-A" -- i.e. SoQtComponent does
  not inherit QWidget. It \e does however inherit QObject, which sole
  purpose is to provide the necessary support for Qt's signal and slot
  mechanisms (which is needed for some internal operations).
*/

// *************************************************************************

#if SOQT_DEBUG
static const char rcsid[] =
  "$Id$";
#endif // SOQT_DEBUG

#include <qwidget.h>
#include <qmainwindow.h>
#include <qmessagebox.h>
// FIXME: get rid of this before 1.0 release (convert everything to Qt
// version 2.x API). 19990630 mortene.
#if QT_VERSION >= 200
#include <q1xcompatibility.h>
#endif // Qt v2.x

#if SOQT_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // SOQT_DEBUG

#include <soqtdefs.h>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoQtComponent.h>
#include <Inventor/Qt/SoQtGLWidget.h>
#include <Inventor/Qt/SoQtRenderArea.h>
#include <Inventor/Qt/viewers/SoQtViewer.h>
#include <Inventor/Qt/viewers/SoQtFullViewer.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/Qt/viewers/SoQtPlaneViewer.h>
#include <Inventor/Qt/viewers/SoQtConstrainedViewer.h>
#include <Inventor/Qt/viewers/SoQtWalkViewer.h>
#include <Inventor/Qt/viewers/SoQtFlyViewer.h>
#include <Inventor/Qt/SoQtSliderSetBase.h>
#include <Inventor/Qt/SoQtSliderSet.h>
#include <Inventor/Qt/SoQtLightSliderSet.h>
#include <Inventor/Qt/SoQtMaterialSliderSet.h>
#include <Inventor/Qt/SoQtTransformSliderSet.h>

// debug
#define SOQTCOMP_RESIZE_DEBUG 0

static const char nullstring[] = "(null)";

// *************************************************************************

// The private data for the SoQtComponent.

class SoQtComponentP {
public:
  // Constructor.
  SoQtComponentP(SoQtComponent * o) {
    this->owner = o;

    if ( !SoQtComponentP::soqtcomplist )
      SoQtComponentP::soqtcomplist = new SbList<SoQtComponent *>;
    SoQtComponentP::soqtcomplist->append(this->owner);
  }

  // Destructor.
  ~SoQtComponentP() {
    if ( SoQtComponentP::soqtcomplist->getLength() == 0 ) {
      delete SoQtComponentP::soqtcomplist;
      SoQtComponentP::soqtcomplist = NULL;
    }
  }

  // Variables.

  QWidget * parent;
  QWidget * widget;
  SbBool embedded, shelled;
  QString classname, widgetname, captiontext, icontext;
  SoQtComponentCB * closeCB;
  void * closeCBdata;
  SbPList * visibilitychangeCBs;
  SbBool realized;
  SbVec2s storesize;

  // List of all SoQtComponent instances. Needed for the
  // SoQtComponent::getComponent() function.
  static SbList<SoQtComponent *> * soqtcomplist;

private:
  SoQtComponent * owner;
};

SbList<SoQtComponent *> * SoQtComponentP::soqtcomplist = NULL;

#define THIS (this->pimpl)

// *************************************************************************

SOQT_OBJECT_ABSTRACT_SOURCE(SoQtComponent);

void
SoQtComponent::initClasses(
  void )
{
  SoQtComponent::initClass();
  SoQtGLWidget::initClass();
  SoQtRenderArea::initClass();
  SoQtViewer::initClass();
  SoQtFullViewer::initClass();
  SoQtExaminerViewer::initClass();
  SoQtPlaneViewer::initClass();
  SoQtConstrainedViewer::initClass();
  SoQtWalkViewer::initClass();
  SoQtFlyViewer::initClass();
  SoQtSliderSetBase::initClass();
  SoQtSliderSet::initClass();
  SoQtLightSliderSet::initClass();
  SoQtMaterialSliderSet::initClass();
  SoQtTransformSliderSet::initClass();
} // initClasses()

// *************************************************************************

/*!
  \fn virtual const char * SoQtComponent::componentClassName(void) const

  Returns class name of the component.
 */

/*!
  \var QWidget * SoQtComponent::widget

  Pointer to the Qt widget. This member must be set from all component
  classes which inherits SoQtComponent directly.
*/

// *************************************************************************

/*!
  Constructor.

  \a parent is the widget we'll build this component inside. If \a
  parent is \c NULL, make a new toplevel window.

  \a name is mostly interesting for debugging purposes.

  \a buildInsideParent specifies whether or not we should make a new
  toplevel window for the component even when we've got a non-NULL \a
  parent.
*/

SoQtComponent::SoQtComponent(
  QWidget * const parent,
  const char * const name,
  const SbBool embed )
{
  THIS = new SoQtComponentP(this);

  THIS->realized = FALSE;
  THIS->shelled = FALSE;
  THIS->widget = NULL;
  THIS->parent = parent;
  THIS->closeCB = NULL;
  THIS->closeCBdata = NULL;
  THIS->visibilitychangeCBs = NULL;

  if ( name )
    THIS->widgetname = name;

  THIS->classname = "SoQtComponent";

  THIS->storesize.setValue( -1, -1 );

  if ( (parent == NULL) || ! embed ) {
    THIS->parent = (QWidget *) new QMainWindow( parent, name );
    this->registerWidget( parent );
    THIS->embedded = FALSE;
    THIS->shelled = TRUE;
  } else {
    THIS->parent = parent;
    THIS->embedded = TRUE;
  }
  THIS->parent->installEventFilter( this );
} // SoQtComponent()

/*!
  Destructor.
*/

SoQtComponent::~SoQtComponent(
  void )
{
  if ( ! THIS->embedded )
    this->unregisterWidget( THIS->parent );

  int idx = SoQtComponentP::soqtcomplist->find(this);
  assert(idx != -1);
  SoQtComponentP::soqtcomplist->remove(idx);

  delete THIS->visibilitychangeCBs;

  // If we've got a toplevel widget on our hands it won't
  // automatically be deallocated (there's no real parent widget).
  if (THIS->widget && !THIS->widget->parentWidget()) delete THIS->widget;

  delete THIS;
} // ~SoQtComponent()

/*!
  Add a callback which will be called whenever the widget component
  changes visibility status (because of iconification or
  deiconification, for instance).

  \sa removeVisibilityChangeCallback(), isVisible()
*/

void
SoQtComponent::addVisibilityChangeCallback(
  SoQtComponentVisibilityCB * const func,
  void * const user )
{
  if ( ! THIS->visibilitychangeCBs )
    THIS->visibilitychangeCBs = new SbPList;

  THIS->visibilitychangeCBs->append( (void *) func );
  THIS->visibilitychangeCBs->append( user );
} // addVisibilityChangeCallback()

/*!
  Remove one of the callbacks from the list of visibility notification
  callbacks.

  \sa addVisibilityChangeCallback(), isVisible()
*/

void
SoQtComponent::removeVisibilityChangeCallback(
  SoQtComponentVisibilityCB * const func,
  void * const data )
{
#if SOQT_DEBUG
  if ( ! THIS->visibilitychangeCBs ) {
    SoDebugError::postWarning("SoQtComponent::removeVisibilityChangeCallback",
                              "empty callback list");
    return;
  }
#endif // SOQT_DEBUG

  int idx = THIS->visibilitychangeCBs->find( (void *) func);
  if (idx != -1 ) {
    THIS->visibilitychangeCBs->remove(idx);
    THIS->visibilitychangeCBs->remove(idx);
  }

#if SOQT_DEBUG
  if (idx == -1) {
    SoDebugError::postWarning("SoQtComponent::removeVisibilityChangeCallback",
                              "tried to remove non-existant callback");
    return;
  }
#endif // SOQT_DEBUG
} // removeVisibilityChangeCallback()

/*!
  Set class name of widget.

  \sa getClassName(), componentClassName()
*/

void
SoQtComponent::setClassName(
  const char * const name )
{
  THIS->classname = name;
} // setClassName()

// *************************************************************************

/*!
  Set the core widget for this SoQt component. It is important that
  subclasses get this correct, as the widget set here will be the
  widget returned from query methods.

  \sa baseWidget()
*/

void
SoQtComponent::setBaseWidget(
  QWidget * const widget )
{
//  SoDebugError::postInfo( "SoQtComponent::setBaseWidget", "[invoked]" );
  assert( widget );

//  if ( THIS->parent )
//    THIS->parent->removeEventFilter( this );
  if ( THIS->widget )
    THIS->widget->removeEventFilter( this );

  THIS->widget = widget;
//  THIS->parent = widget->parentWidget();

#if 0 // debug
  SoDebugError::postInfo("SoQtComponent::setBaseWidget",
                         "widget: %p, parent: %p", w, THIS->parent);
#endif // debug


#if 0 // debug
  if (!THIS->captiontext.isNull()) {
    SoDebugError::postInfo("SoQtComponent::setBaseWidget",
                           "setCaption('%s')",
                           (const char *)THIS->captiontext);
  }
#endif // debug
  if (THIS->captiontext.isNull()) THIS->captiontext = this->getDefaultTitle();
  this->getShellWidget()->setCaption(THIS->captiontext);

  if (THIS->icontext.isNull()) THIS->icontext = this->getDefaultIconTitle();
  this->getShellWidget()->setIconText(THIS->icontext);

  if (THIS->widgetname.isNull())
    THIS->widgetname = this->getDefaultWidgetName();
  THIS->widget->setName(THIS->widgetname);

  // Need this to auto-detect resize events.
//  if (THIS->parent) THIS->parent->installEventFilter(this);
  THIS->widget->installEventFilter(this);
  QObject::connect(THIS->widget, SIGNAL(destroyed()),
                   this, SLOT(widgetClosed()));
#if 0 // debug
  SoDebugError::postInfo("SoQtComponent::setBaseWidget",
                         "installeventfilter, widget: %p", THIS->widget);
#endif // debug

//  if ( storesize[0] != -1 )
//    THIS->widget->resize( QSize( storesize[0], storesize[1] ) );
} // setBaseWidget()

// *************************************************************************

/*!
  \internal

  Helps us detect changes in size (base widget and parent widget)
  and visibility status.
*/

bool
SoQtComponent::eventFilter( // virtual
  QObject * obj,
  QEvent * e )
{
#if 0 // debug
  static const char eventnaming[][50] = {
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

  SoDebugError::postInfo("SoQtComponent::eventFilter", "%p: %s",
                         obj, eventnaming[e->type()]);
#endif // debug

  if (e->type() == Event_Resize) {
    QResizeEvent * r = (QResizeEvent *)e;

    if (obj == (QObject *)THIS->parent) {
#if SOQTCOMP_RESIZE_DEBUG  // debug
      SoDebugError::postInfo("SoQtComponent::eventFilter",
                             "resize on parent (%p) to %p: (%d, %d)",
                             THIS->parent, THIS->widget,
                             r->size().width(), r->size().height());
#endif // debug
      THIS->widget->resize(r->size());
      THIS->storesize.setValue( r->size().width(), r->size().height() );
      this->sizeChanged(THIS->storesize);
    }
    else if (obj == (QObject *)THIS->widget) {
      THIS->storesize.setValue(r->size().width(), r->size().height());
      this->sizeChanged(THIS->storesize);
    }
  }
  // Detect visibility changes.
  else if (obj == THIS->widget &&
           (e->type() == Event_Show || e->type() == Event_Hide)) {
    if (THIS->visibilitychangeCBs) {
      for (int i=0; i < THIS->visibilitychangeCBs->getLength()/2; i++) {
        SoQtComponentVisibilityCB * cb =
          (SoQtComponentVisibilityCB *)(*(THIS->visibilitychangeCBs))[i*2+0];
        void * userdata = (*(THIS->visibilitychangeCBs))[i*2+1];
        cb(userdata, e->type() == Event_Show ? TRUE : FALSE);
      }
    }
  }

  // It would seem more sensible that we should trigger on
  // Event_Create than on Event_Show for the afterRealizeHook()
  // method, but the Event_Create type is not yet used in Qt (as of
  // version 2.2.2 at least) -- it has just been reserved for future
  // releases.
  if (e->type() == Event_Show && !THIS->realized) {
    THIS->realized = TRUE;
    this->afterRealizeHook();
  }

  return FALSE;
} // eventFilter()

// *************************************************************************

/*!
  This function \e must be called by subclasses after the component's
  widget has been otherwise initialized.
*/

/*
void
SoQtComponent::subclassInitialized(
  void )
{
#if SOQT_DEBUG
  if(!THIS->widget) {
    SoDebugError::postWarning("SoQtComponent::subclassInitialized",
                              "Called while no QWidget has been set.");
    return;
  }
#endif // SOQT_DEBUG
} // subclassInitialized()
*/

// *************************************************************************

/*!
  This will show the widget, deiconifiying and raising it if
  necessary.

  \sa hide(), isVisible()
*/

void
SoQtComponent::show(
  void )
{
#if SOQT_DEBUG
  if(!THIS->widget) {
    SoDebugError::postWarning("SoQtComponent::show",
                              "Called while no QWidget has been set.");
    return;
  }
#endif // SOQT_DEBUG

#if SOQTCOMP_RESIZE_DEBUG  // debug
  SoDebugError::postInfo("SoQtComponent::show-1",
                         "resizing %p: (%d, %d)",
                         THIS->widget,
                         THIS->storesize[0], THIS->storesize[1]);
#endif // debug

  if ( THIS->shelled )
    THIS->parent->resize(THIS->storesize[0], THIS->storesize[1]);
  else
    THIS->widget->resize(THIS->storesize[0], THIS->storesize[1]);

#if SOQTCOMP_RESIZE_DEBUG  // debug
  SoDebugError::postInfo("SoQtComponent::show-2",
                         "resized %p: (%d, %d)",
                         THIS->widget,
                         THIS->widget->size().width(),
                         THIS->widget->size().height());
#endif // debug

  if ( THIS->shelled )
    THIS->parent->show();
  THIS->widget->show();

#if SOQTCOMP_RESIZE_DEBUG  // debug
  SoDebugError::postInfo("SoQtComponent::show-3",
                         "showed %p: (%d, %d)",
                         THIS->widget,
                         THIS->widget->size().width(),
                         THIS->widget->size().height());
#endif // debug

  THIS->widget->raise();
#if SOQTCOMP_RESIZE_DEBUG  // debug
  SoDebugError::postInfo("SoQtComponent::show-4",
                         "raised %p: (%d, %d)",
                         THIS->widget,
                         THIS->widget->size().width(),
                         THIS->widget->size().height());
#endif // debug
  this->sizeChanged( THIS->storesize );
} // show()

/*!
  This will hide the widget.

  \sa show(), isVisible()
*/

void
SoQtComponent::hide(
  void )
{
#if SOQT_DEBUG
  if(!THIS->widget) {
    SoDebugError::postWarning("SoQtComponent::hide",
                              "Called while no QWidget has been set.");
    return;
  }
#endif // SOQT_DEBUG

  if ( THIS->shelled )
    THIS->parent->hide();
  THIS->widget->hide();
} // hide()

// *************************************************************************

/*!
  Returns visibility status on the widget. If any parents of this
  widget or this widget itself is hidden, returns \c FALSE.

  Note that a widget which is just obscured by other windows on the
  desktop is not hidden in this sense, and \c TRUE will be returned.

  \sa show(), hide()
*/

SbBool
SoQtComponent::isVisible(
  void )
{
  if ( ! THIS->widget )
    return FALSE;
  return THIS->widget->isVisible() && THIS->widget->isVisibleToTLW();
} // isVisible()

/*!
  Returns a pointer to the component's window system widget.

  \sa getShellWidget(), getParentWidget()
*/

QWidget *
SoQtComponent::getWidget(
  void ) const
{
  return THIS->widget;
} // getWidget()

/*!
  An SoQtComponent may be composed of any number of widgets in
  parent-children relationships in a tree structure with any depth.
  This method will return the root widget in that tree.

  \sa setBaseWidget()
*/

QWidget *
SoQtComponent::baseWidget(
  void ) const
{
  return THIS->widget;
} // baseWidget()

/*!
  Returns \c TRUE if this component is a toplevel shell, i.e. it has a
  window representation on the desktop.

  \sa getShellWidget()
*/

SbBool
SoQtComponent::isTopLevelShell(
  void ) const
{
#if SOQT_DEBUG && 0
  if ( ! THIS->widget ) {
    SoDebugError::postWarning( "SoQtComponent::isTopLevelShell",
      "Called while no QWidget has been set." );
    return FALSE;
  }
#endif // SOQT_DEBUG
  return THIS->embedded ? FALSE : TRUE;
} // isTopLevelShell()

/*!
  Returns the toplevel shell widget for this component. The toplevel
  shell is the desktop window which contains the component.

  \sa isTopLevelShell(), getWidget()
*/

QWidget *
SoQtComponent::getShellWidget(
  void ) const
{
  return THIS->parent;
  if ( THIS->widget )
    return THIS->widget->topLevelWidget();
  if ( THIS->parent )
    return THIS->parent->topLevelWidget();
#if SOQT_DEBUG
  SoDebugError::postWarning("SoQtComponent::getShellWidget",
                            "No base widget or parent widget.");
#endif // SOQT_DEBUG
  return NULL;
} // getShellWidget()

/*!
  Returns the widget which is the parent (i.e. contains) this
  component's base widget.

  \sa getWidget(), baseWidget(), isTopLevelShell()
*/

QWidget *
SoQtComponent::getParentWidget(
  void ) const
{
  return THIS->parent;
} // getParentWidget()

/*!
  Set the window title of this component. This will not work unless
  the component is a toplevel shell.

  \sa getTitle(), setIconTitle(), isTopLevelShell()
*/

void
SoQtComponent::setTitle(
  const char * const title )
{
  THIS->captiontext = title;
  if ( THIS->widget )
    this->getShellWidget()->setCaption( title );
} // setTitle()

/*!
  Returns the window title. The component should be a toplevel shell
  if you call this method.

  \sa setTitle(), isTopLevelShell()
*/

const char *
SoQtComponent::getTitle(
  void ) const
{
  return
    THIS->captiontext.isNull() ? nullstring : (const char *) THIS->captiontext;
} // getTitle()

/*!
  Sets the window's title when it is iconfied. The component you use
  this method on should be a toplevel shell.

  \sa getIconTitle(), setTitle(), isTopLevelShell()
*/

void
SoQtComponent::setIconTitle(
  const char * const title )
{
  THIS->icontext = title;
  if (THIS->widget)
    this->getShellWidget()->setIconText( title );
} // setIconTitle()

/*!
  Returns the title the window has when iconfied. The component should
  be a toplevel shell if you use this method.

  \sa setIconTitle(), isTopLevelShell()
*/

const char *
SoQtComponent::getIconTitle(
  void ) const
{
  return THIS->icontext.isNull() ? nullstring : (const char *)THIS->icontext;
} // getIconTitle()

/*!
  Returns name of the widget.
*/

const char *
SoQtComponent::getWidgetName(
  void ) const
{
  return
    THIS->widgetname.isNull() ? nullstring : (const char *)THIS->widgetname;
} // getWidgetName()

/*!
  Returns class name of widget.
*/

const char *
SoQtComponent::getClassName(
  void ) const
{
  return (const char *)THIS->classname;
} // getClassName()

/*!
  Returns the default name of an SoQtComponent widget. Should be
  overloaded by subclasses.
*/

const char *
SoQtComponent::getDefaultWidgetName(
  void ) const
{
  return "SoQtComponent";
} // getDefaultWidgetName()

/*!
  Returns the default window caption string of this component. Should
  be overloaded by subclasses.
*/

const char *
SoQtComponent::getDefaultTitle(
  void ) const
{
  return "Qt Component";
} // getDefaultTitle()

/*!
  Returns the default icon title of this component. Should be
  overloaded by subclasses.
*/

const char *
SoQtComponent::getDefaultIconTitle(
  void ) const
{
  return "Qt Comp";
} // getDefaultIconTitle()

// *************************************************************************

/*!
  Resize the component widget.

  \sa getSize()
*/

void
SoQtComponent::setSize(
  const SbVec2s size )
{
#if SOQT_DEBUG
  if((size[0] <= 0) || (size[1] <= 0)) {
    SoDebugError::postWarning("SoQtComponent::setSize",
                              "Invalid size setting: <%d, %d>.",
                              size[0], size[1]);
    return;
  }
#endif // SOQT_DEBUG

#if SOQTCOMP_RESIZE_DEBUG  // debug
  SoDebugError::postInfo("SoQtComponent::setSize",
                         "resize %p: (%d, %d)",
                         THIS->widget,
                         size[0], size[1]);
#endif // debug
  if ( this->isTopLevelShell() ) {
    QWidget * shell = this->getShellWidget();
    if ( shell ) shell->resize( size[0], size[1] );
  }
  THIS->storesize = size;
  this->sizeChanged( size );
} // setSize()

/*!
  Returns the component widget size.

  \sa setSize()
*/

SbVec2s
SoQtComponent::getSize(
  void ) const
{
  return THIS->storesize;
} // getSize()

/*!
  This method is invoked to notify the component that the size has
  changed.  It is called from the top and all the way down to the
  bottom, the size being adjusted to take into account extra
  decorations having been added at each level in the component class
  hierarchy.

  This default implementation does nothing.
*/

void
SoQtComponent::sizeChanged(
  const SbVec2s )
{
  // nada
} // sizeChanged()

// *************************************************************************

/*!
  Open a dialog providing help about use of this component.

  NB: no help system has been implemented yet, so for the time being
  this will only pop up an error message.
*/

void
SoQtComponent::openHelpCard(
  const char * const name )
{
  // FIXME: code MiA. 19990222 mortene.
  QMessageBox::warning( NULL, "SoQt",
                        "The help functionality has not been "
                        "implemented." );
} // openHelpCard()

/*!
  Set up a callback function to use when the component gets closed. A
  component must be a toplevel shell for this to have any effect.

  For toplevel shells with no close callback set, the window will
  simply be hidden. The typical action to take in the callback would
  be to delete the component.

  \sa isTopLevelShell()
*/

void
SoQtComponent::setWindowCloseCallback(
  SoQtComponentCB * const func,
  void * const data )
{
  THIS->closeCB = func;
  THIS->closeCBdata = data;
}

/*!
  \internal

  SLOT for when the user clicks/selects window decoration close.
*/

void
SoQtComponent::widgetClosed(
  void )
{
  if ( THIS->closeCB )
    THIS->closeCB( THIS->closeCBdata, this );
} // widgetClosed()

// *************************************************************************

/*!
  Finds and returns the SoQtComponent corresponding to the given
  QWidget, if any. If no SoQtComponent is the "owner" of the widget,
  \c NULL will be returned.
 */

SoQtComponent *
SoQtComponent::getComponent(
  QWidget * const widget )
{
  for (int i = 0; i < SoQtComponentP::soqtcomplist->getLength(); i++) {
    SoQtComponent * c = (*SoQtComponentP::soqtcomplist)[i];
    if ( c->getWidget() == widget ) return c;
  }

  return NULL;
} // getComponent()

// *************************************************************************

/*!
*/

void
SoQtComponent::registerWidget(
  QWidget * widget )
{
  // nada yet
} // registerWidget()

/*!
*/

void
SoQtComponent::unregisterWidget(
  QWidget * widget )
{
  // nada yet
} // unregisterWidget()

// *************************************************************************

void
SoQtComponent::afterRealizeHook( // virtual
  void )
{
}

// *************************************************************************
