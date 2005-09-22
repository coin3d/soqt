/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

#ifndef SOQT_FULLVIEWER_H
#define SOQT_FULLVIEWER_H

#include <Inventor/Qt/viewers/SoQtViewer.h>

class SoQtPopupMenu;

// *************************************************************************

class SOQT_DLL_API SoQtFullViewer : public SoQtViewer {
  SOQT_OBJECT_ABSTRACT_HEADER(SoQtFullViewer, SoQtViewer);

public:
  enum BuildFlag {
    BUILD_NONE       = 0x00,
    BUILD_DECORATION = 0x01,
    BUILD_POPUP      = 0x02,
    BUILD_ALL        = (BUILD_DECORATION | BUILD_POPUP)
  };

  void setDecoration(const SbBool on);
  SbBool isDecoration(void) const;

  void setPopupMenuEnabled(const SbBool on);
  SbBool isPopupMenuEnabled(void) const;

  QWidget * getAppPushButtonParent(void) const;
  void addAppPushButton(QWidget * newButton);
  void insertAppPushButton(QWidget * newButton, int index);
  void removeAppPushButton(QWidget * oldButton);
  int findAppPushButton(QWidget * oldButton) const;
  int lengthAppPushButton(void) const;

  QWidget * getRenderAreaWidget(void) const;

  virtual void setViewing(SbBool on);

  virtual void setComponentCursor(const SoQtCursor & cursor);

protected:
  SoQtFullViewer(QWidget * parent,
                    const char * name,
                    SbBool embed,
                    BuildFlag flag,
                    Type type,
                    SbBool build);
  ~SoQtFullViewer();

  virtual void sizeChanged(const SbVec2s & size);

  QWidget * buildWidget(QWidget * parent);

  virtual void buildDecoration(QWidget * parent);
  virtual QWidget * buildLeftTrim(QWidget * parent);
  virtual QWidget * buildBottomTrim(QWidget * parent);
  virtual QWidget * buildRightTrim(QWidget * parent);
  QWidget * buildAppButtons(QWidget * parent);
  QWidget * buildViewerButtons(QWidget * parent);
  virtual void createViewerButtons(QWidget * parent, SbPList * buttonlist);

  virtual void buildPopupMenu(void);
  virtual void setPopupMenuString(const char * title);
  virtual void openPopupMenu(const SbVec2s position);

  virtual void leftWheelStart(void);
  virtual void leftWheelMotion(float);
  virtual void leftWheelFinish(void);
  float getLeftWheelValue(void) const;
  void setLeftWheelValue(const float value);

  virtual void bottomWheelStart(void);
  virtual void bottomWheelMotion(float);
  virtual void bottomWheelFinish(void);
  float getBottomWheelValue(void) const;
  void setBottomWheelValue(const float value);

  virtual void rightWheelStart(void);
  virtual void rightWheelMotion(float);
  virtual void rightWheelFinish(void);
  float getRightWheelValue(void) const;
  void setRightWheelValue(const float value);

  void setLeftWheelString(const char * const name);
  QWidget * getLeftWheelLabelWidget(void) const;
  void setBottomWheelString(const char * const name);
  QWidget * getBottomWheelLabelWidget(void) const;
  void setRightWheelString(const char * const name);
  QWidget * getRightWheelLabelWidget(void) const;

  virtual SbBool processSoEvent(const SoEvent * const event);

protected:
  QWidget * leftWheel;
  QWidget * rightWheel;
  QWidget * bottomWheel;

  QWidget * leftDecoration;
  QWidget * rightDecoration;
  QWidget * bottomDecoration;

  QWidget * leftWheelLabel;
  char * leftWheelStr;
  float leftWheelVal;

  QWidget * rightWheelLabel;
  char * rightWheelStr;
  float rightWheelVal;

  QWidget * bottomWheelLabel;
  char * bottomWheelStr;
  float bottomWheelVal;

  SoQtPopupMenu * prefmenu;

private:
  // Private class for implementation hiding. The idiom we're using is
  // a variant of what is known as the "Cheshire Cat", and is also
  // described as the "Bridge" pattern in «Design Patterns» by Gamma
  // et al (aka The Gang Of Four).
  class SoQtFullViewerP * pimpl;

  friend class SoGuiFullViewerP;
  friend class SoQtFullViewerP;



// FIXME: get rid of non-templatized code. 20020108 mortene.

#ifdef __COIN_SOXT__ // FIXME: get rid of non-templatized code. 20020108 mortene.
protected:
  Widget buildFunctionsSubmenu(Widget popup);
  Widget buildDrawStyleSubmenu(Widget popup);

  char * popupTitle;
  SbBool popupEnabled;
  SbPList * viewerButtonWidgets;
#endif // __COIN_SOXT__
};

// *************************************************************************

#endif // ! SOQT_FULLVIEWER_H
