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

#ifndef SOQT_GLAREA_H
#define SOQT_GLAREA_H

#include <qgl.h>

#include <Inventor/Qt/SoQtBasic.h>


typedef void GLAreaKeyHandler(QKeyEvent * ke, void * userdata);

// *************************************************************************

class SoQtGLArea : public QGLWidget {
  typedef QGLWidget inherited;
  Q_OBJECT

public:
  SoQtGLArea(QGLFormat * const format, QWidget * const parent,
             const QGLWidget * sharewidget,
             const char * const name = "QtGLArea");
  ~SoQtGLArea();

  void registerQKeyEventHandler(GLAreaKeyHandler * cb, void * userdata)
  {
    this->keycb = cb;
    this->keycbuserdata = userdata;
  }

signals:
  void init_sig(void);
  void reshape_sig(int, int);
  void expose_sig(void);

protected:
  virtual void paintGL(void);
  virtual void resizeGL(int width, int height);
  virtual void initializeGL(void);

  virtual void focusInEvent(QFocusEvent * e);
  virtual void focusOutEvent(QFocusEvent * e);
  virtual bool event(QEvent * e);

private:
  GLAreaKeyHandler * keycb;
  void * keycbuserdata;
};

// *************************************************************************

#endif // ! SOQT_GLAREA_H
