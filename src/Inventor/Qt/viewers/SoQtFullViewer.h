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

#ifndef SOQT_FULLVIEWER_H
#define SOQT_FULLVIEWER_H

#include <Inventor/Qt/viewers/SoQtViewer.h>
#include <Inventor/Qt/viewers/SoAnyFullViewer.h>

class QPushButton;
class QLayout;
class QLabel;
class QLineEdit;
class QSlider;

class SoAnyPopupMenu;
class SoQtThumbWheel;

// *************************************************************************

class SoQtFullViewer :
  public SoQtViewer,
  public SoAnyFullViewer
{
  typedef SoQtViewer inherited;
  friend class SoAnyFullViewer;

  Q_OBJECT

public:
  enum BuildFlag {
    BUILD_NONE       = 0x00,
    BUILD_DECORATION = 0x01,
    BUILD_POPUP      = 0x02,
    BUILD_ALL        = 0xff
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

  QWidget * getRenderAreaWidget(void);

  // internal
  // These are overloaded to update user interface components.
  virtual void setViewing(SbBool on);
  virtual void setHeadlight(SbBool on);
  virtual void setDrawStyle(SoQtViewer::DrawType type,
                            SoQtViewer::DrawStyle style);
  virtual void setBufferingType(SoQtViewer::BufferType type);
  virtual void setCamera(SoCamera * cam);
  virtual void hide(void);

protected:
  SoQtFullViewer(
    QWidget * parent,
    const char * name,
    SbBool buildInsideParent,
    BuildFlag flag,
    Type type,
    SbBool buildNow );
  ~SoQtFullViewer(void);

  virtual bool eventFilter(QObject * obj, QEvent * e);

  QWidget * buildWidget(QWidget * parent);

  virtual void buildDecoration(QWidget * parent);
  virtual QWidget * buildLeftTrim(QWidget * parent);
  virtual QWidget * buildBottomTrim(QWidget * parent);
  virtual QWidget * buildRightTrim(QWidget * parent);
  QWidget * buildAppButtons(QWidget * parent);
  QWidget * buildViewerButtons(QWidget * parent);
  virtual void createViewerButtons(QWidget * parent, SbPList * buttonlist);

  virtual void buildPopupMenu(void);
  void setPopupMenuString(const char * title);

  virtual QWidget * makeSubPreferences(QWidget * parent);
  void setPrefSheetString(const char * title);

  virtual void leftWheelStart(void);
  virtual void leftWheelMotion(float);
  virtual void leftWheelFinish(void);
  float getLeftWheelValue(void) const;
  virtual void bottomWheelStart(void);
  virtual void bottomWheelMotion(float);
  virtual void bottomWheelFinish(void);
  float getBottomWheelValue(void) const;
  virtual void rightWheelStart(void);
  virtual void rightWheelMotion(float);
  virtual void rightWheelFinish(void);
  float getRightWheelValue(void) const;

  void setLeftWheelString(const char * name);
  void setBottomWheelString(const char * name);
  void setRightWheelString(const char * name);

  virtual void openViewerHelpCard(void);

  SoQtThumbWheel * getThumbwheel( int num );

  enum {
    LEFTDECORATION,
    BOTTOMDECORATION,
    RIGHTDECORATION,

    FIRSTDECORATION = LEFTDECORATION,
    LASTDECORATION = RIGHTDECORATION,
    NUMDECORATIONS = LASTDECORATION - FIRSTDECORATION + 1
  };

private:
  QWidget * makePreferencesWindow(void);
  QWidget * makeSeekPreferences(QWidget * parent);
  QWidget * makeSeekDistancePreferences(QWidget * parent);
  QWidget * makeZoomPreferences(QWidget * parent);
  QWidget * makeAutoclipPreferences(QWidget * parent);

  QWidget * viewerwidget, * canvasparent, * canvas;
  SbBool decorations;
  float wheelvalues[NUMDECORATIONS];
  QString wheelstrings[NUMDECORATIONS];
  SoQtThumbWheel * wheels[NUMDECORATIONS];
  QLabel * wheellabels[NUMDECORATIONS];
  QWidget * decorform[NUMDECORATIONS];

  SbString menutitle;
  SoAnyPopupMenu * prefmenu;
  SbBool menuenabled;

  QLayout * mainlayout;
  void showDecorationWidgets(SbBool onOff);

  QLayout * appbuttonlayout;
  QWidget * appbuttonform;
  SbPList * appbuttonlist;
  void layoutAppButtons(QWidget * form);

  SbPList * viewerbuttons;

  QWidget * prefwindow;
  SbString prefwindowtitle;

  QSlider * zoomslider;
  QLineEdit * zoomfield, * zoomrangefrom, * zoomrangeto;
  SbVec2f zoomrange;

  void setCameraZoom(const float zoom);
  float getCameraZoom(void);
  void setZoomSliderPosition(float zoom);
  void setZoomFieldString(float zoom);

  SoQtThumbWheel * seekdistancewheel;
  QLineEdit * seekdistancefield;

  QLabel * nearclippinglabel, * farclippinglabel;
  SoQtThumbWheel * nearclippingwheel, * farclippingwheel;
  QLineEdit * nearclippingedit, * farclippingedit;

  void setDrawStyleMenuActivation(SoQtViewer::DrawType type,
                                  SoQtViewer::DrawStyle val);

  void setEnabledClippingWidgets(SbBool flag);

private slots:
  // Thumbwheels.
  void leftWheelPressed(void);
  void leftWheelChanged(float value);
  void leftWheelReleased(void);
  void rightWheelPressed(void);
  void rightWheelChanged(float value);
  void rightWheelReleased(void);
  void bottomWheelPressed(void);
  void bottomWheelChanged(float value);
  void bottomWheelReleased(void);

  // Button row.
  void interactbuttonToggled(bool);
  void viewbuttonToggled(bool);
  void helpbuttonClicked();
  void homebuttonClicked();
  void sethomebuttonClicked();
  void viewallbuttonClicked();
  void seekbuttonClicked();

  // Menu items.
  void selectedViewing();
  void selectedDecoration();
  void selectedHeadlight();
  void copyviewSelected();
  void pasteviewSelected();
  void drawstyleActivated(int);
  void selectedPrefs();

  // Pref sheet.
  //  seek settings
  void seekAnimationTimeChanged(const char *);
  void seekAnimationTimeChanged(const QString &);
  void seekDetailToggled(int id);
  void seekDistanceWheelChanged(float);
  void seekDistanceEdit();
  void seekDistanceTypeToggle(int id);
  //  zoom settings
  void zoomSliderMoved(int val);
  void zoomFieldChanged();
  void zoomRangeChanged1();
  void zoomRangeChanged2();
  //  clipping settings
  void clippingToggled(bool flag);
  void nearclippingwheelMoved(float val);
  void farclippingwheelMoved(float val);
  void nearclipEditPressed();
  void farclipEditPressed();

  // Generic slots.
  void increaseInteractiveCount();
  void decreaseInteractiveCount();

}; // class SoQtFullViewer

// *************************************************************************

#endif // ! SOQT_FULLVIEWER_H
