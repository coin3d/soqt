/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

// src/Inventor/Qt/widgets/SoQtPopupMenu.cpp.  Generated from SoGuiPopupMenu.cpp.in by configure.

/*!
  \class SoQtPopupMenu Inventor/Qt/widgets/SoQtPopupMenu.h
  \brief The SoQtPopupMenu class implements a common interface for popup
  menu management for all the Coin GUI toolkit libraries.

  The point of this class is to enable client code to be exactly the
  same for all GUI libraries, even without being template-based.
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <assert.h>

#include <Inventor/SoLists.h>
#include <Inventor/errors/SoDebugError.h>

#include <soqtdefs.h>
#include <Inventor/Qt/widgets/SoQtPopupMenu.h>
#include <Inventor/Qt/widgets/QtNativePopupMenu.h>
#include <Inventor/Qt/common/SbGuiList.h>

// *************************************************************************

// Documentation for abstract methods.

/*!
  \fn void SoQtPopupMenu::popUp(QWidget * inside, int x, int y)

  Invokes this popup menu instance.

  The coordinates for the popup will be used relative to the origo of
  the widget argument.
*/

// *************************************************************************

// The private data for the SoQtPopupMenu.

class SoQtPopupMenuP {
public:
  SbGuiList<int> menuitems;
  SbGuiList<int> radiogroups;
  SbPList * callbacks;
  SbPList * userdata;
};


#define PRIVATE(o) (o->pimpl)

// *************************************************************************

/*!
  Instantiation method.

  SoQtPopupMenu is implemented with this "factory" method instead of
  a public constructor to provide a completely generic interface on
  top of the toolkit's native popup menu implementation.
*/
SoQtPopupMenu *
SoQtPopupMenu::createInstance(void)
{
  return new QtNativePopupMenu();
}


/*!
  The class constructor is protected, as SoQtPopupMenu uses a factory
  instantiation method.
*/
SoQtPopupMenu::SoQtPopupMenu(void)
{
  PRIVATE(this) = new SoQtPopupMenuP;

  PRIVATE(this)->callbacks = NULL;
  PRIVATE(this)->userdata = NULL;
} // SoQtPopupMenu()

/*!
  Destructor.
*/
SoQtPopupMenu::~SoQtPopupMenu()
{
  delete PRIVATE(this)->callbacks;
  delete PRIVATE(this)->userdata;
} // ~SoQtPopupMenu()

// *************************************************************************

void
SoQtPopupMenu::setMenuItemMarked(int itemid, SbBool marked)
{
  // forward to native implementation
  this->_setMenuItemMarked(itemid, marked);

  if (marked) {
    const int radiogroupid = this->getRadioGroup(itemid);
    if (radiogroupid != -1) {
      this->setRadioGroupMarkedItem(itemid);
    }
  }
}

// *************************************************************************

/*!
*/

int
SoQtPopupMenu::newRadioGroup(
  int groupid)
{
  const int numGroupedItems = PRIVATE(this)->radiogroups.getLength();
  int id = groupid;
  if (id != -1) {
    SbBool hit = FALSE;
    int i;
    for (i = 0; i < numGroupedItems && hit == FALSE; i++) {
      if (PRIVATE(this)->radiogroups[i] == id)
        hit = TRUE;
    }
    if (hit == TRUE) {
#if SOQT_DEBUG
      SoDebugError::postInfo("SoQtPopupMenu::NewRadioGroup",
        "requested group id already taken");
#endif // SOQT_DEBUG
      return -1; 
    }
  } else {
    id = 0;
    SbBool found;
    do {
      id++;
      found = FALSE;
      int i;
      for (i = 0; i < numGroupedItems && found == FALSE; i++) {
        if (PRIVATE(this)->radiogroups[i] == id)
          found = TRUE;
      }
    } while (found == TRUE);
  }
  // id is OK here
  PRIVATE(this)->menuitems.append(-1); // fake menu item
  PRIVATE(this)->radiogroups.append(id); // register id in array
  return id;
} // newRadioGroup()

/*!
*/

int
SoQtPopupMenu::getRadioGroup(
  int itemid)
{
  assert(itemid != -1);
  const int numGroupedItems = PRIVATE(this)->radiogroups.getLength();
  int i;
  for (i = 0; i < numGroupedItems; i++) {
    if (PRIVATE(this)->menuitems[i] == itemid)
      return PRIVATE(this)->radiogroups[i];
  }
  return -1;
} // getRadioGroup()

/*!
*/

int
SoQtPopupMenu::getRadioGroupSize(
  int groupid)
{
  int count = 0;
  const int numItems = PRIVATE(this)->radiogroups.getLength();
  int i;
  for (i = 0; i < numItems; i++) {
    if (PRIVATE(this)->radiogroups[i] == groupid &&
         PRIVATE(this)->menuitems[i] != -1)
      count++;
  }
  return count;
} // getRadioGroupSize()

/*!
*/

void
SoQtPopupMenu::addRadioGroupItem(
  int groupid,
  int itemid)
{
  PRIVATE(this)->menuitems.append(itemid);
  PRIVATE(this)->radiogroups.append(groupid);
} // addRadioGroupItem()

/*!
*/

void
SoQtPopupMenu::removeRadioGroupItem(
  int itemid)
{
  assert(itemid != -1);
  const int numGroupedItems = PRIVATE(this)->menuitems.getLength();
  int i;
  for (i = 0; i < numGroupedItems; i++) {
    if (PRIVATE(this)->menuitems[i] == itemid) {
      PRIVATE(this)->menuitems.remove(i);
      PRIVATE(this)->radiogroups.remove(i);
      return;
    }
  }
} // removeRadioGroupItem()

// *************************************************************************

void
SoQtPopupMenu::setRadioGroupMarkedItem(int itemid)
{
  const int idx = PRIVATE(this)->menuitems.find(itemid);
  assert(idx != -1);
  const int groupid = PRIVATE(this)->radiogroups[idx];

  if (groupid == -1) {
    SoDebugError::post("SoQtPopupMenu::setRadioGroupMarkedItem",
                       "item not in a radio group");
    return;
  }

  const int numItems = PRIVATE(this)->menuitems.getLength();
  for (int i = 0; i < numItems; i++) {
    if (i == idx) { continue; }
    if (PRIVATE(this)->radiogroups[i] == groupid) {
      const int item = PRIVATE(this)->menuitems[i];
      if (item != -1) { // FIXME: should this be an assert? 20050622 mortene.
        if ( this->getMenuItemMarked(item) ) {
          this->setMenuItemMarked(item, FALSE);
        }
      }
    }
  }
}

int
SoQtPopupMenu::getRadioGroupMarkedItem(int groupid)
{
  const int numItems = PRIVATE(this)->menuitems.getLength();
  int i;
  for (i = 0; i < numItems; i++) {
    if (PRIVATE(this)->radiogroups[i] == groupid) {
      int item = PRIVATE(this)->menuitems[i];
      if (item != -1 && this->getMenuItemMarked(item))
        return item;
    }
  }
  return -1;
}

// *************************************************************************

/*!
*/

void
SoQtPopupMenu::addMenuSelectionCallback(
  SoQtMenuSelectionCallback * callback,
  void * user)
{
  if (PRIVATE(this)->callbacks == NULL) {
    PRIVATE(this)->callbacks = new SbPList;
    PRIVATE(this)->userdata = new SbPList;
  }
  PRIVATE(this)->callbacks->append((void *) callback);
  PRIVATE(this)->userdata->append(user);
} // addMenuSelectionCallback()

/*!
*/

void
SoQtPopupMenu::removeMenuSelectionCallback(
  SoQtMenuSelectionCallback * callback,
  void * user)
{
  if (PRIVATE(this)->callbacks == NULL) {
#if SOQT_DEBUG
    SoDebugError::postInfo("SoQtPopupMenu::RemoveMenuSelectionCallback",
      "no callbacks at all");
#endif // SOQT_DEBUG
    return;
  }
  int numCallbacks = PRIVATE(this)->callbacks->getLength();
  int i;
  for (i = 0; i < numCallbacks; i++) {
    if ((*PRIVATE(this)->callbacks)[i] == (void *) callback &&
         (*PRIVATE(this)->userdata)[i] == user) {
      PRIVATE(this)->callbacks->remove(i);
      PRIVATE(this)->userdata->remove(i);
      i--;
      numCallbacks--;
    }
  }
} // removeMenuSelectionCallback()

/*!
*/

void
SoQtPopupMenu::invokeMenuSelection(
  int itemid)
{
  if (PRIVATE(this)->callbacks == NULL)
    return;
  const int numCallbacks = PRIVATE(this)->callbacks->getLength();
  int i;
  for (i = 0; i < numCallbacks; i++) {
    SoQtMenuSelectionCallback * cb = (SoQtMenuSelectionCallback *)
      (*PRIVATE(this)->callbacks)[i];
    (*cb)(itemid, (*PRIVATE(this)->userdata)[i]);
  }
} // invokeMenuSelection()

// *************************************************************************

