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

#ifndef SOQT_FULLVIEWER_H
#define SOQT_FULLVIEWER_H

#include <Inventor/Qt/viewers/SoQtViewer.h>

class QPushButton;
class QLayout;
class QLabel;
class QLineEdit;
class QSlider;

class SoAnyPopupMenu;
class SoQtThumbWheel;
class SoAnyFullViewer;

// *************************************************************************

class SOQT_DLL_API SoQtFullViewer : public SoQtViewer {
  SOQT_OBJECT_ABSTRACT_HEADER(SoQtFullViewer, SoQtViewer);
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
  virtual void setCamera(SoCamera * cam);
  virtual void hide(void);

protected:
  SoQtFullViewer(
    QWidget * parent,
    const char * name,
    SbBool embed,
    BuildFlag flag,
    Type type,
    SbBool build );
  ~SoQtFullViewer(void);

  virtual bool eventFilter(QObject * obj, QEvent * e);
  virtual void sizeChanged( const SbVec2s size );

  virtual void afterRealizeHook(void);

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
  void openPopupMenu( const SbVec2s position );

  virtual QWidget * makeSubPreferences(QWidget * parent);
  void setPrefSheetString(const char * title);

  virtual void leftWheelStart(void);
  virtual void leftWheelMotion(float);
  virtual void leftWheelFinish(void);
  float getLeftWheelValue(void) const;
  void setLeftWheelValue( const float value );

  virtual void bottomWheelStart(void);
  virtual void bottomWheelMotion(float);
  virtual void bottomWheelFinish(void);
  float getBottomWheelValue(void) const;
  void setBottomWheelValue( const float value );

  virtual void rightWheelStart(void);
  virtual void rightWheelMotion(float);
  virtual void rightWheelFinish(void);
  float getRightWheelValue(void) const;
  void setRightWheelValue( const float value );

  void setLeftWheelString( const char * const string );
  void setBottomWheelString( const char * const string );
  void setRightWheelString( const char * const string );

  virtual SbBool processSoEvent( const SoEvent * const event );

  virtual void openViewerHelpCard(void);

protected:
  QWidget * leftDecoration;
  QWidget * rightDecoration;
  QWidget * bottomDecoration;

  QWidget * leftWheel;
  QWidget * leftWheelLabel;
  char * leftWheelStr;
  float leftWheelVal;

  QWidget * rightWheel;
  QWidget * rightWheelLabel;
  char * rightWheelStr;
  float rightWheelVal;

  QWidget * bottomWheel;
  QWidget * bottomWheelLabel;
  char * bottomWheelStr;
  float bottomWheelVal;

  SoAnyPopupMenu * prefmenu;


private:
  QWidget * makePreferencesWindow(void);
  QWidget * makeSeekPreferences(QWidget * parent);
  QWidget * makeSeekDistancePreferences(QWidget * parent);
  QWidget * makeZoomPreferences(QWidget * parent);
  QWidget * makeAutoclipPreferences(QWidget * parent);

  void showDecorationWidgets(SbBool onOff);

  void layoutAppButtons(QWidget * form);

  void setCameraZoom(const float zoom);
  float getCameraZoom(void);
  void setZoomSliderPosition(float zoom);
  void setZoomFieldString(float zoom);

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
  void interactbuttonClicked();
  void viewbuttonClicked();
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

private:
  SoAnyFullViewer * common;
  class SoQtFullViewerP * pimpl;

}; // class SoQtFullViewer

// *************************************************************************

#endif // ! SOQT_FULLVIEWER_H
