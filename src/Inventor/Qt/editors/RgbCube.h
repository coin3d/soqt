

#define COLOR_CUBE_DIFFUSE   0
#define COLOR_CUBE_AMBIENT   1
#define COLOR_CUBE_SPECULAR  2
#define COLOR_CUBE_EMISSIVE  3

#define COLOR_PATCH_SPHERE   0
#define COLOR_PATCH_CUBE     1
#define COLOR_PATCH_CONE     2

#define RADIO_BUTTON_SIZE .2

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

  SoScale1Dragger *diffuseDraggerX;
  SoScale1Dragger *diffuseDraggerY;
  SoScale1Dragger *diffuseDraggerZ;

  SoScale1Dragger *specularDraggerX;
  SoScale1Dragger *specularDraggerY;
  SoScale1Dragger *specularDraggerZ;

  SoScale1Dragger *ambientDraggerX;
  SoScale1Dragger *ambientDraggerY;
  SoScale1Dragger *ambientDraggerZ;

  SoScale1Dragger *emissiveDraggerX;
  SoScale1Dragger *emissiveDraggerY;
  SoScale1Dragger *emissiveDraggerZ;

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
  SoSwitch *colorPatchCube;               // Switch for color patch type
  SoSwitch *colorPatchSphere;               // Switch for color patch type
  SoSwitch *colorPatchCone;               // Switch for color patch type


  SoQtExaminerViewer *eviewer;
  SoRayPickAction *rayPickAction;


  SoText2 *textShininess; 
  SoText2 *textTransparency;

  SoText2 *textRedValue;
  SoText2 *textGreenValue;
  SoText2 *textBlueValue;


  SbVec3f *diffuseCubeVertices;
  int32_t diffuseCubeVertexIndices[6*5];

  SbVec3f *specularCubeVertices;
  int32_t specularCubeVertexIndices[6*5];

  SbVec3f *ambientCubeVertices;
  int32_t ambientCubeVertexIndices[6*5];

  SbVec3f *emissiveCubeVertices;
  int32_t emissiveCubeVertexIndices[6*5];


  int currentColorCube;     // What is currently beeing adjusted?
  int currentColorPatch;    // Cube or sphere as demonstration?

  // ---

  cRgbCube();
  ~cRgbCube();

  void initRadioButtons(SoSeparator *root);

  void initCubeFacelist(SoTransformSeparator *root, 
			SbVec3f *cubeVertices,
			SoCoordinate3 *colorCubeCoords,
			int32_t *cubeVertexIndices,
			SoMaterial *cubeMaterial);

  void initCubeDraggers(SoSeparator *root, 
			SoScale1Dragger *draggerX,
			SoScale1Dragger *draggerY,
			SoScale1Dragger *draggerZ,
			SoDraggerCB *cb1, 
			SoDraggerCB *cb2, 
			SoDraggerCB *cb3,
			float value1,float value2,float value3);

  void initRgbCubeScene(int argc,char **argv);

  void updateCubeVertices(SoCoordinate3 *colorCubeCoords, 
			  SoMaterial *cubeMaterial,
			  float x,float y,float z); 

  void modifyDraggerWidget(SoScale1Dragger *dragger);


  // --- Methods called by callback statics

  void updateColorValueText(float red, float green, float blue);

  void draggerCallbackDiffuse();
  void draggerCallbackSpecular();
  void draggerCallbackAmbient();
  void draggerCallbackEmissive();

  void removeCurrentColorCube();

  // --- Static Callbacks

  static void colorPatchToggleCallback(void *classObject,SoPath *selectionPath);
  static void mouseClickCallback(void *classObject, SoEventCallback *cb);

  static void draggerShininessCallback(void *classObject,SoDragger *dragger);

  static void draggerXCallbackDiffuse(void *classObject,SoDragger *dragger);
  static void draggerYCallbackDiffuse(void *classObject,SoDragger *dragger);
  static void draggerZCallbackDiffuse(void *classObject,SoDragger *dragger);

  static void draggerXCallbackAmbient(void *classObject,SoDragger *dragger);
  static void draggerYCallbackAmbient(void *classObject,SoDragger *dragger);
  static void draggerZCallbackAmbient(void *classObject,SoDragger *dragger);

  static void draggerXCallbackSpecular(void *classObject,SoDragger *dragger);
  static void draggerYCallbackSpecular(void *classObject,SoDragger *dragger);
  static void draggerZCallbackSpecular(void *classObject,SoDragger *dragger);

  static void draggerXCallbackEmissive(void *classObject,SoDragger *dragger);
  static void draggerYCallbackEmissive(void *classObject,SoDragger *dragger);
  static void draggerZCallbackEmissive(void *classObject,SoDragger *dragger);

};
