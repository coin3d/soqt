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

#ifndef SOQT_MATERIALEDITOR_H
#define SOQT_MATERIALEDITOR_H

#include <Inventor/Qt/SoQtComponent.h>
#include <qwidget.h>

  class _SoQtColorSlider;
  class _SoQtColorEditor;
  class SoQtMaterialList;
  class SoMaterial;
  class QPopupMenu;
  class QButton;
  class QRadioButton;
  class QCheckBox;
  class SoGLMaterialSphere;
  class QColorSelection;
  class SoMFColor;


typedef void SoQtMaterialEditorCB(void *userData, const SoMaterial *mtl);

class SOQT_DLL_EXPORT SoQtMaterialEditor : public SoQtComponent
{
  Q_OBJECT
public:

        enum UpdateFrequency {
                CONTINUOUS,
                AFTER_ACCEPT
        };

                SoQtMaterialEditor(QWidget *parent = NULL,
                        const char *name =NULL,
                        SbBool buildInsideParent = TRUE);
                ~SoQtMaterialEditor();

        void    attach(SoMaterial *material, int index = 0);
        void    detach();

        SbBool  isAttached();

        void    addMaterialChangedCallback(SoQtMaterialEditorCB *f,
                        void *userData = NULL);
        void    removeMaterialChangedCallback(SoQtMaterialEditorCB *f,
                        void *userData = NULL);

        void    setUpdateFrequency(UpdateFrequency freq);
        UpdateFrequency getUpdateFrequency();

        void    setMaterial(const SoMaterial &mtl);
        const SoMaterial&       getMaterial() const;


public slots:
        void            material_list();
        void            continuous();
        void            manual();
        void            accept();
        void            menu_popup();
        void            colorChanged(QColor&);
        void            rButtonPressed();
        void            cButtonPressed();
        void            setMaterial(SoMaterial *);
        void            clearAllButtons();

signals:
        void            materialChanged();

protected:
        const char*     componentClassName() const;

private:
        SoMaterial*     material;
        SoMFColor*      colors[4];
        int             index;
        int             contId;
        int             manuId;

        QWidget         *acceptButton;
        QCheckBox       *checkButtons[4];
        QRadioButton    *radioButtons[4];
        QPopupMenu      *menu;
        QButton         *menuButton;

        UpdateFrequency updatefreq;

        QWidget*        mgrWidget;

        _SoQtColorEditor        *colorEditor;
        _SoQtColorSlider        *sliders[6];
        QColorSelection         *colorSelection;

        QWidget*        editColor;
        SoGLMaterialSphere*     ball;
        SoMaterial*     dummyMaterial;
        SoQtMaterialList*       materialList;

        void            connectUpdaters(bool connect = true);
};

#endif // ! SOQT_MATERIALEDITOR_H
