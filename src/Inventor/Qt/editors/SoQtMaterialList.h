/**************************************************************************\
 *
 *  This file is part of the Coin GUI toolkit libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation.  See the
 *  file LICENSE.LGPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you want to use this library with software that is incompatible
 *  licensewise with the LGPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
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
