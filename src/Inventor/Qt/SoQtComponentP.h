#ifndef SOQTCOMPONENTP_H
#define SOQTCOMPONENTP_H

/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
  QString classname, widgetname;
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
