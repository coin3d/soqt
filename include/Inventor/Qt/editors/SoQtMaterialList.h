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
 *  http://www.sim.no/ sales@sim.no Voice: +47 73540378 Fax: +47 73943861
 *
\**************************************************************************/

#ifndef _SO_QT_MATERIALLIST_H_
# define _SO_QT_MATERIALLIST_H_

# include <Inventor/Qt/SoQtComponent.h>

  class SoMaterial;
  class QDir;
  class QListBox;
  class QPopupMenu;

  typedef void SoQtMaterialListCB(void *userData, const SoMaterial *mtl);

  class SoQtMaterialList : public SoQtComponent {
    Q_OBJECT;
    public:
			SoQtMaterialList(QWidget *parent = NULL,
				const char *name = NULL, 
				SbBool buildInsideParent = TRUE,
				const char *dir = NULL);
			~SoQtMaterialList();

#if 0
	void		addCallback(SoQtMaterialListCB *f, 
				void *userData = NULL);
	void		removeCallback(SoQtMaterialListCB *f,
				void *userData = NULL);
#endif
    public slots:
	void		setPalette();
	void		setPalette(int);
	void		setPalette(const char *);
	void		setMaterial(const char *);
    signals:
	void		materialSelected(SoMaterial *);
	void		closed();

    protected:
			SoQtMaterialList(QWidget *parent, const char *name,
				SbBool buildInsideParent,
				const char *dir, SbBool buildNow);
	virtual const char *	getDefaultWidgetName() const;
	virtual const char *	getDefaultTitle() const;
	virtual const char *	getDefaultIconTitle() const;
 	virtual const char *	componentClassName() const;

	QWidget*	buildWidget(QWidget *parent);
	QWidget*	buildPulldownMenu(QWidget *parent);

    private:
	QPopupMenu*	menu;
	char*		materialDir;
	char*		curPalettePath;
	QListBox*	mtlList;

	QDir*		mtlPalettes;
	QDir*		mtlDirectory;
	SoMaterial*	material;

	void		dir2List(const char *dir);
  };

#endif
