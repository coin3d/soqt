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

#if SOQT_DEBUG
static const char rcsid[] =
  "$Id$";
#endif

#include <qevent.h>
#include <qpushbutton.h>
#include <qpixmap.h>
#include <qkeycode.h>
#if QT_VERSION >= 200
#include <q1xcompatibility.h>
#endif // Qt >= 2.0.0

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>

#include <soqtdefs.h>
#include <Inventor/Qt/widgets/SoQtThumbWheel.h>

#include <Inventor/Qt/viewers/SoAnyPlaneViewer.h>
#include <Inventor/Qt/viewers/SoQtPlaneViewer.h>

#include <Inventor/Qt/common/pixmaps/ortho.xpm>
#include <Inventor/Qt/common/pixmaps/perspective.xpm>
#include <Inventor/Qt/common/pixmaps/x.xpm>
#include <Inventor/Qt/common/pixmaps/y.xpm>
#include <Inventor/Qt/common/pixmaps/z.xpm>

/*!
  \class SoQtPlaneViewer Inventor/Qt/viewers/SoQtPlaneViewer.h
  \brief The SoQtPlaneViewer class is yet to be documented...
  \ingroup soqtviewers
*/

// ************************************************************************

SOQT_OBJECT_SOURCE(SoQtPlaneViewer);

// ************************************************************************

/*!
  The public constructor.
*/

SoQtPlaneViewer::SoQtPlaneViewer(
  QWidget * parent,
  const char * const name, 
  SbBool embed,
  SoQtFullViewer::BuildFlag flag, 
  SoQtViewer::Type type )
: inherited( parent, name, embed, flag, type, FALSE )
, common( new SoAnyPlaneViewer( this ) )
{
  this->constructor( TRUE );
} // SoQtPlaneViewer()

// ************************************************************************

/*!
  A protected constructor.
*/

SoQtPlaneViewer::SoQtPlaneViewer(
  QWidget * parent,
  const char * const name, 
  SbBool embed, 
  SoQtFullViewer::BuildFlag flag, 
  SoQtViewer::Type type, 
  SbBool build )
: inherited( parent, name, embed, flag, type, FALSE )
, common( new SoAnyPlaneViewer( this ) )
{
  this->constructor( build );
} // SoQtPlaneViewer()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::constructor( // private
  SbBool build )
{
  this->mode = IDLE_MODE;

  this->projector = new SbPlaneProjector;
  SbViewVolume vv;
  vv.ortho(-1, 1, -1, 1, -1, 1);
  this->projector->setViewVolume(vv);

  this->addVisibilityChangeCallback( SoQtPlaneViewer::visibilityCB, this );

  this->setClassName("SoQtPlaneViewer");
  this->setLeftWheelString( "transY" );
  this->setBottomWheelString( "transX" );

  this->pixmaps.orthogonal = new QPixmap( (const char **) ortho_xpm );
  this->pixmaps.perspective = new QPixmap( (const char **) perspective_xpm );

  if ( build ) {
    QWidget * widget = this->buildWidget( this->getParentWidget() );
    this->setBaseWidget( widget );
    this->setSize( SbVec2s( 550, 450 ) ); // extra buttons -> more height
  }
} // constructor()

// ************************************************************************

/*!
  The destructor.
*/

SoQtPlaneViewer::~SoQtPlaneViewer(
  void )
{
  delete this->pixmaps.orthogonal;
  delete this->pixmaps.perspective;
  delete this->projector;
} // ~SoQtPlaneViewer()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::setViewing( // virtual
  SbBool enable )
{
  inherited::setViewing( enable );
} // setViewing()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::setCamera( // virtual
  SoCamera * camera )
{
  if ( camera ) {
    SoType type = camera->getTypeId();
    SbBool orthogonal =
      type.isDerivedFrom( SoOrthographicCamera::getClassTypeId() );
    this->setRightWheelString( orthogonal ? "Zoom" : "Dolly" );
    if ( this->buttons.camera ) {
      this->buttons.camera->setPixmap( orthogonal ?
        *(this->pixmaps.orthogonal) : *(this->pixmaps.perspective) );
    }
  }
  inherited::setCamera( camera );
} // setCamera()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::setCursorEnabled( // virtual
  SbBool enable )
{
  inherited::setCursorEnabled( enable );
} // setCursorEnabled()

// ************************************************************************

/*!
*/

QWidget *
SoQtPlaneViewer::buildWidget(
  QWidget * parent )
{
  QWidget * widget = inherited::buildWidget( parent );

  this->getThumbwheel( LEFTDECORATION )
    -> setRangeBoundaryHandling( SoQtThumbWheel::ACCUMULATE );
  this->getThumbwheel( BOTTOMDECORATION )
    -> setRangeBoundaryHandling( SoQtThumbWheel::ACCUMULATE );
  
  return widget;
} // buildWidget()

// ************************************************************************

/*!
*/

const char *
SoQtPlaneViewer::getDefaultWidgetName( // virtual
  void ) const
{
  static const char defaultWidgetName[] = "";
  return defaultWidgetName;
} // getDefaultWidgetName()

// ************************************************************************

/*!
*/

const char *
SoQtPlaneViewer::getDefaultTitle( // virtual
  void ) const
{
  static const char defaultTitle[] = "Plane Viewer";
  return defaultTitle;
} // getDefaultTitle()

// ************************************************************************

/*!
*/

const char *
SoQtPlaneViewer::getDefaultIconTitle( // virtual
  void ) const
{
  static const char defaultIconTitle[] = "";
  return defaultIconTitle;
} // getDefaultIconTitle()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::processEvent( // virtual
  QEvent * event )
{
  if ( this->processCommonEvents( event ) )
    return;

  // get mouse coordinates
  QWidget * canvas = this->getRenderAreaWidget();
  SbVec2s canvassize = this->getGlxSize();
  SbVec2s mousepos( canvas->mapFromGlobal(QCursor::pos()).x(),
                    canvas->mapFromGlobal(QCursor::pos()).y() );
  mousepos[1] = canvassize[1] - mousepos[1];
  SbVec2f norm_mousepos( mousepos[0]/float(canvassize[0]),
                         mousepos[1]/float(canvassize[1]) );

#if QT_VERSION < 200
  int eventtype = event->type();
#else // Qt 2.0
  QEvent::Type eventtype = event->type();
#endif // Qt 2.0

  switch ( eventtype ) {

  case Event_MouseButtonDblClick:
  case Event_MouseButtonPress:
    {
      switch ( ((QMouseEvent *) event)->button() ) {
      case LeftButton:
        if ( this->mode == IDLE_MODE ) {
          this->interactiveCountInc();
          this->mode = DOLLY_MODE;
        } else if ( this->mode == SEEK_WAIT_MODE ) {
          this->interactiveCountInc();
          this->seekToPoint( mousepos );
        }
        break;

      case MidButton:
        if ( this->mode == IDLE_MODE ) {
          this->interactiveCountInc();
          this->mode = TRANSLATE_MODE;
        } else if ( this->mode == ROTZ_WAIT_MODE ) {
          this->mode = ROTZ_MODE;
        }

        break;

      default:
        break;

      } // switch ( event->button() )

      break;
    }

  case Event_MouseButtonRelease:
    {
      QMouseEvent * be = (QMouseEvent *) event;
      if ( be->button() != LeftButton && be->button() != MidButton )
        break;

      if ( this->mode != IDLE_MODE &&
           this->mode != ROTZ_MODE ) {
        this->interactiveCountDec();
        this->mode = IDLE_MODE;
      }

//    this->setModeFromState( be->state() & ~be->button() );
      break;
    }

  case Event_MouseMove:
    {
      switch ( this->mode ) {
  
      case DOLLY_MODE:
        if ( norm_mousepos[1] != this->prevMousePosition[1] )
          this->rightWheelMotion( this->getRightWheelValue() +
            (this->prevMousePosition[1] - norm_mousepos[1]) * 10.0f );
        break;

      case TRANSLATE_MODE:
        if ( (norm_mousepos[0] != this->prevMousePosition[0]) ||
             (norm_mousepos[1] != this->prevMousePosition[1]) ) {
          float diffx = (norm_mousepos[0] - this->prevMousePosition[0]) * 2.5f;
          float diffy = (norm_mousepos[1] - this->prevMousePosition[1]) * 2.5f;
          this->leftWheelMotion( this->getLeftWheelValue() - diffy );
          this->bottomWheelMotion( this->getBottomWheelValue() + diffx );
        }
        break;

      case ROTZ_MODE:
        if ( (norm_mousepos[0] != this->prevMousePosition[0]) ||
             (norm_mousepos[1] != this->prevMousePosition[1]) )
          common->setPointerLocation( mousepos );
          common->rotateZ( common->getPointerOrigoMotionAngle() );
        break;

      default: // include default to avoid compiler warnings.
        break;

      } // switch ( this->mode )

      break;
    }

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
      do {
        QKeyEvent * keyevent = (QKeyEvent *) event;
        if ( keyevent->key() == Key_Control ) {
           this->mode = ROTZ_WAIT_MODE;
           this->interactiveCountInc();
        }
      } while ( FALSE );
      break;

    case Event_KeyRelease:
      do {
        QKeyEvent * keyevent = (QKeyEvent *) event;
        if ( keyevent->key() == Key_Control ) {
           this->mode = IDLE_MODE;
//           this->interactiveCountDec();
        }
      } while ( FALSE );

      break;

    default:
//      SoDebugError::postInfo( "SoQtPlaneViewer::processEvent",
//        "event not caught" );
      break;

  } // switch ( eventtype )

  this->prevMousePosition = norm_mousepos;
} // processEvent()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::setSeekMode( // virtual
  SbBool enable )
{
  inherited::setSeekMode( enable );
} // setSeekMode()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::actualRedraw( // virtual
  void )
{
  inherited::actualRedraw();
//  if ( this->isFeedbackVisible() )
//    this->drawAxisCross();
} // actualRedraw()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::leftWheelMotion( // virtual
  float value )
{
  common->translateY( value - this->getLeftWheelValue() );
  inherited::leftWheelMotion( value );
} // leftWheelMotion()

/*!
*/

void
SoQtPlaneViewer::bottomWheelMotion( // virtual
  float value )
{
  common->translateX( value - this->getBottomWheelValue() );
  inherited::bottomWheelMotion( value );
} // bottomWheelMotion()

/*!
*/

void
SoQtPlaneViewer::rightWheelMotion( // virtual
  float value )
{
  this->zoom( this->getRightWheelValue() - value );
  inherited::rightWheelMotion( value );
} // rightWheelMotion()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::createPrefSheet( // virtual
  void )
{
} // createPrefSheet()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::createViewerButtons( // virtual
  QWidget * parent,
  SbPList * buttons )
{
  inherited::createViewerButtons( parent, buttons );

  // add X, Y, Z viewpoint buttons
  this->buttons.x = new QPushButton( parent );
  this->buttons.x->setFocusPolicy( QWidget::NoFocus );
  this->buttons.x->setToggleButton( FALSE );
  this->buttons.x->setPixmap( QPixmap( (const char **) x_xpm ) );
  QObject::connect( this->buttons.x, SIGNAL(clicked()),
                    this, SLOT(xClicked()) );
  buttons->append( this->buttons.x );
  this->buttons.y = new QPushButton( parent );
  this->buttons.y->setFocusPolicy( QWidget::NoFocus );
  this->buttons.y->setToggleButton( FALSE );
  this->buttons.y->setPixmap( QPixmap( (const char **) y_xpm ) );
  QObject::connect( this->buttons.y, SIGNAL(clicked()),
                    this, SLOT(yClicked()) );
  buttons->append( this->buttons.y );
  this->buttons.z = new QPushButton( parent );
  this->buttons.z->setFocusPolicy( QWidget::NoFocus );
  this->buttons.z->setToggleButton( FALSE );
  this->buttons.z->setPixmap( QPixmap( (const char **) z_xpm ) );
  QObject::connect( this->buttons.z, SIGNAL(clicked()),
                    this, SLOT(zClicked()) );
  buttons->append( this->buttons.z );

  // add camera toggle button
  assert( this->pixmaps.perspective != NULL );
  assert( this->pixmaps.orthogonal != NULL );
  this->buttons.camera = new QPushButton( parent );
  this->buttons.camera->setFocusPolicy( QWidget::NoFocus );

  QPixmap * pixmap = NULL;
  SoType t = this->getCameraType();
  if (t.isDerivedFrom(SoOrthographicCamera::getClassTypeId()))
    pixmap = this->pixmaps.orthogonal;
  else if (t.isDerivedFrom(SoPerspectiveCamera::getClassTypeId()))
    pixmap = this->pixmaps.perspective;
  else assert(0 && "unsupported cameratype");

  this->buttons.camera->setPixmap( *pixmap );
  buttons->append( this->buttons.camera );

  QObject::connect( this->buttons.camera, SIGNAL(clicked()),
                    this, SLOT(cameraToggleClicked()) );

} // createViewerButtons()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::openViewerHelpCard( // virtual
  void )
{
} // openViewerHelpCard()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::computeSeekFinalOrientation( // virtual
  void )
{
} // computeSeekFinalOrientation()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::zoom(
  const float difference )
{
  SoCamera * camera = this->getCamera();
  assert( camera != NULL );

  SoType type = camera->getTypeId();
  float multiplicator = exp( difference ); // in the range of <0, ->>

  if ( type.isDerivedFrom( SoOrthographicCamera::getClassTypeId() ) ) {
    SoOrthographicCamera * orthocam = (SoOrthographicCamera *) camera;
    orthocam->height = orthocam->height.getValue() * multiplicator;
  } else if ( type.isDerivedFrom( SoPerspectiveCamera::getClassTypeId() ) ) {
    float oldfocaldist = camera->focalDistance.getValue();
    camera->focalDistance = oldfocaldist * multiplicator;
    SbVec3f direction;
    camera->orientation.getValue().multVec( SbVec3f( 0, 0, -1 ), direction );
    camera->position = camera->position.getValue() +
      (camera->focalDistance.getValue() - oldfocaldist) * -direction;
  } else {
    assert( 0 && "impossible" );
  }
} // zoom()

// ************************************************************************

/*!
  \internal
*/

void
SoQtPlaneViewer::xClicked(
  void )
{
  common->viewPlaneX( this->getCamera() );
} // xClicked()

/*!
  \internal
*/

void
SoQtPlaneViewer::yClicked(
  void )
{
  common->viewPlaneY( this->getCamera() );
} // yClicked()

/*!
  \internal
*/

void
SoQtPlaneViewer::zClicked(
  void )
{
  common->viewPlaneZ( this->getCamera() );
} // zClicked()

/*!
  \internal
*/

void
SoQtPlaneViewer::cameraToggleClicked(
  void )
{
  if ( this->getCamera() ) this->toggleCameraType();
} // cameraToggleClicked()

// ************************************************************************

/*!
  \internal
*/

void
SoQtPlaneViewer::visibilityCB( // static
  void * data,
  SbBool visible )
{
  SoQtPlaneViewer * thisp = (SoQtPlaneViewer *) data;

/* examiner viewer does this, we don't have to...
  if ( thisp->isAnimating() ) {
    if ( visible )
      thisp->timerTrigger->schedule();
    else
      thisp->timerTrigger->unschedule();
  }
*/
} // visibilityCB()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::setModeFromState( // private
  unsigned int state )
{
  PlaneViewerMode mode = IDLE_MODE;

  const unsigned int maskedstate =
    state & (LeftButton|MidButton|ControlButton);

  switch ( maskedstate ) {
  case 0:
    mode = IDLE_MODE;
    break;

  case LeftButton:
    mode = TRANSLATE_MODE;
    break;

  case MidButton:
  case (LeftButton|ControlButton):
    mode = DOLLY_MODE;
    break;

  case ControlButton:
    mode = ROTZ_WAIT_MODE;
    break;

  case (MidButton|ControlButton):
  case (LeftButton|MidButton|ControlButton):
    mode = ROTZ_MODE;
    break;

  default:
    SoDebugError::postWarning( "SoQtPlaneViewer::setModeFromState",
      "state not handled: %d", maskedstate );
    break;

  } // switch ( maskedstate )

  this->setMode( mode );
} // setModeFromState()

/*!
*/

void
SoQtPlaneViewer::setMode(
  PlaneViewerMode mode )
{
  // FIXME: set cursor...

  switch ( mode ) {
  case IDLE_MODE:
    while ( this->getInteractiveCount() )
      this->interactiveCountDec();
    break;

  case TRANSLATE_MODE:
  case DOLLY_MODE:
  case ROTZ_MODE:
    while ( this->getInteractiveCount() )
      this->interactiveCountDec();
    break;

  default:
    break;
  } // switch ( mode )

  this->mode = mode;
} // setMode()

// ************************************************************************
