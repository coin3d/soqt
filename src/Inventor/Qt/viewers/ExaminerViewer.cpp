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

#if SOQT_DEBUG
static const char rcsid[] =
  "$Id$";
#endif // SOQT_DEBUG

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
#include <moc_SoQtExaminerViewer.cpp>

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

/*!
  \class SoQtExaminerViewer SoQtExaminerViewer.h Inventor/Qt/viewers/SoQtExaminerViewer.h
  \brief The SoQtExaminerViewer class is a full-fledged model viewer
  with functionality for rotation, pan, zoom, etc.
  \ingroup soqtviewers

  TODO: more doc
  ...overview of what this class provides over parent class...
  ...keyboard combinations...mousebutton combinations...explain pan,
  rotate, zoom, dolly, seek...explain the fact that we're moving the
  camera, not the scene...
  ...viewer modes (examine vs interact) w/ explanation of what they are
  useful for...
  ...screenshot...
  ...example code...

  \sa SoQtWalkViewer, SoQtFlyViewer, SoQtPlaneViewer, SoQtCollisionViewer
*/

/*¡
  SoQtExaminerViewer is missing the class description documentation.
*/

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

SoQtExaminerViewer::SoQtExaminerViewer(
  QWidget * parent,
  const char * name,
  SbBool embed,
  SoQtFullViewer::BuildFlag flag,
  SoQtViewer::Type type)
: inherited(parent, name, embed, flag, type, FALSE)
{
  this->constructor(TRUE);
} // SoQtExaminerViewer()

// *************************************************************************

/*!
  Constructor. See parent class for explanation of arguments.
*/

SoQtExaminerViewer::SoQtExaminerViewer(
  QWidget * parent,
  const char * name,
  SbBool embed,
  SoQtFullViewer::BuildFlag flag,
  SoQtViewer::Type type,
  SbBool build)
: inherited(parent, name, embed, flag, type, FALSE)
{
  this->constructor(build);
} // SoQtExaminerViewer()

// *************************************************************************

/*!
  \internal

  This contains the real constructor code (the two constructors are only
  entry points for this method).
*/

void
SoQtExaminerViewer::constructor(SbBool build)
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

  this->spindetecttimer = NULL;
  this->setClassName("SoQtExaminerViewer");

  this->addVisibilityChangeCallback(SoQtExaminerViewer::visibilityCB, this);

  this->setPopupMenuString("Examiner Viewer");
  this->setPrefSheetString("Examiner Viewer Preference Sheet");
  this->setLeftWheelString("Rotx");
  this->setBottomWheelString("Roty");

  if (build) {
    QWidget * widget = this->buildWidget(this->getParentWidget());
    this->setBaseWidget(widget);
  }
} // constructor()

// *************************************************************************

/*!
  Destructor.
*/

SoQtExaminerViewer::~SoQtExaminerViewer()
{
  // Button pixmaps.
  delete this->orthopixmap;
  delete this->perspectivepixmap;

  // Variables used in the spin animation code.
  delete this->spindetecttimer;

  this->genericDestructor();
} // ~SoQtExaminerViewer()

// *************************************************************************

/*!
  This method overloaded from parent class to make sure the mouse
  pointer cursor is updated.
*/

void
SoQtExaminerViewer::setViewing(// virtual
  SbBool enable)
{
  this->setMode(enable ?
                         SoQtExaminerViewer::EXAMINE :
                         SoQtExaminerViewer::INTERACT);
  inherited::setViewing(enable);
} // setViewing()

// *************************************************************************

/*!
  This method overloaded from parent class to toggle the camera type
  selection button pixmap and string of the zoom/dolly thumbwheel.
*/

void
SoQtExaminerViewer::setCamera(// virtual
  SoCamera * newCamera)
{
  if (newCamera) {
    SoType camtype = newCamera->getTypeId();
    SbBool orthotype =
      camtype.isDerivedFrom(SoOrthographicCamera::getClassTypeId());

    this->setRightWheelString(orthotype ? "Zoom" : "Dolly");
    if (this->cameratogglebutton) {
      this->cameratogglebutton->setPixmap(orthotype ?
                                          * (this->orthopixmap) :
                                          * (this->perspectivepixmap));
    }
  }

  inherited::setCamera(newCamera);
} // setCamera()

// *************************************************************************

/*!
  Overloaded to provide the examiner viewer functionality on the left
  thumbwheel (x axis rotation).
*/

void
SoQtExaminerViewer::leftWheelMotion(
  float value)
{
  if (this->isAnimating())
    this->stopAnimating();

  inherited::leftWheelMotion(
    this->rotXWheelMotion(value, this->getLeftWheelValue()));
} // leftWheelMotion()

/*!
  Overloaded to provide the examiner viewer functionality on the bottom
  thumbwheel (y axis rotation).
*/

void
SoQtExaminerViewer::bottomWheelMotion(
  float value)
{
  if (this->isAnimating())
    this->stopAnimating();

  inherited::bottomWheelMotion(
    this->rotYWheelMotion(value, this->getBottomWheelValue()));
} // bottomWheelMotion()

/*!
  Overloaded to provide the examiner viewer functionality on the left
  thumbwheel (dolly/zoom).
*/

void
SoQtExaminerViewer::rightWheelMotion(
  float value)
{
  this->zoom(this->getRightWheelValue() - value);
  inherited::rightWheelMotion(value);
} // rightWheelMotion()

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
                   this, SLOT(spinAnimationToggled(bool)));

  // Layout row 1.
  toplayout->addWidget(c1, c1->height());
  expandSize(totalsize, c1->size(), LayoutVertical);

  // Do the single widget on the second row (a checkbox).

  QCheckBox * c2 = new QCheckBox("Show point of rotation axes", w);
  c2->adjustSize();
  c2->setChecked(this->isFeedbackVisible());
  QObject::connect(c2, SIGNAL(toggled(bool)),
                   this, SLOT(feedbackVisibilityToggle(bool)));

  // Layout row 2.
  toplayout->addWidget(c2, c2->height());
  expandSize(totalsize, c2->size(), LayoutVertical);


  // Do the four widgets on the third row (label, thumbwheel,
  // lineedit, label).

  QSize tmpsize = QSize(0, 0);

  this->feedbacklabel1 = new QLabel("axes size", w);
  this->feedbacklabel1->adjustSize();
  expandSize(tmpsize, this->feedbacklabel1->size(), LayoutHorizontal);

  this->feedbackwheel = new SoQtThumbWheel(SoQtThumbWheel::Horizontal, w);
  this->feedbackwheel->setRangeBoundaryHandling(SoQtThumbWheel::ACCUMULATE);
  QObject::connect(this->feedbackwheel, SIGNAL(wheelMoved(float)),
                   this, SLOT(feedbackSizeChanged(float)));
  this->feedbackwheel->setValue(float(this->getFeedbackSize())/10.0f);
  this->feedbackwheel->adjustSize();
  expandSize(tmpsize, this->feedbackwheel->size(), LayoutHorizontal);

  this->feedbackedit = new QLineEdit(w);
  QObject::connect(this->feedbackedit, SIGNAL(returnPressed()),
                   this, SLOT(feedbackEditPressed()));
  QString s;
  s.setNum(this->getFeedbackSize());
  this->feedbackedit->setText(s);
  this->feedbackedit->adjustSize();
  expandSize(tmpsize, this->feedbackedit->size(), LayoutHorizontal);

  this->feedbacklabel2 = new QLabel("size", w);
  this->feedbacklabel2->adjustSize();
  expandSize(tmpsize, this->feedbacklabel2->size(), LayoutHorizontal);

  // Layout row 3.
  QHBoxLayout * layout = new QHBoxLayout;
  toplayout->addLayout(layout, tmpsize.height());
  layout->addWidget(this->feedbacklabel1, this->feedbacklabel1->width());
  layout->addWidget(this->feedbackwheel, this->feedbackwheel->width());
  layout->addWidget(this->feedbackedit, this->feedbackedit->width());
  layout->addWidget(this->feedbacklabel2, this->feedbacklabel2->width());
  expandSize(totalsize, tmpsize, LayoutVertical);

  w->resize(totalsize);
  toplayout->activate();

  this->setEnableFeedbackControls(this->isFeedbackVisible());

  return w;
} // makeSubPreferences()

// *************************************************************************

/*!
  Overloaded from parent class so we can append the camera type switch
  button in the rightside button column.
*/

void
SoQtExaminerViewer::createViewerButtons(QWidget * parent, SbPList * buttonlist)
{
  inherited::createViewerButtons(parent, buttonlist);

  this->cameratogglebutton = new QPushButton(parent);
  this->cameratogglebutton->setFocusPolicy(QWidget::NoFocus);
  assert(this->perspectivepixmap);
  assert(this->orthopixmap);

  QPixmap * p = NULL;
  SoType t = this->getCameraType();
  if (t.isDerivedFrom(SoOrthographicCamera::getClassTypeId()))
    p = this->orthopixmap;
  else if (t.isDerivedFrom(SoPerspectiveCamera::getClassTypeId()))
    p = this->perspectivepixmap;
  else assert(0 && "unsupported cameratype");

  this->cameratogglebutton->setPixmap(*p);
  this->cameratogglebutton->adjustSize();

  QObject::connect(this->cameratogglebutton, SIGNAL(clicked()),
                   this, SLOT(cameratoggleClicked()));

  buttonlist->append(this->cameratogglebutton);
} // createViewerButtons()

// *************************************************************************

/*!
  Overloaded to provide name of class.
*/

const char *
SoQtExaminerViewer::getDefaultWidgetName(// virtual
  void) const
{
  static const char defaultWidgetName[] = "SoQtExaminerViewer";
  return defaultWidgetName;
} // getDefaultWidgetName()

// *************************************************************************

/*!
  Overloaded to provide ``title'' of class.
*/

const char *
SoQtExaminerViewer::getDefaultTitle(void) const
{
  static const char defaultTitle[] = "Examiner Viewer";
  return defaultTitle;
} // getDefaultTitle()

// *************************************************************************

/*!
  Overloaded to provide ``title'' of class.
*/

const char *
SoQtExaminerViewer::getDefaultIconTitle(void) const
{
  static const char defaultIconTitle[] = "Examiner Viewer";
  return defaultIconTitle;
} // getDefaultIconTitle()

// *************************************************************************

/*!
  Pops up the examiner viewer help card.
*/

void
SoQtExaminerViewer::openViewerHelpCard(void)
{
  this->openHelpCard("SoQtExaminerViewer.help");
} // openViewerHelpCard()

// *************************************************************************

/*!
  Overload this method to make sure any animations are stopped before
  we go into seek mode.
*/

void
SoQtExaminerViewer::setSeekMode(SbBool on)
{
  // Note: this method is almost identical to the setSeekMode() in the
  // SoQtFlyViewer, so migrate any changes.

#if SOQT_DEBUG
  if (on == this->isSeekMode()) {
    SoDebugError::postWarning("SoQtExaminerViewer::setSeekMode",
                              "seek mode already %sset", on ? "" : "un");
    return;
  }
#endif // SOQT_DEBUG

  if (this->isAnimating()) this->stopAnimating();
  inherited::setSeekMode(on);
  this->setMode(on ?
                        SoQtExaminerViewer::WAITING_FOR_SEEK :
                        SoQtExaminerViewer::EXAMINE);
} // setSeekMode()

// *************************************************************************

/*!
  Overload this method to be able to draw the axis cross if selected
  in the preferences sheet.
*/

void
SoQtExaminerViewer::actualRedraw(void)
{
  this->actualGenericRedraw();
  inherited::actualRedraw();
  if (this->isFeedbackVisible())
    this->drawAxisCross();

  // Immediately reschedule to get continous spin animation.
  if (this->isAnimating())
    this->scheduleRedraw();
} // actualRedraw()

// *************************************************************************

/*!
  \internal

  Set cursor graphics according to mode.
*/

void
SoQtExaminerViewer::setCursorRepresentation(int mode)
{
  // FIXME: with the new So@Gui@Cursor class, this has actually become
  // a possibly generic method for all So* toolkits. Move to common
  // code. 20011125 mortene.

  if (!this->isCursorEnabled()) {
    this->setComponentCursor(SoQtCursor::getBlankCursor());
    return;
  }

  switch (mode) {
  case SoQtExaminerViewer::INTERACT:
    this->setComponentCursor(SoQtCursor(SoQtCursor::DEFAULT));
    break;

  case SoQtExaminerViewer::EXAMINE:
  case SoQtExaminerViewer::DRAGGING:
    this->setComponentCursor(SoQtCursor::getRotateCursor());
    break;

  case SoQtExaminerViewer::ZOOMING:
    this->setComponentCursor(SoQtCursor::getZoomCursor());
    break;

  case SoQtExaminerViewer::WAITING_FOR_SEEK:
    this->setComponentCursor(SoQtCursor(SoQtCursor::CROSSHAIR));
    break;

  case SoQtExaminerViewer::WAITING_FOR_PAN:
  case SoQtExaminerViewer::PANNING:
    this->setComponentCursor(SoQtCursor::getPanCursor());
    break;

  default: assert(0); break;
  }
} // setCursorRepresentation()

// *************************************************************************

/*!
  \internal
*/

void
SoQtExaminerViewer::setEnableFeedbackControls(const SbBool flag)
{
  this->feedbacklabel1->setEnabled(flag);
  this->feedbacklabel2->setEnabled(flag);
  this->feedbackwheel->setEnabled(flag);
  this->feedbackedit->setEnabled(flag);
} // setEnabledFeedbackControls()

// *************************************************************************

/*!
  \internal

  This gets called whenever the visibility status of the viewer widget
  changes (for instance on iconization/deiconization).
*/

void
SoQtExaminerViewer::visibilityCallback(SbBool visible)
{
  if (this->isAnimating()) {
//    if (visible)
//      this->spintimertrigger->schedule();
//    else
//      this->spintimertrigger->unschedule();
  }
}

void
SoQtExaminerViewer::visibilityCB(void * data, SbBool visible)
{
  ((SoQtExaminerViewer *) data)->visibilityCallback(visible);
} // visibilityCB()

// *************************************************************************

/*!
  \internal

  Pref sheet slot.
*/

void
SoQtExaminerViewer::spinAnimationToggled(bool flag)
{
  this->setAnimationEnabled(flag ? TRUE : FALSE);
} // spinAnimationToggled()

// *************************************************************************

/*!
  \internal
  Pref sheet slot.
*/

void
SoQtExaminerViewer::feedbackVisibilityToggle(bool flag)
{
  this->setFeedbackVisibility(flag ? TRUE : FALSE);
  this->setEnableFeedbackControls(flag);
} // feedbackVisibilityToggle()

// *************************************************************************

/*!
  \internal

  Pref sheet slot.
*/

void
SoQtExaminerViewer::feedbackEditPressed()
{
  int val;
  if ((sscanf(this->feedbackedit->text(), "%d", &val) == 1) && (val > 0.0f)) {
    this->feedbackwheel->setValue(float(val)/10.0f);
    this->setFeedbackSize(val);
  }
  else {
    QString s;
    s.setNum(this->getFeedbackSize());
    this->feedbackedit->setText(s);
  }
} // feedbackEditPressed()

// *************************************************************************

/*!
  \internal
  Pref sheet slot.
*/

void
SoQtExaminerViewer::feedbackWheelPressed()
{
  this->interactiveCountInc();
} // feedbackWheelPressed()

// *************************************************************************

/*!
  \internal
  Pref sheet slot.
*/

void
SoQtExaminerViewer::feedbackWheelReleased()
{
  this->interactiveCountDec();
} // feedbackWheelReleased()

// *************************************************************************

/*!
  \internal
  Pref sheet slot.
*/

void
SoQtExaminerViewer::feedbackSizeChanged(float val)
{
  if (val < 0.1f) {
    val = 0.1f;
    this->feedbackwheel->setValue(val);
  }

  this->setFeedbackSize(int(val * 10));

  QString s;
  s.setNum(this->getFeedbackSize());
  this->feedbackedit->setText(s);
} // feedbackSizeChanged()

// *************************************************************************

/*!
  \internal
  Pref sheet slot.
*/

void
SoQtExaminerViewer::cameratoggleClicked()
{
  if (this->getCamera()) this->toggleCameraType();
} // cameratoggleClicked()

// *************************************************************************

/*!
  FIXME: write doc
*/

void
SoQtExaminerViewer::setAnimationEnabled(
  const SbBool enable)
{
  this->setGenericAnimationEnabled(enable);
  // FIXME: set spinanimtoggle state
} // setAnimationEnabled()


/*!
  FIXME: write doc
*/

void
SoQtExaminerViewer::setFeedbackSize(
   const int size)
{
  this->setGenericFeedbackSize(size);
} // setFeedbackSize()

// *************************************************************************

// doc in super
void
SoQtExaminerViewer::afterRealizeHook(// protected virtual
  void)
{
  this->setCursorRepresentation(this->currentmode);
  inherited::afterRealizeHook();
} // afterRealizeHook()

// *************************************************************************

#if SOQT_DEBUG
static const char * getSoQtExaminerViewerRCSID(void) { return rcsid; }
#endif
