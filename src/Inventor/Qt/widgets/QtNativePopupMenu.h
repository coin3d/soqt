/**************************************************************************\
 *
 *  This file is part of the Coin GUI toolkit libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation.  See the
 *  file LICENSE.LGPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you want to use this library with software that is incompatible
 *  licensewise with the LGPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#ifndef SOQT_QTNATIVEPOPUPMENU_H
#define SOQT_QTNATIVEPOPUPMENU_H

#include <qobject.h>
#include <Inventor/Qt/SoQtBasic.h>
#include <Inventor/Qt/widgets/SoQtPopupMenu.h>

// *************************************************************************

struct MenuRecord;
struct ItemRecord;

class QtNativePopupMenu : public QObject, public SoQtPopupMenu
{
  typedef SoQtPopupMenu inherited;
  Q_OBJECT

public:
  QtNativePopupMenu(void);
  virtual ~QtNativePopupMenu();

  virtual int newMenu(const char * name, int menuid = -1);
  virtual int getMenu(const char * name);
  virtual void setMenuTitle(int id, const char * title);
  virtual const char * getMenuTitle(int id);

  virtual int newMenuItem(const char * name, int itemid = -1);
  virtual int getMenuItem(const char * name);
  virtual void setMenuItemTitle(int itemid, const char * title);
  virtual const char * getMenuItemTitle(int itemid);
  virtual void setMenuItemEnabled(int itemid, SbBool enabled);
  virtual SbBool getMenuItemEnabled(int itemid);
  virtual SbBool getMenuItemMarked(int itemid);

  virtual void addMenu(int menuid, int submenuid, int pos = -1);
  virtual void addMenuItem(int menuid, int itemid, int pos = -1);
  virtual void addSeparator(int menuid, int pos = -1);
  virtual void removeMenu(int menuid);
  virtual void removeMenuItem(int itemid);

  virtual void popUp(QWidget * inside, int x, int y);

protected:
  virtual void _setMenuItemMarked(int itemid, SbBool marked);

  MenuRecord * getMenuRecord(int menuid);
  ItemRecord * getItemRecord(int itemid);
  MenuRecord * createMenuRecord(const char * name);
  ItemRecord * createItemRecord(const char * name);

private slots:
  void itemActivation(int itemid);

private:
  SbPList * menus;
  SbPList * items;

};  // class QtNativePopupMenu

// *************************************************************************

#endif // ! SOQT_QTNATIVEPOPUPMENU_H
