/**************************************************************************
 *
 *  This file is part of the Coin SoQt GUI binding library.
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
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

// $Id$

#ifndef SOQT_EXAMINERVIEWER_H
#define SOQT_EXAMINERVIEWER_H

#include <Inventor/SbLinear.h>

#include <Inventor/Qt/viewers/SoQtFullViewer.h>

class SoSeparator;
class SoSwitch;
class SoTranslation;
class SoScale;

class QPushButton;
class QLabel;
class QLineEdit;
class QPixmap;
class QTimer;

class SoQtThumbWheel;
class SoAnyExaminerViewer;

// *************************************************************************

class SOQT_DLL_API SoQtExaminerViewer : public SoQtFullViewer {
  SOQT_OBJECT_HEADER(SoQtExaminerViewer, SoQtFullViewer);
  friend class SoAnyExaminerViewer;
  Q_OBJECT

public:
  SoQtExaminerViewer(
    QWidget * parent = NULL,
    const char * name = NULL,
    SbBool embed = TRUE,
    SoQtFullViewer::BuildFlag flag = BUILD_ALL,
    SoQtViewer::Type type = BROWSER);
  ~SoQtExaminerViewer(void);

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
  virtual void resetToHomePosition(void);
  virtual void viewAll(void);

protected:
  SoQtExaminerViewer(
    QWidget * parent,
    const char * name,
    SbBool embed,
    SoQtFullViewer::BuildFlag flag,
    SoQtViewer::Type type,
    SbBool build);


  virtual void leftWheelMotion(float val);
  virtual void bottomWheelMotion(float val);
  virtual void rightWheelMotion(float val);

  virtual QWidget * makeSubPreferences(QWidget * parent);
  virtual void createViewerButtons(QWidget * parent, SbPList * buttonlist);

  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;

  virtual void openViewerHelpCard(void);

  virtual SbBool processSoEvent(const SoEvent * const event);
  virtual void processEvent(QEvent * anyevent);
  virtual void setSeekMode(SbBool enable);
  virtual void actualRedraw(void);

  virtual void afterRealizeHook(void);

private:
  QPixmap * orthopixmap, * perspectivepixmap;

  void constructor(SbBool buildNow);
  void visibilityCallback(SbBool visible);
  static void visibilityCB(void * data, SbBool visible);

  QTimer * spindetecttimer;

  void setCursorRepresentation(int mode);
  QCursor * pancursor, * rotatecursor;
  QCursor * defaultcursor, * zoomcursor;

  QPushButton * cameratogglebutton;
  QLabel * feedbacklabel1, * feedbacklabel2;
  SoQtThumbWheel * feedbackwheel;
  QLineEdit * feedbackedit;
  void setEnableFeedbackControls(const SbBool flag);

private slots:

// preferences window:
  void spinAnimationToggled(bool);
  void feedbackVisibilityToggle(bool);
  void feedbackEditPressed(void);
  void feedbackWheelPressed(void);
  void feedbackSizeChanged(float val);
  void feedbackWheelReleased(void);

// viewer buttons row:
  void cameratoggleClicked(void);

private:
  SoAnyExaminerViewer * const common;

}; // class SoQtExaminerViewer

// *************************************************************************

#endif // ! SOQT_EXAMINERVIEWER_H
