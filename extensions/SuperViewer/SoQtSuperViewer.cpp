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

#include "SoQtSuperViewer.h"
#include "SoQtSuperViewerP.h"

#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoShapeHints.h>
#include <Inventor/nodes/SoComplexity.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoLightModel.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoMaterialBinding.h>
#include <Inventor/nodes/SoPolygonOffset.h>
#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoNormal.h>
#include <Inventor/nodes/SoNormalBinding.h>
#include <Inventor/projectors/SbSphereSheetProjector.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/actions/SoGetPrimitiveCountAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMotion3Event.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/errors/SoDebugError.h>

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoQtCursor.h>

#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qstringlist.h>
#include "moc_SoQtSuperViewerP.icc"

SOQT_OBJECT_SOURCE(SoQtSuperViewer);

static const int MOUSEPOSLOGSIZE = 16;

// *************************************************************************

#define PRIVATE(o) (o->pimpl)

// *************************************************************************

/*!
  Constructor. See parent class for explanation of arguments.

  Subclasses will probably usually call with the \a buildNow flag
  set to \c FALSE to be able to do delayed building of the OpenGL
  canvas after other setup tasks has been performed.
*/

SoQtSuperViewer::SoQtSuperViewer(
  QWidget * parent,
  const char * name,
  SbBool embed,
  SoQtSuperViewer::BuildFlag buildFlag,
  SoQtViewer::Type type,
  SbBool build)
: inherited(parent, name, embed, type, FALSE)
{
  PRIVATE(this) = new SoQtSuperViewerP(this);

  PRIVATE(this)->viewerwidget = NULL;
  PRIVATE(this)->canvas = NULL;
  PRIVATE(this)->menubar = NULL;

  PRIVATE(this)->filemenu = NULL;
  PRIVATE(this)->viewmenu = NULL;
  PRIVATE(this)->settingsmenu = NULL;
  PRIVATE(this)->cameramenu = NULL;
  PRIVATE(this)->lightsmenu = NULL;
  PRIVATE(this)->modelsubmenu = NULL;
  PRIVATE(this)->informationsubmenu = NULL;
  PRIVATE(this)->linewidthsubmenu = NULL;
  PRIVATE(this)->pointsizesubmenu = NULL;
  PRIVATE(this)->renderqualitysubmenu = NULL;
  PRIVATE(this)->texturequalitysubmenu = NULL;
  PRIVATE(this)->transparencysubmenu = NULL;
  PRIVATE(this)->rendervaluesubmenu = NULL;
  PRIVATE(this)->viewmodesubmenu = NULL;
  PRIVATE(this)->flymodesubmenu = NULL;

  PRIVATE(this)->rendervaluelabel = NULL;
  PRIVATE(this)->texturequalitylabel = NULL;

  PRIVATE(this)->prefwindow = NULL;
  PRIVATE(this)->prefwindowtitle = "Viewer Preference Sheet";

  PRIVATE(this)->currentroot = NULL;
  PRIVATE(this)->cameraswitch = NULL;
  PRIVATE(this)->currentindex = -1;
  PRIVATE(this)->openmodels = NULL;

  PRIVATE(this)->drawstyleroot = NULL;
  PRIVATE(this)->hiddenlineroot = NULL;
  PRIVATE(this)->polygonoffsetparent = NULL;
  PRIVATE(this)->graphswitch = NULL;
  PRIVATE(this)->polygonoffset = NULL;
  PRIVATE(this)->drawstyle = NULL;
  PRIVATE(this)->complexity = NULL;
  PRIVATE(this)->basecolor = NULL;
  PRIVATE(this)->lightmodel = NULL;
  PRIVATE(this)->materialbinding = NULL;
  PRIVATE(this)->shapehints = NULL;
  PRIVATE(this)->emptynormal = NULL;
  PRIVATE(this)->emptynormalbinding = NULL;
  PRIVATE(this)->bbox = NULL;
  PRIVATE(this)->bboxvertices = NULL;
  PRIVATE(this)->searchaction = NULL;
  PRIVATE(this)->countaction = NULL;
  PRIVATE(this)->bboxaction = NULL;
  PRIVATE(this)->cones = 0;
  PRIVATE(this)->cubes = 0;
  PRIVATE(this)->cylinders = 0;
  PRIVATE(this)->spheres = 0;
  PRIVATE(this)->polygonoffsetindex = -1;
  PRIVATE(this)->complexityindex = -1;
  PRIVATE(this)->texturequality = 1.0;
  PRIVATE(this)->howtomove = SoQtSuperViewerP::FULL;

  PRIVATE(this)->linecolor = SbColor(1.0f, 0.0f, 0.0f);
  PRIVATE(this)->pointcolor = SbColor(0.0f, 1.0f, 1.0f);

  //PRIVATE(this)->initializeMenus(buildFlag);

  PRIVATE(this)->menubarenabled = buildFlag;
  PRIVATE(this)->filemenuenabled = buildFlag;
  PRIVATE(this)->viewmenuenabled = buildFlag;
  PRIVATE(this)->settingsmenuenabled = buildFlag;
  PRIVATE(this)->cameramenuenabled = buildFlag;
  PRIVATE(this)->lightsmenuenabled = buildFlag;
  
  PRIVATE(this)->defaultoverride = FALSE;
  PRIVATE(this)->built = FALSE;
  PRIVATE(this)->sepfm = TRUE;
  PRIVATE(this)->sepvm = TRUE;
  PRIVATE(this)->sepcm = TRUE;

  PRIVATE(this)->movingitemchk = 12;
  PRIVATE(this)->transparencyitemchk = 0;
  PRIVATE(this)->cameraitemchk = 6;
  PRIVATE(this)->flymodeitemchk = 0;

  PRIVATE(this)->filled = TRUE;
  PRIVATE(this)->informationenabled = FALSE;
  PRIVATE(this)->flatshadingenabled = FALSE;
  PRIVATE(this)->boundingboxesenabled = FALSE;
  PRIVATE(this)->wireframeenabled = FALSE;
  PRIVATE(this)->verticesenabled = FALSE;
  PRIVATE(this)->hiddenpartsenabled = FALSE;
  PRIVATE(this)->texturesenabled = FALSE;
  PRIVATE(this)->drawstyles = 0;

  PRIVATE(this)->distanceenabled = FALSE;

  PRIVATE(this)->frontcamera = FALSE;

  PRIVATE(this)->filefilter = "Models (*.iv *.wrl)";
  PRIVATE(this)->modeldirectory = "";
  PRIVATE(this)->imagedirectory = "";

  PRIVATE(this)->pathtomodels = NULL;
  PRIVATE(this)->modelnames = NULL;

  PRIVATE(this)->prevRedrawTime = SbTime::getTimeOfDay();
  PRIVATE(this)->spinanimatingallowed = TRUE;
  PRIVATE(this)->spinanimating = FALSE;
  PRIVATE(this)->spinsamplecounter = 0;
  PRIVATE(this)->spinincrement = SbRotation::identity();

  PRIVATE(this)->flying = FALSE;
  PRIVATE(this)->pause = FALSE;
  PRIVATE(this)->busy = FALSE;
  PRIVATE(this)->flymode = SoQtSuperViewerP::FLYMODE;
  PRIVATE(this)->timersensor = 
    new SoTimerSensor(SoQtSuperViewerP::timercb, PRIVATE(this));
  PRIVATE(this)->relspeedglide = 0.1f;
  PRIVATE(this)->relspeedfly = 0.0f;
  PRIVATE(this)->glidespeed = 30.0f;
  PRIVATE(this)->flyspeed = 100.0f;
  PRIVATE(this)->doresetroll = TRUE;
  PRIVATE(this)->viewupaxis = SbVec3f(0.0f, 0.0f, 1.0f);
  PRIVATE(this)->camerapossensor = 
    new SoFieldSensor(SoQtSuperViewerP::camera_pos_cb, PRIVATE(this));
  PRIVATE(this)->camerapossensor->setPriority(0);
  PRIVATE(this)->cameraorientsensor = 
    new SoFieldSensor(SoQtSuperViewerP::camera_orient_cb, PRIVATE(this));
  PRIVATE(this)->cameraorientsensor->setPriority(0);
  PRIVATE(this)->currcam = NULL;

  // FIXME: use a smaller sphere than the default one to have a larger
  // area close to the borders that gives us "z-axis rotation"?
  // 19990425 mortene.
  PRIVATE(this)->spinprojector = new SbSphereSheetProjector;
  SbViewVolume volume;
  volume.ortho(-1, 1, -1, 1, -1, 1);
  PRIVATE(this)->spinprojector->setViewVolume(volume);

  PRIVATE(this)->spinRotation.setValue(SbVec3f(0, 0, -1), 0);

  PRIVATE(this)->log.size = MOUSEPOSLOGSIZE;
  PRIVATE(this)->log.position = new SbVec2s [ MOUSEPOSLOGSIZE ];
  PRIVATE(this)->log.time = new SbTime [ MOUSEPOSLOGSIZE ];
  PRIVATE(this)->log.historysize = 0;
  PRIVATE(this)->button1down = FALSE;
  PRIVATE(this)->button2down = FALSE;
  PRIVATE(this)->button3down = FALSE;
  PRIVATE(this)->controldown = FALSE;
  PRIVATE(this)->motion3OnCamera = TRUE;
   
  this->setSize(SbVec2s(500, 390));
  this->setBackgroundColor(SbColor(0.0, 0.0, 0.4));

  if (! build) return;

  this->setClassName("SoQtSuperViewer");
} // SoQtSuperViewer()

// *************************************************************************

/*!
  Destructor.
*/

SoQtSuperViewer::~SoQtSuperViewer(
  void)
{
  delete PRIVATE(this)->spinprojector;
  delete PRIVATE(this)->log.position;
  delete PRIVATE(this)->log.time;
  delete PRIVATE(this);
} // ~SoQtSuperViewer()

// *************************************************************************

/*!
  Must be called after the viewer instance has been created. If one needs
  to build the viewer with other settings than the default settings, those
  must be set before init() is called.
*/

void
SoQtSuperViewer::init()
{
  PRIVATE(this)->viewerwidget = new QWidget(this->getParentWidget());
  this->registerWidget(PRIVATE(this)->viewerwidget);

  PRIVATE(this)->viewerwidget->move(0, 0);

  // Build and layout the widget components of the viewer window on
  // top of the manager widget.
  PRIVATE(this)->canvas = inherited::buildWidget(PRIVATE(this)->viewerwidget);

  PRIVATE(this)->actualInit(TRUE);

  PRIVATE(this)->canvas->move(0, 0);
  PRIVATE(this)->canvas->resize(PRIVATE(this)->viewerwidget->size());
  this->setBaseWidget(PRIVATE(this)->viewerwidget);
} // init()

// *************************************************************************

/*!

*/

void
SoQtSuperViewer::setBars(int buildFlag)
{
  PRIVATE(this)->bars[0].build = 
    buildFlag & SoQtSuperViewer::BUILD_MENUBAR ? TRUE : FALSE;
  PRIVATE(this)->bars[1].build = 
    buildFlag & SoQtSuperViewer::BUILD_TOOLBAR ? TRUE : FALSE;

  PRIVATE(this)->actualInit(PRIVATE(this)->built ? TRUE : FALSE);

} // setBars()

// *************************************************************************

/*!

*/

void
SoQtSuperViewer::setMenus(int buildFlag)
{
  PRIVATE(this)->menus[0].build = 
    buildFlag & SoQtSuperViewer::FILE_MENU ? TRUE : FALSE;
  PRIVATE(this)->menus[1].build = 
    buildFlag & SoQtSuperViewer::VIEW_MENU ? TRUE : FALSE;
  PRIVATE(this)->menus[2].build = 
    buildFlag & SoQtSuperViewer::SETTINGS_MENU ? TRUE : FALSE;
  PRIVATE(this)->menus[3].build = 
    buildFlag & SoQtSuperViewer::CAMERA_MENU ? TRUE : FALSE;
  PRIVATE(this)->menus[4].build = 
    buildFlag & SoQtSuperViewer::LIGHTS_MENU ? TRUE : FALSE;

  if(PRIVATE(this)->built) 
    PRIVATE(this)->buildMenus();
  else 
    PRIVATE(this)->actualInit(FALSE);

} // setMenus()

// *************************************************************************

/*!

*/

void
SoQtSuperViewer::setFileMenuItems(int buildFlag)
{
  PRIVATE(this)->filemenuItems[0].build = 
    buildFlag & SoQtSuperViewer::OPEN_MODEL ? TRUE : FALSE;
  PRIVATE(this)->filemenuItems[1].build = 
    buildFlag & SoQtSuperViewer::CLOSE_MODEL ? TRUE : FALSE;
  PRIVATE(this)->filemenuItems[2].build = 
    buildFlag & SoQtSuperViewer::CLOSE_ALL ? TRUE : FALSE;
  PRIVATE(this)->filemenuItems[3].build = 
   buildFlag & SoQtSuperViewer::MODELS ? TRUE : FALSE;
  PRIVATE(this)->filemenuItems[4].build = 
    buildFlag & SoQtSuperViewer::SEPARATOR_FILE_1 ? TRUE : FALSE;
  PRIVATE(this)->filemenuItems[5].build = 
    buildFlag & SoQtSuperViewer::NEXT_MODEL ? TRUE : FALSE;
  PRIVATE(this)->filemenuItems[6].build = 
    buildFlag & SoQtSuperViewer::PREVIOUS_MODEL ? TRUE : FALSE;
  PRIVATE(this)->filemenuItems[7].build = 
    buildFlag & SoQtSuperViewer::REFRESH_MODEL ? TRUE : FALSE;
  PRIVATE(this)->filemenuItems[8].build = 
    buildFlag & SoQtSuperViewer::SNAPSHOT ? TRUE : FALSE;
  PRIVATE(this)->filemenuItems[9].build = 
    buildFlag & SoQtSuperViewer::SEPARATOR_FILE_2 ? TRUE : FALSE;
  PRIVATE(this)->filemenuItems[10].build = 
    buildFlag & SoQtSuperViewer::EXIT ? TRUE : FALSE;

  if(PRIVATE(this)->built) 
    PRIVATE(this)->buildFileMenu();
  else 
    PRIVATE(this)->actualInit(FALSE);

} // setFileMenu()

// *************************************************************************

/*!

*/

void
SoQtSuperViewer::setViewMenuItems(int buildFlag)
{
  PRIVATE(this)->viewmenuItems[0].build = 
    buildFlag & SoQtSuperViewer::INFORMATION ? TRUE : FALSE;
  PRIVATE(this)->viewmenuItems[1].build = 
    buildFlag & SoQtSuperViewer::FLATSHADING ? TRUE : FALSE;
  PRIVATE(this)->viewmenuItems[2].build = 
    buildFlag & SoQtSuperViewer::SEPARATOR_VIEW_1 ? TRUE : FALSE;
  PRIVATE(this)->viewmenuItems[3].build = 
    buildFlag & SoQtSuperViewer::FILLED ? TRUE : FALSE;
  PRIVATE(this)->viewmenuItems[4].build = 
    buildFlag & SoQtSuperViewer::BOUNDINGBOXES ? TRUE : FALSE;
  PRIVATE(this)->viewmenuItems[5].build =
    buildFlag & SoQtSuperViewer::WIREFRAME ? TRUE : FALSE;
  PRIVATE(this)->viewmenuItems[6].build = 
    buildFlag & SoQtSuperViewer::VERTICES ? TRUE : FALSE;
  PRIVATE(this)->viewmenuItems[7].build = 
    buildFlag & SoQtSuperViewer::HIDDEN_PARTS ? TRUE : FALSE;
  PRIVATE(this)->viewmenuItems[8].build = 
    buildFlag & SoQtSuperViewer::TEXTURES ? TRUE : FALSE;
  PRIVATE(this)->viewmenuItems[9].build = 
    buildFlag & SoQtSuperViewer::SEPARATOR_VIEW_2 ? TRUE : FALSE;
  PRIVATE(this)->viewmenuItems[10].build = 
    buildFlag & SoQtSuperViewer::WHILE_MOVING ? TRUE : FALSE;
  PRIVATE(this)->viewmenuItems[11].build = 
    buildFlag & SoQtSuperViewer::WHILE_MOVING ? TRUE : FALSE;
  PRIVATE(this)->viewmenuItems[12].build = 
    buildFlag & SoQtSuperViewer::WHILE_MOVING ? TRUE : FALSE;
  PRIVATE(this)->viewmenuItems[13].build = 
    buildFlag & SoQtSuperViewer::WHILE_MOVING ? TRUE : FALSE;

  if(PRIVATE(this)->built) 
    PRIVATE(this)->buildViewMenu();
  else 
    PRIVATE(this)->actualInit(FALSE);

} // setViewMenu()

// *************************************************************************

/*!

*/

void
SoQtSuperViewer::setSettingsMenuItems(int buildFlag)
{
  PRIVATE(this)->settingsmenuItems[0].build = 
    buildFlag & SoQtSuperViewer::INFORMATION_SETTING ? TRUE : FALSE;
  PRIVATE(this)->settingsmenuItems[1].build = 
    buildFlag & SoQtSuperViewer::LINE_WIDTH ? TRUE : FALSE;
  PRIVATE(this)->settingsmenuItems[2].build = 
    buildFlag & SoQtSuperViewer::POINT_SIZE ? TRUE : FALSE;
  PRIVATE(this)->settingsmenuItems[3].build = 
    buildFlag & SoQtSuperViewer::LINE_COLOR ? TRUE : FALSE;
  PRIVATE(this)->settingsmenuItems[4].build = 
    buildFlag & SoQtSuperViewer::POINT_COLOR ? TRUE : FALSE;
  PRIVATE(this)->settingsmenuItems[5].build = 
    buildFlag & SoQtSuperViewer::BACKGROUND_COLOR ? TRUE : FALSE;
  PRIVATE(this)->settingsmenuItems[6].build = 
    buildFlag & SoQtSuperViewer::RENDER_QUALITY ? TRUE : FALSE;
  PRIVATE(this)->settingsmenuItems[7].build = 
    buildFlag & SoQtSuperViewer::TEXTURE_QUALITY ? TRUE : FALSE;
  PRIVATE(this)->settingsmenuItems[8].build = 
    buildFlag & SoQtSuperViewer::TRANSPARENCY_TYPE ? TRUE : FALSE;


  if(PRIVATE(this)->built) 
    PRIVATE(this)->buildSettingsMenu();
  else 
    PRIVATE(this)->actualInit(FALSE);

} // setSettingsMenu()

// *************************************************************************

/*!

*/

void
SoQtSuperViewer::setCameraMenuItems(int buildFlag)
{
  PRIVATE(this)->cameramenuItems[0].build = 
    buildFlag & SoQtSuperViewer::VIEW_ALL ? TRUE : FALSE;
  PRIVATE(this)->cameramenuItems[1].build = 
    buildFlag & SoQtSuperViewer::RESET_VIEW ? TRUE : FALSE;
  PRIVATE(this)->cameramenuItems[2].build = 
    buildFlag & SoQtSuperViewer::SEEK ? TRUE : FALSE;
  PRIVATE(this)->cameramenuItems[3].build = 
    buildFlag & SoQtSuperViewer::VIEW_MODES ? TRUE : FALSE;
  PRIVATE(this)->cameramenuItems[4].build = 
    buildFlag & SoQtSuperViewer::FLY_MODES ? TRUE : FALSE;
  PRIVATE(this)->cameramenuItems[5].build = 
    buildFlag & SoQtSuperViewer::SEPARATOR_CAMERA_1 ? TRUE : FALSE;
  PRIVATE(this)->cameramenuItems[6].build = 
    buildFlag & SoQtSuperViewer::CAMERAS ? TRUE : FALSE;

  if(PRIVATE(this)->built) 
    PRIVATE(this)->buildCameraMenu();
  else 
    PRIVATE(this)->actualInit(FALSE);

} // setCameraMenuItems()

// *************************************************************************

/*!
  Turn the menubar on or off.

  \sa isMenuBar()
*/

void
SoQtSuperViewer::setMenuBar(
  const SbBool enable)
{
#if SOQT_DEBUG
  if ((enable  && this->isMenuBar()) ||
      (!enable && !this->isMenuBar())) {
    SoDebugError::postWarning("SoQtSuperViewer::setMenuBar",
                              "menubar already turned %s",
                              enable ? "on" : "off");
    return;
  }
#endif // SOQT_DEBUG

  PRIVATE(this)->menubarenabled = enable;
} // setMenuBar()

// *************************************************************************

/*!
  Return \c TRUE if the menubar are on, otherwise \c FALSE.

  \sa setMenuBar()
*/

SbBool
SoQtSuperViewer::isMenuBar(
  void) const
{
  return PRIVATE(this)->menubarenabled;
} // isMenuBar()

// *************************************************************************

/*!
  Turn the filemenu on or off.

  \sa isFileMenu()
*/

void
SoQtSuperViewer::setFileMenu(
  const SbBool enable)
{
#if SOQT_DEBUG
  if ((enable  && this->isFileMenu()) ||
      (!enable && !this->isFileMenu())) {
    SoDebugError::postWarning("SoQtSuperViewer::setFileMenu",
                              "filemenu already turned %s",
                              enable ? "on" : "off");
    return;
  }
#endif // SOQT_DEBUG

  PRIVATE(this)->filemenuenabled = enable;
} // setFileMenu()

// *************************************************************************

/*!
  Return \c TRUE if the filemenu are on, otherwise \c FALSE.

  \sa setFileMenu()
*/

SbBool
SoQtSuperViewer::isFileMenu(
  void) const
{
  return PRIVATE(this)->filemenuenabled;
} // isFileMenu()

// *************************************************************************

/*!
  Turn the viewmenu on or off.

  \sa isViewMenu()
*/

void
SoQtSuperViewer::setViewMenu(
  const SbBool enable)
{
#if SOQT_DEBUG
  if ((enable  && this->isViewMenu()) ||
      (!enable && !this->isViewMenu())) {
    SoDebugError::postWarning("SoQtSuperViewer::setViewMenu",
                              "filemenu already turned %s",
                              enable ? "on" : "off");
    return;
  }
#endif // SOQT_DEBUG

  PRIVATE(this)->viewmenuenabled = enable;
} // setViewMenu()

// *************************************************************************

/*!
  Return \c TRUE if the viewmenu are on, otherwise \c FALSE.

  \sa setViewMenu()
*/

SbBool
SoQtSuperViewer::isViewMenu(
  void) const
{
  return PRIVATE(this)->viewmenuenabled;
} // isViewMenu()

// *************************************************************************

/*!
  Turn the settingsmenu on or off.

  \sa isSettingsMenu()
*/

void
SoQtSuperViewer::setSettingsMenu(
  const SbBool enable)
{
#if SOQT_DEBUG
  if ((enable  && this->isSettingsMenu()) ||
      (!enable && !this->isSettingsMenu())) {
    SoDebugError::postWarning("SoQtSuperViewer::setSettingsMenu",
                              "filemenu already turned %s",
                              enable ? "on" : "off");
    return;
  }
#endif // SOQT_DEBUG

  PRIVATE(this)->settingsmenuenabled = enable;
} // setSettingsMenu()

// *************************************************************************

/*!
  Return \c TRUE if the settingsmenu are on, otherwise \c FALSE.

  \sa setSettingsMenu()
*/

SbBool
SoQtSuperViewer::isSettingsMenu(
  void) const
{
  return PRIVATE(this)->settingsmenuenabled;
} // isSettingsMenu()

// *************************************************************************

/*!
  Turn the cameramenu on or off.

  \sa isCameraMenu()
*/

void
SoQtSuperViewer::setCameraMenu(
  const SbBool enable)
{
#if SOQT_DEBUG
  if ((enable  && this->isCameraMenu()) ||
      (!enable && !this->isCameraMenu())) {
    SoDebugError::postWarning("SoQtSuperViewer::setCameraMenu",
                              "filemenu already turned %s",
                              enable ? "on" : "off");
    return;
  }
#endif // SOQT_DEBUG

  PRIVATE(this)->cameramenuenabled = enable;
} // setCameraMenu()

// *************************************************************************

/*!
  Return \c TRUE if the cameramenu are on, otherwise \c FALSE.

  \sa setCameraMenu()
*/

SbBool
SoQtSuperViewer::isCameraMenu(
  void) const
{
  return PRIVATE(this)->cameramenuenabled;
} // isCameraMenu()

// *************************************************************************

/*!
  Turn the lightsmenu on or off.

  \sa isLightsMenu()
*/

void
SoQtSuperViewer::setLightsMenu(
  const SbBool enable)
{
#if SOQT_DEBUG
  if ((enable  && this->isLightsMenu()) ||
      (!enable && !this->isLightsMenu())) {
    SoDebugError::postWarning("SoQtSuperViewer::setLightsMenu",
                              "filemenu already turned %s",
                              enable ? "on" : "off");
    return;
  }
#endif // SOQT_DEBUG

  PRIVATE(this)->lightsmenuenabled = enable;
} // setLightsMenu()

// *************************************************************************

/*!
  Return \c TRUE if the lightsmenu are on, otherwise \c FALSE.

  \sa setLightsMenu()
*/

SbBool
SoQtSuperViewer::isLightsMenu(
  void) const
{
  return PRIVATE(this)->lightsmenuenabled;
} // isLightsMenu()

// *************************************************************************

/*!
  Overloaded to provide name of class.
*/

const char *
SoQtSuperViewer::getDefaultWidgetName(// virtual
  void) const
{
  static const char defaultWidgetName[] = "SoQtSuperViewer";
  return defaultWidgetName;
} // getDefaultWidgetName()

// *************************************************************************

/*!
  Overloaded to provide ``title'' of class.
*/

const char *
SoQtSuperViewer::getDefaultTitle(void) const
{
  static const char defaultTitle[] = "Super Viewer";
  return defaultTitle;
} // getDefaultTitle()

// *************************************************************************

/*!
  Overloaded to provide ``title'' of class.
*/

const char *
SoQtSuperViewer::getDefaultIconTitle(void) const
{
  static const char defaultIconTitle[] = "Super Viewer";
  return defaultIconTitle;
} // getDefaultIconTitle()

// *************************************************************************

/*!
  Returns the render area OpenGL canvas widget.
*/

QWidget *
SoQtSuperViewer::getRenderAreaWidget(void) const
{
  return PRIVATE(this)->canvas;
} // getRenderAreaWidget()

// *************************************************************************

/*!
  Returns the filefilter for the supported filetypes.
*/

SbString
SoQtSuperViewer::getFileFilter(void) const
{
  return PRIVATE(this)->filefilter;
} // getFileFilter()

// *************************************************************************

/*!
  Sets the filefilter for the supported filetypes.
*/

void
SoQtSuperViewer::setFileFilter(SbString filter)
{
  PRIVATE(this)->filefilter = filter;
} // setFileFilter()

// *************************************************************************

/*!
  Returns the directory for where to look for model files.
*/

SbString
SoQtSuperViewer::getModelDirectory(void) const
{
  return PRIVATE(this)->modeldirectory;
} // getDirectory()

// *************************************************************************

/*!
  Sets the directory for where to look for model files.
*/

void
SoQtSuperViewer::setModelDirectory(SbString dir)
{
  PRIVATE(this)->modeldirectory = dir;
} // setDirectory()

// *************************************************************************

/*!
  Returns the directory for where to save image files.
*/

SbString
SoQtSuperViewer::getImageDirectory(void) const
{
  return PRIVATE(this)->imagedirectory;
} // getDirectory()

// *************************************************************************

/*!
  Sets the directory for where to save image files.
*/

void
SoQtSuperViewer::setImageDirectory(SbString dir)
{
  PRIVATE(this)->imagedirectory = dir;
} // setDirectory()

// *************************************************************************

/*!
  Toggles the modelfill on or off.
*/

void
SoQtSuperViewer::toggleFilled()
{
  PRIVATE(this)->filled ? 
    PRIVATE(this)->filled = FALSE : 
    PRIVATE(this)->filled = TRUE;
} //toggleFilled()

// *************************************************************************

/*!
  Query whether or not the model is supposed to be filled.
*/

SbBool
SoQtSuperViewer::isFilled() const
{
  return PRIVATE(this)->filled;
} //isFilled()

// *************************************************************************

/*!
  Toggles the modelinformation on or off.
*/

void
SoQtSuperViewer::toggleInformation()
{
  PRIVATE(this)->informationenabled ? 
    PRIVATE(this)->informationenabled = FALSE : 
    PRIVATE(this)->informationenabled = TRUE;
} //toggleInformation()

// *************************************************************************

/*!
  Query whether or not the modelinformation is supposed to be shown.
*/

SbBool
SoQtSuperViewer::isInformation() const
{
  return PRIVATE(this)->informationenabled;
} //isInformation()

// ************************************************************************

/*!
  Toggles the flatshading on or off.
*/

void
SoQtSuperViewer::toggleFlatshading()
{
  PRIVATE(this)->flatshadingenabled ? 
    PRIVATE(this)->flatshadingenabled = FALSE : 
    PRIVATE(this)->flatshadingenabled = TRUE;

  if(PRIVATE(this)->flatshadingenabled){
    
    if(PRIVATE(this)->shapehints == NULL) 
      PRIVATE(this)->shapehints = new SoShapeHints;
    PRIVATE(this)->shapehints->creaseAngle = 0.0;
    PRIVATE(this)->shapehints->setOverride(TRUE);
    ((SoSeparator *)this->getSceneManager()->getSceneGraph())
      ->insertChild(PRIVATE(this)->shapehints, 0);

    PRIVATE(this)->emptynormal = new SoNormal;
    PRIVATE(this)->emptynormal->setOverride(TRUE);
    ((SoSeparator *)this->getSceneManager()->getSceneGraph())
      ->insertChild(PRIVATE(this)->emptynormal, 0);

    PRIVATE(this)->emptynormalbinding = new SoNormalBinding;
    PRIVATE(this)->emptynormalbinding->setOverride(TRUE);
    ((SoSeparator *)this->getSceneManager()->getSceneGraph())
      ->insertChild(PRIVATE(this)->emptynormalbinding, 0);
  }
  else{

    ((SoSeparator *)this->getSceneManager()->getSceneGraph())
      ->removeChild(PRIVATE(this)->shapehints);
    PRIVATE(this)->shapehints = NULL;
    ((SoSeparator *)this->getSceneManager()->getSceneGraph())
      ->removeChild(PRIVATE(this)->emptynormal);
    PRIVATE(this)->emptynormal = NULL;
    ((SoSeparator *)this->getSceneManager()->getSceneGraph())
      ->removeChild(PRIVATE(this)->emptynormalbinding);
    PRIVATE(this)->emptynormalbinding = NULL;
    }
} //toggleFlatshading()

// *************************************************************************

/*!
  Query whether or not the model is supposed to be flatshaded.
*/

SbBool
SoQtSuperViewer::isFlatshading() const
{
  return PRIVATE(this)->flatshadingenabled;
} //isFlatshading()

// *************************************************************************

/*!
  Toggles the boundingboxes on or off.
*/

void
SoQtSuperViewer::toggleBoundingboxes()
{
  PRIVATE(this)->boundingboxesenabled ? 
    PRIVATE(this)->boundingboxesenabled = FALSE : 
    PRIVATE(this)->boundingboxesenabled = TRUE;

  if(PRIVATE(this)->boundingboxesenabled)
    PRIVATE(this)->drawstyles++;
  else
    PRIVATE(this)->drawstyles--;
    
} //toggleBoundingboxes()

// *************************************************************************

/*!
  Query whether or not the boundingboxes are supposed to be shown.
*/

SbBool
SoQtSuperViewer::isBoundingboxes() const
{
  return PRIVATE(this)->boundingboxesenabled;
} //isBoundingboxes()

// *************************************************************************

/*!
  Toggles the wireframe on or off.
*/

void
SoQtSuperViewer::toggleWireframe()
{
  PRIVATE(this)->wireframeenabled ? 
    PRIVATE(this)->wireframeenabled = FALSE : 
    PRIVATE(this)->wireframeenabled = TRUE;

  if(PRIVATE(this)->wireframeenabled)
    PRIVATE(this)->drawstyles++;
  else
    PRIVATE(this)->drawstyles--;

} //toggleWireframe()

// *************************************************************************

/*!
  Query whether or not the wireframe is supposed to be shown.
*/

SbBool
SoQtSuperViewer::isWireframe() const
{
  return PRIVATE(this)->wireframeenabled;
} //isWireframe()

// *************************************************************************

/*!
  Toggles the vertices on or off.
*/

void
SoQtSuperViewer::toggleVertices()
{
  PRIVATE(this)->verticesenabled ? 
    PRIVATE(this)->verticesenabled = FALSE : 
    PRIVATE(this)->verticesenabled = TRUE;

  if(PRIVATE(this)->verticesenabled)
    PRIVATE(this)->drawstyles++;
  else
    PRIVATE(this)->drawstyles--;

} //toggleVertices()

// *************************************************************************

/*!
  Query whether or not the vertices are supposed to be shown.
*/

SbBool
SoQtSuperViewer::isVertices() const
{
  return PRIVATE(this)->verticesenabled;
} //isVertices()

// *************************************************************************

/*!
  Toggles the hiddenparts on or off.
*/

void
SoQtSuperViewer::toggleHiddenparts()
{
  PRIVATE(this)->hiddenpartsenabled ? 
    PRIVATE(this)->hiddenpartsenabled = FALSE : 
    PRIVATE(this)->hiddenpartsenabled = TRUE;

} //toggleHiddenparts()

// *************************************************************************

/*!
  Query whether or not the occluded wireframe, vertices and boundingboxparts
  are to be shown.
*/

SbBool
SoQtSuperViewer::isHiddenparts() const
{
  return PRIVATE(this)->hiddenpartsenabled;
} //isHiddenparts()

// *************************************************************************

/*!
  Toggles the textures on or off.
*/

void
SoQtSuperViewer::toggleTextures()
{
  PRIVATE(this)->texturesenabled ? 
    PRIVATE(this)->texturesenabled = FALSE : 
    PRIVATE(this)->texturesenabled = TRUE;

} //toggleTextures()

// *************************************************************************

/*!
  Query whether or not the textures are to be shown.
*/

SbBool
SoQtSuperViewer::isTextures() const
{
  return PRIVATE(this)->texturesenabled;
} //isTextures()

// ************************************************************************

/*!
  Toggles the distance item in the information on or off.
*/

void
SoQtSuperViewer::toggleDistance()
{
  PRIVATE(this)->distanceenabled ? 
    PRIVATE(this)->distanceenabled = FALSE : 
    PRIVATE(this)->distanceenabled = TRUE;

} //toggleDistance()

// *************************************************************************

/*!
  Query whether or not the distance is to be shown with the rest of the
  information.
*/

SbBool
SoQtSuperViewer::isDistance() const
{
  return PRIVATE(this)->distanceenabled;
} //isDistance()

// ************************************************************************

/*!
  Sets the new line width.
*/

void
SoQtSuperViewer::setLineWidth(int value)
{
  PRIVATE(this)->drawstyle->lineWidth.setValue(value);
} // setLineWidth()

// ************************************************************************

/*!
  Querys for the current line width.
*/

int
SoQtSuperViewer::getLineWidth() const
{
  return PRIVATE(this)->drawstyle->lineWidth.getValue();
} // getLineWidth()

// ************************************************************************

/*!
  Sets the new point size.
*/

void
SoQtSuperViewer::setPointSize(int value)
{
  PRIVATE(this)->drawstyle->pointSize.setValue(value);
} // setPointSize()

// ************************************************************************

/*!
  Querys for the current point size.
*/

int
SoQtSuperViewer::getPointSize() const
{
  return PRIVATE(this)->drawstyle->pointSize.getValue();
} // getPointSize()

// ************************************************************************

/*!
  Sets the render type to \c type.
*/

void
SoQtSuperViewer::setRenderType(SoComplexity::Type type) 
{
  PRIVATE(this)->complexity->type = type;
} // setRenderType()

// ************************************************************************

/*!
  Set the new render quality value.
*/

void
SoQtSuperViewer::setRenderQuality(float value)
{
  PRIVATE(this)->complexity->value.setValue(value);
} // setRenderQuality()

// ************************************************************************

/*!
  Set the new texture quality value.
*/

void
SoQtSuperViewer::setTextureQuality(float value)
{
  PRIVATE(this)->complexity->textureQuality.setValue(value);
  PRIVATE(this)->texturequality = value;
} // setTextureQuality()

// ************************************************************************

/*!
  Set the camera we want to view the scene with.

  The camera passed in as an argument to this method must be part of
  the viewer's scenegraph.
*/

void
SoQtSuperViewer::setCamera(SoCamera * cam)
{
 
  inherited::setCamera(cam);
  
  if(!PRIVATE(this)->currentroot || !cam) return;
  int index = -1;
  SoGroup * node = PRIVATE(this)->getParentOfNode(
                   PRIVATE(this)->currentroot, cam, index);
  if(!node){
    PRIVATE(this)->cameraswitch = NULL;
    return;
  }
  if(node->getTypeId() == SoSwitch::getClassTypeId()){
    PRIVATE(this)->cameraswitch = (SoSwitch *)node;
    PRIVATE(this)->cameraswitch->whichChild = index;
  }
  
} // setCamera()

// ************************************************************************

/*!
  Decide if it should be possible to start a spin animation of the model in
  the viewer by releasing the mouse button while dragging.

  If the \c on flag is \c FALSE and we're currently animating, the spin
  will be stopped.

  \sa isAnimationEnabled
*/

void
SoQtSuperViewer::setAnimationEnabled(
  const SbBool enable)
{
  PRIVATE(this)->spinanimatingallowed = enable;
  if (! enable && this->isAnimating())
    this->stopAnimating();
} // setAnimationEnabled()

// *************************************************************************

/*!
  Query whether or not it is possible to start a spinning animation by
  releasing the left mouse button while dragging the mouse.

  \sa setAnimationEnabled
*/

SbBool
SoQtSuperViewer::isAnimationEnabled(
  void) const
{
  return PRIVATE(this)->spinanimatingallowed;
} // isAnimationEnabled()

// *************************************************************************

/*!
  Stop the model from spinning.
*/

void
SoQtSuperViewer::stopAnimating(
  void)
{
  if (PRIVATE(this)->spinanimating) {
    PRIVATE(this)->spinanimating = FALSE;
    this->interactiveCountDec();
  }
#if SOQT_DEBUG
  else
    SoDebugError::postWarning("SoQtSuperViewer::stopAnimating",
      "not animating");
#endif // SOQT_DEBUG
} // stopAnimating()

// *************************************************************************

/*!
  Query if the model in the viewer is currently in spinning mode after
  a user drag.
*/

SbBool
SoQtSuperViewer::isAnimating(
  void) const
{
  return PRIVATE(this)->spinanimating;
} // isAnimating()

// *************************************************************************

/*!
  Decide whether or not the mouse pointer cursor should be visible in
  the rendering canvas.
*/
void
SoQtSuperViewer::setCursorEnabled(SbBool enable)
{
  inherited::setCursorEnabled(enable);
  PRIVATE(this)->setCursorRepresentation(PRIVATE(this)->currentmode);
} // setCursorEnabled()

// *************************************************************************

/*!
  Overload this method to make sure any animations are stopped before
  we go into seek mode.
*/

void
SoQtSuperViewer::setSeekMode(SbBool on)
{
#if SOQT_DEBUG
  if (on == this->isSeekMode()) {
    SoDebugError::postWarning("SoQtSuperViewer::setSeekMode",
                              "seek mode already %sset", on ? "" : "un");
    return;
  }
#endif // SOQT_DEBUG

  if (this->isAnimating()) this->stopAnimating();
  inherited::setSeekMode(on);
  PRIVATE(this)->setMode(on ?
                        SoQtSuperViewerP::WAITING_FOR_SEEK :
                        SoQtSuperViewerP::INTERACT);
} // setSeekMode()

// *************************************************************************

/*!
  Call up a color dialog to pick a color for lines.
*/
void
SoQtSuperViewer::setLineColor(const SbColor & color)
{
  PRIVATE(this)->linecolor = color;
} // setLineColor()

// *************************************************************************

/*!
  Call up a color dialog to pick a color for points.
*/
void
SoQtSuperViewer::setPointColor(const SbColor & color)
{
  PRIVATE(this)->pointcolor = color;
} // setPointColor()

// *************************************************************************

/*!
  Turns fly mode on or off. When it is turned off, it enters examine mode.
*/

void
SoQtSuperViewer::setFlyMode(SbBool enable)
{
  PRIVATE(this)->flying = enable;
} // setFlyMode()

// *************************************************************************

/*!
  Returns whether the fly mode is on or off.
*/

SbBool
SoQtSuperViewer::isFlyMode()
{
  return PRIVATE(this)->flying;
} // isFlyMode()

// *************************************************************************

/*!
  This method is invoked so timing can be considered before the scene graph
  is redrawn.
*/

void
SoQtSuperViewer::actualRedraw(void)
{
  SbBool changedComplexitySettings = FALSE;
  if(this->getInteractiveCount() && 
     PRIVATE(this)->howtomove != SoQtSuperViewerP::FULL)
    PRIVATE(this)->movingRedraw(TRUE);
  
  // FIXME: look into if it is possible to make an init method for the viewer
  // where we can place setupNodes(). This is ugly.
  // larsivi 20020318
  if(PRIVATE(this)->polygonoffsetindex == -1) PRIVATE(this)->setupNodes();
  if(!PRIVATE(this)->filled){
    changedComplexitySettings = TRUE;
    PRIVATE(this)->complexity->textureQuality = 0.0;
    PRIVATE(this)->drawstyleroot->whichChild = SO_SWITCH_ALL;
    PRIVATE(this)->drawstyle->style = SoDrawStyle::INVISIBLE;
    if(this->isHiddenparts()) {     
      // render as filled, but with the background color.
      PRIVATE(this)->hiddenlineroot->whichChild = SO_SWITCH_ALL;
      
      PRIVATE(this)->lightmodel->model.setIgnored(FALSE); // override as SoLightModel::BASE
      PRIVATE(this)->drawstyle->style.setIgnored(TRUE); // draw as-is filled/lines/points
      PRIVATE(this)->complexity->type.setIgnored(TRUE); // as-is rendering space
      PRIVATE(this)->complexity->value.setIgnored(TRUE); // as-is complexity on non-simple shapes

      PRIVATE(this)->basecolor->rgb.setIgnored(FALSE);
      PRIVATE(this)->basecolor->rgb.setValue(this->getBackgroundColor());

    }
  }
  else{
    if(!PRIVATE(this)->texturesenabled){
      PRIVATE(this)->complexity->textureQuality = 0.0;
      PRIVATE(this)->drawstyleroot->whichChild = PRIVATE(this)->complexityindex;
    }
    PRIVATE(this)->hiddenlineroot->whichChild = PRIVATE(this)->polygonoffsetindex;
  }
  inherited::actualRedraw();
  if(this->isHiddenparts()){ 
    PRIVATE(this)->hiddenlineroot->whichChild = SO_SWITCH_NONE;
    PRIVATE(this)->basecolor->rgb.setIgnored(TRUE);
    PRIVATE(this)->lightmodel->model.setIgnored(TRUE); // override as SoLightModel::BASE
    PRIVATE(this)->drawstyle->style.setIgnored(FALSE); // draw as-is filled/lines/points
    PRIVATE(this)->complexity->type.setIgnored(FALSE); // as-is rendering space
    PRIVATE(this)->complexity->value.setIgnored(FALSE); // as-is complexity on non-simple shapes
  }
  
  if(PRIVATE(this)->drawstyles) PRIVATE(this)->drawstyleRedraw();
  if(!PRIVATE(this)->filled){
    PRIVATE(this)->drawstyleroot->whichChild = PRIVATE(this)->complexityindex;
  }
  else{
    if(changedComplexitySettings)
      PRIVATE(this)->complexity->textureQuality = PRIVATE(this)->texturequality;
  }

  SbTime thisRedrawTime = SbTime::getTimeOfDay();
  double secs =
    thisRedrawTime.getValue() - PRIVATE(this)->prevRedrawTime.getValue();

  PRIVATE(this)->prevRedrawTime = thisRedrawTime;

  if (this->isAnimating()) {
    SbRotation deltaRotation = PRIVATE(this)->spinRotation;
    deltaRotation.scaleAngle(secs * 5.0);
    PRIVATE(this)->reorientCamera(deltaRotation);
  }

  if (this->getInteractiveCount())
    PRIVATE(this)->movingRedraw(FALSE);

  // the primitivescount
  if(PRIVATE(this)->currentindex >= 0 && this->isInformation()) 
    PRIVATE(this)->drawInformation();
                            
} // actualRedraw()

// *************************************************************************

/*!
  \internal

  Catch close events on the preferences window (to convert to hide
  events).
*/

bool
SoQtSuperViewer::eventFilter(QObject * obj, QEvent * e)
{
  inherited::eventFilter(obj, e);

  //There is no preferences window for the moment.
  /*
  // Catch pref window close events to avoid it actually being
  // destroyed.
  if (obj == PRIVATE(this)->prefwindow && e->type() == QEvent::Close) {
    ((QCloseEvent *)e)->ignore();
    PRIVATE(this)->prefwindow->hide();
    return TRUE;
  }
*/  
  return FALSE;
} // eventFilter()

// *************************************************************************

/*!
  \internal

  Removes an entry from the model list in the menu.
*/

void
SoQtSuperViewer::removeModelEntry()
{
  PRIVATE(this)->modelsubmenu->removeItemAt(PRIVATE(this)->currentindex);
} // removeModelEntry()

// *************************************************************************

#define MOUSEBUTTON_EVENT_TYPE  (SoMouseButtonEvent::getClassTypeId())
#define LOCATION2_EVENT_TYPE    (SoLocation2Event::getClassTypeId())
#define MOTION3_EVENT_TYPE      (SoMotion3Event::getClassTypeId())
#define KEYBOARD_EVENT_TYPE     (SoKeyboardEvent::getClassTypeId())

// Documented in superclass.
SbBool
SoQtSuperViewer::processSoEvent(const SoEvent * const ev)
{
#if SOQT_DEBUG && 0 // debug
  SoDebugError::postInfo("SoQtSuperViewer::processSoEvent",
                          "[invoked], event '%s'",
                          ev->getTypeId().getName().getString());
#endif // debug

  // We're in "interact" mode (ie *not* the camera modification mode),
  // so don't handle the event here. It should either be forwarded to
  // the scenegraph, or caught by So@Gui@Viewer::processSoEvent() if
  // it's an ESC press (to switch modes).
  if (!this->isViewing()) { return inherited::processSoEvent(ev); }
    
  // Events during seeks are ignored, except those which influence the
  // seek mode itself -- these are handled further up the inheritance
  // hierarchy.
  if (this->isSeekMode()) { return inherited::processSoEvent(ev); }

  if (this->isFlyMode() && (ev->getTypeId() == LOCATION2_EVENT_TYPE ||
                            ev->getTypeId() == MOUSEBUTTON_EVENT_TYPE))
    return PRIVATE(this)->processMouseEvent(ev);

  PRIVATE(this)->canvasvec = this->getGLSize();
  const SoType type(ev->getTypeId());
  const SbVec2f prevnormalized = PRIVATE(this)->lastmouseposition;
  const SbVec2s pos(ev->getPosition());
  const SbVec2f posn((float) pos[0] / (float) SoQtMax((int)(PRIVATE(this)->canvasvec[0]-1), 1),
                     (float) pos[1] / (float) SoQtMax((int)(PRIVATE(this)->canvasvec[1]-1), 1));

  PRIVATE(this)->lastmouseposition = posn;

  // Set to TRUE if any event processing happened. Note that it is not
  // necessary to restrict ourselves to only do one "action" for an
  // event, we only need this flag to see if any processing happened
  // at all.
  SbBool processed = FALSE;


  // Mismatches in state of the Ctrl key happens if the user presses
  // or releases it outside the viewer window.
  if (PRIVATE(this)->controldown != ev->wasCtrlDown()) {
    PRIVATE(this)->controldown = ev->wasCtrlDown();
    processed = TRUE;
  }

  // Mouse Button / Spaceball Button handling

  if (type.isDerivedFrom(MOUSEBUTTON_EVENT_TYPE)) {
    const SoMouseButtonEvent * const event = (const SoMouseButtonEvent *) ev;
    const int button = event->getButton();
    const SbBool press = event->getState() == SoButtonEvent::DOWN ? TRUE : FALSE;

    // SoDebugError::postInfo("processSoEvent", "button = %d", button);
    switch (button) {
    case SoMouseButtonEvent::BUTTON1:
      PRIVATE(this)->button1down = press;
      break;
    case SoMouseButtonEvent::BUTTON2:
      PRIVATE(this)->button2down = press;
      break;
    case SoMouseButtonEvent::BUTTON3:
      PRIVATE(this)->button3down = press;
      break;
    default:
      break;
    } // switch (button)

    if (press) {
      switch (button) {
      case SoMouseButtonEvent::BUTTON1:
        if (! this->isSeekMode()) {
          if (this->isAnimating()) this->stopAnimating();
          this->interactiveCountInc();
          PRIVATE(this)->clearLog();
          processed = TRUE;
        }
        break;

      case SoMouseButtonEvent::BUTTON3:
        {
          if (this->isAnimating()) this->stopAnimating();
          this->interactiveCountInc();
          SoCamera * const camera = this->getCamera();
          if (camera == NULL) { // can happen for empty scenegraph
            PRIVATE(this)->panningplane = SbPlane(SbVec3f(0, 0, 1), 0);
          }
          else {
            SbViewVolume volume = camera->getViewVolume(this->getGLAspectRatio());
            PRIVATE(this)->panningplane = volume.getPlane(camera->focalDistance.getValue());
          }
          processed = TRUE;
        }
        break;

#ifdef HAVE_SOMOUSEBUTTONEVENT_BUTTON5
      case SoMouseButtonEvent::BUTTON4:
        PRIVATE(this)->zoom(-0.1f);
        processed = TRUE;
        break;

      case SoMouseButtonEvent::BUTTON5:
        PRIVATE(this)->zoom(0.1f);
        processed = TRUE;
        break;
#endif // HAVE_SOMOUSEBUTTONEVENT_BUTTON5

      default:
        break;
      } // switch (button)

    } else { // ! press
      switch (button) {
      case SoMouseButtonEvent::BUTTON1:
        {
          this->stopAnimating();
          if (! this->isSeekMode()) {
            if (! this->isAnimationEnabled() || PRIVATE(this)->log.historysize < 3) {
              // FIXME: attention: here lies dragons! This will f*ck
              // up the interactioncounter if a mouse release "just
              // happens", as can be the case (dependent on the native
              // UI toolkit). At least Win32 can give us a release
              // event with no press event in advance. 20010709 mortene.
              this->interactiveCountDec();
            }
            else {
              const SbVec2s glsize(this->getGLSize());
              SbVec3f from = PRIVATE(this)->spinprojector->project(SbVec2f(float(PRIVATE(this)->log.position[2][0]) / float(SoQtMax(glsize[0]-1, 1)),
                                                                   float(PRIVATE(this)->log.position[2][1]) / float(SoQtMax(glsize[1]-1, 1))));
              SbVec3f to = PRIVATE(this)->spinprojector->project(posn);
              SbRotation rot = PRIVATE(this)->spinprojector->getRotation(from, to);

              SbTime stoptime = (event->getTime() - PRIVATE(this)->log.time[0]);
              if (stoptime.getValue() > 0.1) {
                this->interactiveCountDec();
              }
              else {
                SbTime delta = (PRIVATE(this)->log.time[0] - PRIVATE(this)->log.time[2]);
                float deltatime = (float) delta.getValue();

                rot.invert();
                rot.scaleAngle(0.2f / deltatime);
                
                SbVec3f axis;
                float radians;
                rot.getValue(axis, radians);
                if (radians < 0.01f || deltatime > 0.3f) {
                  this->interactiveCountDec();
                }
                else {
                  PRIVATE(this)->spinRotation = rot;
                  PRIVATE(this)->spinanimating = TRUE;
                  this->scheduleRedraw();
                }
              }
            }
          }
        }
        processed = TRUE;
        break;

      case SoMouseButtonEvent::BUTTON3:
        this->interactiveCountDec();
        processed = TRUE;
        break;

#ifdef HAVE_SOMOUSEBUTTONEVENT_BUTTON5
      case SoMouseButtonEvent::BUTTON4:
        processed = TRUE; // don't pass on
        break;

      case SoMouseButtonEvent::BUTTON5:
        processed = TRUE; // don't pass on
        break;
#endif // HAVE_SOMOUSEBUTTONEVENT_BUTTON5

      default:
        break;
      } // switch (button)
    }
  }

  // Mouse Movement handling
  if (type.isDerivedFrom(LOCATION2_EVENT_TYPE)) {
    const SoLocation2Event * const event = (const SoLocation2Event *) ev;

    if (PRIVATE(this)->button1down || PRIVATE(this)->button3down) processed = TRUE;

    if ((PRIVATE(this)->button1down && PRIVATE(this)->button3down) ||
         (PRIVATE(this)->button3down && PRIVATE(this)->controldown)) {
      PRIVATE(this)->zoomByCursor(posn, prevnormalized);
    }
    else if ((PRIVATE(this)->button1down && PRIVATE(this)->controldown) || PRIVATE(this)->button3down) {
      PRIVATE(this)->pan(posn, prevnormalized);
    }
    else if (PRIVATE(this)->button1down) {
      PRIVATE(this)->addToLog(event->getPosition(), event->getTime());
      PRIVATE(this)->spin(posn);
    }

  }

  // Keyboard handling
  if (type.isDerivedFrom(KEYBOARD_EVENT_TYPE)) {
    const SoKeyboardEvent * const event = (const SoKeyboardEvent *) ev;
    const SbBool press = event->getState() == SoButtonEvent::DOWN ? TRUE : FALSE;
    if (press) {
      if (event->getKey() == SoKeyboardEvent::LEFT_CONTROL
        || event->getKey() == SoKeyboardEvent::RIGHT_CONTROL) {
        PRIVATE(this)->controldown = TRUE;
        processed = TRUE;
      }
    } else {
      if (event->getKey() == SoKeyboardEvent::LEFT_CONTROL
        || event->getKey() == SoKeyboardEvent::RIGHT_CONTROL) {
        PRIVATE(this)->controldown = FALSE;
        processed = TRUE;
      }
    }
  }

  // Spaceball & Joystick handling
  if (type.isDerivedFrom(MOTION3_EVENT_TYPE)) {
    SoMotion3Event * const event = (SoMotion3Event *) ev;
    SoCamera * const camera = this->getCamera();
    if (camera) {
      if (PRIVATE(this)->motion3OnCamera) {
        camera->position =
          camera->position.getValue() + event->getTranslation();
        camera->orientation =
          camera->orientation.getValue() * event->getRotation();
        processed = TRUE;
      } else {
        // FIXME: move/rotate model
#if SOQT_DEBUG
        SoDebugError::postInfo("SoQtSuperViewer::processSoEvent",
                               "SoMotion3Event for model movement is not implemented yet");
#endif // SOQT_DEBUG
        processed = TRUE;
      }
    }
  }

  if (processed) {
    enum { STATE_LMB = 0x01, STATE_MMB = 0x02, STATE_CTRL = 0x04 };
    unsigned short stateflags =
      (PRIVATE(this)->button1down ? STATE_LMB : 0) +
      (PRIVATE(this)->button3down ? STATE_MMB : 0) +
      (PRIVATE(this)->controldown ? STATE_CTRL : 0);

    SoQtSuperViewerP::ViewerMode mode;

    switch (stateflags) {
    case 0:
      mode = SoQtSuperViewerP::INTERACT;
      break;

    case STATE_LMB:
      mode = SoQtSuperViewerP::DRAGGING;
      break;

    case STATE_MMB:
    case (STATE_LMB | STATE_CTRL):
      mode = SoQtSuperViewerP::PANNING;
      break;

    case STATE_CTRL:
      mode = SoQtSuperViewerP::WAITING_FOR_PAN;
      break;

    case (STATE_MMB | STATE_CTRL):
    case (STATE_LMB | STATE_MMB):
    case (STATE_LMB | STATE_MMB | STATE_CTRL):
      mode = SoQtSuperViewerP::ZOOMING;
      break;

    default:
      assert(FALSE && "unhandled input state");
      break;
    }

    PRIVATE(this)->setMode(mode);
  }

  // If not handled in this class, pass on upwards in the inheritance
  // hierarchy.
  return processed || inherited::processSoEvent(ev);
} // processSoEvent()

// *************************************************************************

/*!
  Opens a model with filename \c filename, and shows it if \c show is
  set to \a TRUE.

*/

SbBool
SoQtSuperViewer::openModel(SbString * const filename, SbBool show){
  
  SoSeparator * newroot;
  newroot = PRIVATE(this)->loadModelFromFile(filename);
  if(newroot == NULL) return FALSE;
  if (PRIVATE(this)->openmodels == NULL) {
    PRIVATE(this)->openmodels = new SoSeparator;
    PRIVATE(this)->openmodels->ref();
  }

  SbIntList slashes;
  filename->findAll("/", slashes);
  PRIVATE(this)->pathtomodels.append(new SbString(*filename));
  PRIVATE(this)->modelnames.append(new SbString(
    filename->getSubString(slashes[slashes.getLength() - 1] + 1).getString()));
  PRIVATE(this)->openmodels->addChild(newroot);
  PRIVATE(this)->currentroot = newroot;
  //search for textures
  PRIVATE(this)->searchaction = new SoSearchAction;
  PRIVATE(this)->searchaction->setInterest(SoSearchAction::ALL);
  PRIVATE(this)->searchaction->setType(SoTexture2::getClassTypeId(), TRUE);
  PRIVATE(this)->searchaction->apply(newroot);
  PRIVATE(this)->modeltextures.append(
                 PRIVATE(this)->searchaction->getPaths().getLength());
  delete PRIVATE(this)->searchaction;
  PRIVATE(this)->searchaction = NULL;
 
  if(show) {
    this->showModel(PRIVATE(this)->openmodels->getNumChildren() - 1);
  }

  return TRUE;

} // openModel()

// *************************************************************************

/*!
  Sets the model given by \c index as the current model and sets up the
  viewer to view it.
*/

void
SoQtSuperViewer::showModel(int index)
{
  PRIVATE(this)->currentindex = index;
  PRIVATE(this)->currentroot = (SoSeparator *)
    PRIVATE(this)->openmodels->getChild(index);
  this->setSceneGraph(PRIVATE(this)->currentroot);
  PRIVATE(this)->resetCountAction();
  PRIVATE(this)->resetBBox();

  SbString caption= "Super Viewer - ";
  caption.operator+=(((SbString *)PRIVATE(this)->modelnames[index])->getString());
  this->setTitle(caption.getString());
  this->saveHomePosition();
} // showModel()

// *************************************************************************

// doc in super
void          // virtual
SoQtSuperViewer::sizeChanged(const SbVec2s & size)
{
#if SOQT_DEBUG && 0
  SoDebugError::postInfo("SoQtSuperViewer::sizeChanged", "[invoked (%d, %d)]",
                         size[0], size[1]);
#endif // SOQT_DEBUG
  if (size[0] <= 0 || size[1] <= 0) return;
  if (PRIVATE(this)->viewerwidget && PRIVATE(this)->canvas) {
    // SoDebugError::postInfo("SoQtSuperViewer::sizeChanged", "[resizing]");
    PRIVATE(this)->viewerwidget->setGeometry(
                 0, 0, size[0], size[1] + PRIVATE(this)->menubar->height());
    PRIVATE(this)->canvas->setGeometry(
                 0, 0 + PRIVATE(this)->menubar->height(), size[0], size[1]);
  }
  inherited::sizeChanged(size);
  
} // sizeChanged()

// *************************************************************************

#if SOQT_DEBUG
static const char * getSoQtSuperViewerRCSId(void) { return rcsid; }
#endif // SOQT_DEBUG


