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

/*!
  \class SoQtGLWidget SoQtGLWidget.h Inventor/Qt/SoQtGLWidget.h
  \brief The SoQtGLWidget class contains the GL canvas widget used for
  rendering.

  TODO:
  - doc on how this needs Qt OpenGL extension library, w/html links to Qt doc
  - use the add/removeVisibilityCB methods in SoQtComponent?
  - "3D look" on border, like in OIV
  - there's a heap of methods missing from SoXtGLWidget, none (or few)
    of which seems relevant for the Qt implementation -- check the truth of
    this statement
 */

#include <Inventor/Qt/SoQtGLWidget.h>
#include <Inventor/errors/SoDebugError.h>
#include <assert.h>

// FIXME: get rid of this before 1.0 release (convert everything to Qt
// version 2.x API)? 19990630 mortene.
#if QT_VERSION >= 200
#include <q1xcompatibility.h>
#endif // Qt v2.x


/*!
  \fn virtual void SoQtGLWidget::redraw(void)
  This method will be called when we need a redraw. It must be overloaded in
  non-abstract subclasses.
 */
/*!
  \var SbBool SoQtGLWidget::drawToFrontBuffer
  FIXME: write doc
*/


static const int SO_BORDER_THICKNESS = 2;

// debug
#define SOQTGL_RESIZE_DEBUG 0


/*!
  FIXME: write function documentation
*/
SoQtGLWidget::SoQtGLWidget(QWidget * const parent, const char * const name, 
			   const SbBool buildInsideParent, const int glModes, 
			   const SbBool buildNow)
  : inherited(parent)
{
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
  this->properties.drawfrontbuff = TRUE;

  this->borderthickness = 0;
}

/*!
  FIXME: write function documentation
*/
QWidget *
SoQtGLWidget::buildWidget(QWidget * parent)
{
  this->borderwidget = new QWidget(parent);

  QGLWidget * w = new PrivateGLWidget(this, this->borderwidget, NULL);
  
  QGLFormat f;
  f.setDoubleBuffer((this->glmodebits & SO_GLX_DOUBLE) ? TRUE : FALSE);
  f.setDepth((this->glmodebits & SO_GLX_ZBUFFER) ? TRUE : FALSE);
  f.setRgba((this->glmodebits & SO_GLX_RGB) ? TRUE : FALSE);
  f.setStereo((this->glmodebits & SO_GLX_STEREO) ? TRUE : FALSE);
  // FIXME: the SO_GLX_OVERLAY bit is not considered (Qt doesn't seem
  // to support overlay planes -- check this with the Qt FAQ or
  // mailing list archives). 990210 mortene.
  w->setFormat(f);

  if (!w->isValid()) {
    // FIXME: what should we do here if the requested mode is not
    // available?  990210 mortene.
    SoDebugError::post("SoQtGLWidget::SoQtGLWidget",
		       "Your graphics hardware is weird! Can't use it.");
  }


  QObject::connect(w, SIGNAL(do_repaint()),
		   this, SLOT(repaint_slot()));

  w->setMouseTracking(TRUE);

  this->glparent = parent;
  this->glwidget = w;

  if (parent) parent->installEventFilter(this);
  this->glwidget->installEventFilter(this);

#if 0 // debug
  SoDebugError::postInfo("SoQtGLWidget::buildWidget",
			 "installeventfilter, parent: %p, glwidget: %p",
			 parent, this->glwidget);
#endif // debug


  this->setBaseWidget(this->borderwidget);
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


  // Redirect keyboard events to the GL canvas widget (workaround for
  // problems with Qt focus policy).
  if ((e->type() == Event_KeyPress) || (e->type() == Event_KeyRelease))
    obj = this->glwidget;

  if (obj == (QObject *)this->glparent) {
    if (e->type() == Event_Resize) {
      QResizeEvent * r = (QResizeEvent *)e;
#if SOQTGL_RESIZE_DEBUG  // debug
      SoDebugError::postInfo("SoQtGLWidget::eventFilter",
			     "resize %p: (%d, %d)",
			     this->glwidget,
			     r->size().width(), r->size().height());
#endif // debug			 

      this->borderwidget->resize(r->size());
      int newwidth = r->size().width() - 2 * this->borderthickness;
      int newheight = r->size().height() - 2 * this->borderthickness;
      this->glwidget->setGeometry(this->borderthickness,
				  this->borderthickness,
				  newwidth, newheight);

      this->sizeChanged(SbVec2s(newwidth, newheight));
    }
  }
  else if (obj == (QObject *)this->glwidget) {
    // Pass this on further down the inheritance hierarchy of the SoQt
    // components.
    this->processEvent(e);
  }
  else {
    // Handle in superclass.
    return inherited::eventFilter(obj, e);
  }

  return FALSE;
}

/*!
  Specify that there should be a border around the OpenGL canvas (or not).

  \sa isBorder()
 */
void 
SoQtGLWidget::setBorder(const SbBool enable)
{
  this->borderthickness = (enable ? SO_BORDER_THICKNESS : 0);
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
    if (enable != this->getQGLWidget()->doubleBuffer()) {
      QGLFormat format = this->getQGLWidget()->format();
      format.setDoubleBuffer(enable);
      this->getQGLWidget()->setFormat(format);
      if(!this->getQGLWidget()->isValid()) {
	SoDebugError::post("SoQtGLWidget::setDoubleBuffer",
			   "Couldn't switch to %s buffer mode. "
			   "Falling back on %s buffer.",
			   enable ? "double" : "single",
			   enable ? "single" : "double");
	format.setDoubleBuffer(!enable);
	this->getQGLWidget()->setFormat(format);
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
  this->properties.drawfrontbuff = enable;
}

/*!
  FIXME: write function documentation
*/
SbBool
SoQtGLWidget::isDrawToFrontBufferEnable(void) const
{
  return this->properties.drawfrontbuff;
}

/*!
  FIXME: write function documentation
*/
void
SoQtGLWidget::setGlxSize(SbVec2s newSize)
{
  assert(this->borderwidget);

  this->borderwidget->resize(newSize[0] + this->borderthickness * 2,
			     newSize[1] + this->borderthickness * 2);
}

/*!
  Return the dimensions of the OpenGL canvas.
 */
const SbVec2s
SoQtGLWidget::getGlxSize(void) const
{
  return SbVec2s(this->glwidget->width(), this->glwidget->height());
}

/*!
  Return the aspect ratio of the OpenGL canvas.
 */
float
SoQtGLWidget::getGlxAspectRatio(void) const
{
  return float(this->glwidget->width())/float(this->glwidget->height());
}

/*!
  Returns a pointer to the Qt QGLWidget.
 */
QGLWidget *
SoQtGLWidget::getQGLWidget(void)
{
  return this->glwidget;
}

/*!
  FIXME: write function documentation
*/
void
SoQtGLWidget::sizeChanged(const SbVec2s & newSize)
{
}

/*!
  This is the method which gets called whenever the OpenGL widget
  changes in any way. Should be overloaded in subclasses.

  \sa sizeChanged()
 */
void
SoQtGLWidget::widgetChanged(void)
{
}

/*!
  \internal
 */
void
SoQtGLWidget::repaint_slot(void)
{
  // Set up the flag which will affect whether or not we're going to
  // render directly into the front buffer on expose-type events. This
  // must be done each time this events occurs, as the
  // drawToFrontBuffer flag is reset immediately to FALSE after a GL
  // redraw. See PrivateGLWidget::swapBuffers().
  this->drawToFrontBuffer = this->properties.drawfrontbuff;

  this->redraw();
}

/*!
  FIXME: write function documentation
*/
void
SoQtGLWidget::processEvent(QEvent * anyevent)
{
  // FIXME: anything to do here? 981029 mortene.
}


/* PrivateGLWidget implementation ************************************/

/*
  Constructor.

  The PrivateGLWidget is a class inheriting QGLWidget to be able to
  overload the "event catching" methods.
 */
PrivateGLWidget::PrivateGLWidget(SoQtGLWidget * owner,
				 QWidget * parent, const char * const name)
  : inherited(parent, name)
{
  this->owner = owner;
}

void 
PrivateGLWidget::initializeGL()
{
  inherited::initializeGL();
  this->setBackgroundMode(QWidget::NoBackground);
  this->setBackgroundColor(QColor(0,0,0));
  this->makeCurrent();

  // Need to call this explicitly, as it seems to have been forgotten
  // in Open Inventor.
  glEnable(GL_DEPTH_TEST);
}

/*
  Emit a signal whenever we need to repaint (usually (always?) because
  of expose events).
 */
void 
PrivateGLWidget::paintGL()
{
  inherited::paintGL();
#if 0 // debug
  SoDebugError::postInfo("PrivateGLWidget::paintGL", "");
#endif //debug
  emit this->do_repaint();
}

/*
  We need to overload QGLWidget::swapBuffers() like this to be able to
  heed the *DrawToFrontBufferEnable() setting.
 */
void
PrivateGLWidget::swapBuffers(void)
{
  if (this->owner->drawToFrontBuffer) {
    // FIXME: need some OpenGL trickery here to be able to draw to the
    // front buffer of a double buffered GL widget. 990209 mortene.
    inherited::swapBuffers(); // tmp hack
  }
  else {
    inherited::swapBuffers();
  }

  this->owner->drawToFrontBuffer = FALSE;
}
