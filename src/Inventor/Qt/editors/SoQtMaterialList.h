/**************************************************************************
 *
 *  This file is part of the Coin SoQt GUI binding library.
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
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

//  $Id$

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
        void            addCallback(SoQtMaterialListCB *f,
                                void *userData = NULL);
        void            removeCallback(SoQtMaterialListCB *f,
                                void *userData = NULL);
#endif
    public slots:
        void            setPalette();
        void            setPalette(int);
        void            setPalette(const char *);
        void            setMaterial(const char *);
    signals:
        void            materialSelected(SoMaterial *);
        void            closed();

    protected:
                        SoQtMaterialList(QWidget *parent, const char *name,
                                SbBool buildInsideParent,
                                const char *dir, SbBool buildNow);
        virtual const char *    getDefaultWidgetName() const;
        virtual const char *    getDefaultTitle() const;
        virtual const char *    getDefaultIconTitle() const;
        virtual const char *    componentClassName() const;

        QWidget*        buildWidget(QWidget *parent);
        QWidget*        buildPulldownMenu(QWidget *parent);

    private:
        QPopupMenu*     menu;
        char*           materialDir;
        char*           curPalettePath;
        QListBox*       mtlList;

        QDir*           mtlPalettes;
        QDir*           mtlDirectory;
        SoMaterial*     material;

        void            dir2List(const char *dir);
};

#endif // ! SOQT_MATERIALLIST_H
