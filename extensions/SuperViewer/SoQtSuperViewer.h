/**************************************************************************
 *
 *  This file is part of the Coin SoQt GUI binding library.
 *  Copyright (C) 1998-2001 by Systems in Motion.  All rights reserved.
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

#ifndef SOQT_SUPERVIEWER_H
#define SOQT_SUPERVIEWER_H

#include <Inventor/Qt/viewers/SoQtViewer.h>
#include <Inventor/nodes/SoComplexity.h>

//*************************************************************************


class SoQtSuperViewer : public SoQtViewer {
  SOQT_OBJECT_HEADER(SoQtSuperViewer, SoQtViewer);

  enum BuildFlag {
    //    BUILD_NOTHING    = 0x00,
    BUILD_MENUBAR    = 0x01,
    BUILD_TOOLBAR    = 0x02,
    BUILD_ALL        = (BUILD_MENUBAR | BUILD_TOOLBAR)
  };

  enum Menus {
    FILE_MENU        = 0x01,
    VIEW_MENU        = 0x02,
    SETTINGS_MENU    = 0x04,
    CAMERA_MENU      = 0x08,
    LIGHTS_MENU      = 0x10,
    HELP_MENU        = 0x20,
    BUILD_ALL_MENUS = (FILE_MENU | VIEW_MENU | SETTINGS_MENU | 
                        CAMERA_MENU | LIGHTS_MENU | HELP_MENU)
  };

  enum FileMenu {
    OPEN_MODEL        = 0x01,
    CLOSE_MODEL       = 0x02,
    CLOSE_ALL         = 0x04,
    MODELS            = 0x08,
    SEPARATOR_FILE_1  = 0x10,
    NEXT_MODEL        = 0x20,
    PREVIOUS_MODEL    = 0x40,
    REFRESH_MODEL     = 0x80,
    SNAPSHOT          = 0x100,
    SEPARATOR_FILE_2  = 0x200,
    EXIT              = 0x400,
    BUILD_FILE_MENU   = (OPEN_MODEL | CLOSE_MODEL | CLOSE_ALL | MODELS |
                         NEXT_MODEL | PREVIOUS_MODEL | REFRESH_MODEL |
                         SNAPSHOT | EXIT | SEPARATOR_FILE_1 | 
                         SEPARATOR_FILE_2)
  };

  enum ViewMenu {
    INFORMATION      = 0x01,
    FLATSHADING      = 0x02,
    SEPARATOR_VIEW_1 = 0x04,
    FILLED           = 0x08,
    BOUNDINGBOXES    = 0x10,
    WIREFRAME        = 0x20,
    VERTICES         = 0x40,
    HIDDEN_PARTS     = 0x80,
    TEXTURES         = 0x100,
    SEPARATOR_VIEW_2 = 0x200,
    WHILE_MOVING     = 0x400,
    BUILD_VIEW_MENU  = (INFORMATION | FLATSHADING | FILLED |
                        BOUNDINGBOXES | WIREFRAME | VERTICES |
                        HIDDEN_PARTS | TEXTURES | WHILE_MOVING |
                        SEPARATOR_VIEW_1 | SEPARATOR_VIEW_2)
  };

  enum SettingsMenu {
    INFORMATION_SETTING = 0x01,
    LINE_WIDTH          = 0x02,
    POINT_SIZE          = 0x04,
    LINE_COLOR          = 0x08,
    POINT_COLOR         = 0x10,
    BACKGROUND_COLOR    = 0x20,
    RENDER_QUALITY      = 0x40,
    TEXTURE_QUALITY     = 0x80,
    TRANSPARENCY_TYPE   = 0x100,
    BUILD_SETTINGS_MENU = (INFORMATION_SETTING | LINE_WIDTH |
                           POINT_SIZE | LINE_COLOR |
                           POINT_COLOR | BACKGROUND_COLOR |
                           RENDER_QUALITY | TEXTURE_QUALITY |
                           TRANSPARENCY_TYPE)
  };

  enum CameraMenu {
    VIEW_ALL           = 0x01,
    RESET_VIEW         = 0x02,
    SEEK               = 0x04,
    VIEW_MODES         = 0x08,
    FLY_MODES          = 0x10,
    SEPARATOR_CAMERA_1 = 0x20,
    CAMERAS            = 0x40,
    BUILD_CAMERA_MENU  = (VIEW_ALL | RESET_VIEW | SEEK |
                          VIEW_MODES | FLY_MODES | CAMERAS |
                          SEPARATOR_CAMERA_1)
  };

 public:
  SoQtSuperViewer(
    QWidget * parent = NULL,
    const char * name = NULL,
    SbBool embed = TRUE,
    BuildFlag flag = BUILD_ALL,
    SoQtViewer::Type type = BROWSER,
    SbBool build = TRUE);
  ~SoQtSuperViewer(void);

  void init(void);

  void setBars(const int buildFlag);
  void setMenus(const int buildFlag = 0, 
                const int enabled = 0);
  void setFileMenuItems(const int buildFlag = 0, 
                        const int enabled = 0,
                        const int checked = 0);
  void setViewMenuItems(const int buildFlag = 0, 
                        const int enabled = 0,
                        const int checked = 0);
  void setSettingsMenuItems(const int buildFlag = 0, 
                            const int enabled = 0,
                            const int checked = 0);
  void setCameraMenuItems(const int buildFlag = 0, 
                          const int enabled = 0,
                          const int checked = 0);

  const int getBuiltItems(const Menus menu);
  const int getEnabledItems(const Menus menu);
  const int getCheckedItems(const Menus menu);

  void setMenuBar(const SbBool on);
  SbBool isMenuBar(void) const;

  void setFileMenu(const SbBool on);
  SbBool isFileMenu(void) const;

  void setViewMenu(const SbBool on);
  SbBool isViewMenu(void) const;

  void setSettingsMenu(const SbBool on);
  SbBool isSettingsMenu(void) const;

  void setCameraMenu(const SbBool on);
  SbBool isCameraMenu(void) const;

  void setLightsMenu(const SbBool on);
  SbBool isLightsMenu(void) const;

  void toggleFilled(void);
  SbBool isFilled(void) const;

  void toggleInformation(void);
  SbBool isInformation(void) const;

  void toggleFlatshading(void);
  SbBool isFlatshading(void) const;

  void toggleBoundingboxes(void);
  SbBool isBoundingboxes(void) const;

  void toggleWireframe(void);
  SbBool isWireframe(void) const;

  void toggleVertices(void);
  SbBool isVertices(void) const;

  void toggleHiddenparts(void);
  SbBool isHiddenparts(void) const;

  void toggleTextures(void);
  SbBool isTextures(void) const;

  void setAnimationEnabled(const SbBool enable);
  SbBool isAnimationEnabled(void) const;

  void stopAnimating(void);
  SbBool isAnimating(void) const;

  void setLineWidth(int value);
  int getLineWidth(void) const;

  void setPointSize(int value);
  int getPointSize(void) const;

  void setPointColor(const SbColor & color);
  void setLineColor(const SbColor & color);

  void toggleDistance(void);
  SbBool isDistance(void) const;

  void setRenderType(SoComplexity::Type type);
  void setRenderQuality(float value);
  void setTextureQuality(float value);

  virtual void setCamera(SoCamera * cam);

   // filemenu
  SbBool openModel(SbString * const filename, SbBool show);
  SbBool closeModel();
  void closeAllModels();
  void nextModel();
  void previousModel();
  void showModel(int index);
  void refreshModel();
  void snapshot();
  void quit();

  void setFileFilter(const SbString filter);
  SbString getFileFilter(void) const;
  void setModelDirectory(const SbString directory);
  SbString getModelDirectory(void) const;
  void setImageDirectory(const SbString directory);
  SbString getImageDirectory(void) const;

  virtual void setCursorEnabled(SbBool enable);
  virtual void setSeekMode(SbBool enable);

  virtual void setFlyMode(SbBool enable);
  virtual SbBool isFlyMode(void);

  QWidget * getRenderAreaWidget(void) const;
 
//**********************************************************************
 protected:
  virtual bool eventFilter(QObject * obj, QEvent * e);
  virtual const char * getDefaultWidgetName(void) const;
  const char * getDefaultTitle(void) const;
  const char * getDefaultIconTitle(void) const;
 
  virtual void sizeChanged(const SbVec2s & size);

  QWidget * buildWidget(QWidget * parent);

  void buildMenuBar(void);
  void buildFileMenu(void);
  void buildViewMenu(void);
  void buildSettingsMenu(void);
  void buildCameraMenu(void);
  void buildLightsMenu(void);
  
  void removeModelEntry(void);

  virtual void actualRedraw(void);
  
  virtual SbBool processSoEvent(const SoEvent * const event);

 protected:
 
//**********************************************************************
 private:
 
  class SoQtSuperViewerP * pimpl;
  friend class SoQtSuperViewerP;

};

#endif //! SOQT_SUPERVIEWER_H







