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
  \class SoQtGLWidget SoQtGLWidget.h Inventor/Qt/SoQtGLWidget.h
  \brief The SoQtGLWidget class contains an OpenGL canvas.

  TODO:
  - doc on how this needs Qt OpenGL extension library, w/html links to Qt doc
  - use the add/removeVisibilityCB methods in SoQtComponent?
  - there's a heap of methods missing from SoXtGLWidget, none (or few)
    of which seems relevant for the Qt implementation -- check the truth of
    this statement
 */

#include <assert.h>

// FIXME: get rid of this before 1.0 release by converting everything
// to Qt version 2.x API? 19990630 mortene.
#include <qevent.h>
#include <qframe.h>
#if QT_VERSION >= 200
#include <q1xcompatibility.h>
#endif // Qt v2.x

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/misc/SoBasic.h>

#include <soqtdefs.h>
#include <Inventor/Qt/SoQtBasic.h>
#include <Inventor/Qt/widgets/SoQtGLArea.h>
#include <Inventor/Qt/SoQtGLWidget.h>

#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H


/*!
  \fn virtual void SoQtGLWidget::redraw(void)
  This method will be called when we need a redraw. It must be overloaded in
  non-abstract subclasses.
 */
/*!
  \var SbBool SoQtGLWidget::waitForExpose
  If this is \c TRUE, rendering should not be done yet. Upon the first
  expose event of a newly created OpenGL widget, this variable will
  be set to \c FALSE.
*/
/*!
  \var SbBool SoQtGLWidget::drawToFrontBuffer
  If this is \c TRUE, rendering will happen in the front buffer even
  if the current rendering mode is double buffered.
*/


static const int SO_BORDER_THICKNESS = 2;

/*!
  FIXME: write function documentation
*/
SoQtGLWidget::SoQtGLWidget(QWidget * const parent, const char * const /*name*/,
                           const SbBool buildInsideParent, const int glModes,
                           const SbBool buildNow)
  : inherited(parent), waitForExpose(TRUE), drawToFrontBuffer(FALSE)
{
  this->glLockLevel = 0;
  this->glmodebits = glModes;

  this->glparent = NULL;
  this->glwidget = NULL;
  this->borderwidget = NULL;

  if (QGLFormat::hasOpenGL()) {
    if(buildNow) this->buildWidget(buildInsideParent ? parent : NULL);
  }
  else {
    SoDebugError::post("SoQtGLWidget::SoQtGLWidget",
                       "OpenGL not available on your display!");
  }

  this->properties.mouseinput = FALSE;
  this->properties.keyboardinput = FALSE;

  this->borderthickness = 0;
}

/*!
  FIXME: write function documentation
*/
QWidget *
SoQtGLWidget::buildWidget(QWidget * parent)
{
//  this->borderwidget = new QWidget(parent);
//  this->borderwidget->setBackgroundColor( QColor( 0, 0, 0 ) );

  this->borderwidget = new QFrame(parent);
  this->borderwidget->setFrameStyle( QFrame::Panel | QFrame::Raised );
  this->borderwidget->setLineWidth( SO_BORDER_THICKNESS );
  this->borderwidget->move( 0, 0 );

  QGLFormat f;
  f.setDoubleBuffer((this->glmodebits & SO_GLX_DOUBLE) ? TRUE : FALSE);
  f.setDepth((this->glmodebits & SO_GLX_ZBUFFER) ? TRUE : FALSE);
  f.setRgba((this->glmodebits & SO_GLX_RGB) ? TRUE : FALSE);
  f.setStereo((this->glmodebits & SO_GLX_STEREO) ? TRUE : FALSE);
#if HAVE_QGLFORMAT_SETOVERLAY
  f.setOverlay( FALSE ); // at the time being...
#endif // HAVE_QGLFORMAT_SETOVERLAY

  // FIXME: the SO_GLX_OVERLAY bit is not considered (Qt doesn't seem
  // to support overlay planes -- check this with the Qt FAQ or
  // mailing list archives). 990210 mortene.

  // FIXME, update: overlay planes are supported with Qt 2.x. 19991218 mortene.

  this->glwidget = new SoQtGLArea( &f, this->borderwidget );
  QRect frameInterior( borderwidget->contentsRect() );
  this->glwidget->move( frameInterior.topLeft() );
  this->glwidget->resize( frameInterior.size() );

  if ( ! this->glwidget->isValid() ) {
    SoDebugError::post("SoQtGLWidget::SoQtGLWidget",
                       "Your graphics hardware is weird! Can't use it.");
  }


  QObject::connect( this->glwidget, SIGNAL(init_sig()), this, SLOT(gl_init()));
  QObject::connect( this->glwidget, SIGNAL(reshape_sig(int, int)),
                   this, SLOT(gl_reshape(int, int)));
  QObject::connect( this->glwidget, SIGNAL(expose_sig()), this, SLOT(gl_exposed()));

  this->glwidget->setMouseTracking( TRUE );

  this->glparent = parent;

  if ( parent != NULL )
    parent->installEventFilter( this );
  this->glwidget->installEventFilter( this );

#if 0 // debug
  SoDebugError::postInfo("SoQtGLWidget::buildWidget",
                         "installeventfilter, parent: %p, glwidget: %p",
                         parent, this->glwidget);
#endif // debug


  this->setBaseWidget( this->borderwidget );
  this->subclassInitialized();
  return this->glwidget;
}

/*!
  FIXME: write function documentation
*/

bool
SoQtGLWidget::eventFilter(QObject * obj, QEvent * e)
{

#if 0 // debug
  SoDebugError::postInfo("SoQtGLWidget::eventFilter", "obj: %p", obj);
#endif // debug

#if 0 // debug
  switch (e->type()) {
  case Event_MouseButtonPress:
//      SoDebugError::postInfo("SoQtGLWidget::eventFilter", "button press");
    break;
  case Event_MouseButtonRelease:
//      SoDebugError::postInfo("SoQtGLWidget::eventFilter", "button release");
    break;
  case Event_MouseButtonDblClick:
//      SoDebugError::postInfo("SoQtGLWidget::eventFilter", "dbl click");
    break;
  case Event_MouseMove:
//      SoDebugError::postInfo("SoQtGLWidget::eventFilter", "mousemove");
    break;
  case Event_Paint:
    SoDebugError::postInfo("SoQtGLWidget::eventFilter", "paint");
    break;
  case Event_Resize:
    SoDebugError::postInfo("SoQtGLWidget::eventFilter", "resize");
    break;
  case Event_FocusIn:
  case Event_FocusOut:
  case Event_Enter:
  case Event_Leave:
  case Event_Move:
  case Event_LayoutHint:
  case Event_ChildInserted:
  case Event_ChildRemoved:
    // ignored
    break;
  default:
    SoDebugError::postInfo("SoQtGLWidget::eventFilter", "type %d", e->type());
    break;
  }
#endif // debug

  SbBool stopevent = FALSE;


  SbBool keyboardevent =
    ( e->type() == Event_KeyPress) || (e->type() == Event_KeyRelease);
#if QT_VERSION >= 200
  // Qt 2 introduced "accelerator" type keyboard events.
  keyboardevent = keyboardevent ||
    (e->type() == QEvent::Accel) || (e->type() == QEvent::AccelAvailable);
#endif // Qt v2.0

  if (keyboardevent) {
    // Redirect absolutely all keyboard events to the GL canvas
    // widget, ignoring the current focus setting.
    obj = this->glwidget;
    // isAccepted() usually defaults to TRUE, but we need to manually
    // set this (probably due to the way we intercept all events
    // through this eventfilter).
    ((QKeyEvent *)e)->accept();
  }


  if ( obj == (QObject *) this->glparent ) {
    if (e->type() == Event_Resize) {
      QResizeEvent * r = (QResizeEvent *)e;
#if 0  // debug
      SoDebugError::postInfo("SoQtGLWidget::eventFilter",
                             "resize %p: (%d, %d)",
                             this->glwidget,
                             r->size().width(), r->size().height());
#endif // debug

      this->borderwidget->resize(r->size());
//      int newwidth = r->size().width() - 2 * this->borderthickness;
//      int newheight = r->size().height() - 2 * this->borderthickness;

//      this->glwidget->setGeometry( this->borderthickness,
//                                   this->borderthickness,
//                                   newwidth, newheight );
      this->glwidget->setGeometry( this->borderwidget->contentsRect() );
  
      int newwidth = r->size().width();
      int newheight = r->size().height();
      this->sizeChanged( SbVec2s(newwidth, newheight) );
#if 0 // debug
      SoDebugError::postInfo("SoQtGLWidget::eventFilter", "resize done");
#endif // debug
    }
  } else if ( obj == (QObject *) this->glwidget ) {
#if 0  // debug
    if (e->type() == Event_Resize)
      SoDebugError::postInfo("SoQtGLWidget::eventFilter", "gl widget resize");
#endif // debug
    // Pass this on further down the inheritance hierarchy of the SoQt
    // components.
    this->processEvent( e );
  } else {
    // Handle in superclass.
    stopevent = inherited::eventFilter( obj, e );
  }

  return stopevent;
}

/*!
  Specify that there should be a border around the OpenGL canvas (or not).

  \sa isBorder()
 */
void
SoQtGLWidget::setBorder(const SbBool enable)
{
  this->borderthickness = (enable ? SO_BORDER_THICKNESS : 0);
  // FIXME: reshape glwidget if built
}

/*!
  Returns whether or not there's a border around the OpenGL canvas.

  \sa setBorder()
 */

SbBool
SoQtGLWidget::isBorder(void) const
{
  return this->borderthickness ? TRUE : FALSE;
}

/*!
  Switch between single and double buffer mode for the OpenGL canvas.
  The default is to use a single buffer canvas.

  \sa isDoubleBuffer()
 */
void
SoQtGLWidget::setDoubleBuffer(const SbBool enable)
{
  if (this->glwidget) {
//    if (enable != this->getQtGLArea()->doubleBuffer()) {
    if ( enable != (SbBool) this->getQtGLArea()->doubleBuffer() ) {
      QGLFormat format = this->getQtGLArea()->format();
      format.setDoubleBuffer(enable);
      this->getQtGLArea()->setFormat(format);
      if(!this->getQtGLArea()->isValid()) {
        SoDebugError::post("SoQtGLWidget::setDoubleBuffer",
                           "Couldn't switch to %s buffer mode. "
                           "Falling back on %s buffer.",
                           enable ? "double" : "single",
                           enable ? "single" : "double");
        format.setDoubleBuffer(!enable);
        this->getQtGLArea()->setFormat(format);
      }

      if (this->glwidget->doubleBuffer()) this->glmodebits |= SO_GLX_DOUBLE;
      else this->glmodebits &= ~SO_GLX_DOUBLE;
    }
  }
  else {
    if (enable) this->glmodebits |= SO_GLX_DOUBLE;
    else this->glmodebits &= ~SO_GLX_DOUBLE;
  }
}

/*!
  Returns the status of the buffer mode.

  \sa setDoubleBuffer()
 */
SbBool
SoQtGLWidget::isDoubleBuffer(void) const
{
  if(this->glwidget) return this->glwidget->doubleBuffer();
  else return (this->glmodebits & SO_GLX_DOUBLE) ? TRUE : FALSE;
}

/*!
  FIXME: write function documentation
*/
void
SoQtGLWidget::setDrawToFrontBufferEnable(const SbBool enable)
{
  this->drawToFrontBuffer = enable;
}

/*!
  FIXME: write function documentation
*/
SbBool
SoQtGLWidget::isDrawToFrontBufferEnable(void) const
{
  return this->drawToFrontBuffer;
}

/*!
  FIXME: write function documentation
*/
void
SoQtGLWidget::setGlxSize(
  const SbVec2s size )
{
  this->setGLSize( size );
} // setGlxSize()

void
SoQtGLWidget::setGLSize(
  const SbVec2s size )
{
  assert(this->borderwidget);
//  this->borderwidget->resize( size[0] + this->borderthickness * 2,
//                              size[1] + this->borderthickness * 2 );
  this->borderwidget->resize( size[0] + this->borderwidget->frameWidth(),
                              size[1] + this->borderwidget->frameWidth() );
} // setGLSize()


/*!
  Return the dimensions of the OpenGL canvas.
*/

SbVec2s
SoQtGLWidget::getGlxSize(
  void ) const
{
  return this->getGLSize();
} // getGlxSize()

SbVec2s
SoQtGLWidget::getGLSize(
  void ) const
{
  assert( this->glwidget != NULL );
  return SbVec2s( this->glwidget->width(), this->glwidget->height() );
}

/*!
  Return the aspect ratio of the OpenGL canvas.
 */
float
SoQtGLWidget::getGlxAspectRatio(void) const
{
  return this->getGLAspectRatio();
}

float
SoQtGLWidget::getGLAspectRatio(
  void ) const
{
  return float(this->glwidget->width())/float(this->glwidget->height());
}  // getGLAspectRatio()

/*!
  Returns a pointer to the Qt QGLWidget.
 */
SoQtGLArea *
SoQtGLWidget::getQtGLArea(void)
{
  return (SoQtGLArea *) this->glwidget;
} // getQtGLArea()

QWidget *
SoQtGLWidget::getGLWidget(void)
{
  return this->glwidget;
} // getGLWidget()


/*!
  FIXME: write function documentation
*/
void
SoQtGLWidget::sizeChanged(
  const SbVec2s size )
{
  // nothing to do
} // sizeChanged()

/*!
  This is the method which gets called whenever the OpenGL widget
  changes in any way. Should be overloaded in subclasses.

  \sa sizeChanged()
 */
void
SoQtGLWidget::widgetChanged(
  QWidget * w )
{
}

/*!
  FIXME: write function documentation
*/
void
SoQtGLWidget::processEvent(QEvent * /*anyevent*/)
{
  SoDebugError::postInfo( "processEvent", "called" );
  // FIXME: anything to do here? 981029 mortene.
}

// *************************************************************************

void
SoQtGLWidget::glLock(
  void )
{
  assert( this->glwidget != NULL );
  this->glLockLevel++;
  assert( this->glLockLevel < 10 && "must be programming error" );
  ((SoQtGLArea *)this->glwidget)->makeCurrent();
} // glLock()

void
SoQtGLWidget::glUnlock(
  void )
{
  this->glLockLevel--;
  assert( this->glLockLevel >= 0 && "programming error" );
} // glUnlock()

void
SoQtGLWidget::glSwapBuffers(
  void )
{
  assert( this->glwidget != NULL );
  assert( this->glLockLevel > 0 );
#if SOQT_DEBUG && 0 // debug
  SoDebugError::postInfo( "SoQtGLWidget::glSwapBuffers", "start" );
#endif // debug
  ((SoQtGLArea *)this->glwidget)->swapBuffers();
#if SOQT_DEBUG && 0 // debug
  SoDebugError::postInfo( "SoQtGLWidget::glSwapBuffers", "done" );
#endif // debug
} // glSwapBuffers()

void
SoQtGLWidget::glFlushBuffer(
  void )
{
  assert( this->glLockLevel > 0 );
  SOQT_STUB();
} // glFlushBuffer()

void
SoQtGLWidget::glInit( // virtual
  void )
{
#if 0 // SOQT_DEBUG
  SoDebugError::postInfo( "SoQtGLWidget::glInit", "called" );
#endif // 0 was SOQT_DEBUG

  glLock();
  // Need to set this explicitly when running on top of Open Inventor,
  // as it seems to have been forgotten there.
  glEnable( GL_DEPTH_TEST );
  glUnlock();
} // glInit()

void
SoQtGLWidget::gl_init( // slot
  void )
{
  this->glInit();
} // gl_init()

void
SoQtGLWidget::glReshape( // virtual
  int width,
  int height )
{
#if 0 // SOQT_DEBUG
  SoDebugError::postInfo( "SoQtGLWidget::glReshape", "called" );
#endif // 0 was SOQT_DEBUG
} // glReshape()

void
SoQtGLWidget::gl_reshape( // slot
  int width,
  int height )
{
  this->sizeChanged( SbVec2s( width, height ) );
  this->glReshape( width, height );
} // gl_reshape()

void
SoQtGLWidget::glRender( // virtual
  void )
{
#if 0 // SOQT_DEBUG
  SoDebugError::postInfo( "SoQtGLWidget::glRender", "called" );
#endif // 0 was SOQT_DEBUG
  // nada
  this->redraw();
} // glRender()

void
SoQtGLWidget::gl_exposed( // slot
  void )
{
  this->glRender();
  this->waitForExpose = FALSE; // Gets flipped from TRUE on first expose.
} // gl_exposed()

// *************************************************************************
