/**************************************************************************\
 *
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
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

static const char rcsid[] =
  "$Id$";

/*!
  \class SoQtExaminerViewer SoQtExaminerViewer.h Inventor/Qt/viewers/SoQtExaminerViewer.h
  \brief The SoQtExaminerViewer class is a full-fledged model viewer
  with functionality for rotation, pan, zoom, etc.
  \ingroup qtviewers

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

#include <assert.h>

#include <qpushbutton.h>
#include <qkeycode.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qpixmap.h>
#include <qbitmap.h>
#include <qtimer.h>
// FIXME: get rid of this before 1.0 release (convert everything to Qt
// version 2.x API). 19990630 mortene.
#if QT_VERSION >= 200
#include <q1xcompatibility.h>
#endif // Qt v2.x

#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/projectors/SbSphereSheetProjector.h>
#if SOQT_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // SOQT_DEBUG

#include <Inventor/Qt/widgets/QtThumbwheel.h>
#include <Inventor/Qt/SoQtCursors.h>

#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>

// Icon graphic for the camera button.
#include "icons/ortho.xpm"
#include "icons/perspective.xpm"

// Bitmap representations of an "X", a "Y" and a "Z" for the axis cross.
static GLubyte xbmp[] = { 0x11,0x11,0x0a,0x04,0x0a,0x11,0x11 };
static GLubyte ybmp[] = { 0x04,0x04,0x04,0x04,0x0a,0x11,0x11 };
static GLubyte zbmp[] = { 0x1f,0x10,0x08,0x04,0x02,0x01,0x1f };

// Inlined convenience methods.
template <class Type>
inline Type exvMin( const Type A, const Type B ) { return (A < B) ? A : B; }
template <class Type>
inline void exvSwap( Type & A, Type & B ) { Type T; T = A; A = B; B = T; }


///////// FIXME start //////////////////////////////////////////////////
// Do something clever about this Qt layout assistant code.. (the code
// for expandSize() is inside SoQtFullViewer.cpp). 990222 mortene.
enum LayoutOrientation { LayoutVertical, LayoutHorizontal };
extern void expandSize(QSize & result, const QSize & addend,
                       LayoutOrientation o);
///////// FIXME end ////////////////////////////////////////////////////


/*!
  Constructor. See parent class for explanation of arguments.
  Calling this constructor will make sure the examiner viewer widget
  will be built immediately.
 */
SoQtExaminerViewer::SoQtExaminerViewer(QWidget * parent, const char * name,
                                       SbBool buildInsideParent,
                                       SoQtFullViewer::BuildFlag b,
                                       SoQtViewer::Type t)
  : inherited(parent, name, buildInsideParent, b, t, FALSE)
{
  this->constructor(TRUE);
}

/*!
  Constructor. See parent class for explanation of arguments.
 */
SoQtExaminerViewer::SoQtExaminerViewer(QWidget * parent, const char * name,
                                       SbBool buildInsideParent,
                                       SoQtFullViewer::BuildFlag b,
                                       SoQtViewer::Type t,
                                       SbBool buildNow)
  : inherited(parent, name, buildInsideParent, b, t, FALSE)
{
  this->constructor(buildNow);
}

/*!
  \internal

  This contains the real constructor code (the two constructors are only
  entry points for this method).
 */
void
SoQtExaminerViewer::constructor(SbBool buildNow)
{
  // FIXME: use a smaller sphere than the default one to have a larger
  // area close to the borders that gives us "z-axis rotation"?
  // 990425 mortene.
  this->projector = new SbSphereSheetProjector;
  SbViewVolume vv;
  vv.ortho(-1, 1, -1, 1, -1, 1);
  this->projector->setViewVolume(vv);

  this->currentmode = EXAMINE;
  this->defaultcursor = NULL;
  this->rotatecursor = NULL;
  this->pancursor = NULL;
  this->zoomcursor = NULL;

  this->orthopixmap = new QPixmap((const char **)ortho_xpm);
  this->perspectivepixmap = new QPixmap((const char **)perspective_xpm);
  assert(this->orthopixmap->size() == this->perspectivepixmap->size());

  this->animatingallowed = TRUE;
  this->spinanimating = FALSE;
  this->spindetecttimer = NULL;
  this->spinsamplecounter = 0;
  this->spinincrement = SbRotation::identity();
  this->timertrigger =
    new SoTimerSensor(SoQtExaminerViewer::timertriggeredCB, this);
  // FIXME: should set equal to vertical refresh rate? 990425 mortene.
  this->timertrigger->setInterval(1.0/30.0);

  this->setClassName("SoQtExaminerViewer");

  this->addVisibilityChangeCallback(SoQtExaminerViewer::visibilityCB, this);

  this->setPopupMenuString("Examiner Viewer");
  this->setPrefSheetString("Examiner Viewer Preference Sheet");
  this->setLeftWheelString("Rotx");
  this->setBottomWheelString("Roty");

  this->axiscrossOn = FALSE;
  this->axiscrossSize = 25;

  if(buildNow) this->setBaseWidget(this->buildWidget(this->getParentWidget()));
}

/*!
  Destructor.
 */
SoQtExaminerViewer::~SoQtExaminerViewer()
{
  // Cursors.
  delete this->zoomcursor;
  delete this->pancursor;
  delete this->rotatecursor;
  delete this->defaultcursor;

  // Button pixmaps.
  delete this->orthopixmap;
  delete this->perspectivepixmap;

  // Variables used in the spin animation code.
  delete this->timertrigger;
  delete this->spindetecttimer;
  delete this->projector;
}

/*!
  Set the flag deciding whether or not to show the axis cross.

  \sa isFeedbackVisible, getFeedbackSize, setFeedbackSize
 */
void
SoQtExaminerViewer::setFeedbackVisibility(const SbBool on)
{
#if SOQT_DEBUG
  if (on == this->axiscrossOn) {
    SoDebugError::postWarning("SoQtExaminerViewer::setFeedbackVisibility",
                              "feedback visibility already set to %s",
                              on ? "TRUE" : "FALSE");
    return;
  }
#endif // SOQT_DEBUG
  this->axiscrossOn = on;
  if (this->isViewing()) this->scheduleRedraw();
}

/*!
  Check if the feedback axis cross is visible.

  \sa setFeedbackVisibility, getFeedbackSize, setFeedbackSize
 */
SbBool
SoQtExaminerViewer::isFeedbackVisible(void) const
{
  return this->axiscrossOn;
}

/*!
  Set the size of the feedback axiscross. The value is interpreted as
  an approximate percentage chunk of the dimensions of the total canvas.

  \sa getFeedbackSize, isFeedbackVisible, setFeedbackVisibility
 */
void
SoQtExaminerViewer::setFeedbackSize(const int size)
{
#if SOQT_DEBUG
  if (size < 1) {
    SoDebugError::postWarning("SoQtExaminerViewer::setFeedbackSize",
                              "the size setting should be larger than 0");
    return;
  }
#endif // SOQT_DEBUG

  this->axiscrossSize = size;
  if (this->isFeedbackVisible() && this->isViewing()) this->scheduleRedraw();
}

/*!
  Return the size of the feedback axis cross. Default is 25.

  \sa setFeedbackSize, isFeedbackVisible, setFeedbackVisibility
 */
int
SoQtExaminerViewer::getFeedbackSize(void) const
{
  return this->axiscrossSize;
}

/*!
  Decide if it should be possible to start a spin animation of the model in
  the viewer by releasing the mouse button while dragging.

  If the \c on flag is \c FALSE and we're currently animating, the spin
  will be stopped.

  \sa isAnimationEnabled
 */
void
SoQtExaminerViewer::setAnimationEnabled(SbBool on)
{
  this->animatingallowed = on;
  if (!on && this->isAnimating()) this->stopAnimating();
}

/*!
  Query whether or not it is possible to start a spinning animation by
  releasing the left mouse button while dragging the mouse.

  \sa setAnimationEnabled
 */
SbBool
SoQtExaminerViewer::isAnimationEnabled(void)
{
  return this->animatingallowed;
}

/*!
  Stop the model from spinning.
 */
void
SoQtExaminerViewer::stopAnimating(void)
{
  if (this->spinanimating) {
    this->timertrigger->unschedule();
    this->interactiveCountDec();
    this->spinanimating = FALSE;
  }
#if SOQT_DEBUG
  else {
    SoDebugError::postWarning("SoQtExaminerViewer::stopAnimating",
                              "not animating");
  }
#endif // SOT_DEBUG
}

/*!
  Query whether the model in the viewer is currently in spinning mode after
  a user drag.
 */
SbBool
SoQtExaminerViewer::isAnimating(void)
{
  return this->spinanimating;
}

/*!
  This method overloaded from parent class to make sure the mouse
  pointer cursor is updated.
 */
void
SoQtExaminerViewer::setViewing(SbBool on)
{
  this->setMode(on ? EXAMINE : INTERACT);
  inherited::setViewing(on);
}

/*!
  This method overloaded from parent class to toggle the camera type
  selection button pixmap and string of the zoom/dolly thumbwheel.
 */
void
SoQtExaminerViewer::setCamera(SoCamera * newCamera)
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
}

/*!
  Decide whether or not the mouse pointer cursor should be visible in the
  rendering canvas.
 */
void
SoQtExaminerViewer::setCursorEnabled(SbBool on)
{
  inherited::setCursorEnabled(on);
  this->setCursorRepresentation(this->currentmode);
}

/*!
  Overloaded to provide the examiner viewer functionality on the left
  thumbwheel (x axis rotation).
 */
void
SoQtExaminerViewer::leftWheelMotion(float val)
{
  this->reorientCamera(SbRotation(SbVec3f(1.0f, 0.0f, 0.0f),
                                  val - this->getLeftWheelValue()));
  inherited::leftWheelMotion(val);
}

/*!
  Overloaded to provide the examiner viewer functionality on the bottom
  thumbwheel (y axis rotation).
 */
void
SoQtExaminerViewer::bottomWheelMotion(float val)
{
  this->reorientCamera(SbRotation(SbVec3f(0.0f, 1.0f, 0.0f),
                                  this->getBottomWheelValue() - val));
  inherited::bottomWheelMotion(val);
}

/*!
  Overloaded to provide the examiner viewer functionality on the left
  thumbwheel (dolly/zoom).
 */
void
SoQtExaminerViewer::rightWheelMotion(float val)
{
  this->zoom(val - this->getRightWheelValue());
  inherited::rightWheelMotion(val);
}

/*!
  Overloaded to add preferences settings for examiner viewer
  specific stuff (enable/disable possible spin animation,
  enable/disable/configure axis cross graphics).
 */
QWidget *
SoQtExaminerViewer::makeSubPreferences(QWidget * parent)
{
  QWidget * w = new QWidget(parent);
//  w->setBackgroundColor( QColor( 250, 0, 0 ) );

  // Initialize objects keeping track of geometry data.

  QSize totalsize(0, 0);
  QVBoxLayout * toplayout = new QVBoxLayout(w);

  // First, do the single widget on the uppermost row (a checkbox).

  QCheckBox * c1 = new QCheckBox("Enable spin animation", w);
  c1->adjustSize();
  c1->setChecked(this->animatingallowed);
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

  this->feedbackwheel = new QtThumbwheel(QtThumbwheel::Horizontal, w);
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
}

/*!
  Overloaded from parent class so we can append the camera type switch
  button in the rightside button column.
 */
void
SoQtExaminerViewer::createViewerButtons(QWidget * parent, SbPList * buttonlist)
{
  inherited::createViewerButtons(parent, buttonlist);

  this->cameratogglebutton = new QPushButton(parent);
  assert(this->perspectivepixmap);
  assert(this->orthopixmap);
  // Doesn't really matter which pixmap, this is just to make sure
  // that the adjustSize() call will come out right.
  QPixmap * p = this->orthopixmap;
  SoCamera * cam = this->getCamera();
  if (cam) {
    SoType t = cam->getTypeId();
    if (t.isDerivedFrom(SoOrthographicCamera::getClassTypeId()))
      p = this->orthopixmap;
    else if (t.isDerivedFrom(SoPerspectiveCamera::getClassTypeId()))
      p = this->perspectivepixmap;
    else assert(0);
  }

  this->cameratogglebutton->setPixmap(*p);
  this->cameratogglebutton->adjustSize();

  QObject::connect(this->cameratogglebutton, SIGNAL(clicked()),
                   this, SLOT(cameratoggleClicked()));

  buttonlist->append(this->cameratogglebutton);
}

/*!
  Overloaded to provide name of class.
 */
const char *
SoQtExaminerViewer::getDefaultWidgetName(void) const
{
  return "SoQtExaminerViewer";
}

/*!
  Overloaded to provide ``title'' of class.
 */
const char *
SoQtExaminerViewer::getDefaultTitle(void) const
{
  return "Examiner Viewer";
}

/*!
  Overloaded to provide ``title'' of class.
 */
const char *
SoQtExaminerViewer::getDefaultIconTitle(void) const
{
  return "Examiner Viewer";
}

/*!
  Pops up the examiner viewer help card.
 */
void
SoQtExaminerViewer::openViewerHelpCard(void)
{
  this->openHelpCard("SoQtExaminerViewer.help");
}

/*!
  Overloaded from parent class to take care of any model interaction
  events.
 */
void
SoQtExaminerViewer::processEvent(QEvent * event)
{
  // Upon first event detected, make sure the cursor is set correctly.
  if (!this->defaultcursor) this->setCursorRepresentation(this->currentmode);
  // Let parent class take care of any events which are common for
  // all viewer classes.
  if (this->processCommonEvents(event)) return;

  QWidget * canvas = this->getRenderAreaWidget();
  SbVec2s canvassize = this->getGlxSize();
  SbVec2s mousepos(canvas->mapFromGlobal(QCursor::pos()).x(),
                   canvas->mapFromGlobal(QCursor::pos()).y());
  // Convert from Qt coordinate system to OpenGL coordinate system.
  mousepos[1] = canvassize[1] - mousepos[1];
  SbVec2f norm_mousepos(mousepos[0]/float(canvassize[0]),
                        mousepos[1]/float(canvassize[1]));

  // Convert dblclick events to press events to get the "correct"
  // sequence of two press+release pairs under Qt 1.xx and Qt 2.00 at
  // least. (FIXME: is this a Qt bug? Report sent to the Trolls
  // 19991001 mortene.)
#if QT_VERSION < 200
  int eventtype = event->type();
#else // Qt 2.0
  QEvent::Type eventtype = event->type();
#endif // Qt 2.0
  eventtype = (eventtype == Event_MouseButtonDblClick ?
               Event_MouseButtonPress : eventtype);

  switch (eventtype) {
  case Event_MouseButtonPress:
    {
      QMouseEvent * be = (QMouseEvent *)event;
      if (be->button() != LeftButton && be->button() != MidButton) break;

      this->interactiveCountInc();

#if 0 // debug
      SoDebugError::postInfo("SoQtExaminerViewer::processEvent",
                             "mb press, nesting count: %d",
                             this->getInteractiveCount());
#endif // debug

      if (this->currentmode == WAITING_FOR_SEEK) {
        this->seekToPoint(mousepos);
      }
      else {
        this->setModeFromState(be->state() | be->button());
        if (this->isAnimating()) this->stopAnimating();
      }
    }
    break;

  case Event_MouseButtonRelease:
    {
      QMouseEvent * be = (QMouseEvent *)event;
      if (be->button() != LeftButton && be->button() != MidButton) break;

      if (this->currentmode == DRAGGING &&
          this->animatingallowed &&
          this->spindetecttimer &&
          this->spindetecttimer->isActive()) {
        this->spindetecttimer->stop();
        this->spinanimating = TRUE;
        this->timertrigger->schedule();
        this->interactiveCountInc();
      }

      // FIXME: This sometimes makes the interactivecount < 0, as
      // reported by pederb. Find out why. 19991110 mortene.
      this->interactiveCountDec();

#if 0 // debug
      SoDebugError::postInfo("SoQtExaminerViewer::processEvent",
                             "mb release, nesting count: %d",
                             this->getInteractiveCount());
#endif // debug
      this->setModeFromState(be->state() & ~be->button());
    }
    break;

  case Event_MouseMove:
    {
      switch (this->currentmode) {
      case DRAGGING:
        if (!this->spindetecttimer) this->spindetecttimer = new QTimer;
        this->spindetecttimer->start(0, TRUE);
        this->spin(norm_mousepos);
        break;

      case PANNING:
        this->pan(norm_mousepos);
        break;

      case ZOOMING:
        this->zoomByCursor(norm_mousepos);
        break;

      default: /* include default to avoid compiler warnings. */
        break;
      }
    }
    break;

  case Event_KeyPress:
  case Event_KeyRelease:
    {
      QKeyEvent * ke = (QKeyEvent *)event;

      if (ke->key() == Key_Control) {
        if (ke->type() == Event_KeyPress)
          this->setModeFromState(ke->state() | ControlButton);
        else
          this->setModeFromState(ke->state() & ~ControlButton);
      }
    }
    break;

  default: /* include default to avoid compiler warnings. */
    break;
  }

  this->lastmouseposition = norm_mousepos;
}

/*!
  Overload this method to make sure any animations are stopped before
  we go into seek mode.
 */
void
SoQtExaminerViewer::setSeekMode(SbBool on)
{
#if SOQT_DEBUG
  if (on == this->isSeekMode()) {
    SoDebugError::postWarning("SoQtExaminerViewer::setSeekMode",
                              "seek mode already %sset", on ? "" : "un");
    return;
  }
#endif // SOQT_DEBUG

  if (this->isAnimating()) this->stopAnimating();
  inherited::setSeekMode(on);
  this->setMode(on ? WAITING_FOR_SEEK : EXAMINE);
}

/*!
  Overload this method to be able to draw the axis cross if selected
  in the preferences sheet.
 */
void
SoQtExaminerViewer::actualRedraw(void)
{
  inherited::actualRedraw();
  if (this->isFeedbackVisible()) this->drawAxisCross();
}

/*!
  \internal

  Set the viewer mode based on the given mouse and keyboard state setting.
 */
void
SoQtExaminerViewer::setModeFromState(const unsigned int state)
{
  ViewerMode mode;
  const unsigned int maskedstate =
    state & (LeftButton|MidButton|ControlButton);

  switch (maskedstate) {
  case 0:
    mode = EXAMINE;
    break;

  case LeftButton:
    mode = DRAGGING;
    break;

  case MidButton:
  case (LeftButton|ControlButton):
    mode = PANNING;
    break;

  case ControlButton:
    mode = WAITING_FOR_PAN;
    break;

  case (MidButton|ControlButton):
  case (LeftButton|MidButton):
  case (LeftButton|MidButton|ControlButton):
    mode = ZOOMING;
    break;

  default: assert(0); break;
  }

  this->setMode(mode);
}

/*!
  \internal

  The viewer is a state machine, and all changes to the current state
  are made through this call.
 */
void
SoQtExaminerViewer::setMode(const ViewerMode mode)
{
  this->setCursorRepresentation(mode);

  switch (mode) {
  case INTERACT:
    if (this->isAnimating()) this->stopAnimating();
    while (this->getInteractiveCount()) this->interactiveCountDec();
    break;

  case DRAGGING:
    this->projector->project(this->lastmouseposition);
    break;

  case PANNING:
    {
      // The plane we're projecting the mouse coordinates to get 3D
      // coordinates should stay the same during the whole pan
      // operation, so we should calculate this value here.
      SoCamera * cam = this->getCamera();
      SbViewVolume vv = cam->getViewVolume(this->getGlxAspectRatio());
      this->panningplane = vv.getPlane(cam->focalDistance.getValue());
    }
    break;

  default: /* include default to avoid compiler warnings. */
    break;
  }

  this->currentmode = mode;
}

/*!
  \internal

  Set cursor graphics according to mode.
 */
void
SoQtExaminerViewer::setCursorRepresentation(const ViewerMode mode)
{
  QWidget * w = this->getRenderAreaWidget();
  assert(w);

  if (!this->defaultcursor) {
    this->defaultcursor = new QCursor(w->cursor());

    QBitmap zoomBtm(so_qt_zoom_width, so_qt_zoom_height,
                    (uchar*)so_qt_zoom_bitmap, FALSE);
    QBitmap zoomMask(so_qt_zoom_width, so_qt_zoom_height,
                     (uchar*)so_qt_zoom_mask_bitmap, FALSE);
    QBitmap panBtm(so_qt_pan_width, so_qt_pan_height,
                   (uchar*)so_qt_pan_bitmap, FALSE);
    QBitmap panMask(so_qt_pan_width, so_qt_pan_height,
                    (uchar*)so_qt_pan_mask_bitmap, FALSE);
    QBitmap rotateBtm(so_qt_rotate_width, so_qt_rotate_height,
                      (uchar*)so_qt_rotate_bitmap, FALSE);
    QBitmap rotateMask(so_qt_rotate_width, so_qt_rotate_height,
                       (uchar*)so_qt_rotate_mask_bitmap, FALSE);

    this->zoomcursor = new QCursor(zoomBtm, zoomMask,
                                   so_qt_zoom_x_hot, so_qt_zoom_y_hot);
    this->pancursor = new QCursor(panBtm, panMask,
                                  so_qt_pan_x_hot, so_qt_pan_y_hot);
    this->rotatecursor = new QCursor(rotateBtm, rotateMask,
                                     so_qt_rotate_x_hot, so_qt_rotate_y_hot);
  }



  if (!this->isCursorEnabled()) {
    w->setCursor(blankCursor);
    return;
  }

  switch (mode) {
  case INTERACT:
    w->setCursor(arrowCursor);
    break;

  case EXAMINE:
  case DRAGGING:
    w->setCursor(* this->rotatecursor);
    break;

  case ZOOMING:
    w->setCursor(* this->zoomcursor);
    break;

  case WAITING_FOR_SEEK:
    w->setCursor(crossCursor);
    break;

  case WAITING_FOR_PAN:
  case PANNING:
    w->setCursor(* this->pancursor);
    break;

  default: assert(0); break;
  }
}

/*!
  \internal

  Draw an arrow for the axis representation directly through OpenGL.
 */
void
SoQtExaminerViewer::drawArrow(void)
{
  glBegin(GL_LINES);
  glVertex3f(0, 0, 0);
  glVertex3f(1, 0, 0);
  glEnd();
  glDisable(GL_CULL_FACE);
  glBegin(GL_TRIANGLES);
  glVertex3f(1.0, 0, 0);
  glVertex3f(1.0-1.0/3, +0.5/4, 0);
  glVertex3f(1.0-1.0/3, -0.5/4, 0);
  glVertex3f(1.0, 0, 0);
  glVertex3f(1.0-1.0/3, 0, +0.5/4);
  glVertex3f(1.0-1.0/3, 0, -0.5/4);
  glEnd();
  glBegin(GL_QUADS);
  glVertex3f(1.0-1.0/3, +0.5/4, 0);
  glVertex3f(1.0-1.0/3, 0, +0.5/4);
  glVertex3f(1.0-1.0/3, -0.5/4, 0);
  glVertex3f(1.0-1.0/3, 0, -0.5/4);
  glEnd();
}

/*!
  \internal

  Draw an axis cross directly through OpenGL.
 */
void
SoQtExaminerViewer::drawAxisCross(void)
{
  // Store GL state information for the variables that we modify.
  glPushAttrib(GL_LIGHTING_BIT|GL_DEPTH_BUFFER_BIT|GL_TRANSFORM_BIT|
               GL_VIEWPORT_BIT|GL_LINE_BIT|GL_ENABLE_BIT);
  GLfloat depthrange[2];
  glGetFloatv(GL_DEPTH_RANGE, depthrange);
  GLdouble projectionmatrix[16];
  glGetDoublev(GL_PROJECTION_MATRIX, projectionmatrix);

  glDepthFunc(GL_ALWAYS);
  glDepthMask(GL_TRUE);
  glDepthRange(0, 0);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);


  // Set the viewport in the OpenGL canvas. Dimensions are calculated
  // as a percentage of the total canvas size.
  SbVec2s view = this->getGlxSize();
  const int pixelarea =
    int(float(this->axiscrossSize)/100.0f * exvMin(view[0], view[1]));
#if 0 // middle of canvas
  SbVec2s origin(view[0]/2 - pixelarea/2, view[1]/2 - pixelarea/2);
#endif // middle of canvas
#if 1 // lower right of canvas
  SbVec2s origin(view[0] - pixelarea, 0);
#endif // lower right of canvas
  glViewport(origin[0], origin[1], pixelarea, pixelarea);


  // Set up the projection matrix.
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  const float NEARVAL = 0.1f;
  const float FARVAL = 10.0f;
  const float dim = NEARVAL * tan(M_PI/8.0f); // FOV is 45° (45/360 = 1/8)
  glFrustum(-dim, dim, -dim, dim, NEARVAL, FARVAL);


  // Set up the model matrix.
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  SbMatrix mx;
  mx = this->getCamera()->orientation.getValue();
  mx = mx.inverse();
  mx[3][2] = -3.5; // Translate away from the projection point (along z axis).
  glLoadMatrixf((float *)mx);


  // Find unit vector end points.
  SbMatrix px;
  glGetFloatv(GL_PROJECTION_MATRIX, (float *)px);
  SbMatrix comb = mx.multRight(px);

  SbVec3f xpos;
  comb.multVecMatrix(SbVec3f(1,0,0), xpos);
  xpos[0] = (1 + xpos[0]) * view[0]/2;
  xpos[1] = (1 + xpos[1]) * view[1]/2;
  SbVec3f ypos;
  comb.multVecMatrix(SbVec3f(0,1,0), ypos);
  ypos[0] = (1 + ypos[0]) * view[0]/2;
  ypos[1] = (1 + ypos[1]) * view[1]/2;
  SbVec3f zpos;
  comb.multVecMatrix(SbVec3f(0,0,1), zpos);
  zpos[0] = (1 + zpos[0]) * view[0]/2;
  zpos[1] = (1 + zpos[1]) * view[1]/2;


  // Render the cross.
  {
    glLineWidth(2.0);

    // FIXME: the code which makes sure we render in the correct order
    // (which we have to do, as Z-buffering is dysfunctional at this
    // stage) is _really_ lousy. A virtual beer to the first hacker
    // who improves this code. 990424 mortene.

    // Bubble sort.. :-}
    float minval = xpos[2];
    float midval = ypos[2];
    float maxval = zpos[2];
    if (minval > midval) exvSwap(minval, midval);
    if (midval > maxval) exvSwap(midval, maxval);
    if (minval > midval) exvSwap(minval, midval);
    assert((minval <= midval) && (midval <= maxval)); // Just checking..

    // Find the order of rendering. Furthest away should render first,
    // so we sort in back-to-front order.
    int xturn = (xpos[2] == minval) ? 2 : ((xpos[2] == midval) ? 1 : 0);
    int yturn = (ypos[2] == minval) ? 2 : ((ypos[2] == midval) ? 1 : 0);
    int zturn = (zpos[2] == minval) ? 2 : ((zpos[2] == midval) ? 1 : 0);

    // In case any of the three planes defined by the axes were
    // parallel with the viewing plane.
    if (yturn == xturn) yturn++;
    if (zturn == xturn) zturn++;
    if (zturn == yturn) zturn++;

    // The code is uglier than Valgerd Svarstad Haugland, but it'd
    // be even more embarrassing if it didn't work correctly.
    assert(xturn != yturn);
    assert(xturn != zturn);
    assert(yturn != zturn);

    for (int i=0; i < 3; i++) {
      glPushMatrix();
      if (xturn == i) {
        // X axis.
        glColor3fv(SbVec3f(0.500f, 0.125f, 0.125f).getValue());
        this->drawArrow();
      }
      else if (yturn == i) {
        // Y axis.
        glRotatef(90, 0, 0, 1);
        glColor3fv(SbVec3f(0.125f, 0.500f, 0.125f).getValue());
        this->drawArrow();
      }
      else {
        // Z axis.
        glRotatef(-90, 0, 1, 0);
        glColor3fv(SbVec3f(0.125f, 0.125f, 0.500f).getValue());
        this->drawArrow();
      }
      glPopMatrix();
    }
  }

  // Render axis notation letters ("X", "Y", "Z").
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, view[0], 0, view[1], -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  GLint unpack;
  glGetIntegerv(GL_UNPACK_ALIGNMENT, &unpack);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glColor3fv(SbVec3f(0.8f, 0.8f, 0.0f).getValue());

  glRasterPos2d(xpos[0], xpos[1]);
  glBitmap(8, 7, 0, 0, 0, 0, xbmp);
  glRasterPos2d(ypos[0], ypos[1]);
  glBitmap(8, 7, 0, 0, 0, 0, ybmp);
  glRasterPos2d(zpos[0], zpos[1]);
  glBitmap(8, 7, 0, 0, 0, 0, zbmp);

  glPixelStorei(GL_UNPACK_ALIGNMENT, unpack);
  glPopMatrix();


  // Reset original state.
  glDepthRange(depthrange[0], depthrange[1]);
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixd(projectionmatrix);
  glPopAttrib();
}

/*!
  \internal

  Rotate the camera by the given amount, then reposition it so we're still
  pointing at the same focal point.
*/
void
SoQtExaminerViewer::reorientCamera(const SbRotation & rot)
{
  SoCamera * cam = this->getCamera();
  assert(cam);

  // Find global coordinates of focal point.
  SbVec3f direction;
  cam->orientation.getValue().multVec(SbVec3f(0, 0, -1), direction);
  SbVec3f focalpoint =
    cam->position.getValue() + cam->focalDistance.getValue() * direction;

  // Set new orientation value by accumulating the new rotation.
  cam->orientation = rot * cam->orientation.getValue();

  // Reposition camera so we are still pointing at the same old focal
  // point.
  cam->orientation.getValue().multVec(SbVec3f(0, 0, -1), direction);
  cam->position = focalpoint - cam->focalDistance.getValue() * direction;
}

/*!
  \internal

  Move scene parallel with the plane orthogonal to the camera
  direction vector.
 */
void
SoQtExaminerViewer::pan(const SbVec2f & mousepos)
{
  SoCamera * cam = this->getCamera();
  assert(cam);

  // Find projection points for the last and current mouse
  // coordinates.
  SbViewVolume vv = cam->getViewVolume(this->getGlxAspectRatio());
  SbLine line;
  vv.projectPointToLine(mousepos, line);
  SbVec3f current_planept;
  this->panningplane.intersect(line, current_planept);
  vv.projectPointToLine(this->lastmouseposition, line);
  SbVec3f old_planept;
  this->panningplane.intersect(line, old_planept);

  // Reposition camera according to the vector difference between the
  // projected points.
  cam->position = cam->position.getValue() - (current_planept - old_planept);
}

/*!
  \internal

  Uses the sphere sheet projector to map the mouseposition unto
  a 3D point and find a rotation from this and the last calculated point.
 */
void
SoQtExaminerViewer::spin(const SbVec2f & mousepos)
{
  assert(this->projector);

  SbRotation r;
  this->projector->projectAndGetRotation(mousepos, r);
#if 0 // debug
  // FIXME: Trying to track down an annoying (non-critical) bug.
  // 990501 mortene.
  if (r == SbRotation::identity()) {
    SoDebugError::postWarning("SoQtExaminerViewer::spin",
                              "rotation equals identity");
  }
#endif // debug
  r.invert();
  this->reorientCamera(r);


  // Calculate an average angle magnitude value to make the transition
  // to a possible spin animation mode appear smooth.

  SbVec3f dummy_axis, newaxis;
  float acc_angle, newangle;
  this->spinincrement.getValue(dummy_axis, acc_angle);
  acc_angle *= this->spinsamplecounter; // weight
  r.getValue(newaxis, newangle);
  acc_angle += newangle;

  this->spinsamplecounter++;
  acc_angle /= this->spinsamplecounter;

  // FIXME: accumulate and average axis vectors aswell? 990501 mortene.
  this->spinincrement.setValue(newaxis, acc_angle);

  // Don't carry too much baggage, as that'll give unwanted results
  // when the user quickly trigger (as in "click-drag-release") a spin
  // animation.
  if (this->spinsamplecounter > 3) this->spinsamplecounter = 3;
}

/*!
  \internal

  Dependent on the camera type this will either shrink or expand
  the height of the viewport (orthogonal camera) or move the
  camera closer or further away from the focal point in the scene.
 */
void
SoQtExaminerViewer::zoom(const float diffvalue)
{
  SoCamera * cam = this->getCamera();
  assert(cam);
  SoType t = cam->getTypeId();

  // This will be in the range of <0, ->>.
  float multiplicator = exp(diffvalue);

  if (t.isDerivedFrom(SoOrthographicCamera::getClassTypeId())) {
    SoOrthographicCamera * oc = (SoOrthographicCamera *)cam;
    oc->height = oc->height.getValue() * multiplicator;
  }
  else if (t.isDerivedFrom(SoPerspectiveCamera::getClassTypeId())) {
    float oldfocaldist = cam->focalDistance.getValue();
    cam->focalDistance = oldfocaldist * multiplicator;

    SbVec3f direction;
    cam->orientation.getValue().multVec(SbVec3f(0, 0, -1), direction);
    cam->position =
      cam->position.getValue() +
      (cam->focalDistance.getValue() - oldfocaldist) * -direction;
  }
  else {
    assert(0);
  }
}

/*!
  \internal

  Calculate a zoom/dolly factor from the difference of the current
  cursor position and the last.
 */
void
SoQtExaminerViewer::zoomByCursor(const SbVec2f & mousepos)
{
  // There is no "geometrically correct" value, 20 just seems to give
  // about the right "feel".
  this->zoom((mousepos[1] - this->lastmouseposition[1]) * 20.0f);
}

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
}

/*!
  \internal

  This is the regularly called code which makes the spin animation run.
 */
void
SoQtExaminerViewer::timertriggeredCB(void * data, SoSensor *)
{
  SoQtExaminerViewer * thisp = (SoQtExaminerViewer *)data;

#if 0 // debug
  SoDebugError::postInfo("SoQtExaminerViewer::timertriggeredCB",
                         "spin samples: %d", thisp->spinsamplecounter);
#endif // debug

  if (thisp->spinsamplecounter < 2) {
    // FIXME: won't the first check here always equal TRUE? 990501
    // mortene.
    if (thisp->isAnimating()) thisp->stopAnimating();
#if 0 // check hypothesis from above FIXME statement.
    else thisp->timertrigger->unschedule();
#else
    else assert(0);
#endif
    return;
  }

  thisp->reorientCamera(thisp->spinincrement);
}


/*!
  \internal

  This gets called whenever the visibility status of the viewer widget
  changes (for instance on iconization/deiconization).
 */
void
SoQtExaminerViewer::visibilityCB(void * data, SbBool visible)
{
  SoQtExaminerViewer * thisp = (SoQtExaminerViewer *)data;

  if (thisp->isAnimating()) {
    if (visible) thisp->timertrigger->schedule();
    else thisp->timertrigger->unschedule();
  }
}

/*!
  \internal
  Pref sheet slot.
 */
void
SoQtExaminerViewer::spinAnimationToggled(bool flag)
{
  this->setAnimationEnabled(flag);
}

/*!
  \internal
  Pref sheet slot.
 */
void
SoQtExaminerViewer::feedbackVisibilityToggle(bool flag)
{
  this->setFeedbackVisibility(flag);
  this->setEnableFeedbackControls(flag);
}

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
}

/*!
  \internal
  Pref sheet slot.
 */
void
SoQtExaminerViewer::feedbackWheelPressed()
{
  this->interactiveCountInc();
}

/*!
  \internal
  Pref sheet slot.
 */
void
SoQtExaminerViewer::feedbackWheelReleased()
{
  this->interactiveCountDec();
}

/*!
  \internal
  Pref sheet slot.
 */
void
SoQtExaminerViewer::feedbackSizeChanged(float val)
{
  if (val <= 0.0f) {
    val = 0.1f;
    this->feedbackwheel->setValue(val);
  }

  this->setFeedbackSize(int(val * 10));

  QString s;
  s.setNum(this->getFeedbackSize());
  this->feedbackedit->setText(s);
}

/*!
  \internal
  Pref sheet slot.
*/

void
SoQtExaminerViewer::cameratoggleClicked()
{
  this->toggleCameraType();
}

