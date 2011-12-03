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
