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

#ifndef SOQT_COMPONENT_H
#define SOQT_COMPONENT_H

#include <qobject.h>

#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>
#include <Inventor/SoLists.h>

#include <Inventor/Qt/SoQtBasic.h>

class QWidget;
class SoQtComponent;

typedef void SoQtComponentCB( void * user, SoQtComponent * component );
typedef void SoQtComponentVisibilityCB( void * user, SbBool visible );

// *************************************************************************

class SOQT_DLL_EXPORT SoQtComponent : public QObject
{
  typedef QObject inherited;

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


protected:
  SoQtComponent(
    QWidget * const parent = NULL,
    const char * const name = NULL,
    const SbBool embed = TRUE );

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

  static SbPList * soqtcomplist;

  SbVec2s storesize;

}; // class SoQtComponent

// *************************************************************************

#endif // ! SOQT_COMPONENT_H
