#ifndef SOQTCOLORTABLEDITOR_H
#define SOQTCOLORTABLEDITOR_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2003 by Systems in Motion.  All rights reserved.
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
 *  See <URL:http://www.coin3d.org> for more information.
 *
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no>.
 *
\**************************************************************************/

#include <qwidget.h>
#include <Inventor/Qt/SoQtBasic.h>
#include <Inventor/SbBasic.h>


#ifndef SOQT_BETA_VERSION
#error This class should not be part of the public API. Move it to somewhere else, like e.g. a new repository with our Qt extension classes.
#endif // SOQT_BETA_VERSION

class SOQT_DLL_API SoQtColorTableEditor : public QWidget {

public:
  SoQtColorTableEditor(int numcolors = 256, 
                       QWidget * parent = 0, 
                       const char * name = 0);
  
  ~SoQtColorTableEditor();

  enum Mode {
    LUMINANCE = 1,
    LUMINANCE_ALPHA,
    RGB,
    RGBA
  };

  void setMode(Mode mode);
  Mode getMode(void) const;

  void setColors(uint8_t * color, int num);
  void getColors(uint8_t * color, int num) const;

  typedef void ChangeCB(SoQtColorTableEditor * editor, void * userdata);
  void setChangeCallback(SoQtColorTableEditor::ChangeCB * cb, void * userdata);

private:
  class SoQtColorTableEditorP * pimpl;
};

#endif // ! SOQTCOLORTABLEDITOR_H
