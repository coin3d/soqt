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

#ifndef _SO_QT_MATERIAL_EDITOR_
# define _SO_QT_MATERIAL_EDITOR_

# include <Inventor/Qt/SoQtComponent.h>
# include <qwidget.h>
 
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

  class SoQtMaterialEditor : public SoQtComponent {
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

	void	attach(SoMaterial *material, int index = 0);
	void 	detach();

	SbBool	isAttached();

	void	addMaterialChangedCallback(SoQtMaterialEditorCB *f,
			void *userData = NULL);
	void	removeMaterialChangedCallback(SoQtMaterialEditorCB *f,
			void *userData = NULL);

	void	setUpdateFrequency(UpdateFrequency freq);
	UpdateFrequency	getUpdateFrequency();

	void	setMaterial(const SoMaterial &mtl);
	const SoMaterial&	getMaterial() const;


    public slots:
	void		material_list();
	void		continuous();
	void		manual();
	void		accept();
	void		menu_popup();
	void		colorChanged(QColor&);
	void		rButtonPressed();
	void		cButtonPressed();
	void		setMaterial(SoMaterial *);
	void		clearAllButtons();

    signals:
        void		materialChanged();

    protected: 
	const char*	componentClassName() const;

    private:
	SoMaterial*	material;
	SoMFColor*	colors[4];
	int		index;
	int		contId;
	int		manuId;

	QWidget		*acceptButton;
	QCheckBox	*checkButtons[4];
	QRadioButton	*radioButtons[4];
	QPopupMenu	*menu;
	QButton		*menuButton;

	UpdateFrequency	updatefreq;

	QWidget*	mgrWidget;
	
	_SoQtColorEditor	*colorEditor;
	_SoQtColorSlider	*sliders[6];
	QColorSelection		*colorSelection;

	QWidget*	editColor;
	SoGLMaterialSphere*	ball;
	SoMaterial*	dummyMaterial;
	SoQtMaterialList*	materialList;
	
	void		connectUpdaters(bool connect = true);
};
#endif


