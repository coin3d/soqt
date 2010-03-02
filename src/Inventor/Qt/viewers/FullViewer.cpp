/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) by Kongsberg Oil & Gas Technologies.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg Oil & Gas Technologies
 *  about acquiring a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg Oil & Gas Technologies, Bygdoy Alle 5, 0257 Oslo, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

// ************************************************************************

// Class is documented in common/viewers/SoGuiFullViewer.cpp.in.

// ************************************************************************

// FIXME: this sourcefile is way too large -- this reeks of bad
// design. Should try to factor out lots of stuff. 20010821 mortene.

// FIXME: can hide more stuff from the public header file into
// SoQtFullViewerP -- most or all of the private methods, for
// instance. 20010821 mortene.

//    FIXME, low priority:
//     * add tooltips to the widgets?
//     * trim length of edit fields

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H
#include <qt-config.h>

#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qmetaobject.h>
#include <qpixmap.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qslider.h>

#ifdef HAVE_QSTYLEFACTORY_H
#include <qstylefactory.h>
#endif // HAVE_QSTYLEFACTORY_H

#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/errors/SoDebugError.h>

#include <Inventor/Qt/viewers/SoQtFullViewerP.h>
#include <Inventor/Qt/viewers/moc_SoQtFullViewerP.icc>

#include <soqtdefs.h>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/widgets/SoQtThumbWheel.h>
#include <Inventor/Qt/widgets/SoQtPopupMenu.h>
#include <Inventor/Qt/viewers/SoQtFullViewer.h>
#include <Inventor/Qt/SoAny.h>

// Button icons.
#include <Inventor/Qt/common/pixmaps/pick.xpm>
#include <Inventor/Qt/common/pixmaps/view.xpm>
#include <Inventor/Qt/common/pixmaps/home.xpm>
#include <Inventor/Qt/common/pixmaps/set_home.xpm>
#include <Inventor/Qt/common/pixmaps/view_all.xpm>
#include <Inventor/Qt/common/pixmaps/seek.xpm>


// ************************************************************************

// Take care of namespace incompatibilities between Qt 3 and Qt 4.

#if QT_VERSION < 0x040000 // pre Qt 4
#define QTWIDGET_NOFOCUS QWidget::NoFocus
#else // Qt 4.0.0+
#define QTWIDGET_NOFOCUS Qt::NoFocus
#endif // Qt 4.0.0+

// *************************************************************************

SOQT_OBJECT_ABSTRACT_SOURCE(SoQtFullViewer);

// *************************************************************************

static const int VIEWERBORDER = 2;
static const int ZOOMSLIDERRESOLUTION = 200;

// *************************************************************************

// Button index values.
enum {
  INTERACT_BUTTON = 0,
  EXAMINE_BUTTON,
  HOME_BUTTON,
  SET_HOME_BUTTON,
  VIEW_ALL_BUTTON,
  SEEK_BUTTON
};

// *************************************************************************

#define PUBLIC(o) (o->pub)
#define PRIVATE(o) (o->pimpl)

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
SoQtFullViewer::SoQtFullViewer(QWidget * parent,
                               const char * name,
                               SbBool embed,
                               SoQtFullViewer::BuildFlag buildFlag,
                               SoQtViewer::Type type,
                               SbBool build)
  : inherited(parent, name, embed, type, FALSE)
{
  PRIVATE(this) = new SoQtFullViewerP(this);

  PRIVATE(this)->viewerwidget = NULL;
  PRIVATE(this)->canvas = NULL;
//  PRIVATE(this)->canvasparent = NULL;

  PRIVATE(this)->viewbutton = NULL;
  PRIVATE(this)->interactbutton = NULL;

  this->leftDecoration = NULL;
  this->bottomDecoration = NULL;
  this->rightDecoration = NULL;

  this->leftWheel = NULL;
  this->leftWheelLabel = NULL;
  this->leftWheelStr = NULL;
  this->leftWheelVal = 0.0f;

  this->bottomWheel = NULL;
  this->bottomWheelLabel = NULL;
  this->bottomWheelStr = NULL;
  this->bottomWheelVal = 0.0f;

  this->rightWheel = NULL;
  this->rightWheelLabel = NULL;
  this->rightWheelStr = NULL;
  this->rightWheelVal = 0.0f;

  this->setLeftWheelString("Motion X");
  this->setBottomWheelString("Motion Y");
  this->setRightWheelString("Motion Z");

  PRIVATE(this)->mainlayout = NULL;
  PRIVATE(this)->appbuttonlayout = NULL;

  PRIVATE(this)->menuenabled = buildFlag & SoQtFullViewer::BUILD_POPUP;
  PRIVATE(this)->decorations =
    (buildFlag & SoQtFullViewer::BUILD_DECORATION) ? TRUE : FALSE;

  this->prefmenu = NULL;
  PRIVATE(this)->menutitle = "Viewer Menu";

  PRIVATE(this)->viewerbuttons = new SbPList;
  PRIVATE(this)->appbuttonlist = new SbPList;
  PRIVATE(this)->appbuttonform = NULL;

  this->setSize(SbVec2s(500, 390));

  if (! build) return;

  this->setClassName("SoQtFullViewer");
  QWidget * viewer = this->buildWidget(this->getParentWidget());
  this->setBaseWidget(viewer);
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
SoQtFullViewer::~SoQtFullViewer()
{
  if (PRIVATE(this)->viewerwidget) {
    this->unregisterWidget(PRIVATE(this)->viewerwidget);
  }

  delete PRIVATE(this)->viewerbuttons;
  delete PRIVATE(this)->appbuttonlist;

  delete [] this->leftWheelStr;
  delete [] this->rightWheelStr;
  delete [] this->bottomWheelStr;

  if (this->prefmenu) {
    delete this->prefmenu;
  }

  delete PRIVATE(this);
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
void
SoQtFullViewer::setDecoration(const SbBool enable)
{
#if SOQT_DEBUG
  if ((enable  && this->isDecoration()) ||
       (!enable && !this->isDecoration())) {
    SoDebugError::postWarning("SoQtFullViewer::setDecoration",
                              "decorations already turned %s",
                              enable ? "on" : "off");
    return;
  }
#endif // SOQT_DEBUG

  PRIVATE(this)->decorations = enable;
  if (PRIVATE(this)->viewerwidget)
    PRIVATE(this)->showDecorationWidgets(enable);
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
SbBool
SoQtFullViewer::isDecoration(void) const
{
  return PRIVATE(this)->decorations;
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
void
SoQtFullViewer::setPopupMenuEnabled(const SbBool enable)
{
#if SOQT_DEBUG
  if ((enable && this->isPopupMenuEnabled()) ||
       (!enable && !this->isPopupMenuEnabled())) {
    SoDebugError::postWarning("SoQtFullViewer::setPopupMenuEnabled",
                              "popup menu already turned %s",
                              enable ? "on" : "off");
    return;
  }
#endif // SOQT_DEBUG
  PRIVATE(this)->menuenabled = enable;
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
SbBool
SoQtFullViewer::isPopupMenuEnabled(void) const
{
  return PRIVATE(this)->menuenabled;
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
QWidget *
SoQtFullViewer::getAppPushButtonParent(void) const
{
  return PRIVATE(this)->appbuttonform;
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
void
SoQtFullViewer::addAppPushButton(QWidget * newButton)
{
  PRIVATE(this)->appbuttonlist->append(newButton);
  PRIVATE(this)->layoutAppButtons(this->getAppPushButtonParent());
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
void
SoQtFullViewer::insertAppPushButton(QWidget * newButton, int index)
{
#if SOQT_DEBUG
  if ((index < 0) || (index > this->lengthAppPushButton())) {
    SoDebugError::postWarning("SoQtFullViewer::insertAppPushButton",
                              "index %d out of bounds", index);
    return;
  }
#endif // SOQT_DEBUG
  PRIVATE(this)->appbuttonlist->insert(newButton, index);
  PRIVATE(this)->layoutAppButtons(this->getAppPushButtonParent());
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
void
SoQtFullViewer::removeAppPushButton(QWidget * oldButton)
{
  int idx = PRIVATE(this)->appbuttonlist->find(oldButton);

#if SOQT_DEBUG
  if (idx == -1) {
    SoDebugError::postWarning("SoQtFullViewer::removeAppPushButton",
                              "tried to remove non-existant button");
    return;
  }
#endif // SOQT_DEBUG

  PRIVATE(this)->appbuttonlist->remove(idx);
  PRIVATE(this)->layoutAppButtons(this->getAppPushButtonParent());
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
int
SoQtFullViewer::findAppPushButton(QWidget * oldButton) const
{
  return PRIVATE(this)->appbuttonlist->find(oldButton);
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
int
SoQtFullViewer::lengthAppPushButton(void) const
{
  return PRIVATE(this)->appbuttonlist->getLength();
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
QWidget *
SoQtFullViewer::getRenderAreaWidget(void) const
{
  return PRIVATE(this)->canvas;
}

// *************************************************************************

// Documented in superclass. Overridden from parent class to correctly
// set the user interface indicators on the current state, i.e. to
// flip the examine and interact pushbuttons and to grey out the seek
// mode activation button iff in interact mode.
void
SoQtFullViewer::setViewing(SbBool enable)
{
  if ((enable && this->isViewing()) ||
       (!enable && !this->isViewing())) {
#if SOQT_DEBUG && 0 // debug
    SoDebugError::postWarning("SoQtFullViewer::setViewing",
                              "view mode already %s", on ? "on" : "off");
#endif // debug
    return;
  }

  inherited::setViewing(enable);

  // Must check that buttons have been built, in case this viewer
  // component was made without decorations.
  if (PRIVATE(this)->viewerbuttons->getLength() > 0) {
#if QT_VERSION >= 0x040000
    PRIVATE(this)->getViewerbutton(EXAMINE_BUTTON)->setChecked(enable);
    PRIVATE(this)->getViewerbutton(INTERACT_BUTTON)->setChecked(enable ? FALSE : TRUE);
#else
    PRIVATE(this)->getViewerbutton(EXAMINE_BUTTON)->setOn(enable);
    PRIVATE(this)->getViewerbutton(INTERACT_BUTTON)->setOn(enable ? FALSE : TRUE);
#endif
    PRIVATE(this)->getViewerbutton(SEEK_BUTTON)->setEnabled(enable);
  }
}

// *************************************************************************

// Documented in superclass.
QWidget *
SoQtFullViewer::buildWidget(QWidget * parent)
{
  // This will build the main view widgets, along with the decorations
  // widgets and popup menu if they are enabled.

#if SOQT_DEBUG && 0
  SoDebugError::postInfo("SoQtFullViewer::buildWidget", "[invoked]");
#endif

  PRIVATE(this)->viewerwidget = new QWidget(parent);
  this->registerWidget(PRIVATE(this)->viewerwidget);

  PRIVATE(this)->viewerwidget->move(0, 0);

#if SOQT_DEBUG && 0
  PRIVATE(this)->viewerwidget->setBackgroundColor(QColor(250, 0, 0));
#endif

  PRIVATE(this)->canvas = inherited::buildWidget(PRIVATE(this)->viewerwidget);

  QSize s(PRIVATE(this)->viewerwidget->size().width(),
          PRIVATE(this)->viewerwidget->size().height());

  PRIVATE(this)->canvas->resize(s);

  this->buildDecoration( PRIVATE(this)->viewerwidget );
  PRIVATE(this)->showDecorationWidgets( PRIVATE(this)->decorations );

  if (PRIVATE(this)->menuenabled)
    this->buildPopupMenu();

  return PRIVATE(this)->viewerwidget;
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
void
SoQtFullViewer::buildDecoration(QWidget * parent)
{
  this->leftDecoration = this->buildLeftTrim(parent);
  this->bottomDecoration = this->buildBottomTrim(parent);
  this->rightDecoration = this->buildRightTrim(parent);
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
QWidget *
SoQtFullViewer::buildLeftTrim(QWidget * parent)
{
  QWidget * w = new QWidget(parent);
  w->setFixedWidth(30);

  QGridLayout * gl = new QGridLayout(w);
#if QT_VERSION >= 0x040000
  gl->setContentsMargins(0,0,0,0);
#endif
  gl->addWidget(this->buildAppButtons(w), 0, 0);

  SoQtThumbWheel * t = new SoQtThumbWheel(SoQtThumbWheel::Vertical, w);
  this->leftWheel = t;
  t->setRangeBoundaryHandling(SoQtThumbWheel::ACCUMULATE);
  this->leftWheelVal = t->value();

  QObject::connect(t, SIGNAL(wheelMoved(float)), PRIVATE(this), SLOT(leftWheelChanged(float)));
  QObject::connect(t, SIGNAL(wheelPressed()), PRIVATE(this), SLOT(leftWheelPressed()));
  QObject::connect(t, SIGNAL(wheelReleased()), PRIVATE(this), SLOT(leftWheelReleased()));

  gl->addWidget(t, 1, 0, Qt::AlignBottom | Qt::AlignHCenter);
  gl->activate();

  return w;
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
QWidget *
SoQtFullViewer::buildBottomTrim(QWidget * parent)
{
  QWidget * w = new QWidget(parent);
  w->setFixedHeight(30);

  QLabel * label = new QLabel(this->leftWheelStr, w);
  label->adjustSize();
  label->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  label->setMargin(2);
  this->leftWheelLabel = label;

  label = new QLabel(this->bottomWheelStr, w);
  label->adjustSize();
  label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  label->setMargin(2);
  this->bottomWheelLabel = label;

  label = new QLabel(this->rightWheelStr, w);
  label->adjustSize();
  label->setAlignment(Qt::AlignRight | Qt::AlignTop);
  label->setMargin(2);
  this->rightWheelLabel = label;

  SoQtThumbWheel * t = new SoQtThumbWheel(SoQtThumbWheel::Horizontal, w);
  this->bottomWheel = t;
  t->setRangeBoundaryHandling(SoQtThumbWheel::ACCUMULATE);

  QObject::connect(t, SIGNAL(wheelMoved(float)),
                   PRIVATE(this), SLOT(bottomWheelChanged(float)));
  QObject::connect(t, SIGNAL(wheelPressed()),
                   PRIVATE(this), SLOT(bottomWheelPressed()));
  QObject::connect(t, SIGNAL(wheelReleased()),
                   PRIVATE(this), SLOT(bottomWheelReleased()));

  this->bottomWheelVal = t->value();

  QGridLayout * layout = new QGridLayout(w);
#if QT_VERSION >= 0x040000
  layout->setContentsMargins(0,0,0,0);
#endif
  layout->addWidget(this->leftWheelLabel, 0, 0, Qt::AlignVCenter | Qt::AlignHCenter);
  layout->addWidget(this->bottomWheelLabel, 0,1,  Qt::AlignVCenter | Qt::AlignRight);
  layout->addWidget(t, 0,2, Qt::AlignVCenter | Qt::AlignLeft);
  layout->addItem(new QSpacerItem(0,0,QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding),0, 3);
  layout->addWidget(this->rightWheelLabel, 0, 4,Qt::AlignVCenter | Qt::AlignRight);

  layout->activate();
  return w;
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
QWidget *
SoQtFullViewer::buildRightTrim(QWidget * parent)
{
  QWidget * w = new QWidget(parent);
  // FIXME: should be set according to width of viewer
  // buttons. 20000424 mortene.
  w->setFixedWidth(30);
  // FIXME: nope, trims are actually guaranteed to be 30 pixels wide

  SoQtThumbWheel * t = new SoQtThumbWheel(SoQtThumbWheel::Vertical, w);
  this->rightWheel = t;
  t->setRangeBoundaryHandling(SoQtThumbWheel::ACCUMULATE);
  this->rightWheelVal = t->value();

  QObject::connect(t, SIGNAL(wheelMoved(float)),
                   PRIVATE(this), SLOT(rightWheelChanged(float)));
  QObject::connect(t, SIGNAL(wheelPressed()),
                   PRIVATE(this), SLOT(rightWheelPressed()));
  QObject::connect(t, SIGNAL(wheelReleased()),
                   PRIVATE(this), SLOT(rightWheelReleased()));

  QGridLayout * l = new QGridLayout(w);
#if QT_VERSION >= 0x040000
  l->setContentsMargins(0,0,0,0);
  l->setVerticalSpacing(0);
#endif
  l->setMargin(0);
  l->addWidget(this->buildViewerButtons(w), 0, 0);
  l->addWidget(t, 2, 0, Qt::AlignBottom | Qt::AlignHCenter);
  l->activate();

  return w;
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
QWidget *
SoQtFullViewer::buildAppButtons(QWidget * parent)
{
  PRIVATE(this)->appbuttonform = new QWidget(parent);
  PRIVATE(this)->appbuttonform->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

  if (this->lengthAppPushButton() > 0)
    PRIVATE(this)->layoutAppButtons(PRIVATE(this)->appbuttonform);

  return PRIVATE(this)->appbuttonform;
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
QWidget *
SoQtFullViewer::buildViewerButtons(QWidget * parent)
{
  QWidget * w = new QWidget(parent);
  this->createViewerButtons(w, PRIVATE(this)->viewerbuttons);
  w->move(0, 0);
  w->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

  // assert(PRIVATE(this)->viewerbuttons->getLength() != 0);
  QGridLayout * l =
    new QGridLayout(w);
  l->setMargin(0);
#if QT_VERSION >= 0x040000
  l->setVerticalSpacing(0);
#endif

  const int numViewerButtons = PRIVATE(this)->viewerbuttons->getLength();
  for (int i = 0; i < numViewerButtons; i++) {
    QPushButton * b = PRIVATE(this)->getViewerbutton(i);
    b->setFixedSize(30, 30);
    b->setFocusPolicy(QTWIDGET_NOFOCUS);
    l->addWidget(b, i, 0);
  }

  l->activate();
  return w;
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
void
SoQtFullViewer::createViewerButtons(QWidget * parent, SbPList * buttonlist)
{
  for (int i=0; i <= SEEK_BUTTON; i++) {
    QPushButton * p = new QPushButton(parent);
    // Button focus doesn't really make sense in the way we're using
    // the pushbuttons.
    p->setFocusPolicy(QTWIDGET_NOFOCUS);

#if QT_VERSION >= 0x040000 // Qt 4.*
    // In some GUI styles in Qt4, a default button is drawn with an
    // extra frame around it, up to 3 pixels or more. This causes
    // pixmaps on buttons to look tiny, which is not what we want.
    p->setIconSize(QSize(24, 24));
#endif

#if (defined Q_WS_MAC && QT_VERSION >= 0x030100) && defined(HAVE_QSTYLEFACTORY_H)
    // Since Qt/Mac 3.1.x, all pushbuttons (even those < 32x32) are drawn
    // using the Aqua style, i.e. with rounded edges and shading. This
    // looks really ugly in the viewer decoration. Drawing the buttons
    // in the Windows style gives us the flat, square buttons we want.
    QStyle * style = QStyleFactory::create("windows");
    if (style) { p->setStyle(style); }
#endif

    // FIXME: its wrong to cast xpm data to (const char **), it
    // _should_ be (const char * const []), but this is not valid ANSI
    // C++. Not sure what to do about this (and the wrong cast can
    // (and has) in fact lead to bugs, so the situation should be
    // resolved). 20000505 mortene.

    switch (i) {
    case INTERACT_BUTTON:
      PRIVATE(this)->interactbutton = p;
#if QT_VERSION >= 0x040000
      p->setCheckable(TRUE);
      p->setChecked(this->isViewing() ? FALSE : TRUE);
      p->setIcon(QPixmap((const char **)pick_xpm));
#else
      p->setToggleButton(TRUE);
      p->setOn(this->isViewing() ? FALSE : TRUE);
      p->setPixmap(QPixmap((const char **)pick_xpm));
#endif
      QObject::connect(p, SIGNAL(clicked()),
                       PRIVATE(this), SLOT(interactbuttonClicked()));
      break;
    case EXAMINE_BUTTON:
      PRIVATE(this)->viewbutton = p;
#if QT_VERSION >= 0x040000
      p->setCheckable(TRUE);
      p->setChecked(this->isViewing());
      p->setIcon(QPixmap((const char **)view_xpm));
#else
      p->setToggleButton(TRUE);
      p->setOn(this->isViewing());
      p->setPixmap(QPixmap((const char **)view_xpm));
#endif
      QObject::connect(p, SIGNAL(clicked()),
                       PRIVATE(this), SLOT(viewbuttonClicked()));
      break;
    case HOME_BUTTON:
      QObject::connect(p, SIGNAL(clicked()), PRIVATE(this), SLOT(homebuttonClicked()));
#if QT_VERSION >= 0x040000
      p->setIcon(QPixmap((const char **)home_xpm));
#else
      p->setPixmap(QPixmap((const char **)home_xpm));
#endif
      break;
    case SET_HOME_BUTTON:
      QObject::connect(p, SIGNAL(clicked()),
                       PRIVATE(this), SLOT(sethomebuttonClicked()));
#if QT_VERSION >= 0x040000
      p->setIcon(QPixmap((const char **)set_home_xpm));
#else
      p->setPixmap(QPixmap((const char **)set_home_xpm));
#endif
      break;
    case VIEW_ALL_BUTTON:
      QObject::connect(p, SIGNAL(clicked()),
                       PRIVATE(this), SLOT(viewallbuttonClicked()));
#if QT_VERSION >= 0x040000
      p->setIcon(QPixmap((const char **)view_all_xpm));
#else
      p->setPixmap(QPixmap((const char **)view_all_xpm));
#endif
      break;
    case SEEK_BUTTON:
      QObject::connect(p, SIGNAL(clicked()), PRIVATE(this), SLOT(seekbuttonClicked()));
#if QT_VERSION >= 0x040000
      p->setIcon(QPixmap((const char **)seek_xpm));
#else
      p->setPixmap(QPixmap((const char **)seek_xpm));
#endif
      break;
    default:
      assert(0);
      break;
    }

    p->adjustSize();
    buttonlist->append(p);
  }
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
void
SoQtFullViewer::buildPopupMenu(void)
{
  this->prefmenu = PRIVATE(this)->setupStandardPopupMenu();
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
void
SoQtFullViewer::openPopupMenu(const SbVec2s position)
{
  if (! this->isPopupMenuEnabled()) return;
  if (this->prefmenu == NULL)
    this->buildPopupMenu();
  int x = 2 + position[0];
  int y = 2 + this->getGLSize()[1] - position[1] - 1;

  PRIVATE(this)->prepareMenu(this->prefmenu);
  this->prefmenu->popUp(this->getGLWidget(), x, y);
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
void
SoQtFullViewer::setLeftWheelString(const char * const string)
{
  delete [] this->leftWheelStr;
  this->leftWheelStr = NULL;

  if (string)
    this->leftWheelStr = strcpy(new char [strlen(string)+1], string);
  if (this->leftWheelLabel)
    ((QLabel *)this->leftWheelLabel)->setText(string ? string : "");
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
void
SoQtFullViewer::setBottomWheelString(const char * const string)
{
  delete [] this->bottomWheelStr;
  this->bottomWheelStr = NULL;

  if (string)
    this->bottomWheelStr = strcpy(new char [strlen(string)+1], string);
  if (this->bottomWheelLabel)
    ((QLabel *)this->bottomWheelLabel)->setText(string ? string : "");
}

// *************************************************************************

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
const char *
SoQtFullViewer::getRightWheelString() const
{
  return this->rightWheelStr;
}

// Documented in common/viewers/SoGuiFullViewer.cpp.in.
void
SoQtFullViewer::setRightWheelString(const char * const string)
{
  delete [] this->rightWheelStr;
  this->rightWheelStr = NULL;

  if (string)
    this->rightWheelStr = strcpy(new char [strlen(string)+1], string);
  if (this->rightWheelLabel)
    ((QLabel *)this->rightWheelLabel)->setText(string ? string : "");
}

// *************************************************************************

// doc in super
void
SoQtFullViewer::sizeChanged(const SbVec2s & size)
{

#if SOQT_DEBUG && 0
  SoDebugError::postInfo("SoQtFullViewer::sizeChanged", "(%d, %d)",
                         size[0], size[1]);
#endif

  SbVec2s newsize(size);
  if (PRIVATE(this)->decorations) {
    newsize[0] -= this->leftDecoration ? this->leftDecoration->width() : 0;
    newsize[0] -= this->rightDecoration ? this->rightDecoration->width() : 0;
    newsize[1] -= this->bottomDecoration ? this->bottomDecoration->height() : 0;
  }

  // Workaround for a bug in Qt/Mac 3.1.0 and 3.1.1 (which has been
  // confirmed fixed in 3.1.2):
  //
  // If the OpenGL context overlaps with the QSizeGrip widget
  // (generated by default), resizing does not work any more. The
  // workaround is to leave 15 pixels at the lower border of the
  // window blank...
#if defined Q_WS_MAC && ((QT_VERSION == 0x030100) || (QT_VERSION == 0x030101))

  // Environment variable to override Qt/Mac 3.1.x workarounds.
  const char * forcenoresizeworkaround =
    SoAny::si()->getenv("FORCE_NO_QTMAC_31_RESIZE_WORKAROUND");
  if (!forcenoresizeworkaround || (atoi(forcenoresizeworkaround) == 0)) {

    if (!PRIVATE(this)->decorations) { // GL context would fill whole window
       newsize -= SbVec2s(0, 15);       // -> leave lowermost 15 px blank

      // spit out a warning that this is a Qt/Mac bug, not an SoQt problem
      const char * env = SoAny::si()->getenv("SOQT_NO_QTMAC_BUG_WARNINGS");
      if (!env || !atoi(env)) {
        SoDebugError::postWarning("SoQtFullViewer::sizeChanged",
                                  "\nThis version of Qt/Mac contains a bug "
                                  "that makes it necessary to leave the\n"
                                  "lowermost 15 pixels of the viewer window "
                                  "blank. Set the environment variable\n"
                                  "FORCE_NO_QTMAC_31_RESIZE_WORKAROUND=1 to "
                                  "override this workaround. \n"
                                  "You can turn off warnings about Qt/Mac "
                                  "bugs permanently by setting \n"
                                  "SOQT_NO_QTMAC_BUG_WARNINGS=1.\n");
      }
    }
  }

#endif

  newsize = SbVec2s(SoQtMax(newsize[0], (short)1),
                    SoQtMax(newsize[1], (short)1));

  inherited::sizeChanged(newsize);
}

// *************************************************************************

#ifndef DOXYGEN_SKIP_THIS

// Show or hide decorations. Will make and activate a Qt layout grid
// if we're turning the decorations on.
void
SoQtFullViewerP::showDecorationWidgets(SbBool onOff)
{
#if SOQT_DEBUG && 0
  SoDebugError::postInfo("SoQtFullViewerP::showDecorationWidgets", "[invoked]");
#endif // SOQT_DEBUG

  if (this->mainlayout) delete this->mainlayout;

  assert(this->viewerwidget);

  assert(PUBLIC(this)->leftDecoration && PUBLIC(this)->bottomDecoration && PUBLIC(this)->rightDecoration);
  if (onOff) {
    PUBLIC(this)->leftDecoration->show();
    PUBLIC(this)->bottomDecoration->show();
    PUBLIC(this)->rightDecoration->show();

#if QT_VERSION >= 0x040000
    this->viewerwidget->setContentsMargins(0,0,0,0);
#endif

    QGridLayout * g = new QGridLayout(this->viewerwidget); // VIEWERBORDER);
    g->setSpacing(0);
#if QT_VERSION >= 0x040000
    g->setContentsMargins(0,0,0,0);
#endif

    g->addWidget(PUBLIC(this)->bottomDecoration, 1, 0);

    QGridLayout * subLayout = new QGridLayout();
    g->addLayout(subLayout, 0, 0);
#if QT_VERSION >= 0x040000
    subLayout->setVerticalSpacing(0);
    subLayout->setContentsMargins(0,0,0,0);
#endif

    PUBLIC(this)->leftDecoration->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));

    subLayout->addWidget(PUBLIC(this)->leftDecoration, 0, 0);
    this->canvas->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
    subLayout->addWidget(this->canvas, 0, 1);
    subLayout->addWidget(PUBLIC(this)->rightDecoration, 0, 2);

    this->mainlayout = g;
  } else {
    QGridLayout * g = new QGridLayout(this->viewerwidget);
    g->addWidget(this->canvas, 0, 0);
#if QT_VERSION >= 0x040000
    g->setContentsMargins(0,0,0,0);
#endif
    this->mainlayout = g;

    PUBLIC(this)->leftDecoration->hide();
    PUBLIC(this)->bottomDecoration->hide();
    PUBLIC(this)->rightDecoration->hide();
  }

  this->mainlayout->activate();
  QSize size = this->viewerwidget->size();
  SbVec2s rasize = SbVec2s(size.width(), size.height());
  PUBLIC(this)->sizeChanged(rasize);
}

// *************************************************************************

// Layout application specified buttons.
void
SoQtFullViewerP::layoutAppButtons(QWidget * form)
{
  delete this->appbuttonlayout; this->appbuttonlayout = NULL;

  int nrbuttons = this->appbuttonlist->getLength();
  if (nrbuttons == 0) return;

  this->appbuttonlayout = new QGridLayout(form);
#if QT_VERSION >= 0x040000
  this->appbuttonlayout->setContentsMargins(0,0,0,0);
#endif
  this->appbuttonlayout->setSpacing(0);

  for (int i=0; i < nrbuttons; i++) {
    QWidget * button = (QWidget *)((*(this->appbuttonlist))[i]);
    ((QGridLayout *)this->appbuttonlayout)->addWidget(button, i, 0);
    button->show();
  }

  this->appbuttonlayout->activate();
}

// *************************************************************************

// Qt slot.
void
SoQtFullViewerP::interactbuttonClicked(void)
{
  if (this->interactbutton)
#if QT_VERSION >= 0x040000
    ((QPushButton *)this->interactbutton)->setChecked(TRUE);
#else
    ((QPushButton *)this->interactbutton)->setOn(TRUE);
#endif
  if (this->viewbutton)
#if QT_VERSION >= 0x040000
    ((QPushButton *)this->viewbutton)->setChecked(FALSE);
#else
    ((QPushButton *)this->viewbutton)->setOn(FALSE);
#endif
  if (PUBLIC(this)->isViewing())
    PUBLIC(this)->setViewing(FALSE);
}

// *************************************************************************

// Qt slot.
void
SoQtFullViewerP::viewbuttonClicked(void)
{
  if (this->interactbutton)
#if QT_VERSION >= 0x040000
    ((QPushButton *)this->interactbutton)->setChecked(FALSE);
#else
    ((QPushButton *)this->interactbutton)->setOn(FALSE);
#endif
  if (this->viewbutton)
#if QT_VERSION >= 0x040000
    ((QPushButton *)this->viewbutton)->setChecked(TRUE);
#else
    ((QPushButton *)this->viewbutton)->setOn(TRUE);
#endif
  if (!PUBLIC(this)->isViewing())
    PUBLIC(this)->setViewing(TRUE);
}

// *************************************************************************

// Qt slot.
void
SoQtFullViewerP::homebuttonClicked()
{
  PUBLIC(this)->resetToHomePosition();
}

// *************************************************************************

// Qt slot.
void
SoQtFullViewerP::sethomebuttonClicked()
{
  PUBLIC(this)->saveHomePosition();
}

// *************************************************************************

// Qt slot.
void
SoQtFullViewerP::viewallbuttonClicked()
{
  PUBLIC(this)->viewAll();
}

// *************************************************************************

// Qt slot.
void
SoQtFullViewerP::seekbuttonClicked()
{
  PUBLIC(this)->setSeekMode(PUBLIC(this)->isSeekMode() ? FALSE : TRUE);
}

// *************************************************************************

// Qt slot.
void
SoQtFullViewerP::selectedViewing()
{
  PUBLIC(this)->setViewing(PUBLIC(this)->isViewing() ? FALSE : TRUE);
}

// *************************************************************************

// Qt slot.
void
SoQtFullViewerP::selectedDecoration()
{
  PUBLIC(this)->setDecoration(PUBLIC(this)->isDecoration() ? FALSE : TRUE);
}

// *************************************************************************

// Qt slot.
void
SoQtFullViewerP::selectedHeadlight()
{
  PUBLIC(this)->setHeadlight(PUBLIC(this)->isHeadlight() ? FALSE : TRUE);
}

// *************************************************************************

// Qt slot.
void
SoQtFullViewerP::increaseInteractiveCount()
{
  PUBLIC(this)->interactiveCountInc();
}

// *************************************************************************

// Qt slot.
void
SoQtFullViewerP::decreaseInteractiveCount()
{
  PUBLIC(this)->interactiveCountDec();
}

// *************************************************************************

SoQtFullViewerP::SoQtFullViewerP(SoQtFullViewer * publ)
  : SoGuiFullViewerP(publ)
{
}

SoQtFullViewerP::~SoQtFullViewerP()
{
}

void
SoQtFullViewerP::setThumbWheelValue(void * wheel, float val)
{
  ((SoQtThumbWheel *)wheel)->setValue(val);
}

// *************************************************************************

// These are all private slots for catching Qt events.
void SoQtFullViewerP::leftWheelPressed(void) { PUBLIC(this)->leftWheelStart(); }
void SoQtFullViewerP::leftWheelChanged(float v) { PUBLIC(this)->leftWheelMotion(v); }
void SoQtFullViewerP::leftWheelReleased(void) { PUBLIC(this)->leftWheelFinish(); }
void SoQtFullViewerP::bottomWheelPressed(void) { PUBLIC(this)->bottomWheelStart(); }
void SoQtFullViewerP::bottomWheelChanged(float v) { PUBLIC(this)->bottomWheelMotion(v);}
void SoQtFullViewerP::bottomWheelReleased(void) { PUBLIC(this)->bottomWheelFinish(); }
void SoQtFullViewerP::rightWheelPressed(void) { PUBLIC(this)->rightWheelStart(); }
void SoQtFullViewerP::rightWheelChanged(float v) { PUBLIC(this)->rightWheelMotion(v); }
void SoQtFullViewerP::rightWheelReleased(void) { PUBLIC(this)->rightWheelFinish(); }

// *************************************************************************

#endif // DOXYGEN_SKIP_THIS

#undef PUBLIC
#undef PRIVATE
