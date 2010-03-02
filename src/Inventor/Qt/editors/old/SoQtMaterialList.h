/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) by Kongsberg Oil & Gas Technologies.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg Oil & Gas Technologies
 *  about acquiring a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg Oil & Gas Technologies, Bygdoy Alle 5, 0257 Oslo, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

#ifndef SOQT_MATERIALLIST_H
#define SOQT_MATERIALLIST_H

#include <Inventor/Qt/SoQtComponent.h>

  class SoMaterial;
  class QDir;
  class QListBox;
  class QPopupMenu;

typedef void SoQtMaterialListCB(void *userData, const SoMaterial *mtl);

class SOQT_DLL_API SoQtMaterialList : public SoQtComponent
{
  Q_OBJECT

public:
  SoQtMaterialList(QWidget *parent = NULL,
                   const char *name = NULL,
                   SbBool buildInsideParent = TRUE,
                   const char *dir = NULL);
  ~SoQtMaterialList();

#if 0
  void addCallback(SoQtMaterialListCB *f,
                   void *userData = NULL);
  void removeCallback(SoQtMaterialListCB *f,
                      void *userData = NULL);
#endif
public slots:
  void setPalette(void);
  void setPalette(int);
  void setPalette(const char *);
  void setMaterial(const char *);
signals:
  void materialSelected(SoMaterial *);
  void closed(void);

protected:
  SoQtMaterialList(QWidget *parent, const char *name,
                   SbBool buildInsideParent,
                   const char *dir, SbBool buildNow);
  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;
  virtual const char * componentClassName(void) const;

  QWidget* buildPulldownMenu(QWidget *parent);

private:
  QPopupMenu* menu;
  char* materialDir;
  char* curPalettePath;
  QListBox* mtlList;

  QDir* mtlPalettes;
  QDir* mtlDirectory;
  SoMaterial* material;

  void dir2List(const char *dir);
};

#endif // ! SOQT_MATERIALLIST_H
