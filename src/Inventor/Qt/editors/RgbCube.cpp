
/**
   Et enkelt RGB-Cube eksperiment
   2002 - Øystein
*/

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/SoPickedPoint.h> 

#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/draggers/SoScale1Dragger.h>
#include <Inventor/nodes/SoTranslation.h> 
#include <Inventor/nodes/SoSeparator.h> 
#include <Inventor/nodes/SoResetTransform.h> 
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
#include <Inventor/nodes/SoSwitch.h> 
#include <Inventor/nodes/SoPerspectiveCamera.h> 
#include <Inventor/nodes/SoEventCallback.h> 
#include <Inventor/events/SoEvent.h> 
#include <Inventor/events/SoMouseButtonEvent.h> 
#include <Inventor/actions/SoRayPickAction.h> 
#include <Inventor/actions/SoWriteAction.h> 
#include <Inventor/nodes/SoMarkerSet.h> 
#include <Inventor/draggers/SoTranslate1Dragger.h> 
#include <Inventor/nodes/SoCylinder.h> 
#include <Inventor/nodes/SoRotationXYZ.h> 
#include <Inventor/nodes/SoAntiSquish.h> 
#include <Inventor/nodes/SoTransformation.h> 
#include <Inventor/nodes/SoPickStyle.h> 


#include "RgbCube.h"


#define CUBE_SIZE_X 2
#define CUBE_SIZE_Y 2
#define CUBE_SIZE_Z 2

#define SIDE_X 0
#define SIDE_Y 1
#define SIDE_Z 2


//cRgbCube *rgbCube;

// Predef'ing some static functions
/*
void static draggerCallbackDiffuse(void);
void static draggerCallbackSpecular(void);
void static draggerCallbackEmissive(void);
void static draggerCallbackAmbient(void);
*/

////////////////////////////////////////////////////////////////

cRgbCube::cRgbCube()
{
  draggerXValueDiffuse = 0.8;
  draggerYValueDiffuse = 0.8;
  draggerZValueDiffuse = 0.8;

  draggerXValueSpecular = 0.001;
  draggerYValueSpecular = 0.001;
  draggerZValueSpecular = 0.001;

  draggerXValueAmbient = 0.2;
  draggerYValueAmbient = 0.2;
  draggerZValueAmbient = 0.2;

  draggerXValueEmissive = 0.001;
  draggerYValueEmissive = 0.001;
  draggerZValueEmissive = 0.001;

  currentColorCube = COLOR_CUBE_DIFFUSE;
  currentColorPatch = COLOR_PATCH_SPHERE;

}
cRgbCube::~cRgbCube()
{
}
////////////////////////////////////////////////////////////////

void cRgbCube::mouseClickCallback(void *classObject, SoEventCallback *cb)
{

  SoMouseButtonEvent *mouseEvent = (SoMouseButtonEvent *) (cb->getEvent());
  
  
  if(mouseEvent->getButton() == SoMouseButtonEvent::BUTTON1 &&
       mouseEvent->getState() == SoButtonEvent::UP) return;
  

  cRgbCube *rgbCube = (cRgbCube *) classObject;  // Fetch caller object


  SbViewportRegion vpr(rgbCube->eviewer->getViewportRegion());
  SoRayPickAction rayPickAction(vpr);

  SbVec2s pos(mouseEvent->getPosition());
  rayPickAction.setPoint(mouseEvent->getPosition());
  rayPickAction.apply(rgbCube->eviewer->getSceneManager()->getSceneGraph());
  

  SoPickedPoint *myPP = rayPickAction.getPickedPoint();
  if(myPP == NULL)
    return;  // no object were selected. aborting.
  

  SoFaceDetail *faceDetail = (SoFaceDetail *) myPP->getDetail();
  SoPath *path = myPP->getPath();
  SoNode *end = path->getTail();
  
  SoIndexedFaceSet *dummy = new SoIndexedFaceSet;


  if(end->getTypeId() == SoIndexedFaceSet::getClassTypeId()){  // Is this the IndexedFaceSet object?
  
    SbVec3f ipoint = myPP->getPoint();

    // Using 'diffusecube' coords since all cubes should be located at the same spot.
    SbVec3f cubeOrigo = rgbCube->diffuseColorCubeCoords->point[0];
 
    // ** INCREDIBLE UGLY ** Have to compensate for the 'translation' in the scenegraph
    cubeOrigo[1] = cubeOrigo[1] + CUBE_SIZE_Y*1.5; 
    
    // Find new corner for color cube.
    SbVec3f newPoint;
    newPoint[0] = (ipoint[0] - cubeOrigo[0])/CUBE_SIZE_X;
    newPoint[1] = (ipoint[1] - cubeOrigo[1])/CUBE_SIZE_Y;
    newPoint[2] = (ipoint[2] - cubeOrigo[2])/CUBE_SIZE_Z;

    // Chech if new corner is out of bounds
    if(newPoint[0] > CUBE_SIZE_X/2) newPoint[0] = CUBE_SIZE_X/2;
    if(newPoint[1] > CUBE_SIZE_Y/2) newPoint[1] = CUBE_SIZE_Y/2;
    if(newPoint[2] > CUBE_SIZE_Z/2) newPoint[2] = CUBE_SIZE_Z/2;


    // Update active cube.
    switch(rgbCube->currentColorCube){
      
    case COLOR_CUBE_DIFFUSE:        
      rgbCube->diffuseDraggerX->scaleFactor.setValue(newPoint[0],1,1);
      rgbCube->diffuseDraggerY->scaleFactor.setValue(newPoint[1],1,1);
      rgbCube->diffuseDraggerZ->scaleFactor.setValue(newPoint[2],1,1);
      rgbCube->draggerXValueDiffuse = newPoint[0];
      rgbCube->draggerYValueDiffuse = newPoint[1];
      rgbCube->draggerZValueDiffuse = newPoint[2];
      rgbCube->draggerCallbackDiffuse();
      
      break;

    case COLOR_CUBE_AMBIENT:      
      rgbCube->ambientDraggerX->scaleFactor.setValue(newPoint[0],1,1);
      rgbCube->ambientDraggerY->scaleFactor.setValue(newPoint[1],1,1);
      rgbCube->ambientDraggerZ->scaleFactor.setValue(newPoint[2],1,1); 
      rgbCube->draggerXValueAmbient = newPoint[0];
      rgbCube->draggerYValueAmbient = newPoint[1];
      rgbCube->draggerZValueAmbient = newPoint[2];
      rgbCube->draggerCallbackAmbient();
      break;

    case COLOR_CUBE_SPECULAR:      
      rgbCube->specularDraggerX->scaleFactor.setValue(newPoint[0],1,1);
      rgbCube->specularDraggerY->scaleFactor.setValue(newPoint[1],1,1);
      rgbCube->specularDraggerZ->scaleFactor.setValue(newPoint[2],1,1);
      rgbCube->draggerXValueSpecular = newPoint[0];
      rgbCube->draggerYValueSpecular = newPoint[1];
      rgbCube->draggerZValueSpecular = newPoint[2];
      rgbCube->draggerCallbackSpecular();
      break;
      
    case COLOR_CUBE_EMISSIVE:      
      rgbCube->emissiveDraggerX->scaleFactor.setValue(newPoint[0],1,1);
      rgbCube->emissiveDraggerY->scaleFactor.setValue(newPoint[1],1,1);
      rgbCube->emissiveDraggerZ->scaleFactor.setValue(newPoint[2],1,1);
      rgbCube->draggerXValueEmissive = newPoint[0];
      rgbCube->draggerYValueEmissive = newPoint[1];
      rgbCube->draggerZValueEmissive = newPoint[2];
      rgbCube->draggerCallbackEmissive();
      break;

    }
  }
}
////////////////////////////////////////////////////////////////
void cRgbCube::colorPatchToggleCallback(void *classObject,SoPath *selectionPath)
{

  cRgbCube *cube = (cRgbCube *) classObject;

  switch(cube->currentColorPatch){
  case COLOR_PATCH_CUBE:
    cube->currentColorPatch = COLOR_PATCH_SPHERE;
    cube->colorPatchCube->whichChild = SO_SWITCH_NONE;
    cube->colorPatchSphere->whichChild = SO_SWITCH_ALL;
    cube->colorPatchCone->whichChild = SO_SWITCH_NONE;
    break;
  case COLOR_PATCH_SPHERE:
    cube->currentColorPatch = COLOR_PATCH_CONE;
    cube->colorPatchCube->whichChild = SO_SWITCH_ALL;
    cube->colorPatchSphere->whichChild = SO_SWITCH_NONE;
    cube->colorPatchCone->whichChild = SO_SWITCH_NONE;
    break;
  case COLOR_PATCH_CONE:
    cube->currentColorPatch = COLOR_PATCH_CUBE;
    cube->colorPatchCube->whichChild = SO_SWITCH_NONE;
    cube->colorPatchSphere->whichChild = SO_SWITCH_NONE;
    cube->colorPatchCone->whichChild = SO_SWITCH_ALL;
    break;
  }

}
////////////////////////////////////////////////////////////////
void cRgbCube::removeCurrentColorCube()
{

  switch(currentColorCube){
  case COLOR_CUBE_DIFFUSE:
    sceneRoot->removeChild(diffuseCubeRoot);
    break;
  case COLOR_CUBE_AMBIENT:
    sceneRoot->removeChild(ambientCubeRoot);
    break;
  case COLOR_CUBE_SPECULAR:
    sceneRoot->removeChild(specularCubeRoot);
    break;
  case COLOR_CUBE_EMISSIVE:
    sceneRoot->removeChild(emissiveCubeRoot);
    break;
  }

  diffuseButtonColor->rgb.setValue(1,1,1);
  ambientButtonColor->rgb.setValue(1,1,1);
  specularButtonColor->rgb.setValue(1,1,1); 
  emissiveButtonColor->rgb.setValue(1,1,1); 
}
////////////////////////////////////////////////////////////////
static void radioButtonDiffuse(void *classObject,SoPath *selectionPath)
{
  cRgbCube *rgbCube = (cRgbCube *) classObject;
  if(rgbCube->currentColorCube == COLOR_CUBE_DIFFUSE) return;
  rgbCube->removeCurrentColorCube();
  rgbCube->diffuseButtonColor->rgb.setValue(0,1,1);
  rgbCube->currentColorCube = COLOR_CUBE_DIFFUSE;
  rgbCube->sceneRoot->addChild(rgbCube->diffuseCubeRoot);
  rgbCube->draggerCallbackDiffuse();
}
static void radioButtonAmbient(void *classObject,SoPath *selectionPath)
{
  cRgbCube *rgbCube = (cRgbCube *) classObject;
  if(rgbCube->currentColorCube == COLOR_CUBE_AMBIENT) return;
  rgbCube->removeCurrentColorCube();
  rgbCube->ambientButtonColor->rgb.setValue(0,1,1);
  rgbCube->currentColorCube = COLOR_CUBE_AMBIENT;
  rgbCube->sceneRoot->addChild(rgbCube->ambientCubeRoot);
  rgbCube->draggerCallbackAmbient();
}
static void radioButtonSpecular(void *classObject,SoPath *selectionPath)
{
  cRgbCube *rgbCube = (cRgbCube *) classObject;
  if(rgbCube->currentColorCube == COLOR_CUBE_SPECULAR) return;
  rgbCube->removeCurrentColorCube();
  rgbCube->specularButtonColor->rgb.setValue(0,1,1);
  rgbCube->currentColorCube = COLOR_CUBE_SPECULAR;
  rgbCube->sceneRoot->addChild(rgbCube->specularCubeRoot);
  rgbCube->draggerCallbackSpecular();
}
static void radioButtonEmissive(void *classObject,SoPath *selectionPath)
{
  cRgbCube *rgbCube = (cRgbCube *) classObject;
  if(rgbCube->currentColorCube == COLOR_CUBE_EMISSIVE) return;
  rgbCube->removeCurrentColorCube();
  rgbCube->emissiveButtonColor->rgb.setValue(0,1,1);
  rgbCube->currentColorCube = COLOR_CUBE_EMISSIVE;
  rgbCube->sceneRoot->addChild(rgbCube->emissiveCubeRoot);
  rgbCube->draggerCallbackEmissive();
}
////////////////////////////////////////////////////////////////

void cRgbCube::draggerShininessCallback(void *classObject,SoDragger *dragger)
{
  cRgbCube *rgbCube = (cRgbCube *) classObject;

  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->colorPatchMaterial->shininess = 1 - sd->scaleFactor.getValue()[0];

  float value = sd->scaleFactor.getValue()[0];
  if(value > 1) value = 1;
  char buffer[24];
  sprintf(buffer,"Shininess [%.2f]",value);
  rgbCube->textShininess->string = buffer;
}

static void draggerTransparencyCallback(void *classObject,SoDragger *dragger)
{
  cRgbCube *rgbCube = (cRgbCube *) classObject;

  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->colorPatchMaterial->transparency = 1 - sd->scaleFactor.getValue()[0];

  float value = sd->scaleFactor.getValue()[0];
  if(value > 1) value = 1;
  char buffer[16];
  sprintf(buffer,"Opaque [%.2f]",value);
  rgbCube->textTransparency->string = buffer;
}
////////////////////////////////////////////////////////////////

void cRgbCube::updateColorValueText(float red, float green, float blue)
{

  if(red < 0) red = 0;
  if(green < 0) green = 0;
  if(blue < 0) blue = 0;

  char buffer[8];

  sprintf(buffer,"[%.2f]",red);
  textRedValue->string = buffer;

  sprintf(buffer,"[%.2f]",green);
  textGreenValue->string = buffer;

  sprintf(buffer,"[%.2f]",blue);
  textBlueValue->string = buffer;

}

//////////////////////-------------------------------------------
void cRgbCube::draggerCallbackDiffuse()
{
  updateCubeVertices(diffuseColorCubeCoords,
		     diffuseCubeMaterial,
		     draggerXValueDiffuse,
		     draggerYValueDiffuse,
		     draggerZValueDiffuse);
  colorPatchMaterial->diffuseColor.setValue(draggerXValueDiffuse, 
					    draggerYValueDiffuse, 
					    draggerZValueDiffuse);
  updateColorValueText(draggerXValueDiffuse,draggerYValueDiffuse,draggerZValueDiffuse);
}
void cRgbCube::draggerXCallbackDiffuse(void *classObject,SoDragger *dragger)
{
  cRgbCube *rgbCube = (cRgbCube *) classObject;
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerXValueDiffuse = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerXValueDiffuse > 1.0)
    rgbCube->draggerXValueDiffuse = 1;
  rgbCube->draggerCallbackDiffuse();
}
void cRgbCube::draggerYCallbackDiffuse(void *classObject,SoDragger *dragger)
{
  cRgbCube *rgbCube = (cRgbCube *) classObject;
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerYValueDiffuse = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerYValueDiffuse > 1.0)
    rgbCube->draggerYValueDiffuse = 1;
  rgbCube->draggerCallbackDiffuse();
}
void cRgbCube::draggerZCallbackDiffuse(void *classObject,SoDragger *dragger)
{
  cRgbCube *rgbCube = (cRgbCube *) classObject;
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerZValueDiffuse = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerZValueDiffuse > 1.0)
    rgbCube->draggerZValueDiffuse = 1;
  rgbCube->draggerCallbackDiffuse();
}

////////////////////-------------------------------------------------
void cRgbCube::draggerCallbackSpecular()
{
  updateCubeVertices(specularColorCubeCoords,
		     specularCubeMaterial,
		     draggerXValueSpecular,
		     draggerYValueSpecular,
		     draggerZValueSpecular);
  colorPatchMaterial->specularColor.setValue(draggerXValueSpecular, 
					     draggerYValueSpecular, 
					     draggerZValueSpecular);
  updateColorValueText(draggerXValueSpecular,draggerYValueSpecular,draggerZValueSpecular);
}
void cRgbCube::draggerXCallbackSpecular(void *classObject,SoDragger *dragger)
{
  cRgbCube *rgbCube = (cRgbCube *) classObject;
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerXValueSpecular = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerXValueSpecular > 1.0)
    rgbCube->draggerXValueSpecular = 1;
  if(sd->scaleFactor.getValue()[0] == 0)
    sd->scaleFactor.setValue(0.01,1,1);
  rgbCube->draggerCallbackSpecular();
}
void cRgbCube::draggerYCallbackSpecular(void *classObject,SoDragger *dragger)
{
  cRgbCube *rgbCube = (cRgbCube *) classObject;
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerYValueSpecular = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerYValueSpecular > 1.0)
    rgbCube->draggerYValueSpecular = 1;
  if(sd->scaleFactor.getValue()[0] == 0)
    sd->scaleFactor.setValue(0.01,1,1);
  rgbCube->draggerCallbackSpecular();
}
void cRgbCube::draggerZCallbackSpecular(void *classObject,SoDragger *dragger)
{
  cRgbCube *rgbCube = (cRgbCube *) classObject;
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerZValueSpecular = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerZValueSpecular > 1.0)
    rgbCube->draggerZValueSpecular = 1;
  if(sd->scaleFactor.getValue()[0] == 0)
    sd->scaleFactor.setValue(0.01,1,1);
  rgbCube->draggerCallbackSpecular();
}
////////////////////-------------------------------------------------
void cRgbCube::draggerCallbackAmbient()
{
  updateCubeVertices(ambientColorCubeCoords,
		     ambientCubeMaterial,
		     draggerXValueAmbient,
		     draggerYValueAmbient,
		     draggerZValueAmbient);
  colorPatchMaterial->ambientColor.setValue(draggerXValueAmbient, 
					    draggerYValueAmbient, 
					    draggerZValueAmbient);
  updateColorValueText(draggerXValueAmbient,draggerYValueAmbient,draggerZValueAmbient);
}
void cRgbCube::draggerXCallbackAmbient(void *classObject,SoDragger *dragger)
{
  cRgbCube *rgbCube = (cRgbCube *) classObject;
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerXValueAmbient = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerXValueAmbient > 1.0)
    rgbCube->draggerXValueAmbient = 1;
  if(sd->scaleFactor.getValue()[0] == 0)
    sd->scaleFactor.setValue(0.01,1,1);
  rgbCube->draggerCallbackAmbient();
}
void cRgbCube::draggerYCallbackAmbient(void *classObject,SoDragger *dragger)
{
  cRgbCube *rgbCube = (cRgbCube *) classObject;
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerYValueAmbient = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerYValueAmbient > 1.0)
    rgbCube->draggerYValueAmbient = 1;
  if(sd->scaleFactor.getValue()[0] == 0)
    sd->scaleFactor.setValue(0.01,1,1);
  rgbCube->draggerCallbackAmbient();
}
void cRgbCube::draggerZCallbackAmbient(void *classObject,SoDragger *dragger)
{
  cRgbCube *rgbCube = (cRgbCube *) classObject;
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerZValueAmbient = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerZValueAmbient > 1.0)
    rgbCube->draggerZValueAmbient = 1;
  if(sd->scaleFactor.getValue()[0] == 0)
    sd->scaleFactor.setValue(0.01,1,1);
  rgbCube->draggerCallbackAmbient();
}

////////////////////-------------------------------------------------
void cRgbCube::draggerCallbackEmissive()
{
  updateCubeVertices(emissiveColorCubeCoords,
		     emissiveCubeMaterial,
		     draggerXValueEmissive,
		     draggerYValueEmissive,
		     draggerZValueEmissive);
  colorPatchMaterial->emissiveColor.setValue(draggerXValueEmissive, 
					     draggerYValueEmissive, 
					     draggerZValueEmissive);
  updateColorValueText(draggerXValueEmissive,draggerYValueEmissive,draggerZValueEmissive);
}
void cRgbCube::draggerXCallbackEmissive(void *classObject,SoDragger *dragger)
{
  cRgbCube *rgbCube = (cRgbCube *) classObject;
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerXValueEmissive = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerXValueEmissive > 1.0)
    rgbCube->draggerXValueEmissive = 1;
  if(sd->scaleFactor.getValue()[0] == 0)
    sd->scaleFactor.setValue(0.01,1,1);
  rgbCube->draggerCallbackEmissive();
}
void cRgbCube::draggerYCallbackEmissive(void *classObject,SoDragger *dragger)
{
  cRgbCube *rgbCube = (cRgbCube *) classObject;
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerYValueEmissive = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerYValueEmissive > 1.0)
    rgbCube->draggerYValueEmissive = 1;
  if(sd->scaleFactor.getValue()[0] == 0)
    sd->scaleFactor.setValue(0.01,1,1);
  rgbCube->draggerCallbackEmissive();
}
void cRgbCube::draggerZCallbackEmissive(void *classObject,SoDragger *dragger)
{
  cRgbCube *rgbCube = (cRgbCube *) classObject;
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerZValueEmissive = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerZValueEmissive > 1.0)
    rgbCube->draggerZValueEmissive = 1;
  if(sd->scaleFactor.getValue()[0] == 0)
    sd->scaleFactor.setValue(0.01,1,1);
  rgbCube->draggerCallbackEmissive();
}

////////////////////////////////////////////////////////////////

void cRgbCube::updateCubeVertices(SoCoordinate3 *cubeCoords,
				  SoMaterial *cubeMaterial,
				  float x,float y,float z)
{

  // X-face
  cubeCoords->point.set1Value(6, x*CUBE_SIZE_X, 
			      y*CUBE_SIZE_Y, 
			      z*CUBE_SIZE_Z);
  cubeCoords->point.set1Value(2, x*CUBE_SIZE_X, 
			      y*CUBE_SIZE_Y, 
			      0);
  cubeCoords->point.set1Value(1, x*CUBE_SIZE_X, 
			      0,
			      0);
  cubeCoords->point.set1Value(5, x*CUBE_SIZE_X, 
			      0,
			      z*CUBE_SIZE_Z);
  
  // Y-face
  cubeCoords->point.set1Value(3, 0, 
			      y*CUBE_SIZE_Y, 
			      0);
  cubeCoords->point.set1Value(7, 0, 
			      y*CUBE_SIZE_Y, 
			      z*CUBE_SIZE_Z);
  
  // Z-face
  cubeCoords->point.set1Value(7, 0, 
			      y*CUBE_SIZE_Y, 
			      z*CUBE_SIZE_Z);
  cubeCoords->point.set1Value(4, 0, 
			      0,
			      z*CUBE_SIZE_Z);
  
  
  cubeMaterial->diffuseColor.set1Value(1, x, 0, 0);
  cubeMaterial->diffuseColor.set1Value(2, x, y, 0);
  cubeMaterial->diffuseColor.set1Value(3, 0, y, 0);
  cubeMaterial->diffuseColor.set1Value(4, 0, 0, z);
  cubeMaterial->diffuseColor.set1Value(5, x, 0, z);
  cubeMaterial->diffuseColor.set1Value(6, x, y, z);
  cubeMaterial->diffuseColor.set1Value(7, 0, y, z);


  colorIndicatorPosition->translation.setValue(cubeCoords->point[6]);  

}

////////////////////////////////////////////////////////////////

void cRgbCube::initCubeFacelist(SoTransformSeparator *root, 
				SbVec3f *cubeVerts,
				SoCoordinate3 *cubeCoords,
				int32_t *cubeVertexIndices,
				SoMaterial *cubeMaterial)
{
  
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
 
  // Indexes
  cubeVertexIndices[0] = 3;
  cubeVertexIndices[1] = 2;
  cubeVertexIndices[2] = 1;
  cubeVertexIndices[3] = 0;
  cubeVertexIndices[4] = SO_END_FACE_INDEX;

  cubeVertexIndices[5] = 5;
  cubeVertexIndices[6] = 6;
  cubeVertexIndices[7] = 7;
  cubeVertexIndices[8] = 4;
  cubeVertexIndices[9] = SO_END_FACE_INDEX;

  cubeVertexIndices[10] = 4;
  cubeVertexIndices[11] = 7;
  cubeVertexIndices[12] = 3;
  cubeVertexIndices[13] = 0;
  cubeVertexIndices[14] = SO_END_FACE_INDEX;

  cubeVertexIndices[15] = 5;
  cubeVertexIndices[16] = 1;
  cubeVertexIndices[17] = 2;
  cubeVertexIndices[18] = 6;
  cubeVertexIndices[19] = SO_END_FACE_INDEX;

  cubeVertexIndices[20] = 7;
  cubeVertexIndices[21] = 6;
  cubeVertexIndices[22] = 2;
  cubeVertexIndices[23] = 3;
  cubeVertexIndices[24] = SO_END_FACE_INDEX;
  
  cubeVertexIndices[25] = 5;
  cubeVertexIndices[26] = 4;
  cubeVertexIndices[27] = 0;
  cubeVertexIndices[28] = 1;
  cubeVertexIndices[29] = SO_END_FACE_INDEX;
  
  cubeMaterial->diffuseColor.set1Value(0, 0,0,0);
  cubeMaterial->diffuseColor.set1Value(1, 1,0,0);
  cubeMaterial->diffuseColor.set1Value(2, 1,1,0);
  cubeMaterial->diffuseColor.set1Value(3, 0,1,0);
  
  cubeMaterial->diffuseColor.set1Value(4, 0,0,1);
  cubeMaterial->diffuseColor.set1Value(5, 1,0,1);
  cubeMaterial->diffuseColor.set1Value(6, 1,1,1);
  cubeMaterial->diffuseColor.set1Value(7, 0,1,1);
  


  // ColorCube + LineCube coordinates
  SoCoordinate3 *lineCubeCoords = new SoCoordinate3;
  lineCubeCoords->point.setValues(0,4*2,cubeVerts);
  cubeCoords->point.setValues(0,4*2,cubeVerts);


  // Cube faceset
  SoIndexedFaceSet *cubeIndexedFacelist = new SoIndexedFaceSet;
  cubeIndexedFacelist->coordIndex.setValues(0, 6*5, cubeVertexIndices);


  // Cube lineset
  SoIndexedLineSet *cubeLineList = new SoIndexedLineSet;
  cubeLineList->coordIndex.setValues(0, 6*5, cubeVertexIndices);
  SoMaterial *cubeLineMaterial = new SoMaterial;
  cubeLineMaterial->diffuseColor.set1Value(0,1,1,1);


  // Cube material
  SoMaterialBinding *cubeMatBind = new SoMaterialBinding;
  cubeMatBind->value = SoMaterialBinding::PER_VERTEX_INDEXED;

  
  // No lighting of color-cube
  SoLightModel *cubeLight = new SoLightModel;
  cubeLight->model = SoLightModel::BASE_COLOR;


  // Current color indicator
  SoSeparator *colorIndicatorRoot = new SoSeparator;

  SoMarkerSet *colorIndicator = new SoMarkerSet;
  colorIndicator->markerIndex = SoMarkerSet::CIRCLE_LINE_9_9;
  colorIndicator->numPoints = 1;

  SoBaseColor *colorIndicatorColor = new SoBaseColor;
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
  
  root->addChild(lineCubeCoords);
  root->addChild(cubeLineMaterial);
  root->addChild(cubeLineList);
  
  root->addChild(colorIndicatorRoot);

}

////////////////////////////////////////////////////////////////

void cRgbCube::initCubeDraggers(SoSeparator *root,
				SoScale1Dragger *draggerX,
				SoScale1Dragger *draggerY,
				SoScale1Dragger *draggerZ,
				SoDraggerCB *cb1, 
				SoDraggerCB *cb2, 
				SoDraggerCB *cb3, 
				float value1,float value2, float value3)
{

  draggerX->scaleFactor.setValue(value1,1,1);
  draggerY->scaleFactor.setValue(value2,1,1);
  draggerZ->scaleFactor.setValue(value3,1,1);
  
  draggerX->addMotionCallback(cb1,this);
  draggerY->addMotionCallback(cb2,this);
  draggerZ->addMotionCallback(cb3,this);

  SoTranslation *draggerXTrans = new SoTranslation;  
  SoTranslation *draggerYTrans = new SoTranslation;  
  SoTranslation *draggerZTrans = new SoTranslation;

  SoSeparator *sep = new SoSeparator;

  SoRotation *draggerXRotation = new SoRotation;
  SoRotation *draggerYRotation = new SoRotation;
  SoRotation *draggerZRotation = new SoRotation;

  draggerXRotation->rotation.setValue(0,1,1,0);
  draggerYRotation->rotation.setValue(1,0,1,0);
  draggerZRotation->rotation.setValue(1,1,0,0);

  draggerXTrans->translation.setValue( CUBE_SIZE_X/2, 0, CUBE_SIZE_Z+.2);
  draggerYTrans->translation.setValue(-CUBE_SIZE_X/2-.2, -CUBE_SIZE_Y-.2, CUBE_SIZE_Z/2+.1);
  draggerZTrans->translation.setValue(-CUBE_SIZE_X/2-.2, -CUBE_SIZE_Y/2-.2, 0);


  // Axis - Text
  SoFont *font = new SoFont;
  font->name.setValue("Times-Roman");
  font->size.setValue(44.0);
  root->addChild(font);

  SoPickStyle *pickStyle = new SoPickStyle;
  pickStyle->style = SoPickStyle::UNPICKABLE;

  SoTranslation *textTrans = new SoTranslation;
  textTrans->translation.setValue(0,.3,-.2);

  SoSeparator *textRedSep = new SoSeparator;
  SoSeparator *textGreenSep = new SoSeparator;
  SoSeparator *textBlueSep = new SoSeparator;

  SoBaseColor *textRedColor = new SoBaseColor;
  textRedColor->rgb.setValue(1,.4,.4);
  SoBaseColor *textGreenColor = new SoBaseColor;
  textGreenColor->rgb.setValue(.4,1,.4);
  SoBaseColor *textBlueColor = new SoBaseColor;
  textBlueColor->rgb.setValue(.4,.4,1);

  textRedSep->addChild(pickStyle);
  textRedSep->addChild(textRedColor);
  textRedSep->addChild(textTrans);
  textRedSep->addChild(textRedValue);      // Class variables. Initialized in 'initRgbCubeScene'

  
  textGreenSep->addChild(pickStyle);
  textGreenSep->addChild(textGreenColor);
  textGreenSep->addChild(textTrans);
  textGreenSep->addChild(textGreenValue);
  
  textBlueSep->addChild(pickStyle);
  textBlueSep->addChild(textBlueColor);
  textBlueSep->addChild(textTrans);
  textBlueSep->addChild(textBlueValue);

  
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

////////////////////////////////////////////////////////////////

void cRgbCube::initRadioButtons(SoSeparator *root)
{
  
  SoTranslation *startPos = new SoTranslation;
  startPos->translation.setValue(0,0,CUBE_SIZE_Z);

  SoTranslation *spacingX = new SoTranslation;
  spacingX->translation.setValue(.5,0,0);
  SoTranslation *spacingY = new SoTranslation;
  spacingY->translation.setValue(0,.5,0);
 
  SoText2 *textDiffuse = new SoText2;
  textDiffuse->string = "Diffuse";
  SoText2 *textSpecular = new SoText2;
  textSpecular->string = "Specular";
  SoText2 *textAmbient = new SoText2;
  textAmbient->string = "Ambient";
  SoText2 *textEmissive = new SoText2;
  textEmissive->string = "Emissive";

  SoCube *diffuseButton = new SoCube;
  SoCube *specularButton = new SoCube;
  SoCube *ambientButton = new SoCube;
  SoCube *emissiveButton = new SoCube;
 
  diffuseButtonColor = new SoBaseColor;
  ambientButtonColor = new SoBaseColor;
  specularButtonColor = new SoBaseColor;
  emissiveButtonColor = new SoBaseColor;

  diffuseButtonColor->rgb.setValue(0,1,1);
  ambientButtonColor->rgb.setValue(1,1,1);
  specularButtonColor->rgb.setValue(1,1,1);
  emissiveButtonColor->rgb.setValue(1,1,1);

  diffuseButton->height = RADIO_BUTTON_SIZE;
  diffuseButton->width = RADIO_BUTTON_SIZE;
  diffuseButton->depth = RADIO_BUTTON_SIZE;
  specularButton->height = RADIO_BUTTON_SIZE;
  specularButton->width = RADIO_BUTTON_SIZE;
  specularButton->depth = RADIO_BUTTON_SIZE;
  ambientButton->height = RADIO_BUTTON_SIZE;
  ambientButton->width = RADIO_BUTTON_SIZE;
  ambientButton->depth = RADIO_BUTTON_SIZE;
  emissiveButton->height = RADIO_BUTTON_SIZE;
  emissiveButton->width = RADIO_BUTTON_SIZE;
  emissiveButton->depth = RADIO_BUTTON_SIZE;

  SoSelection *s1 = new SoSelection;
  SoSelection *s2 = new SoSelection;
  SoSelection *s3 = new SoSelection;
  SoSelection *s4 = new SoSelection;
 
  s1->addSelectionCallback(radioButtonDiffuse,this);
  s2->addSelectionCallback(radioButtonSpecular,this);
  s3->addSelectionCallback(radioButtonAmbient,this);
  s4->addSelectionCallback(radioButtonEmissive,this);

  root->addChild(startPos);

  s1->addChild(diffuseButtonColor);
  s1->addChild(diffuseButton);
  s1->addChild(spacingX);
  s1->addChild(textDiffuse);
  root->addChild(s1);

  root->addChild(spacingY);

  s2->addChild(specularButtonColor);
  s2->addChild(specularButton);
  s2->addChild(spacingX);
  s2->addChild(textSpecular);
  root->addChild(s2);

  root->addChild(spacingY);

  s3->addChild(ambientButtonColor);
  s3->addChild(ambientButton);
  s3->addChild(spacingX);
  s3->addChild(textAmbient);
  root->addChild(s3);

  root->addChild(spacingY);

  s4->addChild(emissiveButtonColor);
  s4->addChild(emissiveButton);
  s4->addChild(spacingX);
  s4->addChild(textEmissive);
  root->addChild(s4);

}
////////////////////////////////////////////////////////////////

void cRgbCube::modifyDraggerWidget(SoScale1Dragger *dragger)
{
  
  SoSeparator *newDragger = new SoSeparator;
  newDragger->ref();

  SoSeparator *newDraggerActive = new SoSeparator;
  newDraggerActive->ref();

  // Optimize all drawing
  SoShapeHints *draggerHint = new SoShapeHints;
  draggerHint->vertexOrdering = SoShapeHints::COUNTERCLOCKWISE;
  draggerHint->shapeType = SoShapeHints::SOLID;
  newDragger->addChild(draggerHint);
  newDraggerActive->addChild(draggerHint);


  SoCylinder *tube = new SoCylinder;
  tube->radius=.05;
  SoRotationXYZ *tubeRot = new SoRotationXYZ;
  tubeRot->axis = SoRotationXYZ::Z;
  tubeRot->angle = 3.1415/2;

  // Passive dragger

  SoMaterial *passiveMat = new SoMaterial;
  passiveMat->diffuseColor.setValue(.7,.7,.7);
  newDragger->addChild(passiveMat);
  newDragger->addChild(tubeRot);
  newDragger->addChild(tube);

  // Active dragger

  SoMaterial *activeMat = new SoMaterial;
  activeMat->diffuseColor.setValue(0,1,1);
  newDraggerActive->addChild(activeMat);
  newDraggerActive->addChild(tubeRot);
  newDraggerActive->addChild(tube);

  // Scaler

  SoSeparator *newScaler = new SoSeparator;
  SoMaterial *scaleMat = new SoMaterial;
  scaleMat->diffuseColor.setValue(0,1,0);

  SoCube *cube1 = new SoCube; // Axis cross
  SoCube *cube2 = new SoCube;
  
  cube1->width = 0.0;
  cube1->height = .5;
  cube1->depth = .1;
  cube2->width = 0.0;
  cube2->height = .1;
  cube2->depth = .5;


  SoSphere *endPoint = new SoSphere;  // Endpoint ball
  endPoint->radius = .05;

  SoAntiSquish *antiSquish = new SoAntiSquish; // Keep aspect ratio!
  antiSquish->sizing = SoAntiSquish::Y;

  SoTranslation *endPointTrans1 = new SoTranslation;
  endPointTrans1->translation.setValue(-1,0,0);
  SoTranslation *endPointTrans2 = new SoTranslation;
  endPointTrans2->translation.setValue(1,0,0);

  SoSeparator *endPoint1Sep = new SoSeparator;
  SoSeparator *endPoint2Sep = new SoSeparator;

  
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

////////////////////////////////////////////////////////////////

void cRgbCube::initRgbCubeScene(int argc,char **argv)
{

  QWidget *widget = SoQt::init(argc,argv,argv[0]);
  eviewer = new SoQtExaminerViewer(widget);
  eviewer->setViewing(FALSE);

  sceneRoot = new SoSeparator;
  sceneRoot->ref();

  SoEventCallback *mouseCallback = new SoEventCallback;
  mouseCallback->addEventCallback(SoMouseButtonEvent::getClassTypeId(), &mouseClickCallback, this);
  sceneRoot->addChild(mouseCallback);
  rayPickAction = new SoRayPickAction(eviewer->getViewportRegion());

  colorIndicatorPosition = new SoTranslation;  // Translation object for colorpoint indicator '*'


  // Creating dragger-text objects
  textRedValue = new SoText2; 
  textGreenValue = new SoText2;
  textBlueValue = new SoText2;
  

  // Setup diffuse cube geometry
  diffuseDraggerX = new SoScale1Dragger;
  diffuseDraggerY = new SoScale1Dragger;
  diffuseDraggerZ = new SoScale1Dragger;
  
  // Modify dragger look
  modifyDraggerWidget(diffuseDraggerX);
  modifyDraggerWidget(diffuseDraggerY);
  modifyDraggerWidget(diffuseDraggerZ);

  diffuseCubeMaterial = new SoMaterial;
  diffuseCubeVertices = new SbVec3f[4*2];
  diffuseColorCubeCoords = new SoCoordinate3;
  diffuseCubeRoot = new SoTransformSeparator;
  initCubeFacelist(diffuseCubeRoot,
		   diffuseCubeVertices,
		   diffuseColorCubeCoords,
		   diffuseCubeVertexIndices,
		   diffuseCubeMaterial);
  SoSeparator *diffuseCubeRootDraggers = new SoSeparator;
  initCubeDraggers(diffuseCubeRootDraggers,
		   diffuseDraggerX,
		   diffuseDraggerY,
		   diffuseDraggerZ,
		   &draggerXCallbackDiffuse,
		   &draggerYCallbackDiffuse,
		   &draggerZCallbackDiffuse,draggerXValueDiffuse,draggerXValueDiffuse,draggerXValueDiffuse);
  diffuseCubeRoot->addChild(diffuseCubeRootDraggers);
  diffuseCubeRoot->ref();

  
  // Setup specular cube geometry
  specularDraggerX = new SoScale1Dragger;
  specularDraggerY = new SoScale1Dragger;
  specularDraggerZ = new SoScale1Dragger;

  // Modify dragger look
  modifyDraggerWidget(specularDraggerX);
  modifyDraggerWidget(specularDraggerY);
  modifyDraggerWidget(specularDraggerZ);

  specularCubeMaterial = new SoMaterial;
  specularCubeVertices = new SbVec3f[4*2];
  specularColorCubeCoords = new SoCoordinate3;
  specularCubeRoot = new SoTransformSeparator;
  initCubeFacelist(specularCubeRoot,
		   specularCubeVertices,
		   specularColorCubeCoords,
		   specularCubeVertexIndices,
		   specularCubeMaterial);
  SoSeparator *specularCubeRootDraggers = new SoSeparator;
  initCubeDraggers(specularCubeRootDraggers,
		   specularDraggerX,
		   specularDraggerY,
		   specularDraggerZ,
		   &draggerXCallbackSpecular,
		   &draggerYCallbackSpecular,
		   &draggerZCallbackSpecular,draggerXValueSpecular,draggerXValueSpecular,draggerXValueSpecular);
  specularCubeRoot->addChild(specularCubeRootDraggers);
  specularCubeRoot->ref();
  
  
  // Setup ambient cube geometry
  ambientDraggerX = new SoScale1Dragger;
  ambientDraggerY = new SoScale1Dragger;
  ambientDraggerZ = new SoScale1Dragger;

  // Modify dragger look
  modifyDraggerWidget(ambientDraggerX);
  modifyDraggerWidget(ambientDraggerY);
  modifyDraggerWidget(ambientDraggerZ);

  ambientCubeMaterial = new SoMaterial;
  ambientCubeVertices = new SbVec3f[4*2];
  ambientColorCubeCoords = new SoCoordinate3;
  ambientCubeRoot = new SoTransformSeparator;
  initCubeFacelist(ambientCubeRoot,
		   ambientCubeVertices,
		   ambientColorCubeCoords,
		   ambientCubeVertexIndices,
		   ambientCubeMaterial);
  SoSeparator *ambientCubeRootDraggers = new SoSeparator;
  initCubeDraggers(ambientCubeRootDraggers,
		   ambientDraggerX,
		   ambientDraggerY,
		   ambientDraggerZ,
		   &draggerXCallbackAmbient,
		   &draggerYCallbackAmbient,
		   &draggerZCallbackAmbient,draggerXValueAmbient,draggerXValueAmbient,draggerXValueAmbient);
  ambientCubeRoot->addChild(ambientCubeRootDraggers);
  ambientCubeRoot->ref();

  
  // Setup emissive cube geometry
  emissiveDraggerX = new SoScale1Dragger;
  emissiveDraggerY = new SoScale1Dragger;
  emissiveDraggerZ = new SoScale1Dragger;

  // Modify dragger look
  modifyDraggerWidget(emissiveDraggerX);
  modifyDraggerWidget(emissiveDraggerY);
  modifyDraggerWidget(emissiveDraggerZ);

  emissiveCubeMaterial = new SoMaterial;
  emissiveCubeVertices = new SbVec3f[4*2];
  emissiveColorCubeCoords = new SoCoordinate3;
  emissiveCubeRoot = new SoTransformSeparator;
  initCubeFacelist(emissiveCubeRoot,
		   emissiveCubeVertices,
		   emissiveColorCubeCoords,
		   emissiveCubeVertexIndices,
		   emissiveCubeMaterial);
  SoSeparator *emissiveCubeRootDraggers = new SoSeparator;
  initCubeDraggers(emissiveCubeRootDraggers,
		   emissiveDraggerX,
		   emissiveDraggerY,
		   emissiveDraggerZ,
		   &draggerXCallbackEmissive,
		   &draggerYCallbackEmissive,
		   &draggerZCallbackEmissive,draggerXValueEmissive,draggerXValueEmissive,draggerXValueEmissive);
  emissiveCubeRoot->addChild(emissiveCubeRootDraggers);
  updateCubeVertices(emissiveColorCubeCoords,     // Cube starts as <0,0,0> as default.
		     emissiveCubeMaterial,
		     draggerXValueEmissive,
		     draggerYValueEmissive,
		     draggerZValueEmissive);
  emissiveCubeRoot->ref();


  // ---- Create radiobuttons
  SoSeparator *buttonRoot = new SoSeparator;
  initRadioButtons(buttonRoot);
  

  // ---- Create color-patch for preview of selected color  

  colorPatchCube = new SoSwitch;
  colorPatchSphere = new SoSwitch;
  colorPatchCone = new SoSwitch;

  colorPatchSphere->whichChild = SO_SWITCH_ALL;

  SoSelection *colorPatchRoot = new SoSelection;
  colorPatchRoot->addSelectionCallback(colorPatchToggleCallback,this);

  SoShapeHints *colorPatchHint = new SoShapeHints;
  colorPatchHint->vertexOrdering = SoShapeHints::COUNTERCLOCKWISE;
  colorPatchHint->shapeType = SoShapeHints::SOLID;

  // No lighting of colorpatch
  SoLightModel *colorPatchLight = new SoLightModel;
  colorPatchLight->model = SoLightModel::PHONG;

  // Demonstration/preview entity.
  SoSphere *colorPatchTypeSphere = new SoSphere;
  SoCube *colorPatchTypeCube = new SoCube;
  SoCone *colorPatchTypeCone = new SoCone;
 
  colorPatchTypeCube->depth = 1.3;
  colorPatchTypeCube->height = 1.3;
  colorPatchTypeCube->width = 1.3;


  // Create patch-material
  colorPatchMaterial = new SoMaterial;
  colorPatchMaterial->diffuseColor.setValue(1,1,1); 
  
  // Transpose cube to the side
  SoTranslation *colorPatchTrans = new SoTranslation;
  colorPatchTrans->translation.setValue(CUBE_SIZE_X*2.2,CUBE_SIZE_Y/2,CUBE_SIZE_Z/2);
  
  // Build sub-scene graph for colorpatch/cube
  colorPatchRoot->addChild(colorPatchHint);
  colorPatchRoot->addChild(colorPatchLight);
  colorPatchRoot->addChild(colorPatchMaterial);
  colorPatchRoot->addChild(colorPatchTrans);

  colorPatchCube->addChild(colorPatchTypeCube);
  colorPatchSphere->addChild(colorPatchTypeSphere);
  colorPatchCone->addChild(colorPatchTypeCone);

  colorPatchRoot->addChild(colorPatchCube);
  colorPatchRoot->addChild(colorPatchSphere);
  colorPatchRoot->addChild(colorPatchCone);



  // ---- Create draggers for Shininess and transparency

  SoSeparator *draggersRoot = new SoSeparator;
  draggersRoot->ref();

  SoTranslation *startPosDraggers = new SoTranslation;
  startPosDraggers->translation.setValue(4*CUBE_SIZE_X,-CUBE_SIZE_Y*1.2,CUBE_SIZE_Z/2);

  SoScale1Dragger *draggerShininess = new SoScale1Dragger;
  SoScale1Dragger *draggerTransparency = new SoScale1Dragger;


  modifyDraggerWidget(draggerShininess);  // Give dragger a customized look
  modifyDraggerWidget(draggerTransparency);

  draggerShininess->addMotionCallback(&draggerShininessCallback,this);
  draggerTransparency->addMotionCallback(&draggerTransparencyCallback,this);

  draggerShininess->scaleFactor.setValue(1-0.2,1,1);  // Shininess is 0.2 as default
  
  SoTranslation *draggerShininessTrans = new SoTranslation;  
  SoTranslation *draggerTransparencyTrans = new SoTranslation;  
  draggerShininessTrans->translation.setValue(-CUBE_SIZE_X*2,0,0);
  draggerTransparencyTrans->translation.setValue(0,CUBE_SIZE_Y/2,0);


  SoSeparator *textSep1 = new SoSeparator;
  SoSeparator *textSep2 = new SoSeparator;
   
  textShininess = new SoText2;
  textShininess->string = "Shininess";
  textTransparency = new SoText2;
  textTransparency->string = "Opaque";

  SoTranslation *textTrans = new SoTranslation;
  textTrans->translation.setValue(0,.1,-.2);

  SoBaseColor *textColor = new SoBaseColor;
  textColor->rgb.setValue(.7,1,1);

  textSep1->addChild(textColor);
  textSep1->addChild(textTrans);
  textSep1->addChild(textShininess);

  textSep2->addChild(textColor);
  textSep2->addChild(textTrans);
  textSep2->addChild(textTransparency);

  draggersRoot->addChild(startPosDraggers);

  draggersRoot->addChild(draggerShininessTrans);
  draggersRoot->addChild(draggerShininess);
  draggersRoot->addChild(textSep1);

  draggersRoot->addChild(draggerTransparencyTrans);
  draggersRoot->addChild(draggerTransparency);
  draggersRoot->addChild(textSep2);
 
  // --------------------------------------------------


  SoTranslation *shiftCube = new SoTranslation;
  shiftCube->translation.setValue(0,CUBE_SIZE_Y*1.5,0);

  sceneRoot->addChild(buttonRoot);
  sceneRoot->addChild(shiftCube);

  sceneRoot->addChild(colorPatchRoot);
  //sceneRoot->addChild(rgbValueRoot);
  sceneRoot->addChild(draggersRoot);

  if(currentColorCube == COLOR_CUBE_DIFFUSE){
    sceneRoot->addChild(diffuseCubeRoot);
    draggerCallbackDiffuse();
  }
  
  if(currentColorCube == COLOR_CUBE_AMBIENT){
    sceneRoot->addChild(ambientCubeRoot);
    draggerCallbackAmbient();
  }
 
  if(currentColorCube == COLOR_CUBE_SPECULAR){
    sceneRoot->addChild(specularCubeRoot);
    draggerCallbackSpecular();
  }

  if(currentColorCube == COLOR_CUBE_EMISSIVE){
    sceneRoot->addChild(emissiveCubeRoot);
    draggerCallbackEmissive();
  }

  eviewer->setSceneGraph(sceneRoot);
  eviewer->setTitle("Coin Material Editor");
  eviewer->show(); 
 
  SoQt::show(widget);
  SoQt::mainLoop();

  sceneRoot->unref();

}

////////////////////////////////////////////////////////////////

int main(int argc,char **argv)
{

  cRgbCube *rgbCube = new cRgbCube();  
  rgbCube->initRgbCubeScene(argc,argv);

  return 0; 

}  

////////////////////////////////////////////////////////////////
