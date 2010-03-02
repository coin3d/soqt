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
  \class RGBCubeEditorKit RGBCubeEditorKit.h
  \brief The RGBCubeEditorKit class is an editor for setting a RGB triplet color value.

  This is a 3D user interface component.

  Example usage:

  \code
  #include <Inventor/Qt/SoQt.h>
  #include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
  #include <Inventor/nodes/SoSeparator.h>
  #include "RGBCubeEditorKit.h"

  static void myRgbChangeCallback(void * userData, SoSensor * sensor)
  {
    SoFieldSensor * fieldSensor = (SoFieldSensor *) sensor;
    SoMFColor * color = (SoMFColor *) fieldSensor->getAttachedField();
  }

  int
  main(int argc, char ** argv)
  {
    QWidget * mainwin = SoQt::init(argc, argv, argv[0]);
    RGBCubeEditorKit::initClass();

    SoSeparator * root = new SoSeparator;
    root->ref();

    // Creating the cube object
    RGBCubeEditorKit *rgbCube = new RGBCubeEditorKit;
    root->addChild(rgbCube);

    // Attaching a sensor to the 'rgb' field in the RGBCubeEditorKit
    SoFieldSensor * rgbCubeSensor = new SoFieldSensor(myRgbChangeCallback,this);
    rgbCubeSensor->attach(&rgbCube->rgb);

    // Setup scene
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

#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/SoPickedPoint.h>

#include <Inventor/nodes/SoCube.h>
#include <Inventor/draggers/SoScale1Dragger.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoText2.h>
#include <Inventor/nodes/SoFont.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoMaterialBinding.h>
#include <Inventor/nodes/SoLightModel.h>
#include <Inventor/nodes/SoLight.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoTransformSeparator.h>
#include <Inventor/nodes/SoSelection.h>
#include <Inventor/nodes/SoShapeHints.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/nodes/SoMarkerSet.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoRotationXYZ.h>
#include <Inventor/nodes/SoAntiSquish.h>
#include <Inventor/nodes/SoTransformation.h>
#include <Inventor/nodes/SoPickStyle.h>
#include <Inventor/actions/SoGetMatrixAction.h>

#include "RGBCubeEditorKit.h"

// *************************************************************************

SO_KIT_SOURCE(RGBCubeEditorKit);

// *************************************************************************

static const int CUBE_SIZE_X = 2;
static const int CUBE_SIZE_Y = 2;
static const int CUBE_SIZE_Z = 2;

class RGBCubeEditorKitP {
public:
  RGBCubeEditorKitP(RGBCubeEditorKit * master) {
    this->master = master;
  }

  float draggerXValue;
  float draggerYValue;
  float draggerZValue;
  SoScale1Dragger * draggerX;             // RGB draggers
  SoScale1Dragger * draggerY;
  SoScale1Dragger * draggerZ;
  SoMaterial * cubeMaterial;              // Rgb cube material
  SoCoordinate3 * colorCubeCoords;
  SoIndexedFaceSet * cubeIndexedFacelist;
  SoTransformSeparator * cubeRoot;
  SoText2 * textRedValue;                 // Text on axis
  SoText2 * textGreenValue;
  SoText2 * textBlueValue;
  SoTranslation * colorIndicatorPosition; // Current color indicator 'o'
  SbVec3f * cubeVertices;
  SoFieldSensor * rgbSensor;

  void draggerCallback(void);

  void initRgbCube(void);

  void initCubeFacelist(SoTransformSeparator * root,
                     SoCoordinate3 * colorCubeCoords,
                     SoMaterial * cubeMaterial);

  void initCubeDraggers(SoSeparator * root,
                     SoScale1Dragger * draggerX,
                     SoScale1Dragger * draggerY,
                     SoScale1Dragger * draggerZ,
                     SoDraggerCB * cb1,
                     SoDraggerCB * cb2,
                     SoDraggerCB * cb3,
                     float value1, float value2, float value3);

  void updateCubeVertices(SoCoordinate3 * colorCubeCoords,
                       SoMaterial * cubeMaterial,
                       float x, float y, float z);

  void modifyDraggerWidget(SoScale1Dragger * dragger);

  void updateColorValueText(float red, float green, float blue);

  static void rgbChangedCallback(void * classObject, SoSensor * sensor);
  static void mouseClickCallback(void *classObject, SoEventCallback * cb);
  static void draggerXCallback(void * classObject, SoDragger * dragger);
  static void draggerYCallback(void * classObject, SoDragger * dragger);
  static void draggerZCallback(void * classObject, SoDragger * dragger);



private:
  RGBCubeEditorKit * master;
};

#define PRIVATE(p) (p->pimpl)
#define PUBLIC(p) (p->master)

// *************************************************************************

RGBCubeEditorKit::RGBCubeEditorKit(void)
{

  PRIVATE(this) = new RGBCubeEditorKitP(this);

  SO_KIT_CONSTRUCTOR(RGBCubeEditorKit);
  SO_KIT_ADD_CATALOG_ENTRY(RGBCubeRoot, SoSeparator, TRUE, this, "", TRUE);

  SO_KIT_ADD_FIELD(rgb, (SbColor(0.8, 0.8, 0.8)));
  SO_KIT_INIT_INSTANCE();

  PRIVATE(this)->draggerXValue = 0.8;
  PRIVATE(this)->draggerYValue = 0.8;
  PRIVATE(this)->draggerZValue = 0.8;

  PRIVATE(this)->initRgbCube();

  PRIVATE(this)->rgbSensor = new SoFieldSensor(pimpl->rgbChangedCallback,PRIVATE(this));
  PRIVATE(this)->rgbSensor->setPriority(0);
  PRIVATE(this)->rgbSensor->attach(&this->rgb);

}

RGBCubeEditorKit::~RGBCubeEditorKit()
{
  delete PRIVATE(this)->rgbSensor;
  delete PRIVATE(this);
}

void
RGBCubeEditorKit::initClass(void)
{
  SO_KIT_INIT_CLASS(RGBCubeEditorKit, SoInteractionKit, "InteractionKit");
}

SbBool
RGBCubeEditorKit::affectsState(void) const
{
  return FALSE;
}

void
RGBCubeEditorKitP::rgbChangedCallback(void * classObject, SoSensor * sensor)
{

  RGBCubeEditorKitP * rgbCubeP = (RGBCubeEditorKitP *) classObject;  // Fetch caller object

  rgbCubeP->draggerXValue = rgbCubeP->master->rgb[0][0];
  rgbCubeP->draggerYValue = rgbCubeP->master->rgb[0][1];
  rgbCubeP->draggerZValue = rgbCubeP->master->rgb[0][2];

  rgbCubeP->draggerX->scaleFactor.setValue(rgbCubeP->draggerXValue,1,1);
  rgbCubeP->draggerY->scaleFactor.setValue(rgbCubeP->draggerYValue,1,1);
  rgbCubeP->draggerZ->scaleFactor.setValue(rgbCubeP->draggerZValue,1,1);

  // Detach sensor to prevent inf. loop. before changing 'rgb' field
  SoFieldSensor * rgbSensor = (SoFieldSensor *) sensor;
  rgbSensor->detach();
  rgbCubeP->draggerCallback();
  rgbSensor->attach(&rgbCubeP->master->rgb);

}

void
RGBCubeEditorKitP::mouseClickCallback(void * classObject, SoEventCallback * cb)
{

  SoMouseButtonEvent * mouseEvent = (SoMouseButtonEvent *) (cb->getEvent());

  if(mouseEvent->getButton() == SoMouseButtonEvent::BUTTON1 &&
     mouseEvent->getState() == SoButtonEvent::UP) return;

  RGBCubeEditorKitP * rgbCubeP = (RGBCubeEditorKitP *) classObject;  // Fetch caller object

  // Fetch viewport and scenegraph
  SoHandleEventAction * handleaction = cb->getAction();
  const SbViewportRegion viewport = handleaction->getViewportRegion();
  const SoPath * scenePath = handleaction->getCurPath();
  SoNode * sceneRoot = scenePath->getHead();


  // Fetch translation of this cube
  SoPath * scenePathCopy = scenePath->copy();
  scenePathCopy->ref();
  SoGetMatrixAction matrixAction(viewport);
  matrixAction.apply(scenePathCopy);
  SbMatrix matrix = matrixAction.getMatrix();
  scenePathCopy->unref();

  SbVec3f scale, translation;
  SbRotation rotation, scaleo;
  matrix.getTransform(translation, rotation, scale, scaleo);

  SoRayPickAction rayPickAction(viewport);
  SbVec2s pos(mouseEvent->getPosition());
  rayPickAction.setPoint(mouseEvent->getPosition());
  rayPickAction.apply(sceneRoot);


  SoPickedPoint * myPP = rayPickAction.getPickedPoint();
  if(myPP == NULL)
    return;  // no object were selected. aborting.


  SoFullPath * path = (SoFullPath *)myPP->getPath();
  SoNode * end = path->getTail();


  if(end == rgbCubeP->cubeIndexedFacelist){  // Is this the IndexedFaceSet object?

    SbVec3f ipoint = myPP->getPoint();

    SbVec3f cubeOrigo = rgbCubeP->colorCubeCoords->point[0];
    cubeOrigo[0] += translation[0];
    cubeOrigo[1] += translation[1];
    cubeOrigo[2] += translation[2];

    // Find new corner for color cube.
    SbVec3f newPoint;
    newPoint[0] = (ipoint[0] - cubeOrigo[0])/CUBE_SIZE_X;
    newPoint[1] = (ipoint[1] - cubeOrigo[1])/CUBE_SIZE_Y;
    newPoint[2] = (ipoint[2] - cubeOrigo[2])/CUBE_SIZE_Z;

    // Chech if new corner is out of bounds
    if(newPoint[0] > CUBE_SIZE_X/2) newPoint[0] = CUBE_SIZE_X/2;
    if(newPoint[1] > CUBE_SIZE_Y/2) newPoint[1] = CUBE_SIZE_Y/2;
    if(newPoint[2] > CUBE_SIZE_Z/2) newPoint[2] = CUBE_SIZE_Z/2;

    rgbCubeP->draggerX->scaleFactor.setValue(newPoint[0], 1, 1);
    rgbCubeP->draggerY->scaleFactor.setValue(newPoint[1], 1, 1);
    rgbCubeP->draggerZ->scaleFactor.setValue(newPoint[2], 1, 1);
    rgbCubeP->draggerXValue = newPoint[0];
    rgbCubeP->draggerYValue = newPoint[1];
    rgbCubeP->draggerZValue = newPoint[2];
    rgbCubeP->draggerCallback();

  }
}


void
RGBCubeEditorKitP::updateColorValueText(float red, float green, float blue)
{

  if(red < 0) red = 0;
  if(green < 0) green = 0;
  if(blue < 0) blue = 0;

  char buffer[8];

  sprintf(buffer, "[%.2f]", red);
  this->textRedValue->string = buffer;

  sprintf(buffer, "[%.2f]", green);
  this->textGreenValue->string = buffer;

  sprintf(buffer, "[%.2f]", blue);
  this->textBlueValue->string = buffer;

}


void
RGBCubeEditorKitP::draggerCallback(void)
{
  this->updateCubeVertices(this->colorCubeCoords,
                           this->cubeMaterial,
                           draggerXValue,
                           draggerYValue,
                           draggerZValue);
  this->updateColorValueText(draggerXValue, draggerYValue, draggerZValue);

  // Update global RGB field
  PUBLIC(this)->rgb.setValue(draggerXValue, draggerYValue, draggerZValue);
}


void
RGBCubeEditorKitP::draggerXCallback(void * obj, SoDragger * dragger)
{
  RGBCubeEditorKit * rgbCube = (RGBCubeEditorKit *)obj;
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  PRIVATE(rgbCube)->draggerXValue = sd->scaleFactor.getValue()[0];
  if(PRIVATE(rgbCube)->draggerXValue > 1.0)
    PRIVATE(rgbCube)->draggerXValue = 1;
  if(PRIVATE(rgbCube)->draggerXValue < 0.0001)
    PRIVATE(rgbCube)->draggerXValue = 0.0001;
  PRIVATE(rgbCube)->draggerCallback();
}


void
RGBCubeEditorKitP::draggerYCallback(void * obj, SoDragger * dragger)
{
  RGBCubeEditorKit * rgbCube = (RGBCubeEditorKit *)obj;
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  PRIVATE(rgbCube)->draggerYValue = sd->scaleFactor.getValue()[0];
  if(PRIVATE(rgbCube)->draggerYValue > 1.0)
    PRIVATE(rgbCube)->draggerYValue = 1;
  if(PRIVATE(rgbCube)->draggerYValue < 0.0001)
    PRIVATE(rgbCube)->draggerYValue = 0.0001;
  PRIVATE(rgbCube)->draggerCallback();
}


void
RGBCubeEditorKitP::draggerZCallback(void * obj, SoDragger * dragger)
{
  RGBCubeEditorKit * rgbCube = (RGBCubeEditorKit *)obj;
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  PRIVATE(rgbCube)->draggerZValue = sd->scaleFactor.getValue()[0];
  if(PRIVATE(rgbCube)->draggerZValue > 1.0)
    PRIVATE(rgbCube)->draggerZValue = 1;
  if(PRIVATE(rgbCube)->draggerZValue < 0.0001)
    PRIVATE(rgbCube)->draggerZValue = 0.0001;
  PRIVATE(rgbCube)->draggerCallback();
}


void
RGBCubeEditorKitP::updateCubeVertices(SoCoordinate3 * cubeCoords,
                              SoMaterial * cubeMaterial,
                              float x, float y, float z)
{

  // X-face
  cubeCoords->point.set1Value(6, x*CUBE_SIZE_X, y*CUBE_SIZE_Y, z*CUBE_SIZE_Z);
  cubeCoords->point.set1Value(2, x*CUBE_SIZE_X, y*CUBE_SIZE_Y, 0);
  cubeCoords->point.set1Value(1, x*CUBE_SIZE_X, 0, 0);
  cubeCoords->point.set1Value(5, x*CUBE_SIZE_X, 0, z*CUBE_SIZE_Z);

  // Y-face
  cubeCoords->point.set1Value(3, 0, y*CUBE_SIZE_Y, 0);
  cubeCoords->point.set1Value(7, 0, y*CUBE_SIZE_Y, z*CUBE_SIZE_Z);

  // Z-face
  cubeCoords->point.set1Value(7, 0, y*CUBE_SIZE_Y, z*CUBE_SIZE_Z);
  cubeCoords->point.set1Value(4, 0, 0, z*CUBE_SIZE_Z);

  cubeMaterial->diffuseColor.set1Value(1, x, 0, 0);
  cubeMaterial->diffuseColor.set1Value(2, x, y, 0);
  cubeMaterial->diffuseColor.set1Value(3, 0, y, 0);
  cubeMaterial->diffuseColor.set1Value(4, 0, 0, z);
  cubeMaterial->diffuseColor.set1Value(5, x, 0, z);
  cubeMaterial->diffuseColor.set1Value(6, x, y, z);
  cubeMaterial->diffuseColor.set1Value(7, 0, y, z);

  colorIndicatorPosition->translation.setValue(cubeCoords->point[6]);

}


void
RGBCubeEditorKitP::initCubeFacelist(SoTransformSeparator * root,
                            SoCoordinate3 * cubeCoords,
                            SoMaterial * cubeMaterial)
{

  SbVec3f cubeVerts[4*2];
  int32_t cubeVertexIndices[] = {3,2,1,0, SO_END_FACE_INDEX,
                             5,6,7,4, SO_END_FACE_INDEX,
                             4,7,3,0, SO_END_FACE_INDEX,
                             5,1,2,6, SO_END_FACE_INDEX,
                             7,6,2,3, SO_END_FACE_INDEX,
                             5,4,0,1, SO_END_FACE_INDEX };

  // Back
  cubeVerts[0].setValue(0, 0, 0);
  cubeVerts[1].setValue(CUBE_SIZE_X, 0, 0);
  cubeVerts[2].setValue(CUBE_SIZE_X, CUBE_SIZE_Y, 0);
  cubeVerts[3].setValue(0, CUBE_SIZE_Y, 0);

  // Front
  cubeVerts[4].setValue(0, 0, CUBE_SIZE_Z);
  cubeVerts[5].setValue(CUBE_SIZE_X, 0, CUBE_SIZE_Z);
  cubeVerts[6].setValue(CUBE_SIZE_X, CUBE_SIZE_Y, CUBE_SIZE_Z);
  cubeVerts[7].setValue(0, CUBE_SIZE_Y, CUBE_SIZE_Z);


  // Vertex colors
  cubeMaterial->diffuseColor.set1Value(0, 0,0,0);
  cubeMaterial->diffuseColor.set1Value(1, 1,0,0);
  cubeMaterial->diffuseColor.set1Value(2, 1,1,0);
  cubeMaterial->diffuseColor.set1Value(3, 0,1,0);

  cubeMaterial->diffuseColor.set1Value(4, 0,0,1);
  cubeMaterial->diffuseColor.set1Value(5, 1,0,1);
  cubeMaterial->diffuseColor.set1Value(6, 1,1,1);
  cubeMaterial->diffuseColor.set1Value(7, 0,1,1);


  // ColorCube + LineCube coordinates
  SoCoordinate3 * lineCubeCoords = new SoCoordinate3;
  lineCubeCoords->point.setValues(0,4*2,cubeVerts);
  cubeCoords->point.setValues(0,4*2,cubeVerts);


  // Cube faceset
  cubeIndexedFacelist = new SoIndexedFaceSet;
  cubeIndexedFacelist->coordIndex.setValues(0, 6*5, cubeVertexIndices);


  // Cube lineset
  SoIndexedLineSet * cubeLineList = new SoIndexedLineSet;
  cubeLineList->coordIndex.setValues(0, 6*5, cubeVertexIndices);
  SoMaterial * cubeLineMaterial = new SoMaterial;
  cubeLineMaterial->diffuseColor.set1Value(0,1,1,1);


  // Cube material
  SoMaterialBinding * cubeMatBind = new SoMaterialBinding;
  cubeMatBind->value = SoMaterialBinding::PER_VERTEX_INDEXED;


  // No lighting of color-cube
  SoLightModel * cubeLight = new SoLightModel;
  cubeLight->model = SoLightModel::BASE_COLOR;


  // Current color indicator
  SoSeparator * colorIndicatorRoot = new SoSeparator;

  SoMarkerSet * colorIndicator = new SoMarkerSet;
  colorIndicator->markerIndex = SoMarkerSet::CIRCLE_LINE_9_9;
  colorIndicator->numPoints = 1;

  SoBaseColor * colorIndicatorColor = new SoBaseColor;
  colorIndicatorColor->rgb.setValue(1,0,0);
  colorIndicatorRoot = new SoSeparator;
  colorIndicatorPosition->translation.setValue(cubeVerts[6].getValue());

  colorIndicatorRoot->addChild(colorIndicatorPosition);
  colorIndicatorRoot->addChild(colorIndicatorColor);
  colorIndicatorRoot->addChild(colorIndicator);


  // build scenegraph
  root->addChild(cubeMatBind);
  root->addChild(cubeMaterial);
  root->addChild(cubeLight);
  root->addChild(cubeCoords);
  root->addChild(cubeIndexedFacelist);

  SoPickStyle * pickStyle = new SoPickStyle;
  pickStyle->style = SoPickStyle::UNPICKABLE;

  SoSeparator * lineRoot = new SoSeparator;
  lineRoot->addChild(pickStyle);              // Make the linecube unpickable
  lineRoot->addChild(lineCubeCoords);
  lineRoot->addChild(cubeLineMaterial);
  lineRoot->addChild(cubeLineList);
  root->addChild(lineRoot);

  root->addChild(colorIndicatorRoot);

}


void
RGBCubeEditorKitP::initCubeDraggers(SoSeparator * root,
                               SoScale1Dragger * draggerX,
                               SoScale1Dragger * draggerY,
                               SoScale1Dragger * draggerZ,
                               SoDraggerCB * cb1,
                               SoDraggerCB * cb2,
                               SoDraggerCB * cb3,
                               float value1,float value2, float value3)
{

  draggerX->scaleFactor.setValue(value1,1,1);
  draggerY->scaleFactor.setValue(value2,1,1);
  draggerZ->scaleFactor.setValue(value3,1,1);

  draggerX->addMotionCallback(cb1, PUBLIC(this));
  draggerY->addMotionCallback(cb2, PUBLIC(this));
  draggerZ->addMotionCallback(cb3, PUBLIC(this));


  SoTranslation * draggerXTrans = new SoTranslation;
  SoTranslation * draggerYTrans = new SoTranslation;
  SoTranslation * draggerZTrans = new SoTranslation;

  SoSeparator * sep = new SoSeparator;

  SoRotation * draggerXRotation = new SoRotation;
  SoRotation * draggerYRotation = new SoRotation;
  SoRotation * draggerZRotation = new SoRotation;

  draggerXRotation->rotation.setValue(0,1,1,0);
  draggerYRotation->rotation.setValue(1,0,1,0);
  draggerZRotation->rotation.setValue(1,1,0,0);

  draggerXTrans->translation.setValue( CUBE_SIZE_X/2, 0, CUBE_SIZE_Z+.2);
  draggerYTrans->translation.setValue(-CUBE_SIZE_X/2-.2, -CUBE_SIZE_Y-.2, CUBE_SIZE_Z/2+.1);
  draggerZTrans->translation.setValue(-CUBE_SIZE_X/2-.2, -CUBE_SIZE_Y/2-.2, 0);


  // Axis - Text
  SoFont * font = new SoFont;
  font->name.setValue("Times-Roman");
  font->size.setValue(24.0);
  root->addChild(font);

  SoPickStyle * pickStyle = new SoPickStyle;
  pickStyle->style = SoPickStyle::UNPICKABLE;

  SoTranslation * textTrans = new SoTranslation;
  textTrans->translation.setValue(0,.3,-.2);

  SoSeparator * textRedSep = new SoSeparator;
  SoSeparator * textGreenSep = new SoSeparator;
  SoSeparator * textBlueSep = new SoSeparator;

  SoBaseColor * textRedColor = new SoBaseColor;
  textRedColor->rgb.setValue(1,.4,.4);
  SoBaseColor * textGreenColor = new SoBaseColor;
  textGreenColor->rgb.setValue(.4,1,.4);
  SoBaseColor * textBlueColor = new SoBaseColor;
  textBlueColor->rgb.setValue(.4,.4,1);

  textRedSep->addChild(pickStyle);
  textRedSep->addChild(textRedColor);
  textRedSep->addChild(textTrans);
  textRedSep->addChild(this->textRedValue);

  textGreenSep->addChild(pickStyle);
  textGreenSep->addChild(textGreenColor);
  textGreenSep->addChild(textTrans);
  textGreenSep->addChild(this->textGreenValue);

  textBlueSep->addChild(pickStyle);
  textBlueSep->addChild(textBlueColor);
  textBlueSep->addChild(textTrans);
  textBlueSep->addChild(this->textBlueValue);


  // build scene graph
  root->addChild(sep);

  root->addChild(draggerXTrans);
  root->addChild(draggerXRotation);
  root->addChild(draggerX);
  root->addChild(textRedSep);

  root->addChild(sep);

  root->addChild(draggerYTrans);
  root->addChild(draggerYRotation);
  root->addChild(draggerY);
  root->addChild(textGreenSep);

  root->addChild(sep);

  root->addChild(draggerZTrans);
  root->addChild(draggerZRotation);
  root->addChild(draggerZ);
  root->addChild(textBlueSep);

}



void
RGBCubeEditorKitP::modifyDraggerWidget(SoScale1Dragger * dragger)
{

  SoSeparator * newDragger = new SoSeparator;
  newDragger->ref();

  SoSeparator * newDraggerActive = new SoSeparator;
  newDraggerActive->ref();

  // Optimize all drawing
  SoShapeHints * draggerHint = new SoShapeHints;
  draggerHint->vertexOrdering = SoShapeHints::COUNTERCLOCKWISE;
  draggerHint->shapeType = SoShapeHints::SOLID;
  newDragger->addChild(draggerHint);
  newDraggerActive->addChild(draggerHint);


  SoCylinder * tube = new SoCylinder;
  tube->radius=.05;
  SoRotationXYZ * tubeRot = new SoRotationXYZ;
  tubeRot->axis = SoRotationXYZ::Z;
  tubeRot->angle = 3.1415/2;

  // Passive dragger
  SoMaterial * passiveMat = new SoMaterial;
  passiveMat->diffuseColor.setValue(.7,.7,.7);
  newDragger->addChild(passiveMat);
  newDragger->addChild(tubeRot);
  newDragger->addChild(tube);

  // Active dragger
  SoMaterial * activeMat = new SoMaterial;
  activeMat->diffuseColor.setValue(0,1,1);
  newDraggerActive->addChild(activeMat);
  newDraggerActive->addChild(tubeRot);
  newDraggerActive->addChild(tube);

  // Scaler
  SoSeparator * newScaler = new SoSeparator;
  SoMaterial * scaleMat = new SoMaterial;
  scaleMat->diffuseColor.setValue(0,1,0);

  SoCube * cube1 = new SoCube; // Axis cross
  SoCube * cube2 = new SoCube;

  cube1->width = 0.0;
  cube1->height = .5;
  cube1->depth = .1;
  cube2->width = 0.0;
  cube2->height = .1;
  cube2->depth = .5;


  SoSphere * endPoint = new SoSphere;  // Endpoint ball
  endPoint->radius = .05;

  SoAntiSquish * antiSquish = new SoAntiSquish; // Keep aspect ratio!
  antiSquish->sizing = SoAntiSquish::Y;

  SoTranslation * endPointTrans1 = new SoTranslation;
  endPointTrans1->translation.setValue(-1,0,0);
  SoTranslation * endPointTrans2 = new SoTranslation;
  endPointTrans2->translation.setValue(1,0,0);

  SoSeparator * endPoint1Sep = new SoSeparator;
  SoSeparator * endPoint2Sep = new SoSeparator;


  // Build scene graph
  endPoint1Sep->addChild(endPointTrans1);
  endPoint1Sep->addChild(antiSquish);
  endPoint1Sep->addChild(endPoint);

  endPoint2Sep->addChild(endPointTrans2);
  endPoint2Sep->addChild(antiSquish);
  endPoint2Sep->addChild(endPoint);

  newScaler->addChild(scaleMat);
  newScaler->addChild(cube1);
  newScaler->addChild(cube2);

  newScaler->addChild(endPoint1Sep);
  newScaler->addChild(endPoint2Sep);


  // Create new draggers
  dragger->setPart("feedback",newDragger);
  dragger->setPart("feedbackActive",newDraggerActive);

  dragger->setPart("scaler",newScaler);
  dragger->setPart("scalerActive",newScaler);

}


void
RGBCubeEditorKitP::initRgbCube(void)
{
  SoSeparator * root = new SoSeparator;
  PUBLIC(this)->setPart("RGBCubeRoot",root);


  SoEventCallback * mouseCallback = new SoEventCallback;
  mouseCallback->addEventCallback(SoMouseButtonEvent::getClassTypeId(),
                                  &this->mouseClickCallback, this);
  root->addChild(mouseCallback);


  // Creating dragger-text objects
  this->textRedValue = new SoText2;
  this->textGreenValue = new SoText2;
  this->textBlueValue = new SoText2;


  // Setup diffuse cube geometry
  this->draggerX =  new SoScale1Dragger;
  this->draggerY =  new SoScale1Dragger;
  this->draggerZ =  new SoScale1Dragger;


  // Modify dragger look
  this->modifyDraggerWidget(this->draggerX);
  this->modifyDraggerWidget(this->draggerY);
  this->modifyDraggerWidget(this->draggerZ);


  // Create 'o' point translation for cube-corner
  this->colorIndicatorPosition = new SoTranslation;

  this->cubeMaterial = new SoMaterial;
  this->colorCubeCoords = new SoCoordinate3;
  this->cubeRoot = new SoTransformSeparator;
  this->initCubeFacelist(this->cubeRoot,
                         this->colorCubeCoords,
                         this->cubeMaterial);
  SoSeparator * cubeRootDraggers = new SoSeparator;
  this->initCubeDraggers(cubeRootDraggers,
                         this->draggerX,
                         this->draggerY,
                         this->draggerZ,
                         &this->draggerXCallback,
                         &this->draggerYCallback,
                         &this->draggerZCallback,
                         draggerXValue,
                         draggerXValue,
                         draggerXValue);
  this->cubeRoot->addChild(cubeRootDraggers);
  this->cubeRoot->ref();


  root->addChild(this->cubeRoot);
  draggerCallback();
}
