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

#ifndef SOQT_DEVICE_H
#define SOQT_DEVICE_H

// *************************************************************************
//
// Toolkit-specific typedef and include(s). Put these before any Coin
// and/or SoQt includes, in case there are any dependency bugs in
// the underlying native toolkit set of include files versus the
// compiler environment's include files.

#include <Inventor/Qt/SoQtBasic.h> // Contains __COIN_SOQT__ define.

#ifdef __COIN_SOQT__
#include <qevent.h>
typedef void SoQtEventHandler(QWidget *, void *, QEvent *, bool *);
#endif // __COIN_SOQT__
#ifdef __COIN_SOXT__
#include <X11/Intrinsic.h>
typedef void SoQtEventHandler(QWidget *, XtPointer, XEvent *, Boolean *);
#endif // __COIN_SOXT__
#ifdef __COIN_SOGTK__
#include <gtk/gtk.h>
typedef gint SoQtEventHandler(QWidget *, QEvent *, gpointer);
#endif // __COIN_SOGTK__
#ifdef __COIN_SOWIN__
#include <windows.h>
typedef LRESULT SoQtEventHandler(QWidget *, UINT, WPARAM, LPARAM);
#endif // __COIN_SOWIN__

// *************************************************************************

#include <Inventor/SbLinear.h>
#include <Inventor/Qt/SoQtObject.h>

class SoEvent;

// *************************************************************************

class SOQT_DLL_API SoQtDevice : public SoQtObject {
  SOQT_OBJECT_ABSTRACT_HEADER(SoQtDevice, SoQtObject);

public:
  virtual ~SoQtDevice();

  virtual void enable(QWidget * w, SoQtEventHandler * handler, void * closure) = 0;
  virtual void disable(QWidget * w, SoQtEventHandler * handler, void * closure) = 0;

  virtual const SoEvent * translateEvent(QEvent * event) = 0;

  void setWindowSize(const SbVec2s size);
  SbVec2s getWindowSize(void) const;

  static void initClasses(void);

protected:
  SoQtDevice(void);

  void setEventPosition(SoEvent * event, int x, int y) const;
  static SbVec2s getLastEventPosition(void);

  void addEventHandler(QWidget *, SoQtEventHandler *, void *);
  void removeEventHandler(QWidget *, SoQtEventHandler *, void *);
  void invokeHandlers(QEvent * event);

private:
  class SoQtDeviceP * pimpl;
  friend class SoQtDeviceP;
};

// *************************************************************************

#endif // !SOQT_DEVICE_H
