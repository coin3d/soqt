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
class SoQtExaminerViewer;

// *************************************************************************

class SOQT_DLL_EXPORT SoQtExaminerViewer : public SoQtFullViewer {
  typedef SoQtFullViewer inherited;
  friend class SoAnyExaminerViewer;

  Q_OBJECT

public:
  SoQtExaminerViewer(
    QWidget * parent = NULL,
    const char * name = NULL,
    SbBool embed = TRUE,
    SoQtFullViewer::BuildFlag flag = BUILD_ALL,
    SoQtViewer::Type type = BROWSER );
  ~SoQtExaminerViewer(void);

  virtual void setViewing( SbBool enable );
  virtual void setCamera( SoCamera * const camera );
  virtual void setCursorEnabled( const SbBool enable );

protected:
  SoQtExaminerViewer(
    QWidget * parent,
    const char * name,
    SbBool embed,
    SoQtFullViewer::BuildFlag flag,
    SoQtViewer::Type type,
    SbBool build );

  virtual void leftWheelMotion( float val );
  virtual void bottomWheelMotion( float val );
  virtual void rightWheelMotion( float val );

  virtual QWidget * makeSubPreferences( QWidget * parent );
  virtual void createViewerButtons( QWidget * parent, SbPList * buttonlist );

  virtual const char * getDefaultWidgetName(void) const;
  virtual const char * getDefaultTitle(void) const;
  virtual const char * getDefaultIconTitle(void) const;

  virtual void openViewerHelpCard(void);

  virtual void processEvent( QEvent * anyevent );
  virtual void setSeekMode( SbBool enable );
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

  void setMode(const ViewerMode mode);
  void setModeFromState(const unsigned int state);

  QPixmap * orthopixmap, * perspectivepixmap;

  void constructor( SbBool buildNow );
  void visibilityCallback( SbBool visible );
  static void visibilityCB(void * data, SbBool visible);

  QTimer * spindetecttimer;

  void setCursorRepresentation(const ViewerMode mode);
  QCursor * pancursor, * rotatecursor;
  QCursor * defaultcursor, * zoomcursor;

  QPushButton * cameratogglebutton;
  QLabel * feedbacklabel1, * feedbacklabel2;
  SoQtThumbWheel * feedbackwheel;
  QLineEdit * feedbackedit;
  void setEnableFeedbackControls(const SbBool flag);

private slots:

// preferences window:
  void spinAnimationToggled( bool );
  void feedbackVisibilityToggle( bool );
  void feedbackEditPressed(void);
  void feedbackWheelPressed(void);
  void feedbackSizeChanged( float val );
  void feedbackWheelReleased(void);

// viewer buttons row:
  void cameratoggleClicked(void);

private:
  SoAnyExaminerViewer * const common;

}; // class SoQtExaminerViewer

// *************************************************************************

#endif // ! SOQT_EXAMINERVIEWER_H
