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

#include "SoQtSuperViewerP.h"
#include "SoQtSuperViewer.h"
#include <Inventor/Qt/SoQt.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoComplexity.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoLightModel.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoMaterialBinding.h>
#include <Inventor/nodes/SoPolygonOffset.h>
#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoLight.h>
#include <Inventor/projectors/SbSphereSheetProjector.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoGetPrimitiveCountAction.h>
#include <Inventor/events/SoEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/lists/SoPathList.h>
#include <Inventor/SoOffscreenRenderer.h>
#include <Inventor/nodekits/SoBaseKit.h>

#include <Inventor/Qt/SoQtCursor.h>

#include <qpopupmenu.h>
#include <qmenubar.h>
#include <qfiledialog.h>
#include <qcolordialog.h>
#include <qcolor.h>
#include <qlabel.h>
#include <qslider.h>


  //static stash
  // FIXME: Most of the static code below is redundant since it also
  // exists in SoGuiViewer. larsivi 20020305

static unsigned char fps2dfont[][12] = {
  {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, //
  {  0,  0, 12, 12,  0,  8, 12, 12, 12, 12, 12,  0 }, // !
  {  0,  0,  0,  0,  0,  0,  0,  0,  0, 20, 20, 20 }, // \"
  {  0,  0, 18, 18, 18, 63, 18, 18, 63, 18, 18,  0 }, // #
  {  0,  8, 28, 42, 10, 10, 12, 24, 40, 42, 28,  8 }, // $
  {  0,  0,  6, 73, 41, 22,  8, 52, 74, 73, 48,  0 }, // %
  {  0, 12, 18, 18, 12, 25, 37, 34, 34, 29,  0,  0 }, // &
  { 12, 12, 24,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, // '
  {  0,  6,  8,  8, 16, 16, 16, 16, 16,  8,  8,  6 }, // (
  {  0, 48,  8,  8,  4,  4,  4,  4,  4,  8,  8, 48 }, //)
  {  0,  0,  0,  0,  0,  0,  8, 42, 20, 42,  8,  0 }, // *
  {  0,  0,  0,  8,  8,  8,127,  8,  8,  8,  0,  0 }, // +
  {  0, 24, 12, 12,  0,  0,  0,  0,  0,  0,  0,  0 }, // ,
  {  0,  0,  0,  0,  0,  0,127,  0,  0,  0,  0,  0 }, // -
  {  0,  0, 24, 24,  0,  0,  0,  0,  0,  0,  0,  0 }, // .
  {  0, 32, 32, 16, 16,  8,  8,  8,  4,  4,  2,  2 }, // /
  {  0,  0, 28, 34, 34, 34, 34, 34, 34, 34, 28,  0 }, // 0
  {  0,  0,  8,  8,  8,  8,  8,  8, 40, 24,  8,  0 }, // 1
  {  0,  0, 62, 32, 16,  8,  4,  2,  2, 34, 28,  0 }, // 2
  {  0,  0, 28, 34,  2,  2, 12,  2,  2, 34, 28,  0 }, // 3
  {  0,  0,  4,  4,  4,126, 68, 36, 20, 12,  4,  0 }, // 4
  {  0,  0, 28, 34,  2,  2,  2, 60, 32, 32, 62,  0 }, // 5
  {  0,  0, 28, 34, 34, 34, 60, 32, 32, 34, 28,  0 }, // 6
  {  0,  0, 16, 16, 16,  8,  8,  4,  2,  2, 62,  0 }, // 7
  {  0,  0, 28, 34, 34, 34, 28, 34, 34, 34, 28,  0 }, // 8
  {  0,  0, 28, 34,  2,  2, 30, 34, 34, 34, 28,  0 }, // 9
  {  0,  0, 24, 24,  0,  0,  0, 24, 24,  0,  0,  0 }, // :
  {  0, 48, 24, 24,  0,  0,  0, 24, 24,  0,  0,  0 }, // ;
  {  0,  0,  0,  2,  4,  8, 16,  8,  4,  2,  0,  0 }, // <
  {  0,  0,  0,  0,  0,127,  0,127,  0,  0,  0,  0 }, // =
  {  0,  0,  0, 16,  8,  4,  2,  4,  8, 16,  0,  0 }, // >
  {  0,  0, 16, 16,  0, 16, 28,  2,  2,  2, 60,  0 }, // ?
  {  0,  0, 28, 32, 73, 86, 82, 82, 78, 34, 28,  0 }, // @
  {  0,  0, 33, 33, 33, 63, 18, 18, 18, 12, 12,  0 }, // A
  {  0,  0, 60, 34, 34, 34, 60, 34, 34, 34, 60,  0 }, // B
  {  0,  0, 14, 16, 32, 32, 32, 32, 32, 18, 14,  0 }, // C
  {  0,  0, 56, 36, 34, 34, 34, 34, 34, 36, 56,  0 }, // D
  {  0,  0, 62, 32, 32, 32, 60, 32, 32, 32, 62,  0 }, // E
  {  0,  0, 16, 16, 16, 16, 30, 16, 16, 16, 30,  0 }, // F
  {  0,  0, 14, 18, 34, 34, 32, 32, 32, 18, 14,  0 }, // G
  {  0,  0, 34, 34, 34, 34, 62, 34, 34, 34, 34,  0 }, // H
  {  0,  0, 62,  8,  8,  8,  8,  8,  8,  8, 62,  0 }, // I
  {  0,  0,112,  8,  8,  8,  8,  8,  8,  8, 62,  0 }, // J
  {  0,  0, 33, 33, 34, 36, 56, 40, 36, 34, 33,  0 }, // K
  {  0,  0, 30, 16, 16, 16, 16, 16, 16, 16, 16,  0 }, // L
  {  0,  0, 33, 33, 33, 45, 45, 45, 51, 51, 33,  0 }, // M
  {  0,  0, 34, 34, 38, 38, 42, 42, 50, 50, 34,  0 }, // N
  {  0,  0, 12, 18, 33, 33, 33, 33, 33, 18, 12,  0 }, // O
  {  0,  0, 32, 32, 32, 60, 34, 34, 34, 34, 60,  0 }, // P
  {  3,  6, 12, 18, 33, 33, 33, 33, 33, 18, 12,  0 }, // Q
  {  0,  0, 34, 34, 34, 36, 60, 34, 34, 34, 60,  0 }, // R
  {  0,  0, 60,  2,  2,  6, 28, 48, 32, 32, 30,  0 }, // S
  {  0,  0,  8,  8,  8,  8,  8,  8,  8,  8,127,  0 }, // T
  {  0,  0, 28, 34, 34, 34, 34, 34, 34, 34, 34,  0 }, // U
  {  0,  0, 12, 12, 18, 18, 18, 33, 33, 33, 33,  0 }, // V
  {  0,  0, 34, 34, 34, 54, 85, 73, 73, 73, 65,  0 }, // W
  {  0,  0, 34, 34, 20, 20,  8, 20, 20, 34, 34,  0 }, // X
  {  0,  0,  8,  8,  8,  8, 20, 20, 34, 34, 34,  0 }, // Y
  {  0,  0, 62, 32, 16, 16,  8,  4,  4,  2, 62,  0 }, // Z
  {  0, 14,  8,  8,  8,  8,  8,  8,  8,  8,  8, 14 }, // [
  {  0,  2,  2,  4,  4,  8,  8,  8, 16, 16, 32, 32 }, // [backslash]
  {  0, 56,  8,  8,  8,  8,  8,  8,  8,  8,  8, 56 }, // ]
  {  0,  0,  0,  0,  0, 34, 34, 20, 20,  8,  8,  0 }, // ^
  {  0,127,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }, // _
  {  0,  0,  0,  0,  0,  0,  0,  0,  0, 24, 24, 12 }, // `
  {  0,  0, 29, 34, 34, 30,  2, 34, 28,  0,  0,  0 }, // a
  {  0,  0, 60, 34, 34, 34, 34, 50, 44, 32, 32, 32 }, // b
  {  0,  0, 14, 16, 32, 32, 32, 16, 14,  0,  0,  0 }, // c
  {  0,  0, 26, 38, 34, 34, 34, 34, 30,  2,  2,  2 }, // d
  {  0,  0, 28, 34, 32, 62, 34, 34, 28,  0,  0,  0 }, // e
  {  0,  0, 16, 16, 16, 16, 16, 16, 62, 16, 16, 14 }, // f
  { 28,  2,  2, 26, 38, 34, 34, 34, 30,  0,  0,  0 }, // g
  {  0,  0, 34, 34, 34, 34, 34, 50, 44, 32, 32, 32 }, // h
  {  0,  0,  8,  8,  8,  8,  8,  8, 56,  0,  8,  8 }, // i
  { 56,  4,  4,  4,  4,  4,  4,  4, 60,  0,  4,  4 }, // j
  {  0,  0, 33, 34, 36, 56, 40, 36, 34, 32, 32, 32 }, // k
  {  0,  0,  8,  8,  8,  8,  8,  8,  8,  8,  8, 56 }, // l
  {  0,  0, 73, 73, 73, 73, 73,109, 82,  0,  0,  0 }, // m
  {  0,  0, 34, 34, 34, 34, 34, 50, 44,  0,  0,  0 }, // n
  {  0,  0, 28, 34, 34, 34, 34, 34, 28,  0,  0,  0 }, // o
  { 32, 32, 60, 34, 34, 34, 34, 50, 44,  0,  0,  0 }, // p
  {  2,  2, 26, 38, 34, 34, 34, 34, 30,  0,  0,  0 }, // q
  {  0,  0, 16, 16, 16, 16, 16, 24, 22,  0,  0,  0 }, // r
  {  0,  0, 60,  2,  2, 28, 32, 32, 30,  0,  0,  0 }, // s
  {  0,  0, 14, 16, 16, 16, 16, 16, 62, 16, 16,  0 }, // t
  {  0,  0, 26, 38, 34, 34, 34, 34, 34,  0,  0,  0 }, // u
  {  0,  0,  8,  8, 20, 20, 34, 34, 34,  0,  0,  0 }, // v
  {  0,  0, 34, 34, 34, 85, 73, 73, 65,  0,  0,  0 }, // w
  {  0,  0, 34, 34, 20,  8, 20, 34, 34,  0,  0,  0 }, // x
  { 48, 16,  8,  8, 20, 20, 34, 34, 34,  0,  0,  0 }, // y
  {  0,  0, 62, 32, 16,  8,  4,  2, 62,  0,  0,  0 }, // z
  {  0,  6,  8,  8,  8,  4, 24,  4,  8,  8,  8,  6 }, // {
  {  0,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8 }, // |
  {  0, 48,  8,  8,  8, 16, 12, 16,  8,  8,  8, 48 }, // }
  {  0,  0,  0,  0,  0,  0, 78, 57,  0,  0,  0,  0 }  // ~
};

static int indices[36] = {
  0, 1, SO_END_LINE_INDEX,
  1, 2, SO_END_LINE_INDEX,
  2, 3, SO_END_LINE_INDEX,
  3, 0, SO_END_LINE_INDEX,
  0, 4, SO_END_LINE_INDEX,
  4, 5, SO_END_LINE_INDEX,
  5, 1, SO_END_LINE_INDEX,
  5, 6, SO_END_LINE_INDEX,
  6, 2, SO_END_LINE_INDEX,
  6, 7, SO_END_LINE_INDEX,
  7, 3, SO_END_LINE_INDEX,
  7, 4, SO_END_LINE_INDEX
};

static void
printString(const char * s)
{
#if defined(__COIN__)
  int i,n;
  n = strlen(s);
  for (i = 0; i < n; i++)
    glBitmap(8, 12, 0.0, 2.0, 10.0, 0.0, fps2dfont[s[i] - 32]);
#endif
}

static void
Draw2DString(const char * str, SbVec2s glsize, SbVec2f position)
{
  // Store GL state.
  glPushAttrib(GL_ALL_ATTRIB_BITS);

  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_TEXTURE_2D);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0.0, glsize[0], 0.0, glsize[1], -1, 1);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glColor3f(0.0, 0.0, 0.0);
  glRasterPos2f(position[0] + 1, position[1]);
  printString(str);
  glRasterPos2f(position[0] - 1, position[1]);
  printString(str);
  glRasterPos2f(position[0], position[1] + 1);
  printString(str);
  glRasterPos2f(position[0], position[1] - 1);
  printString(str);

  glColor3f(1.0, 1.0, 1.0);
  glRasterPos2f(position[0], position[1]);
  printString(str);

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  glPopAttrib();
}

SoQtSuperViewerP::SoQtSuperViewerP(
  SoQtSuperViewer * o)
{
  this->owner = o;
}

SoQtSuperViewerP::~SoQtSuperViewerP()
{}

void
SoQtSuperViewerP::actualInit(SbBool buildNow)
{

  if(!this->defaultoverride){
    
    this->bars = new menuItem[2];
    this->menus = new menuItem[5];
    this->filemenuItems = new menuItem[11];
    this->viewmenuItems = new menuItem[14];
    this->settingsmenuItems = new menuItem[9];
    this->cameramenuItems = new menuItem[7];

    this->bars[0].text = "Toolbar";
    this->bars[1].text = "Menubar";

    this->menus[0].text = "File";
    this->menus[1].text = "View"; 
    this->menus[2].text = "Settings"; 
    this->menus[3].text = "Camera"; 
    this->menus[4].text = "Lights";
    
    this->filemenuItems[0].text = "Open model";
    this->filemenuItems[1].text = "Close model";
    this->filemenuItems[2].text = "Close all models";
    this->filemenuItems[3].text = "Models";
    this->filemenuItems[4].text = "Separator";
    this->filemenuItems[5].text = "Next model";
    this->filemenuItems[6].text = "Previous model";
    this->filemenuItems[7].text = "Refresh model";
    this->filemenuItems[8].text = "Snapshot";
    this->filemenuItems[9].text = "Separator";
    this->filemenuItems[10].text = "Exit";
    
    this->viewmenuItems[0].text = "Information";
    this->viewmenuItems[1].text = "Flatshading";
    this->viewmenuItems[2].text = "Separator";
    this->viewmenuItems[3].text = "Filled";
    this->viewmenuItems[4].text = "Boundingboxes";
    this->viewmenuItems[5].text = "Wireframe";
    this->viewmenuItems[6].text = "Vertices";
    this->viewmenuItems[7].text = "Hidden parts";
    this->viewmenuItems[8].text = "Textures";
    this->viewmenuItems[9].text = "Separator";
    this->viewmenuItems[10].text = "One boundingbox while moving";
    this->viewmenuItems[11].text = "Boundingboxes while moving";
    this->viewmenuItems[12].text = "Full model while moving";
    this->viewmenuItems[13].text = "No textures while moving";
    
    this->settingsmenuItems[0].text = "Information settings";
    this->settingsmenuItems[1].text = "Line width";
    this->settingsmenuItems[2].text = "Point size";
    this->settingsmenuItems[3].text = "Line color";
    this->settingsmenuItems[4].text = "Point color";
    this->settingsmenuItems[5].text = "Background color";
    this->settingsmenuItems[6].text = "Render quality";
    this->settingsmenuItems[7].text = "Texture Quality";
    this->settingsmenuItems[8].text = "Transparency type";
    
    this->cameramenuItems[0].text = "View all";
    this->cameramenuItems[1].text = "Reset view";
    this->cameramenuItems[2].text = "Seek";
    this->cameramenuItems[3].text = "View modes";
    this->cameramenuItems[4].text = "Fly modes";
    this->cameramenuItems[5].text = "Separator";
    this->cameramenuItems[6].text = "Front camera";

    int i = 0;
    //setup menubar and toolbars (2 elements)
    for(;i < 2; i++){
      this->bars[i].index = i;
      this->bars[i].build = TRUE;
      this->bars[i].enabled = TRUE;
      this->bars[i].checked = FALSE;
    }
    //until the toolbar is made
    this->bars[0].build = FALSE;
    this->bars[1].index = 0;
    //the rest should stay when the toolbar is finished
 
    i = 0;
    //setup menus (5 elements)
    for(;i < 5; i++){
      this->menus[i].index = i;
      this->menus[i].build = TRUE;
      this->menus[i].enabled = i == 0 ? TRUE : FALSE;
      this->menus[i].checked = FALSE;
    }

    i = 0;
    //setup filemenu (8 elements)
    for(;i < 11; i++){
      this->filemenuItems[i].index = i;
      this->filemenuItems[i].build = i == 3 ? FALSE : TRUE;
      this->filemenuItems[i].enabled = i == 0 || i > 9 ? TRUE : FALSE;
      this->filemenuItems[i].checked = FALSE;
    }
    
    i = 0;
    //setup viewmenu (12 elements)
    for(;i < 11; i++){
      this->viewmenuItems[i].index = i;
      this->viewmenuItems[i].build = TRUE;
      this->viewmenuItems[i].enabled = (i == 7 || i == 8) ? FALSE : TRUE;
      this->viewmenuItems[i].checked = (i == 3 || i == 12) ? TRUE : FALSE;
    }

    i = 0;
    //setup settingsmenu (9 elements)
    for(;i < 9; i++){
      this->settingsmenuItems[i].index = i;
      this->settingsmenuItems[i].build = TRUE;
      this->settingsmenuItems[i].enabled = i == 0 ? FALSE : TRUE;
      this->settingsmenuItems[i].checked = FALSE;
    }

    i = 0;
    //setup cameramenu (5 elements)
    for(;i < 7; i++){
      this->cameramenuItems[i].index = i;
      this->cameramenuItems[i].build = TRUE;
      this->cameramenuItems[i].enabled = i == 4 ? FALSE : TRUE;
      this->cameramenuItems[i].checked = FALSE;
    }
  }

  if(buildNow){
    this->built = TRUE;
    this->buildBars();
  }
} // actualInit()

void
SoQtSuperViewerP::buildBars()
{
  //toolbar
  if(this->bars[0].build){

  }
  //menubar
  if(this->bars[1].build){
    if(this->menubar == NULL)
      this->menubar = new QMenuBar(this->viewerwidget);
    else
      this->menubar->clear();
    this->buildMenus();
  }
} // buildBars()

void
SoQtSuperViewerP::buildMenus()
{
  int idx = 0;
  if(this->menus[0].build){
    this->buildFileMenu(); 
    this->menus[0].index = idx; 
    idx++;
  }
  if(this->menus[1].build){
    this->buildViewMenu(); this->menus[1].index = idx; idx++;
  }
  if(this->menus[2].build){
    this->buildSettingsMenu(); this->menus[2].index = idx; idx++;
  }
  if(this->menus[3].build){
    this->buildCameraMenu(); this->menus[3].index = idx; idx++;
  }
  if(this->menus[4].build){
    this->buildLightsMenu(); this->menus[4].index = idx;
  }
}

void
SoQtSuperViewerP::buildFileMenu()
{
  if(this->filemenu == NULL)
    this->filemenu = new QPopupMenu(this->menubar);
  else
    this->filemenu->clear();

  int idx = 0;
  if(this->filemenuItems[0].build){
    this->filemenuItems[0].index = idx;
    this->filemenu->insertItem(filemenuItems[0].text.getString(), this,
                               SLOT(openModelSelected()), CTRL+Key_O);
    this->filemenu->setItemEnabled(this->filemenu->idAt(filemenuItems[0].index),
                                   filemenuItems[0].enabled);
    this->filemenu->setItemChecked(this->filemenu->idAt(filemenuItems[0].index),
                                   filemenuItems[0].checked);
    idx++;
  }
  if(this->filemenuItems[1].build){
    this->filemenuItems[1].index = idx;
    this->filemenu->insertItem(filemenuItems[1].text.getString(), this,
                               SLOT(closeModelSelected()), CTRL+Key_K);
    this->filemenu->setItemEnabled(this->filemenu->idAt(filemenuItems[1].index),
                                   filemenuItems[1].enabled);
    this->filemenu->setItemChecked(this->filemenu->idAt(filemenuItems[1].index),
                                   filemenuItems[1].checked);
    idx++;
  }
  if(this->filemenuItems[2].build){
    this->filemenuItems[2].index = idx;
    this->filemenu->insertItem(filemenuItems[2].text.getString(), this,
                               SLOT(closeAllSelected()));
    this->filemenu->setItemEnabled(this->filemenu->idAt(filemenuItems[2].index),
                                   filemenuItems[2].enabled);
    this->filemenu->setItemChecked(this->filemenu->idAt(filemenuItems[2].index),
                                   filemenuItems[2].checked);
    idx++;
  }
  if(this->filemenuItems[3].build){
    this->filemenuItems[3].index = idx;
    if(this->modelsubmenu == NULL)
      this->modelsubmenu = new QPopupMenu(this->filemenu);
    this->filemenu->insertItem(filemenuItems[3].text.getString(), 
                                this->modelsubmenu, 0, filemenuItems[3].index);
    this->filemenu->setItemEnabled(this->filemenu->idAt(filemenuItems[3].index),
                                   filemenuItems[3].enabled);
    idx++;
  }
  if(this->filemenuItems[4].build){ 
    this->filemenuItems[4].index = idx;
    this->filemenu->insertSeparator(); 
    idx++;  
  }
  if(this->filemenuItems[5].build){
    this->filemenuItems[5].index = idx;
    this->filemenu->insertItem(filemenuItems[5].text.getString(), this,
                               SLOT(nextModelSelected()), CTRL+Key_N);
    this->filemenu->setItemEnabled(this->filemenu->idAt(filemenuItems[5].index),
                                   filemenuItems[5].enabled);
    this->filemenu->setItemChecked(this->filemenu->idAt(filemenuItems[5].index),
                                   filemenuItems[5].checked);
    idx++;
  }
  if(this->filemenuItems[6].build){
    this->filemenuItems[6].index = idx;
    this->filemenu->insertItem(filemenuItems[6].text.getString(), this,
                               SLOT(previousModelSelected()), CTRL+Key_P);
    this->filemenu->setItemEnabled(this->filemenu->idAt(filemenuItems[6].index),
                                   filemenuItems[6].enabled);
    this->filemenu->setItemChecked(this->filemenu->idAt(filemenuItems[6].index),
                                   filemenuItems[6].checked);
    idx++;
  }
  if(this->filemenuItems[7].build){
    this->filemenuItems[7].index = idx;
    this->filemenu->insertItem(filemenuItems[7].text.getString(), this,
                               SLOT(refreshSelected()), CTRL+Key_R);
    this->filemenu->setItemEnabled(this->filemenu->idAt(filemenuItems[7].index),
                                   filemenuItems[7].enabled);
    this->filemenu->setItemChecked(this->filemenu->idAt(filemenuItems[7].index),
                                   filemenuItems[7].checked);
    idx++;
  }
  if(this->filemenuItems[8].build){
    this->filemenuItems[8].index = idx;
    this->filemenu->insertItem(filemenuItems[8].text.getString(), this,
                               SLOT(snapshotSelected()), CTRL+Key_S);
    this->filemenu->setItemEnabled(this->filemenu->idAt(filemenuItems[8].index),
                                   filemenuItems[8].enabled);
    this->filemenu->setItemChecked(this->filemenu->idAt(filemenuItems[8].index),
                                   filemenuItems[8].checked);
    idx++;
  }
  if(this->filemenuItems[9].build){ 
    this->filemenuItems[9].index = idx;
    this->filemenu->insertSeparator(); 
    idx++;  
  }
  if(this->filemenuItems[10].build){
    this->filemenuItems[10].index = idx;
    this->filemenu->insertItem(filemenuItems[10].text.getString(), this,
                               SLOT(quitSelected()), CTRL+Key_Q);
    this->filemenu->setItemEnabled(this->filemenu->idAt(filemenuItems[10].index),
                                   filemenuItems[10].enabled);
    this->filemenu->setItemChecked(this->filemenu->idAt(filemenuItems[10].index),
                                   filemenuItems[10].checked);
  }
  this->menubar->insertItem(menus[0].text.getString(), this->filemenu);
  this->menubar->setItemEnabled(this->menubar->idAt(menus[0].index),
                                menus[0].enabled);
} // buildFileMenu()

void
SoQtSuperViewerP::buildViewMenu()
{
  if(this->viewmenu == NULL)
    this->viewmenu = new QPopupMenu(this->menubar);
  else
    this->viewmenu->clear();

  int idx = 0;
  if(this->viewmenuItems[0].build){
    this->viewmenuItems[0].index = idx;
    this->viewmenu->insertItem(viewmenuItems[0].text.getString(), this,
                               SLOT(informationSelected()));
    this->viewmenu->setItemEnabled(this->viewmenu->idAt(viewmenuItems[0].index),
                                   viewmenuItems[0].enabled);
    this->viewmenu->setItemChecked(this->viewmenu->idAt(viewmenuItems[0].index),
                                   viewmenuItems[0].checked);
    idx++;
  }
  if(this->viewmenuItems[1].build){
    this->viewmenuItems[1].index = idx;
    this->viewmenu->insertItem(viewmenuItems[1].text.getString(), this,
                               SLOT(flatshadingSelected()));
    this->viewmenu->setItemEnabled(this->viewmenu->idAt(viewmenuItems[1].index),
                                   viewmenuItems[1].enabled);
    this->viewmenu->setItemChecked(this->viewmenu->idAt(viewmenuItems[1].index),
                                   viewmenuItems[1].checked);
    idx++;
  }
  if(this->viewmenuItems[2].build){ 
    this->viewmenuItems[2].index = idx;
    this->viewmenu->insertSeparator(); 
    idx++;  
  }
  if(this->viewmenuItems[3].build){
    this->viewmenuItems[3].index = idx;
    this->viewmenu->insertItem(viewmenuItems[3].text.getString(), this,
                               SLOT(filledSelected()));
    this->viewmenu->setItemEnabled(this->viewmenu->idAt(viewmenuItems[3].index),
                                   viewmenuItems[3].enabled);
    this->viewmenu->setItemChecked(this->viewmenu->idAt(viewmenuItems[3].index),
                                   viewmenuItems[3].checked);
    idx++;
  }
  if(this->viewmenuItems[4].build){
    this->viewmenuItems[4].index = idx;
    this->viewmenu->insertItem(viewmenuItems[4].text.getString(), this,
                               SLOT(boundingboxesSelected()));
    this->viewmenu->setItemEnabled(this->viewmenu->idAt(viewmenuItems[4].index),
                                   viewmenuItems[4].enabled);
    this->viewmenu->setItemChecked(this->viewmenu->idAt(viewmenuItems[4].index),
                                   viewmenuItems[4].checked);
    idx++;
  }
  if(this->viewmenuItems[5].build){
    this->viewmenuItems[5].index = idx;
    this->viewmenu->insertItem(viewmenuItems[5].text.getString(), this,
                               SLOT(wireframeSelected()));
    this->viewmenu->setItemEnabled(this->viewmenu->idAt(viewmenuItems[5].index),
                                   viewmenuItems[5].enabled);
    this->viewmenu->setItemChecked(this->viewmenu->idAt(viewmenuItems[5].index),
                                   viewmenuItems[5].checked);
    idx++;
  }  
  if(this->viewmenuItems[6].build){
    this->viewmenuItems[6].index = idx;
    this->viewmenu->insertItem(viewmenuItems[6].text.getString(), this,
                               SLOT(verticesSelected()));
    this->viewmenu->setItemEnabled(this->viewmenu->idAt(viewmenuItems[6].index),
                                   viewmenuItems[6].enabled);
    this->viewmenu->setItemChecked(this->viewmenu->idAt(viewmenuItems[6].index),
                                   viewmenuItems[6].checked);
    idx++;
  }
  if(this->viewmenuItems[7].build){
    this->viewmenuItems[7].index = idx;
    this->viewmenu->insertItem(viewmenuItems[7].text.getString(), this,
                               SLOT(hiddenpartsSelected()));
    this->viewmenu->setItemEnabled(this->viewmenu->idAt(viewmenuItems[7].index),
                                   viewmenuItems[7].enabled);
    this->viewmenu->setItemChecked(this->viewmenu->idAt(viewmenuItems[7].index),
                                   viewmenuItems[7].checked);
    idx++;
  }
  if(this->viewmenuItems[8].build){
    this->viewmenuItems[8].index = idx;
    this->viewmenu->insertItem(viewmenuItems[8].text.getString(), this,
                               SLOT(texturesSelected()));
    this->viewmenu->setItemEnabled(this->viewmenu->idAt(viewmenuItems[8].index),
                                   viewmenuItems[8].enabled);
    this->viewmenu->setItemChecked(this->viewmenu->idAt(viewmenuItems[8].index),
                                   viewmenuItems[8].checked);
    idx++;
  }
  if(this->viewmenuItems[9].build){ 
    this->viewmenuItems[9].index = idx;
    this->viewmenu->insertSeparator(); 
    idx++;  
  }

  if(this->viewmenuItems[10].build){
    this->viewmenuItems[10].index = idx;
    this->viewmenu->insertItem("One boundingbox while moving", this,
                               SLOT(oneBBoxMovingSelected()));
    this->viewmenu->insertItem("Boundingboxes while moving", this,
                               SLOT(bBoxesMovingSelected()));
    this->viewmenu->insertItem("Full model while moving", this,
                               SLOT(fullMovingSelected()));
    this->viewmenu->insertItem("No textures while moving", this,
                               SLOT(noTexturesMovingSelected()));
    this->viewmenu->setItemEnabled(this->viewmenu->idAt(viewmenuItems[10].index),
                                   viewmenuItems[10].enabled);
    this->viewmenu->setItemEnabled(this->viewmenu->idAt(viewmenuItems[10].index + 1),
                                   viewmenuItems[10].enabled);
    this->viewmenu->setItemEnabled(this->viewmenu->idAt(viewmenuItems[10].index + 2),
                                   viewmenuItems[10].enabled);
    this->viewmenu->setItemEnabled(this->viewmenu->idAt(viewmenuItems[10].index + 3),
                                   viewmenuItems[10].enabled);
    this->viewmenu->setItemChecked(this->viewmenu->idAt(viewmenuItems[10].index + 2),
                                   TRUE);
    this->movingitemchk = this->viewmenu->idAt(viewmenuItems[10].index  + 2);
  }

  this->menubar->insertItem(menus[1].text.getString(), this->viewmenu);
  this->menubar->setItemEnabled(this->menubar->idAt(menus[1].index),
                                   menus[1].enabled);

} // buildViewMenu()

void
SoQtSuperViewerP::buildSettingsMenu()
{
  if(this->settingsmenu == NULL)
    this->settingsmenu = new QPopupMenu(this->menubar);
  else
    this->settingsmenu.clear();

  int idx = 0;
  if(this->settingsmenuItems[0].build){
    this->settingsmenuItems[0].index = idx;
    if(this->informationsubmenu == NULL)
      this->informationsubmenu = new QPopupMenu(this->settingsmenu);
    this->settingsmenu->insertItem(settingsmenuItems[0].text.getString(), 
                                   this->informationsubmenu);
    this->settingsmenu->setItemEnabled(this->settingsmenu->idAt(settingsmenuItems[0].index),
                                   settingsmenuItems[0].enabled);
    this->informationsubmenu->insertItem("Enable distance",
                                         this, SLOT(distanceSelected()));
    idx++;
  }
  if(this->settingsmenuItems[1].build){
    this->settingsmenuItems[1].index = idx;
    if(this->linewidthsubmenu == NULL)
      this->linewidthsubmenu = new QPopupMenu(this->settingsmenu);
    this->settingsmenu->insertItem(settingsmenuItems[1].text.getString(), 
                                   this->linewidthsubmenu);
    this->settingsmenu->setItemEnabled(this->settingsmenu->idAt(settingsmenuItems[1].index),
                                   settingsmenuItems[1].enabled);
    
    SbVec2f range;
    float gr;
    owner->getLineWidthLimits(range, gr);
    range[0]+= 0.5;
    QLabel * label = new QLabel(this->linewidthsubmenu);
    label->setNum((int)range[0]);
    label->setAlignment(AlignRight | AlignVCenter);
    QSlider * slider = new QSlider(range[0], range[1], range[1], range[0], 
                                   QSlider::Vertical, 
                                   this->linewidthsubmenu);
    QObject::connect(slider, SIGNAL(valueChanged(int)),
                     label, SLOT(setNum(int)));
    QObject::connect(slider, SIGNAL(sliderMoved(int)),
                     this, SLOT(linewidthSelected(int)));
    this->linewidthsubmenu->insertItem(label);
    this->linewidthsubmenu->insertItem(slider);
    idx++;
  }
  if(this->settingsmenuItems[2].build){
    this->settingsmenuItems[2].index = idx;
    if(this->pointsizesubmenu == NULL)
      this->pointsizesubmenu = new QPopupMenu(this->settingsmenu);
    this->settingsmenu->insertItem(settingsmenuItems[2].text.getString(), 
                                   this->pointsizesubmenu);
    this->settingsmenu->setItemEnabled(this->settingsmenu->idAt(settingsmenuItems[2].index),
                                   settingsmenuItems[2].enabled);

    SbVec2f range;
    float gr;
    owner->getPointSizeLimits(range, gr);
    range[0]+= 0.5;
    QLabel * label = new QLabel(this->pointsizesubmenu);
    // the start value is set to 2, since the smallest value tends be too small
    label->setNum(2);
    label->setAlignment(AlignRight | AlignVCenter);
    QSlider * slider = new QSlider(range[0], range[1], range[1], 2, 
                                   QSlider::Vertical, 
                                   this->pointsizesubmenu);
    QObject::connect(slider, SIGNAL(valueChanged(int)),
                     label, SLOT(setNum(int)));
    QObject::connect(slider, SIGNAL(sliderMoved(int)),
                     this, SLOT(pointsizeSelected(int)));
    this->pointsizesubmenu->insertItem(label);
    this->pointsizesubmenu->insertItem(slider);

    idx++;
  }
  if(this->settingsmenuItems[3].build){
    this->settingsmenuItems[3].index = idx;
    this->settingsmenu->insertItem(settingsmenuItems[3].text.getString(), this,
                                   SLOT(linecolorSelected()));
    this->settingsmenu->setItemEnabled(this->settingsmenu->idAt(settingsmenuItems[3].index),
                                   settingsmenuItems[3].enabled);
    this->settingsmenu->setItemChecked(this->settingsmenu->idAt(settingsmenuItems[3].index),
                                   settingsmenuItems[3].checked);
    idx++;
  }
  if(this->settingsmenuItems[4].build){
    this->settingsmenuItems[4].index = idx;
    this->settingsmenu->insertItem(settingsmenuItems[4].text.getString(), this,
                                   SLOT(pointcolorSelected()));
    this->settingsmenu->setItemEnabled(this->settingsmenu->idAt(settingsmenuItems[4].index),
                                   settingsmenuItems[4].enabled);
    this->settingsmenu->setItemChecked(this->settingsmenu->idAt(settingsmenuItems[4].index),
                                   settingsmenuItems[4].checked);
    idx++;
  }
  if(this->settingsmenuItems[5].build){
    this->settingsmenuItems[5].index = idx;
    this->settingsmenu->insertItem(settingsmenuItems[5].text.getString(), this,
                                   SLOT(backgroundcolorSelected()));
    this->settingsmenu->setItemEnabled(this->settingsmenu->idAt(settingsmenuItems[5].index),
                                   settingsmenuItems[5].enabled);
    this->settingsmenu->setItemChecked(this->settingsmenu->idAt(settingsmenuItems[5].index),
                                   settingsmenuItems[5].checked);
    idx++;
  }
  if(this->settingsmenuItems[6].build){
    this->settingsmenuItems[6].index = idx;
    if(this->renderqualitysubmenu == NULL)
      this->renderqualitysubmenu = new QPopupMenu(this->settingsmenu);
    this->settingsmenu->insertItem(settingsmenuItems[6].text.getString(),
                                          this->renderqualitysubmenu);
    this->renderqualitysubmenu->insertItem("Object space", this, 
                                           SLOT(objectspaceSelected()));
    this->renderqualitysubmenu->setItemChecked(
          this->renderqualitysubmenu->idAt(0), TRUE);
    this->renderqualitysubmenu->insertItem("Screen space", this,
                                           SLOT(screenspaceSelected()));
    if(this->rendervaluesubmenu == NULL)
      this->rendervaluesubmenu = new QPopupMenu(this->renderqualitysubmenu);
    this->renderqualitysubmenu->insertItem("Value",
                                           this->rendervaluesubmenu);

    if(this->rendervaluelabel == NULL)
      this->rendervaluelabel = new QLabel(this->rendervaluesubmenu);
    this->rendervaluelabel->setNum((double)1.0);
    this->rendervaluelabel->setAlignment(AlignRight | AlignVCenter);
    QSlider * slider = new QSlider(0, 10, 10, 10, 
                                   QSlider::Vertical, 
                                   this->rendervaluesubmenu);
    QObject::connect(slider, SIGNAL(valueChanged(int)),
                     this, SLOT(setNumD10render(int)));
    QObject::connect(slider, SIGNAL(sliderMoved(int)),
                     this, SLOT(renderqualitySelected(int)));
    this->rendervaluesubmenu->insertItem(this->rendervaluelabel);
    this->rendervaluesubmenu->insertItem(slider);
    idx++;
  }
  if(this->settingsmenuItems[7].build){
    this->settingsmenuItems[7].index = idx;
    if(this->texturequalitysubmenu == NULL)
      this->texturequalitysubmenu = new QPopupMenu(this->settingsmenu);
    this->settingsmenu->insertItem(settingsmenuItems[7].text.getString(),
                                            this->texturequalitysubmenu);

    this->texturequalitylabel = new QLabel(this->texturequalitysubmenu);
    this->texturequalitylabel->setNum((double)1.0);
    this->texturequalitylabel->setAlignment(AlignRight | AlignVCenter);
    QSlider * slider = new QSlider(0, 10, 10, 10, 
                                   QSlider::Vertical, 
                                   this->texturequalitysubmenu);
    QObject::connect(slider, SIGNAL(valueChanged(int)),
                     this, SLOT(setNumD10texture(int)));
    QObject::connect(slider, SIGNAL(sliderMoved(int)),
                     this, SLOT(texturequalitySelected(int)));
    this->texturequalitysubmenu->insertItem(this->texturequalitylabel);
    this->texturequalitysubmenu->insertItem(slider);
  }
  if(this->settingsmenuItems[8].build){
    this->settingsmenuItems[8].index = idx;
    if(this->transparencysubmenu == NULL)
      this->transparencysubmenu = new QPopupMenu(this->settingsmenu);
    this->settingsmenu->insertItem(settingsmenuItems[8].text.getString(),
                                   this->transparencysubmenu);
    this->transparencysubmenu->insertItem("Screen door", 
           this, SLOT(transparencytypeSelected( int )));
    this->transparencysubmenu->setItemChecked(
           this->transparencysubmenu->idAt(0), TRUE);
    this->transparencysubmenu->insertItem("Add", 
           this, SLOT(transparencytypeSelected( int )));
    this->transparencysubmenu->insertItem("Delayed add", 
           this, SLOT(transparencytypeSelected( int )));
    this->transparencysubmenu->insertItem("Sorted object add", 
           this, SLOT(transparencytypeSelected( int )));
    this->transparencysubmenu->insertItem("Blend", 
           this, SLOT(transparencytypeSelected( int )));
    this->transparencysubmenu->insertItem("Delayed blend", 
           this, SLOT(transparencytypeSelected( int )));
    this->transparencysubmenu->insertItem("Sorted object blend", 
           this, SLOT(transparencytypeSelected( int )));
    this->transparencysubmenu->insertItem("Sorted object, sorted triangle add", 
           this, SLOT(transparencytypeSelected( int )));
    this->transparencysubmenu->insertItem("Sorted object, sorted triangle blend", 
           this, SLOT(transparencytypeSelected( int )));
  }

  this->menubar->insertItem(menus[2].text.getString(), this->settingsmenu);
  this->menubar->setItemEnabled(this->menubar->idAt(menus[2].index),
                                   menus[2].enabled);
}

void
SoQtSuperViewerP::buildCameraMenu()
{
  if(this->cameramenu == NULL)
    this->cameramenu = new QPopupMenu(this->menubar);
  else
    this->cameramenu->clear();

  int idx = 0;
  if(this->cameramenuItems[0].build){
    this->cameramenuItems[0].index = idx;
    this->cameramenu->insertItem(cameramenuItems[0].text.getString(), this,
                                 SLOT(viewallSelected()));
    this->cameramenu->setItemEnabled(this->cameramenu->idAt(cameramenuItems[0].index),
                                     cameramenuItems[0].enabled);
    this->cameramenu->setItemChecked(this->cameramenu->idAt(cameramenuItems[0].index),
                                     cameramenuItems[0].checked);
    idx++;
  }
  if(this->cameramenuItems[1].build){
    this->cameramenuItems[1].index = idx;
    this->cameramenu->insertItem(cameramenuItems[1].text.getString(), this,
                                 SLOT(resetviewSelected()));
    this->cameramenu->setItemEnabled(this->cameramenu->idAt(cameramenuItems[1].index),
                                     cameramenuItems[1].enabled);
    this->cameramenu->setItemChecked(this->cameramenu->idAt(cameramenuItems[1].index),
                                     cameramenuItems[1].checked);
    idx++;
  } 
  if(this->cameramenuItems[2].build){
    this->cameramenuItems[2].index = idx;
    this->cameramenu->insertItem(cameramenuItems[2].text.getString(), this,
                                 SLOT(seekSelected()));
    this->cameramenu->setItemEnabled(this->cameramenu->idAt(cameramenuItems[2].index),
                                     cameramenuItems[2].enabled);
    this->cameramenu->setItemChecked(this->cameramenu->idAt(cameramenuItems[2].index),
                                     cameramenuItems[2].checked);
    idx++;
  }
  if(this->cameramenuItems[3].build){
    this->cameramenuItems[3].index = idx;
    if(this->viewmodesubmenu == NULL)
      this->viewmodesubmenu = new QPopupMenu(this->cameramenu);
    this->cameramenu->insertItem(cameramenuItems[3].text.getString(), 
                                 this->viewmodesubmenu);
    this->viewmodesubmenu->insertItem("Examine",
                                      this, SLOT(examineSelected()));
    this->viewmodesubmenu->setItemChecked(
                                  this->viewmodesubmenu->idAt(0), TRUE);
    this->viewmodesubmenu->insertItem("Fly",
                                      this, SLOT(flySelected()));
    this->cameramenu->setItemEnabled(this->cameramenu->idAt(cameramenuItems[3].index),
                                     cameramenuItems[3].enabled);
    this->cameramenu->setItemChecked(this->cameramenu->idAt(cameramenuItems[3].index),
                                     cameramenuItems[3].checked);
    idx++;
  }   
  if(this->cameramenuItems[4].build){
    this->cameramenuItems[4].index = idx;
    if(this->flymodesubmenu == NULL)
      this->flymodesubmenu = new QPopupMenu(this->cameramenu);
    this->cameramenu->insertItem(cameramenuItems[4].text.getString(), 
                                 this->flymodesubmenu);

    this->flymodesubmenu->insertItem("Fly mode", this,
                                     SLOT(flymodeSelected(int)));
    this->flymodesubmenu->setItemChecked(this->flymodesubmenu->idAt(0), TRUE);
    this->flymodesubmenu->insertItem("Glide mode", this,
                                     SLOT(flymodeSelected(int)));
    this->flymodesubmenu->insertItem("Locked mode", this,
                                     SLOT(flymodeSelected(int)));
    this->cameramenu->setItemEnabled(this->cameramenu->idAt(cameramenuItems[4].index),
                                     cameramenuItems[4].enabled);
    this->cameramenu->setItemChecked(this->cameramenu->idAt(cameramenuItems[4].index),
                                     cameramenuItems[4].checked);
    idx++;
  }   
  if(this->cameramenuItems[5].build){
    this->cameramenuItems[5].index = idx;
    this->cameramenu->insertSeparator();
    idx++;
  }

  this->menubar->insertItem(menus[3].text.getString(), this->cameramenu);
  this->menubar->setItemEnabled(this->menubar->idAt(menus[3].index),
                                   menus[3].enabled);

}

void
SoQtSuperViewerP::buildLightsMenu()
{
  if(this->lightsmenu == NULL)
    this->lightsmenu = new QPopupMenu(this->menubar);
  else
    this->lightsmenu->clear();

  this->menubar->insertItem(menus[4].text.getString(), this->lightsmenu);
  this->menubar->setItemEnabled(this->menubar->idAt(menus[4].index),
                                   menus[4].enabled);
}


/*!
  \internal

  Adds an entry to the model list in the menu. If there was no open models,
  the model submenu is created and put into index 3 in the filemenu, thus
  incrementing the indices of the entries below by 1.
*/

void
SoQtSuperViewerP::addModelEntry(
  SbString * const filename)
{
  if(this->modelsubmenu == NULL){
    this->modelsubmenu = new QPopupMenu(this->filemenu);
    owner->setFileMenu(BUILD_FILE_MENU);
  }

  this->modelsubmenu->insertItem(filename->getString(), 
           this, SLOT(modelSelected( int )));
}

void
SoQtSuperViewerP::setupNodes()
{
  if(this->searchaction == NULL)
    this->searchaction = new SoSearchAction;
  this->searchaction->reset(); 
  this->searchaction->setSearchingAll(TRUE);
  this->searchaction->setInterest(SoSearchAction::FIRST);
  SoSeparator * superscene = (SoSeparator *)owner->getSceneManager()->getSceneGraph();
  SoSeparator * usersg = NULL;
  this->graphswitch = new SoSwitch;
                                      
#define LOCATE_NODE(member, type, name) \
  do { \
    member = NULL; \
    this->searchaction->setName(SbName(name)); \
    this->searchaction->apply(superscene); \
    if (this->searchaction->isFound()) { \
      SoNode * node = this->searchaction->getPath()->getTail(); \
      assert(node != NULL); \
      if (node->isOfType(type::getClassTypeId())) \
        member = (type *) node; \
    } else { \
      SoDebugError::post("SoQtSuperViewerP::findNodes", \
                         "didn't locate node \"%s\"", name); \
    } \
  } while (FALSE)

  //  LOCATE_NODE(this->headlight, SoDirectionalLight, "so@gui@->headlight");
  LOCATE_NODE(this->drawstyleroot, SoSwitch, "soqt->drawstyleroot");
  LOCATE_NODE(this->hiddenlineroot, SoSwitch, "soqt->hiddenlineroot");
  LOCATE_NODE(this->polygonoffsetparent, SoSwitch, "soqt->polygonoffsetparent");
  
  LOCATE_NODE(this->basecolor, SoBaseColor, "soqt->basecolor");
  LOCATE_NODE(this->complexity, SoComplexity, "soqt->complexity");
  LOCATE_NODE(this->drawstyle, SoDrawStyle, "soqt->drawstyle");
  LOCATE_NODE(this->lightmodel, SoLightModel, "soqt->lightmodel");
  LOCATE_NODE(this->materialbinding, SoMaterialBinding, "soqt->materialbinding");
  LOCATE_NODE(usersg, SoSeparator, "soqt->userscenegraphroot");
#ifdef HAVE_SOPOLYGONOFFSET
  LOCATE_NODE(this->polygonoffset, SoPolygonOffset, "soqt->polygonoffset");
  if(this->polygonoffset) this->polygonoffset->setOverride(TRUE);
#endif

#undef LOCATE_NODE
      
  this->materialbinding->value.setIgnored(FALSE); // override with OVERALL
  this->polygonoffsetparent->whichChild = SO_SWITCH_ALL;
  this->polygonoffsetindex = this->hiddenlineroot->findChild(this->polygonoffsetparent);
  this->complexityindex = this->drawstyleroot->findChild(this->complexity);
  this->hiddenlineroot->whichChild = this->polygonoffsetindex;
  this->basecolor->rgb.setIgnored(TRUE);
  this->complexity->value = 1.0;
  this->complexity->textureQuality = 1.0;
  usersg->ref();
  superscene->replaceChild(usersg, this->graphswitch);
  this->graphswitch->addChild(usersg);
  this->bbox = new SoIndexedLineSet;
  this->bboxvertices = new SoVertexProperty;
  this->bboxvertices->vertex.setNum(8);
  this->bbox->vertexProperty = this->bboxvertices;
  this->graphswitch->addChild(this->bbox);
  this->graphswitch->whichChild = 0;
  this->drawstyle->lineWidth.setIgnored(FALSE);
  this->drawstyle->pointSize.setIgnored(FALSE);
  this->drawstyle->pointSize = 2.0f;
  delete this->searchaction;
  this->searchaction = NULL;

}

void
SoQtSuperViewerP::initializeMenus(SbBool buildFlag)
{
  //this->menus[0].ID = "MENU_BAR";
  //this->menus[0].

}

void
SoQtSuperViewerP::drawInformation()
{
  if(countaction == NULL) resetCountAction();

  short vertmove = 0;

  char buffer[64];
  if(spheres){
    int nr = sprintf(buffer, "Spheres: %d", spheres);
    Draw2DString(buffer, owner->getGLSize(), SbVec2f(20, 40 + vertmove));
    vertmove += 20;
  }
  if(cylinders){
    int nr = sprintf(buffer, "Cylinders: %d", cylinders);
    Draw2DString(buffer, owner->getGLSize(), SbVec2f(20, 40 + vertmove));
    vertmove += 20;
  }
  if(cubes){
    int nr = sprintf(buffer, "Cubes: %d", cubes);
    Draw2DString(buffer, owner->getGLSize(), SbVec2f(20, 40 + vertmove));
    vertmove += 20;
  }
  if(cones){
    int nr = sprintf(buffer, "Cones: %d", cones);
    Draw2DString(buffer, owner->getGLSize(), SbVec2f(20, 40 + vertmove));
    vertmove += 20;
  }
  if(countaction->getTriangleCount()){
    int nr = sprintf(buffer, "Triangles: %d", countaction->getTriangleCount());
    Draw2DString(buffer, owner->getGLSize(), SbVec2f(20, 40 + vertmove));
    vertmove += 20;
  }
  if(distanceenabled){
    SoCamera * cam = owner->getCamera();
    if (cam == NULL) return; // can happen for empty scenegraph

    SbVec3f campos = cam->position.getValue();

    this->bboxaction = new SoGetBoundingBoxAction(owner->getViewportRegion());
    this->bboxaction->apply(currentroot);
    SbBox3f bboxvec = this->bboxaction->getBoundingBox();
    SbVec3f center = bboxvec.getCenter();
    delete this->bboxaction;
    this->bboxaction = NULL;

    campos.operator-=(center);
    float distance = campos.length();
    
    int nt = sprintf(buffer, "Distance: %f", distance);
    Draw2DString(buffer, owner->getGLSize(), SbVec2f(20, 40 + vertmove));
  }
} // drawInformation()


void
SoQtSuperViewerP::resetCountAction()
{
  if(countaction != NULL){
    delete countaction;
    countaction = NULL;
  }
  
  cones = cubes = cylinders = spheres = 0;
  countaction = new SoGetPrimitiveCountAction;
 
  if(currentroot != NULL){  
    countaction->apply(currentroot); 

    searchaction = new SoSearchAction;
    searchaction->setInterest(SoSearchAction::ALL);
    searchaction->setType(SoCone::getClassTypeId(), TRUE);
    searchaction->apply(currentroot);
    cones = searchaction->getPaths().getLength();
    searchaction->reset();
    searchaction->setInterest(SoSearchAction::ALL);
    searchaction->setType(SoCube::getClassTypeId(), TRUE);
    searchaction->apply(currentroot);
    cubes = searchaction->getPaths().getLength();
    searchaction->reset();
    searchaction->setInterest(SoSearchAction::ALL);
    searchaction->setType(SoCylinder::getClassTypeId(), TRUE);
    searchaction->apply(currentroot);
    cylinders = searchaction->getPaths().getLength();
    searchaction->reset();
    searchaction->setInterest(SoSearchAction::ALL);
    searchaction->setType(SoSphere::getClassTypeId(), TRUE);
    searchaction->apply(currentroot);
    spheres = searchaction->getPaths().getLength();
    delete searchaction;
    searchaction = NULL;
  }
}

void
SoQtSuperViewerP::resetBBox()
{
  this->bboxaction = new SoGetBoundingBoxAction(owner->getViewportRegion());
  this->bboxaction->apply(currentroot);
  SbBox3f bboxvec = this->bboxaction->getBoundingBox();
  float minx, miny, minz, maxx, maxy, maxz;
  minx = miny = minz =  maxx = maxy = maxz = 0.0;
  bboxvec.getBounds(minx, miny, minz, maxx, maxy, maxz);
  this->bboxvertices->vertex.set1Value(0, minx, miny, minz);
  this->bboxvertices->vertex.set1Value(1, minx, miny, maxz);
  this->bboxvertices->vertex.set1Value(2, maxx, miny, maxz);
  this->bboxvertices->vertex.set1Value(3, maxx, miny, minz);
  this->bboxvertices->vertex.set1Value(4, minx, maxy, minz);
  this->bboxvertices->vertex.set1Value(5, minx, maxy, maxz);
  this->bboxvertices->vertex.set1Value(6, maxx, maxy, maxz);
  this->bboxvertices->vertex.set1Value(7, maxx, maxy, minz);
  this->bbox->coordIndex.setValues(0, 36, indices);
  delete this->bboxaction;
  this->bboxaction = NULL;
}

void
SoQtSuperViewerP::drawstyleRedraw()
{
  this->drawstyleroot->whichChild = SO_SWITCH_ALL;
  this->hiddenlineroot->whichChild = SO_SWITCH_ALL;
  this->polygonoffsetparent->whichChild = SO_SWITCH_NONE;
  this->lightmodel->model.setIgnored(FALSE);
  if(this->boundingboxesenabled){
    this->complexity->type = SoComplexity::BOUNDING_BOX;
    this->drawstyle->style = SoDrawStyle::LINES;
    owner->getSceneManager()->render(FALSE,FALSE);
    this->complexity->type = SoComplexity::OBJECT_SPACE;
    this->drawstyle->style = SoDrawStyle::FILLED;
  }
  if(this->wireframeenabled){
    if(this->filled){
      this->basecolor->rgb.setIgnored(FALSE);
      this->basecolor->rgb.setValue(this->linecolor);
    }
    this->drawstyle->style = SoDrawStyle::LINES;
    owner->getSceneManager()->render(FALSE,FALSE);
    this->drawstyle->style = SoDrawStyle::FILLED;
    if(this->filled){
      this->basecolor->rgb.setIgnored(TRUE);
    }
  } 

  if(this->verticesenabled){
    if(this->filled){
      this->basecolor->rgb.setIgnored(FALSE);
      this->basecolor->rgb.setValue(this->pointcolor);
    }
    this->drawstyle->style = SoDrawStyle::POINTS;
    owner->getSceneManager()->render(FALSE,FALSE);
    this->drawstyle->style = SoDrawStyle::FILLED;
    if(this->filled){
      this->basecolor->rgb.setIgnored(TRUE);
    }
  }
  this->lightmodel->model.setIgnored(TRUE);
  this->polygonoffsetparent->whichChild = SO_SWITCH_ALL;
  this->hiddenlineroot->whichChild = SO_SWITCH_NONE;
  this->drawstyleroot->whichChild = complexityindex;
  
}

void
SoQtSuperViewerP::movingRedraw(SbBool on)
{
  if(on){
    mt = mf = mv = mw = mb = FALSE;

    if(this->howtomove == SoQtSuperViewerP::NO_TEXTURES && 
       this->texturesenabled){
      owner->toggleTextures();
      mt = TRUE;
    }
    else if(this->howtomove == SoQtSuperViewerP::BBOXES){
      if(this->filled){ 
        owner->toggleFilled();
        mf = TRUE;
      }
      if(this->verticesenabled){ 
        owner->toggleVertices();
        mv = TRUE;
      }
      if(this->wireframeenabled){ 
        owner->toggleWireframe();
        mw = TRUE;
      }
      if(!this->boundingboxesenabled){ 
        owner->toggleBoundingboxes();
        mb = TRUE;
      }
    }
    else if(this->howtomove == SoQtSuperViewerP::ONE_BBOX){
      this->graphswitch->whichChild = 1;
    } 
  }
  else{
    if(this->howtomove == SoQtSuperViewerP::NO_TEXTURES && 
       mt){
      owner->toggleTextures();
    }
    else if(this->howtomove == SoQtSuperViewerP::BBOXES){
      if(mf) 
        owner->toggleFilled();
      if(mv)
        owner->toggleVertices();
      if(mw)
        owner->toggleWireframe();
      if(mb) 
        owner->toggleBoundingboxes();
    }
    else if(this->howtomove == SoQtSuperViewerP::ONE_BBOX){
      this->graphswitch->whichChild = 0;
    } 
  } 
}

void
SoQtSuperViewerP::changedMoving(SoQtSuperViewerP::WaysToMove how){
  this->howtomove = how;
}

void
SoQtSuperViewerP::changedMovingGUI(SoQtSuperViewerP::WaysToMove how){
  changedMoving(how);
  this->viewmenu->setItemChecked(
    this->viewmenu->idAt(this->movingitemchk), FALSE);
  if(how == SoQtSuperViewerP::FULL){
    this->viewmenu->setItemChecked(
      this->viewmenu->idAt(12), TRUE);
    this->movingitemchk = 12;
  }
  else if(how == SoQtSuperViewerP::ONE_BBOX){
    this->viewmenu->setItemChecked(
      this->viewmenu->idAt(10), TRUE);
    this->movingitemchk = 10;
  }
  else if(how == SoQtSuperViewerP::BBOXES){
    this->viewmenu->setItemChecked(
      this->viewmenu->idAt(11), TRUE);
    this->movingitemchk = 11;
  }
  else if(how == SoQtSuperViewerP::NO_TEXTURES){
    this->viewmenu->setItemChecked(
      this->viewmenu->idAt(13), TRUE);
    this->movingitemchk = 13;
  }
}

// *************************************************************************

/*!
  \internal

  Loads a model from file given by \c filename and returns a SoSeparator
  with the model.
*/

SoSeparator *
SoQtSuperViewerP::loadModelFromFile(SbString * const filename)
{
  SoInput in;
  SoSeparator * newroot;

  if (in.openFile(filename->getString())) {
    newroot = SoDB::readAll(&in);
    if (newroot) {
      return newroot;
    }
    else{
      SoDebugError::postInfo("SoQtSuperViewer::loadModelFromFile", 
                             "[no root loaded]");
      return NULL;
    }
  }
  else{
    SoDebugError::postInfo("SoQtSuperViewer::loadModelFromFile", 
                           "[opening file failed]");
    return NULL;
  }
} // loadModelFromFile()

// ************************************************************************

/*!
  \internal

  Rotate the camera by the given amount, then reposition it so we're still
  pointing at the same focal point.
*/

void
SoQtSuperViewerP::reorientCamera(
  const SbRotation & rot)
{
  SoCamera * cam = owner->getCamera();
  if (cam == NULL) return;

  // Find global coordinates of focal point.
  SbVec3f direction;
  cam->orientation.getValue().multVec(SbVec3f(0, 0, -1), direction);
  SbVec3f focalpoint = cam->position.getValue() +
    cam->focalDistance.getValue() * direction;

  // Set new orientation value by accumulating the new rotation.
  cam->orientation = rot * cam->orientation.getValue();

  // Reposition camera so we are still pointing at the same old focal point.
  cam->orientation.getValue().multVec(SbVec3f(0, 0, -1), direction);
  cam->position = focalpoint - cam->focalDistance.getValue() * direction;
} // reorientCamera()

// ************************************************************************

/*!
  \internal

  Uses the sphere sheet projector to map the mouseposition unto
  a 3D point and find a rotation from this and the last calculated point.
*/

void
SoQtSuperViewerP::spin(
  const SbVec2f & pointerpos)
{
  if (this->log.historysize < 2) return;
  assert(this->spinprojector != NULL);

  SbVec2s glsize(owner->getGLSize());
  SbVec2f lastpos;
  lastpos[0] = float(this->log.position[1][0]) / 
               float(SoQtMax((int)(glsize[0]-1), 1));
  lastpos[1] = float(this->log.position[1][1]) / 
               float(SoQtMax((int)(glsize[1]-1), 1));

  this->spinprojector->project(lastpos);
  SbRotation r;
  this->spinprojector->projectAndGetRotation(pointerpos, r);
  r.invert();
  this->reorientCamera(r);

  // Calculate an average angle magnitude value to make the transition
  // to a possible spin animation mode appear smooth.

  SbVec3f dummy_axis, newaxis;
  float acc_angle, newangle;
  this->spinincrement.getValue(dummy_axis, acc_angle);
  acc_angle *= this->spinsamplecounter; // weight
  r.getValue(newaxis, newangle);
  acc_angle += newangle;

  this->spinsamplecounter++;
  acc_angle /= this->spinsamplecounter;
  // FIXME: accumulate and average axis vectors aswell? 19990501 mortene.
  this->spinincrement.setValue(newaxis, acc_angle);

  // Don't carry too much baggage, as that'll give unwanted results
  // when the user quickly trigger (as in "click-drag-release") a spin
  // animation.
  if (this->spinsamplecounter > 3) 
    this->spinsamplecounter = 3;
} // spin()

// ************************************************************************

/*!
  \internal

  Move scene parallel with the plane orthogonal to the camera
  direction vector.
*/

void
SoQtSuperViewerP::pan(
  const SbVec2f & thispos,
  const SbVec2f & prevpos)
{
  SoCamera * cam = owner->getCamera();
  if (cam == NULL) return; // can happen for empty scenegraph
  if (thispos == prevpos) {
#if SOQT_DEBUG
    SoDebugError::postInfo("SoQtSuperViewer::pan", "useless invokation");
#endif // SOQT_DEBUG
    return;
  }

#if SOQT_DEBUG && 0
  SoDebugError::postInfo("SoQtSuperViewer::pan",
     "was(%.3g, %.3g) -> now(%.3g, %.3g)",
     prevpos[0], prevpos[1], thispos[0], thispos[1]);
#endif // SOQT_DEBUG

  // Find projection points for the last and current mouse coordinates.
  SbViewVolume vv = cam->getViewVolume(owner->getGLAspectRatio());
  SbLine line;
  vv.projectPointToLine(thispos, line);
  SbVec3f current_planept;
  this->panningplane.intersect(line, current_planept);
  vv.projectPointToLine(prevpos, line);
  SbVec3f old_planept;
  this->panningplane.intersect(line, old_planept);

  // Reposition camera according to the vector difference between the
  // projected points.
  cam->position = cam->position.getValue() - (current_planept - old_planept);
} // pan()

// ************************************************************************

/*!
  \internal

  Dependent on the camera type this will either shrink or expand
  the height of the viewport (orthogonal camera) or move the
  camera closer or further away from the focal point in the scene.
*/

void
SoQtSuperViewerP::zoom(
  const float diffvalue)
{
  SoCamera * cam = owner->getCamera();
  if (cam == NULL) return; // can happen for empty scenegraph
  SoType t = cam->getTypeId();

  // This will be in the range of <0, ->>.
  float multiplicator = exp(diffvalue);

  if (t.isDerivedFrom(SoOrthographicCamera::getClassTypeId())) {
    SoOrthographicCamera * oc = (SoOrthographicCamera *)cam;
    oc->height = oc->height.getValue() * multiplicator;
  } else if (t.isDerivedFrom(SoPerspectiveCamera::getClassTypeId())) {
    float oldfocaldist = cam->focalDistance.getValue();
    cam->focalDistance = oldfocaldist * multiplicator;

    SbVec3f direction;
    cam->orientation.getValue().multVec(SbVec3f(0, 0, -1), direction);
    cam->position = cam->position.getValue() +
      (cam->focalDistance.getValue() - oldfocaldist) * -direction;
  } else {
    assert(0 && "impossible");
  }
} // zoom()

// *************************************************************************

/*!
  \internal

  Calculate a zoom/dolly factor from the difference of the current
  cursor position and the last.
*/

void
SoQtSuperViewerP::zoomByCursor(
  const SbVec2f & thispos,
  const SbVec2f & prevpos)
{
  // There is no "geometrically correct" value, 20 just seems to give
  // about the right "feel".
  this->zoom((thispos[1] - prevpos[1]) * 20.0f);
} // zoomByCursor()

// *************************************************************************
// Methods used for spin animation tracking.

/*!
  This method "clears" the mouse location log, used for spin animation
  calculations.
*/

void
SoQtSuperViewerP::clearLog(
  void)
{
  this->log.historysize = 0;
} // clearLog()

/*!
  This method adds another point to the mouse location log, used for spin
  animation calculations.
*/

void
SoQtSuperViewerP::addToLog(
  const SbVec2s pos,
  const SbTime time)
{
  // In case someone changes the const size setting at the top of this
  // file too small.
  assert (this->log.size > 2 && "mouse log too small!");

  if (this->log.historysize > 0 && pos == this->log.position[0]) {
#if SOQT_DEBUG && 0 // debug
    // This can at least happen under SoQt.
    SoDebugError::postInfo("SoQtSuperViewer::addToLog", "got position already!");
#endif // debug
    return;
  }

  for (int i = this->log.size - 1; i > 0; i--) {
    this->log.position[i] = this->log.position[i-1];
    this->log.time[i] = this->log.time[i-1];
  }
  this->log.position[0] = pos;
  this->log.time[0] = time;
  if (this->log.historysize < this->log.size)
    this->log.historysize += 1;
} // addToLog()

// ************************************************************************

/*!
  \internal

  The viewer is a state machine, and all changes to the current state
  are made through this call.
*/

void
SoQtSuperViewerP::setMode(const ViewerMode mode)
{
  this->setCursorRepresentation(mode);

  switch (mode) {
  case FLYMODE:
    break;
  case INTERACT:
    // FIXME: this looks like someone fixed the symptom instead of
    // fixing the cause? 20010709 mortene.
    while (owner->getInteractiveCount())
      owner->interactiveCountDec();
    break;

  case DRAGGING:
    // Set up initial projection point for the projector object when
    // first starting a drag operation.
    this->spinprojector->project(this->lastmouseposition);
    break;

  case PANNING:
    {
      // The plane we're projecting the mouse coordinates to get 3D
      // coordinates should stay the same during the whole pan
      // operation, so we should calculate this value here.
      SoCamera * cam = owner->getCamera();
      if (cam == NULL) { // can happen for empty scenegraph
        this->panningplane = SbPlane(SbVec3f(0, 0, 1), 0);
      }
      else {
        SbViewVolume vv = cam->getViewVolume(owner->getGLAspectRatio());
        this->panningplane = vv.getPlane(cam->focalDistance.getValue());
      }
    }
    break;

  default: // include default to avoid compiler warnings.
    break;
  }

  this->currentmode = mode;
} // setMode()

// *************************************************************************

/*!
  \internal

  Set cursor graphics according to mode.
*/

void
SoQtSuperViewerP::setCursorRepresentation(int mode)
{
  // FIXME: with the new So@Gui@Cursor class, this has actually become
  // a possibly generic method for all So* toolkits. Move to common
  // code. 20011125 mortene.

  if (!owner->isCursorEnabled()) {
    owner->setComponentCursor(SoQtCursor::getBlankCursor());
    return;
  }

  switch (mode) {
  case SoQtSuperViewerP::FLYMODE:
  case SoQtSuperViewerP::INTERACT:
    owner->setComponentCursor(SoQtCursor(SoQtCursor::DEFAULT));
    break;

  case SoQtSuperViewerP::DRAGGING:
    owner->setComponentCursor(SoQtCursor::getRotateCursor());
    break;

  case SoQtSuperViewerP::ZOOMING:
    owner->setComponentCursor(SoQtCursor::getZoomCursor());
    break;

  case SoQtSuperViewerP::WAITING_FOR_SEEK:
    owner->setComponentCursor(SoQtCursor(SoQtCursor::CROSSHAIR));
    break;

  case SoQtSuperViewerP::WAITING_FOR_PAN:
  case SoQtSuperViewerP::PANNING:
    owner->setComponentCursor(SoQtCursor::getPanCursor());
    break;

  default: assert(0); break;
  }
} // setCursorRepresentation()

// *************************************************************************

/*!
  \internal

  Set background color.
*/

void
SoQtSuperViewerP::setBackgroundColor()
{
  SbColor initial = owner->getBackgroundColor();
  QColor rgb;
  // the multiplication and division by 255 is quite ugly, but I don't
  // see any other quick solutions that work. larsivi 20021904
  rgb.setRgb(initial[0]*255, initial[1]*255, initial[2]*255);
  QColor newcolor = QColorDialog::getColor(rgb, owner->getWidget());
  if(!newcolor.isValid()) return;
  owner->setBackgroundColor(
           SbColor(((float)newcolor.red())/255, ((float)newcolor.green())/255, 
                   ((float)newcolor.blue())/255));
} // setBackgroundColor()

// *************************************************************************

/*!
  \internal

  Set line color.
*/

void
SoQtSuperViewerP::setLineColor()
{
  QColor rgb;
  // the multiplication and division by 255 is quite ugly, but I don't
  // see any other quick solutions that work. larsivi 20021904
  rgb.setRgb(this->linecolor[0]*255, this->linecolor[1]*255,
             this->linecolor[2]*255);
  QColor newcolor = QColorDialog::getColor(rgb, owner->getWidget());
  if(!newcolor.isValid()) return;
  this->linecolor = SbColor(((float)newcolor.red())/255, ((float)newcolor.green())/255, 
                            ((float)newcolor.blue())/255);
} // setLineColor()

// *************************************************************************

/*!
  \internal

  Set point color.
*/

void
SoQtSuperViewerP::setPointColor()
{
  QColor rgb;
  // the multiplication and division by 255 is quite ugly, but I don't
  // see any other quick solutions that work. larsivi 20021904
  rgb.setRgb(this->pointcolor[0]*255, this->pointcolor[1]*255,
             this->pointcolor[2]*255);
  QColor newcolor = QColorDialog::getColor(rgb, owner->getWidget());
  if(!newcolor.isValid()) return;
  this->pointcolor = SbColor(((float)newcolor.red())/255, ((float)newcolor.green())/255, 
                            ((float)newcolor.blue())/255);
} // setPointColor()

// *************************************************************************

/*!
  Adds the camera entries when a new model is shown.
*/

void
SoQtSuperViewerP::createCameraEntries()
{
  int cameras = this->cameras.getLength();
  if(this->frontcamera) this->cameramenu->removeItemAt(6);

  for(int i = 0; i < cameras; i++)
    this->cameramenu->removeItemAt(6);

  this->findCameras();
  if(this->frontcamera)
    this->cameramenu->insertItem("Front camera", this, SLOT(frontSelected()));

  cameras = this->cameras.getLength();
  for(i = 0; i < cameras; i++){
    SbString cameraname = this->cameras[i]->getName().getString();
    if(cameraname.getLength() == 0)
      cameraname.sprintf("Camera %2i", 1 + i);
    this->cameramenu->insertItem(cameraname.getString(),
                                 this, SLOT(cameraSelected(int)));
  }

  this->cameraitemchk = 6;
  this->cameramenu->setItemChecked(this->cameramenu->idAt(6), TRUE);

} // createCameraEntries()

// *************************************************************************

/*!
  Adds the light entries when a new model is shown.
*/

void
SoQtSuperViewerP::createLightEntries()
{
  int lights = this->lights.getLength();
  this->lightsmenu->clear();

  this->findLights();
  
  this->lightsmenu->insertItem("Head light", this, SLOT(lightSelected(int)));

  lights = this->lights.getLength();
  for(int i = 0; i < lights; i++){
    SbString lightname = this->lights[i]->getName().getString();
    if(lightname.getLength() == 0)
      lightname.sprintf("Light %2i", 1 + i);
    this->lightsmenu->insertItem(lightname.getString(),
                                 this, SLOT(lightSelected(int)));
  }

  this->lightsmenu->setItemChecked(this->lightsmenu->idAt(0), TRUE);

} // createLightEntries()

#define DIRECTION_NONE 0
#define DIRECTION_FWD  1
#define DIRECTION_BACK 2

/*!
  Internal method that handles mouse events.
*/
SbBool
SoQtSuperViewerP::processMouseEvent(const SoEvent * const event)
{
  SoType eventtype = event->getTypeId();
  
  SbVec2s winsize = owner->getViewportRegion().getWindowSize();
  SbVec2s mousepos = event->getPosition();

  // keep button state in sync
  SbBool leftbuttonevent = FALSE;
  SbBool rightbuttonevent = FALSE;
  SbBool midbuttonevent = FALSE;
  SbBool mousepressevent = FALSE;
  SbBool mousereleaseevent = FALSE;

  if (SO_MOUSE_PRESS_EVENT(event, BUTTON1)) {
    leftbuttonevent = TRUE;
    mousepressevent = TRUE;
    this->button1down = TRUE;
  }
  else if (SO_MOUSE_RELEASE_EVENT(event, BUTTON1)) {
    leftbuttonevent = TRUE;
    mousereleaseevent = TRUE;
    this->button1down = FALSE; 
  }
  else if (SO_MOUSE_PRESS_EVENT(event, BUTTON3)) {
    midbuttonevent = TRUE;
    mousepressevent = TRUE;
    this->button3down = TRUE;
  }
  else if (SO_MOUSE_RELEASE_EVENT(event, BUTTON3)) {
    midbuttonevent = TRUE;
    mousereleaseevent = TRUE;
    this->button3down = FALSE; 
  }
  else if (SO_MOUSE_PRESS_EVENT(event, BUTTON2)) {
    rightbuttonevent = TRUE;
    mousepressevent = TRUE;
    this->button2down = TRUE;
  }
  else if (SO_MOUSE_RELEASE_EVENT(event, BUTTON2)) {
    rightbuttonevent = TRUE;
    mousereleaseevent = TRUE;
    this->button2down = FALSE; 
  }

  if (mousepressevent) {
    this->mousedownpos = mousepos;
    this->flydirection = DIRECTION_NONE;
    this->currentmode = WAITING_FOR_FLY;
    this->prevRedrawTime = SbTime::getTimeOfDay();
    return FALSE;
  }
  else if (mousereleaseevent) {
    this->currentmode = IDLE;
    this->shouldscheduleredraw = TRUE;
    return FALSE;
  }
  else if (eventtype == SoLocation2Event::getClassTypeId()) {
    this->mousepos = mousepos;
    if (this->currentmode == WAITING_FOR_FLY) {
      this->currentmode = this->flymode;
      this->prevRedrawTime = SbTime::getTimeOfDay();
    }
  }
  return FALSE;
}

// *************************************************************************

/*!
  Callback for the animation timer.
*/
void
SoQtSuperViewerP::timercb(void *data, SoSensor *)
{
  ((SoQtSuperViewerP*)data)->pulse();
} // timercb()

// *************************************************************************

/*!
  Sensor callback when camera position changes,
*/
void
SoQtSuperViewerP::camera_pos_cb(void * data, SoSensor * sensor)
{
  static SbTime prevtime = SbTime::zero();
  static SbVec3f prevpos = SbVec3f(0.0, 0.0, -200000.0);

  SoQtSuperViewerP * thisp = (SoQtSuperViewerP*) data;
  SoCamera * camera = (SoCamera*) thisp->owner->getCamera();
 
  SbVec3f pos(0.0, 0.0, 0.0);
  SbVec3f offset(0.0f, 0.0f, 0.0f);

  offset = camera->position.getValue();

  pos[0] += offset[0];
  pos[1] += offset[1];
  pos[2] += offset[2];
  SbVec3f newpos = pos;

  float elev;
  thisp->elevation = -1.0f;

  SbVec3f tmp(offset[0], offset[1], offset[2]);

  if (pos != newpos) {
    thisp->camerapossensor->detach();
 
    camera->position = SbVec3f(offset[0], offset[1], (float) newpos[2]);
    thisp->camerapossensor->attach(&camera->position);
  }

  double dist = (newpos-prevpos).length();
  if (dist < 1000.0) {
    thisp->movedist += (float) dist;
  }
  prevpos = newpos;
}

// *************************************************************************

/*!
  Sensor callback when camera oreintation changes,
*/
void
SoQtSuperViewerP::camera_orient_cb(void * data, SoSensor *)
{
  SoQtSuperViewerP * thisp = (SoQtSuperViewerP*) data;
  thisp->camerarot.setRotate(thisp->currcam->orientation.getValue());
}

// *************************************************************************

/*!
  Internal method called from the timer callback.
*/
void
SoQtSuperViewerP::pulse(void)
{
  // FIXME: No Joystick support for now.
  // larsivi 20020430

  if (!this->pause && !this->busy) {
    switch (this->currentmode) {
    case IDLE:
    case WAITING_FOR_FLY:
    case INTERACT:
    case DRAGGING:
    case WAITING_FOR_SEEK:
    case ZOOMING:
    case WAITING_FOR_PAN:
    case PANNING:
    case WAIT_RB_RELEASE:
      break;
    case FLYMODE:
      this->flyPulse();
      break;
    case GLIDEMODE:
      this->glidePulse();
      break;
    case LOCKEDMODE:
      this->lockedPulse();
      break;
    default:
      break;
    }
  }
  if (this->shouldscheduleredraw) {
    owner->scheduleRedraw();
    this->shouldscheduleredraw = FALSE;
  }
  this->prevRedrawTime = SbTime::getTimeOfDay();
}


/*!
  Pulse while gliding.
*/
void
SoQtSuperViewerP::glidePulse(SbBool joystick)
{
  int dx;
  int dy;
  
  dx = this->mousepos[0] - this->mousedownpos[0];
  dy = - (this->mousepos[1] - this->mousedownpos[1]);
  
  float xmov = float(dx) / 7000.0f;
  float ymov = float(dy) / 6000.0f;
  
  this->yawCamera(-ymov);
  this->pitchCamera(-xmov);
  this->moveCamera(
        SbVec3f(0.0f, 0.0f, -SbAbs(this->relspeedglide*this->glidespeed)), TRUE);
  this->resetRoll();
  this->rollCamera(-xmov*8.0f);
}

/*!
  Pulse while flying.
*/
void
SoQtSuperViewerP::flyPulse(SbBool joystick)
{
  SbVec2s winsize = owner->getViewportRegion().getWindowSize();

  int dx;
  int dy;
  // FIXME Joystick support disabled for now.
  // larsivi 20020430
   
  dx = this->mousepos[0] - this->mousedownpos[0];
  dy = - (this->mousepos[1] - this->mousedownpos[1]);
    
  if (this->button1down) {
    if (dy > 0 && this->flydirection == DIRECTION_BACK) {
      dy -= 20;
      if (dy < 0) dy = 0;
    }
    else if (dy < 0 && this->flydirection == DIRECTION_FWD) {
      dy += 20;
      if (dy > 0) dy = 0;
    }
    
    if (dx == 0 && dy == 0) return;
    this->relspeedfly = SbAbs(float(dy))/float(winsize[1]);
    this->moveCamera(SbVec3f(0.0f, 0.0f, (float)dy), TRUE);
    if (this->flydirection == DIRECTION_NONE && dy) {
      if (dy > 0) this->flydirection = DIRECTION_FWD;
      else this->flydirection = DIRECTION_BACK;
    }
    this->pitchCamera(((float)-dx/float(winsize[0])) * 0.1f);
  }
  else if (this->button2down) {
    if (dx == 0 && dy == 0) return;
    this->pitchCamera(((float)-dx / float(winsize[0])) * 0.1f);
    this->yawCamera(((float)-dy / float(winsize[1])) * 0.1f);
  }
  else if (this->button3down) {
    if (dx == 0 && dy == 0) return;
    float fx = float(dx) / float(winsize[0]);
    float fy = float(dy) / float(winsize[1]);
    this->relspeedfly = (float) sqrt(fx*fx+fy*fy);
    this->moveCamera(SbVec3f((float)dx,
                             (float)(-dy),
                             0.0f), TRUE);
  }
}

void
SoQtSuperViewerP::lockedPulse(SbBool joystick)
{
  SbVec2s winsize = owner->getViewportRegion().getWindowSize();

  int dx = this->mousepos[0] - this->mousedownpos[0];
  int dy = -(this->mousepos[1] - this->mousedownpos[1]);

  if (this->button1down) {
    if (dx == 0 && dy == 0) return;
    if (dy > 0) {
      this->flydirection = DIRECTION_FWD;
    }
    else if (dy < 0) {
      this->flydirection = DIRECTION_BACK;
    }
    float fx = float(dx) / float(winsize[0]);
    float fy = float(dy) / float(winsize[1]);
    this->relspeedfly = (float) sqrt(fx*fx+fy*fy);

    this->moveCamera(SbVec3f((float)dx, 0.0f, (float)dy), TRUE);
    if (this->flydirection == DIRECTION_NONE && dy) {
      if (dy > 0) this->flydirection = DIRECTION_FWD;
      else this->flydirection = DIRECTION_BACK;
    }
  }
  else if (this->button2down) {
    if (dx == 0 && dy == 0) return;
    this->pitchCamera(((float)-dx / float(winsize[0])) * 0.1f);
    this->yawCamera(((float)-dy / float(winsize[1])) * 0.1f);
  }
  else if (this->button3down) {
    if (dy == 0) return;
    float fy = float(dy) / float(winsize[0]);
    this->relspeedfly = SbAbs(fy);
    this->moveCamera(SbVec3f(0.0f, 0.0f, -dy), FALSE);
  }
}

// *************************************************************************

/*!
  Yaw camera with \a rad radians.
*/
void
SoQtSuperViewerP::yawCamera(const float rad)
{
  SoCamera * camera = owner->getCamera();
  SbMatrix yawmat;
  yawmat.setRotate(SbRotation(SbVec3f(1.0f, 0.0f, 0.0f), rad));
  this->camerarot.multLeft(yawmat);
  this->normalizeCamera();
  camera->orientation = SbRotation(this->camerarot);
  this->resetRoll();
}

// *************************************************************************

/*!
  Roll camera with \a rad radians.
*/

void
SoQtSuperViewerP::rollCamera(const float rad)
{
  SoCamera * camera = owner->getCamera();
  SbMatrix rollmat;
  rollmat.setRotate(SbRotation(SbVec3f(0.0f, 0.0f, 1.0f), rad));
  this->camerarot.multLeft(rollmat);
  this->normalizeCamera();
  camera->orientation = SbRotation(this->camerarot);
}

// *************************************************************************

/*!
  Pitch camera with \a rad radians.
*/
void
SoQtSuperViewerP::pitchCamera(const float rad)
{
  SoCamera * camera = owner->getCamera();
  SbMatrix pitchmat;
  pitchmat.setRotate(SbRotation(SbVec3f(0.0f, 1.0f, 0.0f), rad));
  this->camerarot.multLeft(pitchmat);
  this->normalizeCamera();
  camera->orientation = SbRotation(this->camerarot);
  this->resetRoll();
}
/*!
  Normalize camera. Done to avoid accummulating error.
*/

// *************************************************************************

void
SoQtSuperViewerP::normalizeCamera(void)
{
  SbVec3f x, y, z;
  x[0] = this->camerarot[0][0];
  x[1] = this->camerarot[0][1];
  x[2] = this->camerarot[0][2];

  y[0] = this->camerarot[1][0];
  y[1] = this->camerarot[1][1];
  y[2] = this->camerarot[1][2];

  x.normalize();
  y.normalize();
  z = x.cross(y);
  z.normalize();

  this->camerarot[0][0] = x[0];
  this->camerarot[0][1] = x[1];
  this->camerarot[0][2] = x[2];

  this->camerarot[1][0] = y[0];
  this->camerarot[1][1] = y[1];
  this->camerarot[1][2] = y[2];

  this->camerarot[2][0] = z[0];
  this->camerarot[2][1] = z[1];
  this->camerarot[2][2] = z[2];

  this->camerarot[3][0] = 0.0f;
  this->camerarot[3][1] = 0.0f;
  this->camerarot[3][2] = 0.0f;
  this->camerarot[3][3] = 1.0f;
  this->camerarot[0][3] = 0.0f;
  this->camerarot[1][3] = 0.0f;
  this->camerarot[2][3] = 0.0f;
}

// *************************************************************************

/*!
  Resets the roll. Useful if you want the "up" vector of the camera to
  be pointing as much up as possible.
*/
void
SoQtSuperViewerP::resetRoll(void)
{
  if (!this->doresetroll) return;
  SbVec3f newy = this->viewupaxis;
  if (newy == SbVec3f(0.0f, 0.0f, 0.0f)) return;
  SbVec3f Z;
  Z[0] = this->camerarot[2][0];
  Z[1] = this->camerarot[2][1];
  Z[2] = this->camerarot[2][2];

  if (fabs(Z.dot(newy)) > 0.99f) {
    // just give up
    return;
   }
  SbVec3f newx = newy.cross(Z);
  newy = Z.cross(newx);

  newx.normalize();
  newy.normalize();

  this->camerarot[0][0] = newx[0];
  this->camerarot[0][1] = newx[1];
  this->camerarot[0][2] = newx[2];

  this->camerarot[1][0] = newy[0];
  this->camerarot[1][1] = newy[1];
  this->camerarot[1][2] = newy[2];
}

// *************************************************************************

/*!
  Convenience metod that moves the current camera. This must be
  used if you intend to record the speed of the camera.
*/

void
SoQtSuperViewerP::moveCamera(const SbVec3f &vec, const SbBool dorotate)
{
  if (vec.sqrLength() == 0.0f) return;
  SoCamera * camera = (SoCamera*) owner->getCamera();
 
  SbVec3f dst = vec;
  if (dorotate) {
    this->camerarot.multDirMatrix(vec, dst);
  }
  if (this->flymode == LOCKEDMODE && dorotate) dst[2] = 0.0f;

  float speed = this->flymode == GLIDEMODE ?
    this->glidespeed*this->relspeedglide :
    this->flyspeed*this->relspeedfly;

  SbTime difftime = SbTime::getTimeOfDay() - this->prevRedrawTime;
  float diffval = (float) difftime.getValue();
  // if slower than 10fps, ignore difftime. This avoids large jumps in terrain
  float dist = SbMin(diffval, 0.1f) * speed;

  if (dist == 0.0f) return;

  camera->position = camera->position.getValue() + dst*dist;
}

// *************************************************************************
// *************************************************************************

/*!
  \internal slot

  All models selected in the filedialog that pops up, are tried loaded from
  disk. The models are added to the internal list of models and the model
  list in the menu. The last model that is opened is set up to be viewed by
  the viewer.
*/

void
SoQtSuperViewerP::openModelSelected()
{

  QStringList qs(QFileDialog::getOpenFileNames(
    owner->getFileFilter().getString(), 
    owner->getModelDirectory().getString()));
  qs.sort();
  if(!qs.isEmpty()){
    for(QStringList::Iterator i = qs.begin(); i != qs.end(); ++i) {
      SbString s((* i).latin1());
      if(owner->openModel(&s, FALSE))
        owner->addModelEntry(
          this->modelnames[this->modelnames.getLength() - 1]);

    }
    if(this->currentroot != NULL)
      this->modelSelected(this->modelsubmenu->idAt(
                          this->openmodels->getNumChildren() - 1));
  }
} // openModelSelected()

// *************************************************************************

/*!
  \internal slot

  The currently viewed model is closed and removed from the list. If it 
  was the last open model, the list is removed from the menu altogether.
*/

SbBool
SoQtSuperViewerP::closeModelSelected()
{
  if(this->openmodels){
    if(this->openmodels->getNumChildren() > 0){
      this->openmodels->removeChild(this->currentroot);

      delete this->pathtomodels[this->currentindex];
      this->pathtomodels.remove(this->currentindex);
      delete this->modelnames[this->currentindex];
      this->modelnames.remove(this->currentindex);
   
      owner->removeModelEntry();
      if(this->openmodels->getNumChildren() > 0){
        owner->showModel( --this->currentindex < 0 ? 
                         0 : this->currentindex );
      }
      else{
        owner->setSceneGraph(NULL);
        this->openmodels->unref();
        this->openmodels = NULL;
        this->currentindex = -1;
        this->filemenu->removeItemAt(3);
        this->filemenu->setItemEnabled(
                                 this->filemenu->idAt(1), FALSE);
        this->filemenu->setItemEnabled(
                                 this->filemenu->idAt(2), FALSE);
        this->filemenu->setItemEnabled(
                                 this->filemenu->idAt(4), FALSE);
        this->filemenu->setItemEnabled(
                                 this->filemenu->idAt(5), FALSE);
        this->filemenu->setItemEnabled(
                                 this->filemenu->idAt(6), FALSE);
        this->filemenu->setItemEnabled(
                                 this->filemenu->idAt(7), FALSE);
        this->menubar->setItemEnabled(
                                 this->menubar->idAt(1), FALSE);
        this->menubar->setItemEnabled(
                                 this->menubar->idAt(2), FALSE);
        this->menubar->setItemEnabled(
                                 this->menubar->idAt(3), FALSE);
        this->menubar->setItemEnabled(
                                 this->menubar->idAt(4), FALSE);
        delete this->modelsubmenu;
        this->modelsubmenu = NULL;
        owner->setTitle(owner->getDefaultTitle());
      }
      return TRUE;
    }
    else{
      return FALSE;
    }
  }
  else{
    return FALSE;
  }
                                                      
} // closeModelSelected()

// *************************************************************************

/*!
  \internal slot

  Closes all open models and removes the model list from the menu.
*/

void
SoQtSuperViewerP::closeAllSelected()
{
  while(this->closeModelSelected());
} // closeAllSelected()

// *************************************************************************

/*!
  \internal slot

  Sets the next model in the list as the current model and sets up the
  viewer to view this. If the current model before nextModelSelected()
  is called is the last in the list, the first model in the list is chosen.
*/

void
SoQtSuperViewerP::nextModelSelected()
{
  owner->showModel( ++this->currentindex < 
                   this->openmodels->getNumChildren() ? 
                   this->currentindex : 0 );
  this->createCameraEntries();
  this->createLightEntries();
} //nextModelSelected()

// *************************************************************************

/*!
  \internal slot
  
  Sets the previous model in the list as the current model and sets up the
  viewer to view this. If the current model before previousModelSelected()
  is called is the first in the list, the last model in the list is chosen.
*/

void
SoQtSuperViewerP::previousModelSelected()
{
  owner->showModel( --this->currentindex < 0 ? 
                   this->openmodels->getNumChildren() - 1 : 
                   this->currentindex );
  this->createCameraEntries();
  this->createLightEntries();
} //previousModelSelected()

// *************************************************************************

/*!
  \internal slot

  Sets the model given by \c id as the current model and sets up the viewer
  to view this. The id is converted to the index that the model has in the
  list.
*/

void
SoQtSuperViewerP::modelSelected(int id)
{
  owner->showModel(this->modelsubmenu->indexOf(id));

  if(this->modeltextures[this->currentindex] <= 0){
    this->viewmenu->setItemEnabled(
                             this->viewmenu->idAt(8), FALSE);
    this->settingsmenu->setItemEnabled(
                             this->settingsmenu->idAt(7), FALSE);
    this->texturesenabled = FALSE;
  }
  else{
    this->viewmenu->setItemEnabled(
                             this->viewmenu->idAt(8), TRUE);
    this->viewmenu->setItemChecked(
                             this->viewmenu->idAt(8), TRUE);
    this->settingsmenu->setItemEnabled(
                             this->settingsmenu->idAt(7), TRUE);
    this->texturesenabled = TRUE;
  }
  this->createCameraEntries();
  this->createLightEntries();

} // modelSelected()

// *************************************************************************

/*!
  \internal slot

  Reloads the current model from file.
*/

void
SoQtSuperViewerP::refreshSelected()
{
  this->currentroot = 
    this->loadModelFromFile(
          this->pathtomodels[this->currentindex]); 
  this->openmodels->replaceChild(this->currentindex,
                                          this->currentroot);
  owner->showModel(this->currentindex);
} // refreshSelected()

// *************************************************************************

/*!
  \internal slot

  Saves the current view of the current model as a file. 
  The formats available through simage will be choosable
  in the filedialog.
*/

void
SoQtSuperViewerP::snapshotSelected()
{
  SoOffscreenRenderer * wtf = 
    new SoOffscreenRenderer(owner->getViewportRegion());
  wtf->render(owner->getSceneManager()->getSceneGraph());
  int numft = wtf->getNumWriteFiletypes();

  SbString filter("");
  SbList<SbName> ext;
  SbList<SbName> extensions;
  SbList<SbName> psrgbextensions;
  SbStringList filters;
  SbString fullname = "";
  SbString description = "";

  if(!wtf->isWriteSupported("rgb")){
    psrgbextensions.append(SbName("rgb"));
    filter = "SGI RGB (*.rgb)";
    filters.append(new SbString("SGI RGB (*.rgb)"));
  }
  if(!wtf->isWriteSupported("eps")){
    if(filter.getLength() > 0) filter.operator+=(";;");
    filter.operator+=("Encapsulated PostScript (*.ps *.eps)");
    psrgbextensions.append(SbName("ps"));
    psrgbextensions.append(SbName("eps"));
    filters.append(new SbString("Adobe PostScript (*.ps *.eps)"));
  }

  for(int i = 0; i < numft; i++){
    SbString temp;
    wtf->getWriteFiletypeInfo(i, ext, fullname, description);
    filter.operator+=(";;");
    temp = fullname.getString();
    temp.operator+=(" (");
    for(int j = 0; j < ext.getLength(); j++){
      if (j > 0) temp.operator+=(" ");
      temp.operator+=("*.");
      temp.operator+=((SbName)ext[j].getString());
    }
    temp.operator+=(")");
    filters.append(new SbString(temp));
    filter.operator+=(temp);
  }
    
  QFileDialog * filedialog = new QFileDialog(
    owner->getImageDirectory().getString(), filter.getString(), 
    NULL, "Save image to file", TRUE);
  filedialog->setMode(QFileDialog::AnyFile);
  filedialog->setViewMode(QFileDialog::Detail);
  filedialog->show();
  if(filedialog->result()){ // check for cancel
    QString qsf(filedialog->selectedFilter());
    QString qss(filedialog->selectedFile());
    
    int filtnum = 0;
    for(int m = 0; m < filters.getLength(); m++){
      if(operator==(*filters[m], qsf.latin1())){
        filtnum = m;
        break;
      }
    }

    SbString filename(qss.latin1());
    SbName extension = "";
    if(psrgbextensions.getLength() > 0){
      for(int k = 0; k < psrgbextensions.getLength(); k++){
        SbIntList templist;
        if(!filename.findAll(((SbName)psrgbextensions[k]).getString(), templist))
          continue;
       if(templist.getLength() > 0 &&
           (filename[templist[templist.getLength() - 1] - 1] == '.') &&
	    (templist[templist.getLength() - 1] == 
	    (filename.getLength() - ((SbName)psrgbextensions[k]).getLength()))){
          extension = (SbName)psrgbextensions[k];
          break;
        }
      }
    }
    else{
      wtf->getWriteFiletypeInfo(filtnum -
           (psrgbextensions.getLength() > 2 ? 2 : 
           (psrgbextensions.getLength() == 0 ? 0 : 1)), 
           ext, fullname, description);
      for(int k = 0; k < ext.getLength(); k++){
        SbIntList templist;
        if(!filename.findAll(((SbName)ext[k]).getString(), templist))
          continue;
         if(templist.getLength() > 0 &&
           (filename[templist[templist.getLength() - 1] - 1] == '.') &&
	     (templist[templist.getLength() - 1] == 
	     (filename.getLength() - ((SbName)ext[k]).getLength()))){
          extension = (SbName)ext[k];
          break;
        }
      }
    }
    if(!extension.getLength()){
      switch(filtnum + (psrgbextensions.getLength() > 2 ? 0 : 
                       (psrgbextensions.getLength() == 0 ? 2 : 1))){
      case 0:
        extension = (SbName)psrgbextensions[0];
        break;
      case 1:
        extension = (SbName)psrgbextensions[1];
        break;
      default:
        extension = (SbName)ext[0];
        break;
      }
      filename.operator+=(".");
      filename.operator+=(SbString(extension.getString()));
    }
    
    switch(filtnum + (psrgbextensions.getLength() > 2 ? 0 : 
                     (psrgbextensions.getLength() == 0 ? 2 : 1))){
    case 0:
      wtf->writeToRGB(filename.getString());
      break;
    case 1:
      wtf->writeToPostScript(filename.getString());
      break;
    default:
      wtf->writeToFile(filename.getString(), extension);
      break;
    }
  }
  
  while(filters.getLength()){
    delete filters[0];
    filters.remove(0);
  }
  
  delete wtf;
  delete filedialog;

} // snapshotSelected()

// *************************************************************************

/*!
  \internal slot

  Quits the application.
*/

void
SoQtSuperViewerP::quitSelected()
{
  SoQt::exitMainLoop();
} // quitSelected()

// *************************************************************************

/*!
  \internal slot

  Turns the modelfill on or off.
*/

void
SoQtSuperViewerP::filledSelected()
{
  owner->isFilled() ? this->viewmenu->setItemChecked(
                       this->viewmenu->idAt(3), FALSE) :
                     this->viewmenu->setItemChecked(
                       this->viewmenu->idAt(3), TRUE);

  owner->isFilled() ? this->viewmenu->setItemEnabled(
                       this->viewmenu->idAt(7), TRUE):
                     this->viewmenu->setItemEnabled(
                       this->viewmenu->idAt(7), FALSE);
 
  owner->toggleFilled();
} // filledSelected()

// *************************************************************************

/*!
  \internal slot

  Turns scene information on or off.
*/

void
SoQtSuperViewerP::informationSelected()
{
  if(owner->isInformation()){
    this->viewmenu->setItemChecked(
                    this->viewmenu->idAt(0), FALSE);
    this->settingsmenu->setItemEnabled(
                        this->settingsmenu->idAt(0), FALSE);
  }
  else{
    this->viewmenu->setItemChecked(
                    this->viewmenu->idAt(0), TRUE);
    this->settingsmenu->setItemEnabled(
                        this->settingsmenu->idAt(0), TRUE);
  }

  owner->toggleInformation();
} // informationSelected()

// *************************************************************************

/*!
  \internal slot

  Turns flatshading of the scene on or off.
*/

void
SoQtSuperViewerP::flatshadingSelected()
{
  owner->isFlatshading() ? this->viewmenu->setItemChecked(
                            this->viewmenu->idAt(1), FALSE) :
                          this->viewmenu->setItemChecked(
                            this->viewmenu->idAt(1), TRUE);

  owner->toggleFlatshading();
} // flatshadingSelected()

// *************************************************************************

/*!
  \internal slot

  Turns boundingboxes on or off.
*/

void
SoQtSuperViewerP::boundingboxesSelected()
{
  owner->isBoundingboxes() ? this->viewmenu->setItemChecked(
                              this->viewmenu->idAt(4), FALSE) :
                            this->viewmenu->setItemChecked(
                              this->viewmenu->idAt(4), TRUE);

  owner->toggleBoundingboxes();

} // boundingboxesSelected()

// *************************************************************************

/*!
  \internal slot

  Turns the wireframe on or off.
*/

void
SoQtSuperViewerP::wireframeSelected()
{
  
  owner->isWireframe() ? this->viewmenu->setItemChecked(
                              this->viewmenu->idAt(5), FALSE) :
                            this->viewmenu->setItemChecked(
                              this->viewmenu->idAt(5), TRUE);

  owner->toggleWireframe();
} // wireframeSelected()

// *************************************************************************

/*!
  \internal slot

  Turns the vertices on or off.
*/

void
SoQtSuperViewerP::verticesSelected()
{
  
  owner->isVertices() ? this->viewmenu->setItemChecked(
                              this->viewmenu->idAt(6), FALSE) :
                            this->viewmenu->setItemChecked(
                              this->viewmenu->idAt(6), TRUE);

  owner->toggleVertices();
} // verticesSelected()

// *************************************************************************

/*!
  \internal slot

  Turns the hiddenparts on or off.
*/

void
SoQtSuperViewerP::hiddenpartsSelected()
{
  
  owner->isHiddenparts() ? this->viewmenu->setItemChecked(
                            this->viewmenu->idAt(7), FALSE) :
                          this->viewmenu->setItemChecked(
                            this->viewmenu->idAt(7), TRUE);

  owner->toggleHiddenparts();
} // hiddenpartsSelected()

// *************************************************************************

/*!
  \internal slot

  Turns the textures on or off.
*/

void
SoQtSuperViewerP::texturesSelected()
{
  if(owner->isTextures()){
    this->viewmenu->setItemChecked(
                    this->viewmenu->idAt(8), FALSE);
    this->settingsmenu->setItemEnabled(
                        this->settingsmenu->idAt(7), FALSE);
  }
  else{
    this->viewmenu->setItemChecked(
                    this->viewmenu->idAt(8), TRUE);
    this->settingsmenu->setItemEnabled(
                        this->settingsmenu->idAt(7), TRUE);
  }

  owner->toggleTextures();
} // hiddenpartsSelected()

// *************************************************************************

/*!
  \internal slots

  Chooses the correct setting for how the model should appear when moving.
*/

void 
SoQtSuperViewerP::fullMovingSelected() 
{ 
  this->changedMovingGUI(SoQtSuperViewerP::FULL); 
}

void
SoQtSuperViewerP::bBoxesMovingSelected()
{ 
  this->changedMovingGUI(SoQtSuperViewerP::BBOXES); 
}

void
SoQtSuperViewerP::oneBBoxMovingSelected()
{ 
  this->changedMovingGUI(SoQtSuperViewerP::ONE_BBOX);
}

void
SoQtSuperViewerP::noTexturesMovingSelected()
{ 
  this->changedMovingGUI(SoQtSuperViewerP::NO_TEXTURES);
}

// *************************************************************************

/*!
  \internal slot

  Turns the distance in the information display on or off.
*/

void
SoQtSuperViewerP::distanceSelected()
{
  owner->isDistance() ? this->informationsubmenu->setItemChecked(
                         this->informationsubmenu->idAt(0), FALSE) :
                       this->informationsubmenu->setItemChecked(
                         this->informationsubmenu->idAt(0), TRUE);

  owner->toggleDistance();
} // distanceSelected()

// *************************************************************************

/*!
  \internal slot

  Changes the line width value.
*/

void
SoQtSuperViewerP::linewidthSelected(int value)
{
  owner->setLineWidth(value);
} // linewidthSelected()

// *************************************************************************

/*!
  \internal slot

  Changes the point size value.
*/

void
SoQtSuperViewerP::pointsizeSelected(int value)
{
  owner->setPointSize(value);
} // pointsizeSelected()

// *************************************************************************

/*!
  \internal slot

  Changes the line color.
*/

void
SoQtSuperViewerP::linecolorSelected()
{
  this->setLineColor();
} // linecolorSelected()

// *************************************************************************

/*!
  \internal slot

  Changes the point color.
*/

void
SoQtSuperViewerP::pointcolorSelected()
{
  this->setPointColor();
} // pointcolorSelected()

// *************************************************************************

/*!
  \internal slot

  Changes the background color.
*/

void
SoQtSuperViewerP::backgroundcolorSelected()
{
  this->setBackgroundColor();
} // backgroundcolorSelected()

// *************************************************************************

/*!
  \internal slot

  Sets the chosen transparency type.
*/

void
SoQtSuperViewerP::transparencytypeSelected(int id)
{
  int index = this->transparencysubmenu->indexOf(id);
  this->transparencysubmenu->setItemChecked(
        this->transparencysubmenu->idAt(this->transparencyitemchk), FALSE);
  this->transparencysubmenu->setItemChecked(
        this->transparencysubmenu->idAt(index), TRUE);
  this->transparencyitemchk = index;
  switch(index){
  case 0:
    owner->setTransparencyType(SoGLRenderAction::SCREEN_DOOR);
    break;
  case 1:
    owner->setTransparencyType(SoGLRenderAction::ADD);
    break;
  case 2:
    owner->setTransparencyType(SoGLRenderAction::DELAYED_ADD);
    break;
  case 3:
    owner->setTransparencyType(SoGLRenderAction::SORTED_OBJECT_ADD);
    break;
  case 4:
    owner->setTransparencyType(SoGLRenderAction::BLEND);
    break;
  case 5:
    owner->setTransparencyType(SoGLRenderAction::DELAYED_BLEND);
    break;
  case 6:
    owner->setTransparencyType(SoGLRenderAction::SORTED_OBJECT_BLEND);
    break;
  case 7:
    owner->setTransparencyType(SoGLRenderAction::SORTED_OBJECT_SORTED_TRIANGLE_ADD);
    break;
  case 8:
    owner->setTransparencyType(SoGLRenderAction::SORTED_OBJECT_SORTED_TRIANGLE_BLEND);
    break;
  }
} // transparencytypeSelected()

// *************************************************************************

/*!
  \internal slot

  Chooses object space rendering.
*/

void
SoQtSuperViewerP::objectspaceSelected()
{
  this->renderqualitysubmenu->setItemChecked(
        this->renderqualitysubmenu->idAt(1), FALSE);
  this->renderqualitysubmenu->setItemChecked(
        this->renderqualitysubmenu->idAt(0), TRUE);
  owner->setRenderType(SoComplexity::OBJECT_SPACE);
} // objectspaceSelected()

// *************************************************************************

/*!
  \internal slot

  Chooses screen space rendering.
*/

void
SoQtSuperViewerP::screenspaceSelected()
{
  this->renderqualitysubmenu->setItemChecked(
        this->renderqualitysubmenu->idAt(0), FALSE);
  this->renderqualitysubmenu->setItemChecked(
        this->renderqualitysubmenu->idAt(1), TRUE);
  owner->setRenderType(SoComplexity::SCREEN_SPACE);
} // screenspaceSelected()

// *************************************************************************

/*!
  \internal slot

  Changes the render quality value.
*/

void
SoQtSuperViewerP::renderqualitySelected(int value)
{
  owner->setRenderQuality(((float)value)/10);
} // renderqualitySelected()

// *************************************************************************

/*!
  \internal slot

  Changes the texture quality value.
*/

void
SoQtSuperViewerP::texturequalitySelected(int value)
{
  owner->setTextureQuality(value);
} // texturequalitySelected()

// *************************************************************************

/*!
  \internal slot

  Goes to view all mode (chooses supergraph camera and viewAll() is called).
*/

void
SoQtSuperViewerP::viewallSelected()
{
  owner->viewAll();
} // viewallSelected()

// *************************************************************************

/*!
  \internal slot

  Resets the view to original camera view.
*/

void
SoQtSuperViewerP::resetviewSelected()
{
  owner->resetToHomePosition();
} // resetviewSelected()

// *************************************************************************

/*!
  \internal slot

  Selects seek mode.
*/

void
SoQtSuperViewerP::seekSelected()
{
  owner->setSeekMode(TRUE);
} // seekSelected()

// *************************************************************************

/*!
  \internal slot

  Sets the chosen camera to current.
*/

void
SoQtSuperViewerP::cameraSelected(int id)
{
  owner->resetToHomePosition();
  int indexoffset = this->frontcamera ? 7 : 6;

  owner->setCamera(this->cameras[
                   this->cameramenu->indexOf(id) - indexoffset]);
  this->cameramenu->setItemChecked(
                    this->cameramenu->idAt(this->cameraitemchk), FALSE);
  this->cameramenu->setItemChecked(id, TRUE);
  this->cameraitemchk = this->cameramenu->indexOf(id);
} // cameraSelected()

// *************************************************************************

/*!
  \internal slot

  Sets the chosen fly mode to current.
*/

void
SoQtSuperViewerP::flymodeSelected(int id)
{
  int mode = this->flymodesubmenu->indexOf(id);
  switch(mode){
  case 0:
    this->flymode = FLYMODE;
    break;
  case 1:
    this->flymode = GLIDEMODE;
    break;
  case 2:
    this->flymode = LOCKEDMODE;
    break;
  }
  this->flymodesubmenu->setItemChecked(
                    this->flymodesubmenu->idAt(this->flymodeitemchk), FALSE);
  this->flymodesubmenu->setItemChecked(id, TRUE);
  this->flymodeitemchk = mode;
} // cameraSelected()

// *************************************************************************

/*!
  \internal slot

  Sets the front camera to current.
*/

void
SoQtSuperViewerP::frontSelected()
{
  owner->resetToHomePosition();
  if(this->cameraswitch)
    this->cameraswitch->whichChild = SO_SWITCH_NONE;
  this->currentroot->ref();
  owner->setSceneGraph(NULL);
  owner->setSceneGraph(this->currentroot);
  this->currentroot->unref();
  this->cameramenu->setItemChecked(
                    this->cameramenu->idAt(this->cameraitemchk), FALSE);
  this->cameramenu->setItemChecked(this->cameramenu->idAt(6), TRUE);
  this->cameraitemchk = 6;
} // frontSelected()

// *************************************************************************

/*!
  \internal slot

  Sets the chosen light on or off.
*/

void
SoQtSuperViewerP::lightSelected(int id)
{
  int index = this->lightsmenu->indexOf(id);
  if(!index){
    owner->isHeadlight() ?
      this->lightsmenu->setItemChecked(id, FALSE) :
      this->lightsmenu->setItemChecked(id, TRUE);
    owner->isHeadlight() ? 
      owner->setHeadlight(FALSE) : 
      owner->setHeadlight(TRUE);
  }
  else{
    this->lights[index - 1]->on.getValue() ?
      this->lightsmenu->setItemChecked(id, FALSE) :
      this->lightsmenu->setItemChecked(id, TRUE);
    this->lights[index - 1]->on.getValue() ? 
      this->lights[index - 1]->on = FALSE :
      this->lights[index - 1]->on = TRUE;
  }

} // lightSelected()

// *************************************************************************

/*!
  \internal slot

  Turns examine mode on.
*/

void
SoQtSuperViewerP::examineSelected()
{
  this->flying = FALSE;
  this->setMode(INTERACT);
  this->viewmodesubmenu->setItemChecked(this->viewmodesubmenu->idAt(0), TRUE);
  this->viewmodesubmenu->setItemChecked(this->viewmodesubmenu->idAt(1), FALSE);
  this->cameramenu->setItemEnabled(this->cameramenu->idAt(4), FALSE);
  this->timersensor->unschedule();
  this->flyCameraSetup();
} // examineSelected()

// *************************************************************************

/*!
  \internal slot

  Turns fly mode on.
*/

void
SoQtSuperViewerP::flySelected()
{
  if(owner->isAnimating()) owner->stopAnimating();
  this->flying = TRUE;
  this->setMode(FLYMODE);
  this->viewmodesubmenu->setItemChecked(this->viewmodesubmenu->idAt(1), TRUE);
  this->viewmodesubmenu->setItemChecked(this->viewmodesubmenu->idAt(0), FALSE);
  this->cameramenu->setItemEnabled(this->cameramenu->idAt(4), TRUE);
  this->timersensor->schedule();
  this->flyCameraSetup();

} // flySelected()

// ************************************************************************

// Helper slots
void
SoQtSuperViewerP::setNumD10render(int value)
{
  this->rendervaluelabel->setNum(((double)value)/10);
}

void
SoQtSuperViewerP::setNumD10texture(int value)
{
  this->texturequalitylabel->setNum(((double)value)/10);
}

// ************************************************************************

void
SoQtSuperViewerP::findCameras()
{
  this->searchaction = new SoSearchAction;
  this->searchaction->reset(); 
  this->searchaction->setSearchingAll(TRUE);
  this->searchaction->setInterest(SoSearchAction::ALL);
  this->searchaction->setType(SoCamera::getClassTypeId());
  this->searchaction->apply(this->currentroot);
  SoPathList camerapaths = this->searchaction->getPaths();
  if(this->cameras.getLength()) this->cameras.truncate(0);
  
  SoCamera * cam = owner->getCamera();
  this->frontcamera = TRUE;
  for(int i = 0; i < camerapaths.getLength(); i++){
    this->cameras.append((SoCamera *)camerapaths[i]->getTail());
    if(cam->getNodeId() == cameras[i]->getNodeId()) this->frontcamera = FALSE;
  } 

  delete this->searchaction;
  this->searchaction = NULL;
} // findCameras()

// *************************************************************************

void
SoQtSuperViewerP::findLights()
{
  this->searchaction = new SoSearchAction;
  this->searchaction->reset(); 
  this->searchaction->setSearchingAll(TRUE);
  this->searchaction->setInterest(SoSearchAction::ALL);
  this->searchaction->setType(SoLight::getClassTypeId());
  this->searchaction->apply(this->currentroot);
  SoPathList lightpaths = this->searchaction->getPaths();
  if(this->lights.getLength()) this->lights.truncate(0);
 
  for(int i = 0; i < lightpaths.getLength(); i++){
    SoLight * light = (SoLight *)lightpaths[i]->getTail();
    if(this->lights.find(light) == -1){
      light->on = FALSE;
      this->lights.append(light);
    }
  }

  delete this->searchaction;
  this->searchaction = NULL;
} // findLights()

// *************************************************************************

/*!
  \internal

  Return the parent node in the scene graph of the given \a node.
  NB: this is just a quick'n'dirty thing for often executed code,
  and doesn't cover cases where nodes have multiple parents.
*/

SoGroup *
SoQtSuperViewerP::getParentOfNode(SoNode * root, SoNode * node, int & index)
{
  SbBool oldsearch = SoBaseKit::isSearchingChildren();
  SoBaseKit::setSearchingChildren(TRUE);

  assert(node && root && "get_parent_of_node() called with null argument");

  this->searchaction = new SoSearchAction;
  this->searchaction->reset();
  this->searchaction->setSearchingAll(TRUE);
  this->searchaction->setNode(node);
  this->searchaction->apply(root);
  if(!this->searchaction->getPath()) return NULL;
  SoNode * parent =
    ((SoFullPath *) this->searchaction->getPath())->getNodeFromTail(1);
  assert(parent && "couldn't find parent");
  delete this->searchaction;
  this->searchaction = NULL;
  SoBaseKit::setSearchingChildren(oldsearch);
  index = ((SoGroup *)parent)->findChild(node);
  return (SoGroup *)parent;

}

// *************************************************************************

void
SoQtSuperViewerP::flyCameraSetup()
{
  if(this->flying){
    if (this->currcam) {
      this->camerapossensor->detach();
      this->cameraorientsensor->detach();
    }
    this->currcam = owner->getCamera();
    
    this->camerapossensor->attach(&this->currcam->position);
    
    this->cameraorientsensor->attach(&this->currcam->orientation);
    this->camerarot.setRotate(this->currcam->orientation.getValue());
    
    SoQtSuperViewerP::camera_pos_cb((void*)this, 
                                    this->camerapossensor);
    SoQtSuperViewerP::camera_orient_cb((void*)this, 
                                       this->cameraorientsensor);
  }
  else{
    if (this->currcam) {
      this->camerapossensor->detach();
      this->cameraorientsensor->detach();
      this->currcam = NULL;
    }
  }
}
// *************************************************************************

#if SOQT_DEBUG
static const char * getSoQtSuperViewerPRCSId(void) { return rcsid; }
#endif // SOQT_DEBUG
