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
  \class SoQtRenderArea SoQtRenderArea.h Inventor/Qt/SoQtRenderArea.h
  \brief The SoQtRenderArea class blablabla TODO

  TODO:
  - more doc (much of this is just a wrapper around methods in SoSceneManager)
  - Qt doesn't have any way of dealing with overlay planes -- check this
  with 2.0 aswell
  - Qt does not seem to have any way of dealing with "raw" devices either
  (like Xt has)
 */

#include <Inventor/Qt/SoQtRenderArea.h>
#include <Inventor/Qt/devices/SoQtMouse.h>
#include <Inventor/Qt/devices/SoQtKeyboard.h>

#include <Inventor/SoSceneManager.h>
#include <Inventor/sensors/SoNodeSensor.h>
#if SOQT_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // SOQT_DEBUG
#include <assert.h>

/*!
  \var SoQtRenderAreaEventCB * SoQtRenderArea::appEventHandler
  FIXME: write doc
*/
/*!
  \var void * SoQtRenderArea::appEventHandlerData
  FIXME: write doc
*/
/*!
  \var SbPList * SoQtRenderArea::deviceList
  FIXME: write doc
*/


// debug
#define SOQT_RA_RESIZE_DEBUG 0

/*!
  Constructor.
*/
SoQtRenderArea::SoQtRenderArea(QWidget * parent,
			       const char * const name, 
			       SbBool buildInsideParent, 
			       SbBool getMouseInput,
			       SbBool getKeyboardInput)
  : inherited(parent, name, buildInsideParent,
	      SO_GLX_RGB|SO_GLX_DOUBLE|SO_GLX_ZBUFFER, FALSE)
{
#if SOQT_RA_RESIZE_DEBUG  // debug
  SoDebugError::postInfo("SoQtRenderArea::SoQtRenderArea-1",
			 "size %p: <%d, %d>",
			 this->getWidget(),
			 getSize()[0], getSize()[1]);
#endif // debug

  this->constructor_initialize(getMouseInput, getKeyboardInput);
  this->buildWidget(buildInsideParent ? parent : NULL);

#if SOQT_RA_RESIZE_DEBUG  // debug
  SoDebugError::postInfo("SoQtRenderArea::SoQtRenderArea-2",
			 "size %p: (%d, %d)",
			 this->getWidget(),
			 getSize()[0], getSize()[1]);

  QWidget * w = getWidget();
  SoDebugError::postInfo("SoQtRenderArea::SoQtRenderArea-3",
			 "size %p: (%d, %d)",
			 w, w->size().width(), w->size().height());
#endif // debug
}

/*!
  This constructor can only be used by subclasses.
 */
SoQtRenderArea::SoQtRenderArea(QWidget * parent,
			       const char * const name, 
			       SbBool buildInsideParent, 
			       SbBool getMouseInput,
			       SbBool getKeyboardInput,
			       SbBool buildNow)
  : inherited(parent, name, buildInsideParent,
	      SO_GLX_RGB|SO_GLX_DOUBLE|SO_GLX_ZBUFFER, buildNow)
{
  this->constructor_initialize(getMouseInput, getKeyboardInput);
  if (buildNow) this->buildWidget(buildInsideParent ? parent : NULL);
}

/*!
  FIXME: write function documentation
*/
QWidget *
SoQtRenderArea::buildWidget(QWidget * parent)
{
  QWidget * w = inherited::buildWidget(parent);
  this->setBorder(TRUE);
  // Set default size if no size has been specified.
  if (this->getSize()[0] == -1) this->setSize(SbVec2s(400, 400));

  return w;
}

void
SoQtRenderArea::constructor_initialize(SbBool getmouseinput,
				       SbBool getkeyboardinput)

{
  this->sceneManager = new SoSceneManager;
  this->sceneManager->setRenderCallback(SoQtRenderArea::renderCB, this);
  // FIXME: this should probably be done in the visibility
  // callback. 990203 mortene.
  this->sceneManager->activate();

  this->overlaySceneManager = new SoSceneManager;
  // FIXME: this should probably be done in the visibility
  // callback. 990203 mortene.
  this->overlaySceneManager->activate();

  this->colormap = NULL;
  this->cmNum = 0;
  this->overlayColormap= NULL;
  this->ocmNum = 0;

  this->clear = TRUE;
  this->clearOverlay = TRUE;
  this->autoRedraw = TRUE;

  this->selection = NULL;
  this->overlaySelection = NULL;

  this->mousedevice = getmouseinput ? new SoQtMouse : NULL;
  this->kbddevice = getkeyboardinput ? new SoQtKeyboard : NULL;
  this->deviceList = NULL;

  this->appEventHandler = NULL;
}

/*!
  Destructor.
 */
SoQtRenderArea::~SoQtRenderArea()
{
  delete this->sceneManager;
  delete this->overlaySceneManager;
  delete [] this->colormap;
  delete [] this->overlayColormap;
  delete this->deviceList;
  delete this->mousedevice;
  delete this->kbddevice;
}

void
SoQtRenderArea::renderCB(void * data, SoSceneManager * scenemanager)
{
  ((SoQtRenderArea *)data)->render();
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::setSceneGraph(SoNode * const newScene)
{
  this->sceneManager->setSceneGraph(newScene);
}

/*!
  FIXME: write function documentation
*/
SoNode *
SoQtRenderArea::getSceneGraph(void) const
{  
  return this->sceneManager->getSceneGraph();
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::setOverlaySceneGraph(SoNode * const newScene)
{
  this->overlaySceneManager->setSceneGraph(newScene);
}

/*!
  FIXME: write function documentation
*/
SoNode *
SoQtRenderArea::getOverlaySceneGraph(void) const
{
  return this->overlaySceneManager->getSceneGraph();
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::registerDevice(SoQtDevice * const device)
{
  if (!this->deviceList) this->deviceList = new SbPList;
  this->deviceList->append(device);
  device->setWindowSize(this->getGlxSize());
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::unregisterDevice(SoQtDevice * const device)
{
  int idx = this->deviceList->find(device);
  if (idx != -1) this->deviceList->remove(idx);
#if SOQT_DEBUG
  if (idx == -1) {
    SoDebugError::postWarning("SoQtRenderArea::unregisterDevice",
			      "tried to remove device not in list");
  }
#endif // SOQT_DEBUG
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::setBackgroundColor(const SbColor & c)
{
  this->sceneManager->setBackgroundColor(c);
}

/*!
  FIXME: write function documentation
*/
const SbColor &
SoQtRenderArea::getBackgroundColor() const
{
  return this->sceneManager->getBackgroundColor();  
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::setBackgroundIndex(const int index)
{
  this->sceneManager->setBackgroundIndex(index);
}

/*!
  FIXME: write function documentation
*/
int 
SoQtRenderArea::getBackgroundIndex() const
{
  return this->sceneManager->getBackgroundIndex();
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::setOverlayBackgroundIndex(const int index)
{
  this->overlaySceneManager->setBackgroundIndex(index);
}

/*!
  FIXME: write function documentation
*/
int 
SoQtRenderArea::getOverlayBackgroundIndex() const
{
  return this->overlaySceneManager->getBackgroundIndex();
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::setColorMap(const int startIndex, const int num, const
			    SbColor * const colors)
{
  delete [] this->colormap;
  this->cmStartIndex = startIndex;
  this->cmNum = num;
  this->colormap = new SbColor[num];
  for (int i = 0; i < num; i++) {
    this->colormap[i] = colors[i];
  }
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::setOverlayColorMap(const int startIndex, const int num,
				   const SbColor * const colors)
{
  delete [] this->overlayColormap;
  this->ocmStartIndex = startIndex;
  this->ocmNum = num;
  this->overlayColormap = new SbColor[num];
  for (int i = 0; i < num; i++) {
    this->overlayColormap[i] = colors[i];
  }
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::setViewportRegion(const SbViewportRegion & newRegion)
{
  this->sceneManager->getGLRenderAction()->setViewportRegion(newRegion);
}

/*!
  FIXME: write function documentation
*/
const SbViewportRegion &
SoQtRenderArea::getViewportRegion() const
{
  return this->sceneManager->getGLRenderAction()->getViewportRegion();
}


/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::setTransparencyType(const SoGLRenderAction::TransparencyType type)
{
  this->sceneManager->getGLRenderAction()->setTransparencyType(type);
}

/*!
  FIXME: write function documentation
*/
SoGLRenderAction::TransparencyType 
SoQtRenderArea::getTransparencyType(void) const
{
  return this->sceneManager->getGLRenderAction()->getTransparencyType();
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::setAntialiasing(const SbBool smoothing, const int numPasses)
{
  this->sceneManager->setAntialiasing(smoothing, numPasses);
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::getAntialiasing(SbBool & smoothing, int & numPasses) const
{
  this->sceneManager->getAntialiasing(smoothing, numPasses);
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::setClearBeforeRender(const SbBool trueOrFalse)
{
  this->clear = trueOrFalse;
}

/*!
  FIXME: write function documentation
*/
SbBool 
SoQtRenderArea::isClearBeforeRender(void) const
{
  return this->clear;
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::setClearBeforeOverlayRender(const SbBool trueOrFalse)
{
  this->clearOverlay = trueOrFalse;
}

/*!
  FIXME: write function documentation
*/
SbBool 
SoQtRenderArea::isClearBeforeOverlayRender(void) const
{
  return this->clearOverlay;
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::setAutoRedraw(const SbBool trueOrFalse)
{
  this->autoRedraw = trueOrFalse;
}

/*!
  FIXME: write function documentation
*/
SbBool 
SoQtRenderArea::isAutoRedraw(void) const
{
  return this->autoRedraw;
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::setRedrawPriority(const uint32_t priority)
{
  this->sceneManager->setRedrawPriority(priority);
  this->overlaySceneManager->setRedrawPriority(priority);
}

/*!
  FIXME: write function documentation
*/
uint32_t 
SoQtRenderArea::getRedrawPriority(void) const
{
  return this->sceneManager->getRedrawPriority();
}

/*!
  FIXME: write function documentation
*/
uint32_t 
SoQtRenderArea::getDefaultRedrawPriority(void)
{
  return SoSceneManager::getDefaultRedrawPriority(); 
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::render(void)
{
  assert(this->getQGLWidget());

  this->getQGLWidget()->makeCurrent();
  this->redraw();
  // FIXME: this does not seem to work correctly for the singlebuffer
  // case -- check with SoQtExaminerViewer.. 990226 mortene.
  if (this->isDoubleBuffer()) this->getQGLWidget()->swapBuffers();
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::renderOverlay(void)
{
  assert(this->overlaySceneManager);
  // FIXME: doesn't work, as Qt has no notion of overlay
  // planes. 990215 mortene.
  this->overlaySceneManager->render(this->clearOverlay, 
				    this->clearOverlay);  
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::scheduleRedraw(void)
{
  this->sceneManager->scheduleRedraw();
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::scheduleOverlayRedraw(void)
{
  this->sceneManager->scheduleRedraw();
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::redrawOnSelectionChange(SoSelection * const s)
{
  this->selection = s;
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::redrawOverlayOnSelectionChange(SoSelection * const s)
{
  this->overlaySelection = s;
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::setEventCallback(SoQtRenderAreaEventCB * const fcn, 
				 void * const userData)
{
  this->appEventHandler = fcn;
  this->appEventHandlerData = userData;
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::setGLRenderAction(SoGLRenderAction * const action)
{
  this->sceneManager->setGLRenderAction(action);
}

/*!
  FIXME: write function documentation
*/
SoGLRenderAction *
SoQtRenderArea::getGLRenderAction(void) const
{

  return this->sceneManager->getGLRenderAction();
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::setOverlayGLRenderAction(SoGLRenderAction * const ra)
{
  this->overlaySceneManager->setGLRenderAction(ra);
}

/*!
  FIXME: write function documentation
*/
SoGLRenderAction *
SoQtRenderArea::getOverlayGLRenderAction(void) const
{
  return this->overlaySceneManager->getGLRenderAction();
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::setSceneManager(SoSceneManager * const sm)
{
  this->sceneManager = sm;
}

/*!
  FIXME: write function documentation
*/
SoSceneManager *
SoQtRenderArea::getSceneManager(void) const
{
  return this->sceneManager;
}

/*!
  FIXME: write function documentation
*/
void 
SoQtRenderArea::setOverlaySceneManager(SoSceneManager * const sm)
{
  this->overlaySceneManager = sm;
}

/*!
  FIXME: write function documentation
*/
SoSceneManager *
SoQtRenderArea::getOverlaySceneManager(void) const
{
  return this->overlaySceneManager;
}

/*!
  FIXME: write function documentation
*/
void
SoQtRenderArea::sizeChanged(const SbVec2s & newSize)
{
  assert(this->sceneManager);

  this->sceneManager->setWindowSize(newSize);
  this->sceneManager->setSize(newSize);

  this->overlaySceneManager->setWindowSize(newSize);
  this->overlaySceneManager->setSize(newSize);

  // All devices belonging to the render area need to know the window
  // size to be able to convert from window system coordinates to
  // OpenGL/OIV system (i.e. y=0 at the bottom of the canvas).
  if (this->mousedevice) this->mousedevice->setWindowSize(newSize);
  if (this->kbddevice) this->kbddevice->setWindowSize(newSize);
  if (this->deviceList) {
    for (int i=0; i < this->deviceList->getLength(); i++)
      ((SoQtDevice *)((*(this->deviceList))[i]))->setWindowSize(newSize);
  }
}

/*!
  FIXME: write function documentation
*/
void
SoQtRenderArea::redraw(void)
{
#if 0 // debug
  SoDebugError::postInfo("SoQtRenderArea::redraw", "start");
#endif // debug

  // actualRedraw() can be overloaded by subclasses if there's need
  // for any magic when rendering (like multipass rendering for hidden
  // line drawstyle, for instance).
  this->actualRedraw();

#if 0 // debug
  SoDebugError::postInfo("SoQtRenderArea::redraw", "done");
#endif // debug
}

/*!
  FIXME: write function documentation
*/
void
SoQtRenderArea::actualRedraw(void)
{
  // NB! This is only called upon expose-type paint events. QGLWidget
  // takes care of making a current context and swapping buffers in
  // those cases.
  this->sceneManager->render(this->clear /* ?? */, this->clear /* ?? */);
}

/*!
  FIXME: write function documentation
*/
void
SoQtRenderArea::redrawOverlay(void)
{
  // See comments on SoQtRenderArea::redraw().
  this->actualOverlayRedraw();
}

/*!
  FIXME: write function documentation
*/
void
SoQtRenderArea::actualOverlayRedraw(void)
{
  // FIXME: defunct -- overlay planes not supported in Qt. 990224 mortene
  this->overlaySceneManager->render(this->clear /* ?? */,
				    this->clear /* ?? */);
}

/*!
  FIXME: write function documentation
*/
const char *
SoQtRenderArea::componentClassName(void) const
{
  return "SoQtRenderArea";
}

/*!
  Returns the default name of an SoQtRenderArea widget. Should be overloaded
  by subclasses.
 */
const char *
SoQtRenderArea::getDefaultWidgetName(void) const
{
  return "SoQtRenderArea";
}

/*!
  Returns the default window caption string of this component. Should be
  overloaded by subclasses.
 */
const char *
SoQtRenderArea::getDefaultTitle(void) const
{
  return "Qt RenderArea";
}

/*!
  Returns the default icon title of this component. Should be overloaded
  by subclasses.
 */
const char *
SoQtRenderArea::getDefaultIconTitle(void) const
{
  return "Qt RenderArea";
}

/*!
  FIXME: write function documentation
*/
SbBool
SoQtRenderArea::invokeAppCB(QEvent * anyevent)
{
  return (this->appEventHandler &&
	  this->appEventHandler(this->appEventHandlerData, anyevent));
}

/*!
  FIXME: write function documentation
*/
void
SoQtRenderArea::processEvent(QEvent * anyevent)
{
  // If there's a event handling callback registered, it should be
  // used before the OIV translation and handling.

  const SoEvent * ev = NULL;

  // Workaround for Qt design problem: mouse position is not recorded
  // for anything but MouseMove events. We want to know the mouse
  // position for all event types.
  QGLWidget * w = this->getQGLWidget();
  SoQtDevice::lasteventposition = w->mapFromGlobal(QCursor::pos());

  // Try list of user devices (if any) before mouse and keyboard.
  if (this->deviceList) {
    for (int i=0; i < this->deviceList->getLength(); i++) {
      SoQtDevice * dev = (SoQtDevice *)(*(this->deviceList))[i];
      ev = dev->translateEvent(anyevent);
      if (ev) break;
    }
  }


  // Try mouse device.
  if (!ev && this->mousedevice)
    ev = this->mousedevice->translateEvent(anyevent);

  // Try keyboard device.
  if (!ev && this->kbddevice)
    ev = this->kbddevice->translateEvent(anyevent);

  if (ev) {
    if (!this->overlaySceneManager->processEvent(ev))
      this->sceneManager->processEvent(ev);
  }
}
