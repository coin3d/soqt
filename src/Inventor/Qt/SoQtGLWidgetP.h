#ifndef SOQTGLWIDGETP_H
#define SOQTGLWIDGETP_H

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

// *************************************************************************

#include <qobject.h>

#include <Inventor/Qt/SoGuiGLWidgetP.h>
#include <Inventor/SbLinear.h>

class QKeyEvent;

// ************************************************************************

// This class contains private data and methods used within the
// SoQtGLWidget class.

class SoQtGLWidgetP : public QObject, public SoGuiGLWidgetP
{
  Q_OBJECT

public:
  SoQtGLWidgetP(SoQtGLWidget * publ);
  ~SoQtGLWidgetP();

  static void GLAreaKeyEvent(QKeyEvent * e, void * userdata);
  void buildGLWidget(void);
  virtual bool eventFilter(QObject * obj, QEvent * e);
  static void eventHandler(QWidget *, void *, QEvent *, bool *);

  const class QGLContext * getNormalContext(void);
  const class QGLContext * getOverlayContext(void);

  SbVec2s glSize;
#if QT_VERSION >= 0x050000
  SbVec2s glSizeUnscaled;
#endif
  SbBool wasresized;
  const QGLContext * oldcontext;

  class SoQtGLArea * currentglwidget;
  class SoQtGLArea * previousglwidget;
  QWidget * glparent;
  class QFrame * borderwidget;
  int borderthickness;
  class QGLFormat * glformat;

public slots:
#if QT_VERSION >= 0x050000
  void gl_changed(void);
#endif
  void gl_init(void);
  void gl_reshape(int, int);
  void gl_exposed(void);

protected:
  virtual SbBool isDirectRendering(void);
};

// ************************************************************************

#endif // !SOQTGLWIDGETP_H
