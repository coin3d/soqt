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

#ifndef SOQT_COMPONENT_H
#define SOQT_COMPONENT_H

#include <Inventor/SbLinear.h>
#include <Inventor/Qt/SoQtObject.h>

#ifdef __COIN_SOQT__
class QWidget;
#endif // __COIN_SOQT__
#ifdef __COIN_SOXT__
#include <X11/Intrinsic.h>
#endif // __COIN_SOXT__
#ifdef __COIN_SOGTK__
#include <gtk/gtk.h>
#endif // __COIN_SOGTK__
#ifdef __COIN_SOWIN__
#include <windows.h>
#endif // __COIN_SOWIN__


class SoQtComponent;
class SoQtCursor;

typedef void SoQtComponentCB(void * user, SoQtComponent * component);
typedef void SoQtComponentVisibilityCB(void * user, SbBool visible);

// *************************************************************************

class SOQT_DLL_API SoQtComponent : public SoQtObject {
  SOQT_OBJECT_ABSTRACT_HEADER(SoQtComponent, SoQtObject);

public:
  virtual ~SoQtComponent();

  virtual void show(void);
  virtual void hide(void);

  virtual void setComponentCursor(const SoQtCursor & cursor);
  static void setWidgetCursor(QWidget * w, const SoQtCursor & cursor);

  SbBool isFullScreen(void) const;
  SbBool setFullScreen(const SbBool onoff);

  SbBool isVisible(void);
  SbBool isTopLevelShell(void) const;

  QWidget * getWidget(void) const;
  QWidget * getBaseWidget(void) const;
  QWidget * getShellWidget(void) const;
  QWidget * getParentWidget(void) const;

  void setSize(const SbVec2s size);
  SbVec2s getSize(void) const;

  void setTitle(const char * const title);
  const char * getTitle(void) const;
  void setIconTitle(const char * const title);
  const char * getIconTitle(void) const;

  const char * getWidgetName(void) const;
  const char * getClassName(void) const;

  void setWindowCloseCallback(SoQtComponentCB * const func,
                              void * const user = NULL);
  static SoQtComponent * getComponent(QWidget * widget);

  static void initClasses(void);

protected:
  SoQtComponent(QWidget * const parent = NULL,
                   const char * const name = NULL,
                   const SbBool embed = TRUE);

  virtual void afterRealizeHook(void);

  // About the wrapping below: this variable was added after SoQt 1.0,
  // and before SoXt 1.1. To be able to release SoQt 1.1 from this
  // same branch, sizeof(SoQtComponent) needs to be the same as for
  // SoQt 1.0, which means we can't add this variable for SoQt.
#ifndef __COIN_SOQT__
  SbBool firstRealize;
#endif // __COIN_SOQT__

  void setClassName(const char * const name);
  void setBaseWidget(QWidget * widget);

  void registerWidget(QWidget * widget);
  void unregisterWidget(QWidget * widget);

  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;

  virtual void sizeChanged(const SbVec2s & size);

  void addVisibilityChangeCallback(SoQtComponentVisibilityCB * const func,
                                   void * const user = NULL);
  void removeVisibilityChangeCallback(SoQtComponentVisibilityCB * const func,
                                      void * const user = NULL);

private:
  class SoQtComponentP * pimpl;
  friend class SoGuiComponentP;
  friend class SoQtComponentP;

  // FIXME!: audit and remove as much as possible of the remaining
  // toolkit specific parts below. 20020117 mortene.

#ifdef __COIN_SOXT__
public:
  Display * getDisplay(void);
  void fitSize(const SbVec2s size);
  // FIXME: I guess these should really be part of the common
  // API. 20011012 mortene.
  void addWindowCloseCallback(SoXtComponentCB * callback, void * closure = NULL);
  void removeWindowCloseCallback(SoXtComponentCB * callback, void * closure = NULL);

protected:
  // FIXME: I guess this should perhaps be part of the common API?
  // 20011012 mortene.
  void invokeVisibilityChangeCallbacks(const SbBool enable) const;
  void invokeWindowCloseCallbacks(void) const;
  virtual void windowCloseAction(void);

private:
  // FIXME: get rid of this? 20011012 mortene.
  static void event_handler(Widget, XtPointer, XEvent *, Boolean *);
#endif // __COIN_SOXT__

#ifdef __COIN_SOGTK__
protected:
  virtual SbBool eventFilter(GtkWidget * object, GdkEvent * event);
private:
  static gint eventHandler(GtkWidget * object, GdkEvent * event, gpointer closure);
#endif // __COIN_SOGTK__
};

// *************************************************************************

#endif // ! SOQT_COMPONENT_H
