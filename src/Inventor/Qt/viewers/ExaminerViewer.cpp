/**************************************************************************\
 *
 *  This file is part of the Coin GUI toolkit libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation.  See the
 *  file LICENSE.LGPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you want to use this library with software that is incompatible
 *  licensewise with the LGPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

// Class documentation in common/viewers/SoGuiExaminerViewer.cpp.in.

// *************************************************************************

#include <qpushbutton.h>
#include <qkeycode.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qpixmap.h>
#include <qbitmap.h>
#include <qtimer.h>
#include <qcursor.h>
#include <qmetaobject.h>
#include <moc_SoQtExaminerViewerP.cpp>
#include <SoQtExaminerViewerP.h>

#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/projectors/SbSphereSheetProjector.h>
#if SOQT_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // SOQT_DEBUG

#include <soqtdefs.h>
#include <Inventor/Qt/widgets/SoQtThumbWheel.h>
#include <Inventor/Qt/SoQtCursor.h>

#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>

// Icon graphic for the camera button.
#include <Inventor/Qt/common/pixmaps/ortho.xpm>
#include <Inventor/Qt/common/pixmaps/perspective.xpm>

// *************************************************************************

// SoQtExaminerViewerP "private implementation" class.

SoQtExaminerViewerP::SoQtExaminerViewerP(SoQtExaminerViewer * publ)
  : SoGuiExaminerViewerP(publ)
{
}

SoQtExaminerViewerP::~SoQtExaminerViewerP()
{
  // Button pixmaps.
  delete this->orthopixmap;
  delete this->perspectivepixmap;

  this->genericDestructor();
}

// *************************************************************************

SOQT_OBJECT_SOURCE(SoQtExaminerViewer);

// *************************************************************************

///////// FIXME start //////////////////////////////////////////////////
// Do something clever about this Qt layout assistant code.. (the code
// for expandSize() is inside SoQtFullViewer.cpp). 990222 mortene.
enum LayoutOrientation { LayoutVertical, LayoutHorizontal };
extern void expandSize(QSize & result, const QSize & addend,
                       LayoutOrientation o);
///////// FIXME end ////////////////////////////////////////////////////

// *************************************************************************

/*!
  Constructor.  See parent class for explanation of arguments.
  Calling this constructor will make sure the examiner viewer widget
  will be built immediately.
*/

SoQtExaminerViewer::SoQtExaminerViewer(QWidget * parent,
                                       const char * name,
                                       SbBool embed,
                                       SoQtFullViewer::BuildFlag flag,
                                       SoQtViewer::Type type)
  : inherited(parent, name, embed, flag, type, FALSE)
{
  PRIVATE(this) = new SoQtExaminerViewerP(this);
  PRIVATE(this)->constructor(TRUE);
}

// *************************************************************************

/*!
  Constructor. See parent class for explanation of arguments.
*/

SoQtExaminerViewer::SoQtExaminerViewer(QWidget * parent,
                                       const char * name,
                                       SbBool embed,
                                       SoQtFullViewer::BuildFlag flag,
                                       SoQtViewer::Type type,
                                       SbBool build)
  : inherited(parent, name, embed, flag, type, FALSE)
{
  PRIVATE(this) = new SoQtExaminerViewerP(this);
  PRIVATE(this)->constructor(build);
}

// *************************************************************************

/*!
  \internal

  This contains the real constructor code (the two constructors are only
  entry points for this method).
*/

void
SoQtExaminerViewerP::constructor(SbBool build)
{
  this->genericConstructor();

  this->feedbacklabel1 = NULL;
  this->feedbacklabel2 = NULL;
  this->feedbackwheel = NULL;
  this->feedbackedit = NULL;
  this->cameratogglebutton = NULL;

  this->orthopixmap = new QPixmap((const char **)ortho_xpm);
  this->perspectivepixmap = new QPixmap((const char **)perspective_xpm);
  assert(this->orthopixmap->size() == this->perspectivepixmap->size());

  PUBLIC(this)->setClassName("SoQtExaminerViewer");

  PUBLIC(this)->setPopupMenuString("Examiner Viewer");
  PUBLIC(this)->setPrefSheetString("Examiner Viewer Preference Sheet");
  PUBLIC(this)->setLeftWheelString("Rotx");
  PUBLIC(this)->setBottomWheelString("Roty");

  if (build) {
    QWidget * widget = PUBLIC(this)->buildWidget(PUBLIC(this)->getParentWidget());
    PUBLIC(this)->setBaseWidget(widget);
  }
}

// *************************************************************************

/*!
  Destructor.
*/

SoQtExaminerViewer::~SoQtExaminerViewer()
{
  delete PRIVATE(this);
}

// *************************************************************************

// Documented in superclass.
void
SoQtExaminerViewer::setCamera(SoCamera * newCamera)
{
  // This method overridden from parent class to toggle the camera
  // type selection button pixmap and string of the zoom/dolly
  // thumbwheel.

  if (newCamera) {
    SoType camtype = newCamera->getTypeId();
    SbBool orthotype =
      camtype.isDerivedFrom(SoOrthographicCamera::getClassTypeId());

    this->setRightWheelString(orthotype ? "Zoom" : "Dolly");
    if (PRIVATE(this)->cameratogglebutton) {
      PRIVATE(this)->cameratogglebutton->setPixmap(orthotype ?
                                                   * (PRIVATE(this)->orthopixmap) :
                                                   * (PRIVATE(this)->perspectivepixmap));
    }
  }

  inherited::setCamera(newCamera);
}

// *************************************************************************

/*!
  Overloaded to add preferences settings for examiner viewer
  specific stuff (enable/disable possible spin animation,
  enable/disable/configure axis cross graphics).
*/

QWidget *
SoQtExaminerViewer::makeSubPreferences(QWidget * parent)
{
  QWidget * w = new QWidget(parent);
//  w->setBackgroundColor(QColor(250, 0, 0));

  // Initialize objects keeping track of geometry data.

  QSize totalsize(0, 0);
  QVBoxLayout * toplayout = new QVBoxLayout(w);

  // First, do the single widget on the uppermost row (a checkbox).

  QCheckBox * c1 = new QCheckBox("Enable spin animation", w);
  c1->adjustSize();
  c1->setChecked(this->isAnimationEnabled());
  QObject::connect(c1, SIGNAL(toggled(bool)),
                   PRIVATE(this), SLOT(spinAnimationToggled(bool)));

  // Layout row 1.
  toplayout->addWidget(c1, c1->height());
  expandSize(totalsize, c1->size(), LayoutVertical);

  // Do the single widget on the second row (a checkbox).

  QCheckBox * c2 = new QCheckBox("Show point of rotation axes", w);
  c2->adjustSize();
  c2->setChecked(this->isFeedbackVisible());
  QObject::connect(c2, SIGNAL(toggled(bool)),
                   PRIVATE(this), SLOT(feedbackVisibilityToggle(bool)));

  // Layout row 2.
  toplayout->addWidget(c2, c2->height());
  expandSize(totalsize, c2->size(), LayoutVertical);


  // Do the four widgets on the third row (label, thumbwheel,
  // lineedit, label).

  QSize tmpsize = QSize(0, 0);

  PRIVATE(this)->feedbacklabel1 = new QLabel("axes size", w);
  PRIVATE(this)->feedbacklabel1->adjustSize();
  expandSize(tmpsize, PRIVATE(this)->feedbacklabel1->size(), LayoutHorizontal);

  PRIVATE(this)->feedbackwheel = new SoQtThumbWheel(SoQtThumbWheel::Horizontal, w);
  PRIVATE(this)->feedbackwheel->setRangeBoundaryHandling(SoQtThumbWheel::ACCUMULATE);
  QObject::connect(PRIVATE(this)->feedbackwheel, SIGNAL(wheelMoved(float)),
                   PRIVATE(this), SLOT(feedbackSizeChanged(float)));
  PRIVATE(this)->feedbackwheel->setValue(float(this->getFeedbackSize())/10.0f);
  PRIVATE(this)->feedbackwheel->adjustSize();
  expandSize(tmpsize, PRIVATE(this)->feedbackwheel->size(), LayoutHorizontal);

  PRIVATE(this)->feedbackedit = new QLineEdit(w);
  QObject::connect(PRIVATE(this)->feedbackedit, SIGNAL(returnPressed()),
                   PRIVATE(this), SLOT(feedbackEditPressed()));
  QString s;
  s.setNum(this->getFeedbackSize());
  PRIVATE(this)->feedbackedit->setText(s);
  PRIVATE(this)->feedbackedit->adjustSize();
  expandSize(tmpsize, PRIVATE(this)->feedbackedit->size(), LayoutHorizontal);

  PRIVATE(this)->feedbacklabel2 = new QLabel("size", w);
  PRIVATE(this)->feedbacklabel2->adjustSize();
  expandSize(tmpsize, PRIVATE(this)->feedbacklabel2->size(), LayoutHorizontal);

  // Layout row 3.
  QHBoxLayout * layout = new QHBoxLayout;
  toplayout->addLayout(layout, tmpsize.height());
  layout->addWidget(PRIVATE(this)->feedbacklabel1, PRIVATE(this)->feedbacklabel1->width());
  layout->addWidget(PRIVATE(this)->feedbackwheel, PRIVATE(this)->feedbackwheel->width());
  layout->addWidget(PRIVATE(this)->feedbackedit, PRIVATE(this)->feedbackedit->width());
  layout->addWidget(PRIVATE(this)->feedbacklabel2, PRIVATE(this)->feedbacklabel2->width());
  expandSize(totalsize, tmpsize, LayoutVertical);

  w->resize(totalsize);
  toplayout->activate();

  PRIVATE(this)->setEnableFeedbackControls(this->isFeedbackVisible());

  return w;
}

// *************************************************************************

// Documented in superclass. Overridden so we can append the camera
// type switch button in the rightside button column.
void
SoQtExaminerViewer::createViewerButtons(QWidget * parent, SbPList * buttonlist)
{
  inherited::createViewerButtons(parent, buttonlist);

  PRIVATE(this)->cameratogglebutton = new QPushButton(parent);
  PRIVATE(this)->cameratogglebutton->setFocusPolicy(QWidget::NoFocus);
  assert(PRIVATE(this)->perspectivepixmap);
  assert(PRIVATE(this)->orthopixmap);

  QPixmap * p = NULL;
  SoType t = this->getCameraType();
  if (t.isDerivedFrom(SoOrthographicCamera::getClassTypeId()))
    p = PRIVATE(this)->orthopixmap;
  else if (t.isDerivedFrom(SoPerspectiveCamera::getClassTypeId()))
    p = PRIVATE(this)->perspectivepixmap;
  else assert(0 && "unsupported cameratype");

  PRIVATE(this)->cameratogglebutton->setPixmap(*p);
  PRIVATE(this)->cameratogglebutton->adjustSize();

  QObject::connect(PRIVATE(this)->cameratogglebutton, SIGNAL(clicked()),
                   PRIVATE(this), SLOT(cameratoggleClicked()));

  buttonlist->append(PRIVATE(this)->cameratogglebutton);
}

// *************************************************************************

/*!
  \internal
*/

void
SoQtExaminerViewerP::setEnableFeedbackControls(const SbBool flag)
{
  this->feedbacklabel1->setEnabled(flag);
  this->feedbacklabel2->setEnabled(flag);
  this->feedbackwheel->setEnabled(flag);
  this->feedbackedit->setEnabled(flag);
}

// *************************************************************************

//  Pref sheet slot.
void
SoQtExaminerViewerP::spinAnimationToggled(bool flag)
{
  PUBLIC(this)->setAnimationEnabled(flag ? TRUE : FALSE);
}

// *************************************************************************

// Pref sheet slot.
void
SoQtExaminerViewerP::feedbackVisibilityToggle(bool flag)
{
  PUBLIC(this)->setFeedbackVisibility(flag ? TRUE : FALSE);
  this->setEnableFeedbackControls(flag);
}

// *************************************************************************

//  Pref sheet slot.
void
SoQtExaminerViewerP::feedbackEditPressed()
{
  int val;
  if ((sscanf(this->feedbackedit->text(), "%d", &val) == 1) && (val > 0.0f)) {
    this->feedbackwheel->setValue(float(val)/10.0f);
    PUBLIC(this)->setFeedbackSize(val);
  }
  else {
    QString s;
    s.setNum(PUBLIC(this)->getFeedbackSize());
    this->feedbackedit->setText(s);
  }
}

// *************************************************************************

// Pref sheet slot.
void
SoQtExaminerViewerP::feedbackWheelPressed()
{
  PUBLIC(this)->interactiveCountInc();
}

// *************************************************************************

// Pref sheet slot.
void
SoQtExaminerViewerP::feedbackWheelReleased()
{
  PUBLIC(this)->interactiveCountDec();
}

// *************************************************************************

// Pref sheet slot.
void
SoQtExaminerViewerP::feedbackSizeChanged(float val)
{
  if (val < 0.1f) {
    val = 0.1f;
    this->feedbackwheel->setValue(val);
  }

  PUBLIC(this)->setFeedbackSize(int(val * 10));

  QString s;
  s.setNum(PUBLIC(this)->getFeedbackSize());
  this->feedbackedit->setText(s);
}

// *************************************************************************

// Pref sheet slot.
void
SoQtExaminerViewerP::cameratoggleClicked()
{
  if (PUBLIC(this)->getCamera()) PUBLIC(this)->toggleCameraType();
}

// *************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtExaminerViewer::setAnimationEnabled(const SbBool enable)
{
  // FIXME: update pref-sheet widget with the value. 20020603 mortene.
  PRIVATE(this)->setGenericAnimationEnabled(enable);
}


/*!
  FIXME: write doc
*/

void
SoQtExaminerViewer::setFeedbackSize(const int size)
{
  // FIXME: update pref-sheet widget with the value. 20020603 mortene.
  PRIVATE(this)->setGenericFeedbackSize(size);
}

// *************************************************************************
