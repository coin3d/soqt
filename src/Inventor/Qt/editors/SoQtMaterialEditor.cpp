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

#include <SoQtMaterialEditor.h>

SoQtMaterialEditor::SoQtMaterialEditor(QWidget * parent,
                                       const char * name,
                                       SbBool embedinparent)
{
}

SoQtMaterialEditor::SoQtMaterialEditor(QWidget * parent,
                                       const char * name,
                                       SbBool embedinparent,
                                       SbBool buildnow)
{
}

SoQtMaterialEditor::~SoQtMaterialEditor()
{
}

void
SoQtMaterialEditor::attach(SoMaterial * node, int index)
{
}

void
SoQtMaterialEditor::detach(void)
{
}

SbBool
SoQtMaterialEditor::isAttached(void)
{
}


void
SoQtMaterialEditor::addMaterialChangedCallback(SoQtMaterialEditorCB * f, void * userdata = NULL)
{
}

void
SoQtMaterialEditor::removeMaterialChangedCallback(SoQtMaterialEditorCB * f, void * userdata = NULL)
{
}


void
SoQtMaterialEditor::setUpdateFrequency(SoQtMaterialEditor::UpdateFrequency freq)
{
}

SoQtMaterialEditor::UpdateFrequency
SoQtMaterialEditor::getUpdateFrequency(void)
{
}

void
SoQtMaterialEditor::setMaterial(const SoMaterial & node)
{
}

const SoMaterial &
SoQtMaterialEditor::getMaterial(void) const
{
}


QWidget *
SoQtMaterialEditor::buildWidget(QWidget * parent)
{
}


const char *
SoQtMaterialEditor::getDefaultWidgetName(void) const
{
}

const char *
SoQtMaterialEditor::getDefaultTitle(void) const
{
}

const char *
SoQtMaterialEditor::getDefaultIconTitle(void) const
{
}
