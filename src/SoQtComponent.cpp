/**************************************************************************\
 * 
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 73540378 Fax: +47 73943861
 *
\**************************************************************************/

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

#include <Inventor/Qt/SoQtComponent.h>

#if SOQT_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // SOQT_DEBUG

#include <qwidget.h>
#include <assert.h>

// FIXME: get rid of this before 1.0 release (convert everything to Qt
// version 2.x API). 19990630 mortene.
#if QT_VERSION >= 200
#include <q1xcompatibility.h>
#endif // Qt v2.x


// debug
#define SOQTCOMP_RESIZE_DEBUG 0


static const char nullstring[] = "(null)";

// *************************************************************************
// Documentation

/*!
  \fn virtual const char * SoQtComponent::componentClassName(void) const

  Returns class name of the component.
 */

/*!
  \fn virtual void SoQtComponent::sizeChanged(const SbVec2s & newSize)

  Overload to detect when the base widget in the component changes its
  dimensions (an operation which is usually triggered by the user).
 */

/*!
  \var QWidget * SoQtComponent::widget

  Pointer to the Qt widget. This member must be set from all component
  classes which inherits SoQtComponent directly.
*/


// *************************************************************************

// Static lists which'll keep track of all SoQtComponent <-> QWidget
// connections.
// FIXME: replace with SbDict? Or a Qt dictionary? 990202 mortene.
SbPList SoQtComponent::soqtcomplist;
SbPList SoQtComponent::qtwidgetlist;

// *************************************************************************

/*!
  Constructor.

  \a parent is the widget we'll build this component inside. If \a parent is
  \a NULL, make a new toplevel window.

  \a name is mostly interesting for debugging purposes.

  \a buildInsideParent specifies whether or not we should make a new
  toplevel window for the component even when we've got a non-NULL
  \a parent.
*/
SoQtComponent::SoQtComponent(QWidget * const parent,
			     const char * const name,
			     const SbBool buildInsideParent)
{
  this->widget = NULL;
  this->parent = parent;
  this->closeCB = NULL;
  this->closeCBdata = NULL;
  this->visibilitychangeCBs = NULL;

  if (name) this->widgetname = name;
  this->classname = "SoQtComponent";

  this->storesize.setValue(-1, -1);

  this->buildinside = buildInsideParent;
}

/*!
  Destructor.
 */
SoQtComponent::~SoQtComponent()
{
  // Link us out of the static QWidget<->SoQtComponent "correlation"
  // lists.
  int idx = SoQtComponent::qtwidgetlist.find(this->widget);
  assert(idx != -1);
  SoQtComponent::qtwidgetlist.remove(idx);
  SoQtComponent::soqtcomplist.remove(idx);
  
  delete this->visibilitychangeCBs;

  // If we've got a toplevel widget on our hands it won't
  // automatically be deallocated (there's no real parent widget).
  if (this->widget && !this->widget->parentWidget()) delete this->widget;
}

/*!
  Add a callback which will be called whenever the widget component
  changes visibility status (because of iconification or
  deiconification, for instance).

  \sa removeVisibilityChangeCallback(), isVisible()
 */
void
SoQtComponent::addVisibilityChangeCallback(SoQtComponentVisibilityCB * func,
					   void * userData)
{
  if (!this->visibilitychangeCBs) this->visibilitychangeCBs = new SbPList;
  this->visibilitychangeCBs->append((void *)func);
  this->visibilitychangeCBs->append(userData);
}

/*!
  Remove one of the callbacks from the list of visibility notification
  callbacks.

  \sa addVisibilityChangeCallback(), isVisible()
 */
void
SoQtComponent::removeVisibilityChangeCallback(SoQtComponentVisibilityCB * func,
					      void * userData)
{
#if SOQT_DEBUG
  if (!this->visibilitychangeCBs) {
    SoDebugError::postWarning("SoQtComponent::removeVisibilityChangeCallback",
			      "empty callback list");
    return;
  }
#endif // SOQT_DEBUG

  int idx = this->visibilitychangeCBs->find((void *)func);
  if (idx != -1 ) {
    this->visibilitychangeCBs->remove(idx);
    this->visibilitychangeCBs->remove(idx);
  }

#if SOQT_DEBUG
  if (idx == -1) {
    SoDebugError::postWarning("SoQtComponent::removeVisibilityChangeCallback",
			      "tried to remove non-existant callback");
    return;
  }
#endif // SOQT_DEBUG
}

/*!
  Set class name of widget.

  \sa getClassName(), componentClassName()
 */
void
SoQtComponent::setClassName(const char * const name)
{
  this->classname = name;
}

/*!
  Set the core widget for this SoQt component. It is important that
  subclasses get this correct, as the widget set here will be the widget
  returned from query methods.

  \sa baseWidget()
 */
void
SoQtComponent::setBaseWidget(QWidget * w)
{
  assert(w);

  if (this->parent) this->parent->removeEventFilter(this);
  if (this->widget) this->widget->removeEventFilter(this);

  this->widget = w;
  this->parent = w->parentWidget();

#if 0 // debug
  SoDebugError::postInfo("SoQtComponent::setBaseWidget",
			 "widget: %p, parent: %p", w, this->parent);
#endif // debug


#if 0 // debug
  if (!this->captiontext.isNull()) {
    SoDebugError::postInfo("SoQtComponent::setBaseWidget",
			   "setCaption('%s')",
			   (const char *)this->captiontext);
  }
#endif // debug
  if (this->captiontext.isNull()) this->captiontext = this->getDefaultTitle();
  this->getShellWidget()->setCaption(this->captiontext);

  if (this->icontext.isNull()) this->icontext = this->getDefaultIconTitle();
  this->getShellWidget()->setIconText(this->icontext);

  if (this->widgetname.isNull())
    this->widgetname = this->getDefaultWidgetName();
  this->widget->setName(this->widgetname);

  // Need this to auto-detect resize events.
  if (this->parent) this->parent->installEventFilter(this);
  this->widget->installEventFilter(this);
#if 0 // debug
  SoDebugError::postInfo("SoQtComponent::setBaseWidget",
			 "installeventfilter, widget: %p", this->widget);
#endif // debug
}

/*!
  \internal 

  Helps us detect changes in size (base widget and parent widget)
  and visibility status.
 */
bool
SoQtComponent::eventFilter(QObject *obj, QEvent * e)
{
#if 0 // debug
  SoDebugError::postInfo("SoQtComponent::eventFilter", "obj: %p", obj);
#endif // debug

  // Remove event filter if unknown Qt widget.
  // FIXME: this code should probably be superfluous if everything
  // else works 100%? 990216 mortene.
  if ((obj != this->widget) && (obj != this->parent)) {
#if SOQT_DEBUG
    SoDebugError::postWarning("SoQtComponent::eventFilter",
			      "had to do a removeEventFilter()");
#endif // SOQT_DEBUG
    obj->removeEventFilter(this);
    return FALSE;
  }

  // Detect resize events.
  if (e->type() == Event_Resize) {
    QResizeEvent * r = (QResizeEvent *)e;

    if (obj == (QObject *)this->parent) {
#if SOQTCOMP_RESIZE_DEBUG  // debug
      SoDebugError::postInfo("SoQtComponent::eventFilter",
			     "resize %p: (%d, %d)",
			     this->widget,
			     r->size().width(), r->size().height());
#endif // debug			 
      this->widget->resize(r->size());
    }
    else if (obj == (QObject *)this->widget) {
      this->storesize.setValue(r->size().width(), r->size().height());
      this->sizeChanged(this->storesize);
    }
    else
      assert(0);

  }
  // Detect visibility changes.
  else if (e->type() == Event_Show || e->type() == Event_Hide) {
    if (this->visibilitychangeCBs) {
      for (int i=0; i < this->visibilitychangeCBs->getLength()/2; i++) {
	SoQtComponentVisibilityCB * cb =
	  (SoQtComponentVisibilityCB *)(*(this->visibilitychangeCBs))[i*2+0];
	void * userdata = (*(this->visibilitychangeCBs))[i*2+1];
	cb(userdata, e->type() == Event_Show ? TRUE : FALSE);
      }
    }
  }

  return FALSE;
}

/*!
  This function \e must be called by subclasses after the component's
  widget has been otherwise initialized.
*/
void 
SoQtComponent::subclassInitialized(void)
{
#if SOQT_DEBUG
  if(!this->widget) {
    SoDebugError::postWarning("SoQtComponent::subclassInitialized",
			      "Called while no QWidget has been set.");
    return;
  }
#endif // SOQT_DEBUG

  QObject::connect(this->widget, SIGNAL(destroyed()),
		   this, SLOT(widgetClosed()));
}

/*!
  This will show the widget, deiconifiying and raising it if
  necessary.

  \sa hide(), isVisible()
 */
void 
SoQtComponent::show(void)
{
#if SOQT_DEBUG
  if(!this->widget) {
    SoDebugError::postWarning("SoQtComponent::show",
			      "Called while no QWidget has been set.");
    return;
  }
#endif // SOQT_DEBUG

#if SOQTCOMP_RESIZE_DEBUG  // debug
  SoDebugError::postInfo("SoQtComponent::show-1",
			 "resizing %p: (%d, %d)",
			 this->widget,
			 this->storesize[0], this->storesize[1]);
#endif // debug
			 
  this->widget->resize(this->storesize[0], this->storesize[1]);

#if SOQTCOMP_RESIZE_DEBUG  // debug
  SoDebugError::postInfo("SoQtComponent::show-2",
			 "resized %p: (%d, %d)",
			 this->widget,
			 this->widget->size().width(),
			 this->widget->size().height());
#endif // debug			 

  this->widget->show();
#if SOQTCOMP_RESIZE_DEBUG  // debug
  SoDebugError::postInfo("SoQtComponent::show-3",
			 "showed %p: (%d, %d)",
			 this->widget,
			 this->widget->size().width(),
			 this->widget->size().height());
#endif // debug

  this->widget->raise();
#if SOQTCOMP_RESIZE_DEBUG  // debug
  SoDebugError::postInfo("SoQtComponent::show-4",
			 "raised %p: (%d, %d)",
			 this->widget,
			 this->widget->size().width(),
			 this->widget->size().height());
#endif // debug
}

/*!
  This will hide the widget.

  \sa show(), isVisible()
 */
void 
SoQtComponent::hide(void)
{
#if SOQT_DEBUG
  if(!this->widget) {
    SoDebugError::postWarning("SoQtComponent::hide",
			      "Called while no QWidget has been set.");
    return;
  }
#endif // SOQT_DEBUG

  this->widget->hide();
}

/*!
  Returns visibility status on the widget. If any parents of this widget
  or this widget itself is hidden, returns \a FALSE.
  
  Note that a widget which is just obscured by other windows on the
  desktop is not hidden in this sense, and \a TRUE will be returned.

  \sa show(), hide()
 */
SbBool 
SoQtComponent::isVisible(void)
{
  if (!this->widget) return FALSE;

  return this->widget->isVisible() && this->widget->isVisibleToTLW();
}

/*!
  Returns a pointer to the component's window system widget.

  \sa getShellWidget(), getParentWidget()
 */
QWidget *
SoQtComponent::getWidget(void) const
{
  return this->widget;
}

/*!
  An SoQtComponent may be composed of any number of widgets in
  parent-children relationships in a tree structure with any depth.
  This method will return the root widget in that tree.

  \sa setBaseWidget()
 */
QWidget *
SoQtComponent::baseWidget(void) const
{
  return this->widget;
}

/*!
  Returns \a TRUE if this component is a toplevel shell, i.e. it has a
  window representation on the desktop.

  \sa getShellWidget()
 */
SbBool 
SoQtComponent::isTopLevelShell(void) const
{
#if SOQT_DEBUG
  if(!this->widget) {
    SoDebugError::postWarning("SoQtComponent::isTopLevelShell",
			      "Called while no QWidget has been set.");
    return FALSE;
  }
#endif // SOQT_DEBUG

  return this->widget->isTopLevel();
}

/*!
  Returns the toplevel shell widget for this component. The toplevel shell
  is the desktop window which contains the component.

  \sa isTopLevelShell(), getWidget()
 */
QWidget *
SoQtComponent::getShellWidget(void) const
{
#if SOQT_DEBUG
  if (!this->widget) {
    SoDebugError::postWarning("SoQtComponent::getShellWidget",
			      "Called while no QWidget has been set.");
    return NULL;
  }
#endif // SOQT_DEBUG

  return this->widget->topLevelWidget();
}

/*!
  Returns the widget which is the parent (i.e. contains) this component's
  base widget.

  \sa getWidget(), baseWidget(), isTopLevelShell()
 */
QWidget *
SoQtComponent::getParentWidget(void) const
{
  return this->parent;
}

/*!
  Set the window title of this component. This will not work unless the
  component is a toplevel shell.

  \sa getTitle(), setIconTitle(), isTopLevelShell()
 */
void 
SoQtComponent::setTitle(const char * const newTitle)
{
#if 0 // debug
  SoDebugError::postInfo("SoQtComponent::setTitle", "'%s'", newTitle);
#endif // debug

  this->captiontext = newTitle;
  if (this->widget) {
#if 0 // debug
    SoDebugError::postInfo("SoQtComponent::setTitle",
			   "actually setCaption('%s')", newTitle);
#endif // debug
    this->getShellWidget()->setCaption(newTitle);
  }
}

/*!
  Returns the window title. The component should be a toplevel shell if
  you call this method.

  \sa setTitle(), isTopLevelShell()
 */
const char *
SoQtComponent::getTitle(void) const
{
  return
    this->captiontext.isNull() ? nullstring : (const char *)this->captiontext;
}

/*!
  Sets the window's title when it is iconfied. The component you use this
  method on should be a toplevel shell.

  \sa getIconTitle(), setTitle(), isTopLevelShell()
 */
void
SoQtComponent::setIconTitle(const char * const newIconTitle)
{
  this->icontext = newIconTitle;
  if (this->widget) this->getShellWidget()->setIconText(newIconTitle);
}

/*!
  Returns the title the window has when iconfied. The component should be
  a toplevel shell if you use this method.

  \sa setIconTitle(), isTopLevelShell()
 */
const char *
SoQtComponent::getIconTitle(void) const
{
  return this->icontext.isNull() ? nullstring : (const char *)this->icontext;
}

/*!
  Returns name of the widget.
 */
const char *
SoQtComponent::getWidgetName(void) const
{
  return
    this->widgetname.isNull() ? nullstring : (const char *)this->widgetname;
}

/*!
  Returns class name of widget.
 */
const char *
SoQtComponent::getClassName(void) const
{
  return (const char *)this->classname;
}

/*!
  Returns the default name of an SoQtComponent widget. Should be overloaded
  by subclasses.
 */
const char *
SoQtComponent::getDefaultWidgetName(void) const
{
  return "SoQtComponent";
}

/*!
  Returns the default window caption string of this component. Should be
  overloaded by subclasses.
 */
const char *
SoQtComponent::getDefaultTitle(void) const
{
  return "Qt Component";
}

/*!
  Returns the default icon title of this component. Should be overloaded
  by subclasses.
 */
const char *
SoQtComponent::getDefaultIconTitle(void) const
{
  return "Qt Comp";
}


/*!
  Resize the component widget.

  \sa getSize()
 */
void 
SoQtComponent::setSize(const SbVec2s & size)
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
			 this->widget,
			 size[0], size[1]);
#endif // debug
			 
  this->storesize = size;
  if (this->widget) {
    QSize newsize(size[0], size[1]);
    if (this->widget->size() != newsize) {
      this->widget->resize(newsize);
      this->sizeChanged(size);
    }
  }
}

/*!
  Returns the component widget size.

  \sa setSize()
 */
SbVec2s 
SoQtComponent::getSize(void)
{
  return this->storesize;
}

/*!
  Open a dialog providing help about use of this component.

  NB: no help system has been implemented yet, so for the time being this
  will only pop up an error message.
 */
#include <qmessagebox.h>
void
SoQtComponent::openHelpCard(const char * name)
{
  // FIXME: code MiA. 990222 mortene.
  QMessageBox::warning(NULL, "SoQt",
		       "The help functionality has not been "
		       "implemented.");
}

/*!
  Set up a callback function to use when the component gets closed. A
  component must be a toplevel shell for this to have any effect.

  For toplevel shells with no close callback set, the window will
  simply be hidden. The typical action to take in the callback would
  be to delete the component.

  \sa isTopLevelShell()
 */
void 
SoQtComponent::setWindowCloseCallback(SoQtComponentCB *func,
				      void * const data)
{
  this->closeCB = func;
  this->closeCBdata = data;
}

/*!
  \internal

  SLOT for when the user clicks/selects window decoration close.
*/
void 
SoQtComponent::widgetClosed(void)
{
  if (this->closeCB) this->closeCB(this->closeCBdata, this);
}

/* static functions ***************************************************/

/*!
  Finds and returns the \a SoQtComponent corresponding to the given
  \a QWidget, if any. If no SoQtComponent is the "owner" of the widget,
  \a NULL will be returned.
 */
SoQtComponent *
SoQtComponent::getComponent(QWidget * const w)
{
  int idx = SoQtComponent::qtwidgetlist.find(w);
  if(idx != -1) return (SoQtComponent *)SoQtComponent::soqtcomplist[idx];
  else return NULL;
}
