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
