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

class SOQT_DLL_API SoQtMaterialEditor : public SoQtComponent
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
