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

// $Id$

#ifndef SOQT_COMPONENT_H
#define SOQT_COMPONENT_H

#include <qobject.h>

#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>
#include <Inventor/SoLists.h>

#include <Inventor/Qt/SoQtObject.h>

class QWidget;
class SoQtComponent;

typedef void SoQtComponentCB( void * user, SoQtComponent * component );
typedef void SoQtComponentVisibilityCB( void * user, SbBool visible );

// *************************************************************************

class SOQT_DLL_EXPORT SoQtComponent : public SoQtObject {
  SOQT_OBJECT_ABSTRACT_HEADER(SoQtComponent, SoQtObject);
  Q_OBJECT

public:
  virtual ~SoQtComponent(void);

  virtual void show(void);
  virtual void hide(void);
  SbBool isVisible(void);
  QWidget * getWidget(void) const;
  QWidget * baseWidget(void) const;
  SbBool isTopLevelShell(void) const;
  QWidget * getShellWidget(void) const;
  QWidget * getParentWidget(void) const;
  void setSize( const SbVec2s size );
  SbVec2s getSize(void) const;
  void setTitle( const char * const title );
  const char * getTitle(void) const;
  void setIconTitle( const char * const title );
  const char * getIconTitle(void) const;
  void setWindowCloseCallback( SoQtComponentCB * const func,
                               void * const user = NULL );
  static SoQtComponent * getComponent( QWidget * const widget );
  const char * getWidgetName(void) const;
  const char * getClassName(void) const;

  static void initClasses(void);

protected:
  SoQtComponent(
    QWidget * const parent = NULL,
    const char * const name = NULL,
    const SbBool embed = TRUE );

  virtual void afterRealizeHook(void);

  void setClassName( const char * const name );
  void setBaseWidget( QWidget * const widget );

  void registerWidget( QWidget * widget );
  void unregisterWidget( QWidget * widget );

  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;

  virtual void sizeChanged( const SbVec2s size );

  void addVisibilityChangeCallback( SoQtComponentVisibilityCB * const func,
                                    void * const user = NULL );
  void removeVisibilityChangeCallback( SoQtComponentVisibilityCB * const func,
                                       void * const user = NULL );

  void openHelpCard( const char * const name );

  virtual bool eventFilter( QObject * obj, QEvent * e );

private slots:
  void widgetClosed(void);

private:
  QWidget * parent;
  QWidget * widget;
  SbBool embedded, shelled;
  QString classname, widgetname, captiontext, icontext;
  SoQtComponentCB * closeCB;
  void * closeCBdata;
  SbPList * visibilitychangeCBs;
  SbBool realized;

  static SbPList * soqtcomplist;

  SbVec2s storesize;

}; // class SoQtComponent

// *************************************************************************

#endif // ! SOQT_COMPONENT_H
