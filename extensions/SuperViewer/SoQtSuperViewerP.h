/**************************************************************************
 *
 *  This file is part of the Coin SoQt GUI binding library.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License version
 *  2.1 as published by the Free Software Foundation.  See the file
 *  LICENSE.LGPL at the root directory of the distribution for all the
 *  details.
 *
 *  If you want to use Coin SoQt for applications not compatible with the
 *  LGPL, please contact SIM to acquire a Professional Edition License.
 *
 *  Systems in Motion, Prof Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
 **************************************************************************/

#ifndef SOQT_SUPERVIEWERP_H
#define SOQT_SUPERVIEWERP_H

#include <Inventor/Qt/viewers/SoQtViewer.h>

class QMenuBar;
class QWidget;
class QPopupMenu;
class QCursor;
class QLabel;
class SoSeparator;
class SbStringList;
class SbIntList;
class SoComplexity;
class SoDrawStyle;
class SoLightModel;
class SoBaseColor;
class SoMaterialBinding;
class SoNormal;
class SoNormalBinding;
class SoSwitch;
class SoLight;
class SoPolygonOffset;
class SoIndexedLineSet;
class SoVertexProperty;
class SoShapeHints;
class SoSearchAction;
class SoGetPrimitiveCountAction;
class SoGetBoundingBoxAction;
class SoFieldSensor;
class SoQtSuperViewer;

//*************************************************************************

class SoQtSuperViewerP : QObject{
  Q_OBJECT

 public:
  SoQtSuperViewerP(SoQtSuperViewer * o);
  ~SoQtSuperViewerP(void);

  // Variables used for the Qt part of the viewer
  QWidget * viewerwidget, * canvas;
  QMenuBar * menubar;
  QPopupMenu * filemenu, * viewmenu, * cameramenu, * settingsmenu;
  QPopupMenu * lightsmenu, * modelsubmenu;
  QPopupMenu * informationsubmenu, * linewidthsubmenu, * pointsizesubmenu;
  QPopupMenu * renderqualitysubmenu, * texturequalitysubmenu, * transparencysubmenu;
  QPopupMenu * rendervaluesubmenu, * viewmodesubmenu, * flymodesubmenu;
  
  QWidget * prefwindow;
  QCursor * defaultcursor;
  QLabel * rendervaluelabel, * texturequalitylabel;

  // Variables used for the models viewed with the viewer
  SoSeparator * currentroot;
  SoSwitch * cameraswitch;
  int currentindex;
  SoSeparator * openmodels;
  SbStringList pathtomodels;
  SbStringList modelnames;
  SbIntList modeltextures;

  SoComplexity * complexity;
  SoDrawStyle * drawstyle;
  SoLightModel * lightmodel;
  SoBaseColor * basecolor;
  SoMaterialBinding * materialbinding;
  SoSwitch * drawstyleroot, * hiddenlineroot, * polygonoffsetparent, * graphswitch;
  SoPolygonOffset * polygonoffset;
  SoIndexedLineSet * bbox;
  SoVertexProperty * bboxvertices;
  SoShapeHints * shapehints;
  SoNormal * emptynormal;
  SoNormalBinding * emptynormalbinding;
  SoSearchAction * searchaction;
  SoGetPrimitiveCountAction * countaction;
  SoGetBoundingBoxAction * bboxaction;
  int cones, cubes, cylinders, spheres; 
  int polygonoffsetindex, complexityindex;
  float texturequality;

  SbColor linecolor, pointcolor;

  // Flags used by the viewer
  SbBool menubarenabled;
  SbBool filemenuenabled;
  SbBool viewmenuenabled;
  SbBool settingsmenuenabled;
  SbBool cameramenuenabled;
  SbBool lightsmenuenabled;

  struct menuItem {
    SbString ID;
    SbBool build;
    SbBool enabled;
    int index;
  };

  /*  menuItem[6] menus;
  menuItem[8] filemenuItems;
  menuItem[12] viewmenuItems;
  menuItem[9] settingsmenuItems;
  menuItem[5] cameramenuItems;
 */
  int movingitemchk, transparencyitemchk, cameraitemchk, flymodeitemchk;
  SbBool mt, mf, mv, mw, mb;

  // Flags for the viewmenu
  SbBool filled;
  SbBool informationenabled;
  SbBool flatshadingenabled;
  SbBool boundingboxesenabled;
  SbBool wireframeenabled;
  SbBool verticesenabled;
  SbBool hiddenpartsenabled;
  SbBool texturesenabled;
  int drawstyles;

  // Flags for the settingsmenu
  SbBool distanceenabled;

  // Flags for the cameramenu
  SbBool frontcamera;

  // Strings used in different circumstances by the viewer
  SbString prefwindowtitle;
  SbString filefilter;
  SbString modeldirectory; 
  SbString imagedirectory;

  //variables used for model movement
  struct { // tracking mouse movement in a log
    short size;
    short historysize;
    SbVec2s * position;
    SbTime * time;
  } log;

  enum WaysToMove {
    FULL,
    ONE_BBOX,
    BBOXES,
    NO_TEXTURES
  };

  WaysToMove howtomove;

  SbTime prevRedrawTime;

  SbVec2f lastmouseposition;
  SbPlane panningplane;

  SbBool spinanimating;
  SbBool spinanimatingallowed;
  SbVec2f lastspinposition;
  int spinsamplecounter;
  SbRotation spinincrement;
  class SbSphereSheetProjector * spinprojector;

  SbRotation spinRotation;

  SbVec2s canvasvec;

  // Flags used by processSoEvent()
  SbBool button1down;
  SbBool button2down;
  SbBool button3down;
  SbBool controldown;
  SbBool motion3OnCamera;

  // Variables used by the fly mode
  SbVec2s mousedownpos;
  SbVec2s mousepos;
  SbTime prevtime;
  SbBool shouldscheduleredraw;
  SbBool flying;
  SbBool pause;
  SbBool busy;
  int flydirection;
  SoTimerSensor * timersensor;
  float glidespeed;
  float flyspeed;
  float relspeedglide;
  float relspeedfly;
  SbMatrix camerarot;
  SbBool doresetroll;
  SbVec3f viewupaxis;
  SoFieldSensor * camerapossensor;
  SoFieldSensor * cameraorientsensor;
  SoCamera * currcam;
  float elevation;
  double movedist;

 public:

  void setupNodes();
  void initializeMenus(SbBool buildFlag);
  void drawInformation();
  void resetCountAction();
  void resetBBox();
  void drawstyleRedraw();
  void movingRedraw(SbBool on);
  void changedMoving(SoQtSuperViewerP::WaysToMove how);
  void changedMovingGUI(SoQtSuperViewerP::WaysToMove how);
  SoGroup * getParentOfNode(SoNode * root, SoNode * node, int & index);

  SoSeparator * loadModelFromFile(SbString * const filename);
  void reorientCamera(const SbRotation & rotation);
  void spin (const SbVec2f & pointerpos);
  void pan(const SbVec2f & mousepos, const SbVec2f & prevpos);
  void zoom(const float diffvalue);
  void zoomByCursor(const SbVec2f & mousepos, const SbVec2f & prevpos);

  void clearLog(void);
  void addToLog(const SbVec2s pos, const SbTime time);

  SbBool processMouseEvent(const SoEvent * const event);
  void glidePulse(SbBool joystick = FALSE);
  void flyPulse(SbBool joystick = FALSE);
  void lockedPulse(SbBool Joystick = FALSE);
  //void zoomInPulse(void);
  //void zoomOutPulse(void);
  void pulse(void);

  enum ViewerMode {
    IDLE,
    INTERACT,
    DRAGGING,
    WAITING_FOR_SEEK,
    ZOOMING,
    WAITING_FOR_PAN,
    PANNING,
    FLYMODE,
    GLIDEMODE,
    LOCKEDMODE,
    WAIT_RB_RELEASE,
    WAITING_FOR_FLY
  } mode;

  ViewerMode currentmode;
  ViewerMode flymode;

  void setMode(const ViewerMode mode);
  void setCursorRepresentation(int mode);
  void setLineColor();
  void setPointColor();
  void setBackgroundColor();
  void createCameraEntries();
  void createLightEntries();

  static void timercb(void *data, SoSensor * sensor);
  static void camera_pos_cb(void * data, SoSensor *);
  static void camera_orient_cb(void * data, SoSensor *);

  void moveCamera(const SbVec3f &vec, const SbBool dorotate = FALSE);
  void yawCamera(const float rad);
  void rollCamera(const float rad);
  void pitchCamera(const float rad);
  void resetRoll(void);
  void normalizeCamera(void);

 public slots:
  // filemenu
  void openModelSelected();
  SbBool closeModelSelected();
  void closeAllSelected();
  void nextModelSelected();
  void previousModelSelected();
  void modelSelected( int );
  void refreshSelected();
  void snapshotSelected();
  void quitSelected();

  // viewmenu
  void filledSelected();
  void informationSelected();
  void flatshadingSelected();
  void boundingboxesSelected();
  void wireframeSelected();
  void verticesSelected();
  void hiddenpartsSelected();
  void texturesSelected();
  void oneBBoxMovingSelected();
  void bBoxesMovingSelected();
  void fullMovingSelected();
  void noTexturesMovingSelected();

  // settingsmenu
  void distanceSelected();
  void linewidthSelected( int );
  void pointsizeSelected( int );
  void linecolorSelected();
  void pointcolorSelected();
  void backgroundcolorSelected();
  void transparencytypeSelected( int );
  void objectspaceSelected();
  void screenspaceSelected();
  void renderqualitySelected( int );
  void texturequalitySelected( int );

  // cameramenu
  void viewallSelected();
  void resetviewSelected();
  void seekSelected();
  void cameraSelected( int );
  void frontSelected();
  void examineSelected();
  void flySelected();
  void flymodeSelected( int );

  // lightsmenu
  void lightSelected( int );

  // intermediate slots
  void setNumD10render( int );
  void setNumD10texture( int );

//**********************************************************************
 protected:


//**********************************************************************
 private:

  void findCameras();
  void findLights();
  void flyCameraSetup();

  SbList<SoCamera *> cameras;
  SbList<SoLight *> lights;

  class SoQtSuperViewer * owner;
  friend class SoQtSuperViewer;

};

#endif //! SOQT_SUPERVIEWERP_H






