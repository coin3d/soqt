/**************************************************************************\
 *
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
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

static const char rcsid[] =
  "$Id$";

#include <qpopupmenu.h>

#include <Inventor/SoLists.h>
#include <Inventor/errors/SoDebugError.h>

#include <soqtdefs.h>
#include <Inventor/Qt/widgets/SoQtPopupMenu.h>

/*!
  \class SoQtPopupMenu Inventor/Qt/widgets/SoQtPopupMenu.h
  \brief The SoQtPopupMenu class implements a common interface for popup
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

SoQtPopupMenu::SoQtPopupMenu(
  void )
{
  this->menus = new SbPList;
  this->items = new SbPList;
} // SoQtPopupMenu()

/*!
  Destructor.
*/

SoQtPopupMenu::~SoQtPopupMenu(
  void )
{
  const int numMenus = this->menus->getLength();
  QPopupMenu * popup = NULL;
  int i;
  for ( i = 0; i < numMenus; i++ ) {
    MenuRecord * rec = (MenuRecord *) (*this->menus)[i];
    if ( rec->menuid == 0 ) popup = rec->menu;
    delete [] rec->name;
    delete [] rec->title;
    if ( rec->parent == NULL ) delete rec->menu; // menu not attached
    delete rec;
  }

  const int numItems = this->items->getLength();
  for ( i = 0; i < numItems; i++ ) {
    ItemRecord * rec = (ItemRecord *) (*this->items)[i];
    delete [] rec->name;
    delete [] rec->title;
    delete rec;
  }

  // delete root popup menu
  delete popup;
} // ~SoQtPopupMenu()

// *************************************************************************

/*!
*/

int
SoQtPopupMenu::NewMenu(
  char * name,
  int menuid )
{
  int id = menuid;
  if ( id == -1 ) {
    id = 1;
    while ( this->getMenuRecord( id ) != NULL ) id++;
  } else {
    if ( this->getMenuRecord( id ) != NULL ) {
#if SOQT_DEBUG
      SoDebugError::postInfo( "SoQtPopupMenu::NewMenu",
        "requested menuid already taken" );
#endif // SOQT_DEBUG
      return -1;
    }
  }
  // id contains ok ID
  MenuRecord * rec = createMenuRecord( name );
  rec->menuid = id;
  this->menus->append( (void *) rec );
  return id;
} // NewMenu()

/*!
*/

int
SoQtPopupMenu::GetMenu(
  char * name )
{
  const int numMenus = this->menus->getLength();
  int i;
  for ( i = 0; i < numMenus; i++ )
    if ( strcmp( ((MenuRecord *) (*this->menus)[i])->name, name ) == 0 )
      return ((MenuRecord *) (*this->menus)[i])->menuid;
  return -1;
} // GetMenu()

/*!
*/

void
SoQtPopupMenu::SetMenuTitle(
  int menuid,
  char * title )
{
  MenuRecord * rec = this->getMenuRecord( menuid );
  if ( rec == NULL ) {
    SoDebugError::postWarning( "SoQtPopupMenu::SetMenuTitle",
      "no such menu (%d.title = \"%s\")", menuid, title );
    return;
  }
  delete [] rec->title;
  rec->title = strcpy( new char [strlen(title)+1], title );
#if QT_VERSION >= 200
  if ( rec->parent )
    rec->parent->changeItem( rec->menuid, QString( rec->title ) );
#else // Qt version < 2.0.0
  // This QMenuData::changeItem() method is being obsoleted from Qt
  // from version 2.0.0 onwards.
  if ( rec->parent )
    rec->parent->changeItem( rec->title, rec->menuid );
#endif // Qt version < 2.0.0
} // SetMenuTitle()

/*!
*/

char *
SoQtPopupMenu::GetMenuTitle(
  int menuid )
{
  MenuRecord * rec = this->getMenuRecord( menuid );
  if ( rec == NULL )
    return NULL;
  return rec->title;
} // GetMenuTitle()

// *************************************************************************

/*!
*/

int
SoQtPopupMenu::NewMenuItem(
  char * name,
  int itemid )
{
  int id = itemid;
  if ( id == -1 ) {
    id = 1;
    while ( this->getItemRecord( itemid ) != NULL ) id++;
  } else {
    if ( this->getItemRecord( itemid ) != NULL ) {
#if SOQT_DEBUG
      SoDebugError::postInfo( "SoQtPopupMenu::NewMenuItem",
        "requested itemid already taken" );
#endif // SOQT_DEBUG
      return -1;
    }
  }
  ItemRecord * rec = createItemRecord( name );
  rec->itemid = id;
  this->items->append( rec );
  return id;
} // NewMenuItem()

/*!
*/

int
SoQtPopupMenu::GetMenuItem(
  char * name )
{
  const int numItems = this->items->getLength();
  int i;
  for ( i = 0; i < numItems; i++ )
    if ( strcmp( ((ItemRecord *) (*this->items)[i])->name, name ) == 0 )
      return ((ItemRecord *) (*this->items)[i])->itemid;
  return -1;
} // GetMenuItem()

/*!
*/

void
SoQtPopupMenu::SetMenuItemTitle(
  int itemid,
  char * title )
{
  ItemRecord * rec = this->getItemRecord( itemid );
  if ( rec == NULL )
    return;
  delete [] rec->title;
  rec->title = strcpy( new char [strlen(title)+1], title );
#if QT_VERSION >= 200
  if ( rec->parent )
    rec->parent->changeItem( rec->itemid, QString( rec->title ) );
#else // Qt version < 2.0.0
  // This QMenuData::changeItem() method is being obsoleted from Qt
  // from version 2.0.0 onwards.
  if ( rec->parent )
    rec->parent->changeItem( rec->title, rec->itemid );
#endif // Qt version < 2.0.0
} // SetMenuItemTitle()

/*!
*/

char *
SoQtPopupMenu::GetMenuItemTitle(
  int itemid )
{
  ItemRecord * rec = this->getItemRecord( itemid );
  if ( rec == NULL ) return NULL;
  return rec->title;
} // GetMenuItemTitle()

/*!
*/

void
SoQtPopupMenu::SetMenuItemEnabled(
  int itemid,
  SbBool enabled )
{
  ItemRecord * rec = this->getItemRecord( itemid );
  if ( rec == NULL )
    return;
  rec->parent->setItemEnabled( rec->itemid, enabled ? true : false );
} // SetMenuItemEnabled()

/*!
*/

SbBool
SoQtPopupMenu::GetMenuItemEnabled(
  int itemid )
{
  ItemRecord * rec = this->getItemRecord( itemid );
  if ( rec == NULL )
    return FALSE;
  return rec->parent->isItemEnabled( rec->itemid ) ? TRUE : FALSE;
} // GetMenuItemEnabled()

/*!
*/

void
SoQtPopupMenu::SetMenuItemMarked(
  int itemid,
  SbBool marked )
{
  ItemRecord * rec = this->getItemRecord( itemid );
  if ( rec == NULL )
    return;
  if ( marked )
    rec->flags |= ITEM_MARKED;
  else
    rec->flags &= ~ITEM_MARKED;
  if ( rec->parent == NULL )
    return;
  rec->parent->setItemChecked( rec->itemid, marked ? true : false );
  if ( marked )
    this->SetRadioGroupMarkedItem( itemid );
} // SetMenuItemMarked()

/*!
*/

SbBool
SoQtPopupMenu::GetMenuItemMarked(
  int itemid )
{
  ItemRecord * rec = this->getItemRecord( itemid );
  if ( rec == NULL )
    return FALSE;
  if ( rec->parent == NULL )
    return (rec->flags & ITEM_MARKED) ? TRUE : FALSE;
  return rec->parent->isItemChecked( rec->itemid ) ? TRUE : FALSE;
} // GetMenuItemMarked()

// *************************************************************************

/*!
*/

void
SoQtPopupMenu::AddMenu(
  int menuid,
  int submenuid,
  int pos )
{
  MenuRecord * super = this->getMenuRecord( menuid );
  MenuRecord * sub = this->getMenuRecord( submenuid );
  if ( super == NULL || sub == NULL ) {
#if SOQT_DEBUG
    SoDebugError::postInfo( "SoQtPopupMenu::AddMenu",
      "no such menu (super = 0x%08x, sub = 0x%08x)", super, sub );
#endif // SOQT_DEBUG
    return;
  }
  if ( pos == -1 )
    super->menu->insertItem( QString( sub->title ), sub->menu, sub->menuid );
  else
    super->menu->insertItem( QString( sub->title ),
                             sub->menu, sub->menuid, pos );
  sub->parent = super->menu;
} // AddMenu()

/*!
*/

void
SoQtPopupMenu::AddMenuItem(
  int menuid,
  int itemid,
  int pos )
{
  MenuRecord * menu = this->getMenuRecord( menuid );
  ItemRecord * item = this->getItemRecord( itemid );
  if ( menu == NULL || item == NULL ) {
#if SOQT_DEBUG
    SoDebugError::postInfo( "SoQtPopupMenu::AddMenuItem",
      "no such item (menu = 0x%08x, item = 0x%08x)", menu, item );
#endif // SOQT_DEBUG
    return;
  }
  if ( pos == -1 )
    menu->menu->insertItem( QString( item->title ), item->itemid );
  else
    menu->menu->insertItem( QString( item->title ), item->itemid, pos );
  item->parent = menu->menu;
  if ( item->flags & ITEM_MARKED )
    item->parent->setItemChecked( item->itemid, true );
} // AddMenuItem()

void
SoQtPopupMenu::AddSeparator(
  int menuid,
  int pos )
{
  MenuRecord * menu = this->getMenuRecord( menuid );
  if ( menu == NULL ) {
    SoDebugError::postWarning( "SoQtPopupMenu::AddSeparator",
      "no such menu (%d)", menuid );
    return;
  }
  ItemRecord * rec = createItemRecord( "separator" );
  menu->menu->insertSeparator( pos );
  rec->flags |= ITEM_SEPARATOR;
  this->items->append( rec );
} // AddSeparator()

/*!
  This method removes the submenu with the given \a menuid.

  A removed menu can be attached again later - its menuid will still be
  allocated.
*/

void
SoQtPopupMenu::RemoveMenu(
  int menuid )
{
  MenuRecord * rec = this->getMenuRecord( menuid );
  if ( rec == NULL ) {
#if SOQT_DEBUG
    SoDebugError::postInfo( "SoQtPopupMenu::RemoveMenu", "no such menu" );
#endif // SOQT_DEBUG
    return;
  }
  if ( rec->menuid == 0 ) {
#if SOQT_DEBUG
    SoDebugError::postInfo( "SoQtPopupMenu::RemoveMenu", "can't remove root" );
#endif // SOQT_DEBUG
    return;
  }
  if ( rec->parent == NULL ) {
#if SOQT_DEBUG
    SoDebugError::postInfo( "SoQtPopupMenu::RemoveMenu", "menu not attached" );
#endif // SOQT_DEBUG
    return;
  }
  rec->parent->removeItem( rec->menuid );
  rec->parent = NULL;
} // RemoveMenu()

/*!
  This method removes the menu item with the given \a itemid.

  A removed menu item can be attached again later - its itemid will still
  be allocated.
*/

void
SoQtPopupMenu::RemoveMenuItem(
  int itemid )
{
  ItemRecord * rec = this->getItemRecord( itemid );
  if ( rec == NULL ) {
#if SOQT_DEBUG
    SoDebugError::postInfo( "SoQtPopupMenu::RemoveMenu", "no such item" );
#endif // SOQT_DEBUG
    return;
  }
  if ( rec->parent == NULL ) {
#if SOQT_DEBUG
    SoDebugError::postInfo( "SoQtPopupMenu::RemoveMenu", "item not attached" );
#endif // SOQT_DEBUG
    return;
  }
  rec->parent->removeItem( rec->itemid );
  rec->parent = NULL;
} // RemoveMenuItem()

// *************************************************************************

/*!
  This method invokes the popup menu.

  If -1 is returned, no menu item was selected.  The itemid of the selected
  item is returned otherwise.
*/

void
SoQtPopupMenu::PopUp(
  QWidget * inside,
  int x,
  int y )
{
  MenuRecord * rec = this->getMenuRecord( 0 );
  rec->menu->popup( QPoint( x, y ) );
} // PopUp()

// *************************************************************************

/*!
*/

MenuRecord *
SoQtPopupMenu::getMenuRecord(
  int menuid )
{
  const int numMenus = this->menus->getLength();
  int i;
  for ( i = 0; i < numMenus; i++ )
    if ( ((MenuRecord *) (*this->menus)[i])->menuid == menuid )
      return (MenuRecord *) (*this->menus)[i];
  return (MenuRecord *) NULL;
} // getMenuRecord()

/*!
*/

ItemRecord *
SoQtPopupMenu::getItemRecord(
  int itemid )
{
  const int numItems = this->items->getLength();
  int i;
  for ( i = 0; i < numItems; i++ )
    if ( ((ItemRecord *) (*this->items)[i])->itemid == itemid )
      return (ItemRecord *) (*this->items)[i];
  return (ItemRecord *) NULL;
} // getItemRecord()

// *************************************************************************

/*!
*/

MenuRecord *
SoQtPopupMenu::createMenuRecord(
  char * name )
{
  MenuRecord * rec = new MenuRecord;
  rec->menuid = -1;
  rec->name = strcpy( new char [strlen(name)+1], name );
  rec->title = strcpy( new char [strlen(name)+1], name );
  rec->menu = new QPopupMenu( (QWidget *) NULL, name );
  QObject::connect( rec->menu, SIGNAL(activated(int)),
                    this, SLOT(itemActivation(int)) );
  rec->parent = NULL;
  return rec;
} // create()

/*!
*/

ItemRecord *
SoQtPopupMenu::createItemRecord(
  char * name )
{
  ItemRecord * rec = new ItemRecord;
  rec->itemid = -1;
  rec->flags = 0;
  rec->name = strcpy( new char [strlen(name)+1], name );
  rec->title = strcpy( new char [strlen(name)+1], name );
  rec->parent = NULL;
  return rec;
} // create()

// *************************************************************************

void
SoQtPopupMenu::itemActivation( // private slot
  int itemid )
{
  inherited::InvokeMenuSelection( itemid );
} // menuSelection()

// *************************************************************************
