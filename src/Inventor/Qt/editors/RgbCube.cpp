
/**
   Et enkelt RGB-Cube eksperiment
   2002 - Øystein
*/

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>

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

#include "RgbCube.h"


#define CUBE_SIZE_X 2
#define CUBE_SIZE_Y 2
#define CUBE_SIZE_Z 2

#define SIDE_X 0
#define SIDE_Y 1
#define SIDE_Z 2


cRgbCube *rgbCube;

////////////////////////////////////////////////////////////////

cRgbCube::cRgbCube()
{
  draggerXValueDiffuse = 1;
  draggerYValueDiffuse = 1;
  draggerZValueDiffuse = 1;

  draggerXValueSpecular = 1;
  draggerYValueSpecular = 1;
  draggerZValueSpecular = 1;

  draggerXValueAmbient = 1;
  draggerYValueAmbient = 1;
  draggerZValueAmbient = 1;

  draggerXValueEmissive = 0;
  draggerYValueEmissive = 0;
  draggerZValueEmissive = 0;

  currentColorCube = COLOR_CUBE_DIFFUSE;

}
cRgbCube::~cRgbCube()
{
}

////////////////////////////////////////////////////////////////
static void removeCurrentColorCube()
{

  switch(rgbCube->currentColorCube){
  case COLOR_CUBE_DIFFUSE:
    rgbCube->sceneRoot->removeChild(rgbCube->diffuseCubeRoot);
    break;
  case COLOR_CUBE_AMBIENT:
    rgbCube->sceneRoot->removeChild(rgbCube->ambientCubeRoot);
    break;
  case COLOR_CUBE_SPECULAR:
    rgbCube->sceneRoot->removeChild(rgbCube->specularCubeRoot);
    break;
  case COLOR_CUBE_EMISSIVE:
    rgbCube->sceneRoot->removeChild(rgbCube->emissiveCubeRoot);
    break;
  }

  rgbCube->diffuseButtonColor->rgb.setValue(1,1,1);
  rgbCube->ambientButtonColor->rgb.setValue(1,1,1);
  rgbCube->specularButtonColor->rgb.setValue(1,1,1); 
  rgbCube->emissiveButtonColor->rgb.setValue(1,1,1); 
}
////////////////////////////////////////////////////////////////
static void radioButtonDiffuse(void *,SoPath *selectionPath)
{
  if(rgbCube->currentColorCube == COLOR_CUBE_DIFFUSE) return;
  removeCurrentColorCube();
  rgbCube->diffuseButtonColor->rgb.setValue(0,1,1);
  rgbCube->currentColorCube = COLOR_CUBE_DIFFUSE;
  rgbCube->sceneRoot->addChild(rgbCube->diffuseCubeRoot);
}
static void radioButtonAmbient(void *,SoPath *selectionPath)
{
  if(rgbCube->currentColorCube == COLOR_CUBE_AMBIENT) return;
  removeCurrentColorCube();
  rgbCube->ambientButtonColor->rgb.setValue(0,1,1);
  rgbCube->currentColorCube = COLOR_CUBE_AMBIENT;
  rgbCube->sceneRoot->addChild(rgbCube->ambientCubeRoot);
}
static void radioButtonSpecular(void *,SoPath *selectionPath)
{
  if(rgbCube->currentColorCube == COLOR_CUBE_SPECULAR) return;
  removeCurrentColorCube();
  rgbCube->specularButtonColor->rgb.setValue(0,1,1);
  rgbCube->currentColorCube = COLOR_CUBE_SPECULAR;
  rgbCube->sceneRoot->addChild(rgbCube->specularCubeRoot);
}
static void radioButtonEmissive(void *,SoPath *selectionPath)
{
  if(rgbCube->currentColorCube == COLOR_CUBE_EMISSIVE) return;
  removeCurrentColorCube();
  rgbCube->emissiveButtonColor->rgb.setValue(0,1,1);
  rgbCube->currentColorCube = COLOR_CUBE_EMISSIVE;
  rgbCube->sceneRoot->addChild(rgbCube->emissiveCubeRoot);
}
////////////////////////////////////////////////////////////////

static void draggerShininessCallback(void *,SoDragger *dragger)
{
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->colorPatchMaterial->shininess = 1 - sd->scaleFactor.getValue()[0];
}

static void draggerTransparencyCallback(void *,SoDragger *dragger)
{
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->colorPatchMaterial->transparency = 1 - sd->scaleFactor.getValue()[0];  
}
//////////////////////-------------------------------------------
static void draggerXCallbackDiffuse(void *,SoDragger *dragger)
{
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerXValueDiffuse = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerXValueDiffuse > 1.0)
    rgbCube->draggerXValueDiffuse = 1;
  rgbCube->updateCubeVertices(rgbCube->diffuseColorCubeCoords,
			      rgbCube->diffuseCubeMaterial,
			      rgbCube->draggerXValueDiffuse,rgbCube->draggerYValueDiffuse,rgbCube->draggerZValueDiffuse);
  rgbCube->colorPatchMaterial->diffuseColor.setValue(rgbCube->draggerXValueDiffuse, 
						     rgbCube->draggerYValueDiffuse, 
						     rgbCube->draggerZValueDiffuse);
}
static void draggerYCallbackDiffuse(void *,SoDragger *dragger)
{
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerYValueDiffuse = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerYValueDiffuse > 1.0)
    rgbCube->draggerYValueDiffuse = 1;
  rgbCube->updateCubeVertices(rgbCube->diffuseColorCubeCoords,
			      rgbCube->diffuseCubeMaterial,
			      rgbCube->draggerXValueDiffuse,rgbCube->draggerYValueDiffuse,rgbCube->draggerZValueDiffuse);
  rgbCube->colorPatchMaterial->diffuseColor.setValue(rgbCube->draggerXValueDiffuse, 
						     rgbCube->draggerYValueDiffuse, 
						     rgbCube->draggerZValueDiffuse);
}
static void draggerZCallbackDiffuse(void *,SoDragger *dragger)
{
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerZValueDiffuse = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerZValueDiffuse > 1.0)
    rgbCube->draggerZValueDiffuse = 1;
  rgbCube->updateCubeVertices(rgbCube->diffuseColorCubeCoords,
			      rgbCube->diffuseCubeMaterial,
			      rgbCube->draggerXValueDiffuse,
			      rgbCube->draggerYValueDiffuse,
			      rgbCube->draggerZValueDiffuse);
  rgbCube->colorPatchMaterial->diffuseColor.setValue(rgbCube->draggerXValueDiffuse, 
						     rgbCube->draggerYValueDiffuse, 
						     rgbCube->draggerZValueDiffuse);
}
////////////////////-------------------------------------------------
static void draggerXCallbackSpecular(void *,SoDragger *dragger)
{
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerXValueSpecular = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerXValueSpecular > 1.0)
    rgbCube->draggerXValueSpecular = 1;
  rgbCube->updateCubeVertices(rgbCube->specularColorCubeCoords,
			      rgbCube->specularCubeMaterial,
			      rgbCube->draggerXValueSpecular,
			      rgbCube->draggerYValueSpecular,
			      rgbCube->draggerZValueSpecular);
  rgbCube->colorPatchMaterial->specularColor.setValue(rgbCube->draggerXValueSpecular, 
						      rgbCube->draggerYValueSpecular, 
						      rgbCube->draggerZValueSpecular);
}
static void draggerYCallbackSpecular(void *,SoDragger *dragger)
{
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerYValueSpecular = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerYValueSpecular > 1.0)
    rgbCube->draggerYValueSpecular = 1;
  rgbCube->updateCubeVertices(rgbCube->specularColorCubeCoords,
			      rgbCube->specularCubeMaterial,
			      rgbCube->draggerXValueSpecular,
			      rgbCube->draggerYValueSpecular,
			      rgbCube->draggerZValueSpecular);
  rgbCube->colorPatchMaterial->specularColor.setValue(rgbCube->draggerXValueSpecular, 
						      rgbCube->draggerYValueSpecular, 
						      rgbCube->draggerZValueSpecular);
}
static void draggerZCallbackSpecular(void *,SoDragger *dragger)
{
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerZValueSpecular = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerZValueSpecular > 1.0)
    rgbCube->draggerZValueSpecular = 1;
  rgbCube->updateCubeVertices(rgbCube->specularColorCubeCoords,
			      rgbCube->specularCubeMaterial,
			      rgbCube->draggerXValueSpecular,
			      rgbCube->draggerYValueSpecular,
			      rgbCube->draggerZValueSpecular);
  rgbCube->colorPatchMaterial->specularColor.setValue(rgbCube->draggerXValueSpecular, 
						      rgbCube->draggerYValueSpecular, 
						      rgbCube->draggerZValueSpecular);
}
////////////////////-------------------------------------------------
static void draggerXCallbackAmbient(void *,SoDragger *dragger)
{
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerXValueAmbient = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerXValueAmbient > 1.0)
    rgbCube->draggerXValueAmbient = 1;
  rgbCube->updateCubeVertices(rgbCube->ambientColorCubeCoords,
			      rgbCube->ambientCubeMaterial,
			      rgbCube->draggerXValueAmbient,
			      rgbCube->draggerYValueAmbient,
			      rgbCube->draggerZValueAmbient);
  rgbCube->colorPatchMaterial->ambientColor.setValue(rgbCube->draggerXValueAmbient, 
						     rgbCube->draggerYValueAmbient, 
						     rgbCube->draggerZValueAmbient);
}
static void draggerYCallbackAmbient(void *,SoDragger *dragger)
{
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerYValueAmbient = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerYValueAmbient > 1.0)
    rgbCube->draggerYValueAmbient = 1;
  rgbCube->updateCubeVertices(rgbCube->ambientColorCubeCoords,
			      rgbCube->ambientCubeMaterial,
			      rgbCube->draggerXValueAmbient,
			      rgbCube->draggerYValueAmbient,
			      rgbCube->draggerZValueAmbient);
  rgbCube->colorPatchMaterial->ambientColor.setValue(rgbCube->draggerXValueAmbient, 
						     rgbCube->draggerYValueAmbient, 
						     rgbCube->draggerZValueAmbient);
}
static void draggerZCallbackAmbient(void *,SoDragger *dragger)
{
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerZValueAmbient = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerZValueAmbient > 1.0)
    rgbCube->draggerZValueAmbient = 1;
  rgbCube->updateCubeVertices(rgbCube->ambientColorCubeCoords,
			      rgbCube->ambientCubeMaterial,
			      rgbCube->draggerXValueAmbient,
			      rgbCube->draggerYValueAmbient,
			      rgbCube->draggerZValueAmbient);
  rgbCube->colorPatchMaterial->ambientColor.setValue(rgbCube->draggerXValueAmbient, 
						     rgbCube->draggerYValueAmbient, 
						     rgbCube->draggerZValueAmbient);
}

////////////////////-------------------------------------------------
static void draggerXCallbackEmissive(void *,SoDragger *dragger)
{
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerXValueEmissive = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerXValueEmissive > 1.0)
    rgbCube->draggerXValueEmissive = 1;
  rgbCube->updateCubeVertices(rgbCube->emissiveColorCubeCoords,
			      rgbCube->emissiveCubeMaterial,
			      rgbCube->draggerXValueEmissive,
			      rgbCube->draggerYValueEmissive,
			      rgbCube->draggerZValueEmissive);
  rgbCube->colorPatchMaterial->emissiveColor.setValue(rgbCube->draggerXValueEmissive, 
						     rgbCube->draggerYValueEmissive, 
						     rgbCube->draggerZValueEmissive);
}
static void draggerYCallbackEmissive(void *,SoDragger *dragger)
{
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerYValueEmissive = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerYValueEmissive > 1.0)
    rgbCube->draggerYValueEmissive = 1;
  rgbCube->updateCubeVertices(rgbCube->emissiveColorCubeCoords,
			      rgbCube->emissiveCubeMaterial,
			      rgbCube->draggerXValueEmissive,
			      rgbCube->draggerYValueEmissive,
			      rgbCube->draggerZValueEmissive);
  rgbCube->colorPatchMaterial->emissiveColor.setValue(rgbCube->draggerXValueEmissive, 
						     rgbCube->draggerYValueEmissive, 
						     rgbCube->draggerZValueEmissive);
}
static void draggerZCallbackEmissive(void *,SoDragger *dragger)
{
  SoScale1Dragger * sd = (SoScale1Dragger *)dragger;
  rgbCube->draggerZValueEmissive = sd->scaleFactor.getValue()[0];
  if(rgbCube->draggerZValueEmissive > 1.0)
    rgbCube->draggerZValueEmissive = 1;
  rgbCube->updateCubeVertices(rgbCube->emissiveColorCubeCoords,
			      rgbCube->emissiveCubeMaterial,
			      rgbCube->draggerXValueEmissive,
			      rgbCube->draggerYValueEmissive,
			      rgbCube->draggerZValueEmissive);
  rgbCube->colorPatchMaterial->emissiveColor.setValue(rgbCube->draggerXValueEmissive, 
						     rgbCube->draggerYValueEmissive, 
						     rgbCube->draggerZValueEmissive);
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

  //colorIndicatorPosition->translation.setValue(cubeCoords->point[6]);  
  colorIndicatorPosition->translation.setValue(x*CUBE_SIZE_X,y*CUBE_SIZE_Y,z*CUBE_SIZE_Z);
 
}

////////////////////////////////////////////////////////////////

void cRgbCube::initCubeFacelist(SoTransformSeparator *root, 
				SbVec3f *cubeVerts,
				SoCoordinate3 *cubeCoords,
				int32_t *cubeVertexIndices,
				SoMaterial *cubeMaterial)
{
  
  //cubeVertices = new SbVec3f[4*2];

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
  SoText2 *colorIndicator = new SoText2;
  colorIndicator->string = "O";
  SoBaseColor *colorIndicatorColor = new SoBaseColor;
  colorIndicatorColor->rgb.setValue(1,0,0);
  colorIndicatorRoot = new SoSeparator;
  colorIndicatorPosition = new SoTranslation;
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
				SoDraggerCB *cb1, 
				SoDraggerCB *cb2, 
				SoDraggerCB *cb3, 
				float value1,float value2, float value3)
{

  SoScale1Dragger *draggerX = new SoScale1Dragger;
  SoScale1Dragger *draggerY = new SoScale1Dragger;
  SoScale1Dragger *draggerZ = new SoScale1Dragger;

  /*
  draggerX->scaleFactor.setValue(value1,0,0);
  draggerY->scaleFactor.setValue(value2,0,0);
  draggerZ->scaleFactor.setValue(value3,0,0);
  */

  draggerX->addMotionCallback(cb1,NULL);
  draggerY->addMotionCallback(cb2,NULL);
  draggerZ->addMotionCallback(cb3,NULL);

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

  SoText2 *textRed = new SoText2;
  textRed->string = "Red";
  SoText2 *textGreen = new SoText2;
  textGreen->string = "Green";
  SoText2 *textBlue = new SoText2;
  textBlue->string = "Blue";

  SoBaseColor *textRedColor = new SoBaseColor;
  textRedColor->rgb.setValue(1,0,0);
  SoBaseColor *textGreenColor = new SoBaseColor;
  textGreenColor->rgb.setValue(0,1,0);
  SoBaseColor *textBlueColor = new SoBaseColor;
  textBlueColor->rgb.setValue(0,0,1);

  root->addChild(sep);

  root->addChild(draggerXTrans);
  root->addChild(draggerXRotation);
  root->addChild(draggerX);
  root->addChild(textRedColor);
  root->addChild(textRed);

  root->addChild(sep);
  
  root->addChild(draggerYTrans);
  root->addChild(draggerYRotation);
  root->addChild(draggerY);
  root->addChild(textGreenColor);
  root->addChild(textGreen);

  root->addChild(sep);

  root->addChild(draggerZTrans);
  root->addChild(draggerZRotation);
  root->addChild(draggerZ);
  root->addChild(textBlueColor);
  root->addChild(textBlue);

}

////////////////////////////////////////////////////////////////

void cRgbCube::initRadioButtons(SoSeparator *root)
{
  
#define BUTTON_SIZE .2

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

  diffuseButton->height = BUTTON_SIZE;
  diffuseButton->width = BUTTON_SIZE;
  diffuseButton->depth = BUTTON_SIZE;
  specularButton->height = BUTTON_SIZE;
  specularButton->width = BUTTON_SIZE;
  specularButton->depth = BUTTON_SIZE;
  ambientButton->height = BUTTON_SIZE;
  ambientButton->width = BUTTON_SIZE;
  ambientButton->depth = BUTTON_SIZE;
  emissiveButton->height = BUTTON_SIZE;
  emissiveButton->width = BUTTON_SIZE;
  emissiveButton->depth = BUTTON_SIZE;

  SoSelection *s1 = new SoSelection;
  SoSelection *s2 = new SoSelection;
  SoSelection *s3 = new SoSelection;
  SoSelection *s4 = new SoSelection;
 
  s1->addSelectionCallback(radioButtonDiffuse,NULL);
  s2->addSelectionCallback(radioButtonSpecular,NULL);
  s3->addSelectionCallback(radioButtonAmbient,NULL);
  s4->addSelectionCallback(radioButtonEmissive,NULL);


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

void cRgbCube::initRgbCubeScene(int argc,char **argv)
{

  QWidget *widget = SoQt::init(argc,argv,argv[0]);
  SoQtExaminerViewer *eviewer = new SoQtExaminerViewer(widget);

  sceneRoot = new SoSeparator;
  sceneRoot->ref();

  // Setup diffuse cube geometry
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
		   &draggerXCallbackDiffuse,
		   &draggerYCallbackDiffuse,
		   &draggerZCallbackDiffuse,1,1,1);
  diffuseCubeRoot->addChild(diffuseCubeRootDraggers);
  diffuseCubeRoot->ref();

  
  // Setup specular cube geometry
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
		   &draggerXCallbackSpecular,
		   &draggerYCallbackSpecular,
		   &draggerZCallbackSpecular,1,1,1);
  specularCubeRoot->addChild(specularCubeRootDraggers);
  specularCubeRoot->ref();
  
  
  // Setup ambient cube geometry
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
		   &draggerXCallbackAmbient,
		   &draggerYCallbackAmbient,
		   &draggerZCallbackAmbient,1,1,1);
  ambientCubeRoot->addChild(ambientCubeRootDraggers);
  ambientCubeRoot->ref();

  
  // Setup emissive cube geometry
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
		   &draggerXCallbackEmissive,
		   &draggerYCallbackEmissive,
		   &draggerZCallbackEmissive,0.1,0.1,0.1);
  emissiveCubeRoot->addChild(emissiveCubeRootDraggers);
  emissiveCubeRoot->ref();


  // ---- Create radiobuttons
  SoSeparator *buttonRoot = new SoSeparator;
  initRadioButtons(buttonRoot);
  

  // ---- Create color-patch for preview of selected color  
  SoSeparator *colorPatchRoot = new SoSeparator;
  colorPatchRoot->ref();

  SoShapeHints *colorPatchHint = new SoShapeHints;
  colorPatchHint->vertexOrdering = SoShapeHints::COUNTERCLOCKWISE;
  colorPatchHint->shapeType = SoShapeHints::SOLID;

  // No lighting of colorpatch
  SoLightModel *colorPatchLight = new SoLightModel;
  colorPatchLight->model = SoLightModel::PHONG;

  // Demonstration/preview entity.
  SoSphere *colorPatchCube = new SoSphere;

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
  colorPatchRoot->addChild(colorPatchCube);


  // ---- Create draggers for Shininess and transparency

  SoSeparator *draggersRoot = new SoSeparator;
  draggersRoot->ref();

  SoTranslation *startPosDraggers = new SoTranslation;
  startPosDraggers->translation.setValue(4*CUBE_SIZE_X,-CUBE_SIZE_Y*1.1,CUBE_SIZE_Z/2);

  SoScale1Dragger *draggerShininess = new SoScale1Dragger;
  SoScale1Dragger *draggerTransparency = new SoScale1Dragger;
  
  draggerShininess->addMotionCallback(&draggerShininessCallback,NULL);
  draggerTransparency->addMotionCallback(&draggerTransparencyCallback,NULL);

  SoTranslation *draggerShininessTrans = new SoTranslation;  
  SoTranslation *draggerTransparencyTrans = new SoTranslation;  
  draggerShininessTrans->translation.setValue(-CUBE_SIZE_X*2,0,0);
  draggerTransparencyTrans->translation.setValue(0,CUBE_SIZE_Y/2,0);
   
  SoText2 *textShininess = new SoText2;
  textShininess->string = "Shininess";
  SoText2 *textTransparency = new SoText2;
  textTransparency->string = "Opaque";

  SoBaseColor *textColor = new SoBaseColor;
  textColor->rgb.setValue(1,1,1);

  draggersRoot->addChild(startPosDraggers);

  draggersRoot->addChild(textColor);
  draggersRoot->addChild(draggerShininessTrans);
  draggersRoot->addChild(draggerShininess);
  draggersRoot->addChild(textShininess);

  draggersRoot->addChild(draggerTransparencyTrans);
  draggersRoot->addChild(draggerTransparency);
  draggersRoot->addChild(textTransparency);

 
  // --------------------------------------------------


  SoTranslation *shiftCube = new SoTranslation;
  shiftCube->translation.setValue(0,CUBE_SIZE_Y*1.5,0);

  sceneRoot->addChild(buttonRoot);
  sceneRoot->addChild(shiftCube);

  sceneRoot->addChild(colorPatchRoot);
  sceneRoot->addChild(draggersRoot);

  if(currentColorCube == COLOR_CUBE_DIFFUSE)
    sceneRoot->addChild(diffuseCubeRoot);
  
  if(currentColorCube == COLOR_CUBE_AMBIENT)
    sceneRoot->addChild(ambientCubeRoot);
 
  if(currentColorCube == COLOR_CUBE_SPECULAR)
    sceneRoot->addChild(specularCubeRoot);

  if(currentColorCube == COLOR_CUBE_EMISSIVE)
    sceneRoot->addChild(emissiveCubeRoot);


  eviewer->setSceneGraph(sceneRoot);
  eviewer->setTitle("RGB-cube color chooser");
  eviewer->show(); 
 
  SoQt::show(widget);
  SoQt::mainLoop();

  sceneRoot->unref();

}

////////////////////////////////////////////////////////////////

int main(int argc,char **argv)
{

  std::cout << "- RgbCube v0.1, Øystein\n";

  rgbCube = new cRgbCube();  
  rgbCube->initRgbCubeScene(argc,argv);

  return 0; 

}  

////////////////////////////////////////////////////////////////
