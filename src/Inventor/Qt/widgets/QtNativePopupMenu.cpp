/**************************************************************************\
 *
 *  This file is part of the Coin family of 3D visualization libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and / or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.  See the
 *  file LICENSE.GPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you desire to use this library in software that is incompatible
 *  with the GNU GPL, and / or you would like to take advantage of the
 *  additional benefits with regard to our support services, please
 *  contact Systems in Motion about acquiring a Coin Professional
 *  Edition License.  See <URL:http://www.coin3d.org> for more
 *  information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#include <qpopupmenu.h>
#include <qmetaobject.h>
#include <Inventor/Qt/widgets/moc_QtNativePopupMenu.icc>

#include <Inventor/SoLists.h>
#include <Inventor/errors/SoDebugError.h>

#include <soqtdefs.h>
#include <Inventor/Qt/widgets/QtNativePopupMenu.h>

/*!
  \class QtNativePopupMenu Inventor/Qt/widgets/QtNativePopupMenu.h
  \brief The QtNativePopupMenu class implements a common interface for popup
  menu management for all the Coin GUI toolkit libraries.
*/

// *************************************************************************

struct MenuRecord {
  int menuid;
  char * name;
  char * title;
  QPopupMenu * menu;
  QPopupMenu * parent;
}; // struct MenuRecord

struct ItemRecord {
  int itemid;
  int flags;
  char * name;
  char * title;
  QPopupMenu * parent;
}; // struct ItemRecord

#define ITEM_MARKED       0x0001
#define ITEM_SEPARATOR    0x0002
#define ITEM_ENABLED      0x0004

// *************************************************************************

/*!
  The constructor.
*/

QtNativePopupMenu::QtNativePopupMenu(
  void)
{
  this->menus = new SbPList;
  this->items = new SbPList;
} // QtNativePopupMenu()

/*!
  Destructor.
*/

QtNativePopupMenu::~QtNativePopupMenu()
{
  const int numMenus = this->menus->getLength();

  int i;
  for (i = 0; i < numMenus; i++) {
    MenuRecord * rec = (MenuRecord *) (*this->menus)[i];
    delete [] rec->name;
    delete [] rec->title;
    // If top-level QPopupMenu is not attached to any parent instance,
    // we dealloc it ourselves.
    if (rec->parent == NULL) delete rec->menu;
    delete rec;
  }

  const int numItems = this->items->getLength();
  for (i = 0; i < numItems; i++) {
    ItemRecord * rec = (ItemRecord *) (*this->items)[i];
    delete [] rec->name;
    delete [] rec->title;
    delete rec;
  }
} // ~QtNativePopupMenu()

// *************************************************************************

/*!
*/

int
QtNativePopupMenu::newMenu(
  const char * name,
  int menuid)
{
  int id = menuid;
  if (id == -1) {
    id = 1;
    while (this->getMenuRecord(id) != NULL) id++;
  } else {
    assert(this->getMenuRecord(id) == NULL &&
            "requested menuid already taken");
  }

  // id contains ok ID
  MenuRecord * rec = this->createMenuRecord(name);
  rec->menuid = id;
  this->menus->append((void *) rec);
  return id;
} // newMenu()

/*!
*/

int
QtNativePopupMenu::getMenu(
  const char * name)
{
  const int numMenus = this->menus->getLength();
  int i;
  for (i = 0; i < numMenus; i++) {
    MenuRecord * rec = (MenuRecord *) (*this->menus)[i];
    if (strcmp(rec->name, name) == 0)
      return rec->menuid;
  }
  return -1;
} // getMenu()

/*!
*/

void
QtNativePopupMenu::setMenuTitle(
  int menuid,
  const char * title)
{
  MenuRecord * rec = this->getMenuRecord(menuid);
  assert(rec && "no such menu");
  delete [] rec->title;
  rec->title = strcpy(new char [strlen(title)+1], title);
#if QT_VERSION >= 200
  if (rec->parent)
    rec->parent->changeItem(rec->menuid, QString(rec->title));
#else // Qt version < 2.0.0
  // This QMenuData::changeItem() method is being obsoleted from Qt
  // from version 2.0.0 onwards.
  if (rec->parent)
    rec->parent->changeItem(rec->title, rec->menuid);
#endif // Qt version < 2.0.0
} // setMenuTitle()

/*!
*/

const char *
QtNativePopupMenu::getMenuTitle(
  int menuid)
{
  MenuRecord * rec = this->getMenuRecord(menuid);
  assert(rec && "no such menu");
  return rec->title;
} // getMenuTitle()

// *************************************************************************

/*!
*/

int
QtNativePopupMenu::newMenuItem(
  const char * name,
  int itemid)
{
  int id = itemid;
  if (id == -1) {
    id = 1;
    while (this->getItemRecord(itemid) != NULL) id++;
  } else {
    assert(this->getItemRecord(itemid) == NULL &&
            "requested itemid already taken");
  }
  ItemRecord * rec = createItemRecord(name);
  rec->itemid = id;
  this->items->append(rec);
  return id;
} // newMenuItem()

/*!
*/

int
QtNativePopupMenu::getMenuItem(
  const char * name)
{
  const int numItems = this->items->getLength();
  int i;
  for (i = 0; i < numItems; i++) {
    ItemRecord * rec = (ItemRecord *) (*this->items)[i];
    if (strcmp(rec->name, name) == 0)
      return rec->itemid;
  }
  return -1;
} // getMenuItem()

/*!
*/

void
QtNativePopupMenu::setMenuItemTitle(
  int itemid,
  const char * title)
{
  ItemRecord * rec = this->getItemRecord(itemid);
  assert(rec && "no such menu");
  delete [] rec->title;
  rec->title = strcpy(new char [strlen(title)+1], title);
#if QT_VERSION >= 200
  if (rec->parent)
    rec->parent->changeItem(rec->itemid, QString(rec->title));
#else // Qt version < 2.0.0
  // This QMenuData::changeItem() method is being obsoleted from Qt
  // from version 2.0.0 onwards.
  if (rec->parent)
    rec->parent->changeItem(rec->title, rec->itemid);
#endif // Qt version < 2.0.0
} // setMenuItemTitle()

/*!
*/

const char *
QtNativePopupMenu::getMenuItemTitle(
  int itemid)
{
  ItemRecord * rec = this->getItemRecord(itemid);
  assert(rec && "no such menu");
  return rec->title;
} // getMenuItemTitle()

/*!
*/

void
QtNativePopupMenu::setMenuItemEnabled(
  int itemid,
  SbBool enabled)
{
  ItemRecord * rec = this->getItemRecord(itemid);
  assert(rec && "no such menu");
  assert(rec->parent && "a menuitem must have a parent to be enabled/disabled");
  rec->parent->setItemEnabled(rec->itemid, enabled ? true : false);
} // setMenuItemEnabled()

/*!
*/

SbBool
QtNativePopupMenu::getMenuItemEnabled(
  int itemid)
{
  ItemRecord * rec = this->getItemRecord(itemid);
  assert(rec && "no such menu");
  return rec->parent->isItemEnabled(rec->itemid) ? TRUE : FALSE;
} // getMenuItemEnabled()

/*!
*/

void
QtNativePopupMenu::_setMenuItemMarked(
  int itemid,
  SbBool marked)
{
  ItemRecord * rec = this->getItemRecord(itemid);
  if (rec == NULL)
    return;
  if (marked)
    rec->flags |= ITEM_MARKED;
  else
    rec->flags &= ~ITEM_MARKED;
  if (rec->parent != NULL)
    rec->parent->setItemChecked(rec->itemid, marked ? true : false);
} // _setMenuItemMarked()

/*!
*/

SbBool
QtNativePopupMenu::getMenuItemMarked(
  int itemid)
{
  ItemRecord * rec = this->getItemRecord(itemid);
  assert(rec && "no such menu");
  if (rec->parent == NULL)
    return (rec->flags & ITEM_MARKED) ? TRUE : FALSE;
  return rec->parent->isItemChecked(rec->itemid) ? TRUE : FALSE;
} // getMenuItemMarked()

// *************************************************************************

/*!
*/

void
QtNativePopupMenu::addMenu(
  int menuid,
  int submenuid,
  int pos)
{
  MenuRecord * super = this->getMenuRecord(menuid);
  MenuRecord * sub = this->getMenuRecord(submenuid);
  assert(super && sub && "no such menu");

  if (pos == -1)
    super->menu->insertItem(QString(sub->title), sub->menu, sub->menuid);
  else
    super->menu->insertItem(QString(sub->title),
                             sub->menu, sub->menuid, pos);
  sub->parent = super->menu;
} // addMenu()

/*!
*/

void
QtNativePopupMenu::addMenuItem(
  int menuid,
  int itemid,
  int pos)
{
  MenuRecord * menu = this->getMenuRecord(menuid);
  ItemRecord * item = this->getItemRecord(itemid);
  assert(menu && item && "no such menu");

  if (pos == -1)
    menu->menu->insertItem(QString(item->title), item->itemid);
  else
    menu->menu->insertItem(QString(item->title), item->itemid, pos);
  item->parent = menu->menu;
  if (item->flags & ITEM_MARKED)
    item->parent->setItemChecked(item->itemid, true);
} // addMenuItem()

void
QtNativePopupMenu::addSeparator(
  int menuid,
  int pos)
{
  MenuRecord * menu = this->getMenuRecord(menuid);
  assert(menu && "no such menu");

  ItemRecord * rec = createItemRecord("separator");
  menu->menu->insertSeparator(pos);
  rec->flags |= ITEM_SEPARATOR;
  this->items->append(rec);
} // addSeparator()

/*!
  This method removes the submenu with the given \a menuid.

  A removed menu can be attached again later - its menuid will still be
  allocated.
*/

void
QtNativePopupMenu::removeMenu(
  int menuid)
{
  MenuRecord * rec = this->getMenuRecord(menuid);
  assert(rec && "no such menu");

  if (rec->menuid == 0) {
#if SOQT_DEBUG
    SoDebugError::postInfo("QtNativePopupMenu::RemoveMenu", "can't remove root");
#endif // SOQT_DEBUG
    return;
  }
  if (rec->parent == NULL) {
#if SOQT_DEBUG
    SoDebugError::postInfo("QtNativePopupMenu::RemoveMenu", "menu not attached");
#endif // SOQT_DEBUG
    return;
  }
  rec->parent->removeItem(rec->menuid);
  rec->parent = NULL;
} // removeMenu()

/*!
  This method removes the menu item with the given \a itemid.

  A removed menu item can be attached again later - its itemid will still
  be allocated.
*/

void
QtNativePopupMenu::removeMenuItem(
  int itemid)
{
  ItemRecord * rec = this->getItemRecord(itemid);
  assert(rec && "no such item");

  if (rec->parent == NULL) {
#if SOQT_DEBUG
    SoDebugError::postInfo("QtNativePopupMenu::RemoveMenu", "item not attached");
#endif // SOQT_DEBUG
    return;
  }
  rec->parent->removeItem(rec->itemid);
  rec->parent = NULL;
} // removeMenuItem()

// *************************************************************************

// Doc in superclass.
void
QtNativePopupMenu::popUp(QWidget * inside, int x, int y)
{
  MenuRecord * rec = this->getMenuRecord(0);
  rec->menu->popup(inside->mapToGlobal(QPoint(x, y)));
} // PopUp()

// *************************************************************************

/*!
*/

MenuRecord *
QtNativePopupMenu::getMenuRecord(
  int menuid)
{
  const int numMenus = this->menus->getLength();
  int i;
  for (i = 0; i < numMenus; i++)
    if (((MenuRecord *) (*this->menus)[i])->menuid == menuid)
      return (MenuRecord *) (*this->menus)[i];
  return (MenuRecord *) NULL;
} // getMenuRecord()

/*!
*/

ItemRecord *
QtNativePopupMenu::getItemRecord(
  int itemid)
{
  const int numItems = this->items->getLength();
  int i;
  for (i = 0; i < numItems; i++)
    if (((ItemRecord *) (*this->items)[i])->itemid == itemid)
      return (ItemRecord *) (*this->items)[i];
  return (ItemRecord *) NULL;
} // getItemRecord()

// *************************************************************************

/*!
*/

MenuRecord *
QtNativePopupMenu::createMenuRecord(
  const char * name)
{
  MenuRecord * rec = new MenuRecord;
  rec->menuid = -1;
  rec->name = strcpy(new char [strlen(name)+1], name);
  rec->title = strcpy(new char [strlen(name)+1], name);
  rec->menu = new QPopupMenu((QWidget *) NULL, name);
  QObject::connect(rec->menu, SIGNAL(activated(int)),
                    this, SLOT(itemActivation(int)));
  rec->parent = NULL;
  return rec;
} // create()

/*!
*/

ItemRecord *
QtNativePopupMenu::createItemRecord(
  const char * name)
{
  ItemRecord * rec = new ItemRecord;
  rec->itemid = -1;
  rec->flags = 0;
  rec->name = strcpy(new char [strlen(name)+1], name);
  rec->title = strcpy(new char [strlen(name)+1], name);
  rec->parent = NULL;
  return rec;
} // create()

// *************************************************************************

void
QtNativePopupMenu::itemActivation(// private slot
  int itemid)
{
  inherited::invokeMenuSelection(itemid);
} // menuSelection()

// *************************************************************************
