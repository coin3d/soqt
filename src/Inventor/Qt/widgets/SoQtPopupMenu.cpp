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

#include <Inventor/Qt/widgets/SoQtPopupMenu.h>

// *************************************************************************

struct MenuRecord {
  static MenuRecord * create( char * name );
  int menuid;
  char * name;
  char * title;
  QPopupMenu * menu;
  QPopupMenu * parent;
}; // struct MenuRecord

struct ItemRecord {
  static ItemRecord * create( char * name );
  int itemid;
  char * name;
  char * title;
  QPopupMenu * parent;
}; // struct ItemRecord

// *************************************************************************

SoQtPopupMenu::SoQtPopupMenu(
  SoAnyPopupMenu * handler )
{
  this->handler = handler;
  this->menus = new SbPList;
  this->items = new SbPList;
} // SoQtPopupMenu()

/*!
*/

SoQtPopupMenu::~SoQtPopupMenu(
  void )
{
  const int numMenus = this->menus->getLength();
  QPopupMenu * popup = NULL;
  for ( int i = 0; i < numMenus; i++ ) {
    MenuRecord * rec = (MenuRecord *) (*this->menus)[i];
    if ( rec->menuid == 0 ) popup = rec->menu;
    delete [] rec->name;
    delete [] rec->title;
    delete rec;
   }

  const int numItems = this->items->getLength();
  for ( int i = 0; i < numItems; i++ ) {
    MenuRecord * rec = (MenuRecord *) (*this->menus)[i];
    if ( rec->menuid == 0 ) delete rec->menu; // delete root popup menu
    delete [] rec->name;
    delete [] rec->title;
    delete rec;
  }

  // delete root popup menu
  delete popup;
} // ~SoQtPopupMenu()

// *************************************************************************

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
  MenuRecord * rec = MenuRecord::create( name );
  rec->menuid = id;
  this->menus->append( (void *) rec );
  return id;
} // NewMenu()

int
SoQtPopupMenu::GetMenu(
  char * name )
{
  const int numMenus = this->menus->getLength();
  for ( int i = 0; i < numMenus; i++ )
    if ( strcmp( ((MenuRecord *) (*this->menus)[i])->name, name ) == 0 )
      return ((MenuRecord *) (*this->menus)[i])->menuid;
  return -1;
} // GetMenu()

void
SoQtPopupMenu::SetMenuTitle(
  int menuid,
  char * title )
{
  MenuRecord * rec = this->getMenuRecord( menuid );
  if ( rec != NULL ) {
    delete [] rec->title;
    rec->title = strcpy( new char [strlen(title)+1], title );
//    rec->menu->SetTitle( title );
  }
} // SetMenuTitle()

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
  ItemRecord * rec = ItemRecord::create( name );
  rec->itemid = id;
  this->items->append( rec );
  return id;
} // NewMenuItem()

int
SoQtPopupMenu::GetMenuItem(
  char * name )
{
  const int numItems = this->items->getLength();
  for ( int i = 0; i < numItems; i++ )
    if ( strcmp( ((ItemRecord *) (*this->items)[i])->name, name ) == 0 )
      return ((ItemRecord *) (*this->items)[i])->itemid;
  return -1;
} // GetMenuItem()

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
//  rec->item->SetLabel( title );
} // SetMenuItemTitle()

char *
SoQtPopupMenu::GetMenuItemTitle(
  int itemid )
{
  ItemRecord * rec = this->getItemRecord( itemid );
  if ( rec == NULL ) return NULL;
  return rec->title;
} // GetMenuItemTitle()

void
SoQtPopupMenu::SetMenuItemEnabled(
  int itemid,
  SbBool enabled )
{
  ItemRecord * rec = this->getItemRecord( itemid );
  if ( rec == NULL )
    return;
//  rec->item->SetEnabled( enabled );
} // SetMenuItemEnabled()

SbBool
SoQtPopupMenu::GetMenuItemEnabled(
  int itemid )
{
  ItemRecord * rec = this->getItemRecord( itemid );
  if ( rec == NULL )
    return FALSE;
//  if ( rec->item->IsEnabled() ) return TRUE;
  return FALSE;
} // GetMenuItemEnabled()

void
SoQtPopupMenu::SetMenuItemMarked(
  int itemid,
  SbBool marked )
{
  ItemRecord * rec = this->getItemRecord( itemid );
  if ( rec == NULL )
    return;
//  rec->item->SetMarked( marked );
} // SetMenuItemMarked()

SbBool
SoQtPopupMenu::GetMenuItemMarked(
  int itemid )
{
  ItemRecord * rec = this->getItemRecord( itemid );
  if ( rec == NULL )
    return FALSE;
//  if ( rec->item->IsMarked() ) return TRUE;
  return FALSE;
} // GetMenuItemMarked()

// *************************************************************************

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
//  if ( pos == -1 )
//    super->menu->AddItem( sub->menu );
//  else
//    super->menu->AddItem( sub->menu, pos );
  sub->parent = super->menu;
} // AddMenu()

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
//  if ( pos == -1 )
//    menu->menu->AddItem( item->item );
//  else
//    menu->menu->AddItem( item->item, pos );
  item->parent = menu->menu;
} // AddMenuItem()

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
//  rec->parent->RemoveItem( rec->menu );
  rec->parent = NULL;
} // RemoveMenu()

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
//  rec->parent->RemoveItem( rec->item );
  rec->parent = NULL;
} // RemoveMenuItem()

// *************************************************************************

int
SoQtPopupMenu::PopUp(
  int screenx,
  int screeny )
{
  MenuRecord * rec = this->getMenuRecord( 0 );
  int item = rec->menu->exec( QPoint( screenx, screeny ) );
//  if ( item != NULL ) {
//    const int numItems = this->items.getLength();
//    for ( int i = 0; i < numItems; i++ ) {
//      if ( this->items[i]->item == item )
//        return this->items[i]->itemid;
//    }
//  }
  return 0;
} // PopUp()

// *************************************************************************

MenuRecord *
SoQtPopupMenu::getMenuRecord(
  int menuid )
{
  const int numMenus = this->menus->getLength();
  for ( int i = 0; i < numMenus; i++ )
    if ( ((MenuRecord *) (*this->menus)[i])->menuid == menuid )
      return (MenuRecord *) (*this->menus)[i];
  return (MenuRecord *) NULL;
} // getMenuRecord()

ItemRecord *
SoQtPopupMenu::getItemRecord(
  int itemid )
{
  const int numItems = this->items->getLength();
  for ( int i = 0; i < numItems; i++ )
    if ( ((ItemRecord *) (*this->items)[i])->itemid == itemid )
      return (ItemRecord *) (*this->items)[i];
  return (ItemRecord *) NULL;
} // getItemRecord()

// *************************************************************************

MenuRecord *
MenuRecord::create(
  char * name )
{
  MenuRecord * rec = new MenuRecord;
  rec->menuid = -1;
  rec->name = strcpy( new char [strlen(name)+1], name );
  rec->title = strcpy( new char [strlen(name)+1], name );
//  rec->menu = new QPopupMenu( name );
  rec->parent = NULL;
  return rec;
} // create()

ItemRecord *
ItemRecord::create(
  char * name )
{
  ItemRecord * rec = new ItemRecord;
  rec->itemid = -1;
  rec->name = strcpy( new char [strlen(name)+1], name );
  rec->title = strcpy( new char [strlen(name)+1], name );
  rec->parent = NULL;
  return rec;
} // create()

// *************************************************************************
