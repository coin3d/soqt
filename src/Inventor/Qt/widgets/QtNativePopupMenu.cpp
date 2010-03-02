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

/*!
  \class QtNativePopupMenu Inventor/Qt/widgets/QtNativePopupMenu.h
  \brief The QtNativePopupMenu class implements a common interface for popup
  menu management for all the Coin GUI toolkit libraries.
*/

// *************************************************************************

// FIXME: create a new Qt4NativePopupMenu. There are just too
// many differences between Qt3 menu handling and Qt4 menu handling.

#include <qmetaobject.h>

// *************************************************************************

// Take care of class name incompatibilities between Qt 3 and Qt 4.

#if QT_VERSION < 0x040000 // pre Qt 4
#include <qaction.h>
#include <qpopupmenu.h>
#define QPOPUPMENU_CLASS QPopupMenu
#else // Qt 4.0.0+
#include <QtGui/QMenu>
#define QPOPUPMENU_CLASS QMenu
#endif // Qt 4.0.0+

// ************************************************************************

#include <Inventor/SoLists.h>
#include <Inventor/errors/SoDebugError.h>

#include <Inventor/Qt/widgets/QtNativePopupMenu.h>
#include <Inventor/Qt/widgets/moc_QtNativePopupMenu.icc>

#include <soqtdefs.h>

// *************************************************************************

struct MenuRecord {
  int menuid;
  char * name;
  char * title;
  QAction * action;
  QPOPUPMENU_CLASS * menu;
  QPOPUPMENU_CLASS * parent;
}; // struct MenuRecord

struct ItemRecord {
  int itemid;
  int flags;
  char * name;
  char * title;
  QAction * action;
  QPOPUPMENU_CLASS * parent;
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
    // We used to delete only the root menu, and trust that Qt cleaned
    // up all submenus, but after doing some testing with huge menus,
    // we found that Qt does _not_ automatically delete submenus when
    // the parent is destructed. We therefore delete all menus
    // manually here. pederb, 2005-12-05
    delete rec->menu;
    delete rec;
  }

  const int numItems = this->items->getLength();
  for (i = 0; i < numItems; i++) {
    ItemRecord * rec = (ItemRecord *) (*this->items)[i];
    delete [] rec->name;
    delete [] rec->title;
    delete rec;
  }

  delete this->menus;
  delete this->items;

} // ~QtNativePopupMenu()

// *************************************************************************

/*!
*/

int
QtNativePopupMenu::newMenu(
  const char * name,
  int menuid)
{
  // FIXME: this function is the same in the other So-libraries --
  // move to common abstraction layer SoGuiPopupMenu of
  // possible. 20031012 mortene.

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
  if (rec->parent) {
    //rec->parent->actionAt(QPoint(rec->menuid,0))->setText(rec->title);
    getMenuRecord(rec->menuid)->action->setText(rec->title);
  }
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
    while (this->getItemRecord(id) != NULL) id++;
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
#if QT_VERSION >= 0x040000
    rec->parent->actionAt(QPoint(rec->itemid,0))->setText(rec->title);
#else
    rec->parent->changeItem(rec->itemid, QString(rec->title));
#endif
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
QtNativePopupMenu::setMenuItemEnabled(int itemid,
                                      SbBool enabled)
{
  ItemRecord * rec = this->getItemRecord(itemid);
  if (rec) {
#if QT_VERSION >= 0x040000
    rec->parent->actionAt(QPoint(rec->itemid,0))->setEnabled(enabled ? true : false);
#else
    rec->parent->setItemEnabled(rec->itemid, enabled ? true : false);
#endif
    return;
  }
  MenuRecord * mrec = this->getMenuRecord(itemid);
  assert(mrec && "no such menu");
  assert(mrec->parent && "a menuitem must have a parent to be enabled/disabled");

#if QT_VERSION >= 0x040000
  mrec->parent->actionAt(QPoint(mrec->menuid,0))->setEnabled(enabled ? true : false);
#else
  mrec->parent->setItemEnabled(mrec->menuid, enabled ? true : false);
#endif
} // setMenuItemEnabled()

/*!
*/

SbBool
QtNativePopupMenu::getMenuItemEnabled(int itemid)
{
  ItemRecord * rec = this->getItemRecord(itemid);

  if (rec) {
#if QT_VERSION >= 0x040000
    return rec->parent->actionAt(QPoint(rec->itemid,0))->isEnabled();
#else
    return rec->parent->isItemEnabled(rec->itemid) ? TRUE : FALSE;
#endif
  }

  MenuRecord * mrec = this->getMenuRecord(itemid);
  assert(mrec && "no such menu");
  assert(mrec->parent && "a menuitem must have a parent to be enabled/disabled");

#if QT_VERSION >= 0x040000
  return mrec->parent->actionAt(QPoint(mrec->menuid,0))->isEnabled();
#else
  return mrec->parent->isItemEnabled(mrec->menuid) ? TRUE : FALSE;
#endif
} // getMenuItemEnabled()

/*!
*/

void
QtNativePopupMenu::_setMenuItemMarked(int itemid, SbBool marked)
{
  ItemRecord * rec = this->getItemRecord(itemid);
  if (rec == NULL)
    return;
  if (marked)
    rec->flags |= ITEM_MARKED;
  else
    rec->flags &= ~ITEM_MARKED;

  if (rec->parent != NULL) {
#if QT_VERSION >= 0x040000
    QAction * action = rec->action;
    if (action) {
      //FIXME: Could this be done on creation? - BFG 20090910
      action->setCheckable(true);
      action->setChecked(marked ? true : false);
    }
#else
    rec->parent->setItemChecked(rec->itemid, marked ? true : false);
#endif
  }
}

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

#if QT_VERSION >= 0x040000
  QAction * action = rec->action;
  if (!action) return false;
  return action->isChecked();
#else
  return rec->parent->isItemChecked(rec->itemid) ? TRUE : FALSE;
#endif
} // getMenuItemMarked()

// *************************************************************************

/*!
*/

void
QtNativePopupMenu::addMenu(int menuid,
                           int submenuid,
                           int pos)
{
  MenuRecord * super = this->getMenuRecord(menuid);
  MenuRecord * sub = this->getMenuRecord(submenuid);
  assert(super && sub && "no such menu");

  // disconnect the submenu from the activated() signal. In Qt 4.0
  // only the parent menu should be connected, since both the parent
  // menu and the submenu will generate a call to
  // itemActivation(). Multiple calls to itemActivation() causes a
  // segfault when selecting Quadbuffer stereo, at least when it's not
  // supported. (20050726 frodo)

  // this was changed/fixed again in Qt 4.4.0, so now we shouldn't
  // disconnect menu items if this version is detected...
  // (20070530 pederb)
#if (QT_VERSION >= 0x040000) && (QT_VERSION < 0x040400)
  QObject::disconnect(sub->menu, SIGNAL(activated(int)),
                      this, SLOT(itemActivation(int)));
#endif // QT-version >= 400 && QT-version < 4.4.0

#if QT_VERSION >= 0x040000
  QAction * action;
  if (pos == -1) {
    action = super->menu->addMenu(sub->menu);
  }
  else {
    QAction * before = super->menu->actionAt(QPoint(pos,0));
    action = super->menu->insertMenu(before,sub->menu);
  }
  action->setText(QString(sub->title));
#else
  if (pos == -1)
    super->menu->insertItem(QString(sub->title), sub->menu, sub->menuid);
  else
    super->menu->insertItem(QString(sub->title),
			    sub->menu, sub->menuid, pos);
#endif
  sub->parent = super->menu;
} // addMenu()

/*!
*/

void
QtNativePopupMenu::addMenuItem(int menuid,
                               int itemid,
                               int pos)
{
  MenuRecord * menu = this->getMenuRecord(menuid);
  assert(menu && "invalid parent menu id");
  ItemRecord * item = this->getItemRecord(itemid);
  assert(item && "invalid child menu id");

#if QT_VERSION >= 0x040000
  item->action = new QAction(menu->menu);
  item->action->setText(item->title);
  if (pos == -1) {
    menu->menu->addAction(item->action);
  }
  else {
    menu->menu->insertAction(menu->menu->actionAt(QPoint(pos,0)),item->action);
  }
#else
  if (pos == -1)
    menu->menu->insertItem(QString(item->title), item->itemid);
  else
    menu->menu->insertItem(QString(item->title), item->itemid, pos);
#endif
  item->parent = menu->menu;

#if QT_VERSION >= 0x040000
  // FIXME: is this really safe? (20050726 frodo)
  QAction * action = (QAction *) item->parent->actionAt(QPoint(itemid,0));
  if (action) action->setCheckable(true);
#endif // Qt 4.*

  if (item->flags & ITEM_MARKED) {
#if QT_VERSION >= 0x040000
    if (action) action->setChecked(true);
#else
    item->parent->setItemChecked(item->itemid, true);
#endif
  }
} // addMenuItem()

void
QtNativePopupMenu::addSeparator(int menuid,
                                int pos)
{
  MenuRecord * menu = this->getMenuRecord(menuid);
  assert(menu && "no such menu");

  ItemRecord * rec = createItemRecord("separator");
#if QT_VERSION >= 0x040000
  menu->menu->insertSeparator(menu->menu->actionAt(QPoint(pos,0)));
#else
  menu->menu->insertSeparator(pos);
#endif
  rec->flags |= ITEM_SEPARATOR;
  this->items->append(rec);
} // addSeparator()

/*!
  This method removes the submenu with the given \a menuid.

  A removed menu can be attached again later - its menuid will still be
  allocated.
*/

void
QtNativePopupMenu::removeMenu(int menuid)
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
#if QT_VERSION >= 0x040000
  rec->parent->removeAction(rec->parent->actionAt(QPoint(rec->menuid,0)));
#else
  rec->parent->removeItem(rec->menuid);
#endif
  rec->parent = NULL;
} // removeMenu()

/*!
  This method removes the menu item with the given \a itemid.

  A removed menu item can be attached again later - its itemid will still
  be allocated.
*/

void
QtNativePopupMenu::removeMenuItem(int itemid)
{
  ItemRecord * rec = this->getItemRecord(itemid);
  assert(rec && "no such item");

  if (rec->parent == NULL) {
#if SOQT_DEBUG
    SoDebugError::postInfo("QtNativePopupMenu::RemoveMenu", "item not attached");
#endif // SOQT_DEBUG
    return;
  }
#if QT_VERSION >= 0x040000
  rec->parent->removeAction(rec->parent->actionAt(QPoint(rec->itemid,0)));
#else
  rec->parent->removeItem(rec->itemid);
#endif
  rec->parent = NULL;
} // removeMenuItem()

// *************************************************************************

// Doc in superclass.
void
QtNativePopupMenu::popUp(QWidget * inside, int x, int y)
{
  MenuRecord * rec = this->getMenuRecord(0);

  // Use exec() and not popup(). popup() doesn't seem to work properly
  // with a GL widget (the GL-redraw seems to overwrite the popup
  // widget or something). pederb, 2003-10-01
  //
  // An additional piece of information: the popup-menu misbehavior is
  // that at first attempt just a "shadow" comes up, and then on the
  // second RMB-press the menu actually comes up. This problem has
  // only been seen on a few Windows 2000 platforms, though, so in
  // case we ever need to revert to using popup() again, make sure the
  // code is properly tested over a wide range of platforms.
  // mortene, 2003-10-01
  //
  // Ignore return value. We use callbacks.
  (void) rec->menu->exec(inside->mapToGlobal(QPoint(x, y)));
}

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
QtNativePopupMenu::getItemRecord(int itemid)
{
  const int numItems = this->items->getLength();
  for (int i = 0; i < numItems; i++) {
    const int recid = ((ItemRecord *) (*this->items)[i])->itemid;
    if (recid == itemid) { return (ItemRecord *) (*this->items)[i]; }
  }

  return (ItemRecord *) NULL;
}

// *************************************************************************

/*!
*/
ItemRecord *
QtNativePopupMenu::getItemRecordFromAction(QAction * action)
{
  const int numItems = this->items->getLength();
  for (int i = 0; i < numItems; i++) {
    const ItemRecord * rec = static_cast<ItemRecord *>((*this->items)[i]);
    if (rec->action == action) { return (ItemRecord *) (*this->items)[i]; }
  }

  return (ItemRecord *) NULL;
}

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

#if QT_VERSION >= 0x040000
  rec->menu = new QPOPUPMENU_CLASS(QString(name));
  QObject::connect(rec->menu, SIGNAL(triggered(QAction *)),
                   this, SLOT(itemActivation(QAction *)));
#else
  rec->menu = new QPOPUPMENU_CLASS((QWidget *) NULL, name);
  QObject::connect(rec->menu, SIGNAL(activated(int)),
                   this, SLOT(itemActivation(int)));
#endif

  rec->parent = NULL;
  rec->action = NULL;
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
  rec->action = NULL;
  return rec;
} // create()

// *************************************************************************

void
QtNativePopupMenu::itemActivation(// private slot
  QAction * action
  )
{
  ItemRecord * rec = getItemRecordFromAction(action);
  assert(rec);
  inherited::invokeMenuSelection(rec->itemid);
} // menuSelection()

void
QtNativePopupMenu::itemActivation(// private slot used for Qt3 code path
  int itemid
  )
{
  inherited::invokeMenuSelection(itemid);
}

// *************************************************************************
