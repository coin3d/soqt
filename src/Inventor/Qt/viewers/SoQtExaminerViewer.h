/**************************************************************************\
 *
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

//  $Id$

#ifndef __SOQT_EXAMINERVIEWER_H__
#define __SOQT_EXAMINERVIEWER_H__

#include <Inventor/Qt/viewers/SoQtFullViewer.h>
#include <Inventor/SbLinear.h>

class SbSphereSheetProjector;
class SoTimerSensor;
class SoSeparator;
class SoSwitch;
class SoTranslation;
class SoScale;

class QPushButton;
class QLabel;
class QLineEdit;
class QtThumbwheel;
class QPixmap;
class QTimer;

// *************************************************************************

class SoQtExaminerViewer : public SoQtFullViewer {
  typedef SoQtFullViewer inherited;

  Q_OBJECT

public:
  SoQtExaminerViewer(QWidget * parent = NULL,
                     const char * name = NULL,
                     SbBool buildInsideParent = TRUE,
                     SoQtFullViewer::BuildFlag flag = BUILD_ALL,
                     SoQtViewer::Type type = BROWSER);
  ~SoQtExaminerViewer(void);

  void setFeedbackVisibility(const SbBool on);
  SbBool isFeedbackVisible(void) const;

  void setFeedbackSize(const int size);
  int getFeedbackSize(void) const;

  void setAnimationEnabled(SbBool on);
  SbBool isAnimationEnabled(void);

  void stopAnimating(void);
  SbBool isAnimating(void);

  virtual void setViewing(SbBool on);
  virtual void setCamera(SoCamera * cam);
  virtual void setCursorEnabled(SbBool on);

protected:
  SoQtExaminerViewer(QWidget * parent,
                     const char * name,
                     SbBool buildInsideParent,
                     SoQtFullViewer::BuildFlag flag,
                     SoQtViewer::Type type,
                     SbBool buildNow);

  virtual void leftWheelMotion(float val);
  virtual void bottomWheelMotion(float val);
  virtual void rightWheelMotion(float val);

  virtual QWidget * makeSubPreferences(QWidget * parent);
  virtual void createViewerButtons(QWidget * parent, SbPList * buttonlist);

  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;

  virtual void openViewerHelpCard(void);

  virtual void processEvent(QEvent * anyevent);
  virtual void setSeekMode(SbBool on);
  virtual void actualRedraw(void);

private:
  enum ViewerMode {
    INTERACT,
    EXAMINE, DRAGGING,
    WAITING_FOR_SEEK,
    ZOOMING,
    WAITING_FOR_PAN, PANNING
  };

  ViewerMode currentmode;

  void reorientCamera(const SbRotation & rot);
  void zoom(const float diffvalue);
  void zoomByCursor(const SbVec2f & mousepos);
  void spin(const SbVec2f & mousepos);
  void pan(const SbVec2f & mousepos);

  void setMode(const ViewerMode mode);
  void setModeFromState(const unsigned int state);

  void drawAxisCross(void);
  void drawArrow(void);

  SbBool axiscrossOn;
  int axiscrossSize;

  QPixmap * orthopixmap, * perspectivepixmap;

  void constructor(SbBool buildNow);
  static void visibilityCB(void * data, SbBool visible);

  QTimer * spindetecttimer;
  SbBool spinanimating, animatingallowed;
  SoTimerSensor * timertrigger;
  static void timertriggeredCB(void * data, SoSensor *);

  SbSphereSheetProjector * projector;

  void setCursorRepresentation(const ViewerMode mode);
  QCursor * pancursor, * rotatecursor;
  QCursor * defaultcursor, * zoomcursor;

  SbVec2f lastmouseposition;
  SbPlane panningplane;

  SbRotation spinincrement;
  int spinsamplecounter;

  QPushButton * cameratogglebutton;
  QLabel * feedbacklabel1, * feedbacklabel2;
  QtThumbwheel * feedbackwheel;
  QLineEdit * feedbackedit;
  void setEnableFeedbackControls(const SbBool flag);

private slots:
  // Pref sheet.
  void spinAnimationToggled(bool flag);
  void feedbackVisibilityToggle(bool flag);
  void feedbackEditPressed();
  void feedbackWheelPressed();
  void feedbackSizeChanged(float val);
  void feedbackWheelReleased();
  // Button row.
  void cameratoggleClicked();

}; // class SoQtExaminerViewer

// *************************************************************************

#endif // ! __SOQT_EXAMINERVIEWER_H__
