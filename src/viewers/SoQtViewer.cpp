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
 *  http://www.sim.no/ sales@sim.no Voice: +47 73540378 Fax: +47 73943861
 *
\**************************************************************************/

/*!
  \class SoQtViewer SoQtViewer.h Inventor/Qt/viewers/SoQtViewer.h
  \brief The SoQtViewer class is the top level base viewer class.
  \ingroup qtviewers

  TODO: more doc
  ...overview of what this class provides over parent class...
  ...keyboard combinations: Home, s, arrow keys (but only during
  viewing), Esc...
  ...explain pan, rotate, zoom, dolly, seek...
  ..explain the fact that we're moving the camera, not the scene...
  ...viewer modes (examine vs interact) w/ explanation of what they are
  useful for...

  \sa SoQtFullViewer
*/

#include <Inventor/Qt/viewers/SoQtViewer.h>
#include <Inventor/SoDB.h>

#if defined(COIN_CONFIG_NO_SOROTATION)
#define NO_HEADLIGHT 1
#endif // COIN_CONFIG_NO_SOROTATION
#if defined(COIN_CONFIG_NO_SODIRECTIONALLIGHT)
#define NO_HEADLIGHT 1
#endif // COIN_CONFIG_NO_SODIRECTIONALLIGHT
#if defined(COIN_CONFIG_NO_SORESETTRANSFORM)
#define NO_HEADLIGHT 1
#endif // COIN_CONFIG_NO_SORESETTRANSFOM

#if defined(COIN_CONFIG_NO_SOSWITCH)
#define NO_DRAWSTYLESETTING 1
#endif // !COIN_CONFIG_NO_SOSWITCH
#if defined(COIN_CONFIG_NO_SODRAWSTYLE)
#define NO_DRAWSTYLESETTING 1
#endif // !COIN_CONFIG_NO_SODRAWSTYLE
#if defined(COIN_CONFIG_NO_SOLIGHTMODEL)
#define NO_DRAWSTYLESETTING 1
#endif // !COIN_CONFIG_NO_SOLIGHTMODEL
#if defined(COIN_CONFIG_NO_SOBASECOLOR)
#define NO_DRAWSTYLESETTING 1
#endif // !COIN_CONFIG_NO_SOBASECOLOR
#if defined(COIN_CONFIG_NO_SOMATERIALBINDING)
#define NO_DRAWSTYLESETTING 1
#endif // !COIN_CONFIG_NO_SOMATERIALBINDING
#if defined(COIN_CONFIG_NO_SOCOMPLEXITY)
#define NO_DRAWSTYLESETTING 1
#endif // !COIN_CONFIG_NO_SOCOMPLEXITY

#if !defined(NO_HEADLIGHT)
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoResetTransform.h>
#endif // !NO_HEADLIGHT

#if !defined(NO_DRAWSTYLESETTING)
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoComplexity.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoLightModel.h>
#include <Inventor/nodes/SoMaterialBinding.h>
#include <Inventor/nodes/SoSwitch.h>
#if !defined(COIN_CONFIG_NO_SOPOLYGONOFFSET)
#include <Inventor/nodes/SoPolygonOffset.h>
#endif // !COIN_CONFIG_NO_SOPOLYGONOFFSET
#endif // !NO_DRAWSTYLESETTING

#include <Inventor/nodes/SoSeparator.h>
#if !defined(COIN_CONFIG_NO_SOLOCATEHIGHLIGHT)
#include <Inventor/nodes/SoLocateHighlight.h>
#endif // !COIN_CONFIG_NO_SOLOCATEHIGHLIGHT
#if !defined(COIN_CONFIG_NO_SOORTHOGRAPHICCAMERA)
#include <Inventor/nodes/SoOrthographicCamera.h>
#endif // !COIN_CONFIG_NO_SOORTHOGRAPHICCAMERA
#if !defined(COIN_CONFIG_NO_SOPERSPECTIVECAMERA)
#include <Inventor/nodes/SoPerspectiveCamera.h>
#endif // !COIN_CONFIG_NO_SOPERSPECTIVECAMERA

#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoSearchAction.h>
#if !defined(COIN_CONFIG_NO_SORAYPICKACTION)
#include <Inventor/actions/SoRayPickAction.h>
#endif // !COIN_CONFIG_NO_SORAYPICKACTION

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/SoSceneManager.h>
#include <Inventor/SoPickedPoint.h>

#include <qkeycode.h>
#include <assert.h>

// FIXME: get rid of this before 1.0 release (convert everything to Qt
// version 2.x API). 19990630 mortene.
#if QT_VERSION >= 200
#include <q1xcompatibility.h>
#endif // Qt v2.x


/*!
  \enum SoQtViewer::Type
  FIXME: write documentation for enum
*/
/*!
  \var SoQtViewer::Type SoQtViewer::BROWSER
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtViewer::Type SoQtViewer::EDITOR
  FIXME: write documentation for enum definition
*/

/*!
  \enum SoQtViewer::DecimationStrategy
  FIXME: write documentation for enum
*/
/*!
  \var SoQtViewer::DecimationStrategy SoQtViewer::NORMAL
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtViewer::DecimationStrategy SoQtViewer::FIXED_NUM_TRIANGLES
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtViewer::DecimationStrategy SoQtViewer::FRAMES_PER_SECOND
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtViewer::DecimationStrategy SoQtViewer::FIXED_PERCENTAGE
  FIXME: write documentation for enum definition
*/

/*!
  \enum SoQtViewer::DrawStyle
  FIXME: write documentation for enum
*/
/*!
  \var SoQtViewer::DrawStyle SoQtViewer::VIEW_AS_IS
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtViewer::DrawStyle SoQtViewer::VIEW_HIDDEN_LINE
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtViewer::DrawStyle SoQtViewer::VIEW_NO_TEXTURE
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtViewer::DrawStyle SoQtViewer::VIEW_LOW_COMPLEXITY
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtViewer::DrawStyle SoQtViewer::VIEW_LINE
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtViewer::DrawStyle SoQtViewer::VIEW_POINT
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtViewer::DrawStyle SoQtViewer::VIEW_BBOX
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtViewer::DrawStyle SoQtViewer::VIEW_LOW_RES_LINE
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtViewer::DrawStyle SoQtViewer::VIEW_LOW_RES_POINT
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtViewer::DrawStyle SoQtViewer::VIEW_SAME_AS_STILL
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtViewer::DrawStyle SoQtViewer::ALL_STYLES_COMBINED
  FIXME: write documentation for enum definition
*/

/*!
  \enum SoQtViewer::DrawType
  FIXME: write documentation for enum
*/
/*!
  \var SoQtViewer::DrawType SoQtViewer::STILL
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtViewer::DrawType SoQtViewer::INTERACTIVE
  FIXME: write documentation for enum definition
*/

/*!
  \enum SoQtViewer::BufferType
  FIXME: write documentation for enum
*/
/*!
  \var SoQtViewer::BufferType SoQtViewer::BUFFER_SINGLE
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtViewer::BufferType SoQtViewer::BUFFER_DOUBLE
  FIXME: write documentation for enum definition
*/
/*!
  \var SoQtViewer::BufferType SoQtViewer::BUFFER_INTERACTIVE
  FIXME: write documentation for enum definition
*/




/*!
  \internal

  Return the parent node in the scene graph of the given \a node.
  NB: this is just a quick'n'dirty thing for often executed code,
  and doesn't cover cases where nodes have multiple parents.
 */
static inline SoGroup *
getParentOfNode(SoNode * root, SoNode * node)
{
  SoSearchAction search;
  assert(node);
  search.setNode(node);
  assert(root);
  search.apply(root);
  assert(search.getPath());
  return (SoGroup *) ((SoFullPath *)search.getPath())->getNodeFromTail(1);
}

/*!
  Constructor. \a parent, \a name and \a buildInsideParent are passed on
  to SoQtRenderArea, so see the documentation for that constructor for
  for more information on those.
*/
SoQtViewer::SoQtViewer(QWidget * parent, const char * name,
		       SbBool buildInsideParent, SoQtViewer::Type t,
		       SbBool buildNow) 
  : inherited(parent, name, buildInsideParent, TRUE, TRUE, FALSE)
{
  this->viewertype = t;
  this->viewmode = TRUE;
  this->cursoron = TRUE;

  this->cameratype = SoPerspectiveCamera::getClassTypeId();
  this->camera = NULL;
  this->deletecamera = FALSE;
  this->buffertype = this->isDoubleBuffer() ? BUFFER_DOUBLE : BUFFER_SINGLE;

  this->interactionstartCallbacks = new SoCallbackList;
  this->interactionendCallbacks = new SoCallbackList;
  this->interactionnesting = 0;

  this->seekdistance = 50.0f;
  this->seekdistanceabs = TRUE;
  this->seektopoint = TRUE;
  this->seekperiod = 2.0f;
  this->inseekmode = FALSE;
  this->seeksensor = new SoTimerSensor(SoQtViewer::seeksensorCB, this);

  this->userroot = NULL;

  this->viewerroot = new SoSeparator;
  this->viewerroot->ref();
  this->viewerroot->renderCaching.setValue(SoSeparator::OFF);
  this->viewerroot->renderCulling.setValue(SoSeparator::OFF);

#if !defined(NO_DRAWSTYLESETTING)
  // Drawstyle subgraph.
  {
    this->drawstyleroot = new SoSwitch;

    this->solightmodel = new SoLightModel;
    this->solightmodel->setOverride(TRUE);
    this->solightmodel->model = SoLightModel::BASE_COLOR;

    this->sodrawstyle = new SoDrawStyle;
    this->sodrawstyle->setOverride(TRUE);
    this->sodrawstyle->pointSize.setIgnored(TRUE);
    this->sodrawstyle->lineWidth.setIgnored(TRUE);
    this->sodrawstyle->linePattern.setIgnored(TRUE);

    this->socomplexity = new SoComplexity;
    this->socomplexity->setOverride(TRUE);
    this->socomplexity->textureQuality = 0.0f;
    this->socomplexity->value = 0.1f;

    this->drawstyleroot->addChild(this->solightmodel);
    this->drawstyleroot->addChild(this->sodrawstyle);
    this->drawstyleroot->addChild(this->socomplexity);
    this->viewerroot->addChild(this->drawstyleroot);
    this->drawstyleroot->whichChild = SO_SWITCH_NONE;
  }

  // Hidden line rendering subgraph.
  {
    this->hiddenlineroot = new SoSwitch;

    this->sobasecolor = new SoBaseColor;
    this->sobasecolor->setOverride(TRUE);
    this->hiddenlineroot->addChild(this->sobasecolor);

    this->somaterialbinding = new SoMaterialBinding;
    this->somaterialbinding->setOverride(TRUE);
    this->somaterialbinding->value = SoMaterialBinding::OVERALL;
    this->hiddenlineroot->addChild(this->somaterialbinding);

#if !defined(COIN_CONFIG_NO_SOPOLYGONOFFSET)
    this->polygonoffsetparent = new SoSwitch;
    this->polygonoffsetparent->whichChild = SO_SWITCH_NONE;
    this->sopolygonoffset = new SoPolygonOffset;
    this->polygonoffsetparent->addChild(this->sopolygonoffset);
    this->hiddenlineroot->addChild(this->polygonoffsetparent);
#endif // !COIN_CONFIG_NO_SOPOLYGONOFFSET

    this->drawstyleroot->addChild(this->hiddenlineroot);
    this->hiddenlineroot->whichChild = SO_SWITCH_NONE;
  }
#endif // !NO_DRAWSTYLESETTING


  this->drawstyles[STILL] = VIEW_AS_IS;
  this->drawstyles[INTERACTIVE] = VIEW_SAME_AS_STILL;

  this->lighton = TRUE;
  this->lightroot = NULL;

  this->addStartCallback(SoQtViewer::interactivestartCB);
  this->addFinishCallback(SoQtViewer::interactiveendCB);

  this->adjustclipplanes = TRUE;
  this->autoclipbox = NULL;

  if(buildNow) this->setBaseWidget(this->buildWidget(this->getParentWidget()));
}

/*!
  Destructor.
 */
SoQtViewer::~SoQtViewer()
{
  delete this->autoclipbox;

  delete this->interactionstartCallbacks;
  delete this->interactionendCallbacks;

  delete this->seeksensor;

  if (this->userroot) this->setSceneGraph(NULL);
  if (this->lightroot) this->lightroot->unref();
  this->viewerroot->unref();
}

/*!
  Set the camera we want to view the scene with. This will
  set it up with the headlight and register it for later retrieval
  (from getCamera()) and subsequent use.

  \sa getCamera()
 */
void
SoQtViewer::setCamera(SoCamera * cam)
{
  // Store for re-enabling after camera is attached.
  SbBool headlightflag = this->isHeadlight();

  if (this->camera) {
    // Detach headlight.
    if (this->isHeadlight()) this->setHeadlight(FALSE);
	
    // If we made the camera, detach it. Otherwise just leave it in
    // the graph.
    if (this->deletecamera) {
      SoGroup * cameraparent = getParentOfNode(this->viewerroot, this->camera);
      cameraparent->removeChild(this->camera);
      this->deletecamera = FALSE;
    }

    this->camera->unref();
  }
    
  this->camera = cam;
    
  if (this->camera) {
    this->camera->ref();
    this->saveHomePosition();
    if (headlightflag) this->setHeadlight(TRUE);
  }
}

/*!
  Returns the camera currently used by the viewer for rendering
  the scene.

  \sa setCamera()
 */
SoCamera *
SoQtViewer::getCamera(void) const
{
  return this->camera;
}

/*!
  When the viewer has to make its own camera as a result of the graph
  passed to setSceneGraph() not containing any camera nodes, this call
  can be made in advance to decide which type the camera will be of.

  Default is to use an SoPerspectiveCamera.

  \sa getCameraType()
 */
void
SoQtViewer::setCameraType(SoType t)
{
#if SOQT_DEBUG
  SbBool valid = TRUE;
  if (t == SoType::badType()) valid = FALSE;
  if (valid) {
    valid = FALSE;
#if !defined(COIN_CONFIG_NO_SOPERSPECTIVECAMERA)
    if (t.isDerivedFrom(SoPerspectiveCamera::getClassTypeId())) valid = TRUE;
#endif // !COIN_CONFIG_NO_SOPERSPECTIVECAMERA
#if !defined(COIN_CONFIG_NO_SOORTHOGRAPHICCAMERA)
    if (t.isDerivedFrom(SoOrthographicCamera::getClassTypeId())) valid = TRUE;
#endif // !COIN_CONFIG_NO_SOORTHOGRAPHICCAMERA
  }

  if (!valid) {
    SoDebugError::post("SoQtViewer::setCameraType",
		       "not a valid camera type: '%s'",
		       t == SoType::badType() ?
		       "badType" : t.getName().getString());
    return;
  }
#endif // SOQT_DEBUG

  this->cameratype = t;
}

/*!
  Returns camera type which will be used when the viewer has to make its
  own camera.

  Note that this call does \e not return the current cameratype, as one
  might expect. Use getCamera() and SoType::getTypeId() for that inquiry.

  \sa setCameraType()
 */
SoType
SoQtViewer::getCameraType(void) const
{
  return this->cameratype;
}

/*!
  Reposition the current camera so we can see the complete scene.
 */
void
SoQtViewer::viewAll(void)
{
  assert(this->camera);
  this->camera->viewAll(this->userroot, this->getViewportRegion());
}

/*!
  Store the current camera settings for later retrieval with 
  resetToHomePosition().

  \sa resetToHomePosition()
 */
void
SoQtViewer::saveHomePosition(void)
{
  assert(this->camera);
    
  this->storedorientation = this->camera->orientation.getValue();
  this->storedposition = this->camera->position.getValue();

  SoType t = this->camera->getTypeId();
#if !defined(COIN_CONFIG_NO_SOORTHOGRAPHICCAMERA)
  if (t.isDerivedFrom(SoOrthographicCamera::getClassTypeId()))
    this->storedheightval =
      ((SoOrthographicCamera *)this->camera)->height.getValue();
#endif // !COIN_CONFIG_NO_SOORTHOGRAPHICCAMERA
#if !defined(COIN_CONFIG_NO_SOPERSPECTIVECAMERA)
  if (t.isDerivedFrom(SoPerspectiveCamera::getClassTypeId()))
    this->storedheightval =
      ((SoPerspectiveCamera *)this->camera)->heightAngle.getValue();
#endif // !COIN_CONFIG_NO_SOPERSPECTIVECAMERA
}

/*!
  Restore the saved camera settings.

  \sa saveHomePosition()
 */
void
SoQtViewer::resetToHomePosition(void)
{
  assert(this->camera);
    
  this->camera->orientation = this->storedorientation;
  this->camera->position = this->storedposition;

  SoType t = this->camera->getTypeId();
#if !defined(COIN_CONFIG_NO_SOORTHOGRAPHICCAMERA)
  if (t.isDerivedFrom(SoOrthographicCamera::getClassTypeId()))
    ((SoOrthographicCamera *)this->camera)->height = this->storedheightval;
#endif // !COIN_CONFIG_NO_SOORTHOGRAPHICCAMERA
#if !defined(COIN_CONFIG_NO_SOPERSPECTIVECAMERA)
  if (t.isDerivedFrom(SoPerspectiveCamera::getClassTypeId()))
    ((SoPerspectiveCamera *)this->camera)->heightAngle = this->storedheightval;
#endif // !COIN_CONFIG_NO_SOPERSPECTIVECAMERA

  this->setClippingPlanes();
  this->camera->focalDistance =
    (this->camera->farDistance.getValue() +
     this->camera->nearDistance.getValue())/2;
}

/*!
  Turn the camera headlight on or off.

  Default is to have a headlight turned on.

  \sa isHeadlight(), getHeadlight()
 */
void
SoQtViewer::setHeadlight(SbBool on)
{
#if SOQT_DEBUG
  if (this->lightroot &&
      ((on && this->isHeadlight()) || (!on && !this->isHeadlight()))) {
    SoDebugError::postWarning("SoQtViewer::setHeadlight",
			      "headlight already turned %s",
			      on ? "on" : "off");
    return;
  }
#endif // SOQT_DEBUG

#if !defined(NO_HEADLIGHT)
  SoSearchAction search;

  if (on) {
    if (!this->lightroot) {
      this->lightroot = new SoGroup;
      this->lightroot->ref();
      this->lightroot->addChild(new SoRotation);
      SoDirectionalLight * dl = new SoDirectionalLight;
      dl->direction.setValue(1, -1, -10);
      this->lightroot->addChild(dl);
      this->lightroot->addChild(new SoResetTransform);
    }

    assert(this->camera);
    SoGroup * cameraparent = getParentOfNode(this->viewerroot, this->camera);
    int idx = cameraparent->findChild(this->camera);
    cameraparent->insertChild(this->lightroot, idx+1);

    SoRotation * lorient = (SoRotation *) this->lightroot->getChild(0);
    lorient->rotation.connectFrom(& this->camera->orientation);
  }
  else {
    assert(this->lightroot);
    SoGroup * lightparent = getParentOfNode(this->viewerroot, this->lightroot);
    lightparent->removeChild(this->lightroot);

    SoRotation * lorient = (SoRotation *) this->lightroot->getChild(0);
    lorient->rotation.disconnect();
  }
    
  this->lighton = on;
#endif // !NO_HEADLIGHT
}

/*!
  Returns status of the viewer headlight, whether it is on or off.

  Note that the returned flag does not check the state of the \a on
  field of the SoDirectionalLight headlight node, it only indicates
  whether or not a headlight is part of the scene graph.

  \sa setHeadlight(), getHeadlight()
 */
SbBool
SoQtViewer::isHeadlight(void) const
{
  return this->lighton;
}

/*!
  Returns the a pointer to the directional light node which is the
  viewer headlight.

  The fields of the node is available for user editing.

  \sa isHeadlight(), setHeadlight()
 */
SoDirectionalLight *
SoQtViewer::getHeadlight(void) const
{
#if !defined(NO_HEADLIGHT)
  if (!this->lightroot) return NULL;

  SoDirectionalLight * dl =
    (SoDirectionalLight *) this->lightroot->getChild(1);
  assert(dl->isOfType(SoDirectionalLight::getClassTypeId()));
  return dl;
#else // NO_HEADLIGHT
  return NULL;
#endif // NO_HEADLIGHT
}

/*!
  Set up a drawing style. The \a type argument specifies if the given
  \a style should be interpreted as the drawstyle during animation or
  when the camera is static.

  Default values for the drawing style is to render the scene "as is"
  in both still mode and while the camera is moving.

  See the documentation for the \a DrawType and \a DrawStyle for more
  information.

  \sa getDrawStyle()
 */
void
SoQtViewer::setDrawStyle(SoQtViewer::DrawType type,
			 SoQtViewer::DrawStyle style)
{
#if SOQT_DEBUG
  if ((type != STILL) && (type != INTERACTIVE)) {
    SoDebugError::postWarning("SoQtViewer::setDrawStyle",
			      "unknown drawstyle type setting 0x%x", type);
    return;
  }
  int s = style & ALL_STYLES_COMBINED;
  int bits = 0;
  while (s) { if (s & 0x0001) bits++; s >>= 1; }
  if (bits != 1) {
    SoDebugError::postWarning("SoQtViewer::setDrawStyle",
			      "unknown drawstyle setting 0x04%x", style);
    return;
  }
#endif // SOQT_DEBUG

  if (style == this->getDrawStyle(type)) {
#if 0 // SOQT_DEBUG
    SoDebugError::postWarning("SoQtViewer::setDrawStyle",
			      "drawstyle for type 0x%02x already 0x%02x",
			      type, style);
#endif // SOQT_DEBUG
    return;
  }

  this->drawstyles[type] = style;
  this->changeDrawStyle(this->currentDrawStyle());
}

/*!
  Return current drawstyles for the given type (\a STILL or
  \a INTERACTIVE).

  \sa setDrawStyle()
 */
SoQtViewer::DrawStyle
SoQtViewer::getDrawStyle(const SoQtViewer::DrawType type) const
{
#if SOQT_DEBUG
  if ((type != STILL) && (type != INTERACTIVE)) {
    SoDebugError::postWarning("SoQtViewer::setDrawStyle",
			      "unknown drawstyle type setting 0x%x", type);
    return this->drawstyles[STILL];
  }
#endif // SOQT_DEBUG
  return this->drawstyles[type];
}

/*!
  Set the viewer's buffer type.

  Default is to use a double buffering scheme.

  \sa getBufferingType()
 */
void
SoQtViewer::setBufferingType(SoQtViewer::BufferType type)
{
#if 0 // SOQT_DEBUG
  if (type == this->buffertype) {
    SoDebugError::postWarning("SoQtViewer::setBufferingType",
			      "buffer type 0x%x already set", type);
    return;
  }

  if (type != BUFFER_SINGLE &&
      type != BUFFER_DOUBLE &&
      type != BUFFER_INTERACTIVE) {
    SoDebugError::postWarning("SoQtViewer::setBufferingType",
			      "unknown buffer type 0x%x", type);
    return;
  }
#endif // SOQT_DEBUG
    
  this->buffertype = type;
  inherited::setDoubleBuffer(type == BUFFER_DOUBLE ? TRUE : FALSE);
}

/*!
  Return the viewer's buffer type.

  \sa setBufferingType()
 */
SoQtViewer::BufferType
SoQtViewer::getBufferingType(void) const
{
  return this->buffertype;
}

/*!
  Set view mode.

  If the view mode is on, user events will be caught and used to
  influence the camera position/orientation. If view mode is off,
  all events in the viewer canvas will be passed along to the scene
  graph.

  Default is to have the view mode active.

  \sa getViewing()
 */
void
SoQtViewer::setViewing(SbBool on)
{
#if SOQT_DEBUG
  if (this->viewmode == on) {
    SoDebugError::postWarning("SoQtViewer::setViewing", "unnecessary called");
    return;
  }
#endif // SOQT_DEBUG
    
#if !defined(COIN_CONFIG_NO_SOLOCATEHIGHLIGHT)
  // Turn off the selection indicators when we go back from picking
  // mode into viewing mode.
  if (on) {
    SoGLRenderAction * action = this->getGLRenderAction();
    if (action) SoLocateHighlight::turnOffCurrentHighlight(action);
  }
#endif // !COIN_CONFIG_NO_SOLOCATEHIGHLIGHT

  this->viewmode = on;
}

/*!
  Return state of view mode.

  \sa setViewing()
 */
SbBool
SoQtViewer::isViewing(void) const
{
  return this->viewmode;
}

/*!
  Set whether or not the mouse cursor representation should be visible
  in the viewer canvas.

  Default value is on.

  \sa getCursorEnabled()
 */
void
SoQtViewer::setCursorEnabled(SbBool on)
{
  this->cursoron = on;
}

/*!
  Returns visibility status of mouse cursor.

  \sa setCursorEnabled()
 */
SbBool
SoQtViewer::isCursorEnabled(void) const
{
  return this->cursoron;
}

/*!
  Turn on or off continuous automatic adjustments of the near
  and far clipping planes.

  Automatic clipping is on as default.

  \sa getAutoClipping()
 */
void
SoQtViewer::setAutoClipping(SbBool on)
{
#if SOQT_DEBUG
  if (this->adjustclipplanes == on) {
    SoDebugError::postWarning("SoQtViewer::setAutoClipping",
			      "unnecessary called");
    return;
  }
#endif // SOQT_DEBUG
  this->adjustclipplanes = on;
  if (on) this->scheduleRedraw();
}

/*!
  Return value of the automatic near/far clipplane adjustment indicator.

  \sa setAutoClipping()
 */
SbBool
SoQtViewer::isAutoClipping(void) const
{
  return this->adjustclipplanes;
}

/*!
  Turn stereo viewing on. Default is off.

  NB: stereo viewing has not been implemented for this component library
  yet.

  \sa isStereoViewing()
*/
void
SoQtViewer::setStereoViewing(SbBool on)
{
  // FIXME: implement. 990507 mortene.
  SoDebugError::postInfo("SoQtViewer::setStereoViewing",
			 "stereo viewing not implemented yet");
}

/*!
  Returns a boolean indicating whether or not we're in stereo viewing
  mode.

  \sa setStereoViewing()
 */
SbBool
SoQtViewer::isStereoViewing(void) const
{
  // FIXME: implement. 990507 mortene.
  return FALSE;
}

/*!
  Set the offset between the two viewpoints when in stereo mode.

  NB: stereo viewing has not been implemented for this component library
  yet.

  \sa getStereoOffset()
 */
void
SoQtViewer::setStereoOffset(const float dist)
{
  // FIXME: implement. 990507 mortene.
  SoDebugError::postInfo("SoQtViewer::setStereoOffset",
			 "stereo viewing not implemented yet");
}

/*!
  Return the offset distance between the two viewpoints when in stereo mode.

  \sa setStereoOffset()
 */
float
SoQtViewer::getStereoOffset(void) const
{
  // FIXME: implement. 990507 mortene.
  return 0.0f;
}

/*!
  Toggle between seeking to a point or seeking to an object.

  Default is to seek to a point.

  \sa isDetailSeek()
 */
void
SoQtViewer::setDetailSeek(const SbBool on)
{
#if SOQT_DEBUG
  if (this->seektopoint == on) {
    SoDebugError::postWarning("SoQtViewer::setDetailSeek",
			      "unnecessary called");
    return;
  }
#endif // SOQT_DEBUG
  this->seektopoint = on;
}

/*!
  Returns a value indicating whether or not seeks will be performed
  to the exact point of picking or just towards the picked object.

  \sa setDetailSeek()
 */
SbBool
SoQtViewer::isDetailSeek(void) const
{
  return this->seektopoint;
}

/*!
  Set the duration of animating the camera repositioning
  after a successful seek. Call with \a seconds equal to \a 0.0 to make
  the camera jump immediately to the correct spot.

  Default value is 2 seconds.

  \sa getSeekTime()
 */
void
SoQtViewer::setSeekTime(const float seconds)
{
#if SOQT_DEBUG
  if (seconds < 0.0f) {
    SoDebugError::postWarning("SoQtViewer::setSeekTime",
			      "an attempt was made to set a negative seek "
			      "time duration");
    return;
  }
#endif SOQT_DEBUG
  this->seekperiod = seconds;
}

/*!
  Returns the camera repositioning duration following a seek action.

  \sa setSeekTime()
 */
float
SoQtViewer::getSeekTime(void) const
{
  return this->seekperiod;
}

/*!
  Add a function to call when user interaction with the scene starts.

  \sa removeStartCallback(), addFinishCallback()
 */
void
SoQtViewer::addStartCallback(SoQtViewerCB * func, void * data)
{
  this->interactionstartCallbacks->addCallback((SoCallbackListCB *)func, data);
}

/*!
  Add a function to call when user interaction with the scene ends.

  \sa removeFinishCallback(), addStartCallback()
 */
void
SoQtViewer::addFinishCallback(SoQtViewerCB * func, void * data)
{
  this->interactionendCallbacks->addCallback((SoCallbackListCB *)func, data);
}

/*!
  Remove one of the functions which has been set up to be called when user
  interaction with the scene starts.

  \sa addStartCallback(), removeFinishCallback()
 */
void
SoQtViewer::removeStartCallback(SoQtViewerCB * func, void * data)
{
  this->interactionstartCallbacks->removeCallback((SoCallbackListCB *)func,
						  data);
}

/*!
  Remove one of the functions which has been set up to be called when user
  interaction with the scene ends.

  \sa addFinishCallback(), removeStartCallback()
 */
void
SoQtViewer::removeFinishCallback(SoQtViewerCB * func, void * data)
{
  this->interactionendCallbacks->removeCallback((SoCallbackListCB *)func,
						data);
}

/*!
  Copy the current camera to the system clipboard. This makes it
  easy to synchronize camera settings over different applications.

  Note: has not been implemented yet.

  \sa pasteView()
 */
void
SoQtViewer::copyView(const SbTime eventTime)
{
  // FIXME: not implemented. Needs SoQtClipboard implementation
  // first. 990507 mortene.

  SoDebugError::postInfo("SoQtViewer::copyView",
			 "clipboard support not implemented yet");
}

/*!
  Set a new camera from the system clipboard.

  Note: has not been implemented yet.

  \sa copyView()
 */
void
SoQtViewer::pasteView(const SbTime eventTime)
{
  // FIXME: not implemented. Needs SoQtClipboard implementation
  // first. 990507 mortene.

  SoDebugError::postInfo("SoQtViewer::pasteView",
			 "clipboard support not implemented yet");
}

/*!
  Not used, only included for compatibility reasons.
 */
void
SoQtViewer::recomputeSceneSize(void)
{
  SoDebugError::postInfo("SoQtViewer::recomputeSceneSize",
			 "this method is obsoleted, don't use it");
}

/*!
  Large Model Visualization; not implemented yet.
 */
void
SoQtViewer::setDecimationStrategy(const SoQtViewer::DecimationStrategy strategy)
{
  // FIXME: implement. 990508 mortene.
  SoDebugError::postInfo("SoQtViewer::setDecimationStrategy",
			 "not implemented yet");
}

/*!
  Large Model Visualization; not implemented yet.
 */
SoQtViewer::DecimationStrategy
SoQtViewer::getDecimationStrategy(void) const
{
  // FIXME: implement. 990508 mortene.
  SoDebugError::postInfo("SoQtViewer::getDecimationStrategy",
			 "not implemented yet");
  return NORMAL;
}


/*!
  Large Model Visualization; not implemented yet.
 */
void
SoQtViewer::setGoalNumberOfTriangles(const int32_t goal)
{
  // FIXME: implement. 990508 mortene.
  SoDebugError::postInfo("SoQtViewer::setGoalNumberOfTriangles",
			 "not implemented yet");
}

/*!
  Large Model Visualization; not implemented yet.
 */
int32_t
SoQtViewer::getGoalNumberOfTriangles(void) const
{
  // FIXME: implement. 990508 mortene.
  SoDebugError::postInfo("SoQtViewer::getGoalNumberOfTriangles",
			 "not implemented yet");
  return -1;
}


/*!
  Large Model Visualization; not implemented yet.
 */
void
SoQtViewer::setGoalFramesPerSecond(const float goal)
{
  // FIXME: implement. 990508 mortene.
  SoDebugError::postInfo("SoQtViewer::setGoalFramesPerSecond",
			 "not implemented yet");
}

/*!
  Large Model Visualization; not implemented yet.
 */
float
SoQtViewer::getGoalFramesPerSecond(void) const
{
  // FIXME: implement. 990508 mortene.
  SoDebugError::postInfo("SoQtViewer::getGoalFramesPerSecond",
			 "not implemented yet");
  return 72.0f;
}


/*!
  Large Model Visualization; not implemented yet.
 */
void
SoQtViewer::setFixedPercentage(const float percent)
{
  // FIXME: implement. 990508 mortene.
  SoDebugError::postInfo("SoQtViewer::setFixedPercentage",
			 "not implemented yet");
}

/*!
  Large Model Visualization; not implemented yet.
 */
float
SoQtViewer::getFixedPercentage(void) const
{
  // FIXME: implement. 990508 mortene.
  SoDebugError::postInfo("SoQtViewer::getFixedPercentage",
			 "not implemented yet");
  return 100.0f;
}


/*!
  Large Model Visualization; not implemented yet.
 */
void
SoQtViewer::enableFullRenderingWhenStill(const SbBool on)
{
  // FIXME: implement. 990508 mortene.
  SoDebugError::postInfo("SoQtViewer::enableFullRenderingWhenStill",
			 "not implemented yet");
}

/*!
  Large Model Visualization; not implemented yet.
 */
SbBool
SoQtViewer::isFullRenderingWhenStill(void) const
{
  // FIXME: implement. 990508 mortene.
  SoDebugError::postInfo("SoQtViewer::isFullRenderingWhenStill",
			 "not implemented yet");
  return TRUE;
}

/*!
  Large Model Visualization; not implemented yet.
 */
SbBool
SoQtViewer::isStillNow(void) const
{
  // FIXME: implement. 990508 mortene.
  SoDebugError::postInfo("SoQtViewer::isStillNow",
			 "not implemented yet");
  return this->getInteractiveCount() == 0;
}


/*!
  Large Model Visualization; not implemented yet.
 */
void
SoQtViewer::setFramesPerSecondCallback(SoQtViewerFPSCB * callback, void * data)
{
  // FIXME: implement. 990508 mortene.
  SoDebugError::postInfo("SoQtViewer::setFramesPerSecondCallback",
			 "not implemented yet");
}


/*!
  Large Model Visualization; not implemented yet.
 */
void
SoQtViewer::setNumSamples(const int numFrames)
{
  // FIXME: implement. 990508 mortene.
  SoDebugError::postInfo("SoQtViewer::setNumSamples",
			 "not implemented yet");
}

/*!
  Large Model Visualization; not implemented yet.
 */
int
SoQtViewer::getNumSamples(void) const
{
  // FIXME: implement. 990508 mortene.
  SoDebugError::postInfo("SoQtViewer::getNumSamples",
			 "not implemented yet");
  return 10;
}


/*!
  Large Model Visualization; not implemented yet.
 */
void
SoQtViewer::setDecimationPercentageCallback(SoQtViewerDecimationPercentageCB * cb, void * data)
{
  // FIXME: implement. 990508 mortene.
  SoDebugError::postInfo("SoQtViewer::setDecimationPercentageCallback",
			 "not implemented yet");
}

/*!
  Large Model Visualization; not implemented yet.
 */
float
SoQtViewer::getCurrentDecimationPercentage(void) const
{
  // FIXME: implement. 990508 mortene.
  SoDebugError::postInfo("SoQtViewer::getCurrentDecimationPercentage",
			 "not implemented yet");
  return 100.0f;
}

/*!
  Overloaded to update the local bufferingtype variable.

  \sa setBufferingType(), getBufferingType()
 */
void
SoQtViewer::setDoubleBuffer(SbBool on)
{
  this->buffertype = on ? BUFFER_DOUBLE : BUFFER_SINGLE;
  inherited::setDoubleBuffer(on);
}

/*!
  Give the viewer a scenegraph to render and interact with. Overloaded
  from parent class so the viewer can add it's own nodes to control
  rendering in different styles, rendering with a headlight, etc.

  The \a root node will be inserted under the \e viewer's root node,
  which also covers the nodes necessary to implement the different
  preferences drawing style settings.

  If no camera is part of the scene graph under \a root, one will be
  added automatically.

  \sa getSceneGraph(), setCameraType()
 */
void
SoQtViewer::setSceneGraph(SoNode * root)
{
  if (!inherited::getSceneGraph()) inherited::setSceneGraph(this->viewerroot);

  if (this->userroot) {
    if (this->getCamera()) this->setCamera(NULL);
    // Release the old user-supplied graph.
    this->viewerroot->removeChild(this->userroot);
  }

  this->userroot = root;
  if (!root) return;

  this->viewerroot->addChild(this->userroot);
 
  // Search for a camera already present.
  SoSearchAction search;
  search.setType(SoCamera::getClassTypeId());
  search.apply(this->userroot);
  SoCamera * scenecamera = NULL;
  SoFullPath * fullpath = (SoFullPath *)search.getPath();
  if (fullpath) scenecamera = (SoCamera *)fullpath->getTail();

#if 0 // debug
  SoDebugError::postInfo("SoQtViewer::setSceneGraph",
			 "camera %sfound in graph",
			 scenecamera ? "" : "not ");
#endif // debug
 
  // Make our own camera if none was available.
  if (!scenecamera) {
    scenecamera = (SoCamera *)this->cameratype.createInstance();
    this->deletecamera = TRUE;

    if (this->viewertype == SoQtViewer::BROWSER) {
      this->viewerroot->insertChild(scenecamera, 1);
    }
    else {
      if (this->userroot->isOfType(SoGroup::getClassTypeId())) {
	((SoGroup *)this->userroot)->insertChild(scenecamera, 0);
      }
      else {
	SoGroup * g = new SoGroup;
	g->addChild(scenecamera);
	g->addChild(this->userroot);
	this->viewerroot->removeChild(this->userroot);
	this->viewerroot->addChild(g);
	this->userroot = g;
      }
    }

    scenecamera->viewAll(this->userroot, this->getViewportRegion());
  }
 
  // This will set up the headlight
  this->setCamera(scenecamera);
}

/*!
  Overloaded from parent class to return the root of the scene graph
  set by the user, without the extras added by the viewer to control
  rendering.

  \sa setSceneGraph()
 */
SoNode *
SoQtViewer::getSceneGraph(void)
{
  return this->userroot;
}

/*!
  Put the viewer in or out of seek mode.

  If the user performs a mouse button click when the viewer is in seek
  mode, the camera will be repositioned so the camera focal point lies
  on the point of the geometry under the mouse cursor.

  \sa isSeekMode(), setDetailSeek()
 */
void
SoQtViewer::setSeekMode(SbBool on)
{
  assert(this->isViewing());
    
  if (!on && this->seeksensor->isScheduled()) {
    this->seeksensor->unschedule();
    this->interactiveCountDec();
  }
    
  this->inseekmode = on;
}

/*!
  Return a flag which indicates whether or not the viewer is in seek mode.

  \sa setSeekMode()
 */
SbBool
SoQtViewer::isSeekMode(void) const
{
  return this->inseekmode;
}

/*!
  Call this method to initiate a seek action towards the 3D intersection
  of the scene and the ray from the screen coordinate's point and in the same
  direction as the camera is pointing.

  Returns \a TRUE if the ray from the \a screenpos position intersect with
  any parts of the onscreen geometry, otherwise FALSE.
 */
SbBool
SoQtViewer::seekToPoint(const SbVec2s & screenpos)
{
  assert(this->camera);
    
#if !defined(COIN_CONFIG_NO_SORAYPICKACTION)
  SoRayPickAction rpaction(this->getViewportRegion());
  rpaction.setPoint(screenpos);
  rpaction.setRadius(2);
  rpaction.apply(this->viewerroot);
    
  SoPickedPoint * picked = rpaction.getPickedPoint();
  if (!picked) return FALSE;
    
  SbVec3f hitpoint;
  if (this->seektopoint) {
    hitpoint = picked->getPoint();
  }
  else {
    SoGetBoundingBoxAction bbaction(this->getViewportRegion());
    bbaction.apply(picked->getPath());
    SbBox3f bbox = bbaction.getBoundingBox();
    hitpoint = bbox.getCenter();
  }
    
  this->camerastartposition = this->camera->position.getValue();

  float fd = this->seekdistance;
  if (this->seekdistanceabs)
    fd *= (hitpoint - this->camera->position.getValue()).length()/100.0f;
  this->camera->focalDistance = fd;
	
  SbVec3f dir;
  this->camera->orientation.getValue().multVec(SbVec3f(0, 0, -1), dir);
  this->cameraendposition = hitpoint - fd * dir;

  if (!this->seeksensor->isScheduled()) {
    this->seeksensor->setBaseTime(SbTime::getTimeOfDay());
    this->seeksensor->schedule();
    this->interactiveCountInc();
  }

  return TRUE;
#else // COIN_CONFIG_NO_SORAYPICKACTION
//    this->setSeekMode(FALSE);
#ifdef SOQT_DEBUG
  SoDebugError::postWarning("SoQtViewer::seekToPoint",
			    "no SoRayPickAction available");
#endif // SOQT_DEBUG
  return FALSE;
#endif // COIN_CONFIG_NO_SORAYPICKACTION
}

/*!
  Overloaded from parent class to be able to do the necessary two-pass
  rendering if the drawing style is \e hidden \e line.
 */
void
SoQtViewer::actualRedraw(void)
{
  // Recalculate near/far planes.
  if (this->isAutoClipping()) this->setClippingPlanes();
    
#if !defined(NO_DRAWSTYLESETTING)
  if (this->drawAsHiddenLine()) {
    this->sodrawstyle->style = SoDrawStyle::FILLED;
    this->somaterialbinding->value.setIgnored(FALSE);
    this->sobasecolor->rgb.setValue(this->getBackgroundColor());
    this->sobasecolor->rgb.setIgnored(FALSE);

#if !defined(COIN_CONFIG_NO_SOPOLYGONOFFSET)
    this->polygonoffsetparent->whichChild = SO_SWITCH_ALL;
#endif // !COIN_CONFIG_NO_SOPOLYGONOFFSET

    this->getSceneManager()->render(this->isClearBeforeRender(), TRUE);

    this->sodrawstyle->style = SoDrawStyle::LINES;
    this->somaterialbinding->value.setIgnored(TRUE);
    this->sobasecolor->rgb.setIgnored(TRUE);
#if !defined(COIN_CONFIG_NO_SOPOLYGONOFFSET)
    this->polygonoffsetparent->whichChild = SO_SWITCH_NONE;
#endif // !COIN_CONFIG_NO_SOPOLYGONOFFSET

    this->getSceneManager()->render(FALSE, FALSE);

    return;
  }
#endif // NO_DRAWSTYLESETTING

  DrawStyle style = this->currentDrawStyle();
  SbBool clearzbuffer =
    (style & (VIEW_LOW_RES_LINE|VIEW_LOW_RES_POINT|VIEW_BBOX)) ? FALSE : TRUE;
  this->getSceneManager()->render(isClearBeforeRender(), clearzbuffer);
}

/*!
  This method should be called from subclasses to handle events
  with common interpretation for all viewer classes.
 */
SbBool
SoQtViewer::processCommonEvents(QEvent * e)
{
  // Check if the application wants to "steal" the event.
  if (inherited::invokeAppCB(e)) return TRUE;
    
  // Hit Escape to toggle between interact and examine viewer modes.
  if (e->type() == Event_KeyPress) {
    QKeyEvent * ke = (QKeyEvent *)e;
    if (ke->key() == Key_Escape) {
      this->setViewing(this->isViewing() ? FALSE : TRUE);
      return TRUE;
    }
  }
    
  // If we're in interact mode, don't catch anything else than Esc
  // presses, everything else should be passed on to the scene graph.
  if (!this->isViewing()) {
    inherited::processEvent(e);
    return TRUE;
  }
  
  if (e->type() == Event_KeyPress) {
    QKeyEvent * ke = (QKeyEvent *)e;
    SbVec2f pos(0.0f, 0.0f);

    switch (ke->key()) {
    case Key_Home:
      this->resetToHomePosition();
      return TRUE;
      
    case Key_S:
      this->setSeekMode(this->isSeekMode() ? FALSE : TRUE);
      return TRUE;

    case Key_Left:
      pos.setValue(-0.1f, 0.0f);
      break;
    case Key_Down:
      pos.setValue(0.0f, -0.1f);
      break;
    case Key_Right:
      pos.setValue(0.1f, 0.0f);
      break;
    case Key_Up:
      pos.setValue(0.0f, 0.1f);
      break;

    default:
      return FALSE;
    }

    // Arrow keys falls through to this code.
    assert(pos != SbVec2f(0.0f, 0.0f));
    this->moveCameraScreen(pos);
    return TRUE;
  }
    
  return FALSE;
}

/*!
  To be able to trigger callback functions when user interaction starts
  and/or stops, we need to keep track of the viewer state (i.e. are we in
  still mode or in animation mode?).

  SoQtViewer automatically adds callbacks to switch between still and
  moving draw style, and to switch between single/double buffer when
  the buffer type is \a INTERACTIVE.

  \sa interactiveCountDec(), getInteractiveCount()
  \sa addStartCallback(), addFinishCallback()
  \sa removeStartCallback(), removeFinishCallback()
  \sa setDrawStyle(), setBufferingType()
 */
void
SoQtViewer::interactiveCountInc(void)
{
  // Catch problems with missing interactiveCountDec() calls.
  assert(this->interactionnesting < 100);

  if (++(this->interactionnesting) == 1)
    this->interactionstartCallbacks->invokeCallbacks(this);

#if 0 // debug
  SoDebugError::postInfo("SoQtViewer::interactiveCountInc", "%d -> %d",
			 this->interactionnesting - 1,
			 this->interactionnesting);
#endif // debug
}

/*!
  To be able to trigger callback functions when user interaction starts
  and/or stops, we need to keep track of the viewer state (i.e. are we in
  still mode or in animation mode?).

  SoQtViewer automatically adds callbacks to switch between still and
  moving draw style, and to switch between single/double buffer when
  the buffer type is \a INTERACTIVE.

  \sa interactiveCountInc(), getInteractiveCount()
  \sa addStartCallback(), addFinishCallback()
  \sa removeStartCallback(), removeFinishCallback()
  \sa setDrawStyle(), setBufferingType()
 */
void
SoQtViewer::interactiveCountDec(void)
{
  // Catch problems with missing interactiveCountInc() calls.
  assert(this->interactionnesting > 0);

  if (--(this->interactionnesting) == 0)
    this->interactionendCallbacks->invokeCallbacks(this);

#if 0 // debug
  SoDebugError::postInfo("SoQtViewer::interactiveCountDec", "%d -> %d",
			 this->interactionnesting + 1,
			 this->interactionnesting);
#endif // debug
}

/*!
  Return current interaction count nesting. If equal to zero, the viewer
  is in animation mode, otherwise the camera is still.

  \sa interactiveCountInc(), interactiveCountDec()
 */
int
SoQtViewer::getInteractiveCount(void) const
{
  return this->interactionnesting;
}

/*!
  Set the value used for calculating how close the camera and intersection
  hit point should be made at the end of a seek operation.

  The value can be interpreted as an absolute value in the given world
  unit (which typically is meters) or as a percentage value of the
  distance between the camera starting position and the intersection
  hit point. This can be controlled through the
  setSeekValueAsPercentage() method. It is as default used as an
  absolute value.

  Default value is 50 (absolute distance or percent).

  \sa getSeekDistance(), setSeekValueAsPercentage(), setSeekTime()
 */
void
SoQtViewer::setSeekDistance(const float distance)
{
#if SOQT_DEBUG
  if (distance <= 0.0f) {
    SoDebugError::postWarning("SoQtViewer::setSeekDistance",
			      "invalid seek distance value: %f",
			      distance);
    return;
  }
#endif // SOQT_DEBUG
  this->seekdistance = distance;
}

/*!
  Returns the current seek distance. Value given as an absolute scalar
  length or as a percentage value of the original distance between
  the hitpoint and the camera starting position.

  \sa setSeekDistance(), isSeekValueAsPercentage()
 */
float
SoQtViewer::getSeekDistance(void) const
{
  return this->seekdistance;
}

/*!
  Control whether or not the seek distance value should be interpreted as
  a percentage value or as an absolute distance. See documentation on
  setSeekDistance() for more information.

  \sa setSeekDistance(), isSeekValueAsPercentage()
 */
void
SoQtViewer::setSeekValueAsPercentage(const SbBool on)
{
#if SOQT_DEBUG
  if ((on && this->isSeekValuePercentage()) ||
      (!on && !this->isSeekValuePercentage())) {
    SoDebugError::postWarning("SoQtViewer::setSeekDistanceAsPercentage",
			      "unnecessary called, value already %s",
			      on ? "on" : "off");
    return;
  }
#endif // SOQT_DEBUG
  this->seekdistanceabs = on ? FALSE : TRUE;
}

/*!
  Returns an boolean which indicates if the seek distance value from
  getSeekDistance() should be interpreted as a percentage value or
  as an absolute value.

  \sa setSeekValuePercentage(), getSeekDistance()
 */
SbBool
SoQtViewer::isSeekValuePercentage(void) const
{
  return this->seekdistanceabs ? FALSE : TRUE;
}

/*!
  If the current camera is of perspective type, switch to orthographic,
  and vice versa.
 */
void
SoQtViewer::toggleCameraType(void)
{
#if defined(COIN_CONFIG_NO_SOPERSPECTIVECAMERA)
#define CAN_NOT_TOGGLE 1
#endif // COIN_CONFIG_NO_SOPERSPECTIVECAMERA
#if defined(COIN_CONFIG_NO_SOORTHOGRAPHICCAMERA)
#define CAN_NOT_TOGGLE 1
#endif // COIN_CONFIG_NO_SOORTHOGRAPHICCAMERA

#if !defined(CAN_NOT_TOGGLE)
  assert(this->camera);

  SoType oldtype = this->camera->getTypeId();
  SoType perspectivetype = SoPerspectiveCamera::getClassTypeId();
  SoType orthotype = SoOrthographicCamera::getClassTypeId();
  SoType newtype = oldtype == perspectivetype ? orthotype : perspectivetype;

  SoCamera * newcamera = (SoCamera *)newtype.createInstance();
  newcamera->aspectRatio.setValue(camera->aspectRatio.getValue());
  newcamera->focalDistance.setValue(camera->focalDistance.getValue());
  newcamera->orientation.setValue(camera->orientation.getValue());
  newcamera->position.setValue(camera->position.getValue());
  newcamera->viewportMapping.setValue(camera->viewportMapping.getValue());

  if (oldtype.isDerivedFrom(perspectivetype)) {
    ((SoOrthographicCamera *)newcamera)->height =
      2 * this->camera->focalDistance.getValue() *
      tan(((SoPerspectiveCamera *)this->camera)->heightAngle.getValue()/2.0f);
  }
  else if (oldtype.isDerivedFrom(orthotype)) {
    ((SoPerspectiveCamera *)newcamera)->heightAngle = 2.0f *
      atan(((SoOrthographicCamera *)this->camera)->height.getValue() / 2.0f /
	   this->camera->focalDistance.getValue());
  }
  else {
    assert(0);
  }
    
  SoGroup * cameraparent = getParentOfNode(this->viewerroot, this->camera);
  cameraparent->insertChild(newcamera, cameraparent->findChild(this->camera));
  SoCamera * oldcamera = !this->deletecamera ? this->camera : NULL;
  this->setCamera(newcamera);
  this->deletecamera = TRUE;
  if (oldcamera) cameraparent->removeChild(oldcamera);
#endif // !CAN_NOT_TOGGLE
#undef CAN_NOT_TOGGLE
}

/*!
  \internal

  Returns a boolean to indicate if the dynamic drawstyle equals
  the static drawstyle.
 */
SbBool
SoQtViewer::drawInteractiveAsStill(void) const
{
  SbBool moveasstill = this->drawstyles[INTERACTIVE] == VIEW_SAME_AS_STILL;
  if (!moveasstill)
    moveasstill = this->drawstyles[INTERACTIVE] == this->drawstyles[STILL];
  if (!moveasstill)
    moveasstill =
      this->drawstyles[INTERACTIVE] == VIEW_NO_TEXTURE &&
      this->drawstyles[STILL] != VIEW_AS_IS;
  return moveasstill;
}

/*!
  \internal

  Returns the current drawing style.
 */
SoQtViewer::DrawStyle
SoQtViewer::currentDrawStyle(void) const
{
  SbBool interactivemode = this->getInteractiveCount() > 0 ? TRUE : FALSE;
  SbBool moveasstill = this->drawInteractiveAsStill();
  
  if (!interactivemode || this->drawInteractiveAsStill())
    return this->drawstyles[STILL];
  else
    return this->drawstyles[INTERACTIVE];
}

/*!
  \internal

  Returns a boolean to indicate if the current drawstyle settings implies
  hidden line rendering.
 */
SbBool
SoQtViewer::drawAsHiddenLine(void) const
{
  return ((this->currentDrawStyle() == VIEW_HIDDEN_LINE) ? TRUE : FALSE);
}

/*!
  \internal

  Use the given style setting to set the correct states in the
  rendering control nodes. This will affect the way the scene is
  currently rendered.
 */
void
SoQtViewer::changeDrawStyle(SoQtViewer::DrawStyle style)
{
#if !defined(NO_DRAWSTYLESETTING)
  // Turn on/off Z-buffering based on the style setting.
  this->getQGLWidget()->makeCurrent();
  DrawStyle s = this->currentDrawStyle();
  if (s & (VIEW_LOW_RES_LINE|VIEW_LOW_RES_POINT|VIEW_BBOX))
    glDisable(GL_DEPTH_TEST);
  else
    glEnable(GL_DEPTH_TEST);


  this->drawstyleroot->whichChild = SO_SWITCH_NONE;

  // Render everything as its supposed to be done, don't override
  // any of the settings in the ``real'' graph.
  if (style == VIEW_AS_IS) return;

  this->drawstyleroot->whichChild = SO_SWITCH_ALL;

  // Further settings for rendering as hidden line will be done in the
  // overloaded actualRedraw().
  if (style == VIEW_HIDDEN_LINE) {
    this->socomplexity->type.setIgnored(TRUE);
    this->socomplexity->value.setIgnored(TRUE);
    this->hiddenlineroot->whichChild = SO_SWITCH_ALL;
    return;
  }
  
  this->hiddenlineroot->whichChild = SO_SWITCH_NONE;

  // Set ignore flags.
  SbBool ignored =
    ((VIEW_NO_TEXTURE|VIEW_LOW_COMPLEXITY) & style) ? TRUE : FALSE;
  this->sodrawstyle->style.setIgnored(ignored);
  this->solightmodel->model.setIgnored(ignored);
  ignored = ((VIEW_NO_TEXTURE|VIEW_LOW_COMPLEXITY|VIEW_LINE|VIEW_POINT) &
	     style) ? TRUE : FALSE;
  this->socomplexity->type.setIgnored(ignored);
  ignored = ((VIEW_NO_TEXTURE|VIEW_LINE|VIEW_POINT|VIEW_BBOX) & style) ?
    TRUE : FALSE;
  this->socomplexity->value.setIgnored(ignored);
  ignored = ((VIEW_NO_TEXTURE|VIEW_LOW_COMPLEXITY|VIEW_LINE|VIEW_LOW_RES_LINE|
	      VIEW_POINT|VIEW_LOW_RES_POINT|VIEW_BBOX) & style) ? TRUE : FALSE;

  // Set draw style.
  if (!this->sodrawstyle->style.isIgnored()) {
    SoDrawStyle::Style ds;
    if (style & (VIEW_LINE|VIEW_LOW_RES_LINE|VIEW_BBOX))
      ds = SoDrawStyle::LINES;
    else if (style & (VIEW_POINT|VIEW_LOW_RES_POINT))
      ds = SoDrawStyle::POINTS;
    else assert(0);

    this->sodrawstyle->style = ds;
  }

  // Set rendering complexity type.
  if (!this->socomplexity->type.isIgnored()) {
    SoComplexity::Type t;
    if (style & (VIEW_LINE|VIEW_LOW_RES_LINE))
      t = SoComplexity::OBJECT_SPACE;
    else if (style & VIEW_BBOX)
      t = SoComplexity::BOUNDING_BOX;
    else assert(0);

    this->socomplexity->type = t;
  }

#if 0 // debug
  SoDebugError::postInfo("SoQtViewer::changeDrawStyle",
			 "\n"
			 "\tdrawstyle style: 0x%02x (isIgnored() == %s)\n"
			 "\tlightmodel model: 0x%02x, (isIgnored() == %s)\n"
			 "\tcomplexity type: 0x%02x, (isIgnored() == %s)\n"
			 "\tcomplexity value: %f, (isIgnored() == %s)\n"
			 "",
			 this->sodrawstyle->style.getValue(),
			 this->sodrawstyle->style.isIgnored() ? "T" : "F",
			 this->solightmodel->model.getValue(),
			 this->solightmodel->model.isIgnored() ? "T" : "F",
			 this->socomplexity->type.getValue(),
			 this->socomplexity->type.isIgnored() ? "T" : "F",
			 this->socomplexity->value.getValue(),
			 this->socomplexity->value.isIgnored() ? "T" : "F");
#endif // debug

#endif // !NO_DRAWSTYLESETTING
}

/*!
  \internal

  Position the near and far clipping planes just in front of and behind 
  the scene's bounding box. This will give us the optimal utilization of
  the z buffer resolution by shrinking it to its minimum depth.
 */
void
SoQtViewer::setClippingPlanes(void)
{
  if (!this->autoclipbox)
    this->autoclipbox = new SoGetBoundingBoxAction(this->getViewportRegion());
  else
    this->autoclipbox->setViewportRegion(this->getViewportRegion());

  this->autoclipbox->apply(this->viewerroot);

  SbXfBox3f xbox = this->autoclipbox->getXfBoundingBox();
  SbMatrix mat;
  mat.setTranslate(- this->camera->position.getValue());
  xbox.transform(mat);
  mat = this->camera->orientation.getValue().inverse();
  xbox.transform(mat);
  SbBox3f box = xbox.project();

  // Bounding box was calculated in camera space, so we need to "flip"
  // the box (because camera is pointing in the (0,0,-1) direction
  // from origo.
  float near = -box.getMax()[2];
  float far = -box.getMin()[2];

  // This factor should really be made dependent on the underlying
  // hardware or software Z buffer resolution.
  const float SLACK = 1.0f/1000.0f;

  // Scene is completely behind us.
  if (far < SLACK) return;

  // Disallow negative near clipping plane distance, and make sure the
  // z-buffer depth utilization is kept below a certain threshold.
  near = QMAX(SLACK * far, near);
    
  // Give a bit of slack to avoid artifacts when scene fits exactly
  // inside bounding box.
  this->camera->nearDistance = near * (1.0f - SLACK);
  this->camera->farDistance = far * (1.0f + SLACK);

#if 0 // debug
  SoDebugError::postInfo("SoQtViewer::setClippingPlanes",
			 "near, far: %f (%f), %f (%f)",
			 near, this->camera->nearDistance.getValue(),
			 far, this->camera->farDistance.getValue());
#endif // debug
}

/*!
  \internal

  Translate camera a distance equal to the difference in projected,
  normalized screen coordinates given by the argument.
 */
void
SoQtViewer::moveCameraScreen(const SbVec2f & screenpos)
{
  SoCamera * cam = this->getCamera();
  assert(cam);
    
#if 1 // debug
  SoDebugError::postInfo("SoQtViewer::moveCameraScreen",
			 "screenpos: <%f, %f>, campos: <%f, %f, %f>",
			 screenpos[0], screenpos[1],
			 cam->position.getValue()[0],
			 cam->position.getValue()[1],
			 cam->position.getValue()[2]);
#endif // debug

  SbViewVolume vv = cam->getViewVolume(this->getGlxAspectRatio());
  SbPlane panplane = vv.getPlane(cam->focalDistance.getValue());

  SbLine line;
  vv.projectPointToLine(screenpos + SbVec2f(0.5, 0.5f), line);
  SbVec3f current_planept;
  panplane.intersect(line, current_planept);
  vv.projectPointToLine(SbVec2f(0.5f, 0.5f), line);
  SbVec3f old_planept;
  panplane.intersect(line, old_planept);

  // Reposition camera according to the vector difference between the
  // projected points.
  cam->position = cam->position.getValue() - (current_planept - old_planept);

#if 1 // debug
  SoDebugError::postInfo("SoQtViewer::moveCameraScreen",
			 "newcampos: <%f, %f, %f>",
			 cam->position.getValue()[0],
			 cam->position.getValue()[1],
			 cam->position.getValue()[2]);
#endif // debug
}

/*!
  \internal

  Called when viewer enters interactive mode (animation, drag, ...).
 */
void
SoQtViewer::interactivestartCB(void *, SoQtViewer * thisp)
{
  // In interactive buffer mode, doublebuffering is used during interaction.
  if (thisp->buffertype == BUFFER_INTERACTIVE)
    thisp->inherited::setDoubleBuffer(TRUE);

  // Use the dynamic drawstyle.
  if (!thisp->drawInteractiveAsStill())
    thisp->changeDrawStyle(thisp->drawstyles[INTERACTIVE]);
}

/*!
  \internal

  Called when viewer goes out of interactive mode and into
  "frozen" mode.
 */
void
SoQtViewer::interactiveendCB(void *, SoQtViewer * thisp)
{
  // In interactive buffer mode, doublebuffering is used during
  // interaction, singelbuffering while the camera is static.
  if (thisp->buffertype == BUFFER_INTERACTIVE)
    thisp->inherited::setDoubleBuffer(FALSE);

  // Back to static drawstyle.
  if (!thisp->drawInteractiveAsStill())
    thisp->changeDrawStyle(thisp->drawstyles[STILL]);
}

/*!
  \internal

  Called repeatedly during the seek animation.
 */
void
SoQtViewer::seeksensorCB(void * data, SoSensor * s)
{
  SbTime currenttime = SbTime::getTimeOfDay();

  SoQtViewer * thisp = (SoQtViewer *)data;
  SoTimerSensor * sensor = (SoTimerSensor *)s;

  float t =
    (currenttime - sensor->getBaseTime()).getValue() / thisp->seekperiod;
  if ((t > 1.0f) || (t + sensor->getInterval().getValue() > 1.0f)) t = 1.0f;
  SbBool end = (t == 1.0f);

  t = 0.5f - cos(M_PI * t) * 0.5f;
  thisp->camera->position = thisp->camerastartposition +
    (thisp->cameraendposition - thisp->camerastartposition) * t;

  if (end) thisp->setSeekMode(FALSE);
}

#undef NO_HEADLIGHT
#undef NO_DRAWSTYLESETTING
