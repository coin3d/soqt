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
    BUILD_NONE       = 0x00,
    BUILD_MENUBAR    = 0x01,
    FILE_MENU        = 0x02,
    VIEW_MENU        = 0x04,
    SETTINGS_MENU    = 0x08,
    CAMERA_MENU      = 0x10,
    LIGHTS_MENU      = 0x20,
    //FIXME: Popup menu presence not yet decided on.
    //BUILD_POPUP    = 0x02,
    BUILD_ALL        = (BUILD_MENUBAR | FILE_MENU | VIEW_MENU | 
                        SETTINGS_MENU | CAMERA_MENU | LIGHTS_MENU)
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
  
  void addModelEntry(SbString * const filename);
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







