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
#endif // SOQT_DEBUG

// *************************************************************************

/*!
  \class SoQtGLWidget SoQtGLWidget.h Inventor/Qt/SoQtGLWidget.h
  \brief The SoQtGLWidget class contains an OpenGL canvas.

  [FIXME: basic doc here]

  An important thing to know about embedding SoQtGLWidget derived
  components into other Qt widgets is that you need to set up "focus
  proxying" to have events still be set to the OpenGL canvas
  widget. This is true for both the SoQtRenderArea aswell as all the
  viewer components (like SoQtExaminerViewer, SoQtWalkViewer etc).  As
  an example, if you embed an SoQtExaminerViewer inside a QFrame like
  this:

  \code
  QMainWindow * toplevel = new QMainWindow;
  QFrame * frame = new QFrame(toplevel);
  SoQtExaminerViewer * viewer = new SoQtExaminerViewer(toplevelwidget);
  \endcode

  ..events from the keyboard will not always automatically be
  forwarded to the viewer OpenGL canvas. This is the code you need to
  add in this case:

  \code
  toplevel->setFocusProxy(viewer);
  \endcode
*/

//  FIXME:
//    - use the add/removeVisibilityCB methods in SoQtComponent?
//    - there's a heap of methods missing from SoXtGLWidget, none (or few)
//      of which seems relevant for the Qt implementation -- check the truth of
//      this statement

// *************************************************************************

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

/*!
  \fn void SoQtGLWidget::setStereoBuffer(SbBool flag)
  
  Sets whether OpenGL stereo buffers (quad buffer stereo) should be used.
*/

/*!
  \fn SbBool SoQtGLWidget::isStereoBuffer(void) const

  Returns whether OpenGL stereo buffers are being used.
*/

// *************************************************************************

#include <qevent.h>
#include <qframe.h>
#include <qmetaobject.h>
#include <moc_SoQtGLWidget.cpp>

#include <Inventor/Qt/SoAny.h>
#include <Inventor/Qt/SoQtBasic.h>
#include <Inventor/Qt/SoQtGLWidget.h>
#include <Inventor/Qt/widgets/SoQtGLArea.h>
#include <Inventor/SbTime.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/misc/SoBasic.h>
#include <soqtdefs.h>
#include <stdlib.h>

#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

// Abstract the overlay handling methods on QGLFormat and QGLWidget,
// because they may or may not be there depending on the version of
// the QGL library installed on the developer's system.
//
// (And we'd like to avoid scattering #ifdef's all over the code, so
// we make some new functions.)
//
#if HAVE_QGLFORMAT_SETOVERLAY
static inline bool QGLFormat_hasOverlay(const QGLFormat * f)
{ return f->hasOverlay(); }
static inline void QGLFormat_setOverlay(QGLFormat * f, bool enable)
{ f->setOverlay(enable); }
static inline void QGLFormat_makeOverlayCurrent(QGLWidget * w)
{ w->makeOverlayCurrent(); }
static inline const QGLContext * QGLWidget_overlayContext(QGLWidget * w)
{ return w->overlayContext(); }
static inline const QColor QGLContext_overlayTransparentColor(const QGLContext * c)
{ return c->overlayTransparentColor(); }
#else // !HAVE_QGLFORMAT_SETOVERLAY
static inline bool QGLFormat_hasOverlay(const QGLFormat * f) { return false; }
static inline void QGLFormat_setOverlay(QGLFormat * f, bool enable) { }
static inline void QGLFormat_makeOverlayCurrent(QGLWidget * w) { }
static inline const QGLContext * QGLWidget_overlayContext(QGLWidget * w) { return NULL; }
static inline const QColor QGLContext_overlayTransparentColor(const QGLContext * c) { return QColor(0, 0, 0); }
#endif // !HAVE_QGLFORMAT_SETOVERLAY


// For Qt v2.2.2 at least, Troll Tech forgot to include
// operator==(QGLFormat&,QGLFormat&) in the publicly exported API for
// MSWindows DLLs. This abstracts the workaround into a method
// QGLFormat_eq().
//
#if HAVE_QGLFORMAT_EQ_OP
static inline bool
QGLFormat_eq(const QGLFormat & a, const QGLFormat & b)
{
  return (a == b);
}
#else // !HAVE_QGLFORMAT_EQ_OP
static inline bool
QGLFormat_eq(const QGLFormat & a, const QGLFormat & b)
{
  if (a.doubleBuffer() != b.doubleBuffer()) return false;
  if (a.depth() != b.depth()) return false;
  if (a.rgba() != b.rgba()) return false;
  if (a.stereo() != b.stereo()) return false;
  if (QGLFormat_hasOverlay(&a) != QGLFormat_hasOverlay(&b)) return false;
  return true;
}
#endif // !HAVE_QGLFORMAT_EQ_OP

// *************************************************************************

// The private data for the SoQtGLWidget.

class SoQtGLWidgetP {
public:
  SoQtGLWidgetP(void)
    : borderthickness(0)
  {
  }

  static void GLAreaKeyEvent(QKeyEvent * e, void * userdata);

  SbVec2s glSize;
  SbBool wasresized;

  SoQtGLArea * currentglwidget;
  SoQtGLArea * previousglwidget;
  QWidget * glparent;
  QFrame * borderwidget;
  int borderthickness;
  QGLFormat * glformat;
};

#define PRIVATE(o) (o->pimpl)

// *************************************************************************

SOQT_OBJECT_ABSTRACT_SOURCE(SoQtGLWidget);

static const int SO_BORDER_THICKNESS = 2;

// *************************************************************************

/*!
  Protected constructor.
*/
SoQtGLWidget::SoQtGLWidget(QWidget * const parent,
                           const char * const name,
                           const SbBool embed,
                           const int glmodes,
                           const SbBool build)
  : inherited(parent, name, embed),
    waitForExpose(TRUE),
    drawToFrontBuffer(FALSE)
{
  PRIVATE(this) = new SoQtGLWidgetP;

  PRIVATE(this)->glSize = SbVec2s(0, 0);
  PRIVATE(this)->wasresized = FALSE;

  PRIVATE(this)->glformat = new QGLFormat;
  PRIVATE(this)->glformat->setDoubleBuffer((glmodes & SO_GL_DOUBLE) ? true : false);
  PRIVATE(this)->glformat->setDepth((glmodes & SO_GL_ZBUFFER) ? true : false);
  PRIVATE(this)->glformat->setRgba((glmodes & SO_GL_RGB) ? true : false);
  PRIVATE(this)->glformat->setStereo((glmodes & SO_GL_STEREO) ? true : false);
  bool enableoverlay = (glmodes & SO_GL_OVERLAY) ? true : false;
  QGLFormat_setOverlay(PRIVATE(this)->glformat, enableoverlay);

  PRIVATE(this)->glparent = NULL;
  PRIVATE(this)->currentglwidget = NULL;
  PRIVATE(this)->previousglwidget = NULL;
  PRIVATE(this)->borderwidget = NULL;

  if (! QGLFormat::hasOpenGL()) {
    SoDebugError::post("SoQtGLWidget::SoQtGLWidget",
                        "OpenGL not available!");
    // FIXME: this is not the way to handle this -- we should call the
    // fatal error handler. 20011112 mortene.
    return;
  }

  if (! build) { return; }

  this->setClassName("SoQtGLWidget");
  QWidget * parentwidget = this->getParentWidget();
  QWidget * widget = this->buildWidget(parentwidget);
  this->setBaseWidget(widget);
} // SoQtGLWidget()

// *************************************************************************

/*!
  Protected destructor.
*/
SoQtGLWidget::~SoQtGLWidget()
{
  // Don't delete the widgets we've allocated, as they are destructed
  // implicitly when their parent widgets die. (Destructing "our"
  // child widgets in this destructor can in fact lead to crashes due
  // to the widgets being deallocated multiple times.)

  if (PRIVATE(this)->currentglwidget) SoAny::si()->unregisterGLContext((void*) this);
  
  delete PRIVATE(this)->glformat;
  delete PRIVATE(this);
}

// *************************************************************************

/*!
  FIXME: write function documentation
*/
QWidget *
SoQtGLWidget::buildWidget(QWidget * parent)
{
  if (parent != NULL && this->isTopLevelShell()) {
    parent->installEventFilter(this);
  }

  PRIVATE(this)->borderwidget = new QFrame(parent);
  this->registerWidget(PRIVATE(this)->borderwidget);

  PRIVATE(this)->borderwidget->setFrameStyle(QFrame::Panel | QFrame::Raised);
  PRIVATE(this)->borderwidget->setLineWidth(PRIVATE(this)->borderthickness);
  PRIVATE(this)->borderwidget->setMargin(0);
  PRIVATE(this)->borderwidget->move(0, 0);

  // Remember our parent widget so we can use it in tests in the
  // eventFilter().
  PRIVATE(this)->glparent = parent;

  this->buildGLWidget();

  return PRIVATE(this)->borderwidget;
} // buildWidget()


// The GL widget rebuilding has been written to remember the previous
// GL widget, which might be swapped back in if it fits the wanted
// format.
//
// There are two reasons for keeping track of both the current and the
// previous widget:
//
//  1) efficiency; often one swaps back and forth between only two
//  different visuals -- like single and double buffering, or stereo
//  mode on and off
//
//  2) robustness; killing off the previous widget in the build-method
//  below has nasty sideeffects (like "random" coredumps), since the
//  Qt event loop might be using it
void
SoQtGLWidget::buildGLWidget(void)
{
  if (SOQT_DEBUG && 0) { // debug
    SoDebugError::postInfo("SoQtGLWidget::buildGLWidget",
                           "%s, %s, %s, %s, %s",
                           PRIVATE(this)->glformat->doubleBuffer() ? "double" : "single",
                           PRIVATE(this)->glformat->depth() ? "z-buffer" : "no z-buffer",
                           PRIVATE(this)->glformat->rgba() ? "RGBA" : "colorindex",
                           PRIVATE(this)->glformat->stereo() ? "stereo" : "mono",
                           QGLFormat_hasOverlay(PRIVATE(this)->glformat) ? "overlay" : "no overlay");
  }

  SoQtGLArea * wascurrent = PRIVATE(this)->currentglwidget;
  SoQtGLArea * wasprevious = PRIVATE(this)->previousglwidget;

  void * display = NULL;
  void * screen = NULL;

#if defined(_WS_X11_) // Qt defines this under X11
  // FIXME: should make context sharing work for other Qt
  // base-platforms (MSWin, MacOS X) aswell. 20020118 mortene.

  // the following Qt methods are only available under X11
  display = (void*) QPaintDevice::x11AppDisplay();
  screen = (void*) ((unsigned int) QPaintDevice::x11AppScreen());
#endif // _WS_X11_

  if (wascurrent) {
    // Do _not_ turn off mousetracking or remove the eventfilter, as
    // we'd loose events after the switch has happened if the user is
    // already interacting with the canvas (e.g. when starting a drag
    // in BUFFER_INTERACTIVE mode).
#if 0 // Keep this code around so we don't accidentally reinsert it. :^}
    wascurrent->removeEventFilter(this);
    wascurrent->setMouseTracking(FALSE);
#endif // Permanently disabled.
    QObject::disconnect(wascurrent, SIGNAL(expose_sig()), this, SLOT(gl_exposed()));
    QObject::disconnect(wascurrent, SIGNAL(init_sig()), this, SLOT(gl_init()));
    //    QObject::disconnect(wascurrent, SIGNAL(reshape_sig()), this, SLOT(gl_reshape()));
    PRIVATE(this)->previousglwidget = wascurrent;
  }

  if (wasprevious && QGLFormat_eq(*PRIVATE(this)->glformat, wasprevious->format())) {
    // Reenable the previous widget.
    if (PRIVATE(this)->currentglwidget) SoAny::si()->unregisterGLContext((void*) this);
    PRIVATE(this)->currentglwidget = wasprevious;
    SoAny::si()->registerGLContext((void*) this, display, screen);
    if (SOQT_DEBUG && 0) { // debug
      SoDebugError::postInfo("SoQtGLWidget::buildGLWidget",
                             "reused previously used GL widget");
    }
  }
  else {
    // Couldn't use the previous widget, make a new one.
    SoQtGLWidget * sharewidget = (SoQtGLWidget*) SoAny::si()->getSharedGLContext(display, screen);
    if (PRIVATE(this)->currentglwidget) SoAny::si()->unregisterGLContext((void*) this);
    PRIVATE(this)->currentglwidget =
      new SoQtGLArea(PRIVATE(this)->glformat,
                     PRIVATE(this)->borderwidget,
                     sharewidget ? (const QGLWidget*) sharewidget->getGLWidget() : NULL);
    PRIVATE(this)->currentglwidget->registerQKeyEventHandler(SoQtGLWidgetP::GLAreaKeyEvent,
                                                             this);
    SoAny::si()->registerGLContext((void *)this, display, screen);
    // Send this one to the final hunting grounds.    
    delete wasprevious;
  }

  if (!PRIVATE(this)->currentglwidget->isValid()) {
    SbString s =
      "Can't set up a valid OpenGL canvas, "
      "something is seriously wrong with your system!";
    SbBool handled =
      SoAny::si()->invokeFatalErrorHandler(s, SoQt::NO_OPENGL_CANVAS);
    if (handled) { return; }
    exit(1);
  }

  if (SOQT_DEBUG) { // Warn about requested features that we didn't get.
    QGLFormat * w = PRIVATE(this)->glformat; // w(anted)
    QGLFormat g = PRIVATE(this)->currentglwidget->format(); // g(ot)

#define GLWIDGET_FEATURECMP(_glformatfunc_, _truestr_, _falsestr_) \
  do { \
    if (w->_glformatfunc_() != g._glformatfunc_()) { \
      SoDebugError::postWarning("SoQtGLWidget::buildGLWidget", \
                                "wanted %s, but that is not supported " \
                                "by the OpenGL driver", \
                                w->_glformatfunc_() ? _truestr_ : _falsestr_); \
    } \
  } while (0)

    GLWIDGET_FEATURECMP(doubleBuffer, "doublebuffer visual", "singlebuffer visual");
    GLWIDGET_FEATURECMP(depth, "visual with depthbuffer", "visual without depthbuffer");
    GLWIDGET_FEATURECMP(rgba, "RGBA buffer", "colorindex buffer");
    GLWIDGET_FEATURECMP(stereo, "stereo buffers", "mono buffer");

    if (QGLFormat_hasOverlay(w) != QGLFormat_hasOverlay(&g)) {
      SoDebugError::postWarning("SoQtGLWidget::buildGLWidget",
                                "wanted %s, but that is not supported "
                                "by the OpenGL driver",
                                QGLFormat_hasOverlay(w) ?
                                "overlay plane(s)" :
                                "visual without overlay plane(s)");
    }
  }
#undef GLWIDGET_FEATURECMP

  *PRIVATE(this)->glformat = PRIVATE(this)->currentglwidget->format();

  int frame = this->isBorder() ? PRIVATE(this)->borderthickness : 0;
  PRIVATE(this)->currentglwidget->setGeometry(frame, frame,
                                              PRIVATE(this)->glSize[0] - 2*frame,
                                              PRIVATE(this)->glSize[1] - 2*frame);

  QObject::connect(PRIVATE(this)->currentglwidget, SIGNAL(init_sig()),
                   this, SLOT(gl_init()));
  //  QObject::connect(PRIVATE(this)->currentglwidget, SIGNAL(reshape_sig(int, int)),
  //                    this, SLOT(gl_reshape(int, int)));
  QObject::connect(PRIVATE(this)->currentglwidget, SIGNAL(expose_sig()),
                   this, SLOT(gl_exposed()));

  PRIVATE(this)->currentglwidget->setMouseTracking(TRUE);
  PRIVATE(this)->currentglwidget->installEventFilter(this);

  // Reset to avoid unnecessary scenegraph redraws.
  this->waitForExpose = TRUE;

  // We've changed to a new widget, so notify subclasses through this
  // virtual method.
  this->widgetChanged(PRIVATE(this)->currentglwidget);

  if (wascurrent) {
    // If we are rebuilding, we need to explicitly call show() here,
    // as no message to show will be given from an already visible
    // parent. (If the glwidget was built but not shown before the
    // rebuild, the call below doesn't do any harm, as the glwidget
    // still won't become visible until all parents are visible.)
    PRIVATE(this)->currentglwidget->show();
    PRIVATE(this)->currentglwidget->raise();
  }
  PRIVATE(this)->currentglwidget->setFocus();
}

// *************************************************************************

// Gets called by the SoQtGLArea instance upon keyboard presses. These
// are then forwarded to subclasses for handling.
void
SoQtGLWidgetP::GLAreaKeyEvent(QKeyEvent * e, void * userdata)
{
  SoQtGLWidget * that = (SoQtGLWidget *)userdata;
  that->processEvent(e);
}

// *************************************************************************

static const char eventnaming[][50] = {
  "None", // 0
  "Timer",
  "MouseButtonPress",
  "MouseButtonRelease",
  "MouseButtonDblClick",
  "MouseMove",
  "KeyPress",
  "KeyRelease",
  "FocusIn",
  "FocusOut",
  "Enter",
  "Leave",
  "Paint",
  "Move",
  "Resize",
  "Create",
  "Destroy",
  "Show",
  "Hide",
  "Close",
  "Quit", // 20
  "*unknown*", "*unknown*", "*unknown*", "*unknown*", "*unknown*",
  "*unknown*", "*unknown*", "*unknown*", "*unknown*",
  "Accel", // 30
  "Wheel",
  "AccelAvailable", // 32
  "CaptionChange",
  "*unknown*", "*unknown*", "*unknown*", "*unknown*", "*unknown*", "*unknown*",
  "Clipboard", // 40
  "*unknown*", "*unknown*", "*unknown*", "*unknown*", "*unknown*",
  "*unknown*", "*unknown*", "*unknown*", "*unknown*",
  "SockAct", // 50
  "AccelOverride", "*unknown*", "*unknown*", "*unknown*", "*unknown*",
  "*unknown*", "*unknown*", "*unknown*", "*unknown*",
  "DragEnter", // 60
  "DragMove",
  "DragLeave",
  "Drop",
  "DragResponse", // 64
  "*unknown*", "*unknown*", "*unknown*", "*unknown*", "*unknown*",
  "ChildInserted", // 70
  "ChildRemoved",
  "LayoutHint", // 72
  "*unknown*", "*unknown*", "*unknown*", "*unknown*", "*unknown*",
  "*unknown*", "*unknown*",
  "ActivateControl", // 80
  "DeactivateControl"
};

/*!
  FIXME: write function documentation
*/
bool
SoQtGLWidget::eventFilter(QObject * obj, QEvent * e)
{
  if (SOQT_DEBUG && 0) { // debug
    SbString w = obj->name();
    SbBool istoplevel = obj == PRIVATE(this)->currentglwidget->topLevelWidget();

    if (obj == PRIVATE(this)->glparent) { w = "glparent"; }
    else if (obj == PRIVATE(this)->currentglwidget) { w = "currentglwidget"; }
    else if (obj == PRIVATE(this)->borderwidget) { w = "borderwidget"; }
    else if (istoplevel) { w = "top-level"; }

    SoDebugError::postInfo("SoQtGLWidget::eventFilter",
                           "[invoked] QEvent==%p obj==%p==\"%s\"==%s (%s) %s (typecode==%d)",
                           e, obj, w.getString(), obj->className(),
                           istoplevel ? "TOPLEVEL" : "",
                           eventnaming[e->type()], e->type());
  }

#if QT_VERSION >= 200
  // Qt 2 introduced "accelerator" type keyboard events, which should
  // simply be ignored (all keyboard events are first attempted passed
  // by the Qt event engine as accelerator events, before they are
  // re-sent as "ordinary" keyboard events).
  if (e->type() == QEvent::Accel || e->type() == QEvent::AccelAvailable) {
    ((QKeyEvent *)e)->ignore();
    // It might not matter whether we return TRUE or FALSE here, but
    // it seems more natural to return FALSE according to the
    // semantics of the eventFilter() method (FALSE means Qt should
    // re-dispatch "normally").
    return FALSE;
  }
#endif // Qt v2.0

  // FIXME: Under Qt 3.0.0 we got buggy mouse event handling, since
  // mouse events were routed to the gl widget, even if it was
  // supposed to go somewhere else. I'm not sure if this is the
  // correct fix though. pederb, 2001-10-16
  if ((e->type() == QEvent::MouseButtonPress ||
       e->type() == QEvent::MouseButtonRelease ||
       e->type() == QEvent::MouseButtonDblClick ||
       e->type() == QEvent::MouseMove) &&
      (obj != PRIVATE(this)->currentglwidget)) return FALSE;

  SbBool keyboardevent =
    (e->type() == QEvent::KeyPress) || (e->type() == QEvent::KeyRelease);
  if (keyboardevent) {
    // Ignore keyboard-events, as they are caught directly by the
    // SoQtGLArea widget and forwarded through the
    // SoQtGLWidgetP::GLAreaKeyEvent() callback.
    return FALSE;
  }

  if (obj == (QObject *) PRIVATE(this)->glparent) {
    // If this hits, the PRIVATE(this)->glparent QWidget is a toplevelshell, so
    // we resize the GL widget along with it.
    if (e->type() == QEvent::Resize) {
      QResizeEvent * r = (QResizeEvent *)e;
      if (SOQT_DEBUG && 0) {  // debug
        SoDebugError::postInfo("SoQtGLWidget::eventFilter",
                               "resize parent %p: (%d, %d)",
                               PRIVATE(this)->glparent,
                               r->size().width(), r->size().height());
      }

      PRIVATE(this)->borderwidget->resize(r->size());
//      int newwidth = r->size().width() - 2 * PRIVATE(this)->borderthickness;
//      int newheight = r->size().height() - 2 * PRIVATE(this)->borderthickness;

//      this->glwidget->setGeometry(PRIVATE(this)->borderthickness,
//                                   PRIVATE(this)->borderthickness,
//                                   newwidth - 1, newheight -1);
//      QRect glarea = PRIVATE(this)->borderwidget->contentsRect();
//      glarea =
//      this->glwidget->setGeometry(PRIVATE(this)->borderwidget->contentsRect());

/*
      int newwidth = r->size().width();
      int newheight = r->size().height();
      this->sizeChanged(SbVec2s(newwidth - 1, newheight - 1));
*/
#if 0 // debug
      SoDebugError::postInfo("SoQtGLWidget::eventFilter", "resize done");
#endif // debug
    }
  }
  else if (obj == (QObject *) PRIVATE(this)->currentglwidget) {
    // We used to return ``true'' here if the event was a
    // QResizeEvent. The reason why we'd want to stop resize events
    // being passed on to the native Qt handler was not commented, and
    // I can't see why this should be necessary. Also, kyrah found out
    // that it causes a nasty problem with Qt/Mac, so it has been
    // removed.  <mortene@sim.no>.
  }
  else {
    // Handle in superclass.
    bool stop = inherited::eventFilter(obj, e);
    if (stop) { return TRUE; }
  }

  this->processEvent(e);
  return FALSE;
}

// *************************************************************************

/*!
  Specify that there should be a border around the OpenGL canvas (or not).

  \sa isBorder()
*/
void
SoQtGLWidget::setBorder(const SbBool enable)
{
  PRIVATE(this)->borderthickness = (enable ? SO_BORDER_THICKNESS : 0);
  if (PRIVATE(this)->borderwidget != NULL) {
    PRIVATE(this)->borderwidget->setLineWidth(PRIVATE(this)->borderthickness);
    PRIVATE(this)->currentglwidget->move(PRIVATE(this)->borderthickness, PRIVATE(this)->borderthickness);
    QSize frame(PRIVATE(this)->borderwidget->size());
    PRIVATE(this)->currentglwidget->setGeometry(
      QRect(PRIVATE(this)->borderthickness, PRIVATE(this)->borderthickness,
             frame.width() - 2 * PRIVATE(this)->borderthickness,
             frame.height() - 2 * PRIVATE(this)->borderthickness));

//    this->glwidget->resize(
//      frame.width() - 2 * PRIVATE(this)->borderthickness,
//      frame.height() - 2 * PRIVATE(this)->borderthickness);
  }
} // setBorder()

/*!
  Returns whether or not there's a border around the OpenGL canvas.

  \sa setBorder()
*/
SbBool
SoQtGLWidget::isBorder(void) const
{
  return PRIVATE(this)->borderthickness ? TRUE : FALSE;
} // isBorder()

// *************************************************************************


/*!
  Turn on or off the use of overlay planes.

  \sa isOverlayRender()
*/
void
SoQtGLWidget::setOverlayRender(const SbBool onoff)
{
  SbBool ison = QGLFormat_hasOverlay(PRIVATE(this)->glformat);
  if ((onoff && ison) || (!onoff && !ison)) { return; }

  QGLFormat_setOverlay(PRIVATE(this)->glformat, onoff);

  ison = QGLFormat_hasOverlay(PRIVATE(this)->glformat);
  if (onoff && !ison) {
    SoDebugError::postWarning("SoQtGLWidget::setOverlayRender",
                              "overlay planes not supported");
    return;
  }

  // Rebuild if a GL widget has already been built.
  if (PRIVATE(this)->currentglwidget) this->buildGLWidget();
}

/*!
  Returns a flag indicating whether or not overplay planes are
  currently used.

  \sa setOverlayRender()
 */
SbBool
SoQtGLWidget::isOverlayRender(void) const
{
  return QGLFormat_hasOverlay(PRIVATE(this)->glformat);
}

/*!
  Switch between single and double buffer mode for the OpenGL canvas.
  The default is to use a single buffer canvas.

  \sa isDoubleBuffer()
*/
void
SoQtGLWidget::setDoubleBuffer(const SbBool enable)
{
  if ((enable && PRIVATE(this)->glformat->doubleBuffer()) ||
       (!enable && !PRIVATE(this)->glformat->doubleBuffer()))
    return;

  PRIVATE(this)->glformat->setDoubleBuffer(enable);
  // Rebuild if a GL widget has already been built.
  if (PRIVATE(this)->currentglwidget) this->buildGLWidget();
}

/*!
  Returns the status of the buffer mode.

  \sa setDoubleBuffer()
 */
SbBool
SoQtGLWidget::isDoubleBuffer(void) const
{
  return PRIVATE(this)->glformat->doubleBuffer();
}

/*!
  Enables or disables quad buffer stereo.
*/
void
SoQtGLWidget::setQuadBufferStereo(const SbBool enable)
{
  if ((enable && PRIVATE(this)->glformat->stereo()) ||
       (!enable && !PRIVATE(this)->glformat->stereo()))
    return;

  PRIVATE(this)->glformat->setStereo(enable);

  // Rebuild if a GL widget has already been built.
  if (PRIVATE(this)->currentglwidget) this->buildGLWidget();
}

/*!
  Returns \c TRUE if quad buffer stereo is enabled for this widget.
*/

SbBool
SoQtGLWidget::isQuadBufferStereo(void) const
{
  return PRIVATE(this)->glformat->stereo();
}

/*!
  If this is set to \c TRUE, rendering will happen in the front buffer
  even if the current rendering mode is double buffered.
*/
void
SoQtGLWidget::setDrawToFrontBufferEnable(const SbBool enable)
{
  this->drawToFrontBuffer = enable;
}

/*!
  \sa setDrawToFrontBufferEnable()
*/
SbBool
SoQtGLWidget::isDrawToFrontBufferEnable(void) const
{
  return this->drawToFrontBuffer;
}

// *************************************************************************

/*!
  For SoQt, this returns the same widget pointer as that of
  SoQtGLWidget::getGLWidget().
*/
QWidget *
SoQtGLWidget::getNormalWidget(void) const
{
  return this->getGLWidget();
}

/*!
  Returns widget associated with overlay planes, or \c NULL if no
  overlay planes are available.

  For the Qt toolkit, overlay planes is a feature of the QGLWidget,
  and not seen at a separate widget entity. So this call will just
  return the same widget reference as the SoQt::getGLWidget() call (if
  overlay planes are supported).
*/
QWidget *
SoQtGLWidget::getOverlayWidget(void) const
{
  // Cast away this-pointer constness, as
  // SoQtGLWidget::getOverlayContext() is not defined as const.
  SoQtGLWidget * that = (SoQtGLWidget *)this;

  return that->getOverlayContext() ? this->getGLWidget() : NULL;
}

// *************************************************************************

/*!
  Sets the size of the GL canvas.
*/
void
SoQtGLWidget::setGLSize(const SbVec2s size)
{
  if (size == PRIVATE(this)->glSize) return;
#if SOQT_DEBUG && 0 // debug
  SoDebugError::postInfo("SoQtGLWidget::setGLSize",
                         "[invoked (%d, %d)]", size[0], size[1]);
#endif // debug
  PRIVATE(this)->glSize = size;
  if (PRIVATE(this)->currentglwidget) {
    int frame = this->isBorder() ? PRIVATE(this)->borderthickness : 0;
    PRIVATE(this)->currentglwidget->setGeometry(QRect(frame, frame, PRIVATE(this)->glSize[0], PRIVATE(this)->glSize[1]));
  }
} // setGLSize()

/*!
  Return the dimensions of the OpenGL canvas.
*/
SbVec2s
SoQtGLWidget::getGLSize(void) const
{
  return PRIVATE(this)->glSize;
}

/*!
  Return the aspect ratio of the OpenGL canvas.
*/
float
SoQtGLWidget::getGLAspectRatio(void) const
{
  return float(PRIVATE(this)->currentglwidget->width()) /
    float(PRIVATE(this)->currentglwidget->height());
}  // getGLAspectRatio()

/*!
  \fn void SoQtGLWidget::setGlxSize(const SbVec2s size)
  This function has been renamed to the more appropriate setGLSize.
  \sa setGLSize
*/

/*!
  \fn SbVec2s SoQtGLWidget::getGlxSize(void) const
  This function has been renamed to the more appropriate getGLSize.
  \sa getGLSize
*/

/*!
  \fn float SoQtGLWidget::getGlxAspectRatio(void) const
  This function has been renamed to the more appropriate getGLAspectRatio.
  \sa getGLAspectRatio
*/

// *************************************************************************

/*!
  Returns a pointer to the Qt QGLWidget.
*/
QWidget *
SoQtGLWidget::getGLWidget(void) const
{
  return PRIVATE(this)->currentglwidget;
} // getGLWidget()


// *************************************************************************

/*!
  This is the method which gets called whenever we change which OpenGL
  widget is used.

  Should be overloaded in subclasses which directly or indirectly
  store the return value from the SoQtGLWidget::getGLWidget() method.

  \sa sizeChanged()
*/
void
SoQtGLWidget::widgetChanged(QWidget * w)
{
  // virtual
}

/*!
  Any events from the native window system that goes to the OpenGL
  canvas gets piped through this method.

  It is overloaded in the subclasses to catch user interaction with
  the render canvas in the viewers, aswell as forwarding relevant
  events to the scenegraph.
*/
void
SoQtGLWidget::processEvent(QEvent * anyevent)
{
  // Nothing is done here for the SoQtGLWidget, as realize, resize and
  // expose events are caught by explicitly attaching signal callbacks
  // to the widget.
}

// *************************************************************************

/*!
  This method calls make-current on the correct context and ups the
  lock level.
*/
void
SoQtGLWidget::glLockNormal(void)
{
  assert(PRIVATE(this)->currentglwidget != NULL);
  ((SoQtGLArea *)PRIVATE(this)->currentglwidget)->makeCurrent();
}

/*!
  This method drops the lock level.
*/
void
SoQtGLWidget::glUnlockNormal(void)
{
  // does nothing under Qt. Under BeOS the buffer needs to be unlocked
}

/*!
  FIXME: write doc
*/
void
SoQtGLWidget::glSwapBuffers(void)
{
  assert(PRIVATE(this)->currentglwidget != NULL);
  ((SoQtGLArea *)PRIVATE(this)->currentglwidget)->swapBuffers();
} // glSwapBuffers()

/*!
  Flush the current GL buffer. Simply calls glFlush().
*/
void 
SoQtGLWidget::glFlushBuffer(void)
{
  // might be called for both normal and overlay widgets
  glFlush();

#ifdef Q_WS_MAC
  // Qt/Mac double-buffers everything internally to circumvent some of
  // AGLs limitations. Since we don't use their "recommended"
  // updateGL() way of rendering, we have to explicitly swap the
  // buffers.
  ((QGLWidget *)this->getGLWidget())->swapBuffers();
  // FIXME: this should only be a temporary hack until Apple fixes
  // AGL...  kyrah 20011129
  //
  // UPDATE: or until we pick up and integrate into the SoQt library
  // the pieces of sourcecode from QGLWidget et al that depend on. As
  // Qt Professional Edition License holders on all platforms, this is
  // something we seem to be allowed to do.  20011129 mortene.
  //

  // For reference, this is what Sam Magnusen from TrollTech says why
  // they need the ugly bitblt hack on the Mac:
  //
  // «All widgets in Qt/Mac are really just an area that you are
  // "allowed to paint on", and then when you do Qt/Mac will figure
  // out what that area is, and only paint on it. Most of this magic
  // is in QWidget/QPainter - however they can't handle the QGLWidget
  // case as when QWidget decides what that region is, QPainter can't
  // apply it. It could be done in QGLWidget (if AGL offered complex
  // region clipping, however they only allow for a rectangle. This is
  // not good enough if you had widgets overlapping the opengl widget,
  // if you are sure you don't, you can turn off the
  // QMAC_OPENGL_DOUBLEBUFFER ifdef (in qgl.h) and it will not use the
  // technique, and I think you will get acceleration as well.»

  // UPDATE: testing shows that this works in window mode, but that it
  // fails miserably in full screen mode (with lots of Core Graphics
  // Services errors). 20011201 kyrah (writeup by mortene).

#endif // Q_WS_MAC
}

/*!
  This method calls make-current on the correct context and ups the lock
  level.
*/

void
SoQtGLWidget::glLockOverlay(void)
{
  assert(PRIVATE(this)->currentglwidget != NULL);
  QGLFormat_makeOverlayCurrent((SoQtGLArea *)PRIVATE(this)->currentglwidget);
} // glLock()

/*!
  This method drops the lock level.
*/
void
SoQtGLWidget::glUnlockOverlay(void)
{
  // does nothing under Qt. Under BeOS the buffer needs to be unlocked  
} // glUnlock()

// slot invoked upon QGLWidget initialization
void
SoQtGLWidget::gl_init(void)
{
  if (SOQT_DEBUG && 0) { // debug
    SoDebugError::postInfo("gl_init", "invoked");
  }

  this->initGraphic();
}

// slot invoked upon QGLWidget resizes
void
SoQtGLWidget::gl_reshape(int width, int height)
{
  if (SOQT_DEBUG && 0) { // debug
    SoDebugError::postInfo("gl_reshape", "<%d, %d>", width, height);
  }

  PRIVATE(this)->glSize = SbVec2s((short) width, (short) height);
  PRIVATE(this)->wasresized = TRUE;
}

// slot invoked upon QGLWidget expose events
void
SoQtGLWidget::gl_exposed(void)
{
  if (SOQT_DEBUG && 0) { // debug
    SoDebugError::postInfo("gl_exposed", "%f", SbTime::getTimeOfDay().getValue());
  }

  if (this->waitForExpose) {
    this->waitForExpose = FALSE; // Gets flipped from TRUE on first expose.
#if 0 // tmp disabled
    // The Qt library uses QApplication::sendPostedEvents() for
    // passing out various delayed events upon show(), among them a
    // bunch of bl**dy resize events which will overload any size
    // settings done before we show the SoQt component widgets.

    // FIXME: should probably be an afterRealizeHook() fix. 20001125 mortene.

    this->setSize(this->getSize());
#endif // tmp disabled
  }
  if (PRIVATE(this)->wasresized) {
    this->sizeChanged(PRIVATE(this)->glSize);
    PRIVATE(this)->wasresized = FALSE;
  }

  if (!this->glScheduleRedraw()) {
    this->redraw();
  }
}

// *************************************************************************

/*!
  FIXME: write doc
*/
void
SoQtGLWidget::eventHandler(
  QWidget * widget,
  void * closure,
  QEvent * event,
  bool *) // ?)
{
  assert(closure != NULL);
  SoQtGLWidget * component = (SoQtGLWidget *) closure;
  component->processEvent(event);
} // eventHandler()

/*!
  Returns the normal GL context.
*/
const QGLContext * 
SoQtGLWidget::getNormalContext(void)
{
  QGLWidget * w = (QGLWidget*) this->getGLWidget();
  if (w) return w->context();
  return NULL;
}

/*!
  Returns the overlay GL context.
*/
const QGLContext * 
SoQtGLWidget::getOverlayContext(void)
{
  QGLWidget * w = (QGLWidget*) this->getGLWidget();
  if (w) { return QGLWidget_overlayContext(w); }
  return NULL;
}

/*!
  Returns the overlay transparent pixel.
*/
unsigned long 
SoQtGLWidget::getOverlayTransparentPixel(void)
{
  const QGLContext * ctx = this->getOverlayContext();
  if (ctx) {
    QColor color = QGLContext_overlayTransparentColor(ctx);
    return color.pixel();
  }
  return 0;
}

/*!
  Returns TRUE if the normal GL context is in RGBA mode.
  Return FALSE if color index mode is used.
*/
SbBool 
SoQtGLWidget::isRGBMode(void)
{
  return (SbBool) PRIVATE(this)->glformat->rgba();
}

/*!
  Renders the overlay scene graph. Default method is empty. Subclasses
  should overload this method.
*/
void 
SoQtGLWidget::redrawOverlay(void)
{
  // should be empty. It's up subclasses to do some work here
}

/*!
  Will be called when GL widget should initialize graphic, after
  the widget has been created. Default method enabled GL_DEPTH_TEST.
*/
void 
SoQtGLWidget::initGraphic(void)
{
  this->glLockNormal();
  // Need to set this explicitly when running on top of Open Inventor,
  // as it seems to have been forgotten there.
  // This code should be invoked from SoQtRenderArea::initGraphics()
  glEnable(GL_DEPTH_TEST);
  this->glUnlockNormal();
}

/*!
  Will be called after the overlay widget has been created, and subclasses
  should overload this to initialize overlay stuff.

  Default method does nothing.
*/
void 
SoQtGLWidget::initOverlayGraphic(void)
{
  // FIXME: can't see this function called from anywhere within SoQt.
  // That seems bogus. 20010831 mortene.
}

// doc in super
void
SoQtGLWidget::sizeChanged(const SbVec2s & size)
{
}

/*!
  Will be called whenever scene graph needs to be redrawn().
  If this method return FALSE, redraw() will be called immediately.

  Default method simply returns FALSE. Overload this method to
  schedule a redraw and return TRUE if you're trying to do The Right
  Thing.  
*/
SbBool 
SoQtGLWidget::glScheduleRedraw(void)
{
  return FALSE;
}

/*!
  Will return \c TRUE if an overlay GL drawing area exists.
*/
SbBool 
SoQtGLWidget::hasOverlayGLArea(void) const 
{
  return this->getOverlayWidget() != NULL;
}

/*!
  Will return \c TRUE if a normal GL drawing area exists.
*/
SbBool 
SoQtGLWidget::hasNormalGLArea(void) const 
{
  return this->getNormalWidget() != NULL;
}

// *************************************************************************
