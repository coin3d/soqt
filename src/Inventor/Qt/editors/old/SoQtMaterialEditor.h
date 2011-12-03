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
