

#define COLOR_CUBE_DIFFUSE   0
#define COLOR_CUBE_AMBIENT   1
#define COLOR_CUBE_SPECULAR  2
#define COLOR_CUBE_EMISSIVE  3

class cRgbCube {
  

public:

  float draggerXValueDiffuse;
  float draggerYValueDiffuse;
  float draggerZValueDiffuse;

  float draggerXValueSpecular;
  float draggerYValueSpecular;
  float draggerZValueSpecular;

  float draggerXValueAmbient;
  float draggerYValueAmbient;
  float draggerZValueAmbient;

  float draggerXValueEmissive;
  float draggerYValueEmissive;
  float draggerZValueEmissive;

  SoSeparator *sceneRoot;

  SoMaterial *diffuseCubeMaterial;
  SoCoordinate3 *diffuseColorCubeCoords;
  SoMaterial *specularCubeMaterial;
  SoCoordinate3 *specularColorCubeCoords;
  SoMaterial *ambientCubeMaterial;
  SoCoordinate3 *ambientColorCubeCoords;
  SoMaterial *emissiveCubeMaterial;
  SoCoordinate3 *emissiveColorCubeCoords;

  SoTransformSeparator *diffuseCubeRoot;
  SoTransformSeparator *ambientCubeRoot;
  SoTransformSeparator *specularCubeRoot;
  SoTransformSeparator *emissiveCubeRoot;

  SoBaseColor *diffuseButtonColor;
  SoBaseColor *ambientButtonColor;
  SoBaseColor *specularButtonColor;
  SoBaseColor *emissiveButtonColor;

  SoTranslation *colorIndicatorPosition;
  SoMaterial *colorPatchMaterial;

  SbVec3f *diffuseCubeVertices;
  int32_t diffuseCubeVertexIndices[6*5];

  SbVec3f *specularCubeVertices;
  int32_t specularCubeVertexIndices[6*5];

  SbVec3f *ambientCubeVertices;
  int32_t ambientCubeVertexIndices[6*5];

  SbVec3f *emissiveCubeVertices;
  int32_t emissiveCubeVertexIndices[6*5];

  int currentColorCube;

  cRgbCube();
  ~cRgbCube();

  void initRadioButtons(SoSeparator *root);

  void initCubeFacelist(SoTransformSeparator *root, 
			SbVec3f *cubeVertices,
			SoCoordinate3 *colorCubeCoords,
			int32_t *cubeVertexIndices,
			SoMaterial *cubeMaterial);

  void initCubeDraggers(SoSeparator *root, 
			SoDraggerCB *cb1, 
			SoDraggerCB *cb2, 
			SoDraggerCB *cb3,
			float value1,float value2,float value3);

  void initRgbCubeScene(int argc,char **argv);

  void updateCubeVertices(SoCoordinate3 *colorCubeCoords, 
			  SoMaterial *cubeMaterial,
			  float x,float y,float z); 

};
