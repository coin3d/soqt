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

#if SOQT_DEBUG
static const char rcsid[] =
  "$Id$";
#endif // SOQT_DEBUG

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

#include <soqtdefs.h>
#include <Inventor/Qt/widgets/SoQtThumbWheel.h>
#include <Inventor/Qt/SoQtCursors.h>

#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/Qt/viewers/SoAnyExaminerViewer.h>

// Icon graphic for the camera button.
#include <Inventor/Qt/common/pixmaps/ortho.xpm>
#include <Inventor/Qt/common/pixmaps/perspective.xpm>

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
  SoQtViewer::Type type )
: inherited( parent, name, embed, flag, type, FALSE )
, common( new SoAnyExaminerViewer( this ) )
{
  this->constructor( TRUE );
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
: inherited( parent, name, embed, flag, type, FALSE )
, common( new SoAnyExaminerViewer( this ) )
{
  this->constructor( build );
} // SoQtExaminerViewer()

// *************************************************************************

/*!
  \internal

  This contains the real constructor code (the two constructors are only
  entry points for this method).
*/

void
SoQtExaminerViewer::constructor(
  SbBool build )
{
  this->currentmode = EXAMINE;
  this->defaultcursor = NULL;
  this->rotatecursor = NULL;
  this->pancursor = NULL;
  this->zoomcursor = NULL;

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

  if ( build ) {
    QWidget * widget = this->buildWidget( this->getParentWidget() );
    this->setBaseWidget( widget );
  }
} // constructor()

// *************************************************************************

/*!
  Destructor.
*/

SoQtExaminerViewer::~SoQtExaminerViewer(
  void )
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
  delete this->spindetecttimer;

  delete this->common;
} // ~SoQtExaminerViewer()

// *************************************************************************

/*!
  This method overloaded from parent class to make sure the mouse
  pointer cursor is updated.
*/

void
SoQtExaminerViewer::setViewing( // virtual
  SbBool enable )
{
  this->setMode( enable ? EXAMINE : INTERACT );
  inherited::setViewing( enable );
} // setViewing()

// *************************************************************************

/*!
  This method overloaded from parent class to toggle the camera type
  selection button pixmap and string of the zoom/dolly thumbwheel.
*/

void
SoQtExaminerViewer::setCamera( // virtual
  SoCamera * newCamera )
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
  Decide whether or not the mouse pointer cursor should be visible in the
  rendering canvas.
*/

void
SoQtExaminerViewer::setCursorEnabled( // virtual, protected
  SbBool enable )
{
  inherited::setCursorEnabled( enable );
  this->setCursorRepresentation( this->currentmode );
} // setcursorEnabled()

/*!
  FIXME: write doc
*/

void
SoQtExaminerViewer::resetToHomePosition(
  void )
{
  inherited::resetToHomePosition();
} // resetToHomePosition()

/*!
  FIXME: write doc
*/

void
SoQtExaminerViewer::viewAll( // virtual
  void )
{
  inherited::viewAll();
} // viewAll()

// *************************************************************************

/*!
  Overloaded to provide the examiner viewer functionality on the left
  thumbwheel (x axis rotation).
*/

void
SoQtExaminerViewer::leftWheelMotion(
  float value )
{
  if ( common->isAnimating() )
    common->stopAnimating();

  inherited::leftWheelMotion(
    common->rotXWheelMotion( value, this->getLeftWheelValue() ) );
} // leftWheelMotion()

/*!
  Overloaded to provide the examiner viewer functionality on the bottom
  thumbwheel (y axis rotation).
*/

void
SoQtExaminerViewer::bottomWheelMotion(
  float value )
{
  if ( common->isAnimating() )
    common->stopAnimating();

  inherited::bottomWheelMotion(
    common->rotYWheelMotion( value, this->getBottomWheelValue() ) );
} // bottomWheelMotion()

/*!
  Overloaded to provide the examiner viewer functionality on the left
  thumbwheel (dolly/zoom).
*/

void
SoQtExaminerViewer::rightWheelMotion(
  float value )
{
  common->zoom( this->getRightWheelValue() - value );
  inherited::rightWheelMotion( value );
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
//  w->setBackgroundColor( QColor( 250, 0, 0 ) );

  // Initialize objects keeping track of geometry data.

  QSize totalsize(0, 0);
  QVBoxLayout * toplayout = new QVBoxLayout(w);

  // First, do the single widget on the uppermost row (a checkbox).

  QCheckBox * c1 = new QCheckBox("Enable spin animation", w);
  c1->adjustSize();
  c1->setChecked(common->isAnimationEnabled());
  QObject::connect(c1, SIGNAL(toggled(bool)),
                   this, SLOT(spinAnimationToggled(bool)));

  // Layout row 1.
  toplayout->addWidget(c1, c1->height());
  expandSize(totalsize, c1->size(), LayoutVertical);

  // Do the single widget on the second row (a checkbox).

  QCheckBox * c2 = new QCheckBox("Show point of rotation axes", w);
  c2->adjustSize();
  c2->setChecked(common->isFeedbackVisible());
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
  this->feedbackwheel->setRangeBoundaryHandling( SoQtThumbWheel::ACCUMULATE );
  QObject::connect(this->feedbackwheel, SIGNAL(wheelMoved(float)),
                   this, SLOT(feedbackSizeChanged(float)));
  this->feedbackwheel->setValue(float(common->getFeedbackSize())/10.0f);
  this->feedbackwheel->adjustSize();
  expandSize(tmpsize, this->feedbackwheel->size(), LayoutHorizontal);

  this->feedbackedit = new QLineEdit(w);
  QObject::connect(this->feedbackedit, SIGNAL(returnPressed()),
                   this, SLOT(feedbackEditPressed()));
  QString s;
  s.setNum(common->getFeedbackSize());
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

  this->setEnableFeedbackControls(common->isFeedbackVisible());

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
SoQtExaminerViewer::getDefaultWidgetName( // virtual
  void ) const
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
  Overloaded from parent class to take care of any model interaction
  events.
*/

void
SoQtExaminerViewer::processEvent(QEvent * event)
{
//  SoDebugError::postInfo( "SoQtExaminerViewer::processEvent", "[invoked]" );
  // Upon first event detected, make sure the cursor is set correctly.
  if (!this->defaultcursor) this->setCursorRepresentation(this->currentmode);
  // Let parent class take care of any events which are common for
  // all viewer classes.
  if (this->processCommonEvents(event)) return;

  QWidget * canvas = this->getRenderAreaWidget();
  SbVec2s canvassize = this->getGLSize();
  SbVec2s mousepos(canvas->mapFromGlobal(QCursor::pos()).x(),
                   canvas->mapFromGlobal(QCursor::pos()).y());
  // Convert from Qt coordinate system to OpenGL coordinate system.
  mousepos[1] = canvassize[1] - mousepos[1];
  SbVec2f norm_mousepos(mousepos[0]/float(canvassize[0]),
                        mousepos[1]/float(canvassize[1]));
#if SOQT_DEBUG && 0
  static int _pressed = 0;
  if ( _pressed ) {
    SoDebugError::postInfo( "event",
      "mousepos( %d, %d ) - norm_mousepos( %f, %f )",
       mousepos[0], mousepos[1], norm_mousepos[0], norm_mousepos[1] );
  }
#endif

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
#if SOQT_DEBUG && 0
      SoDebugError::postInfo( "press", "" );
      _pressed = 1;
#endif
      common->lastmouseposition = norm_mousepos;
      common->lastspinposition = norm_mousepos;
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
        if (common->isAnimating()) common->stopAnimating();
      }
    }
    break;

  case Event_MouseButtonRelease:
    {
#if SOQT_DEBUG && 0
      SoDebugError::postInfo( "release", "" );
      _pressed = 0;
#endif
      QMouseEvent * be = (QMouseEvent *)event;
      if (be->button() != LeftButton && be->button() != MidButton) break;

      if (this->currentmode == DRAGGING &&
          common->spinanimatingallowed &&
          this->spindetecttimer &&
          this->spindetecttimer->isActive()) {
        this->spindetecttimer->stop();
        common->spinanimating = TRUE;
        common->spintimertrigger->schedule();
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
        common->spin(norm_mousepos);
        break;

      case PANNING:
        common->pan(norm_mousepos);
        break;

      case ZOOMING:
        common->zoomByCursor(norm_mousepos);
        break;

      default: // include default to avoid compiler warnings.
        break;
      }
    }
    break;

#if QT_VERSION >= 200
  case QEvent::Accel:
  case QEvent::AccelAvailable:
    // Qt 2 introduced "accelerator" type keyboard events. They should
    // be handled by SoQtGLWidget (that is: ignored), so we should
    // never see any accelerator events here.
    assert(FALSE && "got accelerator event");
    break;
#endif // Qt v2.0

  case Event_KeyPress:
    {
      QKeyEvent * ke = (QKeyEvent *)event;
      if (ke->key() == Key_Control)
        this->setModeFromState(ke->state() | ControlButton);
    }
    break;

  case Event_KeyRelease:
    {
      QKeyEvent * ke = (QKeyEvent *)event;
      if (ke->key() == Key_Control)
        this->setModeFromState(ke->state() & ~ControlButton);
    }
    break;

  default: // include default to avoid compiler warnings.
    break;
  }

  common->lastmouseposition = norm_mousepos;
} // processEvents()

// *************************************************************************

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

  if (common->isAnimating()) common->stopAnimating();
  inherited::setSeekMode(on);
  this->setMode(on ? WAITING_FOR_SEEK : EXAMINE);
} // setSeekMode()

// *************************************************************************

/*!
  Overload this method to be able to draw the axis cross if selected
  in the preferences sheet.
*/

void
SoQtExaminerViewer::actualRedraw(void)
{
  inherited::actualRedraw();
  if ( common->isFeedbackVisible() )
    common->drawAxisCross();
} // actualRedraw()

// *************************************************************************

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
} // setModeFromState()

// *************************************************************************

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
    if (common->isAnimating()) common->stopAnimating();
    while (this->getInteractiveCount()) this->interactiveCountDec();
    break;

  case DRAGGING:
    // what's this?  move to SoAny*
    common->spinprojector->project( common->lastmouseposition );
    break;

  case PANNING:
    {
      // The plane we're projecting the mouse coordinates to get 3D
      // coordinates should stay the same during the whole pan
      // operation, so we should calculate this value here.
      SoCamera * cam = this->getCamera();
      SbViewVolume vv = cam->getViewVolume(this->getGLAspectRatio());
      common->panningplane = vv.getPlane(cam->focalDistance.getValue());
    }
    break;

  default: // include default to avoid compiler warnings.
    break;
  }

  this->currentmode = mode;
} // setMode()

// *************************************************************************

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

    // For Qt on MSWin, it is necessary to mask the bitmaps "manually"
    // before setting up the QBitmaps for the cursors. It doesn't seem
    // to matter any way under X11. Sounds like a Qt bug to me, which
    // seems strange -- as this issue has been present for at least a
    // couple of years. 20000630 mortene.
    {
      unsigned char * bitmaps[] = {
        so_qt_rotate_bitmap, so_qt_rotate_mask_bitmap,
        so_qt_zoom_bitmap, so_qt_zoom_mask_bitmap,
        so_qt_pan_bitmap, so_qt_pan_mask_bitmap
      };
      unsigned int bitmapsizes[] = {
        (so_qt_rotate_width + 7) / 8 * so_qt_rotate_height,
        (so_qt_zoom_width + 7) / 8 * so_qt_zoom_height,
        (so_qt_pan_width + 7) / 8 * so_qt_pan_height,
      };

      for ( unsigned int i = 0;
            i < (sizeof(bitmapsizes) / sizeof(unsigned int)); i++) {
        for ( unsigned int j = 0; j < bitmapsizes[i]; j++)
          bitmaps[i*2][j] &= bitmaps[i*2+1][j];
      }
    }

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
SoQtExaminerViewer::visibilityCallback( SbBool visible )
{
  if ( common->isAnimating() ) {
    if ( visible )
      common->spintimertrigger->schedule();
    else
      common->spintimertrigger->unschedule();
  }
}

void
SoQtExaminerViewer::visibilityCB(void * data, SbBool visible)
{
  ((SoQtExaminerViewer *) data)->visibilityCallback( visible );
} // visibilityCB()

// *************************************************************************

/*!
  \internal

  Pref sheet slot.
*/

void
SoQtExaminerViewer::spinAnimationToggled(bool flag)
{
  common->setAnimationEnabled(flag ? TRUE : FALSE);
} // spinAnimationToggled()

// *************************************************************************

/*!
  \internal
  Pref sheet slot.
*/

void
SoQtExaminerViewer::feedbackVisibilityToggle(bool flag)
{
  common->setFeedbackVisibility(flag ? TRUE : FALSE);
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
    common->setFeedbackSize(val);
  }
  else {
    QString s;
    s.setNum(common->getFeedbackSize());
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

  common->setFeedbackSize(int(val * 10));

  QString s;
  s.setNum(common->getFeedbackSize());
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
  if ( this->getCamera() ) this->toggleCameraType();
} // cameratoggleClicked()

// *************************************************************************

void
SoQtExaminerViewer::setAnimationEnabled(
  const SbBool enable )
{
  common->setAnimationEnabled( enable );
  // FIXME: set spinanimtoggle state
} // setAnimationEnabled()

SbBool
SoQtExaminerViewer::isAnimationEnabled(
  void ) const
{
  return common->isAnimationEnabled();
} // isAnimationEnabled()

void
SoQtExaminerViewer::stopAnimating(
  void )
{
  common->stopAnimating();
} // stopAnimating()

SbBool
SoQtExaminerViewer::isAnimating(
  void ) const
{
  return common->isAnimating();
} // isAnimating()

void
SoQtExaminerViewer::setFeedbackVisibility(
  const SbBool enable )
{
  common->setFeedbackVisibility( enable );
} // setFeedbackVisibility()

SbBool
SoQtExaminerViewer::isFeedbackVisible(
  void ) const
{
  return common->isFeedbackVisible();
} // isFeedbackVisible()

void
SoQtExaminerViewer::setFeedbackSize(
   const int size )
{
  common->setFeedbackSize( size );
} // setFeedbackSize()

int
SoQtExaminerViewer::getFeedbackSize(
  void ) const
{
  return common->getFeedbackSize();
} // getFeedbackSize()

// *************************************************************************
