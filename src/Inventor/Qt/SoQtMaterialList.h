/**************************************************************************
 *
 *  This file is part of the Coin SoQt GUI binding library.
 *  Copyright (C) 2000 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License version
 *  2.1 as published by the Free Software Foundation.  See the file
 *  LICENSE.LGPL at the root directory of the distribution for all the
 *  details.
 *
 *  If you want to use Coin SoQt for applications not compatible with the
 *  LGPL, please contact SIM to acquire a Professional Edition License.
 *
 *  Systems in Motion, Prof Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
 **************************************************************************/

// $Id$

#ifndef SOQT_MATERIALLIST_H
#define SOQT_MATERIALLIST_H

#include <Inventor/Qt/SoQtComponent.h>

class SoMaterial;
class SoAnyMaterialList;

typedef void SoQtMaterialListCB(void * closure, const SoMaterial * material);

// *************************************************************************

class SOQT_DLL_API SoQtMaterialList : public SoQtComponent {
  SOQT_OBJECT_HEADER(SoQtMaterialList, SoQtComponent);

public:
  SoQtMaterialList(
    QWidget * parent = NULL,
    const char * const name = NULL,
    SbBool embed = TRUE,
    const char * const dir = NULL);
  ~SoQtMaterialList(void);

  void addCallback(
    SoQtMaterialListCB * const callback,
    void * const closure = NULL);
  void removeCallback(
    SoQtMaterialListCB * const callback,
    void * const closure = NULL);

protected:
  SoQtMaterialList(
    QWidget * parent,
    const char * const name,
    SbBool embed,
    const char * const dir,
    SbBool build);

  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;

  QWidget * buildWidget(QWidget * parent);
  QWidget * buildPulldownMenu(QWidget * parent);

private:
  void constructor(const char * const dir, const SbBool build);

  void selectionCallback(int i);
  static void selection_cb(QWidget *, void *, void *);

  void paletteMenuCallback(QWidget *);
  static void palette_menu_cb(QWidget *, void *, void *);

  QWidget * listwidget;

  SoAnyMaterialList * common;

}; // public SoQtMaterialList

// *************************************************************************

#endif // ! SOQT_MATERIALLIST_H
