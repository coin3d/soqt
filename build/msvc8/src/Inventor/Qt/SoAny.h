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

// src/Inventor/Qt/SoAny.h.  Generated from SoAny.h.in by configure.

#ifndef SOANY_H
#define SOANY_H

// This file contains definitions which should _only_ be used during
// library build. It is not installed for use by the application
// programmer.
#ifndef SOQT_INTERNAL
#error Only for internal use during library build.
#endif /* !SOQT_INTERNAL */

// ************************************************************************

#include <Inventor/SbPList.h>

#include <Inventor/Qt/SoQt.h>

class SoNode;
class SoSearchAction;

// ************************************************************************

class SoAny {
public:
  static void init();

  // use the singleton design pattern for access
  static SoAny * si(void);

  static const char * getenv(const char * e);

  void * getSharedGLContext(void * display, void * screen);
  void registerGLContext(void * context, void * display, void * screen);
  void unregisterGLContext(void * context);
  int getSharedCacheContextId(void * context);

  static void listWin32ProcessModules(void);

  SoQt::FatalErrorCB * setFatalErrorHandler(SoQt::FatalErrorCB * cb, void * userdata);
  SbBool invokeFatalErrorHandler(SbString errmsg, SoQt::FatalErrors errcode);
  typedef void InternalFatalErrorCB(void * userdata);
  void addInternalFatalErrorHandler(SoAny::InternalFatalErrorCB * cb,
                                    void * ud);

  static char * strconcat(const char ** stringlist, const char * glue = NULL, SbBool glueend = TRUE);
  static SoNode * loadSceneGraph(const char ** stringlist);
  static SoNode * loadSceneGraph(char * buffer, unsigned int bufsize = 0);
  static SoNode * scanSceneForName(SoNode * scene, const char * name, SbBool searchAll = FALSE);

  // FIXME: Dummy sogui_atexit(). Replace with real
  // implementation. kintel 20060209
  typedef void atexit_f(void);
  static void atexit(atexit_f * fp, int priority);

private:
  SoAny(void);
  ~SoAny();
  static void cleanup_si(void);

  // (use SbPList instances to be able to compile properly on SGI /
  // TGS Inventor aswell as Coin)
  SbPList cclist;
  SbPList internalfehandlers, internalfedata;

  SoQt::FatalErrorCB * fatalcb;
  void * userdata;

  static SoSearchAction * finder;
}; // class SoAny

// ************************************************************************

#endif // ! SOANY_H
