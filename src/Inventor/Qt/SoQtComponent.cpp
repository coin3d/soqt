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

#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <qwidget.h>
#include <qmainwindow.h>
#include <qmessagebox.h>
#include <qapplication.h>
#include <qmetaobject.h>
#include <moc_SoQtComponent.cpp>

#include <Inventor/errors/SoDebugError.h>

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

    if (!SoQtComponentP::soqtcomplist)
      SoQtComponentP::soqtcomplist = new SbPList;
    SoQtComponentP::soqtcomplist->append((void *) this->owner);
  }

  // Destructor.
  ~SoQtComponentP() {
    if (SoQtComponentP::soqtcomplist->getLength() == 0) {
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
  SbBool fullscreen;

  // List of all SoQtComponent instances. Needed for the
  // SoQtComponent::getComponent() function.
  static SbPList * soqtcomplist;

private:
  SoQtComponent * owner;
};

SbPList * SoQtComponentP::soqtcomplist = NULL;

#define PRIVATE(o) (o->pimpl)

// *************************************************************************

SOQT_OBJECT_ABSTRACT_SOURCE(SoQtComponent);

/*!
  \internal
  This function initializes the type system for all the component classes.
  It is called indirectly when you call SoQt::init().
*/

void
SoQtComponent::initClasses(
  void)
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
  const SbBool embed)
{
  PRIVATE(this) = new SoQtComponentP(this);

  PRIVATE(this)->realized = FALSE;
  PRIVATE(this)->shelled = FALSE;
  PRIVATE(this)->widget = NULL;
  PRIVATE(this)->parent = parent;
  PRIVATE(this)->closeCB = NULL;
  PRIVATE(this)->closeCBdata = NULL;
  PRIVATE(this)->visibilitychangeCBs = NULL;
  PRIVATE(this)->fullscreen = FALSE;

  if (name)
    PRIVATE(this)->widgetname = name;

  PRIVATE(this)->classname = "SoQtComponent";

  PRIVATE(this)->storesize.setValue(-1, -1);

  if ((parent == NULL) || ! embed) {
    PRIVATE(this)->parent = (QWidget *) new QMainWindow(parent, name);
    this->registerWidget(parent);
    PRIVATE(this)->embedded = FALSE;
    PRIVATE(this)->shelled = TRUE;
  } else {
    PRIVATE(this)->parent = parent;
    PRIVATE(this)->embedded = TRUE;
  }
  PRIVATE(this)->parent->installEventFilter(this);
} // SoQtComponent()

/*!
  Destructor.
*/

SoQtComponent::~SoQtComponent(
  void)
{
  if (! PRIVATE(this)->embedded)
    this->unregisterWidget(PRIVATE(this)->parent);

  int idx = SoQtComponentP::soqtcomplist->find((void *) this);
  assert(idx != -1);
  SoQtComponentP::soqtcomplist->remove(idx);

  delete PRIVATE(this)->visibilitychangeCBs;

  // If we've got a toplevel widget on our hands it won't
  // automatically be deallocated (there's no real parent widget).
  if (PRIVATE(this)->widget && !PRIVATE(this)->widget->parentWidget()) delete PRIVATE(this)->widget;

  delete PRIVATE(this);
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
  void * const user)
{
  if (! PRIVATE(this)->visibilitychangeCBs)
    PRIVATE(this)->visibilitychangeCBs = new SbPList;

  PRIVATE(this)->visibilitychangeCBs->append((void *) func);
  PRIVATE(this)->visibilitychangeCBs->append(user);
} // addVisibilityChangeCallback()

/*!
  Remove one of the callbacks from the list of visibility notification
  callbacks.

  \sa addVisibilityChangeCallback(), isVisible()
*/

void
SoQtComponent::removeVisibilityChangeCallback(
  SoQtComponentVisibilityCB * const func,
  void * const data)
{
#if SOQT_DEBUG
  if (! PRIVATE(this)->visibilitychangeCBs) {
    SoDebugError::postWarning("SoQtComponent::removeVisibilityChangeCallback",
                              "empty callback list");
    return;
  }
#endif // SOQT_DEBUG

  int idx = PRIVATE(this)->visibilitychangeCBs->find((void *) func);
  if (idx != -1) {
    PRIVATE(this)->visibilitychangeCBs->remove(idx);
    PRIVATE(this)->visibilitychangeCBs->remove(idx);
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
  const char * const name)
{
  PRIVATE(this)->classname = name;
} // setClassName()

// *************************************************************************

/*!
  Set the core widget for this SoQt component. It is important that
  subclasses get this correct, as the widget set here will be the
  widget returned from query methods.

  \sa baseWidget()
*/
void
SoQtComponent::setBaseWidget(QWidget * widget)
{
//  SoDebugError::postInfo("SoQtComponent::setBaseWidget", "[invoked]");
  assert(widget);

//  if (PRIVATE(this)->parent)
//    PRIVATE(this)->parent->removeEventFilter(this);
  if (PRIVATE(this)->widget)
    PRIVATE(this)->widget->removeEventFilter(this);

  PRIVATE(this)->widget = widget;
//  PRIVATE(this)->parent = widget->parentWidget();

#if 0 // debug
  SoDebugError::postInfo("SoQtComponent::setBaseWidget",
                         "widget: %p, parent: %p", w, PRIVATE(this)->parent);
#endif // debug


#if 0 // debug
  if (!PRIVATE(this)->captiontext.isNull()) {
    SoDebugError::postInfo("SoQtComponent::setBaseWidget",
                           "setCaption('%s')",
                           (const char *)PRIVATE(this)->captiontext);
  }
#endif // debug
  if (PRIVATE(this)->captiontext.isNull()) PRIVATE(this)->captiontext = this->getDefaultTitle();
  this->getShellWidget()->setCaption(PRIVATE(this)->captiontext);

  if (PRIVATE(this)->icontext.isNull()) PRIVATE(this)->icontext = this->getDefaultIconTitle();
  this->getShellWidget()->setIconText(PRIVATE(this)->icontext);

  if (PRIVATE(this)->widgetname.isNull())
    PRIVATE(this)->widgetname = this->getDefaultWidgetName();
  PRIVATE(this)->widget->setName(PRIVATE(this)->widgetname);

  // Need this to auto-detect resize events.
//  if (PRIVATE(this)->parent) PRIVATE(this)->parent->installEventFilter(this);
  PRIVATE(this)->widget->installEventFilter(this);
  QObject::connect(PRIVATE(this)->widget, SIGNAL(destroyed()),
                   this, SLOT(widgetClosed()));
#if 0 // debug
  SoDebugError::postInfo("SoQtComponent::setBaseWidget",
                         "installeventfilter, widget: %p", PRIVATE(this)->widget);
#endif // debug

//  if (storesize[0] != -1)
//    PRIVATE(this)->widget->resize(QSize(storesize[0], storesize[1]));
} // setBaseWidget()

// *************************************************************************

/*!
  \internal

  Helps us detect changes in size (base widget and parent widget)
  and visibility status.
*/

bool
SoQtComponent::eventFilter(// virtual
  QObject * obj,
  QEvent * e)
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

  if (e->type() == QEvent::Resize) {
    QResizeEvent * r = (QResizeEvent *)e;

    if (obj == (QObject *)PRIVATE(this)->parent) {
#if SOQTCOMP_RESIZE_DEBUG  // debug
      SoDebugError::postInfo("SoQtComponent::eventFilter",
                             "resize on parent (%p) to %p: (%d, %d)",
                             PRIVATE(this)->parent, PRIVATE(this)->widget,
                             r->size().width(), r->size().height());
#endif // debug
      PRIVATE(this)->widget->resize(r->size());
      PRIVATE(this)->storesize.setValue(r->size().width(), r->size().height());
      this->sizeChanged(PRIVATE(this)->storesize);
    }
    else if (obj == (QObject *)PRIVATE(this)->widget) {
      PRIVATE(this)->storesize.setValue(r->size().width(), r->size().height());
      this->sizeChanged(PRIVATE(this)->storesize);
    }
  }
  // Detect visibility changes.
  else if (obj == PRIVATE(this)->widget &&
           (e->type() == QEvent::Show || e->type() == QEvent::Hide)) {
    if (PRIVATE(this)->visibilitychangeCBs) {
      for (int i=0; i < PRIVATE(this)->visibilitychangeCBs->getLength()/2; i++) {
        SoQtComponentVisibilityCB * cb =
          (SoQtComponentVisibilityCB *)(*(PRIVATE(this)->visibilitychangeCBs))[i*2+0];
        void * userdata = (*(PRIVATE(this)->visibilitychangeCBs))[i*2+1];
        cb(userdata, e->type() == QEvent::Show ? TRUE : FALSE);
      }
    }
  }

  // It would seem more sensible that we should trigger on
  // QEvent::Create than on QEvent::Show for the afterRealizeHook()
  // method, but the QEvent::Create type is not yet used in Qt (as of
  // version 2.2.2 at least) -- it has just been reserved for future
  // releases.
  if (e->type() == QEvent::Show && !PRIVATE(this)->realized) {
    PRIVATE(this)->realized = TRUE;
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
  void)
{
#if SOQT_DEBUG
  if(!PRIVATE(this)->widget) {
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
  void)
{
#if SOQT_DEBUG
  if(!PRIVATE(this)->widget) {
    SoDebugError::postWarning("SoQtComponent::show",
                              "Called while no QWidget has been set.");
    return;
  }
#endif // SOQT_DEBUG

#if SOQTCOMP_RESIZE_DEBUG  // debug
  SoDebugError::postInfo("SoQtComponent::show-1",
                         "resizing %p: (%d, %d)",
                         PRIVATE(this)->widget,
                         PRIVATE(this)->storesize[0], PRIVATE(this)->storesize[1]);
#endif // debug

  if (PRIVATE(this)->shelled)
    PRIVATE(this)->parent->resize(PRIVATE(this)->storesize[0], PRIVATE(this)->storesize[1]);
  else
    PRIVATE(this)->widget->resize(PRIVATE(this)->storesize[0], PRIVATE(this)->storesize[1]);

#if SOQTCOMP_RESIZE_DEBUG  // debug
  SoDebugError::postInfo("SoQtComponent::show-2",
                         "resized %p: (%d, %d)",
                         PRIVATE(this)->widget,
                         PRIVATE(this)->widget->size().width(),
                         PRIVATE(this)->widget->size().height());
#endif // debug

  if (PRIVATE(this)->widget) 
    PRIVATE(this)->widget->topLevelWidget()->show();
#if SOQTCOMP_RESIZE_DEBUG  // debug
  SoDebugError::postInfo("SoQtComponent::show-3",
                         "showed %p: (%d, %d)",
                         PRIVATE(this)->widget,
                         PRIVATE(this)->widget->size().width(),
                         PRIVATE(this)->widget->size().height());
#endif // debug

  PRIVATE(this)->widget->raise();
#if SOQTCOMP_RESIZE_DEBUG  // debug
  SoDebugError::postInfo("SoQtComponent::show-4",
                         "raised %p: (%d, %d)",
                         PRIVATE(this)->widget,
                         PRIVATE(this)->widget->size().width(),
                         PRIVATE(this)->widget->size().height());
#endif // debug
  this->sizeChanged(PRIVATE(this)->storesize);
  if (SoQt::getApplication())
    SoQt::getApplication()->processEvents();
} // show()

/*!
  This will hide the widget.

  \sa show(), isVisible()
*/

void
SoQtComponent::hide(
  void)
{
#if SOQT_DEBUG
  if(!PRIVATE(this)->widget) {
    SoDebugError::postWarning("SoQtComponent::hide",
                              "Called while no QWidget has been set.");
    return;
  }
#endif // SOQT_DEBUG

  if (PRIVATE(this)->widget) 
    PRIVATE(this)->widget->topLevelWidget()->hide();
  if (SoQt::getApplication())
    SoQt::getApplication()->processEvents();
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
  void)
{
  if (! PRIVATE(this)->widget)
    return FALSE;
  return PRIVATE(this)->widget->isVisible() && PRIVATE(this)->widget->isVisibleToTLW();
} // isVisible()

/*!
  Returns a pointer to the component's window system widget.

  \sa getShellWidget(), getParentWidget()
*/

QWidget *
SoQtComponent::getWidget(
  void) const
{
  return PRIVATE(this)->widget;
} // getWidget()

/*!
  An SoQtComponent may be composed of any number of widgets in
  parent-children relationships in a tree structure with any depth.
  This method will return the root widget in that tree.

  \sa setBaseWidget()
*/

QWidget *
SoQtComponent::baseWidget(
  void) const
{
  return PRIVATE(this)->widget;
} // baseWidget()

/*!
  Returns \c TRUE if this component is a toplevel shell, i.e. it has a
  window representation on the desktop.

  \sa getShellWidget()
*/

SbBool
SoQtComponent::isTopLevelShell(
  void) const
{
#if SOQT_DEBUG && 0
  if (! PRIVATE(this)->widget) {
    SoDebugError::postWarning("SoQtComponent::isTopLevelShell",
      "Called while no QWidget has been set.");
    return FALSE;
  }
#endif // SOQT_DEBUG
  return PRIVATE(this)->embedded ? FALSE : TRUE;
} // isTopLevelShell()

/*!
  Returns the toplevel shell widget for this component. The toplevel
  shell is the desktop window which contains the component.

  \sa isTopLevelShell(), getWidget()
*/

QWidget *
SoQtComponent::getShellWidget(
  void) const
{
  return PRIVATE(this)->parent;
  if (PRIVATE(this)->widget)
    return PRIVATE(this)->widget->topLevelWidget();
  if (PRIVATE(this)->parent)
    return PRIVATE(this)->parent->topLevelWidget();
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
  void) const
{
  return PRIVATE(this)->parent;
} // getParentWidget()

/*!
  Set the window title of this component. This will not work unless
  the component is a toplevel shell.

  \sa getTitle(), setIconTitle(), isTopLevelShell()
*/

void
SoQtComponent::setTitle(
  const char * const title)
{
  PRIVATE(this)->captiontext = title;
  if (PRIVATE(this)->widget)
    this->getShellWidget()->setCaption(title);
} // setTitle()

/*!
  Returns the window title. The component should be a toplevel shell
  if you call this method.

  \sa setTitle(), isTopLevelShell()
*/

const char *
SoQtComponent::getTitle(
  void) const
{
  return
    PRIVATE(this)->captiontext.isNull() ? nullstring : (const char *) PRIVATE(this)->captiontext;
} // getTitle()

/*!
  Sets the window's title when it is iconfied. The component you use
  this method on should be a toplevel shell.

  \sa getIconTitle(), setTitle(), isTopLevelShell()
*/

void
SoQtComponent::setIconTitle(
  const char * const title)
{
  PRIVATE(this)->icontext = title;
  if (PRIVATE(this)->widget)
    this->getShellWidget()->setIconText(title);
} // setIconTitle()

/*!
  Returns the title the window has when iconfied. The component should
  be a toplevel shell if you use this method.

  \sa setIconTitle(), isTopLevelShell()
*/

const char *
SoQtComponent::getIconTitle(
  void) const
{
  return PRIVATE(this)->icontext.isNull() ? nullstring : (const char *)PRIVATE(this)->icontext;
} // getIconTitle()

/*!
  Returns name of the widget.
*/

const char *
SoQtComponent::getWidgetName(
  void) const
{
  return
    PRIVATE(this)->widgetname.isNull() ? nullstring : (const char *)PRIVATE(this)->widgetname;
} // getWidgetName()

/*!
  Returns class name of widget.
*/

const char *
SoQtComponent::getClassName(
  void) const
{
  return (const char *)PRIVATE(this)->classname;
} // getClassName()

/*!
  Returns the default name of an SoQtComponent widget. Should be
  overloaded by subclasses.
*/

const char *
SoQtComponent::getDefaultWidgetName(
  void) const
{
  return "SoQtComponent";
} // getDefaultWidgetName()

/*!
  Returns the default window caption string of this component. Should
  be overloaded by subclasses.
*/

const char *
SoQtComponent::getDefaultTitle(
  void) const
{
  return "Qt Component";
} // getDefaultTitle()

/*!
  Returns the default icon title of this component. Should be
  overloaded by subclasses.
*/

const char *
SoQtComponent::getDefaultIconTitle(
  void) const
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
  const SbVec2s size)
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
                         PRIVATE(this)->widget,
                         size[0], size[1]);
#endif // debug
  if (this->isTopLevelShell()) {
    QWidget * shell = this->getShellWidget();
    if (shell) shell->resize(size[0], size[1]);
  }
  PRIVATE(this)->storesize = size;
  this->sizeChanged(size);
} // setSize()

/*!
  Returns the component widget size.

  \sa setSize()
*/

SbVec2s
SoQtComponent::getSize(
  void) const
{
  return PRIVATE(this)->storesize;
} // getSize()

/*!
  This method is invoked to notify the component that the size has
  changed.  It is called from the top and all the way down to the
  bottom, the size being adjusted to take into account extra
  decorations having been added at each level in the component class
  hierarchy.
*/
void
SoQtComponent::sizeChanged(const SbVec2s & size)
{
  // The default implementation does nothing.
}

// *************************************************************************

/*!
  Open a dialog providing help about use of this component.

  NB: no help system has been implemented yet, so for the time being
  this will only pop up an error message.
*/

void
SoQtComponent::openHelpCard(
  const char * const name)
{
  // FIXME: code MiA. 19990222 mortene.
  QMessageBox::warning(NULL, "SoQt",
                        "The help functionality has not been "
                        "implemented.");
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
  void * const data)
{
  PRIVATE(this)->closeCB = func;
  PRIVATE(this)->closeCBdata = data;
}

/*!
  \internal

  SLOT for when the user clicks/selects window decoration close.
*/

void
SoQtComponent::widgetClosed(
  void)
{
  if (PRIVATE(this)->closeCB)
    PRIVATE(this)->closeCB(PRIVATE(this)->closeCBdata, this);
} // widgetClosed()

// *************************************************************************

/*!
  Finds and returns the SoQtComponent corresponding to the given
  QWidget, if any. If no SoQtComponent is the "owner" of the widget,
  \c NULL will be returned.
*/

SoQtComponent *
SoQtComponent::getComponent(
  QWidget * const widget)
{
  for (int i = 0; i < SoQtComponentP::soqtcomplist->getLength(); i++) {
    SoQtComponent * c = (SoQtComponent *) (*SoQtComponentP::soqtcomplist)[i];
    if (c->getWidget() == widget) return c;
  }

  return NULL;
} // getComponent()

// *************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtComponent::registerWidget(
  QWidget * widget)
{
  // nada yet
} // registerWidget()

/*!
  FIXME: write doc
*/

void
SoQtComponent::unregisterWidget(
  QWidget * widget)
{
  // nada yet
} // unregisterWidget()

// *************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtComponent::afterRealizeHook(// virtual
  void)
{
}

/*!
  Toggle full screen mode for this component, if possible.

  Returns \c FALSE if operation failed.  This might happen if the
  toolkit doesn't support attempts at making the component cover the
  complete screen or if the component is not a toplevel window.
*/
SbBool 
SoQtComponent::setFullScreen(const SbBool onoff)
{
  if (onoff == PRIVATE(this)->fullscreen) { return TRUE; }
  
  // FIXME: hmm.. this looks suspicious. Shouldn't we just return
  // FALSE if the (base)widget is not a shellwidget? 20010817 mortene.
  QWidget * w = this->getShellWidget();
  if (w == NULL) w = this->getParentWidget();
  if (w == NULL) w = this->getWidget();
  if (!w) { return FALSE; }

  // FIXME: note that the compile-time binding technique against
  // QWidget::showFullScreen() doesn't work very well with the idea
  // that we'll compile a distribution version of SoQt against the
  // lowest common denominator of Qt versions we support (ie v2.0.0),
  // as that means SoQtComponent::setFullScreen() will never work as
  // expected in the pre-compiled distro version we make.  20010608 mortene.

#if HAVE_QWIDGET_SHOWFULLSCREEN
  if (onoff) w->showFullScreen();
  else w->showNormal();
  PRIVATE(this)->fullscreen = onoff;
  return TRUE;
#else // !HAVE_QWIDGET_SHOWFULLSCREEN
  SoDebugError::postWarning("SoQtComponent::setFullScreen",
                            "SoQt was compiled against version %s of Qt, "
                            "which doesn't have the "
                            "QWidget::showFullScreen() method",
                            QT_VERSION_STR);
  return FALSE;
#endif // !HAVE_QWIDGET_SHOWFULLSCREEN
}

/*!
  Returns if this widget/component is in full screen mode.
*/
SbBool 
SoQtComponent::isFullScreen(void) const
{
  return PRIVATE(this)->fullscreen;
}

// *************************************************************************
