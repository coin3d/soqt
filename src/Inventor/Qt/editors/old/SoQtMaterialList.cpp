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

// FIXME: not in use yet. 19990620 mortene.

#include <qlistbox.h>
#include <qdir.h>
#include <qpopmenu.h>
#include <qmenubar.h>
#include <qlayout.h>

#include <Inventor/SoInput.h>
#include <Inventor/SoPath.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoGroup.h>

#include <Inventor/Qt/SoQtMaterialList.h>

// FIXME: move this to config.h or something?
#define DEFAULT_MATERIAL_DIR "/usr/share/data/materials"

SoQtMaterialList::SoQtMaterialList(QWidget * parent, const char * name,
        SbBool buildInsideParent, const char * dir) : SoQtComponent(parent)
{
  printf("0\n");
  materialDir = NULL;
  curPalettePath = NULL;
  if (dir != NULL) {
    materialDir = new char[strlen(dir)+1];
    strcpy(materialDir, dir);
  }
  else {
    materialDir = new char[strlen(DEFAULT_MATERIAL_DIR)+1];
    strcpy(materialDir, DEFAULT_MATERIAL_DIR);
  }
  printf("1\n");

  widget = new QWidget(buildInsideParent ? parent : NULL, name);
  widget->setCaption("Material List");
  printf("2\n");

  QVBoxLayout * layout = new QVBoxLayout(widget);

  menu = new QPopupMenu;
  menu->setCheckable(true);
  printf("3\n");
  dir2List(materialDir);
  printf("4\n");

  QMenuBar * bar = new QMenuBar(widget);
  bar->insertItem("&Palettes", menu);
  layout->setMenuBar(bar);
  printf("5\n");

  mtlList = new QListBox(widget);
  mtlList->setFixedVisibleLines(10);
  layout->addWidget(mtlList);
  printf("6\n");


  QObject::connect(mtlList, SIGNAL(highlighted(const char *)), this, SLOT(setMaterial(const char *)));

  setPalette(menu->idAt(0));
}

SoQtMaterialList::~SoQtMaterialList()
{
  delete [] materialDir;
  delete [] curPalettePath;
}

void SoQtMaterialList::dir2List(const char * dir)
{
  mtlPalettes = new QDir(dir, NULL, QDir::Unsorted, QDir::Dirs);
  SoInput in;
  if (!mtlPalettes->exists()) {
    warning("Cannot find directory %s", dir);
    return;
  }
  for (int i = 0; i < mtlPalettes->count(); i++) {
    if ((* mtlPalettes)[i][0] != '.') {
            menu->insertItem((*mtlPalettes)[i], 100 + i);
    }
  }
  connect(menu, SIGNAL(activated(int)), this, SLOT(setPalette(int)));
  delete mtlPalettes;
}

void SoQtMaterialList::setPalette()
{
  const char * item = NULL;
  for (int i = 0; i < menu->count() && item == NULL; i++) {
    if (menu->isItemChecked(i)) item = menu->text(i);
  }
  if (item) setPalette(item);
}

void SoQtMaterialList::setPalette(int id)
{
  const char * item = menu->text(id);
  for (int i = 0; i < menu->count(); i++) {
    if (menu->isItemChecked(menu->idAt(i))) menu->setItemChecked(menu->idAt(i), false);
  }
  menu->setItemChecked(id, true);
  setPalette(item);
}

void SoQtMaterialList::setPalette(const char * dir)
{
  printf("setPalette(%s)\n", dir);
  delete [] curPalettePath;
  curPalettePath = new char[strlen(dir) + strlen(materialDir) + 2];
  strcpy(curPalettePath, materialDir);
  strcat(curPalettePath, "/");
  strcat(curPalettePath, dir);
  QDir d(curPalettePath, NULL, QDir::Unsorted, QDir::Files);
  if (!d.exists()) {
    warning("Cannot find directory %s", curPalettePath);
    goto out;
  }
  mtlList->clear();
  for (int i = 0; i < d.count(); i++) {
    mtlList->insertItem(d[i]);
  }
  mtlList->show();
out:
  return;
}

void SoQtMaterialList::setMaterial(const char * file)
{
  SoInput in;
  char * fullPath = new char[strlen(curPalettePath) + strlen(file) + 2];
  strcpy(fullPath, curPalettePath);
  strcat(fullPath, "/");
  strcat(fullPath, file);
  if (in.openFile(fullPath) == FALSE) {
    warning("Unable to open file %s", fullPath);
    return;
  }
  SoNode * node;
  if (SoDB::read(&in, node) == FALSE) {
    printf("SoDB::read returned false, file = %s\n", file);
  }
  printf("node = %s\n", node->getTypeId().getName().getString());
  if (node->getTypeId() != SoMaterial::getClassTypeId()) {
    warning("Unexpected content in material file %s!\n", fullPath);
    return;
  }
  material = (SoMaterial *) node;
  emit materialSelected(material);
}

const char * SoQtMaterialList::componentClassName() const
{
  return "SoQtMaterialList";
}


const char * SoQtMaterialList::getDefaultWidgetName() const
{
  printf("FIXME: not implemented\n");
  return "SoQtMaterialList";
}

const char * SoQtMaterialList::getDefaultTitle() const
{
  printf("FIXME: not implemented\n");
  return NULL;
}

const char * SoQtMaterialList::getDefaultIconTitle() const
{
  printf("FIXME: not implemented\n");
  return NULL;
}
