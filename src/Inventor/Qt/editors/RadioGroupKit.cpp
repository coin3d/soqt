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

/*!
  \class RadioGroupKit RadioGroupKit.h
  \brief The RadioGroupKit class is a radiobutton group.

  This is a 3D user interface component.

  Example usage:

  \code
  #include <Inventor/Qt/SoQt.h>
  #include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
  #include <Inventor/nodes/SoSeparator.h>
  #include "RadioGroupKit.h"

  int
  main(int argc, char ** argv)
  {
    QWidget * mainwin = SoQt::init(argc, argv, argv[0]);
    RadioGroupKit::initClass();

    SoSeparator * root = new SoSeparator;
    root->ref();

    RadioGroupKit * radiogroup = new RadioGroupKit;
    radiogroup->labels.set1Value(0,"Item #1");
    radiogroup->labels.set1Value(1,"Item #2");
    radiogroup->labels.set1Value(2,"Item #3");
    root->addChild(radiogroup);

    //
    // Here you can add a sensor callback to the 'selected' field in the RadioGroupKit
    // Ex:
    //
    //   SoFieldSensor * radioGroupSensor = new SoFieldSensor(myRadioButtonCallback,this);
    //   radioGroupSensor->attach(&radiogroup->selected);
    //

    SoQtExaminerViewer * viewer = new SoQtExaminerViewer(mainwin);
    viewer->setSceneGraph(root);
    viewer->show();

    SoQt::show(mainwin);
    SoQt::mainLoop();

    delete viewer;
    root->unref();

    return 0;
  }
  \endcode
*/

#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransformSeparator.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoText2.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoSelection.h>
#include <Inventor/nodes/SoShapeHints.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoFont.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/events/SoEvent.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/nodes/SoTransformation.h>
#include <Inventor/lists/SbPList.h>
#include <Inventor/nodekits/SoShapeKit.h>
#include <Inventor/nodes/SoMarkerSet.h>

#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/errors/SoDebugError.h>

#include "RadioGroupKit.h"

SO_KIT_SOURCE(RadioGroupKit);

#define RADIO_BUTTON_SIZE .2

typedef struct {
  class RadioGroupKitP * thisClass;
  SoSeparator * buttonroot;
} paramPackage;

static const char RADIOBULLET_radiobulletgeometry[] =
"#Inventor V2.1 ascii\n"
"\n"
"DEF RadioButtons Separator {\n"
"\n"
" DEF BulletColorActive BaseColor { rgb 0 1 1 }\n"
" DEF BulletColor BaseColor { rgb 1 1 1 }\n"
"\n"
" DEF RadioBulletActive TransformSeparator {\n"
"   USE BulletColorActive\n"
"   Cube { width 0.2 height 0.2 depth 0.2 }\n"
" }\n"
" \n"
" DEF RadioBullet TransformSeparator {\n"
"   USE BulletColor\n"
"   Cube { width 0.2 height 0.2 depth 0.2 }\n"
" }\n"
"}\n"
"\n";


class RadioGroupKitP {
public:
  RadioGroupKitP(RadioGroupKit * master) {
    this->master = master;
  }

  RadioGroupKit * master;
  int buttonCounter;
  SbPList *buttonList;
  SoSeparator *root;
  SoFieldSensor * labelSensor;

  void addRadioButton(SbString label);
  static void buttonClickedCallback(void *userData, SoPath *node);
  static void radioButtonAdded(void *classObject, SoSensor *sensor);

};

#define PRIVATE(p) (p->pimpl)
#define PUBLIC(p) (p->master)


RadioGroupKit::RadioGroupKit(void)
{
  SO_KIT_CONSTRUCTOR(RadioGroupKit);

  PRIVATE(this) = new RadioGroupKitP(this);

  if (SO_KIT_IS_FIRST_INSTANCE()) {
    SoInput input;
    input.setBuffer((void *) RADIOBULLET_radiobulletgeometry, strlen(RADIOBULLET_radiobulletgeometry));
    SoDB::readAll(&input);
  }

  SO_KIT_ADD_CATALOG_ENTRY(radioGroupRoot,SoSeparator,FALSE,this, "",TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(RadioBulletActive, SoTransformSeparator, TRUE, radioGroupRoot, , TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(RadioBullet, SoTransformSeparator, TRUE, radioGroupRoot, , TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(BulletColorActive, SoBaseColor, TRUE, radioGroupRoot, , TRUE);
  SO_KIT_ADD_CATALOG_ENTRY(BulletColor, SoBaseColor, TRUE, radioGroupRoot, , TRUE);

  SO_KIT_INIT_INSTANCE();

  this->setPartAsDefault("RadioBullet", "RadioBullet");
  this->setPartAsDefault("RadioBulletActive", "RadioBulletActive");
  this->setPartAsDefault("BulletColor", "BulletColor");
  this->setPartAsDefault("BulletColorActive", "BulletColorActive");

  PRIVATE(this)->buttonCounter = 0;
  PRIVATE(this)->buttonList = new SbPList(1);

  PRIVATE(this)->labelSensor = new SoFieldSensor(PRIVATE(this)->radioButtonAdded,PRIVATE(this));
  PRIVATE(this)->labelSensor->setPriority(0);
  PRIVATE(this)->labelSensor->attach(&labels);

  PRIVATE(this)->root = new SoSeparator;
  this->setPart("radioGroupRoot", PRIVATE(this)->root);
}

RadioGroupKit::~RadioGroupKit()
{
  delete PRIVATE(this)->labelSensor;
  delete PRIVATE(this)->buttonList;
  delete PRIVATE(this);
}

void
RadioGroupKit::initClass(void)
{
  SO_KIT_INIT_CLASS(RadioGroupKit, SoInteractionKit, "InteractionKit");
}

SbBool
RadioGroupKit::affectsState() const
{
  return(FALSE);
}

void
RadioGroupKitP::buttonClickedCallback(void * userData, SoPath * path)
{
  paramPackage * pp = (paramPackage *) userData;
  RadioGroupKitP * radioButtonsP = (RadioGroupKitP *)pp->thisClass;
  int idx = radioButtonsP->root->findChild(pp->buttonroot);
  assert(idx != -1);
  idx /= 2; // there's a subgraph for Y-spacing inbetween each button root

  SoTransformSeparator * button = (SoTransformSeparator *) radioButtonsP->buttonList->get(idx);

  for(int i=0;i<radioButtonsP->buttonList->getLength();++i){
    SoTransformSeparator *sep = (SoTransformSeparator *) radioButtonsP->buttonList->get(i);
    SoBaseColor *color = (SoBaseColor *) sep->getChild(0);
    SoBaseColor *bulletColor =  (SoBaseColor*) SO_GET_PART(PUBLIC(radioButtonsP), "BulletColor",SoBaseColor);
    color->rgb = bulletColor->rgb;
  }

  // Highlight selected button
  SoBaseColor * color = (SoBaseColor *) button->getChild(0);
  SoBaseColor * bulletColor =  (SoBaseColor*) SO_GET_PART(PUBLIC(radioButtonsP), "BulletColorActive",SoBaseColor);
  color->rgb = bulletColor->rgb;

  // Update selected field
  PUBLIC(radioButtonsP)->selected.setValue(idx);
#if 0 // debug
  SoDebugError::postInfo("RadioGroupKitP::buttonClickedCallback",
                         "selected %d", idx);
#endif // debug
}

void
RadioGroupKitP::radioButtonAdded(void * classObject, SoSensor * sensor)
{
  RadioGroupKitP * pimpl = (RadioGroupKitP *) classObject;
  SbString newlabel = PUBLIC(pimpl)->labels[pimpl->buttonCounter];
  pimpl->addRadioButton(newlabel);
  pimpl->buttonCounter++;
}

void
RadioGroupKitP::addRadioButton(SbString label)
{

  SoSeparator * buttonRoot = new SoSeparator;
  SoShapeHints * hints = new SoShapeHints;
  hints->vertexOrdering = SoShapeHints::COUNTERCLOCKWISE;
  hints->shapeType = SoShapeHints::SOLID;

  SoFont * font = new SoFont;
  font->name.setValue("Times-Roman");
  font->size.setValue(24.0);

  buttonRoot->addChild(hints);
  buttonRoot->addChild(font);


  SoText2 * buttonLabel = new SoText2;
  buttonLabel->string = label;

  SoSelection * selection = new SoSelection;

  paramPackage * pp = new paramPackage;
  pp->thisClass = this;
  pp->buttonroot = buttonRoot;
  selection->addSelectionCallback(&buttonClickedCallback, pp);
  SoTransformSeparator * sep;

  // Make first added button selected as default
  if(buttonCounter == 0){
    sep = (SoTransformSeparator*) SO_GET_PART(master, "RadioBulletActive",SoTransformSeparator)->copy();
    master->selected.setValue(0);
  } else {
    sep = (SoTransformSeparator*) SO_GET_PART(master, "RadioBullet",SoTransformSeparator)->copy();
  }

  buttonList->set(buttonCounter,sep);    // Save the separator node for later changes @ callback
  selection->addChild(sep);

  // Fetch bullet boundingbox
  SbViewportRegion dummyViewport(100,100);
  SoGetBoundingBoxAction bboxAction(dummyViewport);
  if(buttonCounter == 0)
    bboxAction.apply(sep);
  else
    bboxAction.apply((SoTransformSeparator *) buttonList->get(buttonCounter-1)); // Previous radiobutton

  SbBox3f bbox = bboxAction.getBoundingBox();
  SoTranslation *spacingX = new SoTranslation;
  SoTranslation *spacingY = new SoTranslation;
  float dx,dy,dz;
  bbox.getSize(dx,dy,dz);
  spacingX->translation.setValue(dx,-dy/2,0);
  spacingY->translation.setValue(0,-dy*2,0);


  selection->addChild(spacingX);
  selection->addChild(buttonLabel);
  buttonRoot->addChild(selection);

  this->root->addChild(buttonRoot);
  this->root->addChild(spacingY);
}
