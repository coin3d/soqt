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
  \class RadioGroupKit RadioGroupKit.h
  \brief The RadioGroupKit class is a radiobutton group.

  This is a 3D user interface component.

  Example usage:

  \code
  #include <Inventor/Qt/SoQt.h>
  #include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
  #include <Inventor/nodes/SoSeparator.h>
  #include "RadioGroupKit.h"


  static void
  myRadioButtonCallback(void * userdata, SoSensor * sensor)
  {
    SoFieldSensor * fieldsensor = (SoFieldSensor *)sensor;
    SoSFInt32 * button = (SoSFInt32 *)fieldsensor->getAttachedField();
    SoDebugError::postInfo("myRadioButtonCallback",
                           "Button '%d' clicked",
                           button->getValue());
  }

  int
  main(int argc, char ** argv)
  {
    QWidget * mainwin = SoQt::init(argc, argv, argv[0]);
    RadioGroupKit::initClass();

    SoSeparator * root = new SoSeparator;
    root->ref();

    // Creating a basic radiobutton group
    RadioGroupKit * radiogroup = new RadioGroupKit;
    radiogroup->labels.set1Value(0,"Item #1");
    radiogroup->labels.set1Value(1,"Item #2");
    radiogroup->labels.set1Value(2,"Item #3");
    root->addChild(radiogroup);

    // Setting up a callback sensor for the radiobuttons
    SoFieldSensor * radioGroupSensor =
      new SoFieldSensor(myRadioButtonCallback, NULL);
    radioGroupSensor->attach(&radiogroup->selected);

    // Setting up scene
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
  SoSelection *root;
  SoFieldSensor * labelSensor;
  SoSelection * groupSelection;

  void removeAllRadioButtons();
  void reconstructRadioButtons();
  void addRadioButton(SbString label);
  static void buttonClickedCallback(void *userData, SoPath *node);
  static void radioButtonSensor(void *classObject, SoSensor *sensor);


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

  SO_KIT_ADD_CATALOG_ENTRY(radioGroupRoot,SoSelection,FALSE,this, "",TRUE);
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

  PRIVATE(this)->labelSensor = new SoFieldSensor(PRIVATE(this)->radioButtonSensor,PRIVATE(this));
  PRIVATE(this)->labelSensor->setPriority(0);
  PRIVATE(this)->labelSensor->attach(&labels);

  PRIVATE(this)->root = new SoSelection;
  this->setPart("radioGroupRoot", PRIVATE(this)->root);

  // General SoSelector node for this radiogroup
  PRIVATE(this)->root->addSelectionCallback(&PRIVATE(this)->buttonClickedCallback, PRIVATE(this));

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

  RadioGroupKitP * radioGroupP = (RadioGroupKitP *) userData;

  // Fetch clicked node object
  SoNode * tail = (SoNode *) ((SoFullPath*)path)->getNodeFromTail(0);

  // Bullet or the text?
  if(tail->isOfType(SoText2::getClassTypeId()))
    tail = (SoNode *) ((SoFullPath*)path)->getNodeFromTail(1);
  else
    tail = (SoNode *) ((SoFullPath*)path)->getNodeFromTail(2);

  int index = (radioGroupP->root->findChild(tail))/2;
  assert(index != -1); // Failsafe

  SoTransformSeparator * button = (SoTransformSeparator *) radioGroupP->buttonList->get(index);
  for(int i=0;i<radioGroupP->buttonList->getLength();++i){
    SoTransformSeparator *sep = (SoTransformSeparator *) radioGroupP->buttonList->get(i);
    SoBaseColor *color = (SoBaseColor *) sep->getChild(0);
    SoBaseColor *bulletColor =  (SoBaseColor*) SO_GET_PART(PUBLIC(radioGroupP), "BulletColor",SoBaseColor);
    color->rgb = bulletColor->rgb;
  }

  // Highlight selected button
  SoBaseColor * color = (SoBaseColor *) button->getChild(0);
  SoBaseColor * bulletColor =  (SoBaseColor*) SO_GET_PART(PUBLIC(radioGroupP), "BulletColorActive",SoBaseColor);
  color->rgb = bulletColor->rgb;

  // Update selected field
  PUBLIC(radioGroupP)->selected.setValue(index);


#if 0 // debug
  SoDebugError::postInfo("RadioGroupKitP::buttonClickedCallback","RadioGroupKit::selected = %d", index);
#endif // debug

}

void
RadioGroupKitP::radioButtonSensor(void * classObject, SoSensor * sensor)
{

  RadioGroupKitP * pimpl = (RadioGroupKitP *) classObject;

  // Button is added
  if(pimpl->buttonCounter < PUBLIC(pimpl)->labels.getNum()){
    SbString newlabel = PUBLIC(pimpl)->labels[pimpl->buttonCounter];
    pimpl->addRadioButton(newlabel);
    pimpl->buttonCounter++;

  // Button is removed
  } else if(pimpl->buttonCounter > PUBLIC(pimpl)->labels.getNum()){
    pimpl->removeAllRadioButtons();
    pimpl->reconstructRadioButtons();

  // Assuming a button is modified
  } else {
    pimpl->removeAllRadioButtons();
    pimpl->reconstructRadioButtons();
  }

}


void
RadioGroupKitP::removeAllRadioButtons()
{

  // Remove all registrated buttons for list
  for(int i=0;i<this->buttonList->getLength();++i)
    this->buttonList->remove(i);

  this->root->removeAllChildren();
  this->buttonCounter = 0;

}


void
RadioGroupKitP::reconstructRadioButtons()
{
  for(int i=0;i<PUBLIC(this)->labels.getNum(); ++i){
    this->addRadioButton(PUBLIC(this)->labels[i]);
    this->buttonCounter++;
  }
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

  SoTransformSeparator * sep;

  // Make the first added button selected as default
  if(buttonCounter == 0){
    sep = (SoTransformSeparator*) SO_GET_PART(PUBLIC(this), "RadioBulletActive",SoTransformSeparator)->copy();
    PUBLIC(this)->selected.setValue(0);
  } else {
    sep = (SoTransformSeparator*) SO_GET_PART(PUBLIC(this), "RadioBullet",SoTransformSeparator)->copy();
  }

  this->buttonList->set(buttonCounter,sep);    // Save the separator node for later changes @ callback
  buttonRoot->addChild(sep);

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

  buttonRoot->addChild(spacingX);
  buttonRoot->addChild(buttonLabel);

  this->root->addChild(buttonRoot);
  this->root->addChild(spacingY);

}
