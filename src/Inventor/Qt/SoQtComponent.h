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

//  $Id$

#ifndef __SOQT_COMPONENT_H__
#define __SOQT_COMPONENT_H__

#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>
#include <Inventor/SoLists.h>
#include <qobject.h>

class QWidget;
class SoQtComponent;


typedef void SoQtComponentCB(void * userData, SoQtComponent * comp);
typedef void SoQtComponentVisibilityCB(void * userData, SbBool visibleFlag);


class SoQtComponent : public QObject
{
  Q_OBJECT

public:
  virtual ~SoQtComponent();

  virtual void show(void);
  virtual void hide(void);
  SbBool isVisible(void);
  QWidget * getWidget(void) const;
  QWidget * baseWidget(void) const;
  SbBool isTopLevelShell(void) const;
  QWidget * getShellWidget(void) const;
  QWidget * getParentWidget(void) const;
  void setSize(const SbVec2s & size);
  SbVec2s getSize(void);
  void setTitle(const char * const newTitle);
  const char * getTitle(void) const;
  void setIconTitle(const char * const newIconTitle);
  const char * getIconTitle(void) const;
  void setWindowCloseCallback(SoQtComponentCB * func,
                              void * const data = NULL);
  static SoQtComponent * getComponent(QWidget * const w);
  const char * getWidgetName(void) const;
  const char * getClassName(void) const;


protected:
  SoQtComponent(QWidget * const parent = NULL,
                const char * const name = NULL,
                const SbBool buildInsideParent = TRUE);

  void setClassName(const char * const name);
  void setBaseWidget(QWidget * w);

  void subclassInitialized(void);

  virtual const char * componentClassName(void) const = 0;
  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;

  virtual void sizeChanged(const SbVec2s & newSize) = 0;

  void addVisibilityChangeCallback(SoQtComponentVisibilityCB * func,
                                   void * userData = NULL);
  void removeVisibilityChangeCallback(SoQtComponentVisibilityCB * func,
                                      void * userData = NULL);

  void openHelpCard(const char * name);

  virtual bool eventFilter(QObject * obj, QEvent * e);

private slots:
  void widgetClosed(void);

private:
  QWidget * widget;
  QWidget * parent;
  SbBool buildinside;
  QString classname, widgetname, captiontext, icontext;
  SoQtComponentCB * closeCB;
  void * closeCBdata;
  SbPList * visibilitychangeCBs;

  // Could probably improve code by using an SbDict here. 990205 mortene.
  static SbPList soqtcomplist;
  static SbPList qtwidgetlist;

  // Need to keep track of setSize()/getSize() even when there's no
  // QWidget yet.
  SbVec2s storesize;
};

#endif // ! __SOQT_COMPONENT_H__
