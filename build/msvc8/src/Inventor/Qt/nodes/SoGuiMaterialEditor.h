#ifndef COIN_SOGUIMATERIALEDITOR_H
#define COIN_SOGUIMATERIALEDITOR_H

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

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/nodekits/SoBaseKit.h>

class SoMaterial;
class SoGuiColorEditor;

typedef SoGuiColorEditor * SoGuiColorEditorOpenCB(void * closure);
typedef void SoGuiColorEditorCloseCB(void * closure, SoGuiColorEditor * editor);

class SoGuiMaterialEditor : public SoBaseKit {
  typedef SoBaseKit inherited;
  SO_KIT_HEADER(SoGuiMaterialEditor);
  SO_KIT_CATALOG_ENTRY_HEADER(root);

public:
  static void initClass(void);
  SoGuiMaterialEditor(void);
  
  enum UpdateFrequency {
    CONTINUOUS,
    AFTER_ACCEPT
  };

  SoSFNode material;
  SoSFShort index;
  SoSFEnum update;

  void setColorEditorCallbacks(SoGuiColorEditorOpenCB * open, SoGuiColorEditorCloseCB * close, void * closure);
  SoMaterial * getSphereMaterialNode(void) const;

protected:
  ~SoGuiMaterialEditor(void);

private:
  void * internals;

};

#endif // !COIN_SOGUIMATERIALEDITOR_H
