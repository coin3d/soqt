/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2004 by Systems in Motion.  All rights reserved.
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
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

#ifndef SOQT_EXAMINERVIEWER_H
#define SOQT_EXAMINERVIEWER_H

#include <Inventor/SbLinear.h>
#include <Inventor/Qt/viewers/SoQtFullViewer.h>

class SoSeparator;
class SoSwitch;
class SoTranslation;
class SoScale;

class SoQtThumbWheel;

// *************************************************************************

class SOQT_DLL_API SoQtExaminerViewer : public SoQtFullViewer {
  SOQT_OBJECT_HEADER(SoQtExaminerViewer, SoQtFullViewer);

public:
  SoQtExaminerViewer(QWidget * parent = NULL,
                        const char * name = NULL,
                        SbBool embed = TRUE,
                        SoQtFullViewer::BuildFlag flag = BUILD_ALL,
                        SoQtViewer::Type type = BROWSER);
  ~SoQtExaminerViewer();

  void setAnimationEnabled(const SbBool enable);
  SbBool isAnimationEnabled(void) const;

  void stopAnimating(void);
  SbBool isAnimating(void) const;

  void setFeedbackVisibility(const SbBool enable);
  SbBool isFeedbackVisible(void) const;

  void setFeedbackSize(const int size);
  int getFeedbackSize(void) const;

  virtual void setViewing(SbBool enable);
  virtual void setCamera(SoCamera * camera);
  virtual void setCursorEnabled(SbBool enable);

protected:
  SoQtExaminerViewer(QWidget * parent,
                        const char * name,
                        SbBool embed,
                        SoQtFullViewer::BuildFlag flag,
                        SoQtViewer::Type type,
                        SbBool build);

  virtual void leftWheelMotion(float val);
  virtual void bottomWheelMotion(float val);
  virtual void rightWheelMotion(float val);

  virtual void createViewerButtons(QWidget * parent, SbPList * buttonlist);

  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;

  virtual SbBool processSoEvent(const SoEvent * const event);
  virtual void setSeekMode(SbBool enable);
  virtual void actualRedraw(void);

  virtual void afterRealizeHook(void);

private:
  class SoQtExaminerViewerP * pimpl;

  friend class SoGuiExaminerViewerP;
  friend class SoQtExaminerViewerP;
};

#endif // ! SOQT_EXAMINERVIEWER_H
