/**************************************************************************
 *
 *  Copyright (C) 2000 by Systems in Motion.  All rights reserved.
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
 **************************************************************************/

static const char rcsid[] =
  "$Id$";

/*!
  \class SoQtPlaneViewer Inventor/Qt/viewers/SoQtPlaneViewer.h
  \brief The SoQtPlaneViewer class is yet to be documented...
  \ingroup soqtviewers
*/

#include <qevent.h>
#include <qpushbutton.h>
#include <qpixmap.h>
#include <q1xcompatibility.h>

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>

#include <Inventor/Qt/widgets/QtThumbwheel.h>

#include <Inventor/Qt/common/SoAnyPlaneViewer.h>
#include <Inventor/Qt/viewers/SoQtPlaneViewer.h>

#include "icons/ortho.xpm"
#include "icons/perspective.xpm"

// ************************************************************************

/*!
  The public constructor.
*/

SoQtPlaneViewer::SoQtPlaneViewer(
  QWidget * parent = NULL,
  const char * const name = NULL, 
  SbBool buildInsideParent = TRUE,
  SoQtFullViewer::BuildFlag flag = BUILD_ALL, 
  SoQtViewer::Type type = BROWSER )
: inherited( parent, name, buildInsideParent, flag, type, FALSE )
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
  SbBool buildInsideParent, 
  SoQtFullViewer::BuildFlag flag, 
  SoQtViewer::Type type, 
  SbBool buildNow )
: inherited( parent, name, buildInsideParent, flag, type, FALSE )
{
  this->constructor( buildNow );
} // SoQtPlaneViewer()

// ************************************************************************

/*!
*/

void
SoQtPlaneViewer::constructor( // private
  SbBool buildNow )
{
  this->planeViewerMode = WAITING_FOR_DOLLY_MODE;

  this->projector = new SbPlaneProjector;
  SbViewVolume vv;
  vv.ortho(-1, 1, -1, 1, -1, 1);
  this->projector->setViewVolume(vv);

/*  this->addVisibilityChangeCallback(SoQtPlaneViewer::visibilityCB, this); */

  this->setClassName("SoQtPlaneViewer");
  this->setLeftWheelString( "transY" );
  this->setBottomWheelString( "transX" );

  this->pixmaps.orthogonal = new QPixmap( (const char **) ortho_xpm );
  this->pixmaps.perspective = new QPixmap( (const char **) perspective_xpm );

  if ( buildNow )
    this->setBaseWidget( this->buildWidget( this->getParentWidget() ) );

  this->setSize( SbVec2s( 550, 450 ) ); // extra buttons -> more height
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

  this->getThumbwheel( LEFTDECORATION )->
    setRangeBoundaryHandling( QtThumbwheel::ACCUMULATE );
  this->getThumbwheel( BOTTOMDECORATION )->
    setRangeBoundaryHandling( QtThumbwheel::ACCUMULATE );
  
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
        if ( this->planeViewerMode == WAITING_FOR_DOLLY_MODE ) {
          this->interactiveCountInc();
          this->planeViewerMode = DOLLY_MODE;
        } else if ( this->planeViewerMode == WAITING_FOR_SEEK_MODE ) {
          this->interactiveCountInc();
          this->seekToPoint( mousepos );
        }
        break;

      case MidButton:
        if ( this->planeViewerMode == WAITING_FOR_DOLLY_MODE ) {
          this->interactiveCountInc();
          this->planeViewerMode = TRANSLATE_MODE;
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

      this->interactiveCountDec();
      this->planeViewerMode = WAITING_FOR_DOLLY_MODE;

//    this->setModeFromState( be->state() & ~be->button() );
      break;
    }

  case Event_MouseMove:
    {
      switch ( this->planeViewerMode ) {
  
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

/*
      case DRAGGING:
        if (!this->spindetecttimer) this->spindetecttimer = new QTimer;
        this->spindetecttimer->start(0, TRUE);
        this->spin(norm_mousepos);
        break;

      case PANNING:
        this->pan(norm_mousepos);
        break;
*/

      default: /* include default to avoid compiler warnings. */
        break;

      } // switch ( this->planeViewerMode )

      break;
    }

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
  inherited::leftWheelMotion(
    SoAnyPlaneViewer::transYWheelMotion( value, this->getLeftWheelValue(),
                                         this->getCamera() ) );
} // leftWheelMotion()

/*!
*/

void
SoQtPlaneViewer::bottomWheelMotion( // virtual
  float value )
{
  inherited::bottomWheelMotion(
    SoAnyPlaneViewer::transXWheelMotion( value, this->getBottomWheelValue(),
                                         this->getCamera() ) );
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
  // add X, Y, Z viewpoint buttons
  inherited::createViewerButtons( parent, buttons );
  this->buttons.x = new QPushButton( parent );
  this->buttons.x->setFocusPolicy( QWidget::NoFocus );
  this->buttons.x->setText( QString( "X" ) );
  buttons->append( this->buttons.x );
  this->buttons.y = new QPushButton( parent );
  this->buttons.y->setFocusPolicy( QWidget::NoFocus );
  this->buttons.y->setText( QString( "Y" ) );
  buttons->append( this->buttons.y );
  this->buttons.z = new QPushButton( parent );
  this->buttons.z->setFocusPolicy( QWidget::NoFocus );
  this->buttons.z->setText( QString( "Z" ) );
  buttons->append( this->buttons.z );
  // add camera toggle button
  assert( this->pixmaps.perspective != NULL );
  assert( this->pixmaps.orthogonal != NULL );
  this->buttons.camera = new QPushButton( parent );
  this->buttons.camera->setFocusPolicy( QWidget::NoFocus );
  QPixmap * pixmap = this->pixmaps.orthogonal;
  SoCamera * cam = this->getCamera();
  if ( cam != NULL ) {
    SoType type = cam->getTypeId();
    if ( type.isDerivedFrom(SoOrthographicCamera::getClassTypeId()) )
      pixmap = this->pixmaps.orthogonal;
    else if ( type.isDerivedFrom(SoPerspectiveCamera::getClassTypeId()) )
      pixmap = this->pixmaps.perspective;
    else
      assert( 0 && "impossible" );
  }
  this->buttons.camera->setPixmap( *pixmap );
  buttons->append( this->buttons.camera );

  QObject::connect( this->buttons.camera, SIGNAL(clicked()),
                    this, SLOT(cameratoggleClicked()) );

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
SoQtPlaneViewer::cameratoggleClicked()
{
  this->toggleCameraType();
} // cameratoggleClicked()

// ************************************************************************
