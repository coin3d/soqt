/**************************************************************************\
 * 
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

// FIXME: not in use yet. 19990620 mortene.

#include <Inventor/Qt/SoQtMaterialList.h>

#include <qlistbox.h>
#include <qdir.h>
#include <qpopmenu.h>
#include <qmenubar.h>
#include <qlayout.h>

#include <Inventor/SoInput.h>
#include <Inventor/SoPath.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoGroup.h>

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
