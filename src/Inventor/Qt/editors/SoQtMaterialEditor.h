/**************************************************************************\
 *
 *  This file is part of the Coin family of 3D visualization libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and / or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.  See the
 *  file LICENSE.GPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you desire to use this library in software that is incompatible
 *  with the GNU GPL, and / or you would like to take advantage of the
 *  additional benefits with regard to our support services, please
 *  contact Systems in Motion about acquiring a Coin Professional
 *  Edition License.  See <URL:http://www.coin3d.org> for more
 *  information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#ifndef SOQTMATERIALEDITOR_H
#define SOQTMATERIALEDITOR_H

#include <Inventor/Qt/SoQtComponent.h>

class SoMaterial;

typedef void SoQtMaterialEditorCB(void * userdata, const SoMaterial * node);

class SoQtMaterialEditor : public SoQtComponent {
public:
  enum UpdateFrequency { CONTINUOUS, AFTER_ACCEPT };

  SoQtMaterialEditor(QWidget * parent = NULL,
                     const char * name = NULL,
                     SbBool embedinparent = TRUE);
  ~SoQtMaterialEditor();

  void attach(SoMaterial * node, int index = 0);
  void detach(void);
  SbBool isAttached(void);

  void addMaterialChangedCallback(SoQtMaterialEditorCB * f, void * userdata = NULL);
  void removeMaterialChangedCallback(SoQtMaterialEditorCB * f, void * userdata = NULL);

  void setUpdateFrequency(SoQtMaterialEditor::UpdateFrequency freq);
  SoQtMaterialEditor::UpdateFrequency getUpdateFrequency(void);

  void setMaterial(const SoMaterial & node);
  const SoMaterial & getMaterial(void) const;

protected:
  SoQtMaterialEditor(QWidget * parent,
                     const char * name,
                     SbBool embedinparent,
                     SbBool buildnow);

  QWidget * buildWidget(QWidget * parent);

  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;

private:
  class SoQtMaterialEditorP * pimpl;
  friend class SoQtMaterialEditorP;
};

#endif // SOQTMATERIALEDITOR_H
