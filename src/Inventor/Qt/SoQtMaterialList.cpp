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

#include <qmetaobject.h>
#include <Inventor/Qt/moc_SoQtMaterialList.icc>

#include <stdlib.h>

#include <Inventor/SbPList.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/SoDB.h>
#include <Inventor/SoInput.h>
#include <Inventor/nodes/SoMaterial.h>

#include <soqtdefs.h>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoAnyMaterialList.h>

#include <Inventor/Qt/SoQtMaterialList.h>

// *************************************************************************

/*!
  \class SoQtMaterialList Inventor/Qt/SoQtMaterialList.h
  \brief The SoQtMaterialList class is a component for adding material
  selection to scene graph editors.
*/

// *************************************************************************

SOQT_OBJECT_SOURCE(SoQtMaterialList);

// *************************************************************************

/*!
  Public constructor.
*/

SoQtMaterialList::SoQtMaterialList(
  QWidget * parent,
  const char * const name,
  SbBool embed,
  const char * const dir)
: inherited(parent, name, embed)
{
  this->constructor(dir, TRUE);
} // SoQtMaterialList()

/*!
  Protected constructor.
*/

SoQtMaterialList::SoQtMaterialList(// protected
  QWidget * parent,
  const char * const name,
  SbBool embed,
  const char * const dir,
  SbBool build)
: inherited(parent, name, embed)
{
  this->constructor(dir, build);
} // SoQtMaterialList()

/*!
  Common constructor code.
*/

void
SoQtMaterialList::constructor(// private
  const char * const dir,
  const SbBool build)
{
  this->common = new SoAnyMaterialList(dir);
  this->setSize(SbVec2s(200, 300));

  if (build) {
    this->setClassName("SoQtMaterialList");
    QWidget * materials = this->buildWidget(this->getParentWidget());
    this->setBaseWidget(materials);
  }
} // constructor()

/*!
  Destructor.
*/

SoQtMaterialList::~SoQtMaterialList(
  void)
{
  delete this->common;
} // ~SoQtMaterialList()

// *************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtMaterialList::addCallback(
  SoQtMaterialListCB * const callback,
  void * const closure)
{
  common->addCallback(callback, closure);
} // addCallback()

/*!
  FIXME: write doc
*/

void
SoQtMaterialList::removeCallback(
  SoQtMaterialListCB * const callback,
  void * const closure)
{
  common->removeCallback(callback, closure);
} // removeCallback()

// *************************************************************************

/*!
  FIXME: write doc
*/

const char *
SoQtMaterialList::getDefaultWidgetName(// virtual, protected
  void) const
{
  static const char defaultWidgetName[] = "SoQtMaterialList";
  return defaultWidgetName;
} // getDefaultWidgetName()

/*!
  FIXME: write doc
*/

const char *
SoQtMaterialList::getDefaultTitle(// virtual, protected
  void) const
{
  static const char defaultTitle[] = "Material List";
  return defaultTitle;
} // getDefaultTitle()

/*!
  FIXME: write doc
*/

const char *
SoQtMaterialList::getDefaultIconTitle(// virtual, protected
  void) const
{
  static const char defaultIconTitle[] = "Material List";
  return defaultIconTitle;
} // getDefaultIconTitle()

// *************************************************************************

/*!
  FIXME: write doc
*/

QWidget *
SoQtMaterialList::buildWidget(// protected
  QWidget * parent)
{
/*
  // we're building pulldown menu automatically...
  QWidget * root = XtVaCreateManagedWidget(this->getClassName(),
    xmFormWidgetClass, parent,
    NULL);

  QWidget * menubar = XtVaCreateManagedWidget("menubar",
    xmRowColumnWidgetClass, root,
    XmNleftAttachment, XmATTACH_FORM,
    XmNtopAttachment, XmATTACH_FORM,
    XmNrightAttachment, XmATTACH_FORM,
    XmNrowColumnType, XmMENU_BAR,
    NULL);

  QWidget * palettemenu = this->buildPulldownMenu(menubar);

  SoQtMaterialDirectory * dir = common->getMaterialDirectory();

  int group, materials;
  XmStringTable list;
  if (dir->numGroups > 0) {
    group = dir->current;
    materials = dir->groups[group]->numMaterials;
    list = (XmStringTable) XtMalloc(sizeof(XmString) * materials);
    for (int i = 0; i < materials; i++)
      list[i] =
        SoQt::encodeString(dir->groups[group]->materials[i]->name);
  } else {
    materials = 0;
    list = NULL;
  }

  Arg argv[10];
  int argc = 0;
  XtSetArg(argv[argc], XmNleftAttachment, XmATTACH_FORM); argc++;
  XtSetArg(argv[argc], XmNtopAttachment, XmATTACH_WIDGET); argc++;
  XtSetArg(argv[argc], XmNtopWidget, menubar); argc++;
  XtSetArg(argv[argc], XmNrightAttachment, XmATTACH_FORM); argc++;
  XtSetArg(argv[argc], XmNbottomAttachment, XmATTACH_FORM); argc++;
  XtSetArg(argv[argc], XmNselectionPolicy, XmSINGLE_SELECT); argc++;
  XtSetArg(argv[argc], XmNscrollBarDisplayPolicy, XmSTATIC); argc++;
  XtSetArg(argv[argc], XmNitems, list); argc++;
  XtSetArg(argv[argc], XmNitemCount, materials); argc++;

  this->listwidget = XmCreateScrolledList(root, "materials", argv, argc);
  XtManageChild(this->listwidget);
  XtAddCallback(this->listwidget, XmNdefaultActionCallback,
    SoQtMaterialList::selection_cb, (void *) this);
  for (int i = 0; i < materials; i++)
    XmStringFree(list[i]);
  XtFree((char *) list);
  return root;
*/
  return NULL;
} // buildWidget()

// *************************************************************************

/*!
  \internal
  FIXME: write doc
*/

void
SoQtMaterialList::selectionCallback(// private
  int materialid)
{
  materialid--; // get index
  SoQtMaterialDirectory * data = common->getMaterialDirectory();

  assert(materialid >= 0 &&
          materialid < data->groups[data->current]->numMaterials);
  const char * materialdata =
    data->groups[data->current]->materials[materialid]->data;

  SoInput reader;
  if (data->flags & SOQT_BUILTIN_MATERIALS) {
    reader.setBuffer((void *) materialdata, strlen(materialdata));
  } else {
    if (! reader.openFile(materialdata, FALSE)) {
      SoDebugError::postWarning("SoQtMaterialList::selectionCallback",
        "could not open file: \"%s\"", materialdata);
      return;
    }
  }

  SoNode * material = NULL;
  if (! SoDB::read(&reader, material)) {
    SoDebugError::postWarning("SoQtMaterialList::selectionCallback",
      "failed to read material");
    return;
  }
  if (! material) {
    SoDebugError::postWarning("SoQtMaterialList::selectionCallback",
      "read returned no data");
    return;
  }
  material->ref();
  if (! material->isOfType(SoMaterial::getClassTypeId())) {
    SoDebugError::postWarning("SoQtMaterialList::selectionCallback",
      "not a material node!");
    material->unref();
    return;
  }
  common->invokeCallbacks((SoMaterial *) material);
  material->unref();
} // selectionCallback()

/*!
  \internal
  FIXME: write doc
*/

void
SoQtMaterialList::selection_cb(// static, private
  QWidget *,
  void * closure,
  void * call_data)
{
/*
  SoQtMaterialList * component = (SoQtMaterialList *) closure;
  XmListCallbackStruct * data = (XmListCallbackStruct *) call_data;
  component->selectionCallback(data->item_position);
*/
} // selection_cb()

// *************************************************************************

/*!
  \internal
  FIXME: write doc
*/

void
SoQtMaterialList::paletteMenuCallback(// private
  QWidget * menuitem)
{
/*
  SoQtMaterialDirectory * data = common->getMaterialDirectory();
  int i, j;
  for (i = 0; i < data->numGroups; i++) {
    if (data->groups[i]->menuitem == menuitem) {
      XmStringTable list = (XmStringTable) XtMalloc(sizeof(XmString) *
        data->groups[i]->numMaterials);
      for (j = 0; j < data->groups[i]->numMaterials; j++)
        list[j] = SoQt::encodeString(data->groups[i]->materials[j]->name);
      XtVaSetValues(this->listwidget,
        XmNitemCount, data->groups[i]->numMaterials,
        XmNitems, list,
        NULL);
      for (j = 0; j < data->groups[i]->numMaterials; j++)
        XmStringFree(list[j]);
      XtFree((char *) list);
      data->current = i;
      return;
    }
  }
*/
} // paletteMenuCallback()

/*!
  \internal
  FIXME: write doc
*/

void
SoQtMaterialList::palette_menu_cb(// static, private
  QWidget * widget,
  void * closure,
  void *)
{
  assert(closure != NULL);
  SoQtMaterialList * component = (SoQtMaterialList *) closure;
  component->paletteMenuCallback(widget);
} /* palette_menu_cb */

// *************************************************************************

/*!
  This method builds the pulldown menu.
  The current implementation demands that the \a parent argument should be
  the menubar RowColumn widget - only the "Palettes" menubar button and the
  pulldown menu is built by this method.
*/

QWidget *
SoQtMaterialList::buildPulldownMenu(// protected
  QWidget * parent)
{
/*
  QWidget * palettes = XtVaCreateManagedWidget("palettes",
    xmCascadeButtonGadgetClass, parent,
    XtVaTypedArg,
      XmNlabelString, XmRString,
      "Palettes", sizeof("Palettes") + 1,
    NULL);

  QWidget * shell = SoQt::getShellWidget(parent);
  assert(shell != (Widget) NULL);

  Visual * visual;
  Colormap colormap;
  int depth;

  XtVaGetValues(shell,
    XmNvisual, &visual,
    XmNcolormap, &colormap,
    XmNdepth, &depth,
    NULL);

  QWidget * menu =
    XmVaCreateSimplePulldownMenu(parent, "materialsmenu", 0, NULL, NULL);

  SoQtMaterialDirectory * data = common->getMaterialDirectory();
  for (int i = 0; i < data->numGroups; i++) {
    QWidget * item;
    item = XtVaCreateManagedWidget(data->groups[i]->name,
             xmPushButtonGadgetClass, menu,
             XtVaTypedArg,
               XmNlabelString, XmRString,
               data->groups[i]->name, strlen(data->groups[i]->name) + 1,
             NULL);
    data->groups[i]->menuitem = item;
    XtAddCallback(item, XmNactivateCallback,
      SoQtMaterialList::palette_menu_cb, (void *) this);
  }

  return palettes;
*/
  return NULL;
} // buildPulldownMenu()

// *************************************************************************
