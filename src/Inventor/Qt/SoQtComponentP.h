#ifndef SOQTCOMPONENTP_H
#define SOQTCOMPONENTP_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2009 by Systems in Motion.  All rights reserved.
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

#ifndef SOQT_INTERNAL
#error this is a private header file
#endif /* !SOQT_INTERNAL */

#include <qobject.h>
#include <Inventor/Qt/SoGuiComponentP.h>
#include <Inventor/Qt/SoQtCursor.h>
#include <Inventor/Qt/SoQtComponent.h> // for SoQtComponentCB typedef

// ************************************************************************

// This class contains private data and methods used within the
// SoQtComponent class.

class SoQtComponentP : public QObject, public SoGuiComponentP
{
  Q_OBJECT

public:
  SoQtComponentP(SoQtComponent * publ);
  ~SoQtComponentP();

  static class QCursor * getNativeCursor(const SoQtCursor::CustomCursor * cc);

  static void fatalerrorHandler(void * userdata);
  static void atexit_cleanup();
  void cleanupQtReferences(void);

  // Variables.

  QWidget * parent;
  QWidget * widget;
  SbBool embedded, shelled;
  char * classname, * widgetname, * icontext, * captiontext;
  SoQtComponentCB * closeCB;
  void * closeCBdata;
  SbPList * visibilitychangeCBs;
  SbBool realized;
  SbVec2s storesize;
#ifdef Q_WS_MAC
  // Workaround: Qt/Mac does not remember windowsize when going fullscreen
  SbVec2s windowsize;
#endif
  SbBool fullscreen;

  virtual bool eventFilter(QObject * obj, QEvent * e);

public slots:
  void widgetClosed(void);

private:
  static SbDict * cursordict;
};

// ************************************************************************

#endif // !SOQTCOMPONENTP_H
